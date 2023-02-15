//
// Created by Monika on 10.06.2022.
//

#include <Graphics/Memory/UBOManager.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Pipeline/Environment.h>

namespace SR_GRAPH_NS::Memory {
    UBOManager::UBOManager()
        : m_pipeline(Environment::Get())
    {
        m_virtualTableSize = 1024 * 64;
        m_virtualTable = new VirtualUBOInfo[m_virtualTableSize];
        m_singleIdentifierMode = SR_UTILS_NS::Features::Instance().Enabled("SingleUBOIdentifierMode", false);
    }

    void UBOManager::SetIdentifier(void* pIdentifier) {
        m_identifier = m_singleIdentifierMode ? nullptr : pIdentifier;
    }

    void* UBOManager::GetIdentifier() const noexcept {
        return m_identifier;
    }

    void UBOManager::SetIgnoreIdentifiers(bool value) {
        SR_LOCK_GUARD
        m_ignoreIdentifier = value;
    }

    UBOManager::VirtualUBO UBOManager::AllocateUBO(uint32_t uboSize, uint32_t samples) {
        if (!m_identifier && !m_singleIdentifierMode && !m_ignoreIdentifier) {
            SRHalt("UBOManager::AllocateUBO() : identifier is nullptr!");
            return SR_ID_INVALID;
        }

        auto&& pShader = m_pipeline->GetCurrentShader();
        auto&& shaderProgram = pShader ? pShader->GetId() : SR_ID_INVALID;

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

        VirtualUBOInfo::ShaderInfo shaderInfo;
        shaderInfo.pShader = pShader;
        shaderInfo.shaderProgram = shaderProgram;
        shaderInfo.samples = samples;
        shaderInfo.uboSize = uboSize;

        VirtualUBOInfo virtualUboInfo;

        virtualUboInfo.m_data.emplace_back(VirtualUBOInfo::Data {
                m_ignoreIdentifier ? nullptr : m_identifier,
                descriptor,
                ubo,
                shaderInfo
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

        auto&& info = m_virtualTable[*virtualUbo];
        for (auto&& [pIdentifier, descriptor, ubo, shaderInfo] : info.m_data) {
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
        auto&& shaderIdStash = m_pipeline->GetCurrentShaderId();

        m_pipeline->SetCurrentShaderId(shader);

        const static std::vector<uint64_t> uniformTypes = {
                static_cast<uint64_t>(VulkanTools::CastAbsDescriptorTypeToVk(DescriptorType::Uniform))
        };

        const static std::vector<uint64_t> combinedImageTypes = {
                static_cast<uint64_t>(VulkanTools::CastAbsDescriptorTypeToVk(DescriptorType::CombinedImage))
        };

        if (uboSize > 0) {
            if (*descriptor = m_pipeline->AllocDescriptorSet(uniformTypes); *descriptor < 0) {
                SR_ERROR("UBOManager::AllocMemory() : failed to allocate descriptor set! (Uniform)");
                goto fails;
            }

            if (*ubo = m_pipeline->AllocateUBO(uboSize); *ubo < 0) {
                SR_ERROR("UBOManager::AllocMemory() : failed to allocate uniform buffer object!");
                goto fails;
            }
        }
        else if (samples > 0) {
            if (*descriptor = m_pipeline->AllocDescriptorSet(combinedImageTypes); *descriptor < 0) {
                SR_ERROR("UBOManager::AllocMemory() : failed to allocate descriptor set! (CombinedImage)");
                goto fails;
            }
        }

        SRAssert(*ubo != SR_ID_INVALID || *descriptor != SR_ID_INVALID || (uboSize == 0 && samples == 0));

        m_pipeline->SetCurrentShaderId(shaderIdStash);
        return true;

    fails:
        m_pipeline->SetCurrentShaderId(shaderIdStash);
        return false;
    }

    UBOManager::BindResult UBOManager::BindUBO(VirtualUBO virtualUbo) noexcept {
        auto&& pShader = m_pipeline->GetCurrentShader();

	#ifdef SR_DEBUG
        if (virtualUbo == SR_ID_INVALID) {
            SRHalt("UBOManager::BindUBO() : invalid virtual ubo!");
            return BindResult::Failed;
        }

        if (!m_identifier && !m_singleIdentifierMode && !m_ignoreIdentifier) {
            SRHalt("UBOManager::BindUBO() : identifier is nullptr!");
            return BindResult::Failed;
        }

        if (!pShader) {
            SRHaltOnce("Current shader is nullptr!");
            return BindResult::Failed;
        }
	#endif

        auto&& info = m_virtualTable[virtualUbo];
        BindResult result = BindResult::Success;

        Descriptor descriptor = SR_ID_INVALID;
        UBO ubo = SR_ID_INVALID;

        for (auto&& data : info.m_data) {
            if (data.pIdentifier == (m_ignoreIdentifier ? nullptr : m_identifier) && data.shaderInfo.pShader == pShader) {
                descriptor = data.descriptor;
                ubo = data.ubo;
                break;
            }
        }

        /// если не нашли камеру, то дублируем память под новую камеру
        if (descriptor == SR_ID_INVALID && ubo == SR_ID_INVALID)
        {
            VirtualUBOInfo::ShaderInfo shaderInfo;
            shaderInfo.pShader = pShader;
            shaderInfo.shaderProgram = pShader->GetId();
            shaderInfo.uboSize = pShader->GetUBOBlockSize();
            shaderInfo.samples = pShader->GetSamplersCount();

            if (!AllocMemory(&ubo, &descriptor, shaderInfo.uboSize, shaderInfo.samples, shaderInfo.shaderProgram)) {
                SR_ERROR("UBOManager::BindUBO() : failed to allocate memory!");
                return BindResult::Failed;
            }

            info.m_data.emplace_back(VirtualUBOInfo::Data {
                    m_ignoreIdentifier ? nullptr : m_identifier,
                    descriptor,
                    ubo,
                    shaderInfo
            });

            result = BindResult::Duplicated;
        }

        if (ubo != SR_ID_INVALID) {
            m_pipeline->BindUBO(ubo);
        }

        if (descriptor != SR_ID_INVALID) {
            m_pipeline->BindDescriptorSet(descriptor);
        }

        return result;
    }

    UBOManager::VirtualUBO UBOManager::ReAllocateUBO(VirtualUBO virtualUbo, uint32_t uboSize, uint32_t samples) {
        if (virtualUbo == SR_ID_INVALID) {
            return AllocateUBO(uboSize, samples);
        }

        auto&& pShader = m_pipeline->GetCurrentShader();
        auto&& shaderProgram = pShader ? pShader->GetId() : SR_ID_INVALID;

        if (shaderProgram == SR_ID_INVALID) {
            SR_ERROR("UBOManager::ReAllocateUBO() : shader program do not set!");
            return virtualUbo;
        }

        auto&& info = m_virtualTable[virtualUbo];

        /// очищаем ВСЕ старые данные
        for (auto&& [pIdentifier, descriptor, ubo, shaderInfo] : info.m_data) {
            FreeMemory(&ubo, &descriptor);
        }
        info.m_data.clear();

        /// выделяем ОДНУ новую юниформу с дескриптором
        Descriptor descriptor = SR_ID_INVALID;
        UBO ubo = SR_ID_INVALID;

        if (!AllocMemory(&ubo, &descriptor, uboSize, samples, shaderProgram)) {
            SR_ERROR("UBOManager::ReAllocateUBO() : failed to allocate memory!");
        }

        VirtualUBOInfo::ShaderInfo shaderInfo;
        shaderInfo.pShader = pShader;
        shaderInfo.shaderProgram = shaderProgram;
        shaderInfo.samples = samples;
        shaderInfo.uboSize = uboSize;

        info.m_data.emplace_back(VirtualUBOInfo::Data {
                m_ignoreIdentifier ? nullptr : m_identifier,
                descriptor,
                ubo,
                shaderInfo
        });

        return virtualUbo;
    }

    void UBOManager::FreeMemory(UBOManager::UBO *ubo, UBOManager::Descriptor *descriptor) {
        if (*ubo != SR_ID_INVALID && !m_pipeline->FreeUBO(ubo)) {
            SR_ERROR("UBOManager::FreeMemory() : failed to free ubo!");
        }

        if (*descriptor != SR_ID_INVALID && !m_pipeline->FreeDescriptorSet(descriptor)) {
            SR_ERROR("UBOManager::FreeMemory() : failed to free descriptor!");
        }
    }
}