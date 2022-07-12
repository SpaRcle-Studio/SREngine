//
// Created by Nikita on 17.11.2020.
//

#include <Render/Shader.h>

#include <Types/Texture.h>
#include <Render/Render.h>
#include <Environment/Environment.h>

#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Xml.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/Common/Hashes.h>

namespace SR_GRAPH_NS {
    Shader::Shader()
        : IResource(typeid(Shader).name())
    { }

    Shader::~Shader() {
        m_uniformBlock.DeInit();
        m_uniformBlock = Memory::ShaderUBOBlock();

        m_samplers.clear();
    }

    bool Shader::Init() {
        if (m_isInit)
            return true;

        if (!SRVerifyFalse2(!(m_render = SR_THIS_THREAD->GetContext()->GetPointer<Render>()), "Is not render context!")) {
            m_hasErrors = true;
            return false;
        }

        if (!Compile()) {
            SR_ERROR("Shader::Init() : failed compiling shader!");
            return false;
        }

        if (!Link()) {
            SR_ERROR("Shader::Init() : failed linking shader!");
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

    bool Shader::Compile() {
        if (m_isCompile) {
            SR_ERROR("Shader::Compile() : shader already compile!");
            return false;
        }

        SR_SHADER_LOG("Shader::Compile() : compiling \"" + m_shaderCreateInfo.path.ToString() + "\" shader...");

        auto&& env = Environment::Get();

        m_fbo = env->GetCurrentFBO();

        if (env->GetPipeLine() == PipeLine::OpenGL) {
            if (!env->CompileShader(m_shaderCreateInfo.path, m_fbo, &m_shaderTempData)) {
                SR_ERROR("Shader::Compile() : failed to compile opengl \"" + m_shaderCreateInfo.path.ToString() + "\" shader!");
                return false;
            }
        }
        else {
            auto&& sizes = std::vector<uint64_t>();
            sizes.reserve(m_shaderCreateInfo.uniforms.size());
            for (auto&& [binding, size] : m_shaderCreateInfo.uniforms)
                sizes.push_back(size);

            if (!env->CompileShader(m_shaderCreateInfo.path, m_fbo, &m_shaderTempData, sizes)) {
                SR_ERROR("Shader::Compile() : failed to compile \"" + m_shaderCreateInfo.path.ToString() + "\" shader!");
                return false;
            }
        }

        m_isCompile = true;

        return true;
    }

    bool Shader::Link() {
        if (m_isLink) {
            SR_ERROR("Shader::Link() : shader already linking!");
            return false;
        }

        if (!m_isCompile) {
            SR_ERROR("Shader::Link() : shader is not compile!");
            return false;
        }

        auto&& env = Environment::Get();

        SR_SHADER_LOG("Shader::Link() : linking \"" + m_shaderCreateInfo.path.ToString() + "\" shader...");

        if (m_shaderProgram != SR_NULL_SHADER && !env->DeleteShader(m_shaderProgram)) {
            SR_ERROR("Shader::Free() : failed to free video memory! Name: " + m_shaderCreateInfo.path.ToString());
        }

        if (!env->LinkShader(&m_shaderProgram, &m_shaderTempData, m_shaderCreateInfo.vertexDescriptions, m_shaderCreateInfo.vertexAttributes,
                               m_shaderCreateInfo)) {
            SR_ERROR("Shader::Link() : failed linking \"" + m_shaderCreateInfo.path.ToString() + "\" shader!");
            return false;
        }

        m_isLink = true;

        return true;
    }

    bool Shader::Use() noexcept {
        if (!m_isInit) {
            if (m_hasErrors)
                return false;

            if (!Init()) {
                SR_ERROR("Shader::Use() : failed to initialize shader!");
                m_hasErrors = true;
                return false;
            }
            m_isInit = true;
        }

        auto&& env = Environment::Get();

        if (m_fbo != env->GetCurrentFBO()) {
            if (m_fbo == SR_ID_INVALID) {
                SR_INFO("Shader::Use() : re-create \"" + m_shaderCreateInfo.path.ToString() + "\" shader...");
                if (!env->ReCreateShader(m_shaderProgram)) {
                    SR_ERROR("Shader::Use() : failed to re-create shader!");
                    m_hasErrors = true;
                    return false;
                }
                else
                    m_fbo = env->GetCurrentFBO();
            }
            else {
                SRHalt("Shader::Use() : frame buffer was been changed!");
            }
        }

        env->UseShader(m_shaderProgram);

        return true;
    }

    void Shader::UnUse() noexcept {
        auto&& env = Environment::Get();
        env->UnUseShader();
    }

    void Shader::FreeVideoMemory() {
        if (m_isInit) {
            SR_SHADER("Shader::Free() : free \"" + m_shaderCreateInfo.path.ToString() + "\" shader class pointer and free video memory...");

            auto&& env = Environment::Get();

            if (!env->DeleteShader(m_shaderProgram)) {
                SR_ERROR("Shader::Free() : failed to free video memory! Name: " + m_shaderCreateInfo.path.ToString());
            }

            m_shaderProgram = SR_NULL_SHADER;
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
        if (!m_isInit) {
            if (m_hasErrors)
                return false;

            if (!Init()) {
                SR_ERROR("Shader::GetID() : failed to initialize shader!");
                m_hasErrors = true;
                return SR_ID_INVALID;
            }
            m_isInit = true;
        }

        return m_shaderProgram;
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
        auto&& env = Environment::Get();
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
        auto&& env = Environment::Get();

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

        auto&& env = Environment::Get();

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
        SR_SHADER_LOG("Shader::Reload() : reloading \"" + m_shaderCreateInfo.path.ToString() + "\" shader...");

        m_loadState = LoadState::Reloading;

        Unload();

        if (!Load()) {
            return false;
        }

        m_loadState = LoadState::Loaded;

        UpdateResources();

        Environment::Get()->SetBuildState(false);

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

        m_isCompile = false;
        m_isLink = false;

        m_uniformBlock.DeInit();

        m_properties.clear();
        m_samplers.clear();

        return !hasErrors;
    }
}