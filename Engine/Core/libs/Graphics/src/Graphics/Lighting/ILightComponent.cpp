//
// Created by Nikita on 13.12.2020.
//

#include <Graphics/Lighting/LightSystem.h>
#include <Graphics/Lighting/ILightComponent.h>

namespace SR_GRAPH_NS {

    void ILightComponent::OnAttached() {
        GetRenderScene().Do([this](SR_GRAPH_NS::RenderScene *ptr) {
            ptr->GetLightSystem()->Register(this);
        });
        Component::OnAttached();
    }

    void ILightComponent::OnDestroy() {
        RenderScene::Ptr renderScene = TryGetRenderScene();

        Component::OnDestroy();

        if (renderScene) {
            renderScene->GetLightSystem()->Remove(this);
        }
    }
}