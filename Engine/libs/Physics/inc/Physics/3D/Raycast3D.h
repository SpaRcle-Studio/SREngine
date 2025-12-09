//
// Created by innerviewer on 2/13/2023.
//

#ifndef SR_ENGINE_RAYCAST3D_H
#define SR_ENGINE_RAYCAST3D_H

#include <Physics/Raycast.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Common/Singleton.h>

namespace SR_PHYSICS_NS {
    class Raycast3D final : public SR_UTILS_NS::Singleton<Raycast3D>, public Raycast {
        SR_REGISTER_SINGLETON(Raycast3D)
    public:
        SR_NODISCARD RaycastHits Cast(const SR_MATH_NS::FVector3 &origin, const SR_MATH_NS::FVector3 &direction, float_t maxDistance, uint32_t maxHits, const SR_UTILS_NS::LayerMask& layerMask = SR_UTILS_NS::LayerMask::Any());
        SR_NODISCARD RaycastHits Cast(const SR_MATH_NS::FVector3 &origin, const SR_MATH_NS::FVector3 &direction, float_t maxDistance, const SR_UTILS_NS::LayerMask& layerMask = SR_UTILS_NS::LayerMask::Any());
        SR_NODISCARD std::optional<SR_UTILS_NS::RaycastHit> CastSingle(const SR_MATH_NS::FVector3& origin, const SR_MATH_NS::FVector3& direction, float_t maxDistance, const SR_UTILS_NS::LayerMask& layerMask = SR_UTILS_NS::LayerMask::Any());

    };
}

#endif //SR_ENGINE_RAYCAST3D_H
