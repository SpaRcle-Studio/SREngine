//
// Created by Nikita on 01.03.2021.
//

#include "Math/Quaternion.h"
#include <Math/Vector3.h>
#include <Math/Matrix3x3.h>
#include <Math/Matrix4x4.h>

//bool degrees
Framework::Helper::Math::Vector3<Framework::Helper::Math::Unit> Framework::Helper::Math::Quaternion::EulerAngle() const {
    //if (degrees)
    //    return Vector3<Framework::Helper::Math::Unit>(glm::eulerAngles(self)).Degrees();
    //else
        return Vector3<Framework::Helper::Math::Unit>(glm::eulerAngles(glm::normalize(self))).Degrees();
}

//, bool inRads
Framework::Helper::Math::Quaternion::Quaternion(const Framework::Helper::Math::Vector3<Framework::Helper::Math::Unit> &p_euler) {
    //if (inRads)
        self = p_euler.ToGLM();
    //else
    //    self = glm::radians(v.ToGLM());
}

Framework::Helper::Math::Vector3<Framework::Helper::Math::Unit>
Framework::Helper::Math::Quaternion::operator*(const Framework::Helper::Math::Vector3<Framework::Helper::Math::Unit> &v) const {
    /*glm::vec3 rot = EulerAngle().ToGLM();

    glm::fquat q = glm::vec3(
            rot.x,
            rot.y,
            -rot.z
    );*/

    return Vector3<Framework::Helper::Math::Unit>(self * v.ToGLM());
}

Framework::Helper::Math::Quaternion
Framework::Helper::Math::Quaternion::Rotate(const Framework::Helper::Math::Vector3<Framework::Helper::Math::Unit> &v) const {
    if (v.Empty())
        return *this;

    glm::quat q = glm::rotate(self, 1.f, glm::radians(glm::vec3(v.x, v.y, v.z)));
    return Framework::Helper::Math::Quaternion(q);
}

Framework::Helper::Math::Matrix4x4 Framework::Helper::Math::Quaternion::ToMat4x4() const {
    return Matrix4x4(mat4_cast(self));
}

Framework::Helper::Math::Vector3<Framework::Helper::Math::Unit>
Framework::Helper::Math::Quaternion::operator/(const Framework::Helper::Math::Vector3<Framework::Helper::Math::Unit> &v) const {
    glm::vec3 rot = EulerAngle().ToGLM();

    glm::fquat q = glm::vec3(1) / glm::vec3(
            rot.x,
            rot.y,
            -rot.z
    );

    return Vector3<Framework::Helper::Math::Unit>(q * v.ToGLM());
}

Quaternion Quaternion::FromEuler(const Vector3<Unit> &euler) {
    return euler.Radians().ToQuat();
}

