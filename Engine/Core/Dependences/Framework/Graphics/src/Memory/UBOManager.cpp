//
// Created by Monika on 10.06.2022.
//

#include <Memory/UBOManager.h>
#include <Types/Camera.h>
#include <Environment/Environment.h>

namespace SR_GRAPH_NS::Memory {
    UBOManager::UBOManager() {
        m_virtualTableSize = 1024 * 64;
        m_virtualTable = new VirtualUBOInfo[m_virtualTableSize];
        m_singleCameraMode = SR_UTILS_NS::Features::Instance().Enabled("SingleCameraMode", false);
    }

    void UBOManager::SetCurrentCamera(Types::Camera *pCamera) {
        m_camera = m_singleCameraMode ? nullptr : pCamera;
    }

    UBOManager::VirtualUBO UBOManager::AllocateUBO(uint32_t uboSize, uint32_t samples) {
        if (!m_camera && !m_singleCameraMode && !m_ignoreCameras) {
            SRHalt("UBOManager::AllocateUBO() : camera is nullptr!");
            return SR_ID_INVALID;
        }

        auto&& env = Environment::Get();
        auto&& shaderProgram = env->GetCurrentShaderId();

        if (shaderProgram == SR_ID_INVALID) {
            SRHalt("UBOManager::AllocateUBO() : shader program do not set!");
            return SR_ID_INVALID;
        }

        const VirtualUBO virtualUbo = GenerateUnique();

        if (virtualUbo == SR_ID_INVALID) {
            SR_ERROR("UBOManager::AllocateUBO() : failed to get unique id!");
            return SR_ID_INVALID;
        }

        Descriptor descriptor = SR_ID_INVALID;
        UBO ubo = SR_ID_INVALID;

        if (!AllocMemory(&ubo, &descriptor, uboSize, samples, shaderProgram)) {
            SR_ERROR("UBOManager::AllocateUBO() : failed to allocate memory!");
            return SR_ID_INVALID;
        }

        VirtualUBOInfo virtualUboInfo;

        virtualUboInfo.m_samples = samples;
        virtualUboInfo.m_uboSize = uboSize;
        virtualUboInfo.m_shaderProgram = shaderProgram;

        virtualUboInfo.m_data.emplace_back(VirtualUBOInfo::Data {
                m_ignoreCameras ? nullptr : m_camera,
                descriptor,
                ubo
        });

        m_virtualTable[virtualUbo] = std::move(virtualUboInfo);

        return virtualUbo;
    }

    bool UBOManager::FreeUBO(UBOManager::VirtualUBO *virtualUbo) {
        if (!SRVerifyFalse(!virtualUbo)) {
            return false;
        }

        if (*virtualUbo >= m_virtualTableSize) {
            SRHalt("UBOManager::FreeUBO() : ubo not found!");
            return false;
        }

        auto&& env = Environment::Get();

        auto&& info = m_virtualTable[*virtualUbo];
        for (auto&& [pCamera, descriptor, ubo] : info.m_data) {
            FreeMemory(&ubo, &descriptor);
        }

        m_virtualTable[*virtualUbo].Reset();
        *virtualUbo = SR_ID_INVALID;

        return true;
    }

    UBOManager::VirtualUBO UBOManager::GenerateUnique() const {
        /// TODO: следует делать одновременно поиск с конца
        for (uint32_t i = 0; i < m_virtualTableSize; ++i) {
            if (m_virtualTable[i].Valid()) {
                continue;
            }

            return static_cast<VirtualUBO>(i);
        }

        SR_ERROR("UBOManager::GenerateUnique() : the virtual table overflow!");

        return SR_ID_INVALID;
    }

    bool UBOManager::AllocMemory(UBO *ubo, Descriptor *descriptor, uint32_t uboSize, uint32_t samples, int32_t shader) {
        auto&& env = Environment::Get();
        auto&& shaderIdStash = env->GetCurrentShaderId();

        env->SetCurrentShaderId(shader);

        if (uboSize > 0) {
            if (*descriptor = env->AllocDescriptorSet({DescriptorType::Uniform}); *descriptor < 0) {
                SR_ERROR("UBOManager::AllocMemory() : failed to allocate descriptor set!");
                goto fails;
            }

            if (*ubo = env->AllocateUBO(uboSize); *ubo < 0) {
                SR_ERROR("UBOManager::AllocMemory() : failed to allocate uniform buffer object!");
                goto fails;
            }
        }
        else if (samples > 0) {
            if (*descriptor = env->AllocDescriptorSet({DescriptorType::CombinedImage}); *descriptor < 0) {
                SR_ERROR("UBOManager::AllocMemory() : failed to allocate descriptor set!");
                goto fails;
            }
        }

        SRAssert(*ubo != SR_ID_INVALID || *descriptor != SR_ID_INVALID);

        env->SetCurrentShaderId(shaderIdStash);
        return true;

    fails:
        env->SetCurrentShaderId(shaderIdStash);
        return false;
    }

    UBOManager::BindResult UBOManager::BindUBO(VirtualUBO virtualUbo) noexcept {
        if (virtualUbo == SR_ID_INVALID) {
            SRHalt("UBOManager::BindUBO() : invalid virtual ubo!");
            return BindResult::Failed;
        }

        if (!m_camera && !m_singleCameraMode && !m_ignoreCameras) {
            SRHalt("UBOManager::BindUBO() : camera is nullptr!");
            return BindResult::Failed;
        }

        auto&& info = m_virtualTable[virtualUbo];
        BindResult result = BindResult::Success;

        Descriptor descriptor = SR_ID_INVALID;
        UBO ubo = SR_ID_INVALID;

        for (auto&& data : info.m_data) {
            if (data.pCamera == (m_ignoreCameras ? nullptr : m_camera)) {
                descriptor = data.descriptor;
                ubo = data.ubo;
                break;
            }
        }

        /// если не нашли камеру, то дублируем память под новую камеру
        if (descriptor == SR_ID_INVALID && ubo == SR_ID_INVALID)
        {
            if (!AllocMemory(&ubo, &descriptor, info.m_uboSize, info.m_samples, info.m_shaderProgram)) {
                SR_ERROR("UBOManager::BindUBO() : failed to allocate memory!");
                return BindResult::Failed;
            }

            info.m_data.emplace_back(VirtualUBOInfo::Data {
                    m_ignoreCameras ? nullptr : m_camera,
                    descriptor,
                    ubo
            });

            result = BindResult::Duplicated;
        }

        auto&& env = Environment::Get();

        if (ubo != SR_ID_INVALID) {
            env->BindUBO(ubo);
        }

        if (descriptor != SR_ID_INVALID) {
            env->BindDescriptorSet(descriptor);
        }

        return result;
    }

    UBOManager::VirtualUBO UBOManager::ReAllocateUBO(VirtualUBO virtualUbo, uint32_t uboSize, uint32_t samples) {
        if (virtualUbo == SR_ID_INVALID) {
            return AllocateUBO(uboSize, samples);
        }

        auto&& env = Environment::Get();
        auto&& shaderProgram = env->GetCurrentShaderId();

        if (shaderProgram == SR_ID_INVALID) {
            SR_ERROR("UBOManager::ReAllocateUBO() : shader program do not set!");
            return virtualUbo;
        }

        auto&& info = m_virtualTable[virtualUbo];

        /// задаем новые значения для дублирования памяти
        info.m_uboSize = uboSize;
        info.m_samples = samples;
        info.m_shaderProgram = shaderProgram;

        /// очищаем ВСЕ старые данные
        for (auto&& [pCamera, descriptor, ubo] : info.m_data) {
            FreeMemory(&ubo, &descriptor);
        }
        info.m_data.clear();

        /// выделяем ОДНУ новую юниформу с дескриптором
        Descriptor descriptor = SR_ID_INVALID;
        UBO ubo = SR_ID_INVALID;

        if (!AllocMemory(&ubo, &descriptor, info.m_uboSize, info.m_samples, info.m_shaderProgram)) {
            SR_ERROR("UBOManager::ReAllocateUBO() : failed to allocate memory!");
        }

        info.m_data.emplace_back(VirtualUBOInfo::Data {
                m_ignoreCameras ? nullptr : m_camera,
                descriptor,
                ubo
        });

        return virtualUbo;
    }

    void UBOManager::FreeMemory(UBOManager::UBO *ubo, UBOManager::Descriptor *descriptor) {
        auto&& env = Environment::Get();

        if (*ubo != SR_ID_INVALID && !env->FreeUBO(ubo)) {
            SR_ERROR("UBOManager::FreeMemory() : failed to free ubo!");
        }

        if (*descriptor != SR_ID_INVALID && !env->FreeDescriptorSet(descriptor)) {
            SR_ERROR("UBOManager::FreeMemory() : failed to free descriptor!");
        }
    }

    void UBOManager::SetIgnoreCameras(bool value) {
        SR_LOCK_GUARD
        m_ignoreCameras = value;
    }
}