//
// Created by innerviewer on 2/13/2023.
//

#include <Physics/3D/Raycast3D.h>
#include <Physics/PhysicsWorld.h>
#include <Physics/PhysX/PhysXRaycast3DImpl.h>

#include <Codegen/Raycast3D.generated.hpp>

namespace SR_PHYSICS_NS {
    SR_MAYBE_UNUSED_VAR RayCast3D::Instance();

    SR_UTILS_NS::RayCastHits RayCast3D::Cast(const SR_MATH_NS::FVector3 &origin, const SR_MATH_NS::FVector3 &direction, float_t maxDistance, uint32_t maxHits, const SR_UTILS_NS::LayerMask& layerMask) {
        SR_TRACY_ZONE;
        return m_world->GetRayCast3DImpl()->Cast(origin, direction, maxDistance, maxHits, layerMask);
    }

    SR_UTILS_NS::RayCastHits RayCast3D::Cast(const SR_MATH_NS::FVector3 &origin, const SR_MATH_NS::FVector3 &direction, float_t maxDistance, const SR_UTILS_NS::LayerMask& layerMask) {
        SR_TRACY_ZONE;
        return m_world->GetRayCast3DImpl()->Cast(origin, direction, maxDistance, 1, layerMask);
    }

    SR_UTILS_NS::Optional<SR_UTILS_NS::RayCastHit> RayCast3D::CastSingle(const SR_MATH_NS::FVector3& origin, const SR_MATH_NS::FVector3& direction, float_t maxDistance, const SR_UTILS_NS::LayerMask& layerMask) {
        SR_TRACY_ZONE;
        auto hits = Cast(origin, direction, maxDistance, 1, layerMask);
        if (hits.empty()) {
            return {};
        }
        return hits[0];
    }
}