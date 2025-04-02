

# File TextureHelper.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pipeline**](dir_5b8a811d805f0a9bb3b25de386a42645.md) **>** [**TextureHelper.h**](TextureHelper_8h.md)

[Go to the documentation of this file](TextureHelper_8h.md)


```C++
//
// Created by Nikita on 12.12.2020.
//

#ifndef SR_ENGINE_TEXTUREHELPER_H
#define SR_ENGINE_TEXTUREHELPER_H

#include <Utils/Common/Enumerations.h>
#include <Utils/Resources/Xml.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(SSBOUsage, uint8_t,
        Unknown,
        Read, Write, ReadWrite
    );

    SR_ENUM_NS_CLASS_T(ImageLoadFormat, uint8_t,
        Unknown,
        Grey,
        GreyAlpha,
        RGB,
        RGBA
    );

    /*SR_ENUM_NS_CLASS_T(Dimension, uint8_t,
        Unknown,
        DIMENSION_2D,
        DIMENSION_3D,
        DIMENSION_CUBE
    );*/

    SR_ENUM_NS_CLASS_T(Antialiasing, uint8_t,
        None,
        Samples2,
        Samples4,
        Samples8,
        Samples16,
        Samples32
    );

    SR_ENUM_NS_CLASS(ImageAspect,
        None, Depth, Stencil, Color, DepthStencil
    );

    SR_ENUM_NS_CLASS(ImageFormat,
        Unknown,
        None,
        Auto,

        RGBA8_UNORM,
        BGRA8_UNORM,
        RGBA16_UNORM,
        RGBA16_SFLOAT,

        RGB8_UNORM,
        RGB8_SRGB,
        RGB16_UNORM,

        RGBA8_SRGB,

        R8_UNORM,
        R16_UNORM,

        R32_SFLOAT,
        R64_SFLOAT,

        R8_UINT,
        R16_UINT,
        R32_UINT,
        R64_UINT,

        RG8_UNORM,

        D16_UNORM,
        D24_UNORM_S8_UINT,
        D32_SFLOAT,
        D32_SFLOAT_S8_UINT
    );

    SR_INLINE static uint8_t GetChannelCount(ImageFormat format) {
        switch (format) {
            case ImageFormat::RGBA8_UNORM:
            case ImageFormat::BGRA8_UNORM:
            case ImageFormat::RGBA8_SRGB:
                return 4;
            case ImageFormat::R8_UNORM:
            case ImageFormat::R8_UINT:
                return 1;
            case ImageFormat::RG8_UNORM:
                return 2;
            case ImageFormat::RGB8_UNORM:
                return 3;
            case ImageFormat::RGBA16_UNORM:
            case ImageFormat::RGB16_UNORM:
            case ImageFormat::R16_UNORM:
            case ImageFormat::R32_SFLOAT:
            case ImageFormat::R64_SFLOAT:
            case ImageFormat::R16_UINT:
            case ImageFormat::R32_UINT:
            case ImageFormat::R64_UINT:
                SR_ERROR("GetChannelCount : unsupported color format!\n\tImageFormat: " + SR_UTILS_NS::EnumReflector::ToStringAtom(format).ToStringRef());
                return 0;
            case ImageFormat::Unknown:
            default:
                SR_ERROR("GetChannelCount : unknown color format!\n\tImageFormat: " + SR_UTILS_NS::EnumReflector::ToStringAtom(format).ToStringRef());
                return 0;
        }
    }

    struct ColorLayer {
        int32_t texture = SR_ID_INVALID;
        ImageFormat format = ImageFormat::Unknown;
    };

    struct DepthLayer {
        int32_t texture = SR_ID_INVALID;
        ImageFormat format = ImageFormat::Unknown;
        ImageAspect aspect = ImageAspect::DepthStencil;
        std::vector<int32_t> subLayers;
    };

    //inline static bool IsSRGB(ColorFormat f) {
    //    return f == ColorFormat::RGBA8_SRGB;
    //}

    //inline static bool IsUNORM(ColorFormat f) {
    //    return f >= ColorFormat::RGBA8_UNORM || f <= ColorFormat::RGBA16_UNORM;
    //}

    SR_ENUM_NS_CLASS(TextureFilter,
        Unknown = 0, NEAREST = 1, LINEAR = 2, NEAREST_MIPMAP_NEAREST = 3,
        LINEAR_MIPMAP_NEAREST = 4, NEAREST_MIPMAP_LINEAR = 5, LINEAR_MIPMAP_LINEAR = 6
    );

    SR_ENUM_NS_CLASS(TextureCompression,
        None = 0, BC1 = 1, BC2 = 2, BC3 = 3, BC4 = 4, BC5 = 5, BC6 = 6, BC7 = 7
    );

    SR_INLINE static uint32_t Find4(uint32_t i) {
        if (i % 4 == 0)
            return i;
        else
            return Find4(i - 1);
    }

    SR_INLINE static auto MakeGoodSizes(uint32_t w, uint32_t h) -> auto {
        return std::pair(Find4(w), Find4(h));
    }

    SR_INLINE static uint8_t* ResizeToLess(uint32_t ow, uint32_t oh, uint32_t nw, uint32_t nh, const uint8_t* pixels) {
        auto* image = (uint8_t*)malloc(nw * nh * 4);
        uint32_t dw = ow - nw;

        for (uint32_t row = 0; row < nh; ++row) {
            memcpy(image + (nw * 4 * row), pixels + (dw * 4 * row) + (nw * 4 * row), nw * 4);
        }

        return image;
    }

    uint32_t GetPixelSize(ImageFormat format);

    uint8_t* Compress(uint32_t w, uint32_t h, uint8_t* pixels, SR_GRAPH_NS::TextureCompression method);
}

#endif //SR_ENGINE_TEXTUREHELPER_H
```


