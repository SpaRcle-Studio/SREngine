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

    constexpr Quaternion() {
        x = y = z = static_cast<T>(0);
        w = static_cast<T>(1);
    }

    constexpr explicit Quaternion(T x, T y, T z, T w)
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

    Vector3<Unit> operator*(const Vector3<Unit> &v) const noexcept {
        Vector3<Unit> const QuatVector(x, y, z);
        Vector3<Unit> const uv = QuatVector.Cross(v);
        Vector3<Unit> const uuv = QuatVector.Cross(uv);

        return v + ((uv * w) + uuv) * static_cast<Unit>(2);
    }
};

#endif //EVOSCRIPTLIB_QUATERNION_H
