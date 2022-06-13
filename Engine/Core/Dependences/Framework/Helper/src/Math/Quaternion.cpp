//
// Created by Nikita on 01.03.2021.
//

#include <Math/Quaternion.h>
#include <Math/Vector3.h>
#include <Math/Matrix3x3.h>
#include <Math/Matrix4x4.h>

namespace SR_UTILS_NS::Math {
    Vector3<Unit> Quaternion::EulerAngle() const {
        return Vector3<Unit>(glm::eulerAngles(glm::normalize(self))).Degrees();
    }

    Quaternion::Quaternion(const Vector3<Unit> &p_euler) {
        self = p_euler.ToGLM();
    }

    Vector3<Unit>Quaternion::operator*(const Vector3<Unit> &v) const {
        return Vector3<Framework::Helper::Math::Unit>(self * v.ToGLM());
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
}