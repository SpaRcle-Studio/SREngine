

# File ILightComponent.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Lighting**](dir_84c906e4a9232501b7e5ce92a32284b3.md) **>** [**ILightComponent.h**](ILightComponent_8h.md)

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


