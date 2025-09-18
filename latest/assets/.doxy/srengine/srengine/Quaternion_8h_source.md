

# File Quaternion.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Math**](dir_f20ff43999c2f98e3f122645c07885db.md) **>** [**Quaternion.h**](Quaternion_8h.md)

[Go to the documentation of this file](Quaternion_8h.md)


```C++
//
// Created by Nikita on 01.03.2021.
//

#ifndef SR_ENGINE_QUATERNION_H
#define SR_ENGINE_QUATERNION_H

#include <Utils/Math/Mathematics.h>

namespace SR_MATH_NS {
    template<typename T> struct Vector3;
    template<typename T> struct Vector4;

    class Matrix4x4;

    class SR_COMMON_DLL_API Quaternion {
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

            glm::quat self{};
        };
    public:
        SR_NODISCARD const glm::quat& ToGLM() const noexcept;
        SR_NODISCARD Vector4<Unit> Vector() const noexcept;
        SR_NODISCARD Matrix4x4 ToMat4x4() const;
        SR_NODISCARD glm::mat4 ToMat4x4GLM() const noexcept;
        SR_NODISCARD Vector3<T> EulerAngle() const;
        SR_NODISCARD Quaternion Rotate(const Vector3<T>& v) const;

        SR_NODISCARD Quaternion RotateX(Unit angle) const;
        SR_NODISCARD Quaternion RotateY(Unit angle) const;
        SR_NODISCARD Quaternion RotateZ(Unit angle) const;

        SR_NODISCARD T X() const noexcept;
        SR_NODISCARD T Y() const noexcept;
        SR_NODISCARD T Z() const noexcept;
        SR_NODISCARD T W() const noexcept;

        Quaternion();
        Quaternion(const Quaternion &p_q);
        Quaternion(const Vector3<Unit> &p_euler);
        Quaternion(const glm::quat &q);
        Quaternion(const Vector3<Unit>& axis, Unit angle);
        explicit Quaternion(const Matrix4x4& matrix);
        explicit Quaternion(T x, T y, T z, T w);

        static Quaternion FromEuler(const Vector3<Unit>& euler);
        static Quaternion Identity();

        SR_NODISCARD Quaternion Inverse() const;
        SR_NODISCARD Quaternion Conjurate() const;

        SR_NODISCARD bool SR_FASTCALL IsEquals(const Quaternion& q, Unit tolerance) const noexcept;

        SR_NODISCARD Quaternion Slerp(const Quaternion& q, Unit t) const;

        SR_NODISCARD static Quaternion LookAt(const Vector3<Unit>& direction);
        SR_NODISCARD static Quaternion LookAt(const Vector3<Unit>& direction, const Vector3<Unit>& up);

        SR_NODISCARD Quaternion Normalized() const;
        SR_NODISCARD Quaternion Normalize() const;

        SR_NODISCARD Unit Roll() const noexcept;
        SR_NODISCARD Unit Pitch() const noexcept;
        SR_NODISCARD Unit Yaw() const noexcept;

        SR_NODISCARD Unit Magnitude() const noexcept;
        SR_NODISCARD Unit SquaredNorm() const noexcept;

        SR_NODISCARD std::string ToString() const;

        bool operator!=(const Quaternion& q) const noexcept;
        bool operator==(const Quaternion& q) const noexcept;

        SR_NODISCARD Unit SR_FASTCALL Distance(const Quaternion& q) const;
        SR_NODISCARD Unit SR_FASTCALL Angle(const Quaternion& q) const;

        SR_NODISCARD bool IsFinite() const noexcept;
        SR_NODISCARD bool IsIdentity() const noexcept;
        SR_NODISCARD bool IsSane() const noexcept;

        void operator+=(const Quaternion &p_q);
        void operator-=(const Quaternion &p_q);
        void operator*=(const Quaternion &p_q);
        void operator*=(const double &s);
        void operator/=(const double &s);
        Quaternion operator+(const Quaternion &q2) const;
        Quaternion operator-(const Quaternion &q2) const;
        Quaternion operator-() const;
        Quaternion operator*(const double &s) const;
        Quaternion operator/(const double &s) const;
        Vector3<Unit> operator*(const Vector3<Unit> &v) const noexcept;
        Vector3<Unit> operator/(const Vector3<Unit> &v) const;
        Quaternion operator*(const Quaternion& rhs) const;
    };

    inline static const Quaternion InfinityQuaternion = Quaternion { UnitMAX, UnitMAX, UnitMAX, UnitMAX };
}

#endif //SR_ENGINE_QUATERNION_H
```


