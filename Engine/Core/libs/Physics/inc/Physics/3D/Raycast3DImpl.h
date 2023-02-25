//
// Created by innerviewer on 2/16/2023.
//

#ifndef SRENGINE_RAYCAST3DIMPL_H
#define SRENGINE_RAYCAST3DIMPL_H

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

#endif //SRENGINE_RAYCAST3DIMPL_H
