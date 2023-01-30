//
// Created by innerviewer on 21.01.2023.
//

#ifndef SRENGINE_COLLISIONDATA_H
#define SRENGINE_COLLISIONDATA_H

#include <Utils/Math/Vector3.h>

namespace SR_UTILS_NS {
    struct CollisionData {
        void* pHandler = nullptr;
        SR_MATH_NS::FVector3 point;
        SR_MATH_NS::FVector3 impulse;
    };
}

#endif //SRENGINE_COLLISIONDATA_H
