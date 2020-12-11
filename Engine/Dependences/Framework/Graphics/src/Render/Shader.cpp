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

void Framework::Graphics::Shader::SetBool(const std::string &name, bool v) const noexcept { m_env->SetBool(m_ID, name, v); }

void Framework::Graphics::Shader::SetFloat(const std::string &name, float v) const noexcept {
    m_env->SetFloat(m_ID, name, v);
}

void Framework::Graphics::Shader::SetInt(const std::string &name, int v) const noexcept { m_env->SetInt(m_ID, name, v); }
void Framework::Graphics::Shader::SetMat4(const std::string &name, glm::mat4 v) const noexcept { m_env->SetMat4(m_ID, name, v); }

void Framework::Graphics::Shader::SetVec4(const std::string &name, glm::vec4 v) const noexcept {

}

void Framework::Graphics::Shader::SetVec3(const std::string &name, glm::vec3 v) const noexcept {
    m_env->SetVec3(m_ID, name, v);
}

void Framework::Graphics::Shader::SetVec2(const std::string &name, glm::vec2 v) const noexcept {

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

Framework::Graphics::Shader *Framework::Graphics::Shader::GetStandartGeometryShader() noexcept {
    if (!g_stdGeometry)
        Debug::Error("Shader::GetStandartGeometryShader() : shader is nullptr!");

    return g_stdGeometry;
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

bool Framework::Graphics::Shader::Use() {
    if (!m_isLink)
        return false;

    m_env->UseShader(m_ID);

    return true;
}

