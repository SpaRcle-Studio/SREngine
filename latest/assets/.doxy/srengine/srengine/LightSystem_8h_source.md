

# File LightSystem.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Lighting**](dir_b94c38cb0a82e06a7dce50d9e5876b41.md) **>** [**LightSystem.h**](LightSystem_8h.md)

[Go to the documentation of this file](LightSystem_8h.md)


```C++
//
// Created by Monika on 22.05.2023.
//

#ifndef SR_ENGINE_LIGHTSYSTEM_H
#define SR_ENGINE_LIGHTSYSTEM_H

#include <Graphics/Lighting/LightType.h>

#include <Utils/Math/Vector3.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_GRAPH_NS {
    class RenderScene;
    class ILightComponent;

    class LightSystem : SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
    public:
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::RenderScene>;

        explicit LightSystem(RenderScenePtr pRenderScene);
        ~LightSystem() override;

        void Register(ILightComponent* pLightComponent);
        void Remove(ILightComponent* pLightComponent);
        void OnLightTransformChanged(ILightComponent* pLightComponent);

        SR_NODISCARD SR_MATH_NS::FVector3 GetDirectionalLightDirection() const noexcept;

    public:
        RenderScenePtr m_renderScene;

        std::array<std::set<ILightComponent*>, SR_UTILS_NS::EnumTraits<LightType>::NumItems> m_lights;

    private:
        SR_MATH_NS::FVector3 m_directionalLightDir;

    };
}

#endif //SR_ENGINE_LIGHTSYSTEM_H
```


