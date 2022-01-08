//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_VECTOR2_H
#define GAMEENGINE_VECTOR2_H

#include <string>
#include "Mathematics.h"
#include <glm/glm.hpp>

namespace Framework::Helper::Math {
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

        _FORCE_INLINE_ Vector2() {
            x = 0;
            y = 0;
        }

        _FORCE_INLINE_ Vector2(T p_x, T p_y) {
            x = p_x;
            y = p_y;
        }

        _FORCE_INLINE_ Vector2(T p) {
            x = p;
            y = p;
        }

        _FORCE_INLINE_ Vector2(const glm::vec2 &vec2) {
            x = static_cast<T>(vec2.x);
            y = static_cast<T>(vec2.y);
        }

        template<typename U> [[nodiscard]] Vector2<U> Cast() const { return Vector2<U>(
                    static_cast<U>(x),
                    static_cast<U>(y)
            );
        }

        [[nodiscard]] Vector2 Singular(const Vector2& segment) const { return Vector2(
                    x > 0 ? x + segment.x : x - segment.x,
                    y > 0 ? y + segment.y : y - segment.y
            );
        }
        [[nodiscard]] Vector2 DeSingular(const Vector2& segment) const { return Vector2(
                    x > 0 ? x - segment.x : x,
                    y > 0 ? y - segment.y : y
            );
        }

        [[nodiscard]] T Distance(const Vector2 &vec) const noexcept {
            return static_cast<T>(sqrt(pow(vec.x - x, 2) + pow(vec.y - y, 2)));
        }

        [[nodiscard]] Vector2 Abs() const {
            return Vector2(static_cast<T>(abs(x)), static_cast<T>(abs(y)));
        }

        _FORCE_INLINE_ Vector2 operator-() const { return Vector2(-x, -y); }
        _FORCE_INLINE_ Vector2 operator+() const { return *this; }

        _FORCE_INLINE_ bool operator<=(const Vector2 &p_v) const { return x <= p_v.x && y <= p_v.y; }
        _FORCE_INLINE_ bool operator>=(const Vector2 &p_v) const { return x >= p_v.x && y >= p_v.y; }
        _FORCE_INLINE_ bool operator<(const Vector2 &p_v) const { return x < p_v.x && y < p_v.y; }
        _FORCE_INLINE_ bool operator>(const Vector2 &p_v) const { return x > p_v.x && y > p_v.y; }

        _FORCE_INLINE_ bool operator>(T p_scalar) const { return *this > Vector2<T>(p_scalar); }
        _FORCE_INLINE_ bool operator<(T p_scalar) const { return *this < Vector2<T>(p_scalar); }
        _FORCE_INLINE_ bool operator>=(T p_scalar) const { return *this >= Vector2<T>(p_scalar); }
        _FORCE_INLINE_ bool operator<=(T p_scalar) const { return *this <= Vector2<T>(p_scalar); }
        _FORCE_INLINE_ bool operator==(T p_scalar) const { return *this == Vector2<T>(p_scalar); }
        _FORCE_INLINE_ bool operator!=(T p_scalar) const { return *this != Vector2<T>(p_scalar); }

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

        template<typename U> _FORCE_INLINE_ Vector2 operator/(const U &v) const {
            return Vector2(x / v, y / v);
        }

        template<typename U> _FORCE_INLINE_ Vector2 &operator/=(U p_scalar) {
            x /= p_scalar;
            y /= p_scalar;
            return *this;
        }

        template<typename U> _FORCE_INLINE_ Vector2 &operator-=(const Vector2<U> &p_v) {
            x -= p_v.x;
            y -= p_v.y;
            return *this;
        }

        template<typename U> _FORCE_INLINE_ Vector2 &operator+=(Vector2<U> v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        [[nodiscard]] _FORCE_INLINE_ bool Empty() const {
            return x == 0 && y == 0;
        }

        [[nodiscard]] bool HasZero() const {
            return (x == 0 || y == 0);
        }

        [[nodiscard]] _FORCE_INLINE_ glm::vec2 ToGLM() const noexcept {
            return { static_cast<float_t>(x), static_cast<float_t>(y) };
        }

        _FORCE_INLINE_ const T &operator[](int p_axis) const {
            return coord[p_axis];
        }

        _FORCE_INLINE_ T &operator[](int p_axis) {
            return coord[p_axis];
        }

        [[nodiscard]] std::string ToString() const {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        }
    };

    typedef Vector2<Unit> FVector2;
    typedef Vector2<int32_t> IVector2;
    typedef Vector2<uint32_t> UVector2;
}

namespace std {
    template <class T> static inline void hash_vector2_combine(std::size_t & s, const T & v) {
        std::hash<T> h;
        s^= h(v) + 0x9e3779b9 + (s<< 6) + (s>> 2);
    }

    template<typename U> struct hash<Framework::Helper::Math::Vector2<U>> {
        size_t operator()(Framework::Helper::Math::Vector2<U> const& vec) const {
            std::size_t res = 0;
            hash_vector2_combine<U>(res, vec.x);
            hash_vector2_combine<U>(res, vec.y);
            return res;
        }
    };
}

#endif //GAMEENGINE_VECTOR2_H
