//
// Created by Nikita on 03.12.2020.
//

#define STB_IMAGE_IMPLEMENTATION

#include <Utils/Common/StringUtils.h>
#include <Utils/Debug.h>

#include <Graphics/Loaders/TextureLoader.h>
#include <Graphics/Types/Texture.h>

#include <stbi/stb_image.c>

bool Framework::Graphics::TextureLoader::Load(Types::Texture* texture, std::string path) {
    if (!SRVerifyFalse(!texture)) {
        return false;
    }

    if (!SRVerifyFalse2(texture->m_data, "Texture already loaded!")) {
        return false;
    }

    int width, height, numComponents;

    unsigned char* imgData = stbi_load(path.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

    if (!imgData) {
        SR_ERROR("TextureLoader::Load() : can not load \"" + path + "\" file!");
        return false;
    }

    texture->m_height     = height;
    texture->m_width      = width;
    texture->m_channels   = numComponents;
    texture->m_data       = imgData;
    texture->m_config.m_alpha = (numComponents == 4) ? Helper::BoolExt::True : Helper::BoolExt::False;

    return true;
}

bool Framework::Graphics::TextureLoader::Free(unsigned char *data) {
    if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
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

bool Framework::Graphics::TextureLoader::LoadFromMemory(Types::Texture* texture, const std::string& data) {
    if (!SRVerifyFalse(!texture)) {
        return false;
    }

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

        return false;
    }

    texture->m_height = height;
    texture->m_width  = width;
    texture->m_data   = imgData;
    texture->m_config.m_alpha = (numComponents == 4) ? Helper::BoolExt::True : Helper::BoolExt::False;

    return true;
}