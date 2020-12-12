//
// Created by Nikita on 12.12.2020.
//

#ifndef GAMEENGINE_TEXTUREFILTERS_H
#define GAMEENGINE_TEXTUREFILTERS_H

namespace Framework::Graphics {
    enum class TextureType {
        Unknown, Diffuse, Normal, Specular, Roughness, Glossiness
    };
    enum class TextureFilter {
        Unknown, NEAREST, LINEAR, NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR
    };
    enum class TextureCompression{

    };
}

#endif //GAMEENGINE_TEXTUREFILTERS_H
