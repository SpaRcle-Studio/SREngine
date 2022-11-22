//
// Created by Monika on 22.11.2022.
//

#ifndef SRENGINE_BULLET3PHYSICSLIB_H
#define SRENGINE_BULLET3PHYSICSLIB_H

#include <Physics/PhysicsLib.h>

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btBox2dShape.h>

#include <LinearMath/btVector3.h>
#include <LinearMath/btAlignedObjectArray.h>

namespace SR_PHYSICS_UTILS_NS {
    SR_MAYBE_UNUSED static btVector3 FV3ToBtV3(const SR_MATH_NS::FVector3 &vector3) {
        return btVector3(vector3.x, vector3.y, vector3.z);
    }

    SR_MAYBE_UNUSED static SR_MATH_NS::FVector3 BtV33ToFV(const btVector3 &vector3) {
        return SR_MATH_NS::FVector3(vector3.x(), vector3.y(), vector3.z());
    }
}

#endif //SRENGINE_BULLET3PHYSICSLIB_H
