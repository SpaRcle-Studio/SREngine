

# File FrustumCulling.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**FrustumCulling.h**](FrustumCulling_8h.md)

[Go to the documentation of this file](FrustumCulling_8h.md)


```C++
//
// Created by Monika on 07.04.2024.
//

#ifndef SR_ENGINE_GRAPHICS_FRUSTUM_CULLING_H
#define SR_ENGINE_GRAPHICS_FRUSTUM_CULLING_H

#include <Graphics/macros.h>

#include <Utils/Common/NonCopyable.h>
#include <Utils/Math/Matrix4x4.h>

namespace SR_GRAPH_NS {
    struct FrustumPlane {
        SR_MATH_NS::FVector3 normal = { 0.f, 1.f, 0.f };
        float_t distance = 0.f;
    };

    struct Frustum {
        FrustumPlane topFace;
        FrustumPlane bottomFace;

        FrustumPlane rightFace;
        FrustumPlane leftFace;

        FrustumPlane farFace;
        FrustumPlane nearFace;
    };

    class FrustumCulling : public SR_UTILS_NS::NonCopyable {
    public:
        FrustumCulling() = default;

        //void UpdateFrustum(const SR_GTYPES_NS::Camera& camera) noexcept;
        //SR_NODISCARD bool IsSphereInFrustum(const SR_GTYPES_NS::Vector3& center, float_t radius) const noexcept;
        //SR_NODISCARD bool IsBoxInFrustum(const SR_GTYPES_NS::Vector3& min, const SR_GTYPES_NS::Vector3& max) const noexcept;

    private:
        SR_MATH_NS::FVector4 m_planes[6];

    };

}

#endif //SR_ENGINE_GRAPHICS_FRUSTUM_CULLING_H
```


