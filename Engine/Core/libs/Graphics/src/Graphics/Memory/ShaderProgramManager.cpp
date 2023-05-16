//
// Created by Monika on 11.07.2022.
//

#include <Graphics/Memory/ShaderProgramManager.h>
#include <Graphics/Types/Framebuffer.h>

namespace SR_GRAPH_NS::Memory {
    ShaderProgramManager::ShaderProgramManager()
        : SR_UTILS_NS::Singleton<ShaderProgramManager>()
        , m_pipeline(Environment::Get())
    {
        m_virtualTable.max_load_factor(0.9f);
        m_virtualTable.reserve(1000);
    }

    ShaderProgramManager::~ShaderProgramManager() { }

    void ShaderProgramManager::OnSingletonDestroy() {
        Singleton::OnSingletonDestroy();
    }

    ShaderProgramManager::VirtualProgram ShaderProgramManager::Allocate(const SRShaderCreateInfo &createInfo) {
        SR_LOCK_GUARD

        VirtualProgram virtualProgram = GenerateUnique();

        if (virtualProgram == SR_ID_INVALID) {
            SR_ERROR("ShaderProgramManager::Allocate() : failed to generate virtual program!");
            return SR_ID_INVALID;
        }

        VirtualProgramInfo virtualProgramInfo;
        virtualProgramInfo.m_createInfo = SRShaderCreateInfo(createInfo);

        if (auto&& shaderProgramInfo = AllocateShaderProgram(createInfo); shaderProgramInfo.Valid()) {
            virtualProgramInfo.m_data[m_pipeline->GetCurrentFramebufferId()] = shaderProgramInfo;
        }
        else {
            SR_ERROR("ShaderProgramManager::Allocate() : failed to allocate shader program!");
            return SR_ID_INVALID;
        }

        m_virtualTable.insert(std::make_pair(
                virtualProgram,
                std::move(virtualProgramInfo)
        ));

        return virtualProgram;
    }

    ShaderProgramManager::VirtualProgram ShaderProgramManager::ReAllocate(VirtualProgram program, const SRShaderCreateInfo& createInfo) {
        SR_LOCK_GUARD

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Medium) {
            SR_GRAPH_LOG("ShaderProgramManager::ReAllocate() : re-allocate shader program...");
        }

        if (program == SR_ID_INVALID) {
            return Allocate(createInfo);
        }

        auto&& pIt = m_virtualTable.find(program);
        if (pIt == m_virtualTable.end()) {
            SRHalt("ShaderProgramManager::ReAllocate() : virtual program not found!");
            return SR_ID_INVALID;
        }

        auto&& [_, virtualProgramInfo] = *pIt;

        EVK_PUSH_LOG_LEVEL(EvoVulkan::Tools::LogLevel::ErrorsOnly);

        /// очишаем старые шейдерные программы
        for (auto&& [fbo /** unused */, shaderProgramInfo] : virtualProgramInfo.m_data) {
            m_pipeline->DeleteShader(shaderProgramInfo.id);
        }
        virtualProgramInfo.m_data.clear();

        /// обновляем данные
        virtualProgramInfo.m_createInfo = SRShaderCreateInfo(createInfo);

        if (auto&& shaderProgramInfo = AllocateShaderProgram(createInfo); shaderProgramInfo.Valid()) {
            virtualProgramInfo.m_data[m_pipeline->GetCurrentFramebufferId()] = shaderProgramInfo;
            EVK_POP_LOG_LEVEL();
        }
        else {
            SR_ERROR("ShaderProgramManager::ReAllocate() : failed to allocate shader program!");
            EVK_POP_LOG_LEVEL();
            return SR_ID_INVALID;
        }

        return program;
    }

    ShaderProgramManager::VirtualProgram ShaderProgramManager::GenerateUnique() const {
        volatile VirtualProgram virtualProgram = SR_ID_INVALID;

        auto&& random = SR_UTILS_NS::Random::Instance();

        while (true) {
            VirtualProgram unique = random.Int32();

            /// можно использовать только положительные индексы
            if (unique < 0) {
                unique = -unique;
            }

            SRAssertOnce(unique >= 0);

            if (m_virtualTable.count(unique) == 0 && unique != SR_ID_INVALID) {
                virtualProgram = unique;
                break;
            }

            SR_WARN("ShaderProgramManager::GenerateUnique() : collision detected!");
        }

        return virtualProgram;
    }

    ShaderProgramManager::BindResult ShaderProgramManager::BindProgram(VirtualProgram virtualProgram) noexcept {
        SR_LOCK_GUARD

        auto&& pIt = m_virtualTable.find(virtualProgram);
        if (pIt == std::end(m_virtualTable)) {
            SRHalt("ShaderProgramManager::BindProgram() : virtual program not found!");
            return BindResult::Failed;
        }

        BindResult result = BindResult::Success;

        auto&& [_, virtualProgramInfo] = *pIt;
        auto&& framebufferId = m_pipeline->GetCurrentFramebufferId();
    retry:
        auto&& fboIt = virtualProgramInfo.m_data.find(framebufferId);
        if (fboIt == std::end(virtualProgramInfo.m_data))
        {
            if (auto&& shaderProgramInfo = AllocateShaderProgram(virtualProgramInfo.m_createInfo); shaderProgramInfo.Valid()) {
                virtualProgramInfo.m_data[m_pipeline->GetCurrentFramebufferId()] = shaderProgramInfo;
                result = BindResult::Duplicated;
                goto retry;
            }
            else {
                SR_ERROR("ShaderProgramManager::BindProgram() : failed to allocate shader program!");
                return BindResult::Failed;
            }
        }

        if (!BindShaderProgram(fboIt->second, virtualProgramInfo.m_createInfo)) {
            SR_ERROR("ShaderProgramManager::BindProgram() : failed to bind shader program!");
            return BindResult::Failed;
        }

        return result;
    }

    bool ShaderProgramManager::FreeProgram(VirtualProgram *program) {
        if (!SRVerifyFalse(!program)) {
            return false;
        }

        auto&& pIt = m_virtualTable.find(*program);
        if (pIt == std::end(m_virtualTable)) {
            SRHalt("ShaderProgramManager::FreeProgram() : virtual program not found!");
            return false;
        }

        auto&& [_, info] = *pIt;

        for (auto&& [fbo /** unused */, shaderProgramInfo] : info.m_data) {
            m_pipeline->DeleteShader(shaderProgramInfo.id);
        }

        m_virtualTable.erase(pIt);

        *program = SR_ID_INVALID;

        return true;
    }

    ShaderProgramManager::ShaderProgram ShaderProgramManager::GetProgram(VirtualProgram virtualProgram) const noexcept {
        SR_LOCK_GUARD

        auto&& pIt = m_virtualTable.find(virtualProgram);
        if (pIt == std::end(m_virtualTable)) {
            SRHalt("ShaderProgramManager::GetProgram() : virtual program not found!");
            return SR_ID_INVALID;
        }

        auto&& [_, info] = *pIt;
        auto&& framebufferId = m_pipeline->GetCurrentFramebufferId();
        auto&& fboIt = info.m_data.find(framebufferId);

        if (fboIt == std::end(info.m_data))
        {
            SRHalt("ShaderProgramManager::GetProgram() : framebuffer not found!");
            return SR_ID_INVALID;
        }

        return fboIt->second.id;
    }

    VirtualProgramInfo::ShaderProgramInfo ShaderProgramManager::AllocateShaderProgram(const SRShaderCreateInfo &createInfo) const {
        /// выделяем новую шейдерную программу
        auto&& framebufferId = m_pipeline->GetCurrentFramebufferId();

        auto&& shaderProgram = m_pipeline->AllocateShaderProgram(createInfo, framebufferId);
        if (shaderProgram == SR_ID_INVALID) {
            SR_ERROR("ShaderProgramManager::AllocateShaderProgram() : failed to allocate shader program!");
            return VirtualProgramInfo::ShaderProgramInfo();
        }

        VirtualProgramInfo::ShaderProgramInfo shaderProgramInfo;
        shaderProgramInfo.id = shaderProgram;

        if (auto&& pFramebuffer = m_pipeline->GetCurrentFramebuffer()) {
            shaderProgramInfo.samples = pFramebuffer->GetSamplesCount();
            shaderProgramInfo.depth = pFramebuffer->IsDepthEnabled();
        }
        else {
            shaderProgramInfo.samples = m_pipeline->GetSamplesCount();
            shaderProgramInfo.depth = createInfo.blendEnabled;
        }

        return shaderProgramInfo;
    }

    bool ShaderProgramManager::BindShaderProgram(VirtualProgramInfo::ShaderProgramInfo &shaderProgramInfo, const SRShaderCreateInfo& createInfo) {
        if (auto&& pFramebuffer = m_pipeline->GetCurrentFramebuffer()) {
            if (pFramebuffer->IsDepthEnabled() != shaderProgramInfo.depth || pFramebuffer->GetSamplesCount() != shaderProgramInfo.samples) {
                SR_LOG("ShaderProgramManager::BindShaderProgram() : the frame buffer parameters have been changed, the shader has been recreated...");
                m_pipeline->DeleteShader(shaderProgramInfo.id);
                if ((shaderProgramInfo = AllocateShaderProgram(createInfo)).Valid()) {
                    return BindShaderProgram(shaderProgramInfo, createInfo);
                }
                else {
                    SR_ERROR("ShaderProgramManager::BindShaderProgram() : failed to allocate shader program!");
                    return false;
                }
            }

            m_pipeline->UseShader(static_cast<ShaderProgram>(shaderProgramInfo.id));
        }
        else {
            m_pipeline->UseShader(static_cast<ShaderProgram>(shaderProgramInfo.id));
        }

        return true;
    }
}

