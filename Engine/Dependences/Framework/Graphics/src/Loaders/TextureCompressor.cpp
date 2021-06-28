//
// Created by Nikita on 27.06.2021.
//

#include "Loaders/TextureCompressor.h"
#include <cmp_core.h>
#include <malloc.h>

uint8_t *Framework::Graphics::TextureCompressor::Compress(
    uint8_t *pixels,
    uint32_t width,
    uint32_t height,
    Framework::Graphics::TextureCompression compression)
{
    uint32_t blockCount = (width / 4) * (height / 4);
    auto* cmpBuffer = (uint8_t*)malloc(16 * blockCount * 4);
    for (uint32_t col = 0; col < width / 4; col++) {
        for (uint32_t row = 0; row < height / 4; row++) {
            uint32_t pixelOffset = col * 16 + row * 16 * width;
            switch (compression) {
                case TextureCompression::BC1:
                    CompressBlockBC1(pixels + pixelOffset, 4 * width, cmpBuffer + (col * 16) + (row * width * 4));
                    break;
                case TextureCompression::BC2:
                    CompressBlockBC2(pixels + pixelOffset, 4 * width, cmpBuffer + (col * 16) + (row * width * 4));
                    break;
                case TextureCompression::BC3:
                    CompressBlockBC3(pixels + pixelOffset, 4 * width, cmpBuffer + (col * 16) + (row * width * 4));
                    break;
                case TextureCompression::BC4:
                    CompressBlockBC4(pixels + pixelOffset, 4 * width, cmpBuffer + (col * 16) + (row * width * 4));
                    break;
                case TextureCompression::BC5:
                    //CompressBlockBC5(pixels + col * 16 + row * 16 * width, 4 * width, cmpBuffer + (col * 16) + (row * width * 4));
                    break;
                case TextureCompression::BC6:
                    //CompressBlockBC6(pixels + col * 16 + row * 16 * width, 4 * width, cmpBuffer + (col * 16) + (row * width * 4));
                    break;
                case TextureCompression::BC7:
                    CompressBlockBC7(pixels + pixelOffset, 4 * width, cmpBuffer + (col * 16) + (row * width * 4));
                    break;
                default:
                    break;
            }
        }
    }

    return cmpBuffer;
}
