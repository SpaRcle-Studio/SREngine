

# File Raycast3DImpl.h

[**File List**](files.md) **>** [**3D**](dir_4a56e980c41c37d86fa22e353a593c22.md) **>** [**Raycast3DImpl.h**](Raycast3DImpl_8h.md)

[Go to the documentation of this file](Raycast3DImpl_8h.md)


```C++
//
// Created by innerviewer on 2/16/2023.
//

#ifndef SR_ENGINE_RAYCAST3DIMPL_H
#define SR_ENGINE_RAYCAST3DIMPL_H

#include <Physics/RaycastImpl.h>

namespace SR_PHYSICS_NS {
    class Raycast3DImpl : public RaycastImpl{
        using Super = RaycastImpl;
    public:
        explicit Raycast3DImpl(SR_PHYSICS_NS::PhysicsWorld* world)
            : Super(world)
        { }

        virtual RaycastHits Cast(const SR_MATH_NS::FVector3 &origin, const SR_MATH_NS::FVector3 &direction, float_t maxDistance, uint32_t maxHits) = 0;
    };
}

#endif //SR_ENGINE_RAYCAST3DIMPL_H
```


