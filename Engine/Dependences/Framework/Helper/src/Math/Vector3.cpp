//
// Created by Nikita on 01.03.2021.
//

#include "Math/Vector3.h"
#include <Math/Quaternion.h>
#include <glm/detail/type_quat.hpp>
#include <limits>
#include <algorithm>
#include <glm/gtc/quaternion.hpp>

//Framework::Helper::Math::Vector3::Vector3(const Framework::Helper::Math::Quaternion &q) {
//    Vector3 v = q.EulerAngle();
//    this->x = v.x;
//    this->y = v.y;
//    this->z = v.z;
//}
Framework::Helper::Math::Vector3 Framework::Helper::Math::Vector3::Rotate(const Framework::Helper::Math::Quaternion &q) const {
    // Extract the vector part of the quaternion
    Vector3 u(q.self.x, q.self.y, q.self.z);

    // Extract the scalar part of the quaternion
    double s = q.self.w;

    Vector3 v = *this;

    // Do the math
    return u * 2.0f * Dot(u, v)
             + v * (s*s - Dot(u, u))
             + Cross(u, v) * 2.0f * s;
}

