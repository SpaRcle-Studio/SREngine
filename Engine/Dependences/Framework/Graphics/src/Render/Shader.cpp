//
// Created by Nikita on 17.11.2020.
//

#include "Render/Shader.h"
#include <Debug.h>
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

    //std::string path = ResourceManager::GetResourcesFolder() + "\\Shaders\\" + m_name;
    //this->m_fields = m_env->GetShaderFields(m_ID, path);

    this->m_isInit = true;

    return true;
}


bool Framework::Graphics::Shader::Compile() {
    if (m_isCompile) {
        Debug::Error("Shader::Compile() : shader already compile!");
        return false;
    }
    Debug::Shader("Shader::Compile() : compiling \""+m_name+"\" shader...");

    if (this->m_env->GetPipeLine() == PipeLine::OpenGL) {
        if (!m_env->CompileShader(m_name, -1, &m_shaderTempData)) {
            Debug::Error("Shader::Compile() : failed compile opengl \"" + m_name + "\" shader!");
            return false;
        }
    } else {
        if (!m_env->CompileShader(m_name, m_env->GetCurrentFBO(), &m_shaderTempData)) {
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

bool Framework::Graphics::Shader::SetStandardGeometryShader(Shader* shader) noexcept {
    if (g_stdGeometry) {
        Debug::Warn("Shader::SetStandardGeometryShader() : shader already set!");
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
            Debug::Error("Shader::Use() : failed initialize shader!");
            this->m_isError = true;
            return false;
        }
        this->m_isInit = true;
    }

    m_env->UseShader(m_shaderProgram);

    return true;
}

void Framework::Graphics::Shader::Free() {
    if (m_isInit) {
        Debug::Shader("Shader::Free() : free \""+m_name + "\" shader class pointer and free video memory...");
        m_env->DeleteShader(m_shaderProgram);
        m_env->FreeShaderProgram(m_shaderProgram);
        this->m_shaderProgram = SR_NULL_SHADER;
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

