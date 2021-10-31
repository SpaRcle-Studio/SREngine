//
// Created by Nikita on 17.11.2020.
//

#include "Render/Shader.h"
#include <Debug.h>
#include <Xml.h>
#include <Environment/Environment.h>
#include <ResourceManager/ResourceManager.h>

using namespace Framework::Helper;

Framework::Graphics::Shader::Shader(Framework::Graphics::Render *render, const std::string& name) : m_env(Environment::Get()) {
    this->m_render  = render;
    this->m_name    = name;
}

bool Framework::Graphics::Shader::Init() {
    if (!Compile()) {
        Debug::Error("Shader::Init() : failed compiling shader!");
        return false;
    }

    if (!Link()) {
        Debug::Error("Shader::Init() : failed linking shader!");
        return false;
    }

    if (m_env->GetPipeLine() == PipeLine::Vulkan)
    {
        std::vector<uint64_t> sizes = {};
        for (auto uniform : m_uniformsInfo)
            if (uniform.first.second == UBOType::Shared)
                sizes.push_back(uniform.second);

        this->m_countSharedUniforms = sizes.size();

        if (!sizes.empty()) {
            this->m_sharedUniforms = (int32_t *) malloc(sizeof(int32_t) * sizes.size());
            for (uint32_t i = 0; i < sizes.size(); i++) {
                 this->m_sharedUniforms[i] = this->m_env->AllocateUBO(sizes[i]);
                 if (this->m_sharedUniforms[i] < 0) {
                     Helper::Debug::Error("Shader::Init() : failed to allocate uniform buffer object!");
                     return false;
                 }
            }
        }
    }

    this->m_isInit = true;

    return true;
}

bool Framework::Graphics::Shader::Compile() {
    if (m_isCompile) {
        Debug::Error("Shader::Compile() : shader already compile!");
        return false;
    }
    Debug::Shader("Shader::Compile() : compiling \""+m_name+"\" shader...");

    m_fbo = m_env->GetCurrentFBO();

    if (this->m_env->GetPipeLine() == PipeLine::OpenGL) {
        if (!m_env->CompileShader(m_name, m_fbo, &m_shaderTempData)) {
            Debug::Error("Shader::Compile() : failed compile opengl \"" + m_name + "\" shader!");
            return false;
        }
    } else {
        auto sizes = std::vector<uint64_t>();
        for (auto info : m_uniformsInfo)
            sizes.push_back(info.second);

        if (!m_env->CompileShader(m_name, m_fbo, &m_shaderTempData, sizes)) {
            Debug::Error("Shader::Compile() : failed compile \"" + m_name + "\" shader!");
            return false;
        }
    }

    m_isCompile = true;

    return true;
}

bool Framework::Graphics::Shader::Link() {
    if (m_isLink) {
        Debug::Error("Shader::Link() : shader already linking!");
        return false;
    }

    if (!m_isCompile){
        Debug::Error("Shader::Link() : shader is not compile!");
        return false;
    }

    Debug::Shader("Shader::Link() : linking \""+this->m_name+"\" shader...");

    if (!m_env->LinkShader(
            &m_shaderProgram,
            &m_shaderTempData,
            this->m_verticesDescription,
            this->m_verticesAttributes,
            this->m_shaderCreateInfo)) {
        Debug::Error("Shader::Link() : failed linking \""+m_name+"\" shader!");
        return false;
    }

    m_isLink = true;

    return true;
}

bool Framework::Graphics::Shader::SetDefaultGeometryShader(Shader* shader) {
    if (g_stdGeometry) {
        Debug::Warn("Shader::SetDefaultGeometryShader() : shader already set!");
        return false;
    }
    else {
        g_stdGeometry = shader;
        return true;
    }
}

bool Framework::Graphics::Shader::Use() noexcept {
    if (!m_isInit) {
        if (m_isError)
            return false;

        if (!this->Init()) {
            Debug::Error("Shader::Use() : failed to initialize shader!");
            this->m_isError = true;
            return false;
        }
        this->m_isInit = true;
    }

    if (m_fbo != m_env->GetCurrentFBO()) {
        Helper::Debug::Info("Shader::Use() : re-create \"" + m_name +  "\" shader...");
        if (!m_env->ReCreateShader(m_shaderProgram)) {
            Debug::Error("Shader::Use() : failed to re-create shader!");
            this->m_isError = true;
            return false;
        } else
            m_fbo = m_env->GetCurrentFBO();
    }

    g_currentShader = this;
    m_env->UseShader(m_shaderProgram);

    return true;
}

void Framework::Graphics::Shader::Free() {
    if (m_isInit) {
        Debug::Shader("Shader::Free() : free \""+m_name + "\" shader class pointer and free video memory...");
        if (!m_env->DeleteShader(m_shaderProgram))
            Helper::Debug::Error("Shader::Free() : failed to free video memory! Name: " + this->m_name);
        this->m_shaderProgram = SR_NULL_SHADER;

        if (m_sharedUniforms) {
            for (uint32_t i = 0; i < m_countSharedUniforms; i++)
                if (!this->m_env->FreeUBO(this->m_sharedUniforms[i]))
                    Helper::Debug::Error("Shader::Free() : failed to free uniform buffer object!");
            free(m_sharedUniforms);
            this->m_countSharedUniforms = 0;
        }
    } else {
        Debug::Shader("Shader::Free() : free \""+m_name + "\" shader class pointer...");
    }

    delete this;
}

bool Framework::Graphics::Shader::SetVertex(
        const std::vector<SR_VERTEX_DESCRIPTION>& descriptions,
        const std::vector<std::pair<Vertices::Attribute, size_t>> &attributes) {
    if (m_isInit) {
        Helper::Debug::Error("Shader::SetVertexDescriptions() : shader already initialized!");
        return false;
    } else {
        this->m_verticesDescription = descriptions;
        this->m_verticesAttributes  = attributes;
    }

    return true;
}

bool Framework::Graphics::Shader::SetCreateInfo(Framework::Graphics::SRShaderCreateInfo shaderCreateInfo) {
    if (m_isInit) {
        Helper::Debug::Error("Shader::SetCreateInfo() : shader already initialized!");
        return false;
    } else
        this->m_shaderCreateInfo = shaderCreateInfo;

    return true;
}

bool Framework::Graphics::Shader::SetUniforms(const std::vector<std::pair<std::pair<uint32_t, UBOType>, uint64_t>> &uniforms) {
    if (m_isInit) {
        Helper::Debug::Error("Shader::SetUniforms() : shader already initialized!");
        return false;
    } else
        this->m_uniformsInfo = uniforms;

    return true;
}

void Framework::Graphics::Shader::CopyVertexAndUniformsInfo(const Framework::Graphics::Shader *source) {
    if (m_isInit) {
        Helper::Debug::Error("Shader::CopyVertexAndUniformsInfo() : shader already initialized!");
        return;
    }

    this->m_verticesAttributes  = source->m_verticesAttributes;
    this->m_verticesDescription = source->m_verticesDescription;
    this->m_uniformsInfo        = source->m_uniformsInfo;
}

Framework::Graphics::Shader *Framework::Graphics::Shader::Load(Render* render, const std::string &name) {
    Helper::Debug::Log("Shader::Load() : load \"" + name + "\" shader...");

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

    auto vertexParser = [=](Shader* shader, const Xml::Node& node) {
        if (auto vertex = getInheritNode(node, "Vertex")) {
            auto [descr, attrib] = Vertices::GetVertexInfo(Vertices::StringToEnumType(vertex.GetAttribute("value").ToString()));
            shader->SetVertex(descr, attrib);
        }
    };

    auto uniformParsers = [=](Shader* shader, const Xml::Node& node) {
        if (auto xmlUniforms = getInheritNode(node, "Uniforms")) {
            std::vector<std::pair<std::pair<uint32_t, UBOType>, uint64_t>> uniforms = {};
            // 0 - binding
            // 1 - type
            // 2 - ubo siz
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

    auto infoParser = [=](Shader* shader, const Xml::Node& node) {
        SRShaderCreateInfo createInfo = {};
        if (auto info = getInheritNode(node, "Info")) {
            if (auto value = info.GetNode("PolygonMode"))
                createInfo.polygonMode = StringToEnumPolygonMode(value.GetAttribute("value").ToString());

            if (auto value = info.GetNode("CullMode"))
                createInfo.cullMode = StringToEnumCullMode(value.GetAttribute("value").ToString());

            if (auto value = info.GetNode("DepthCompare"))
                createInfo.depthCompare = StringToEnumDepthCompare(value.GetAttribute("value").ToString());

            if (auto value = info.GetNode("DepthWrite"))
                createInfo.depthWrite = value.GetAttribute("value").ToBool();

            if (auto value = info.GetNode("DepthTest"))
                createInfo.depthTest = value.GetAttribute("value").ToBool();
        }
        shader->SetCreateInfo(createInfo);
    };

    auto shaderParser = [=](const Xml::Node& node) -> Shader* {
        if (auto path = node.GetAttribute("path"); path.Valid()) {
            auto shader = new Shader(render, path.ToString()); {
                vertexParser(shader, node);
                uniformParsers(shader, node);
                infoParser(shader, node);
            }
            return shader;
        } else
            return nullptr;
    };

    auto createInfoPath = Helper::StringUtils::MakePath(Helper::ResourceManager::Instance().GetResourcesFolder() + "/Shaders/CreateInfo.xml");
    if (FileSystem::FileExists(createInfoPath)) {
        auto xml = Helper::Xml::Document::Load(createInfoPath);
        shaders = xml.Root().GetNode("Shaders").GetNodes();
        if (auto shaderXml = findShader(name)) {
            auto shader = shaderParser(shaderXml);
            if (!shader)
                Helper::Debug::Error("Shader::Load() : failed to load \"" + name + "\" shader!");
            return shader;
        }
    } else
        Helper::Debug::Error("Shader::Load() : create info file not found! \n\tPath: " + createInfoPath);

    return nullptr;
}

