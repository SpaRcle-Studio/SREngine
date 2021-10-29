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

struct Vector2 {
public:
    union {
        struct {
            Unit x;
            Unit y;
        };

        Unit coord[2] = {0};
    };

    Unit Distance(const Vector2 &vec) const noexcept {
        return sqrt(pow(vec.x - x, 2) + pow(vec.y - y, 2));
    }

    inline Vector2 operator*(const Unit &scalar) noexcept {
        return Vector2(x * scalar, y * scalar);
    }

    _FORCE_INLINE_ Vector2 operator+(const Vector2 &p_v) const {
        return Vector2(x + p_v.x, y + p_v.y);
    }

    _FORCE_INLINE_ Vector2

    operator-(const Vector2 &p_v) const {
        return Vector2(x - p_v.x, y - p_v.y);
    }

    _FORCE_INLINE_ Vector2

    operator*(const Vector2 &p_v) const {
        return Vector2(x * p_v.x, y * p_v.y);
    }

    _FORCE_INLINE_ Vector2

    operator/(const Vector2 &p_v) const {
        return Vector2(x / p_v.x, y / p_v.y);
    }

    _FORCE_INLINE_ Vector2() {
        x = 0;
        y = 0;
    }

    _FORCE_INLINE_ const Unit &operator[](int p_axis) const {
        return coord[p_axis];
    }

    _FORCE_INLINE_ Unit &operator[](int p_axis) {
        return coord[p_axis];
    }

    _FORCE_INLINE_ Vector2(Unit p_x, Unit p_y) {
        x = p_x;
        y = p_y;
    }

    std::string ToString() {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

#endif //EVOSCRIPTLIB_VECTOR2_H
