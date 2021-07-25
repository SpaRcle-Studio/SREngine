//
// Created by Nikita on 11.07.2021.
//

#ifndef EVOSCRIPTLIB_VECTOR3_H
#define EVOSCRIPTLIB_VECTOR3_H

#include "Math.h"

struct Vector3 {
public:
    union {
        struct {
            Unit x;
            Unit y;
            Unit z;
        };

        Unit coord[3] = { 0 };
    };

    [[nodiscard]] Unit Max() const {
        return x > y && x > z ? x : y > x && y > z ? y : z;
    }
    [[nodiscard]] Unit Min() const {
        return x < y && x < z ? x : y < x && y < z ? y : z;
    }

    [[nodiscard]] inline bool Empty() const {
        return (x == 0 && y == 0 && z == 0);
    }

    [[nodiscard]] inline Vector3 Radians() const noexcept {
        return { static_cast<Unit>(RAD(x)), static_cast<Unit>(RAD(y)), static_cast<Unit>(RAD(z)) };
    }
    [[nodiscard]] inline Vector3 Degrees() const noexcept {
        return { static_cast<Unit>(DEG(x)), static_cast<Unit>(DEG(y)), static_cast<Unit>(DEG(z)) };
    }

    inline std::string ToString(){
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }

    _FORCE_INLINE_ Vector3() {
        x = 0;
        y = 0;
        z = 0;
    }
    _FORCE_INLINE_ Vector3(const float* vec) {
        x = (Unit)vec[0];
        y = (Unit)vec[1];
        z = (Unit)vec[2];
    }
    _FORCE_INLINE_ Vector3(const unsigned char* axis) {
        x = (Unit)axis[0];
        y = (Unit)axis[1];
        z = (Unit)axis[2];
    }
    _FORCE_INLINE_ Vector3(Unit p_x, Unit p_y, Unit p_z) {
        x = p_x;
        y = p_y;
        z = p_z;
    }
    _FORCE_INLINE_ Vector3(Unit p) {
        x = p;
        y = p;
        z = p;
    }
    [[nodiscard]] Unit Distance(Vector3 point) const {
        return sqrt(
                pow(point.x - x, 2) +
                pow(point.y - y, 2) +
                pow(point.z - z, 2)
        );
    }

    static Unit Magnitude(Vector3 vec) {
        return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
    }

    [[nodiscard]] Vector3 Direction(Vector3 point) const noexcept {
        if (point == *this)
            return Vector3();
        Vector3 heading = point - (*this);
        Unit distance = Magnitude(heading);
        return heading / distance;
    }

    Vector3 Limits(int lim) const {
        int xi = (int)x / lim;
        int yi = (int)y / lim;
        int zi = (int)z / lim;

        Unit xd = x - lim * (Unit)xi;
        Unit yd = y - lim * (Unit)yi;
        Unit zd = z - lim * (Unit)zi;

        return Vector3(xd, yd, zd);
    }

    [[nodiscard]] Vector3 Inverse() const {
        return Vector3(-x, -y, -z);
    }

    [[nodiscard]] Vector3 InverseAxis(unsigned char axis) const {
        Vector3 v = *this;
        v[axis] = -v[axis];
        return v;
    }

    [[nodiscard]] Vector3 Normalize() const {
        Unit len = std::sqrt(x * x + y * y + z * z);

        Vector3 vec3 = *this;

        if (len != 0.)
        {
            vec3.x /= len;
            vec3.y /= len;
            vec3.z /= len;
        }

        return vec3;
    }

    _FORCE_INLINE_ const Unit &operator[](int p_axis) const {
        return coord[p_axis];
    }

    _FORCE_INLINE_ Unit &operator[](int p_axis) {
        return coord[p_axis];
    }

    inline Vector3 Replace(int from, int to) const noexcept {
        return Vector3(
                x == from ? to : x,
                y == from ? to : y,
                z == from ? to : z);
    }
    inline Vector3 Abs() const noexcept {
        return Vector3(abs(x), abs(y), abs(z));
    }

    static inline Unit Dot(Vector3 lhs, Vector3 rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
    [[nodiscard]] Unit Dot(Vector3 p_b) const { return x * p_b.x + y * p_b.y + z * p_b.z; }

    [[nodiscard]] inline Vector3 Cross(const Vector3 &p_b) const {
        Vector3 ret(
                (y * p_b.z) - (z * p_b.y),
                (z * p_b.x) - (x * p_b.z),
                (x * p_b.y) - (y * p_b.x));

        return ret;
    }
    static inline Vector3 Cross(const Vector3 &p_a, const Vector3 &p_b) {
        Vector3 ret(
                (p_a.y * p_b.z) - (p_a.z * p_b.y),
                (p_a.z * p_b.x) - (p_a.x * p_b.z),
                (p_a.x * p_b.y) - (p_a.y * p_b.x));
        return ret;
    }

    _FORCE_INLINE_ Vector3 &operator+=(const Vector3 &p_v){
        x += p_v.x;
        y += p_v.y;
        z += p_v.z;
        return *this;
    }
    _FORCE_INLINE_ Vector3 operator+(const Vector3 &p_v) const {
        return Vector3(x + p_v.x, y + p_v.y, z + p_v.z); }
    _FORCE_INLINE_ Vector3 &operator-=(const Vector3 &p_v) {
        x -= p_v.x;
        y -= p_v.y;
        z -= p_v.z;
        return *this;
    }
    _FORCE_INLINE_ Vector3 operator-(const Vector3 &p_v) const {
        return Vector3(x - p_v.x, y - p_v.y, z - p_v.z);
    }
    _FORCE_INLINE_ Vector3 &operator*=(const Vector3 &p_v) {
        x *= p_v.x;
        y *= p_v.y;
        z *= p_v.z;
        return *this;
    }
    _FORCE_INLINE_ Vector3 operator*(const Vector3 &p_v) const {
        return Vector3(x * p_v.x, y * p_v.y, z * p_v.z);
    }

    _FORCE_INLINE_ Vector3 &operator/=(const Vector3 &p_v) {
        x /= p_v.x;
        y /= p_v.y;
        z /= p_v.z;
        return *this;
    }
    _FORCE_INLINE_ Vector3 operator/(const Vector3 &p_v) const {
        return Vector3(x / p_v.x, y / p_v.y, z / p_v.z);
    }

    _FORCE_INLINE_ Vector3 &operator*=(Unit p_scalar) {
        x *= p_scalar;
        y *= p_scalar;
        z *= p_scalar;
        return *this;
    }
    _FORCE_INLINE_ Vector3 operator*(Unit p_scalar) const {
        return Vector3(x * p_scalar, y * p_scalar, z * p_scalar);
    }
    _FORCE_INLINE_ Vector3 &operator/=(Unit p_scalar) {
        x /= p_scalar;
        y /= p_scalar;
        z /= p_scalar;
        return *this;
    }
    _FORCE_INLINE_ Vector3 operator/(Unit p_scalar) const {
        return Vector3(x / p_scalar, y / p_scalar, z / p_scalar);
    }

    _FORCE_INLINE_ Vector3 operator-() const { return Vector3(-x, -y, -z); }

    _FORCE_INLINE_ bool operator==(const Vector3 &p_v) const { return x == p_v.x && y == p_v.y && z == p_v.z; }
    _FORCE_INLINE_ bool operator!=(const Vector3 &p_v) const {return x != p_v.x || y != p_v.y || z != p_v.z; }
    _FORCE_INLINE_ bool operator<(const Vector3 &p_v) const {
        if (x == p_v.x) {
            if (y == p_v.y) {
                return z < p_v.z;
            }
            return y < p_v.y;
        }
        return x < p_v.x;
    }
    _FORCE_INLINE_ bool operator<=(const Vector3 &p_v) const {
        if (x == p_v.x) {
            if (y == p_v.y) {
                return z > p_v.z;
            }
            return y > p_v.y;
        }
        return x > p_v.x;
    }
    _FORCE_INLINE_ bool operator>(const Vector3 &p_v) const {
        if (x == p_v.x) {
            if (y == p_v.y) {
                return z <= p_v.z;
            }
            return y < p_v.y;
        }
        return x < p_v.x;
    }
    _FORCE_INLINE_ bool operator>=(const Vector3 &p_v) const {
        if (x == p_v.x) {
            if (y == p_v.y) {
                return z >= p_v.z;
            }
            return y > p_v.y;
        }
        return x > p_v.x;
    }
};

#endif //EVOSCRIPTLIB_VECTOR3_H
