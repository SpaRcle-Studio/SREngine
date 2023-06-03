//
// Created by innerviewer on 2/13/2023.
//

#include <Physics/3D/Raycast3D.h>
#include <Physics/PhysicsWorld.h>
#include <Physics/PhysX/PhysXRaycast3DImpl.h>

namespace SR_PHYSICS_NS {
    Raycast3D::RaycastHits Raycast3D::Cast(const SR_MATH_NS::FVector3 &origin, const SR_MATH_NS::FVector3 &direction, float_t maxDistance, uint32_t maxHits){
        return m_world->GetRaycast3DImpl()->Cast(origin, direction, maxDistance, maxHits);
    }

    Raycast3D::RaycastHits Raycast3D::Cast(const SR_MATH_NS::FVector3 &origin, const SR_MATH_NS::FVector3 &direction, float_t maxDistance){
        return m_world->GetRaycast3DImpl()->Cast(origin, direction, maxDistance, 1);
    }
}