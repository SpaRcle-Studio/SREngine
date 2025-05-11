

# File Size.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Math**](dir_f20ff43999c2f98e3f122645c07885db.md) **>** [**Size.h**](Size_8h.md)

[Go to the documentation of this file](Size_8h.md)


```C++
//
// Created by Monika on 19.01.2025.
//

#ifndef SR_ENGINE_UTILS_MATH_SIZE_H
#define SR_ENGINE_UTILS_MATH_SIZE_H

#include <Utils/Math/Vector2.h>
#include <Utils/Common/Enumerations.h>

namespace SR_MATH_NS {
    SR_ENUM_NS_CLASS_T(SizeMetric, uint8_t,
        Px, Percent
    );

    template<typename T> struct Size {
        Size() noexcept
            : value(T())
        { }


        Size(T value, SizeMetric metric) noexcept
            : value(value)
            , metric(metric)
        { }

        union {
            struct {
                T value;
            };
            struct {
                T v;
            };
        };

        SizeMetric metric = SizeMetric::Px;

        SR_NODISCARD bool IsPixel() const noexcept { return metric == SizeMetric::Px; }
        SR_NODISCARD bool IsPercent() const noexcept { return metric == SizeMetric::Percent; }

        SR_NODISCARD T ToPixels() const noexcept { return v; }
        SR_NODISCARD T ToPixels(const T& parentSize) const noexcept {
            if (IsPixel()) {
                return v;
            }
            return (v / 100.f) * parentSize;
        }
    };

    template<typename T> struct Size2 {
        Size2() noexcept
            : width(Size<T>())
            , height(Size<T>())
        { }

        union {
            struct {
                Size<T> width;
                Size<T> height;
            };
            struct {
                Size<T> w;
                Size<T> h;
            };
        };

        SR_NODISCARD bool HasPercent() const noexcept { return width.IsPercent() || height.IsPercent(); }

        SR_NODISCARD Vector2<T> ToPixels() const noexcept {
            return SR_MATH_NS::Vector2<T>(width.ToPixels(), height.ToPixels());
        }

        SR_NODISCARD Vector2<T> ToPixels(const Vector2<T>& parentSize) const noexcept {
            return SR_MATH_NS::Vector2<T>(width.ToPixels(parentSize.x), height.ToPixels(parentSize.y));
        }

        void SetPixels(const Vector2<T>& size) noexcept {
            width.v = size.x;
            height.v = size.y;
            width.metric = SizeMetric::Px;
            height.metric = SizeMetric::Px;
        }
    };

    using FSize = Size<float_t>;
    using ISize = Size<int32_t>;
    using USize = Size<uint32_t>;

    using FSize2 = Size2<float_t>;
    using ISize2 = Size2<int32_t>;
    using USize2 = Size2<uint32_t>;
}

#endif //SR_ENGINE_UTILS_MATH_SIZE_H
```


