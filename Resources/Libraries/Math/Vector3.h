//
// Created by Nikita on 11.07.2021.
//

#ifndef EVOSCRIPTLIB_VECTOR3_H
#define EVOSCRIPTLIB_VECTOR3_H

#include <Libraries/Math/CoreMath.h>

template<typename T> struct Vector3 {
public:
    union {
        struct {
            T x;
            T y;
            T z;
        };

        T coord[3] = { 0 };
    };
public:
    SR_FORCE_INLINE Vector3() {
        x = 0;
        y = 0;
        z = 0;
    }
    SR_FORCE_INLINE explicit Vector3(const float* vec) {
        x = (Unit)vec[0];
        y = (Unit)vec[1];
        z = (Unit)vec[2];
    }
    SR_FORCE_INLINE explicit Vector3(const unsigned char* axis) {
        x = (Unit)axis[0];
        y = (Unit)axis[1];
        z = (Unit)axis[2];
    }
    SR_FORCE_INLINE Vector3(T p_x, T p_y, T p_z) {
        x = p_x;
        y = p_y;
        z = p_z;
    }
    SR_FORCE_INLINE Vector3(T p) {
        x = p;
        y = p;
        z = p;
    }

public:
    SR_NODISCARD T Max() const {
        return x > y && x > z ? x : y > x && y > z ? y : z;
    }
    SR_NODISCARD T Min() const {
        return x < y && x < z ? x : y < x && y < z ? y : z;
    }

    SR_NODISCARD Vector3 Sin() const {
        return Vector3(static_cast<T>(sin(x)), static_cast<T>(sin(y)), static_cast<T>(sin(z)));
    }

    SR_NODISCARD Vector3 Cos() const {
        return Vector3(static_cast<T>(cos(x)), static_cast<T>(cos(y)), static_cast<T>(cos(z)));
    }

    SR_NODISCARD bool Empty() const {
        return (x == 0 && y == 0 && z == 0);
    }

    SR_NODISCARD Vector3 Radians() const noexcept {
        return { static_cast<T>(SR_RAD(x)), static_cast<T>(SR_RAD(y)), static_cast<T>(SR_RAD(z)) };
    }
    SR_NODISCARD Vector3 Degrees() const noexcept {
        return { static_cast<T>(SR_DEG(x)), static_cast<T>(SR_DEG(y)), static_cast<T>(SR_DEG(z)) };
    }

    std::string ToString(){
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }

    SR_NODISCARD T Distance(Vector3 point) const {
        return std::sqrt(
                pow(point.x - x, 2) +
                pow(point.y - y, 2) +
                pow(point.z - z, 2)
        );
    }

    SR_NODISCARD Vector3 Direction(Vector3 point) const {
        if (point == *this)
            return Vector3();
        Vector3 heading = point - (*this);
        T distance = Magnitude(heading);
        return heading / distance;
    }

    SR_NODISCARD Vector3 Limits(int lim) const {
        int xi = (int)x / lim;
        int yi = (int)y / lim;
        int zi = (int)z / lim;

        T xd = x - lim * (T)xi;
        T yd = y - lim * (T)yi;
        T zd = z - lim * (T)zi;

        return Vector3(xd, yd, zd);
    }

    SR_NODISCARD Vector3 Inverse() const {
        return Vector3(-x, -y, -z);
    }

    SR_NODISCARD Vector3 InverseAxis(unsigned char axis) const {
        Vector3 v = *this;
        v[axis] = -v[axis];
        return v;
    }

    SR_NODISCARD Vector3<T> Clamp(const Vector3<T>& upper, const Vector3<T>& lover) const {
        return Vector3<T>(
                SR_CLAMP(x, lover.x, upper.x),
                SR_CLAMP(y, lover.y, upper.y),
                SR_CLAMP(z, lover.z, upper.z)
        );
    }

    SR_NODISCARD Vector3 Normalize() const {
        T len = static_cast<T>(std::sqrt(x * x + y * y + z * z));

        Vector3 vec3 = *this;

        if (len != static_cast<T>(0.)) {
            vec3.x /= len;
            vec3.y /= len;
            vec3.z /= len;
        }

        return vec3;
    }

    SR_FORCE_INLINE const Unit &operator[](int p_axis) const {
        return coord[p_axis];
    }

    SR_FORCE_INLINE Unit &operator[](int p_axis) {
        return coord[p_axis];
    }

    SR_NODISCARD Vector3 Replace(int from, int to) const {
        return Vector3(
                x == from ? to : x,
                y == from ? to : y,
                z == from ? to : z);
    }

    SR_NODISCARD Vector3 Abs() const {
        return Vector3(static_cast<T>(abs(x)), static_cast<T>(abs(y)), static_cast<T>(abs(z)));
    }

    SR_NODISCARD T Dot(Vector3 p_b) const { return x * p_b.x + y * p_b.y + z * p_b.z; }

    SR_NODISCARD Vector3 Cross(const Vector3 &p_b) const {
        Vector3 ret(
                (y * p_b.z) - (z * p_b.y),
                (z * p_b.x) - (x * p_b.z),
                (x * p_b.y) - (y * p_b.x));

        return ret;
    }

    template<typename U> SR_FORCE_INLINE Vector3 &operator+=(const Vector3<U> &p_v){
        x += p_v.x;
        y += p_v.y;
        z += p_v.z;
        return *this;
    }
    template<typename U> SR_FORCE_INLINE Vector3 operator+(const Vector3<U> &p_v) const {
        return Vector3(x + p_v.x, y + p_v.y, z + p_v.z);
    }
    template<typename U> SR_FORCE_INLINE Vector3 &operator-=(const Vector3<U> &p_v) {
        x -= p_v.x;
        y -= p_v.y;
        z -= p_v.z;
        return *this;
    }
    template<typename U> SR_FORCE_INLINE Vector3 operator-(const Vector3<U> &p_v) const {
        return Vector3(x - p_v.x, y - p_v.y, z - p_v.z);
    }
    template<typename U> SR_FORCE_INLINE Vector3 &operator*=(const Vector3<U> &p_v) {
        x *= p_v.x;
        y *= p_v.y;
        z *= p_v.z;
        return *this;
    }
    template<typename U> SR_FORCE_INLINE Vector3 operator*(const Vector3<U> &p_v) const {
        return Vector3(x * p_v.x, y * p_v.y, z * p_v.z);
    }

    template<typename U> SR_FORCE_INLINE Vector3 &operator/=(const Vector3<U> &p_v) {
        x /= p_v.x;
        y /= p_v.y;
        z /= p_v.z;
        return *this;
    }
    template<typename U> SR_FORCE_INLINE Vector3 operator/(const Vector3<U> &p_v) const {
        return Vector3(x / p_v.x, y / p_v.y, z / p_v.z);
    }

    template<typename U> SR_FORCE_INLINE Vector3 &operator*=(U p_scalar) {
        x *= p_scalar;
        y *= p_scalar;
        z *= p_scalar;
        return *this;
    }
    template<typename U> SR_FORCE_INLINE Vector3 operator*(U p_scalar) const {
        return Vector3(x * p_scalar, y * p_scalar, z * p_scalar);
    }
    template<typename U> SR_FORCE_INLINE Vector3 &operator/=(U p_scalar) {
        x /= p_scalar;
        y /= p_scalar;
        z /= p_scalar;
        return *this;
    }
    template<typename U> SR_FORCE_INLINE Vector3 operator/(U p_scalar) const {
        return Vector3(x / p_scalar, y / p_scalar, z / p_scalar);
    }

    SR_FORCE_INLINE Vector3 operator-() const { return Vector3(-x, -y, -z); }

    SR_FORCE_INLINE bool operator==(const Vector3 &p_v) const { return x == p_v.x && y == p_v.y && z == p_v.z; }
    SR_FORCE_INLINE bool operator!=(const Vector3 &p_v) const {return x != p_v.x || y != p_v.y || z != p_v.z; }
    SR_FORCE_INLINE bool operator<(const Vector3 &p_v) const {
        if (x == p_v.x) {
            if (y == p_v.y) {
                return z < p_v.z;
            }
            return y < p_v.y;
        }
        return x < p_v.x;
    }
    SR_FORCE_INLINE bool operator<=(const Vector3 &p_v) const {
        if (x == p_v.x) {
            if (y == p_v.y) {
                return z > p_v.z;
            }
            return y > p_v.y;
        }
        return x > p_v.x;
    }
    SR_FORCE_INLINE bool operator>(const Vector3 &p_v) const {
        if (x == p_v.x) {
            if (y == p_v.y) {
                return z <= p_v.z;
            }
            return y < p_v.y;
        }
        return x < p_v.x;
    }
    SR_FORCE_INLINE bool operator>=(const Vector3 &p_v) const {
        if (x == p_v.x) {
            if (y == p_v.y) {
                return z >= p_v.z;
            }
            return y > p_v.y;
        }
        return x > p_v.x;
    }

public:
    static Unit Magnitude(Vector3 vec) {
        return std::sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
    }
    static T Dot(Vector3 lhs, Vector3 rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
    static Vector3 Cross(const Vector3 &p_a, const Vector3 &p_b) {
        Vector3 ret(
                (p_a.y * p_b.z) - (p_a.z * p_b.y),
                (p_a.z * p_b.x) - (p_a.x * p_b.z),
                (p_a.x * p_b.y) - (p_a.y * p_b.x));
        return ret;
    }
};

typedef Vector3<Unit> FVector3;
typedef Vector3<int32_t> IVector3;
typedef Vector3<uint32_t> UVector3;

#endif //EVOSCRIPTLIB_VECTOR3_H
