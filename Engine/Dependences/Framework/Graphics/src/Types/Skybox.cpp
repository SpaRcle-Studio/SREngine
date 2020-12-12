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
        unsigned char* data = stbi_load(std::string(path + files[i] + "." + ext).c_str(), &w, &h, &comp, 4);

        if (!i) {
            W = w;
            H = h;
            C = comp;
        } else if (h != H || w != W || C != comp) {
            Helper::Debug::Warn("Skybox::Load() : \""+name+"\" skybox has different sizes!");
        }

        if (!data) {
            Helper::Debug::Error("Skybox::Load() : failed load \"" + name + "\" skybox!");
            return nullptr;
        }
        sides[i] = data;
    }

    Skybox* skybox = new Skybox();

    skybox->m_data = sides;

    return skybox;
}
