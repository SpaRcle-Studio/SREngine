//
// Created by Monika on 02.10.2022.
//

#ifndef EVOSCRIPTLIB_QUATERNION_H
#define EVOSCRIPTLIB_QUATERNION_H

#include <Libraries/Math/CoreMath.h>
#include <Libraries/Math/Vector3.h>

class Quaternion {
    friend Vector3<Unit>;
    using T = Unit;
public:
    union {
        struct {
            float_t x;
            float_t y;
            float_t z;
            float_t w;
        };
    };
public:
    SR_NODISCARD T X() const noexcept { return static_cast<T>(x); }
    SR_NODISCARD T Y() const noexcept { return static_cast<T>(y); }
    SR_NODISCARD T Z() const noexcept { return static_cast<T>(z); }
    SR_NODISCARD T W() const noexcept { return static_cast<T>(w); }

    constexpr Quaternion(const Quaternion &p_q)
        : x(p_q.x)
        , y(p_q.y)
        , z(p_q.z)
        , w(p_q.w)
    { }

    Quaternion() {
        x = y = z = static_cast<T>(0);
        w = static_cast<T>(1);
    }

    explicit Quaternion(T x, T y, T z, T w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    { }

    Quaternion(const Vector3<Unit>& eulerAngle) {
        Vector3<T> c = (eulerAngle * T(0.5)).Cos();
        Vector3<T> s = (eulerAngle * T(0.5)).Sin();

        this->w = c.x * c.y * c.z + s.x * s.y * s.z;
        this->x = s.x * c.y * c.z - c.x * s.y * s.z;
        this->y = c.x * s.y * c.z + s.x * c.y * s.z;
        this->z = c.x * c.y * s.z - s.x * s.y * c.z;
    }

    /*T Dot(const Quaternion& q) const noexcept {
        return x * q.x + y * q.y + z * q.z + w * q.w;
    }

    T Length() const noexcept {
        return sqrt(Dot(*this));
    }*/

    T Roll() const noexcept {
        return static_cast<T>(atan2(static_cast<T>(2) * (x * y + w * z), w * w + x * x - y * y - z * z));
    }

    T Pitch() const noexcept {
        const T value_y = static_cast<T>(2) * (y * z + w * x);
        const T value_x = w * w - x * x - y * y + z * z;

        /// avoid atan2(0,0) - handle singularity - Matiis
        if (Vector2<T>(value_x, value_y).IsEquals(Vector2<T>(Unit(0), Unit(0)), SR_EPSILON)) {
            return static_cast<T>(static_cast<T>(2) * atan2(x, w));
        }

        return static_cast<T>(atan2(value_y, value_x));
    }

    T Yaw() const noexcept {
        return asin(SR_CLAMP(static_cast<T>(-2) * (x * z - w * y), static_cast<T>(1), static_cast<T>(-1)));
    }

    /*Quaternion Normalize() const noexcept {
        const T len = Length();

        /// Problem
        if (len <= static_cast<T>(0)) {
            return Quaternion(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
        }

        const T oneOverLen = static_cast<T>(1) / len;

        return Quaternion(w * oneOverLen, x * oneOverLen, y * oneOverLen, z * oneOverLen);
    }*/

    Vector3<T> EulerAngles() const noexcept {
        //TODO
        //Quaternion q = Normalize();
        //return Vector3<T>(q.Pitch(), q.Yaw(), q.Roll()).Degrees();
        return Vector3<T>(Pitch(), Yaw(), Roll()).Degrees();
    }

    Quaternion operator*(const Quaternion& q) const noexcept {
        Quaternion result;

        result.w = w * q.w - x * q.x - y * q.y - z * q.z;
        result.x = w * q.x + x * q.w + y * q.z - z * q.y;
        result.y = w * q.y + y * q.w + z * q.x - x * q.z;
        result.z = w * q.z + z * q.w + x * q.y - y * q.x;

        return result;
    }

    Vector3<Unit> operator*(const Vector3<Unit> &v) const noexcept {
        Vector3<Unit> const QuatVector(x, y, z);
        Vector3<Unit> const uv = QuatVector.Cross(v);
        Vector3<Unit> const uuv = QuatVector.Cross(uv);

        return v + ((uv * w) + uuv) * static_cast<Unit>(2);
    }
};

#endif //EVOSCRIPTLIB_QUATERNION_H
