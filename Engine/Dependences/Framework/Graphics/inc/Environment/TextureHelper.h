//
// Created by Nikita on 12.12.2020.
//

#ifndef GAMEENGINE_TEXTUREHELPER_H
#define GAMEENGINE_TEXTUREHELPER_H

#include <cstdint>
#include <utility>
#include <string>

namespace Framework::Graphics {
    enum class TextureFormat {
        Unknown      = 0,

        RGBA8_UNORM  = 10000,
        RGBA16_UNORM = 10001,

        RGBA8_SRGB   = 20000,
    };

    inline static bool IsSRGB(TextureFormat f) {
        return f >= TextureFormat::RGBA8_SRGB || f <= TextureFormat::RGBA8_SRGB;
    }

    inline static bool IsUNORM(TextureFormat f) {
        return f >= TextureFormat::RGBA8_UNORM || f <= TextureFormat::RGBA16_UNORM;
    }

    enum class TextureType {
        Unknown, Diffuse, Normal, Specular, Roughness, Glossiness
    };
    enum class TextureFilter {
        Unknown, NEAREST, LINEAR, NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR
    };
    enum class TextureCompression {
        None, BC1, BC2, BC3, BC4, BC5, BC6, BC7
    };

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
}

#endif //GAMEENGINE_TEXTUREHELPER_H
