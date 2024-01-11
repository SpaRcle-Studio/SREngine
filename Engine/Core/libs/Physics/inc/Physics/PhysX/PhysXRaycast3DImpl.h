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
