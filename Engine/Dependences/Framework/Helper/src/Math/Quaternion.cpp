//
// Created by Nikita on 01.03.2021.
//

#include "Math/Quaternion.h"
#include <Math/Vector3.h>
#include <Math/Matrix3x3.h>

Framework::Helper::Math::Vector3 Framework::Helper::Math::Quaternion::EulerAngle(bool degrees) const {
    if (degrees)
        return Vector3(glm::eulerAngles(self)).Degrees();
    else
        return Vector3(glm::eulerAngles(self));
}

Framework::Helper::Math::Quaternion::Quaternion(const Framework::Helper::Math::Vector3 &p_euler) {
    Vector3 v = p_euler;

    /*if (v.x == 90) v.x -= 0.001;
    else if (v.x == 0) v.x += 0.001;

    if (v.y == 90) v.y -= 0.001;
    else if (v.y == 0) v.y += 0.001;

    if (v.z == 90) v.z -= 0.001;
    else if (v.z == 0) v.z += 0.001;*/

    this->self = glm::radians(v.ToGLM());
    //this->self = p_euler.ToGLM();
}

Framework::Helper::Math::Vector3
Framework::Helper::Math::Quaternion::operator*(const Framework::Helper::Math::Vector3 &v) const {
    glm::vec3 rot = EulerAngle().ToGLM();

    glm::fquat q = glm::vec3(
            rot.x,
            rot.y,
            -rot.z
    );

    return q * v.ToGLM();
}

Framework::Helper::Math::Quaternion
Framework::Helper::Math::Quaternion::Rotate(const Framework::Helper::Math::Vector3 &v) const {
    if (v.Empty())
        return *this;

    glm::quat q = glm::rotate(self, 1.f, glm::radians(glm::vec3(v.x, v.y, v.z)));
    return Framework::Helper::Math::Quaternion(q);
}

