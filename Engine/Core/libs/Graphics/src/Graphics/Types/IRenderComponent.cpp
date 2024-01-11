//
// Created by Monika on 22.05.2023.
//

#include <Utils/World/Scene.h>

#include <Graphics/Types/IRenderComponent.h>
#include <Graphics/Render/RenderScene.h>

namespace SR_GTYPES_NS {
    void IRenderComponent::OnEnable() {
        if (auto&& renderScene = TryGetRenderScene()) {
            renderScene->SetDirty();
        }

        Super::OnEnable();
    }

    void IRenderComponent::OnDisable() {
        if (auto&& renderScene = TryGetRenderScene()) {
            renderScene->SetDirty();
        }

        Super::OnDisable();
    }

    IRenderComponent::RenderScenePtr IRenderComponent::TryGetRenderScene() {
        if (m_renderScene.Valid()) {
            return m_renderScene;
        }

        auto&& pScene = TryGetScene();
        if (!pScene) {
            return m_renderScene;
        }

        m_renderScene = pScene->Do<RenderScenePtr>([](SR_WORLD_NS::Scene* ptr) {
            return ptr->GetDataStorage().GetValue<RenderScenePtr>();
        }, RenderScenePtr());

        return m_renderScene;
    }

    IRenderComponent::RenderScenePtr IRenderComponent::GetRenderScene() {
        if (auto&& pRenderScene = TryGetRenderScene()) {
            return pRenderScene;
        }

        SRHalt("Invalid render scene!");

        return RenderScenePtr();
    }
}