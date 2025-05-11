

# File CSSColor.h

[**File List**](files.md) **>** [**CSS**](dir_8392c415e30628e2ce7c2879273a6118.md) **>** [**CSSColor.h**](CSSColor_8h.md)

[Go to the documentation of this file](CSSColor_8h.md)


```C++
//
// Created by Monika on 20.08.2024.
//

#ifndef SR_COMMON_WEB_CSS_COLOR_H
#define SR_COMMON_WEB_CSS_COLOR_H

#include <Utils/Web/CSS/CSSSizeValue.h>

namespace SR_UTILS_NS::Web {
    enum class CSSGradientSide : uint8_t {
        ClosestSide, ClosestCorner, FarthestSide, FarthestCorner,
    };

    struct CSSDirection {
        enum class DirectionType : uint8_t {
            To, Degree,
        } type = DirectionType::To;

        enum class Type : uint8_t {
            Top,
            Right,
            Bottom,
            Left,
            TopRight,
            BottomRight,
            BottomLeft,
            TopLeft,
        };

        union {
            Type direction = Type::Bottom;
            float_t degree;
        };
    };

    struct CSSRGBAColor {
        uint8_t r = 0, g = 0, b = 0, a = 0;

        SR_NODISCARD static CSSRGBAColor Parse(std::string_view data);

        SR_NODISCARD SR_MATH_NS::FColor ToFColor() const {
            return SR_MATH_NS::FColor(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
        }

        SR_NODISCARD std::string ToString() const {
            return SR_FORMAT("RGBA({}, {}, {}, {})", r, g, b, a);
        }
    };

    struct CSSGradientColor {
        CSSRGBAColor color;
        CSSOptionalSizeValue size;
    };


    struct CSSLinearGradient {
        SR_NODISCARD static CSSLinearGradient Parse(std::string_view data);

        SR_NODISCARD std::string ToString() const;

        CSSDirection direction;
        std::vector<CSSGradientColor> colors;
    };

    struct CSSRadialGradient {
        SR_NODISCARD static CSSRadialGradient Parse(std::string_view data);

        SR_NODISCARD std::string ToString() const;

        CSSSizeValue at;
        std::vector<CSSGradientColor> colors;

        enum class Shape : uint8_t {
            Circle, Ellipse,
        } shape = Shape::Circle;

        CSSGradientSide side = CSSGradientSide::ClosestSide;
    };


    struct CSSColor {
        static SR_NODISCARD CSSColor Parse(std::string_view data);

        SR_NODISCARD std::string ToString() const {
            std::string result;
            if (colorType == ColorType::RGBA) {
                result += color.ToString();
            } else if (colorType == ColorType::LinearGradient) {
                result += linearGradient.ToString();
            } else if (colorType == ColorType::RadialGradient) {
                result += radialGradient.ToString();
            }
            return result;
        }

        enum class ColorType : uint8_t {
            RGBA, LinearGradient, RadialGradient,
        } colorType = ColorType::RGBA;

        CSSRGBAColor color;
        CSSLinearGradient linearGradient;
        CSSRadialGradient radialGradient;
    };

    SR_INLINE_STATIC const CSSColor DEFAULT_CSS_COLOR = CSSColor();
}

#endif //SR_COMMON_WEB_CSS_COLOR_H
```


