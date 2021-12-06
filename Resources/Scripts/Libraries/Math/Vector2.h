//
// Created by Nikita on 12.07.2021.
//

#ifndef EVOSCRIPTLIB_VECTOR2_H
#define EVOSCRIPTLIB_VECTOR2_H

#include "Math.h"

enum Axis {
    NONE = 0,
    AXIS_X = 1,
    AXIS_Y = 2,
    AXIS_Z = 3,
};

template<typename T> struct Vector2 {
public:
    union {
        struct {
            T x;
            T y;
        };

        T coord[2] = { 0 };
    };

    [[nodiscard]] T Distance(const Vector2 &vec) const noexcept {
        return static_cast<T>(sqrt(pow(vec.x - x, 2) + pow(vec.y - y, 2)));
    }

    template<typename U> _FORCE_INLINE_ Vector2 operator*(const U &scalar) const noexcept {
        return Vector2(x * scalar, y * scalar);
    }

    template<typename U> _FORCE_INLINE_ Vector2 operator+(const Vector2<U> &p_v) const {
        return Vector2(x + p_v.x, y + p_v.y);
    }

    template<typename U> _FORCE_INLINE_ Vector2 operator-(const Vector2<U> &p_v) const {
        return Vector2(x - p_v.x, y - p_v.y);
    }

    template<typename U> _FORCE_INLINE_ Vector2 operator*=(const U& value) {
        this->x *= value;
        this->y *= value;
        return *this;
    }

    template<typename U> _FORCE_INLINE_ bool operator==(const Vector2<U> &p_v) const {
        return x == p_v.x && y == p_v.y;
    }

    template<typename U> _FORCE_INLINE_ bool operator!=(const Vector2<U> &p_v) const {
        return x != p_v.x || y != p_v.y;
    }

    template<typename U> _FORCE_INLINE_ Vector2 operator*(const Vector2<U> &p_v) const {
        return Vector2(x * p_v.x, y * p_v.y);
    }

    template<typename U> _FORCE_INLINE_ Vector2 operator/(const Vector2<U> &p_v) const {
        return Vector2(x / p_v.x, y / p_v.y);
    }

    template<typename U> _FORCE_INLINE_ Vector2 &operator/=(U p_scalar) {
        x /= p_scalar;
        y /= p_scalar;
        return *this;
    }

    template<typename U> _FORCE_INLINE_ Vector2 &operator+=(Vector2<U> v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    _FORCE_INLINE_ Vector2() {
        x = 0;
        y = 0;
    }

    _FORCE_INLINE_ const T &operator[](int p_axis) const {
        return coord[p_axis];
    }

    _FORCE_INLINE_ T &operator[](int p_axis) {
        return coord[p_axis];
    }

    _FORCE_INLINE_ Vector2(T p_x, T p_y) {
        x = p_x;
        y = p_y;
    }
};

typedef Vector2<Unit> FVector2;
typedef Vector2<int32_t> IVector2;
typedef Vector2<uint32_t> UVector2;

#endif //EVOSCRIPTLIB_VECTOR2_H
