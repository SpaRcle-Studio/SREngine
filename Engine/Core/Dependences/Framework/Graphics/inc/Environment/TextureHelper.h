//
// Created by Nikita on 12.12.2020.
//

#ifndef GAMEENGINE_TEXTUREHELPER_H
#define GAMEENGINE_TEXTUREHELPER_H

#include <cstdint>
#include <utility>
#include <string>
#include <Utils/Enumerations.h>

namespace Framework::Graphics {
    SR_ENUM_CLASS(TextureFormat,
        Unknown      = 0,

        RGBA8_UNORM  = 10000,
        RGBA16_UNORM = 10001,

        RGBA8_SRGB   = 20000,
    );

    inline static bool IsSRGB(TextureFormat f) {
        return f >= TextureFormat::RGBA8_SRGB || f <= TextureFormat::RGBA8_SRGB;
    }

    inline static bool IsUNORM(TextureFormat f) {
        return f >= TextureFormat::RGBA8_UNORM || f <= TextureFormat::RGBA16_UNORM;
    }

    SR_ENUM_CLASS(TextureType,
        Unknown, Diffuse, Normal, Specular, Roughness, Glossiness
    );

    SR_ENUM_CLASS(TextureFilter,
        Unknown = 0, NEAREST = 1, LINEAR = 2, NEAREST_MIPMAP_NEAREST = 3,
        LINEAR_MIPMAP_NEAREST = 4, NEAREST_MIPMAP_LINEAR = 5, LINEAR_MIPMAP_LINEAR = 6
    );

    SR_ENUM_CLASS(TextureCompression,
        None = 0, BC1 = 1, BC2 = 2, BC3 = 3, BC4 = 4, BC5 = 5, BC6 = 6, BC7 = 7
    );

    inline static uint32_t Find4(uint32_t i) {
        if (i % 4 == 0)
            return i;
        else
            return Find4(i - 1);
    }

    inline static auto MakeGoodSizes(uint32_t w, uint32_t h) -> auto {
        return std::pair(Find4(w), Find4(h));
    }

    inline static uint8_t* ResizeToLess(uint32_t ow, uint32_t oh, uint32_t nw, uint32_t nh, uint8_t* pixels) {
        auto* image = (uint8_t*)malloc(nw * nh * 4);
        uint32_t dw = ow - nw;

        for (uint32_t row = 0; row < nh; row++)
            memcpy(image + (nw * 4 * row), pixels + (dw * 4 * row) + (nw * 4 * row), nw * 4);

        return image;
    }

    uint8_t* Compress(uint32_t w, uint32_t h, uint8_t* pixels, Framework::Graphics::TextureCompression method);

    struct InternalTexture {
        void*    m_data;
        uint32_t m_width;
        uint32_t m_height;

        [[nodiscard]] bool Ready() const { return m_data && m_width && m_height; }
    };
}

#endif //GAMEENGINE_TEXTUREHELPER_H
