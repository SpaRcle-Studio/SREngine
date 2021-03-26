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

    std::string path = ResourceManager::GetResourcesFolder() + "\\Shaders\\" + m_name;
    this->m_fields = m_env->GetShaderFields(m_ID, path);

    this->m_isInit = true;

    return true;
}


bool Framework::Graphics::Shader::Compile() {
    if (m_isCompile) {
        Debug::Error("Shader::Compile() : shader already compile!");
        return false;
    }
    std::string path = ResourceManager::GetResourcesFolder() + "\\Shaders\\" + m_name;

    Debug::Shader("Shader::Compile() : compiling \""+m_name+"\" shader...");

    if (!m_env->CompileShader(path, &m_fragment, &m_vertex)){
        Debug::Error("Shader::Compile() : failed compile \""+m_name+"\" shader!");
        return false;
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

    m_ID = m_env->LinkShader(&m_fragment, &m_vertex);
    if (m_ID == 0){
        Debug::Error("Shader::Link() : failed linking \""+m_name+"\" shader!");
        return false;
    }

    m_isLink = true;

    return true;
}

bool Framework::Graphics::Shader::SetStandartGeometryShader(Shader* shader) noexcept {
    if (g_stdGeometry) {
        Debug::Warn("Shader::SetStandartGeometryShader() : shader already set!");
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

    m_env->UseShader(m_ID);

    return true;
}

void Framework::Graphics::Shader::Free() {
    if (m_isInit) {
        Debug::Shader("Shader::Free() : free \""+m_name + "\" shader class pointer and free video memory...");
        m_env->DeleteShader(m_ID);
    } else {
        Debug::Shader("Shader::Free() : free \""+m_name + "\" shader class pointer...");
    }

    delete this;
}

