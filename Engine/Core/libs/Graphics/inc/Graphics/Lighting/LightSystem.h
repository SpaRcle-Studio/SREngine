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
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderScene>;

        explicit LightSystem(RenderScenePtr pRenderScene);
        ~LightSystem() override;

        void Register(ILightComponent* pLightComponent);
        void Remove(ILightComponent* pLightComponent);

    public:
        SR_MATH_NS::FVector3 m_position = SR_MATH_NS::FVector3(20, 60, 5);
        RenderScenePtr m_renderScene;
        std::set<DirectionalLight*> m_directionalLights;
        std::set<PointLight*> m_pointLights;
        std::set<AreaLight*> m_areaLights;
        std::set<SpotLight*> m_spotLights;
        std::set<ProbeLight*> m_probeLights;
    };
}

#endif //SR_ENGINE_LIGHTSYSTEM_H
