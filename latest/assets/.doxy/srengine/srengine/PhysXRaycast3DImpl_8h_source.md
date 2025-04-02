

# File PhysXRaycast3DImpl.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysX**](dir_ff2872f47b85400c7459df934950f633.md) **>** [**PhysXRaycast3DImpl.h**](PhysXRaycast3DImpl_8h.md)

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


