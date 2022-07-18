//
// Created by Nikita on 17.11.2020.
//

#include <Types/Shader.h>

#include <Types/Texture.h>
#include <Render/Render.h>
#include <Environment/Environment.h>

#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Xml.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/Common/Hashes.h>

namespace SR_GRAPH_NS::Types {
    Shader::Shader()
        : IResource(typeid(Shader).name())
    { }

    Shader::~Shader() {
        m_uniformBlock.DeInit();
        m_uniformBlock = Memory::ShaderUBOBlock();

        m_samplers.clear();
    }

    bool Shader::Init() {
        if (m_isInit) {
            SRHalt("Double shader initialization!");
            return true;
        }

        if (!SRVerifyFalse2(!(m_render = SR_THIS_THREAD->GetContext()->GetPointer<Render>()), "Is not render context!")) {
            m_hasErrors = true;
            return false;
        }

        m_shaderProgram = Memory::ShaderProgramManager::Instance().ReAllocate(m_shaderProgram, m_shaderCreateInfo);
        if (m_shaderProgram == SR_ID_INVALID) {
            SR_ERROR("Shader::Init() : failed to allocate shader program!");
            m_hasErrors = true;
            return false;
        }

        /// calculate shader params hash
        {
            auto&& hash = SR_UTILS_NS::HashCombine(m_properties, 0);
            hash = SR_UTILS_NS::HashCombine(m_samplers, hash);
            SetResourceHash(hash);
        }

        m_isInit = true;

        return true;
    }

    bool Shader::Use() noexcept {
        if (m_hasErrors) {
            return false;
        }

        if (!m_isInit && !Init()) {
            SR_ERROR("Shader::Use() : failed to initialize shader!");
            return false;
        }

        switch (Memory::ShaderProgramManager::Instance().BindProgram(m_shaderProgram)) {
            case Memory::ShaderProgramManager::BindResult::Success:
            case Memory::ShaderProgramManager::BindResult::Duplicated:
                return true;
            case Memory::ShaderProgramManager::BindResult::Failed:
            default:
                return false;
        }
    }

    void Shader::UnUse() noexcept {
        auto&& env = SR_GRAPH_NS::Environment::Get();
        env->UnUseShader();
    }

    void Shader::FreeVideoMemory() {
        if (m_isInit) {
            SR_SHADER("Shader::Free() : free \"" + m_shaderCreateInfo.path.ToString() + "\" shader class pointer and free video memory...");

            if (!Memory::ShaderProgramManager::Instance().FreeProgram(&m_shaderProgram)) {
                SR_ERROR("Shader::Free() : failed to free shader program! \n\tPath: " + m_shaderCreateInfo.path.ToString());
            }
        }
        else {
            SR_SHADER("Shader::Free() : free \"" + m_shaderCreateInfo.path.ToString() + "\" shader class pointer...");
        }
    }

    Shader* Shader::Load(const SR_UTILS_NS::Path &rawPath) {
        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        SR_UTILS_NS::Path&& path = SR_UTILS_NS::Path(rawPath).RemoveSubPath(resourceManager.GetShadersPath());

        if (auto&& pShader = resourceManager.Find<Shader>(path)) {
            return pShader;
        }

        SR_LOG("Shader::Load() : load \"" + path.ToString() + "\" shader...");

        if (!SRVerifyFalse2(path.Empty(), "Invalid shader path!")) {
            SR_WARN("Shader::Load() : failed to load shader!");
            return nullptr;
        }

        if (path.GetExtensionView() != "srsl") {
            SR_ERROR("Shader::Load() : unknown extension!");
            return nullptr;
        }

        auto&& pShader = new Shader();

        pShader->SetId(path.ToString(), false);

        if (!pShader->Reload()) {
            SR_ERROR("Shader::Load() : failed to reload shader!\n\tPath: " + path.ToString());
            delete pShader;
            return nullptr;
        }

        resourceManager.RegisterResource(pShader);

        return pShader;
    }

    int32_t Shader::GetID() {
        if (m_hasErrors) {
            return false;
        }

        if (!m_isInit && !Init()) {
            SR_ERROR("Shader::Use() : failed to initialize shader!");
            return false;
        }

        return Memory::ShaderProgramManager::Instance().GetProgram(m_shaderProgram);
    }

    void Shader::SetBool(uint64_t hashId, const bool &v) noexcept { SetValue(hashId, v); }
    void Shader::SetFloat(uint64_t hashId, const float &v) noexcept { SetValue(hashId, v); }
    void Shader::SetInt(uint64_t hashId, const int &v) noexcept { SetValue(hashId, v); }
    void Shader::SetMat4(uint64_t hashId, const glm::mat4 &v) noexcept { SetValue(hashId, v); }
    void Shader::SetVec3(uint64_t hashId, const glm::vec3 &v) noexcept { SetValue(hashId, v); }
    void Shader::SetVec4(uint64_t hashId, const glm::vec4 &v) noexcept { SetValue(hashId, v); }
    void Shader::SetVec2(uint64_t hashId, const glm::vec2 &v) noexcept { SetValue(hashId, v); }
    void Shader::SetIVec2(uint64_t hashId, const glm::ivec2 &v) noexcept { SetValue(hashId, v); }

    void Shader::SetSampler(uint64_t hashId, int32_t sampler) noexcept {
        auto&& env = SR_GRAPH_NS::Environment::Get();
        env->BindTexture(m_samplers.at(hashId).second, sampler);
    }

    void Shader::SetSampler2D(uint64_t hashId, int32_t sampler) noexcept {
        if (!IsLoaded() || m_samplers.count(hashId) == 0) {
            return;
        }

        SetSampler(hashId, sampler);
    }

    void Shader::SetSamplerCube(uint64_t hashId, int32_t sampler) noexcept {
        if (!IsLoaded() || m_samplers.count(hashId) == 0) {
            return;
        }

        SetSampler(hashId, sampler);
    }

    void Shader::SetSampler2D(uint64_t hashId, Types::Texture *sampler) noexcept {
        if (!IsLoaded() || m_samplers.count(hashId) == 0) {
            return;
        }

        if (!sampler) {
            sampler = SR_GTYPES_NS::Texture::GetNone();
        }

        if (!sampler->HasRender()) {
            SRAssert(m_render);
            m_render->RegisterTexture(sampler);
        }

        SetSampler(hashId, sampler->GetId());
    }

    void Shader::SetSampler2D(const std::string &name, Types::Texture *sampler) noexcept {
        SetSampler2D(SR_RUNTIME_TIME_CRC32_STR(name.c_str()), sampler);
    }

    bool Shader::Ready() const {
        return !m_hasErrors && m_isInit;
    }

    uint64_t Shader::GetUBOBlockSize() const {
        return m_uniformBlock.m_size;
    }

    bool Shader::InitUBOBlock() {
        auto&& env = SR_GRAPH_NS::Environment::Get();

        if (m_uniformBlock.m_size > 0 && m_uniformBlock.m_memory) {
            memset(m_uniformBlock.m_memory, 1, m_uniformBlock.m_size);
        }

        auto&& ubo = env->GetCurrentUBO();
        auto&& descriptorSet = env->GetCurrentDescriptorSet();

        if (ubo != SR_ID_INVALID && descriptorSet != SR_ID_INVALID && m_uniformBlock.Valid()) {
            env->UpdateDescriptorSets(descriptorSet, {
                    { DescriptorType::Uniform, { m_uniformBlock.m_binding, ubo } },
            });

            return true;
        }

        return false;
    }

    bool Shader::Flush() const {
        if (!m_isInit || m_hasErrors) {
            return false;
        }

        auto&& env = SR_GRAPH_NS::Environment::Get();

        auto &&ubo = env->GetCurrentUBO();
        if (ubo != SR_ID_INVALID && m_uniformBlock.Valid()) {
            env->UpdateUBO(ubo, m_uniformBlock.m_memory, m_uniformBlock.m_size);
        }

        return true;
    }

    uint32_t Shader::GetSamplersCount() const {
        return m_samplers.size();
    }

    ShaderProperties Shader::GetProperties() {
        return m_properties;
    }

    SR_UTILS_NS::Path Shader::GetAssociatedPath() const {
        return SR_UTILS_NS::ResourceManager::Instance().GetShadersPath();
    }

    bool Shader::Reload() {
        SR_SHADER_LOG("Shader::Reload() : reloading \"" + GetResourceId() + "\" shader...");

        m_loadState = LoadState::Reloading;

        Unload();

        if (!Load()) {
            return false;
        }

        m_loadState = LoadState::Loaded;

        UpdateResources();

        auto&& env = SR_GRAPH_NS::Environment::Get();
        env->SetBuildState(false);

        return true;
    }

    bool Shader::Load() {
        SR_LOCK_GUARD

        bool hasErrors = !IResource::Load();

        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        SR_UTILS_NS::Path&& path = SR_UTILS_NS::Path(GetResourceId());

        if (path.IsAbs()) {
            SR_ERROR("Shader::Load() : absolute path is not allowed!");
            return false;
        }

        auto &&unit = SRSL::SRSLLoader::Instance().Load(path);

        if (!unit) {
            SR_ERROR("Shader::Load() : failed to load SRSL shader! \n\tPath: " + path.ToString());
            return false;
        }

        m_shaderCreateInfo = std::move(unit->createInfo);
        m_shaderCreateInfo.path = unit->path + "/shader";

        switch (unit->type) {
            case SRSL::ShaderType::Custom:
            case SRSL::ShaderType::PostProcessing:
                break;
            case SRSL::ShaderType::Spatial: {
                UBOInfo uniforms = {};
                for (const auto& [binding, size] : unit->GetUniformSizes()) {
                    uniforms.emplace_back(std::pair(binding, size));
                }

                m_shaderCreateInfo.uniforms = std::move(uniforms);

                SR_FALLTHROUGH;
            }
            case SRSL::ShaderType::SpatialCustom: {
                auto&&[description, attrib] = Vertices::GetVertexInfo(Vertices::Type::StaticMeshVertex);
                m_shaderCreateInfo.vertexDescriptions = std::move(description);
                m_shaderCreateInfo.vertexAttributes = std::move(attrib);
                break;
            }
            case SRSL::ShaderType::Simple:
            case SRSL::ShaderType::Skybox: {
                UBOInfo uniforms = { };
                for (const auto& [binding, size] : unit->GetUniformSizes()) {
                    uniforms.emplace_back(std::pair(binding, size));
                }
                m_shaderCreateInfo.uniforms = std::move(uniforms);

                auto&&[description, attrib] = Vertices::GetVertexInfo(Vertices::Type::SimpleVertex);
                m_shaderCreateInfo.vertexDescriptions = std::move(description);
                m_shaderCreateInfo.vertexAttributes = std::move(attrib);

                break;
            }
            case SRSL::ShaderType::TransparentSpatial:
            case SRSL::ShaderType::Animation:
            case SRSL::ShaderType::Canvas:
            case SRSL::ShaderType::Particles:
            case SRSL::ShaderType::Unknown:
            default:
                SRAssert(false);
                break;
        }

        for (auto&&[name, sampler] : unit->GetSamplers()) {
            m_samplers[SR_RUNTIME_TIME_CRC32_STR(name.c_str())] = std::make_pair(
                sampler.type,
                sampler.binding
            );

            if (sampler.show) {
                m_properties.emplace_back(std::make_pair(name, sampler.type));
            }
        }

        for (auto&&[name, var] : unit->GetUniformBlock()) {
            m_uniformBlock.Append(SR_RUNTIME_TIME_CRC32_STR(name.c_str()), var.type, !var.show);
            m_uniformBlock.m_binding = var.binding;

            if (var.show && !IsMatrixType(var.type)) {
                m_properties.emplace_back(std::make_pair(name, var.type));
            }
        }

        m_uniformBlock.Init();

        return !hasErrors;
    }

    bool Shader::Unload() {
        SR_LOCK_GUARD

        bool hasErrors = !IResource::Unload();

        m_isInit = false;
        m_hasErrors = false;

        m_uniformBlock.DeInit();

        m_properties.clear();
        m_samplers.clear();

        return !hasErrors;
    }
}