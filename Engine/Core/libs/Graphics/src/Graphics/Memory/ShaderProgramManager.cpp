//
// Created by Monika on 11.07.2022.
//

#include <Utils/Common/Numeric.h>

#include <Graphics/Memory/ShaderProgramManager.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Pipeline/Pipeline.h>

#include <EvoVulkan/Tools/VulkanDebug.h>

namespace SR_GRAPH_NS::Memory {
    ShaderProgramManager::ShaderProgramManager()
        : SR_UTILS_NS::Singleton<ShaderProgramManager>()
    {
        m_virtualTable.max_load_factor(0.75f);
        m_virtualTable.reserve(1024);
    }

    void ShaderProgramManager::OnSingletonDestroy() {
        Singleton::OnSingletonDestroy();
    }

    ShaderProgramManager::VirtualProgram ShaderProgramManager::Allocate(const SRShaderCreateInfo &createInfo) {
        SR_LOCK_GUARD

        SR_TRACY_ZONE;

        VirtualProgram virtualProgram = GenerateUnique();

        if (virtualProgram == SR_ID_INVALID) {
            SR_ERROR("ShaderProgramManager::Allocate() : failed to generate virtual program!");
            return SR_ID_INVALID;
        }

        VirtualProgramInfo virtualProgramInfo;
        virtualProgramInfo.m_createInfo = SRShaderCreateInfo(createInfo);

        if (auto&& shaderProgramInfo = AllocateShaderProgram(createInfo); shaderProgramInfo.Valid()) {
            virtualProgramInfo.m_data[GetCurrentIdentifier()] = shaderProgramInfo;
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
            m_pipeline->DeleteShader(&shaderProgramInfo.id);
        }
        virtualProgramInfo.m_data.clear();

        /// обновляем данные
        virtualProgramInfo.m_createInfo = SRShaderCreateInfo(createInfo);

        if (auto&& shaderProgramInfo = AllocateShaderProgram(createInfo); shaderProgramInfo.Valid()) {
            virtualProgramInfo.m_data[GetCurrentIdentifier()] = shaderProgramInfo;
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

    ShaderBindResult ShaderProgramManager::BindProgram(VirtualProgram virtualProgram) noexcept {
        SR_LOCK_GUARD

        auto&& pIt = m_virtualTable.find(virtualProgram);
        if (pIt == std::end(m_virtualTable)) {
            SRHalt("ShaderProgramManager::BindProgram() : virtual program not found!");
            return ShaderBindResult::Failed;
        }

        ShaderBindResult result = ShaderBindResult::Success;

        auto&& [_, virtualProgramInfo] = *pIt;
        auto&& identifier = GetCurrentIdentifier();
    retry:
        auto&& fboIt = virtualProgramInfo.m_data.find(identifier);
        if (fboIt == std::end(virtualProgramInfo.m_data))
        {
            if (auto&& shaderProgramInfo = AllocateShaderProgram(virtualProgramInfo.m_createInfo); shaderProgramInfo.Valid()) {
                virtualProgramInfo.m_data[identifier] = shaderProgramInfo;
                result = ShaderBindResult::Duplicated;
                goto retry;
            }
            else {
                SR_ERROR("ShaderProgramManager::BindProgram() : failed to allocate shader program!");
                return ShaderBindResult::Failed;
            }
        }

        SRAssert2(result != ShaderBindResult::Failed, "unexcepted result!");

        auto&& bindResult = BindShaderProgram(fboIt->second, virtualProgramInfo.m_createInfo);

        if (bindResult == ShaderBindResult::Failed) {
            SR_ERROR("ShaderProgramManager::BindProgram() : failed to bind shader program!");
            return ShaderBindResult::Failed;
        }

        SRAssert2(bindResult != ShaderBindResult::Duplicated, "unexcepted duplication!");

        if (result == ShaderBindResult::Duplicated) {
            return result;
        }

        return bindResult;
    }

    bool ShaderProgramManager::FreeProgram(ShaderProgramManager::VirtualProgram program) {
        return FreeProgram(&program);
    }

    bool ShaderProgramManager::FreeProgram(VirtualProgram *program) {
        SR_TRACY_ZONE;

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
            m_pipeline->DeleteShader(&shaderProgramInfo.id);
        }

        m_virtualTable.erase(pIt);

        *program = SR_ID_INVALID;

        return true;
    }

    bool ShaderProgramManager::IsAvailable(ShaderProgramManager::VirtualProgram virtualProgram) const noexcept {
        SR_LOCK_GUARD

        auto&& pIt = m_virtualTable.find(virtualProgram);
        if (pIt == std::end(m_virtualTable)) {
            return false;
        }

        auto&& [_, info] = *pIt;
        auto&& identifier = GetCurrentIdentifier();
        auto&& fboIt = info.m_data.find(identifier);

        return fboIt != std::end(info.m_data);
    }

    ShaderProgramManager::ShaderProgram ShaderProgramManager::GetProgram(VirtualProgram virtualProgram) const noexcept {
        SR_LOCK_GUARD

        auto&& pIt = m_virtualTable.find(virtualProgram);
        if (pIt == std::end(m_virtualTable)) {
            SRHalt("ShaderProgramManager::GetProgram() : virtual program not found!");
            return SR_ID_INVALID;
        }

        auto&& [_, info] = *pIt;
        auto&& identifier = GetCurrentIdentifier();
        auto&& fboIt = info.m_data.find(identifier);

        if (fboIt == std::end(info.m_data))
        {
            SRHalt("ShaderProgramManager::GetProgram() : framebuffer not found!");
            return SR_ID_INVALID;
        }

        return fboIt->second.id;
    }

    VirtualProgramInfo::ShaderProgramInfo ShaderProgramManager::AllocateShaderProgram(const SRShaderCreateInfo &createInfo) const {
        SR_TRACY_ZONE;

        /// Выделяем новую шейдерную программу
        auto&& frameBufferId = m_pipeline->GetCurrentFrameBufferId();

        auto&& shaderProgram = m_pipeline->AllocateShaderProgram(createInfo, frameBufferId);
        if (shaderProgram == SR_ID_INVALID) {
            SR_ERROR("ShaderProgramManager::AllocateShaderProgram() : failed to allocate shader program!");
            return VirtualProgramInfo::ShaderProgramInfo(); /// NOLINT
        }

        VirtualProgramInfo::ShaderProgramInfo shaderProgramInfo;
        shaderProgramInfo.id = shaderProgram;

        if (auto&& pFrameBuffer = m_pipeline->GetCurrentFrameBuffer()) {
            shaderProgramInfo.samples = pFrameBuffer->GetSamplesCount();
            shaderProgramInfo.depth = pFrameBuffer->IsDepthEnabled();
        }
        else {
            shaderProgramInfo.samples = m_pipeline->GetSamplesCount();
            shaderProgramInfo.depth = createInfo.blendEnabled;
        }

        return shaderProgramInfo;
    }

    ShaderBindResult ShaderProgramManager::BindShaderProgram(VirtualProgramInfo::ShaderProgramInfo &shaderProgramInfo, const SRShaderCreateInfo& createInfo) { /// NOLINT
        if (auto&& pFrameBuffer = m_pipeline->GetCurrentFrameBuffer())
        {
            if (pFrameBuffer->IsDepthEnabled() != shaderProgramInfo.depth || pFrameBuffer->GetSamplesCount() != shaderProgramInfo.samples)
            {
                SR_LOG("ShaderProgramManager::BindShaderProgram() : the frame buffer parameters have been changed, the shader has been recreated...");

                m_pipeline->DeleteShader(&shaderProgramInfo.id);

                if ((shaderProgramInfo = AllocateShaderProgram(createInfo)).Valid()) {
                    if (BindShaderProgram(shaderProgramInfo, createInfo) == ShaderBindResult::Success) {
                        return ShaderBindResult::ReAllocated;
                    }
                    else {
                        SR_ERROR("ShaderProgramManager::BindShaderProgram() : unexcepted result!");
                        return ShaderBindResult::Failed;
                    }
                }
                else {
                    SR_ERROR("ShaderProgramManager::BindShaderProgram() : failed to allocate shader program!");
                    return ShaderBindResult::Failed;
                }
            }

            m_pipeline->UseShader(static_cast<ShaderProgram>(shaderProgramInfo.id));
        }
        else {
            m_pipeline->UseShader(static_cast<ShaderProgram>(shaderProgramInfo.id));
        }

        return ShaderBindResult::Success;
    }

    VirtualProgramInfo::Identifier ShaderProgramManager::GetCurrentIdentifier() const {
        return reinterpret_cast<VirtualProgramInfo::Identifier>(m_pipeline->GetCurrentFBOHandle());
    }

    const VirtualProgramInfo* ShaderProgramManager::GetInfo(ShaderProgramManager::VirtualProgram virtualProgram) const noexcept {
        SR_LOCK_GUARD

        auto&& pIt = m_virtualTable.find(virtualProgram);
        if (pIt == std::end(m_virtualTable)) {
            SRHalt("ShaderProgramManager::GetInfo() : virtual program not found!");
            return nullptr;
        }

        return &pIt->second;
    }

    bool ShaderProgramManager::HasProgram(ShaderProgramManager::VirtualProgram virtualProgram) const noexcept {
        SR_LOCK_GUARD
        return m_virtualTable.find(virtualProgram) != std::end(m_virtualTable);
    }

    void ShaderProgramManager::CollectUnusedShaders() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD

        if (m_virtualTable.empty()) {
            return;
        }

        auto&& handles = m_pipeline->GetFBOHandles();

        uint32_t count = 0;

        /// не удаляем сами виртуальные программы, они могут еще пригодиться
        for (auto&& [virtualProgram, info] : m_virtualTable) {
            for (auto pProgramIt = info.m_data.begin(); pProgramIt != info.m_data.end(); ) {
                auto&& [identifier, program] = *pProgramIt;

                if (handles.count(reinterpret_cast<void*>(identifier)) == 0) {
                    m_pipeline->DeleteShader(&program.id);
                    pProgramIt = info.m_data.erase(pProgramIt);
                    ++count;
                }
                else {
                    ++pProgramIt;
                }
            }
        }

        if (count > 0) {
            SR_LOG(SR_FORMAT("ShaderProgramManager::CollectUnusedShaders() : collected %i unused shaders.", count));
        }
    }
}

