//
// Created by Monika on 11.07.2022.
//

#include <Memory/ShaderProgramManager.h>

namespace SR_GRAPH_NS::Memory {
    ShaderProgramManager::ShaderProgramManager() {
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

        auto&& env = Environment::Get();
        auto&& framebufferId = static_cast<int32_t>(env->GetCurrentFBO());

        ShaderProgram shaderProgram = env->AllocateShaderProgram(createInfo, framebufferId);
        if (shaderProgram == SR_ID_INVALID) {
            SR_ERROR("ShaderProgramManager::Allocate() : failed to allocate shader program!");
            return SR_ID_INVALID;
        }

        VirtualProgramInfo virtualProgramInfo;

        virtualProgramInfo.m_createInfo = createInfo;

        virtualProgramInfo.m_data.insert(std::make_pair(
                framebufferId,
                shaderProgram
        ));

        m_virtualTable.insert(std::make_pair(
                virtualProgram,
                std::move(virtualProgramInfo)
        ));

        return virtualProgram;
    }

    ShaderProgramManager::VirtualProgram ShaderProgramManager::ReAllocate(VirtualProgram program, const SRShaderCreateInfo& createInfo) {
        SR_LOCK_GUARD

        SR_GRAPH_LOG("ShaderProgramManager::ReAllocate() : re-allocate shader program...");

        if (program == SR_ID_INVALID) {
            return Allocate(createInfo);
        }

        auto&& pIt = m_virtualTable.find(program);
        if (pIt == m_virtualTable.end()) {
            SRHalt("ShaderProgramManager::ReAllocate() : virtual program not found!");
            return SR_ID_INVALID;
        }

        auto&& [_, virtualProgramInfo] = *pIt;
        auto&& env = Environment::Get();

        /// очишаем старые шейдерные программы
        for (auto&& [fbo /** unused */, shaderProgram] : virtualProgramInfo.m_data) {
            env->DeleteShader(shaderProgram);
        }
        virtualProgramInfo.m_data.clear();

        /// выделяем новую шейдерную программу
        auto&& framebufferId = static_cast<int32_t>(env->GetCurrentFBO());
        auto&& shaderProgram = env->AllocateShaderProgram(virtualProgramInfo.m_createInfo, framebufferId);
        if (shaderProgram == SR_ID_INVALID) {
            SR_ERROR("ShaderProgramManager::ReAllocate() : failed to allocate shader program!");
            return SR_ID_INVALID;
        }

        virtualProgramInfo.m_data.insert(std::make_pair(
                framebufferId,
                shaderProgram
        ));

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

        auto&& env = Environment::Get();
        auto&& [_, info] = *pIt;
        auto&& framebufferId = static_cast<int32_t>(env->GetCurrentFBO());
    retry:
        auto&& fboIt = info.m_data.find(framebufferId);
        if (fboIt == std::end(info.m_data))
        {
            auto&& shaderProgram = env->AllocateShaderProgram(info.m_createInfo, framebufferId);
            if (shaderProgram == SR_ID_INVALID) {
                SR_ERROR("ShaderProgramManager::BindProgram() : failed to allocate shader program!");
                return BindResult::Failed;
            }

            info.m_data.insert(std::make_pair(
                    framebufferId,
                    shaderProgram
            ));

            result = BindResult::Duplicated;

            goto retry;
        }

        env->UseShader(static_cast<ShaderProgram>(fboIt->second));

        return result;
    }
}

