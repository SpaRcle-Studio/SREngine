//
// Created by Nikita on 27.06.2021.
//

#ifndef GAMEENGINE_TEXTURECOMPRESSOR_H
#define GAMEENGINE_TEXTURECOMPRESSOR_H

#include <cstdint>

#include <Environment/TextureEnums.h>

namespace Framework::Graphics {
    class TextureCompressor {
    public:
        TextureCompressor() = delete;
        ~TextureCompressor() = delete;
        TextureCompressor(const TextureCompressor &) = delete;
    public:
        static uint8_t *Compress(uint8_t* pixels, uint32_t width, uint32_t height, TextureCompression compression);
    };
}

#endif //GAMEENGINE_TEXTURECOMPRESSOR_H
