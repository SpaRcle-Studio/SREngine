//
// Created by Nikita on 01.03.2021.
//

#include <Utils/Math/Quaternion.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Matrix3x3.h>
#include <Utils/Math/Matrix4x4.h>

namespace SR_MATH_NS {
    Vector3<Unit> Quaternion::EulerAngle() const {
        return Vector3<Unit>(glm::eulerAngles(glm::normalize(self))).Degrees();
    }

    Quaternion::Quaternion(const Vector3<Unit>& axis, Unit angle) {
        const Unit halfAngle = angle * static_cast<Unit>(.5f);
        const Unit s = (Unit)SR_SIN(halfAngle);

        auto&& normalized = axis.Normalized();

        x = normalized.x * s;
        y = normalized.y * s;
        z = normalized.z * s;
        w = (Unit)SR_COS(halfAngle);
    }

    Quaternion::Quaternion(const Vector3<Unit>& eulerAngle) {
        Vector3<T> c = (eulerAngle * T(0.5)).Cos();
        Vector3<T> s = (eulerAngle * T(0.5)).Sin();

        this->w = c.x * c.y * c.z + s.x * s.y * s.z;
        this->x = s.x * c.y * c.z - c.x * s.y * s.z;
        this->y = c.x * s.y * c.z + s.x * c.y * s.z;
        this->z = c.x * c.y * s.z - s.x * s.y * c.z;

        ///self = p_euler.ToGLM();
    }

    Vector3<Unit> Quaternion::operator*(const Vector3<Unit> &v) const noexcept {
        Vector3<Unit> const QuatVector(x, y, z);
        Vector3<Unit> const uv = QuatVector.Cross(v);
        Vector3<Unit> const uuv = QuatVector.Cross(uv);

        return v + ((uv * w) + uuv) * static_cast<Unit>(2);
    }

    Quaternion Quaternion::Rotate(const Vector3<Unit> &v) const {
        if (v.Empty())
            return *this;

        glm::quat q = glm::rotate(self, 1.f, glm::radians(glm::vec3(v.x, v.y, v.z)));
        return Quaternion(q);
    }

    Matrix4x4 Quaternion::ToMat4x4() const {
        return Matrix4x4(mat4_cast(self));
    }

   Vector3<Unit> Quaternion::operator/(const Vector3<Unit> &v) const {
        glm::vec3 rot = EulerAngle().ToGLM();

        /// TODO: здесь должна быть инвертирована ось z?
        glm::fquat q = glm::vec3(1) / glm::vec3(
                rot.x,
                rot.y,
                -rot.z
        );

        return Vector3<Unit>(q * v.ToGLM());
    }

   Quaternion Quaternion::FromEuler(const Vector3 <Unit> &euler) {
       return euler.Radians().ToQuat();
   }

   Unit Quaternion::Pitch() const noexcept {
       const Unit value_y = static_cast<Unit>(2) * (y * z + w * x);
       const Unit value_x = w * w - x * x - y * y + z * z;

       /// avoid atan2(0,0) - handle singularity - Matiis
       if (Vector2<Unit>(value_x, value_y) == Vector2<Unit>(Unit(0), Unit(0))) {
           return static_cast<Unit>(static_cast<Unit>(2) * atan2(x, w));
       }

       return static_cast<Unit>(atan2(value_y, value_x));
    }

   Quaternion Quaternion::RotateX(Unit angle) const {
       if (angle == static_cast<Unit>(0)) {
           return *this;
       }

       glm::quat q = glm::rotate(self, static_cast<float_t>(SR_RAD(angle)), glm::vec3(1, 0, 0));
       return Quaternion(q);
   }

   Quaternion Quaternion::RotateY(Unit angle) const {
       if (angle == static_cast<Unit>(0)) {
           return *this;
       }

       glm::quat q = glm::rotate(self, static_cast<float_t>(SR_RAD(angle)), glm::vec3(0, 1, 0));
       return Quaternion(q);
   }

   Quaternion Quaternion::RotateZ(Unit angle) const {
       if (angle == static_cast<Unit>(0)) {
           return *this;
       }

       glm::quat q = glm::rotate(self, static_cast<float_t>(SR_RAD(angle)), glm::vec3(0, 0, 1));
       return Quaternion(q);
   }

    Quaternion Quaternion::LookAt(const Vector3<Unit>& direction) {
        static constexpr Vector3<Unit> up = Vector3<Unit>(0, 1, 0);
        return Quaternion::LookAt(direction, up);
    }

    Quaternion Quaternion::LookAt(const Vector3<Unit>& direction, const Vector3<Unit>& up) {
        /*const Vector3 z = direction.Normalized();
        const Vector3 x = up.Cross(direction).Normalized();
        const Vector3 y = direction.Cross(x).Normalized();

        FVector4 rows[] = {
            FVector4(x, 0.0f),
            FVector4(y, 0.0f),
            FVector4(z, 0.0f),
            FVector4::UnitW()
        };

        return Quaternion(Matrix4x4(rows));*/

        /*const auto fw = direction.Normalized(); // Front
        const auto ri = axis.Cross(fw).Normalized(); // Left
        const auto up = fw.Cross(ri); // Up

        const auto a0 = ri;
        const auto a1 = up;
        const auto a2 = fw;
        const auto a00 = a0.x;
        const auto a10 = a0.y;
        const auto a20 = a0.z;
        const auto a01 = a1.x;
        const auto a11 = a1.y;
        const auto a21 = a1.z;
        const auto a02 = a2.x;
        const auto a12 = a2.y;
        const auto a22 = a2.z;

        const float trace = a00 + a11 + a22;
        if (trace > 0.0f) {
            const float s = 0.5f / std::sqrt(trace + 1.0f);
            return Quaternion(
                    0.25f / s,
                    (a21 - a12) * s,
                    (a02 - a20) * s,
                    (a10 - a01) * s
            ).Normalized();
        } else {
            if (a00 > a11 && a00 > a22) {
                const float s = 2.0f * std::sqrt(1.0f + a00 - a11 - a22);
                return Quaternion(
                        (a21 - a12) / s,
                        0.25f * s,
                        (a01 + a10) / s,
                        (a02 + a20) / s
                ).Normalized();
            } else if (a11 > a22) {
                const float s = 2.0f * std::sqrt(1.0f + a11 - a00 - a22);
                return Quaternion(
                        (a02 - a20) / s,
                        (a01 + a10) / s,
                        0.25f * s,
                        (a12 + a21) / s
                ).Normalized();
            } else {
                const float s = 2.0f * std::sqrt(1.0f + a22 - a00 - a11);
                return Quaternion(
                        (a10 - a01) / s,
                        (a02 + a20) / s,
                        (a12 + a21) / s,
                        0.25f * s
                ).Normalized();
            }
        }*/

        //////////

        /*auto&& normalDir = direction.Normalize();

        const Unit dot = up.Dot(normalDir);
        const Unit angle = std::acos(dot);

        const Vector3 axis = up.Cross(normalDir).Normalize();

        const Unit halfAngle = angle * 0.5f;
        const Unit s = std::sin(halfAngle);

        return Quaternion(
            axis.x * s,
            axis.y * s,
            axis.z * s,
            std::cos(halfAngle)
        );*/

        /////////////

        Quaternion q = glm::quatLookAt(direction.Normalize().ToGLM(), up.ToGLM());

        /// чиним возможные аффинные преобразования
        //q = q.EulerAngle().Radians().ToQuat();

        /// проверка существования кватерниона
        if (q.IsFinite()) {
            return q;
        }

        return Identity();
    }

    Unit Quaternion::SquaredNorm() const noexcept {
        return w * w + x * x + y * y + z * z;
    }

    Vector4 <Unit> Quaternion::Vector() const noexcept {
        return Vector4<Unit>(x, y, z, w);
    }

    Unit Quaternion::Distance(const Quaternion& q) const {
        auto&& qd = Inverse() * q;
        return 2 * atan2(qd.Vector().Length(), qd.W());
    }

    constexpr Quaternion::Quaternion(const Matrix4x4& matrix) {
        Vector3 m0 = matrix[0].XYZ(),
                m1 = matrix[1].XYZ(),
                m2 = matrix[2].XYZ();

        Unit length_sqr = m0[0] * m0[0] + m1[0] * m1[0] + m2[0] * m2[0];

        if (length_sqr != 1.0f && length_sqr != 0.0f) {
            length_sqr = 1.0f / sqrt(length_sqr);
            m0[0] *= length_sqr;
            m1[0] *= length_sqr;
            m2[0] *= length_sqr;
        }

        length_sqr = m0[1] * m0[1] + m1[1] * m1[1] + m2[1] * m2[1];

        if (length_sqr != 1.0f && length_sqr != 0.0f) {
            length_sqr = 1.0f / sqrt(length_sqr);
            m0[1] *= length_sqr;
            m1[1] *= length_sqr;
            m2[1] *= length_sqr;
        }

        length_sqr = m0[2] * m0[2] + m1[2] * m1[2] + m2[2] * m2[2];

        if (length_sqr != 1.0f && length_sqr != 0.0f) {
            length_sqr = 1.0f / sqrt(length_sqr);
            m0[2] *= length_sqr;
            m1[2] *= length_sqr;
            m2[2] *= length_sqr;
        }

        const Unit tr = m0[0] + m1[1] + m2[2];

        if (tr > 0.0f) {
            Unit S = sqrt(tr + 1.0f) * 2.0f; // S=4*qw

            x = (m2[1] - m1[2]) / S;
            y = (m0[2] - m2[0]) / S;
            z = (m1[0] - m0[1]) / S;
            w = 0.25f * S;
        } else if ((m0[0] > m1[1]) && (m0[0] > m2[2])) {
            Unit S = sqrt(1.0f + m0[0] - m1[1] - m2[2]) * 2.0f; // S=4*qx

            x = 0.25f * S;
            y = (m0[1] + m1[0]) / S;
            z = (m0[2] + m2[0]) / S;
            w = (m2[1] - m1[2]) / S;
        } else if (m1[1] > m2[2]) {
            Unit S = sqrt(1.0f + m1[1] - m0[0] - m2[2]) * 2.0f; // S=4*qy

            x = (m0[1] + m1[0]) / S;
            y = 0.25f * S;
            z = (m1[2] + m2[1]) / S;
            w = (m0[2] - m2[0]) / S;
        } else {
            Unit S = sqrt(1.0f + m2[2] - m0[0] - m1[1]) * 2.0f; // S=4*qz

            x = (m0[2] + m2[0]) / S;
            y = (m1[2] + m2[1]) / S;
            z = 0.25f * S;
            w = (m1[0] - m0[1]) / S;
        }
    }
}