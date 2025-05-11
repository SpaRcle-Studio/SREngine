

# File ILightComponent.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Lighting**](dir_b94c38cb0a82e06a7dce50d9e5876b41.md) **>** [**ILightComponent.h**](ILightComponent_8h.md)

[Go to the documentation of this file](ILightComponent_8h.md)


```C++
//
// Created by Monika on 13.12.2020.
//

#ifndef SR_ENGINE_ILIGHTCOMPONENT_H
#define SR_ENGINE_ILIGHTCOMPONENT_H

#include <Graphics/Types/IRenderComponent.h>
#include <Utils/Common/Enumerations.h>

namespace SR_GRAPH_NS {
    class RenderScene;

    SR_ENUM_NS_CLASS_T(LightType, uint8_t,
        Directional, Point, Spot, Area, Probe
    )

    SR_ENUM_NS_CLASS_T(ShadowType, uint8_t,
        Soft, Hard
    )

    class ILightComponent : public SR_GTYPES_NS::IRenderComponent {
    public:
        SR_NODISCARD SR_FORCE_INLINE bool ExecuteInEditMode() const override { return true; }
        SR_NODISCARD bool IsUpdatable() const noexcept override { return false; }
        SR_NODISCARD virtual LightType GetLightType() const = 0;

        void OnAttached() override;
        void OnDestroy() override;

    protected:
        float_t m_intensity = 1.f;
        float_t m_bounceIntensity = 1.f;
        ShadowType m_shadowType = ShadowType::Soft;

    };
}

#endif //SR_ENGINE_ILIGHTCOMPONENT_H
```


