

# File PhysXRaycast3DImpl.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**PhysX**](dir_3ad88c97ba0c5fb710f861c6ad44644a.md) **>** [**PhysXRaycast3DImpl.h**](PhysXRaycast3DImpl_8h.md)

[Go to the documentation of this file](PhysXRaycast3DImpl_8h.md)


```C++
//
// Created by innerviewer on 2/16/2023.
//

#ifndef SR_ENGINE_PHYSXRAYCAST3DIMPL_H
#define SR_ENGINE_PHYSXRAYCAST3DIMPL_H

#include <Physics/3D/Raycast3DImpl.h>
#include <Utils/Common/RaycastHit.h>

namespace SR_PHYSICS_NS {
    class PhysXRaycast3DImpl : public Raycast3DImpl {
        using Super = Raycast3DImpl;
    public:
        explicit PhysXRaycast3DImpl(SR_PHYSICS_NS::PhysicsWorld* world)
            : Super(world)
        { }

        RaycastHits Cast(const SR_MATH_NS::FVector3 &origin, const SR_MATH_NS::FVector3 &direction, float_t maxDistance, uint32_t maxHits) override;
    };
}

#endif //SR_ENGINE_PHYSXRAYCAST3DIMPL_H
```


