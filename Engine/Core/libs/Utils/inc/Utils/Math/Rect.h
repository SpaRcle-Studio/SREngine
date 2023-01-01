//
// Created by Monika on 18.11.2022.
//

#ifndef SRENGINE_RECT_H
#define SRENGINE_RECT_H

#include <Utils/Math/Mathematics.h>
#include <Utils/Math/Vector2.h>

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

    typedef Rect<Unit> FRect;
    typedef Rect<int32_t> IRect;
    typedef Rect<uint32_t> URect;
}

#endif //SRENGINE_RECT_H
