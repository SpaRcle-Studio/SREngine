//
// Created by Nikita on 03.12.2020.
//

#define STB_IMAGE_IMPLEMENTATION

#include "stbi/stb_image.c"

#include <Utils/StringUtils.h>
#include "Loaders/TextureLoader.h"
#include <Types/Texture.h>

#include <Debug.h>

SR_GTYPES_NS::Texture *Framework::Graphics::TextureLoader::Load(std::string path) {
#ifdef WIN32
    path = Helper::StringUtils::MakePath(path, true);
#else
    path = StringUtils::MakePath(path, false);
#endif

    SR_GTYPES_NS::Texture* texture = nullptr;

    {
        int width, height, numComponents;

        unsigned char* imgData = stbi_load(path.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

        if (!imgData) {
            SR_ERROR("TextureLoader::Load() : can not load \""+path + "\" file!");
            return texture;
        }

        texture = new SR_GTYPES_NS::Texture();

        texture->m_height = height;
        texture->m_width  = width;
        texture->m_data   = imgData;
        texture->m_config.m_alpha = (numComponents == 4) ? Helper::BoolExt::True : Helper::BoolExt::False;
    }

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

SR_GTYPES_NS::Texture *Framework::Graphics::TextureLoader::GetDefaultTexture() noexcept {
    return nullptr;
}

SR_GTYPES_NS::Texture *Framework::Graphics::TextureLoader::LoadFromMemory(const std::string& data) {
    SR_GTYPES_NS::Texture* texture = nullptr;

    {
        int width, height, numComponents;

        unsigned char* imgData = stbi_load_from_memory(
                reinterpret_cast<const stbi_uc*>(data.c_str()),
                data.size(), &width, &height, &numComponents, STBI_rgb_alpha
        );

        if (!imgData) {
            std::string reason;
            if (stbi_failure_reason())
                reason = stbi_failure_reason();

            SR_ERROR("TextureLoader::LoadFromMemory() : can not load texture from memory!\n\tReason: " + reason);
            return texture;
        }

        texture = new Types::Texture();

        texture->m_height = height;
        texture->m_width  = width;
        texture->m_data   = imgData;
        texture->m_config.m_alpha = (numComponents == 4) ? Helper::BoolExt::True : Helper::BoolExt::False;
    }

    return texture;
}
