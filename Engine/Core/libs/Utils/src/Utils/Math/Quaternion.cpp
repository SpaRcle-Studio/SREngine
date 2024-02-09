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
        Quaternion q = glm::quatLookAt(direction.Normalize().ToGLM(), up.ToGLM());

        /// чиним возможные аффинные преобразования
        q = q.EulerAngle().Radians().ToQuat();

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
}