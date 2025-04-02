

# File Rect.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Math**](dir_3900fe4b4d95d895210b9082ab5cdd34.md) **>** [**Rect.h**](Rect_8h.md)

[Go to the documentation of this file](Rect_8h.md)


```C++
//
// Created by Monika on 18.11.2022.
//

#ifndef SR_ENGINE_RECT_H
#define SR_ENGINE_RECT_H

#include <Utils/Math/Mathematics.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>

namespace SR_MATH_NS {
    template<typename T> struct SR_DLL_EXPORT Rect {
    public:
        union {
            struct {
                T x;
                T y;
                T w;
                T h;
            };
            struct {
                SR_MATH_NS::Vector2<T> xy;
                SR_MATH_NS::Vector2<T> wh;
            };
        };

    public:
        constexpr Rect(T _x, T _y, T _w, T _h)
            : x(_x)
            , y(_y)
            , w(_w)
            , h(_h)
        { }

        constexpr Rect(const Vector2<T>& position, const Vector2<T>& size)
            : x(position.x)
            , y(position.y)
            , w(size.x)
            , h(size.y)
        { }

        constexpr Rect(const Vector2<T>& position, T width, T height)
            : x(position.x)
            , y(position.y)
            , w(width)
            , h(height)
        { }

        constexpr Rect(T x, T y, const Vector2<T>& size)
            : x(x)
            , y(y)
            , w(size.x)
            , h(size.y)
        { }

        constexpr Rect()
            : Rect(T(), T(), T(), T())
        { }

    public:
        SR_NODISCARD constexpr T X() const noexcept { return x; }
        SR_NODISCARD constexpr T Y() const noexcept { return y; }

        SR_NODISCARD constexpr T Width() const noexcept { return w; }
        SR_NODISCARD constexpr T Height() const noexcept { return h; }

        SR_NODISCARD constexpr T Left() const noexcept { return x; }
        SR_NODISCARD constexpr T Right() const noexcept { return Left() + Width(); }

        SR_NODISCARD constexpr T Bottom() const noexcept { return y;  }
        SR_NODISCARD constexpr T Top() const noexcept { return Bottom() + Height(); }

        SR_NODISCARD constexpr SR_MATH_NS::Vector2<T> XY() const noexcept { return SR_MATH_NS::Vector2<T>(x, y); }
        SR_NODISCARD constexpr SR_MATH_NS::Vector2<T> WH() const noexcept { return SR_MATH_NS::Vector2<T>(w, h); }

        SR_NODISCARD constexpr SR_MATH_NS::Vector3<T> XY0() const noexcept { return SR_MATH_NS::Vector3<T>(x, y, 0); }
        SR_NODISCARD constexpr SR_MATH_NS::Vector3<T> WH0() const noexcept { return SR_MATH_NS::Vector3<T>(w, h, 0); }
        SR_NODISCARD constexpr SR_MATH_NS::Vector3<T> WH1() const noexcept { return SR_MATH_NS::Vector3<T>(w, h, 1); }

        template<typename U> SR_NODISCARD constexpr bool IsInside(const SR_MATH_NS::Vector2<U>& point) const noexcept {
            return point.x >= static_cast<U>(x) && point.x <= static_cast<U>(x + w) &&
                   point.y >= static_cast<U>(y) && point.y <= static_cast<U>(y + h);
        }

        SR_NODISCARD bool operator==(const Rect& other) const noexcept {
            return SR_MATH_NS::IsEquals(x, other.x) && SR_MATH_NS::IsEquals(y, other.y) &&
                   SR_MATH_NS::IsEquals(w, other.w) && SR_MATH_NS::IsEquals(h, other.h);
        }

        SR_NODISCARD bool operator!=(const Rect& other) const noexcept {
            return !(*this == other);
        }

        SR_NODISCARD Rect operator+(const SR_MATH_NS::Rect<T>& other) const noexcept {
            return Rect(x + other.x, y + other.y, w + other.w, h + other.h);
        }

        SR_NODISCARD Rect operator-(const SR_MATH_NS::Rect<T>& other) const noexcept {
            return Rect(x - other.x, y - other.y, w - other.w, h - other.h);
        }

        SR_NODISCARD Rect operator*(const SR_MATH_NS::Rect<T>& other) const noexcept {
            return Rect(x * other.x, y * other.y, w * other.w, h * other.h);
        }

        SR_NODISCARD Rect operator/(const SR_MATH_NS::Rect<T>& other) const noexcept {
            return Rect(x / other.x, y / other.y, w / other.w, h / other.h);
        }

        void operator+=(const SR_MATH_NS::Rect<T>& other) noexcept {
            x += other.x;
            y += other.y;
            w += other.w;
            h += other.h;
        }

        void operator-=(const SR_MATH_NS::Rect<T>& other) noexcept {
            x -= other.x;
            y -= other.y;
            w -= other.w;
            h -= other.h;
        }

        void operator*=(const SR_MATH_NS::Rect<T>& other) noexcept {
            x *= other.x;
            y *= other.y;
            w *= other.w;
            h *= other.h;
        }

        void operator/=(const SR_MATH_NS::Rect<T>& other) noexcept {
            x /= other.x;
            y /= other.y;
            w /= other.w;
            h /= other.h;
        }

    public:
        SR_NODISCARD static Rect<Unit> FromTranslationAndScale(const SR_MATH_NS::FVector2& translation, const SR_MATH_NS::FVector2& scale);

        SR_NODISCARD bool Contains(const SR_MATH_NS::Vector2<T>& point) const noexcept {
            return point.x >= Left() && point.x <= Right() && point.y <= Top() && point.y >= Bottom();
        }


    public:
        constexpr void SetLeft(const T& value) {
            w -= value - x;
            x = value;
        }

        constexpr void SetBottom(const T& value) {
            h -= value - y;
            y = value;
        }

        constexpr void SetRight(const T& value) {
            w = value - x;
        }

        constexpr void SetTop(const T& value) {
            h = value - y;
        }
    };

    template<typename T> Rect<Unit> Rect<T>::FromTranslationAndScale(const FVector2& translation, const FVector2& scale) {
        return Rect<Unit>(translation.x, translation.y, scale.x * 2, scale.y * 2);
    }

    typedef Rect<Unit> FRect;
    typedef Rect<int32_t> IRect;
    typedef Rect<uint32_t> URect;
}

#endif //SR_ENGINE_RECT_H
```


