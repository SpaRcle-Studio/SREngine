//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_PHYSICSLIB_H
#define SRENGINE_PHYSICSLIB_H

#include <Utils/macros.h>
#include <Utils/Common/Enumerations.h>

#include "btBulletDynamicsCommon.h"

#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"

namespace SR_PHYSICS_NS {
    SR_ENUM_CLASS(ShapeType,
        Box2D,
        Cylinder2D,
        Capsule2D,
        Sphere2D,

        Box3D,
        Cylinder3D,
        Capsule3D,
        Sphere3D,
    )
}

namespace SR_PHYSICS_NS::Tools {

}

#endif //SRENGINE_PHYSICSLIB_H
