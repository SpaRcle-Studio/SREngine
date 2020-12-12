//
// Created by Nikita on 20.11.2020.
//

#include "Types/Skybox.h"
#include <ResourceManager/ResourceManager.h>
#include <Utils/StringUtils.h>
#include <stbi/stb_image.h>
#include <Debug.h>

Framework::Graphics::Types::Skybox::Skybox() {
    this->m_env = Environment::Get();
    this->m_data.resize(6);
}

Framework::Graphics::Types::Skybox::~Skybox() {

}

Framework::Graphics::Types::Skybox *Framework::Graphics::Types::Skybox::Load(std::string name, std::string ext) {
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

    Skybox* skybox = new Skybox();

    skybox->m_width = W;
    skybox->m_height = H;
    skybox->m_data = sides;

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

void Framework::Graphics::Types::Skybox::AwaitDestroy() {

}

bool Framework::Graphics::Types::Skybox::Free() {
    return false;
}

void Framework::Graphics::Types::Skybox::Draw() {
    if (!m_isCalculated)
        this->Calculate();

    m_env->SetActiveTexture(0);

    m_env->DrawSkybox(m_VAO, m_cubeMap);
}
