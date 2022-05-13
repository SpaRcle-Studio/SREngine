//
// Created by Nikita on 17.11.2020.
//

#include <Render/Shader.h>
#include <Debug.h>
#include <Xml.h>
#include <Render/Render.h>
#include <Environment/Environment.h>
#include <ResourceManager/ResourceManager.h>
#include <Types/Texture.h>
#include <Types/Thread.h>
#include <Types/DataStorage.h>
#include <Utils/Hashes.h>

namespace SR_GRAPH_NS {
    Shader::Shader(std::string path, std::string name)
            : IResource(typeid(Shader).name())
            , m_env(Environment::Get())
            , m_path(std::move(path))
            , m_name(std::move(name))
    {
        SR_UTILS_NS::IResource::SetId(m_name);
    }

    Shader::~Shader() {
        m_uniformBlock.DeInit();
        m_uniformBlock = ShaderUBOBlock();

        m_sharedUniforms.clear();
        m_samplers.clear();
    }

    Shader::Shader(std::string path)
        : Shader(std::move(path), "Unnamed")
    { }

    bool Shader::Init() {
        if (m_isInit)
            return true;

        if (SRVerifyFalse2((m_render = SR_THIS_THREAD->GetContext()->GetPointer<Render>()), "Is not render context!")) {
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

        if (m_env->GetPipeLine() == PipeLine::Vulkan) {
            std::vector<uint64_t> sizes = {};
            for (const auto &uniform : m_uniformsInfo)
                if (uniform.first.second == UBOType::Shared)
                    sizes.push_back(uniform.second);

            if (!sizes.empty()) {
                m_sharedUniforms.resize(sizes.size());
                for (uint32_t i = 0; i < sizes.size(); ++i) {
                    if ((m_sharedUniforms[i] = m_env->AllocateUBO(sizes[i])) < 0) {
                        SR_ERROR("Shader::Init() : failed to allocate uniform buffer object!");
                        return false;
                    }
                }
            }
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

        SR_SHADER_LOG("Shader::Compile() : compiling \"" + m_path + "\" shader...");

        m_fbo = m_env->GetCurrentFBO();

        if (m_env->GetPipeLine() == PipeLine::OpenGL) {
            if (!m_env->CompileShader(m_path, m_fbo, &m_shaderTempData)) {
                SR_ERROR("Shader::Compile() : failed to compile opengl \"" + m_path + "\" shader!");
                return false;
            }
        }
        else {
            auto sizes = std::vector<uint64_t>();
            for (auto info : m_uniformsInfo)
                sizes.push_back(info.second);

            if (!m_env->CompileShader(m_path, m_fbo, &m_shaderTempData, sizes)) {
                SR_ERROR("Shader::Compile() : failed to compile \"" + m_path + "\" shader!");
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

        SR_SHADER_LOG("Shader::Link() : linking \"" + m_path + "\" shader...");

        if (m_shaderProgram != SR_NULL_SHADER && !m_env->DeleteShader(m_shaderProgram)) {
            SR_ERROR("Shader::Free() : failed to free video memory! Name: " + m_path);
        }

        if (!m_env->LinkShader(&m_shaderProgram, &m_shaderTempData, m_verticesDescription, m_verticesAttributes,
                               m_shaderCreateInfo)) {
            SR_ERROR("Shader::Link() : failed linking \"" + m_path + "\" shader!");
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

        if (m_fbo != m_env->GetCurrentFBO()) {
            SR_INFO("Shader::Use() : re-create \"" + m_path + "\" shader...");
            if (!m_env->ReCreateShader(m_shaderProgram)) {
                SR_ERROR("Shader::Use() : failed to re-create shader!");
                m_hasErrors = true;
                return false;
            }
            else
                m_fbo = m_env->GetCurrentFBO();
        }

        g_currentShader = this;
        m_env->UseShader(m_shaderProgram);

        return true;
    }

    void Shader::UnUse() noexcept {
        m_env->UnUseShader();
    }

    void Shader::FreeVideoMemory() {
        if (m_isInit) {
            SR_SHADER("Shader::Free() : free \"" + m_path + "\" shader class pointer and free video memory...");

            if (!m_env->DeleteShader(m_shaderProgram)) {
                SR_ERROR("Shader::Free() : failed to free video memory! Name: " + m_path);
            }
            m_shaderProgram = SR_NULL_SHADER;

            if (!m_sharedUniforms.empty()) {
                for (uint32_t i = 0; i < m_sharedUniforms.size(); ++i) {
                    if (!m_env->FreeUBO(&m_sharedUniforms[i]))
                        SR_ERROR("Shader::Free() : failed to free uniform buffer object!");
                }

                m_sharedUniforms.clear();
            }
        }
        else {
            SR_SHADER("Shader::Free() : free \"" + m_path + "\" shader class pointer...");
        }
    }

    bool Shader::SetVertex(const VertexDescriptions& descriptions, const VertexAttributes& attributes) {
        if (m_isInit && m_isCompile && m_isLink) {
            SR_ERROR("Shader::SetVertexDescriptions() : shader already initialized!");
            return false;
        }
        else {
            m_verticesDescription = descriptions;
            m_verticesAttributes = attributes;
        }

        return true;
    }

    bool Framework::Graphics::Shader::SetCreateInfo(SRShaderCreateInfo shaderCreateInfo) {
        if (m_isInit && m_isCompile && m_isLink) {
            SR_ERROR("Shader::SetCreateInfo() : shader already initialized!");
            return false;
        }
        else
            m_shaderCreateInfo = shaderCreateInfo;

        return m_shaderCreateInfo.Validate();
    }

    bool Shader::SetUniforms(const UBOInfo &uniforms) {
        if (m_isInit && m_isCompile && m_isLink) {
            SR_ERROR("Shader::SetUniforms() : shader already initialized!");
            return false;
        }
        else
            m_uniformsInfo = uniforms;

        return true;
    }

    void ShaderUBOBlock::Append(uint64_t hashId, ShaderVarType type, bool hidden) {
        auto &&size = GetShaderVarSize(type);

        m_data.insert(std::make_pair(hashId, SubBlock{
                .type = type,
                .size = size,
                .offset = m_size,
                .hidden = hidden,
        }));

        m_size += size;
    }

    void ShaderUBOBlock::Init() {
        if (m_memory) {
            delete m_memory;
            m_memory = nullptr;
        }

        m_memory = new char[m_size];
    }

    void ShaderUBOBlock::DeInit() {
        m_data.clear();
        m_size = 0;
        m_binding = SR_ID_INVALID;

        if (m_memory) {
            delete m_memory;
            m_memory = nullptr;
        }
    }

    void ShaderUBOBlock::SetField(uint64_t hashId, const void *data) noexcept {
        if (auto &&pIt = m_data.find(hashId); pIt != m_data.end() && m_memory) {
            memcpy(m_memory + pIt->second.offset, data, pIt->second.size);
        }
    }

    ShaderUBOBlock::ShaderUBOBlock() {
        m_data.set_empty_key(static_cast<uint64_t>(0));
    }

    Shader* Shader::Load(const SR_UTILS_NS::Path &path) {
        if (auto &&pShader = ResourceManager::Instance().Find<Shader>(path.ToString())) {
            return pShader;
        }

        SR_LOG("Shader::Load() : load \"" + path.ToString() + "\" shader...");

        if (path.GetExtensionView() == "srsl") {
            auto &&shader = new Shader(std::string(), path.ToString());
            shader->Reload();
            return shader;
        }
        else
            return LoadFromConfig(path.ToString());
    }

    Shader* Shader::LoadFromConfig(const std::string &name) {
        std::vector<Xml::Node> shaders = {};

        auto findShader = [&shaders](const std::string &name) -> Xml::Node {
            for (const auto &shaderXml : shaders)
                if (shaderXml.GetAttribute("name").ToString() == name)
                    return shaderXml;
            return Xml::Node::Empty();
        };

        typedef std::function<Xml::Node(const Xml::Node &node, const std::string &attribName)> getInheritNodeFun;
        getInheritNodeFun getInheritNode = [findShader, name, &getInheritNode](const Xml::Node &node, const std::string &nodeName) -> Xml::Node {
            if (auto targetNode = node.GetNode(nodeName)) {
                if (auto inherit = targetNode.GetAttribute("inherit")) {
                    if (auto inheritShader = findShader(inherit.ToString()))
                        return getInheritNode(inheritShader, nodeName);
                    else
                        SR_ERROR("Shader::Load() [getInheritAttrib] : \"" + inherit.ToString() +
                                             "\" inherit shader not found! \n\tShader name: " + name);
                } else
                    return targetNode;
            }
            return Xml::Node::Empty();
        };

        auto &&vertexParser = [=](Shader *shader, const Xml::Node &node) {
            if (auto vertex = getInheritNode(node, "Vertex")) {
                auto[descr, attrib] = Vertices::GetVertexInfo(
                        Vertices::StringToEnumType(vertex.GetAttribute("value").ToString()));
                shader->SetVertex(descr, attrib);
            }
        };

        auto &&uniformParsers = [=](Shader *shader, const Xml::Node &node) {
            if (auto xmlUniforms = getInheritNode(node, "Uniforms")) {
                std::vector<std::pair<std::pair<uint32_t, UBOType>, uint64_t>> uniforms = {};
                // 0 - binding
                // 1 - type
                // 2 - ubo size
                for (const auto &uniform : xmlUniforms.GetNodes()) {
                    uniforms.emplace_back(std::pair(
                            std::pair(
                                    (uint32_t) uniform.GetAttribute("binding").ToInt(),
                                    StringToEnumUBOType(uniform.GetAttribute("type").ToString())),
                            (uint64_t) GetUniformSize(uniform.GetAttribute("UBO").ToString())));
                }
                shader->SetUniforms(uniforms);
            }
        };

        auto &&infoParser = [=](Shader *shader, const Xml::Node &node) {
            auto createInfo = SRShaderCreateInfo();
            if (auto info = getInheritNode(node, "Info")) {
                if (auto value = info.GetNode("PolygonMode"))
                    createInfo.polygonMode = StringToEnumPolygonMode(value.GetAttribute("value").ToString());

                if (auto value = info.GetNode("CullMode"))
                    createInfo.cullMode = StringToEnumCullMode(value.GetAttribute("value").ToString());

                if (auto value = info.GetNode("DepthCompare"))
                    createInfo.depthCompare = StringToEnumDepthCompare(value.GetAttribute("value").ToString());

                if (auto value = info.GetNode("PrimitiveTopology"))
                    createInfo.primitiveTopology = StringToEnumPrimitiveTopology(
                            value.GetAttribute("value").ToString());

                if (auto value = info.GetNode("BlendEnabled"))
                    createInfo.blendEnabled = value.GetAttribute("value").ToBool();

                if (auto value = info.GetNode("DepthWrite"))
                    createInfo.depthWrite = value.GetAttribute("value").ToBool();

                if (auto value = info.GetNode("DepthTest"))
                    createInfo.depthTest = value.GetAttribute("value").ToBool();
            }
            SRAssert2(shader->SetCreateInfo(createInfo), "Failed to validate shader create info!");
        };

        auto &&shaderParser = [=](const Xml::Node &node) -> Shader * {
            if (auto path = node.GetAttribute("path"); path.Valid()) {
                auto shader = new Shader(path.ToString(), name);
                {
                    vertexParser(shader, node);
                    uniformParsers(shader, node);
                    infoParser(shader, node);
                }
                return shader;
            }
            else
                return nullptr;
        };

        auto &&createInfoPath = Helper::StringUtils::MakePath(
                Helper::ResourceManager::Instance().GetResPath().Concat("/Shaders/CreateInfo.xml"));

        if (FileSystem::FileExists(createInfoPath)) {
            auto xml = Helper::Xml::Document::Load(createInfoPath);
            shaders = xml.Root().GetNode("Shaders").GetNodes();
            if (auto shaderXml = findShader(name)) {
                auto shader = shaderParser(shaderXml);
                if (!shader) {
                    SR_ERROR("Shader::LoadFromConfig() : failed to load \"" + name + "\" shader!");
                }
                return shader;
            } else
                SR_ERROR("Shader::LoadFromConfig() : shader \"" + name + "\" have not config!");
        } else
            SR_ERROR("Shader::LoadFromConfig() : create info file not found! \n\tPath: " + createInfoPath);

        return nullptr;
    }

    int32_t Shader::GetUBO(const uint32_t &index) const {
        if (index >= m_sharedUniforms.size()) {
            SR_ERROR("Shader::GetUBO() : index out of range! \n\tCount uniforms: " +
                     std::to_string(m_sharedUniforms.size()) + "\n\tIndex: " + std::to_string(index));
            return -1;
        }
        return m_sharedUniforms[index];
    }

    int32_t Shader::GetID() {
        if (!m_isInit) {
            if (m_hasErrors)
                return false;

            if (!Init()) {
                SR_ERROR("Shader::GetID() : failed to initialize shader!");
                m_hasErrors = true;
                return -1;
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

    void Shader::SetSampler2D(const std::string &name, Types::Texture *sampler) noexcept {
        if (!IsLoaded() || m_samplers.count(name) == 0) {
            return;
        }

        sampler = sampler ? sampler : SR_GTYPES_NS::Texture::GetNone();

        if (!sampler->HasRender()) {
            SRAssert(m_render);
            m_render->RegisterTexture(sampler);
        }

        m_env->BindTexture(m_samplers.at(name).second, sampler->GetID());
    }

    bool Shader::Ready() const {
        return !m_hasErrors && m_isInit;
    }

    uint64_t Shader::GetUBOBlockSize() const {
        return m_uniformBlock.m_size;
    }

    bool Shader::InitUBOBlock() {
        if (m_uniformBlock.m_size > 0 && m_uniformBlock.m_memory) {
            memset(m_uniformBlock.m_memory, 1, m_uniformBlock.m_size);
        }

        auto&& ubo = m_env->GetCurrentUBO();
        auto&& descriptorSet = m_env->GetCurrentDescriptorSet();

        if (ubo != SR_ID_INVALID && descriptorSet != SR_ID_INVALID && m_uniformBlock.Valid()) {
            m_env->UpdateDescriptorSets(descriptorSet, {
                    {DescriptorType::Uniform, {m_uniformBlock.m_binding, ubo}},
            });
        }

        return true;
    }

    bool Shader::Flush() const {
        if (!m_isInit || m_hasErrors) {
            return false;
        }

        auto &&ubo = m_env->GetCurrentUBO();
        if (ubo != SR_ID_INVALID && m_uniformBlock.Valid()) {
            m_env->UpdateUBO(ubo, m_uniformBlock.m_memory, m_uniformBlock.m_size);
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
        SR_SHADER_LOG("Shader::Reload() : reloading \"" + m_name + "\" shader...");

        m_loadState = LoadState::Reloading;

        m_isCompile = false;
        m_isLink = false;

        if (SR_UTILS_NS::Path(m_name).GetExtensionView() == "srsl") {
            auto &&unit = SRSL::SRSLLoader::Instance().Load(m_name);

            if (!unit) {
                SR_ERROR("Shader::Reload() : failed to load SRSL shader! \n\tPath: " + m_name);
            }

            if (unit)
            {
                m_path = unit->path + "/shader";

                const auto &&createInfo = SRShaderCreateInfo{
                        .polygonMode = unit->createInfo.polygonMode,
                        .cullMode = unit->createInfo.cullMode,
                        .depthCompare = unit->createInfo.depthCompare,
                        .primitiveTopology = unit->createInfo.primitiveTopology,
                        .blendEnabled = unit->createInfo.blendEnabled,
                        .depthWrite = unit->createInfo.depthWrite,
                        .depthTest = unit->createInfo.depthTest,
                };
                SRVerifyFalse2(SetCreateInfo(createInfo), "Failed to validate shader create info!");

                switch (unit->type) {
                    case SRSL::ShaderType::Custom:
                    case SRSL::ShaderType::PostProcessing:
                        break;
                    case SRSL::ShaderType::Spatial: {
                        std::vector<std::pair<std::pair<uint32_t, UBOType>, uint64_t>> uniforms = {};
                        /// 0 - binding
                        /// 1 - type
                        /// 2 - ubo size
                        for (const auto&[binding, size] : unit->GetUniformSizes()) {
                            uniforms.emplace_back(std::pair(std::pair(binding, UBOType::Common), size));
                        }
                        SetUniforms(uniforms);

                        SR_FALLTHROUGH;
                    }
                    case SRSL::ShaderType::SpatialCustom: {
                        auto&&[description, attrib] = Vertices::GetVertexInfo(Vertices::Type::StaticMeshVertex);
                        SetVertex(description, attrib);
                        break;
                    }
                    case SRSL::ShaderType::TransparentSpatial:
                    case SRSL::ShaderType::Animation:
                    case SRSL::ShaderType::Skybox:
                    case SRSL::ShaderType::Canvas:
                    case SRSL::ShaderType::Particles:
                    case SRSL::ShaderType::Unknown:
                    default:
                        SRAssert(false);
                        break;
                }

                m_properties.clear();
                m_samplers.clear();
                for (auto&&[name, sampler] : unit->GetSamplers()) {
                    m_samplers[name] = std::make_pair(
                            sampler.type,
                            sampler.binding
                    );

                    if (sampler.show) {
                        m_properties.emplace_back(std::make_pair(name, sampler.type));
                    }
                }

                m_uniformBlock.DeInit();
                for (auto&&[name, var] : unit->GetUniformBlock()) {
                    m_uniformBlock.Append(SR_RUNTIME_TIME_CRC32_STR(name.c_str()), var.type, !var.show);
                    m_uniformBlock.m_binding = var.binding;

                    if (var.show && !IsMatrixType(var.type)) {
                        m_properties.emplace_back(std::make_pair(name, var.type));
                    }
                }

                m_uniformBlock.Init();
            }
        }

        /// в последнюю очередь
        m_hasErrors = false;
        m_isInit = false;

        m_loadState = LoadState::Loaded;

        UpdateResources();

        m_env->SetBuildState(false);

        return true;
    }
}