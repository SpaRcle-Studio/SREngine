//
// Created by Nikita on 03.12.2020.
//

#define STB_IMAGE_IMPLEMENTATION

#include "stbi/stb_image.c"

#include <Utils/StringUtils.h>
#include "Loaders/TextureLoader.h"
#include <Types/Texture.h>

#include <Debug.h>

using namespace Framework::Graphics::Types;

Texture *Framework::Graphics::TextureLoader::Load(std::string path) {
#ifdef WIN32
    path = Helper::StringUtils::MakePath(path, true);
#else
    path = StringUtils::MakePath(path, false);
#endif

    Texture* texture = nullptr;

    {
        int width, height, numComponents;

        unsigned char* imgData = stbi_load(path.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

        if (!imgData) {
            SR_ERROR("TextureLoader::Load() : can not load \""+path + "\" file!");
            return texture;
        }

        texture = new Texture();

        texture->m_height = height;
        texture->m_width  = width;
        texture->m_data   = imgData;
        texture->m_config.m_alpha = (numComponents == 4) ? Helper::BoolExt::True : Helper::BoolExt::False;
    }

    //texture->m_resource_id = path;

    return texture;
}

bool Framework::Graphics::TextureLoader::Free(unsigned char *data) {
    if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High) {
        SR_LOG("TextureLoader::Free() : free source image data...");
    }

    if (data) {
        stbi_image_free(data);
    }
    else {
        SR_ERROR("TextureLoader::Free() : data is nullptr!");
        return false;
    }
    return true;
}

Texture *Framework::Graphics::TextureLoader::GetDefaultTexture() noexcept {
    return nullptr;
}

bool Framework::Graphics::TextureLoader::SetDefaultTexture(Texture *texture) noexcept {
    return false;
}
