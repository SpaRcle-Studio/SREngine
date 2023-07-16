//
// Created by Monika on 22.05.2023.
//

#include <Graphics/Render/RenderScene.h>
#include <Graphics/Lighting/LightSystem.h>

namespace SR_GRAPH_NS {
    LightSystem::LightSystem(RenderScenePtr pRenderScene)
        : SR_UTILS_NS::NonCopyable()
        , m_renderScene(pRenderScene)
    {
        // float angle = glm::radians(3.f * 360.0f);
        // float radius = 20.0f;
        // m_position = glm::vec3(cos(angle) * radius, -radius, sin(angle) * radius);
    }

    LightSystem::~LightSystem() {
        SRAssert(m_directionalLights.empty());
        SRAssert(m_pointLights.empty());
    }

    void LightSystem::Register(ILightComponent* pLightComponent) {
        if (!pLightComponent) {
            SRHalt("LightSystem::Register() : PointLight is nullptr!");
            return;
        }

        switch (pLightComponent->GetLightType()) {
            case LightType::Directional:
                m_directionalLights.insert(dynamic_cast<DirectionalLight*>(pLightComponent));
                break;
            case LightType::Point:
                m_pointLights.insert(dynamic_cast<PointLight*>(pLightComponent));
                break;
            case LightType::Area:
                m_areaLights.insert(dynamic_cast<AreaLight*>(pLightComponent));
                break;
            case LightType::Spot:
                m_spotLights.insert(dynamic_cast<SpotLight*>(pLightComponent));
                break;
            case LightType::Probe:
                m_probeLights.insert(dynamic_cast<ProbeLight*>(pLightComponent));
                break;
        }

        m_renderScene->SetDirty();
    }

    void LightSystem::Remove(ILightComponent* pLightComponent) {
        switch (pLightComponent->GetLightType()) {
            case LightType::Directional:
                m_directionalLights.erase(dynamic_cast<DirectionalLight*>(pLightComponent));
                break;
            case LightType::Point:
                m_pointLights.erase(dynamic_cast<PointLight*>(pLightComponent));
                break;
            case LightType::Area:
                m_areaLights.erase(dynamic_cast<AreaLight*>(pLightComponent));
                break;
            case LightType::Spot:
                m_spotLights.erase(dynamic_cast<SpotLight*>(pLightComponent));
                break;
            case LightType::Probe:
                m_probeLights.erase(dynamic_cast<ProbeLight*>(pLightComponent));
                break;
        }
    }

}