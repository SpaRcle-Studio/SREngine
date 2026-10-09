//
// Created by innerviewer on 2/13/2023.
//

#ifndef SR_ENGINE_RAYCAST3D_H
#define SR_ENGINE_RAYCAST3D_H

#include <Physics/Raycast.h>

#include <Utils/Math/Vector3.h>
#include <Utils/Common/Singleton.h>
#include <Utils/TypeTraits/SRClass.h>

namespace SR_PHYSICS_NS {
    /// @noCopyable @noMovable
    class RayCast3D final : public SR_UTILS_NS::Singleton<RayCast3D>, public RayCast, public SR_UTILS_NS::SRClass {
        SR_REGISTER_SINGLETON(RayCast3D)
        SR_CLASS()
    public:
        SR_NODISCARD void Cast(SR_UTILS_NS::RayCastHits& hits, const SR_MATH_NS::FVector3 &origin, const SR_MATH_NS::FVector3 &direction, float_t maxDistance, uint32_t maxHits, const SR_UTILS_NS::LayerMask& layerMask = SR_UTILS_NS::LayerMask::Any());
        SR_NODISCARD void Cast(SR_UTILS_NS::RayCastHits& hits, const SR_MATH_NS::FVector3 &origin, const SR_MATH_NS::FVector3 &direction, float_t maxDistance, const SR_UTILS_NS::LayerMask& layerMask = SR_UTILS_NS::LayerMask::Any());
        /// @method
        SR_NODISCARD SR_UTILS_NS::Optional<SR_UTILS_NS::RayCastHit> CastSingle(const SR_MATH_NS::FVector3& origin, const SR_MATH_NS::FVector3& direction, float_t maxDistance, const SR_UTILS_NS::LayerMask& layerMask = SR_UTILS_NS::LayerMask::Any());

    };
}

#endif //SR_ENGINE_RAYCAST3D_H
