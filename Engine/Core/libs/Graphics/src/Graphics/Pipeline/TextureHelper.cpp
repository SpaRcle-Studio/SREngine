//
// Created by Nikita on 28.06.2021.
//

#include <Graphics/Pipeline/TextureHelper.h>
#include <Utils/Debug.h>

#include <cmp_core.h>

namespace SR_GRAPH_NS {
    uint8_t* Compress(uint32_t w, uint32_t h, uint8_t *pixels, TextureCompression method) {
        uint32_t blockCount = (w / 4) * (h / 4);
        auto* cmpBuffer = (uint8_t*)malloc(16 * blockCount * 4);
        for (uint32_t col = 0; col < w / 4; col++) {
            for (uint32_t row = 0; row < h / 4; row++) {
                uint32_t colOffs = col * 16;
                uint32_t rowOffs = row * w;

                switch (method) {
                    case TextureCompression::None:
                        return nullptr;
                    case TextureCompression::BC1:
                    case TextureCompression::BC4:
                        //! BC1, BC4 - has 8-byte cmp buffer
                        CompressBlockBC1(
                                pixels + colOffs + rowOffs * 16,            // source
                                4 * w,                                      // count bytes
                                cmpBuffer + colOffs / 2 + (rowOffs * 4) / 2 // dst
                        );
                        break;
                    case TextureCompression::BC2:
                    case TextureCompression::BC3:
                    case TextureCompression::BC5:
                    case TextureCompression::BC6:
                    case TextureCompression::BC7:
                        //! other BC has 16-byte cmp buffer
                        CompressBlockBC7(
                                pixels + colOffs + rowOffs * 16,    // source
                                4 * w,                              // count bytes
                                cmpBuffer + colOffs+ (rowOffs * 4)  // dst
                        );
                        break;
                    default:
                        break;
                }
            }
        }

        return cmpBuffer;
    }

    uint32_t GetPixelSize(ImageFormat format) {
        switch (format) {
            case ImageFormat::RGBA8_UNORM:
            case ImageFormat::BGRA8_UNORM:
            case ImageFormat::RGBA8_SRGB:
                return 4 * 1;
            case ImageFormat::RGBA16_UNORM:
            case ImageFormat::RGBA16_SFLOAT:
                return 4 * 2;
            case ImageFormat::RGB8_UNORM:
            case ImageFormat::RGB8_SRGB:
                return 3 * 1;
            case ImageFormat::RGB16_UNORM:
                return 3 * 2;
            default:
                break;
        }

        SRHalt("Unknown format!");

        return 0;
    }
}
