//
// Created by Nikita on 12.12.2020.
//

#ifndef GAMEENGINE_TEXTUREENUMS_H
#define GAMEENGINE_TEXTUREENUMS_H

namespace Framework::Graphics {
    enum class TextureFormat {
        Unknown      = 0,

        RGBA8_UNORM  = 10000,
        RGBA16_UNORM = 10001,

        RGBA8_SRGB   = 20000,
    };

    static bool IsSRGB(TextureFormat f) {
        return f >= TextureFormat::RGBA8_SRGB || f <= TextureFormat::RGBA8_SRGB;
    }

    static bool IsUNORM(TextureFormat f) {
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
}

#endif //GAMEENGINE_TEXTUREENUMS_H
