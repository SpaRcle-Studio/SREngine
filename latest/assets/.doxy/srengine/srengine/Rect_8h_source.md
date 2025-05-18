

# File Rect.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Math**](dir_f20ff43999c2f98e3f122645c07885db.md) **>** [**Rect.h**](Rect_8h.md)

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
    template<typename T> struct Rect {
    public:
        union {
            struct {
                T x;
                T y;
                T w;
                T h;
            };
            struct {
                T left;
                T top;
                T right;
                T bottom;
            };
            struct {
                SR_MATH_NS::Vector2<T> xy;
                SR_MATH_NS::Vector2<T> wh;
            };
            struct {
                SR_MATH_NS::Vector2<T> position;
                SR_MATH_NS::Vector2<T> size;
            };
        };

    public:
        Rect(T _x, T _y, T _w, T _h);
        Rect(const Vector2<T>& position, const Vector2<T>& size);
        Rect(const Vector2<T>& position, T width, T height);
        Rect(T x, T y, const Vector2<T>& size);
        Rect();

    public:
        void Shrink(const Rect<T>& margin) noexcept;
        SR_NODISCARD Rect<T> Shrink(const Rect<T>& margin) const noexcept;

        SR_NODISCARD T X() const noexcept;
        SR_NODISCARD T Y() const noexcept;

        SR_NODISCARD T Width() const noexcept;
        SR_NODISCARD T Height() const noexcept;

        SR_NODISCARD T Left() const noexcept;
        SR_NODISCARD T Right() const noexcept;

        SR_NODISCARD T Bottom() const noexcept;
        SR_NODISCARD T Top() const noexcept;

        SR_NODISCARD T Horizontal() const noexcept;
        SR_NODISCARD T Vertical() const noexcept;

        SR_NODISCARD SR_MATH_NS::Vector2<T> XY() const noexcept;
        SR_NODISCARD SR_MATH_NS::Vector2<T> WH() const noexcept;

        SR_NODISCARD SR_MATH_NS::Vector2<T> TopBottom() const noexcept;
        SR_NODISCARD SR_MATH_NS::Vector2<T> LeftRight() const noexcept;

        SR_NODISCARD SR_MATH_NS::Vector3<T> XY0() const noexcept;
        SR_NODISCARD SR_MATH_NS::Vector3<T> WH0() const noexcept;
        SR_NODISCARD SR_MATH_NS::Vector3<T> WH1() const noexcept;

        template<typename U> SR_NODISCARD bool IsInside(const SR_MATH_NS::Vector2<U>& point) const noexcept;
        SR_NODISCARD bool operator==(const Rect& other) const noexcept;
        SR_NODISCARD bool operator!=(const Rect& other) const noexcept;
        SR_NODISCARD Rect operator+(const SR_MATH_NS::Rect<T>& other) const noexcept;
        SR_NODISCARD Rect operator-(const SR_MATH_NS::Rect<T>& other) const noexcept;
        SR_NODISCARD Rect operator*(const SR_MATH_NS::Rect<T>& other) const noexcept;
        SR_NODISCARD Rect operator/(const SR_MATH_NS::Rect<T>& other) const noexcept;
        void operator+=(const SR_MATH_NS::Rect<T>& other) noexcept;
        void operator-=(const SR_MATH_NS::Rect<T>& other) noexcept;
        void operator*=(const SR_MATH_NS::Rect<T>& other) noexcept;
        void operator/=(const SR_MATH_NS::Rect<T>& other) noexcept;

    public:
        SR_NODISCARD static Rect<Unit> FromTranslationAndScale(const SR_MATH_NS::FVector2& translation, const SR_MATH_NS::FVector2& scale);

        SR_NODISCARD bool Contains(const SR_MATH_NS::Vector2<T>& point) const noexcept;

    public:
        void SetLeft(const T& value);
        void SetBottom(const T& value);
        void SetRight(const T& value);
        void SetTop(const T& value);
    };


    template<typename T> void Rect<T>::SetLeft(const T& value) {
        w -= value - x;
        x = value;
    }

    template<typename T> void Rect<T>::SetBottom(const T& value) {
        h -= value - y;
        y = value;
    }

    template<typename T> void Rect<T>::SetRight(const T& value) {
        w = value - x;
    }

    template<typename T> void Rect<T>::SetTop(const T& value) {
        h = value - y;
    }

    template<typename T> void Rect<T>::Shrink(const Rect<T>& margin) noexcept {
        x += margin.x;
        y += margin.y;
        w -= margin.x + margin.w;
        h -= margin.y + margin.h;
    }

    template<typename T> Rect<T> Rect<T>::Shrink(const Rect<T>& margin) const noexcept {
        return Rect<T>(x + margin.x, y + margin.y, w - margin.x - margin.w, h - margin.y - margin.h);
    }

    template<typename T> bool Rect<T>::Contains(const Vector2<T> &point) const noexcept {
        return point.x >= Left() && point.x <= Right() && point.y <= Top() && point.y >= Bottom();
    }

    template<typename T> Rect<T>::Rect(T _x, T _y, T _w, T _h)
        : x(_x)
        , y(_y)
        , w(_w)
        , h(_h)
    { }

    template<typename T> Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size)
        : x(position.x)
        , y(position.y)
        , w(size.x)
        , h(size.y)
    { }

    template<typename T> Rect<T>::Rect(const Vector2<T>& position, T width, T height)
        : x(position.x)
        , y(position.y)
        , w(width)
        , h(height)
    { }

    template<typename T> Rect<T>::Rect(T x, T y, const Vector2<T>& size)
        : x(x)
        , y(y)
        , w(size.x)
        , h(size.y)
    { }

    template<typename T> Rect<T>::Rect()
        : Rect(T(), T(), T(), T())
    { }

    template<typename T> SR_NODISCARD T Rect<T>::X() const noexcept { return x; }
    template<typename T> SR_NODISCARD T Rect<T>::Y() const noexcept { return y; }

    template<typename T> SR_NODISCARD T Rect<T>::Width() const noexcept { return w; }
    template<typename T> SR_NODISCARD T Rect<T>::Height() const noexcept { return h; }

    template<typename T> SR_NODISCARD T Rect<T>::Left() const noexcept { return x; }
    template<typename T> SR_NODISCARD T Rect<T>::Right() const noexcept { return Left() + Width(); }

    template<typename T> SR_NODISCARD T Rect<T>::Bottom() const noexcept { return y;  }
    template<typename T> SR_NODISCARD T Rect<T>::Top() const noexcept { return Bottom() + Height(); }

    template<typename T> SR_NODISCARD T Rect<T>::Vertical() const noexcept { return top + bottom; }
    template<typename T> SR_NODISCARD T Rect<T>::Horizontal() const noexcept { return left + right; }

    template<typename T> SR_NODISCARD SR_MATH_NS::Vector2<T> Rect<T>::TopBottom() const noexcept { return SR_MATH_NS::Vector2<T>(Top(), Bottom()); }
    template<typename T> SR_NODISCARD SR_MATH_NS::Vector2<T> Rect<T>::LeftRight() const noexcept { return SR_MATH_NS::Vector2<T>(Left(), Right()); }

    template<typename T> SR_NODISCARD SR_MATH_NS::Vector2<T> Rect<T>::XY() const noexcept { return SR_MATH_NS::Vector2<T>(x, y); }
    template<typename T> SR_NODISCARD SR_MATH_NS::Vector2<T> Rect<T>::WH() const noexcept { return SR_MATH_NS::Vector2<T>(w, h); }

    template<typename T> SR_NODISCARD SR_MATH_NS::Vector3<T> Rect<T>::XY0() const noexcept { return SR_MATH_NS::Vector3<T>(x, y, 0); }
    template<typename T> SR_NODISCARD SR_MATH_NS::Vector3<T> Rect<T>::WH0() const noexcept { return SR_MATH_NS::Vector3<T>(w, h, 0); }
    template<typename T> SR_NODISCARD SR_MATH_NS::Vector3<T> Rect<T>::WH1() const noexcept { return SR_MATH_NS::Vector3<T>(w, h, 1); }

    template<typename T> template<typename U> SR_NODISCARD bool Rect<T>::IsInside(const SR_MATH_NS::Vector2<U>& point) const noexcept {
        return point.x >= static_cast<U>(x) && point.x <= static_cast<U>(x + w) &&
               point.y >= static_cast<U>(y) && point.y <= static_cast<U>(y + h);
    }

    template<typename T> SR_NODISCARD bool Rect<T>::operator==(const Rect& other) const noexcept {
        return SR_MATH_NS::IsEquals(x, other.x) && SR_MATH_NS::IsEquals(y, other.y) &&
               SR_MATH_NS::IsEquals(w, other.w) && SR_MATH_NS::IsEquals(h, other.h);
    }

    template<typename T> SR_NODISCARD bool Rect<T>::operator!=(const Rect& other) const noexcept {
        return !(*this == other);
    }

    template<typename T> SR_NODISCARD Rect<T> Rect<T>::operator+(const SR_MATH_NS::Rect<T>& other) const noexcept {
        return Rect(x + other.x, y + other.y, w + other.w, h + other.h);
    }

    template<typename T> SR_NODISCARD Rect<T> Rect<T>::operator-(const SR_MATH_NS::Rect<T>& other) const noexcept {
        return Rect(x - other.x, y - other.y, w - other.w, h - other.h);
    }

    template<typename T> SR_NODISCARD Rect<T> Rect<T>::operator*(const SR_MATH_NS::Rect<T>& other) const noexcept {
        return Rect(x * other.x, y * other.y, w * other.w, h * other.h);
    }

    template<typename T> SR_NODISCARD Rect<T> Rect<T>::operator/(const SR_MATH_NS::Rect<T>& other) const noexcept {
        return Rect(x / other.x, y / other.y, w / other.w, h / other.h);
    }

    template<typename T> void Rect<T>::operator+=(const SR_MATH_NS::Rect<T>& other) noexcept {
        x += other.x;
        y += other.y;
        w += other.w;
        h += other.h;
    }

    template<typename T> void Rect<T>::operator-=(const SR_MATH_NS::Rect<T>& other) noexcept {
        x -= other.x;
        y -= other.y;
        w -= other.w;
        h -= other.h;
    }

    template<typename T> void Rect<T>::operator*=(const SR_MATH_NS::Rect<T>& other) noexcept {
        x *= other.x;
        y *= other.y;
        w *= other.w;
        h *= other.h;
    }

    template<typename T> void Rect<T>::operator/=(const SR_MATH_NS::Rect<T>& other) noexcept {
        x /= other.x;
        y /= other.y;
        w /= other.w;
        h /= other.h;
    }

    template<typename T> Rect<Unit> Rect<T>::FromTranslationAndScale(const FVector2& translation, const FVector2& scale) {
        return Rect<Unit>(translation.x, translation.y, scale.x * 2, scale.y * 2);
    }

    typedef Rect<Unit> FRect;
    typedef Rect<int32_t> IRect;
    typedef Rect<uint32_t> URect;
}

#endif //SR_ENGINE_RECT_H
```


