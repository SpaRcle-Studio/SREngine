//
// Created by Nikita on 01.03.2021.
//

#ifndef GAMEENGINE_VECTOR3_H
#define GAMEENGINE_VECTOR3_H

#include <string>
#include "Mathematics.h"
#include <glm/glm.hpp>

namespace Framework::Helper::Math {
    class Quaternion;

    struct  Vector2 {
    public:
        union {
            struct {
                double x;
                double y;
            };

            double coord[2] = {0};
        };

        _FORCE_INLINE_ Vector2 operator+(const Vector2 &p_v) const {
            return Vector2(x + p_v.x, y + p_v.y); }
        _FORCE_INLINE_ Vector2 operator-(const Vector2 &p_v) const {
            return Vector2(x - p_v.x, y - p_v.y); }
        _FORCE_INLINE_ Vector2 operator*(const Vector2 &p_v) const {
            return Vector2(x * p_v.x, y * p_v.y); }
        _FORCE_INLINE_ Vector2 operator/(const Vector2 &p_v) const {
            return Vector2(x / p_v.x, y / p_v.y); }

        _FORCE_INLINE_ Vector2(const glm::vec2& vec2) {
            x = vec2.x;
            y = vec2.y;
        }

        _FORCE_INLINE_ glm::vec2 ToGLM() const noexcept {
            return {x,y};
        }

        _FORCE_INLINE_ const double &operator[](int p_axis) const {
            return coord[p_axis];
        }

        _FORCE_INLINE_ double &operator[](int p_axis) {
            return coord[p_axis];
        }
        _FORCE_INLINE_ Vector2(double p_x, double p_y) {
            x = p_x;
            y = p_y;
        }
    };

    struct  Vector3 {
    public:
        enum Axis {
            AXIS_X,
            AXIS_Y,
            AXIS_Z,
            NONE,
        };

        union {
            struct {
                double x;
                double y;
                double z;
            };

            double coord[3] = { 0 };
        };

        [[nodiscard]] inline bool Empty() const {
            return (x == 0 && y == 0 && z == 0);
        }

        [[nodiscard]] inline Vector3 Radians() const noexcept {
            return { RAD(x), RAD(y), RAD(z) };
        }
        [[nodiscard]] inline Vector3 Degrees() const noexcept {
            return { DEG(x), DEG(y), DEG(z) };
        }

        [[nodiscard]] inline glm::vec3 ToGLM() const noexcept {
            return glm::vec3(x,y,z);
        }
         Vector3(glm::vec3 v) {
            x = v.x;
            y = v.y;
            z = v.z;
        }

        inline std::string ToString(){
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
        }

        //Vector3(const Quaternion& q);
        _FORCE_INLINE_ Vector3() {
            x = 0;
            y = 0;
            z = 0;
        }
        _FORCE_INLINE_ Vector3(double p_x, double p_y, double p_z) {
            x = p_x;
            y = p_y;
            z = p_z;
        }

        [[nodiscard]] double Distance(Vector3 point) const {
            return sqrt(
                    pow(point.x - x, 2) +
                        pow(point.y - y, 2) +
                        pow(point.z - z, 2)
            );
        }

        static double Magnitude(Vector3 vec) {
            return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
        }

        [[nodiscard]] Vector3 Direction(Vector3 point) const noexcept {
            Vector3 heading = point - (*this);
            double distance = Magnitude(heading);
            return heading / distance;
        }

        Vector3 Limits(int lim) const {
            int xi = (int)x / lim;
            int yi = (int)y / lim;
            int zi = (int)z / lim;

            double xd = x - lim * (double)xi;
            double yd = y - lim * (double)yi;
            double zd = z - lim * (double)zi;

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
            double len = std::sqrt(x * x + y * y + z * z);

            Vector3 vec3 = *this;

            if (len != 0.)
            {
                vec3.x /= len;
                vec3.y /= len;
                vec3.z /= len;
            }

            return vec3;
        }

        [[nodiscard]] Quaternion ToQuat(bool inRads = false) const;

        _FORCE_INLINE_ const double &operator[](int p_axis) const {
            return coord[p_axis];
        }

        _FORCE_INLINE_ double &operator[](int p_axis) {
            return coord[p_axis];
        }

        static inline double Dot(Vector3 lhs, Vector3 rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
        [[nodiscard]] double Dot(Vector3 p_b) const { return x * p_b.x + y * p_b.y + z * p_b.z; }

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

        _FORCE_INLINE_ Vector3 &operator*=(double p_scalar) {
            x *= p_scalar;
            y *= p_scalar;
            z *= p_scalar;
            return *this;
        }
        _FORCE_INLINE_ Vector3 operator*(double p_scalar) const {
            return Vector3(x * p_scalar, y * p_scalar, z * p_scalar);
        }
        _FORCE_INLINE_ Vector3 &operator/=(double p_scalar) {
            x /= p_scalar;
            y /= p_scalar;
            z /= p_scalar;
            return *this;
        }
        _FORCE_INLINE_ Vector3 operator/(double p_scalar) const {
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

        Vector3 Rotate(const Quaternion& q) const;
    };
}

#endif //GAMEENGINE_VECTOR3_H
