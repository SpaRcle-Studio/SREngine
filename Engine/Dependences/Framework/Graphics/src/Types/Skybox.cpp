//
// Created by Nikita on 20.11.2020.
//

#include "Types/Skybox.h"
#include <ResourceManager/ResourceManager.h>
#include <Utils/StringUtils.h>
#include <stbi/stb_image.h>
#include <Debug.h>
#include <Render/Render.h>
#include <Window/Window.h>

Framework::Graphics::Types::Skybox::Skybox() {
    this->m_env = Environment::Get();
    this->m_data.resize(6);
}

Framework::Graphics::Types::Skybox::~Skybox() = default;

Framework::Graphics::Types::Skybox *Framework::Graphics::Types::Skybox::Load(std::string name, const std::string& shader_name) {
    std::string ext = StringUtils::GetExtensionFromFilePath(name);
    name.resize(name.size() - ext.size() - 1);

    std::string path = Helper::ResourceManager::GetResourcesFolder() + "/Skyboxes/"+name + "/";

#ifdef WIN32
    path = Helper::StringUtils::MakePath(path, true);
#else
    path = Helper::StringUtils::MakePath(path, false);
#endif

    Helper::Debug::Log("Skybox::Load() : loading \""+name+"\" skybox...");

    std::vector<unsigned char*> sides = {
            nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr
    };
    static const std::string files[6]{ "right", "left", "top", "bottom", "front", "back" };

    int W, H, C;

    for (unsigned char i = 0; i < 6; i++) {
        int w = 0, h = 0, comp = 0;
        unsigned char* data = stbi_load(std::string(path + files[i] + "." + ext).c_str(), &w, &h, &comp, 3);

        if (!i) {
            W = w;
            H = h;
            C = comp;
        } else if (h != H || w != W || C != comp) {
            Helper::Debug::Warn("Skybox::Load() : \""+name+"\" skybox has different sizes!");
        }

        if (!data) {
            Helper::Debug::Error("Skybox::Load() : failed load \"" + name + "\" skybox!\n\tPath: "+path + files[i] + "." + ext);
            return nullptr;
        }
        sides[i] = data;
    }

    auto* skybox = new Skybox();

    skybox->m_shaderName = shader_name;
    skybox->m_width  = W;
    skybox->m_height = H;
    skybox->m_data   = sides;

    return skybox;
}

bool Framework::Graphics::Types::Skybox::Calculate() {
    if (m_isCalculated) {
        Helper::Debug::Error("Skybox::Calculate() : skybox already calculated!");
        return false;
    }

    if (m_isDestroy) {
        Helper::Debug::Error("Skybox::Calculate() : skybox is destroyed!");
        return false;
    }

    m_cubeMap = m_env->CalculateCubeMap(m_width, m_height, m_data);

    if (!m_cubeMap) {
        Helper::Debug::Error("Skybox::Calculate() : failed calculate cube map!");
        return false;
    }

    m_VAO = m_env->CalculateSkybox();

    m_isCalculated = true;
    return true;
}

bool Framework::Graphics::Types::Skybox::AwaitDestroy() {
    if (m_isDestroy){
        Debug::Error("Skybox::AwaitDestroy() : skybox already destroyed!");
        return false;
    } else
        Debug::Log("Skybox::AwaitDestory() : destroying skybox...");

    if (m_isCalculated) {
        this->m_render->DelayedDestroySkybox();
        ret:
        if (!this->m_isVideoFree && m_render->GetWindow()->IsWindowOpen())
            goto ret;
    }

    this->m_isDestroy = true;
    return true;
}

bool Framework::Graphics::Types::Skybox::Free() {
    Debug::Log("Skybox::Free() : free skybox pointer...");

    if (m_isCalculated)
        if (!m_isVideoFree) {
            if (m_render->GetWindow()->IsWindowOpen())
                Debug::Warn("Skybox::Free() : video memory is not free!");
            else
                Debug::Warn("Skybox::Free() : video memory is not free! Window is closed.");
        }

    if (m_isDestroy) {
        delete this;
        return true;
    }else{
        Debug::Error("Skybox::Free() : before freeing skybox memory, you need to destroy it!");
        return false;
    }
}

void Framework::Graphics::Types::Skybox::Draw(Camera* camera) {
    if (!m_isCalculated)
        this->Calculate();

    if (!m_shader)
        return;
    else{
        m_shader->Use();
        camera->UpdateShader(m_shader);
        m_shader->SetVec3("CamPos", camera->GetGLPosition());
    }

    //m_env->SetActiveTexture(0);

    m_env->DrawSkybox(m_VAO, m_cubeMap);
}

bool Framework::Graphics::Types::Skybox::SetRender(Render *render) {
    if (m_render) {
        Debug::Error("Skybox::SetRender() : render already set!");
        return false;
    }

    this->m_render = render;

    this->m_shader = new Shader(m_render, m_shaderName);

    return true;
}

bool Framework::Graphics::Types::Skybox::FreeVideoMemory() {
    if (m_isVideoFree) {
        Debug::Error("Skybox::FreeVideoMemory() : video memory already free!");
        return false;
    }

    Debug::Log("Skybox::FreeVideoMemory() : free skybox video memory...");

    if (m_shader)
        m_shader->Free();

    if (m_VAO)
        if (!this->m_env->FreeVAO(m_VAO))
            Helper::Debug::Error("Skybox::FreeVideoMemory() : failed to free VAO!");

    if (m_cubeMap)

        this->m_env->FreeCubeMap(m_cubeMap);

    return true;
}
