

# File LightSystem.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Lighting**](dir_84c906e4a9232501b7e5ce92a32284b3.md) **>** [**LightSystem.h**](LightSystem_8h.md)

[Go to the documentation of this file](LightSystem_8h.md)


```C++
//
// Created by Monika on 22.05.2023.
//

#ifndef SR_ENGINE_LIGHTSYSTEM_H
#define SR_ENGINE_LIGHTSYSTEM_H

#include <Graphics/Pipeline/Pipeline.h>

namespace SR_GRAPH_NS {
    class DirectionalLight;
    class PointLight;
    class AreaLight;
    class SpotLight;
    class ProbeLight;
    class RenderScene;
    class ILightComponent;

    class LightSystem : SR_UTILS_NS::NonCopyable {
    public:
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::RenderScene>;

        explicit LightSystem(RenderScenePtr pRenderScene);
        ~LightSystem() override;

        void Register(ILightComponent* pLightComponent);
        void Remove(ILightComponent* pLightComponent);

        SR_NODISCARD const SR_MATH_NS::FVector3& GetDirectionalLightPosition() const noexcept { return m_position; }
        void SetDirectionalLightPosition(const SR_MATH_NS::FVector3& position) noexcept;

    public:
        RenderScenePtr m_renderScene;
        std::set<DirectionalLight*> m_directionalLights;
        std::set<PointLight*> m_pointLights;
        std::set<AreaLight*> m_areaLights;
        std::set<SpotLight*> m_spotLights;
        std::set<ProbeLight*> m_probeLights;

    private:
        SR_MATH_NS::FVector3 m_position = SR_MATH_NS::FVector3(20, 60, 5);

    };
}

#endif //SR_ENGINE_LIGHTSYSTEM_H
```


