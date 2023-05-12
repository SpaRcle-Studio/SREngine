//
// Created by Nikita on 01.03.2021.
//

#ifndef GAMEENGINE_QUATERNION_H
#define GAMEENGINE_QUATERNION_H

#include <Utils/Math/Mathematics.h>

namespace SR_MATH_NS {
    template<typename T> struct Vector3;

    class Matrix4x4;

    class SR_DLL_EXPORT Quaternion {
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
        SR_NODISCARD SR_FORCE_INLINE glm::quat ToGLM() const noexcept { return self; }
        SR_NODISCARD Matrix4x4 ToMat4x4() const;
        SR_NODISCARD SR_FORCE_INLINE glm::mat4 ToMat4x4GLM() const noexcept { return mat4_cast(self); }
        SR_NODISCARD Vector3<T> EulerAngle() const;
        SR_NODISCARD Quaternion Rotate(const Vector3<T>& v) const;

        SR_NODISCARD Quaternion RotateX(Unit angle) const;
        SR_NODISCARD Quaternion RotateY(Unit angle) const;
        SR_NODISCARD Quaternion RotateZ(Unit angle) const;

        SR_NODISCARD T X() const noexcept { return static_cast<T>(self.x); }
        SR_NODISCARD T Y() const noexcept { return static_cast<T>(self.y); }
        SR_NODISCARD T Z() const noexcept { return static_cast<T>(self.z); }
        SR_NODISCARD T W() const noexcept { return static_cast<T>(self.w); }

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

        //, bool inRads = false
        Quaternion(const Vector3<Unit> &p_euler);

        Quaternion(const glm::quat &q) {
            self = q;
        }

        Quaternion(const Vector3<Unit>& axis, Unit angle);

        constexpr explicit Quaternion(T x, T y, T z, T w)
            : x(x)
            , y(y)
            , z(z)
            , w(w)
        { }

        static Quaternion FromEuler(const Vector3<Unit>& euler);

        constexpr static Quaternion Identity() {
            return Quaternion(0.0, 0.0, 0.0, 1.0);
        }

        SR_NODISCARD Quaternion Inverse() const {
            return Quaternion(glm::inverse(self));
        }

        SR_NODISCARD Quaternion Slerp(const Quaternion& q, Unit t) const {
            SRAssertOnce(t >= 0.f || t <= 1.f);
            return Quaternion(glm::slerp(self, q.self, static_cast<float_t>(t)));
        }

        SR_NODISCARD static Quaternion LookAt(const Vector3<Unit>& direction);
        SR_NODISCARD static Quaternion LookAt(const Vector3<Unit>& direction, const Vector3<Unit>& up);

        SR_NODISCARD Quaternion Normalize() const {
            return Quaternion(glm::normalize(self));
        }

        SR_NODISCARD Unit Roll() const noexcept {
            return static_cast<Unit>(atan2(static_cast<Unit>(2) * (x * y + w * z), w * w + x * x - y * y - z * z));
        }

        SR_NODISCARD Unit Pitch() const noexcept;
        SR_NODISCARD Unit SquaredNorm() const noexcept;

        SR_NODISCARD Unit Yaw() const noexcept {
            return asin(SR_CLAMP(static_cast<Unit>(-2) * (x * z - w * y), static_cast<Unit>(1), static_cast<Unit>(-1)));
        }

        SR_NODISCARD std::string ToString() const {
            return "(" + std::to_string(self.x) + ", " + std::to_string(self.y) + ", " + std::to_string(self.z) + ", " + std::to_string(self.w) + ")";
        }

        SR_FORCE_INLINE bool operator!=(const Quaternion& q) const noexcept {
            return !(*this == q);
        }

        SR_FORCE_INLINE bool operator==(const Quaternion& q) const noexcept {
            return
                SR_EQUALS(x, q.x) &&
                SR_EQUALS(y, q.y) &&
                SR_EQUALS(z, q.z) &&
                SR_EQUALS(w, q.w);
        }

        SR_NODISCARD bool IsFinite() const noexcept {
            /// если будет inf или nan, то вернет false
            return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w);
        }

        SR_NODISCARD bool IsIdentity() const noexcept {
            return
                SR_EQUALS(x, 1.f) &&
                SR_EQUALS(y, 1.f) &&
                SR_EQUALS(z, 1.f) &&
                SR_EQUALS(w, 1.f);
        }

        SR_FORCE_INLINE void operator+=(const Quaternion &p_q) {
            self += p_q.self;
        }
        SR_FORCE_INLINE void operator-=(const Quaternion &p_q) {
            self -= p_q.self;
        }
        SR_FORCE_INLINE void operator*=(const Quaternion &p_q) {
            self *= p_q.self;
        }
        SR_FORCE_INLINE void operator*=(const double &s){
            self *= s;
        }
        SR_FORCE_INLINE void operator/=(const double &s) {
            self *= 1.0 / s;
        }
        SR_FORCE_INLINE Quaternion operator+(const Quaternion &q2) const {
            const Quaternion &q1 = *this;
            return Quaternion(q1.self + q2.self);
        }
        SR_FORCE_INLINE Quaternion operator-(const Quaternion &q2) const {
            const Quaternion &q1 = *this;
            return Quaternion(q1.self - q2.self);
        }
        SR_FORCE_INLINE Quaternion operator-() const {
            const Quaternion &q2 = *this;
            return Quaternion(-q2.self);
        }
        SR_FORCE_INLINE Quaternion operator*(const double &s) const {
            glm::quat q = self;
            q *= s;
            return Quaternion(q);
        }
        SR_FORCE_INLINE Quaternion operator/(const double &s) const {
            glm::quat q = self;
            q *= 1.0 / s;
            return Quaternion(q);
        }

        Vector3<Unit> operator*(const Vector3<Unit> &v) const noexcept;
        Vector3<Unit> operator/(const Vector3<Unit> &v) const;
        Quaternion operator*(const Quaternion& rhs) const {
            return Quaternion(self * rhs.self);
        }
    };

    inline static const Quaternion InfinityQuaternion = Quaternion { UnitMAX, UnitMAX, UnitMAX, UnitMAX };
}

#endif //GAMEENGINE_QUATERNION_H
