

# File Bullet3PhysicsLib.h

[**File List**](files.md) **>** [**Bullet3**](dir_b49b257c816fcf8e49fc788b011f4b07.md) **>** [**Bullet3PhysicsLib.h**](Bullet3PhysicsLib_8h.md)

[Go to the documentation of this file](Bullet3PhysicsLib_8h.md)


```C++
//
// Created by Monika on 22.11.2022.
//

#ifndef SR_ENGINE_BULLET3PHYSICSLIB_H
#define SR_ENGINE_BULLET3PHYSICSLIB_H

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

#endif //SR_ENGINE_BULLET3PHYSICSLIB_H
```


