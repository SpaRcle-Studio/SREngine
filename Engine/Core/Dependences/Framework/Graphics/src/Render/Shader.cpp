//
// Created by Nikita on 17.11.2020.
//

#include "Render/Shader.h"
#include <Debug.h>
#include <Xml.h>
#include <Environment/Environment.h>
#include <ResourceManager/ResourceManager.h>

using namespace Framework::Helper;

Framework::Graphics::Shader::Shader(Framework::Graphics::Render *render, std::string path, std::string name)
    : IResource(typeid(Shader).name())
    , m_env(Environment::Get())
    , m_render(render)
    , m_path(std::move(path))
    , m_name(std::move(name))
{
    SetId(m_name);
}

Framework::Graphics::Shader::Shader(Framework::Graphics::Render *render, std::string path)
    : Shader(render, std::move(path), "Unnamed")
{ }

bool Framework::Graphics::Shader::Init() {
    if (m_isInit)
        return true;

    if (!Compile()) {
        SR_ERROR("Shader::Init() : failed compiling shader!");
        return false;
    }

    if (!Link()) {
        SR_ERROR("Shader::Init() : failed linking shader!");
        return false;
    }

    if (m_env->GetPipeLine() == PipeLine::Vulkan)
    {
        std::vector<uint64_t> sizes = {};
        for (const auto& uniform : m_uniformsInfo)
            if (uniform.first.second == UBOType::Shared)
                sizes.push_back(uniform.second);

        m_countSharedUniforms = sizes.size();

        if (!sizes.empty()) {
            m_sharedUniforms = (int32_t *) malloc(sizeof(int32_t) * sizes.size());
            for (uint32_t i = 0; i < sizes.size(); ++i) {
                 m_sharedUniforms[i] = m_env->AllocateUBO(sizes[i]);
                 if (m_sharedUniforms[i] < 0) {
                     SR_ERROR("Shader::Init() : failed to allocate uniform buffer object!");
                     return false;
                 }
            }
        }
    }

    m_isInit = true;

    return true;
}

bool Framework::Graphics::Shader::Compile() {
    if (m_isCompile) {
        SR_ERROR("Shader::Compile() : shader already compile!");
        return false;
    }
    Debug::Shader("Shader::Compile() : compiling \"" + m_path + "\" shader...");

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

bool Framework::Graphics::Shader::Link() {
    if (m_isLink) {
        SR_ERROR("Shader::Link() : shader already linking!");
        return false;
    }

    if (!m_isCompile){
        SR_ERROR("Shader::Link() : shader is not compile!");
        return false;
    }

    Debug::Shader("Shader::Link() : linking \"" + m_path + "\" shader...");

    if (!m_env->LinkShader(&m_shaderProgram, &m_shaderTempData, m_verticesDescription, m_verticesAttributes, m_shaderCreateInfo)) {
        SR_ERROR("Shader::Link() : failed linking \"" + m_path + "\" shader!");
        return false;
    }

    m_isLink = true;

    return true;
}

bool Framework::Graphics::Shader::Use() noexcept {
    if (!m_isInit) {
        if (m_isError)
            return false;

        if (!Init()) {
            SR_ERROR("Shader::Use() : failed to initialize shader!");
            m_isError = true;
            return false;
        }
        m_isInit = true;
    }

    if (m_fbo != m_env->GetCurrentFBO()) {
        SR_INFO("Shader::Use() : re-create \"" + m_path +  "\" shader...");
        if (!m_env->ReCreateShader(m_shaderProgram)) {
            SR_ERROR("Shader::Use() : failed to re-create shader!");
            m_isError = true;
            return false;
        }
        else
            m_fbo = m_env->GetCurrentFBO();
    }

    g_currentShader = this;
    m_env->UseShader(m_shaderProgram);

    return true;
}

void Framework::Graphics::Shader::FreeVideoMemory() {
    if (m_isInit) {
        SR_SHADER("Shader::Free() : free \"" + m_path + "\" shader class pointer and free video memory...");

        if (!m_env->DeleteShader(m_shaderProgram)) {
            SR_ERROR("Shader::Free() : failed to free video memory! Name: " + m_path);
        }
        m_shaderProgram = SR_NULL_SHADER;

        if (m_sharedUniforms) {
            for (uint32_t i = 0; i < m_countSharedUniforms; ++i) {
                if (!m_env->FreeUBO(m_sharedUniforms[i]))
                    SR_ERROR("Shader::Free() : failed to free uniform buffer object!");
            }

            free(m_sharedUniforms);
            m_sharedUniforms = nullptr;

            m_countSharedUniforms = 0;
        }
    }
    else {
        SR_SHADER("Shader::Free() : free \"" + m_path + "\" shader class pointer...");
    }
}

bool Framework::Graphics::Shader::SetVertex(const std::vector<SR_VERTEX_DESCRIPTION>& descriptions, const std::vector<std::pair<Vertices::Attribute, size_t>> &attributes) {
    if (m_isInit) {
        Helper::Debug::Error("Shader::SetVertexDescriptions() : shader already initialized!");
        return false;
    }
    else {
        m_verticesDescription = descriptions;
        m_verticesAttributes  = attributes;
    }

    return true;
}

bool Framework::Graphics::Shader::SetCreateInfo(Framework::Graphics::SRShaderCreateInfo shaderCreateInfo) {
    if (m_isInit) {
        Helper::Debug::Error("Shader::SetCreateInfo() : shader already initialized!");
        return false;
    }
    else
        m_shaderCreateInfo = shaderCreateInfo;

    return m_shaderCreateInfo.Validate();
}

bool Framework::Graphics::Shader::SetUniforms(const std::vector<std::pair<std::pair<uint32_t, UBOType>, uint64_t>> &uniforms) {
    if (m_isInit) {
        Helper::Debug::Error("Shader::SetUniforms() : shader already initialized!");
        return false;
    }
    else
        m_uniformsInfo = uniforms;

    return true;
}

void Framework::Graphics::Shader::CopyVertexAndUniformsInfo(const Framework::Graphics::Shader *source) {
    if (m_isInit) {
        SR_ERROR("Shader::CopyVertexAndUniformsInfo() : shader already initialized!");
        return;
    }

    m_verticesAttributes  = source->m_verticesAttributes;
    m_verticesDescription = source->m_verticesDescription;
    m_uniformsInfo        = source->m_uniformsInfo;
}

Framework::Graphics::Shader *Framework::Graphics::Shader::Load(Render* render, const SR_UTILS_NS::Path& path) {
    if (auto&& pShader = ResourceManager::Instance().Find<Shader>(path.ToString())) {
        SRAssert(render == pShader->m_render);
        return pShader;
    }

    SR_LOG("Shader::Load() : load \"" + path.ToString() + "\" shader...");

    if (path.GetExtensionView() == "srsl") {
        auto&& unit = SRSL::SRSLLoader::Instance().Load(path.ToString());

        if (!unit) {
            SR_ERROR("Shader::Load() : failed to load SRSL shader! \n\tPath: " + path.ToString());
            return nullptr;
        }

        auto&& shader = new Shader(render, unit->path + "/shader", path.ToString());

        {
            const auto&& createInfo = SRShaderCreateInfo{
                .polygonMode = unit->createInfo.polygonMode,
                .cullMode = unit->createInfo.cullMode,
                .depthCompare = unit->createInfo.depthCompare,
                .primitiveTopology = unit->createInfo.primitiveTopology,
                .blendEnabled = unit->createInfo.blendEnabled,
                .depthWrite = unit->createInfo.depthWrite,
                .depthTest = unit->createInfo.depthTest,
            };
            SRVerifyFalse2(shader->SetCreateInfo(createInfo), "Failed to validate shader create info!");

            switch (unit->type) {
                case SRSL::ShaderType::Spatial: {
                    auto&&[description, attrib] = Vertices::GetVertexInfo(Vertices::Type::StaticMeshVertex);
                    shader->SetVertex(description, attrib);

                    std::vector<std::pair<std::pair<uint32_t, UBOType>, uint64_t>> uniforms = {};
                    // 0 - binding
                    // 1 - type
                    // 2 - ubo size
                    for (const auto& [binding, size] : unit->GetUniformSizes()) {
                        uniforms.emplace_back(std::pair(std::pair(binding, UBOType::Common), size));
                    }
                    shader->SetUniforms(uniforms);
                    break;
                }
                case SRSL::ShaderType::TransparentSpatial:
                case SRSL::ShaderType::Animation:
                case SRSL::ShaderType::PostProcess:
                case SRSL::ShaderType::Skybox:
                case SRSL::ShaderType::Canvas:
                case SRSL::ShaderType::Particles:
                case SRSL::ShaderType::Unknown:
                default:
                    SRAssert(false);
                    break;
            }
        }

        return shader;
    }
    else
        return LoadFromConfig(render, path.ToString());
}

Framework::Graphics::Shader* Framework::Graphics::Shader::LoadFromConfig(Framework::Graphics::Render *render, const std::string &name) {
    std::vector<Xml::Node> shaders = {};

    auto findShader = [&shaders](const std::string& name) -> Xml::Node {
        for (const auto &shaderXml : shaders)
            if (shaderXml.GetAttribute("name").ToString() == name)
                return shaderXml;
        return Xml::Node::Empty();
    };

    typedef std::function<Xml::Node(const Xml::Node& node, const std::string& attribName)> getInheritNodeFun;
    getInheritNodeFun getInheritNode = [findShader, name, &getInheritNode](const Xml::Node& node, const std::string& nodeName) -> Xml::Node {
        if (auto targetNode = node.GetNode(nodeName)) {
            if (auto inherit = targetNode.GetAttribute("inherit")) {
                if (auto inheritShader = findShader(inherit.ToString()))
                    return getInheritNode(inheritShader, nodeName);
                else
                    Helper::Debug::Error("Shader::Load() [getInheritAttrib] : \"" + inherit.ToString() +
                                         "\" inherit shader not found! \n\tShader name: " + name);
            } else
                return targetNode;
        }
        return Xml::Node::Empty();
    };

    auto&& vertexParser = [=](Shader* shader, const Xml::Node& node) {
        if (auto vertex = getInheritNode(node, "Vertex")) {
            auto [descr, attrib] = Vertices::GetVertexInfo(Vertices::StringToEnumType(vertex.GetAttribute("value").ToString()));
            shader->SetVertex(descr, attrib);
        }
    };

    auto&& uniformParsers = [=](Shader* shader, const Xml::Node& node) {
        if (auto xmlUniforms = getInheritNode(node, "Uniforms")) {
            std::vector<std::pair<std::pair<uint32_t, UBOType>, uint64_t>> uniforms = {};
            // 0 - binding
            // 1 - type
            // 2 - ubo size
            for (const auto& uniform : xmlUniforms.GetNodes()) {
                uniforms.emplace_back(std::pair(
                        std::pair(
                                (uint32_t)uniform.GetAttribute("binding").ToInt(),
                                StringToEnumUBOType(uniform.GetAttribute("type").ToString())),
                        (uint64_t)GetUniformSize(uniform.GetAttribute("UBO").ToString())));
            }
            shader->SetUniforms(uniforms);
        }
    };

    auto&& infoParser = [=](Shader* shader, const Xml::Node& node) {
        auto createInfo = SRShaderCreateInfo();
        if (auto info = getInheritNode(node, "Info")) {
            if (auto value = info.GetNode("PolygonMode"))
                createInfo.polygonMode = StringToEnumPolygonMode(value.GetAttribute("value").ToString());

            if (auto value = info.GetNode("CullMode"))
                createInfo.cullMode = StringToEnumCullMode(value.GetAttribute("value").ToString());

            if (auto value = info.GetNode("DepthCompare"))
                createInfo.depthCompare = StringToEnumDepthCompare(value.GetAttribute("value").ToString());

            if (auto value = info.GetNode("PrimitiveTopology"))
                createInfo.primitiveTopology = StringToEnumPrimitiveTopology(value.GetAttribute("value").ToString());

            if (auto value = info.GetNode("BlendEnabled"))
                createInfo.blendEnabled = value.GetAttribute("value").ToBool();

            if (auto value = info.GetNode("DepthWrite"))
                createInfo.depthWrite = value.GetAttribute("value").ToBool();

            if (auto value = info.GetNode("DepthTest"))
                createInfo.depthTest = value.GetAttribute("value").ToBool();
        }
        SRAssert2(shader->SetCreateInfo(createInfo), "Failed to validate shader create info!");
    };

    auto&& shaderParser = [=](const Xml::Node& node) -> Shader* {
        if (auto path = node.GetAttribute("path"); path.Valid()) {
            auto shader = new Shader(render, path.ToString(), name); {
                vertexParser(shader, node);
                uniformParsers(shader, node);
                infoParser(shader, node);
            }
            return shader;
        }
        else
            return nullptr;
    };

    auto&& createInfoPath = Helper::StringUtils::MakePath(Helper::ResourceManager::Instance().GetResPath().Concat("/Shaders/CreateInfo.xml"));

    if (FileSystem::FileExists(createInfoPath)) {
        auto xml = Helper::Xml::Document::Load(createInfoPath);
        shaders = xml.Root().GetNode("Shaders").GetNodes();
        if (auto shaderXml = findShader(name)) {
            auto shader = shaderParser(shaderXml);
            if (!shader) {
                SR_ERROR("Shader::LoadFromConfig() : failed to load \"" + name + "\" shader!");
            }
            return shader;
        }
        else
            SR_ERROR("Shader::LoadFromConfig() : shader \"" + name + "\" have not config!");
    }
    else
        SR_ERROR("Shader::LoadFromConfig() : create info file not found! \n\tPath: " + createInfoPath);

    return nullptr;
}

