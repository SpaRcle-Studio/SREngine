//
// Created by Nikita on 13.12.2020.
//

#include <Graphics/Lighting/LightSystem.h>
#include <Graphics/Lighting/DirectionalLight.h>

namespace SR_GRAPH_NS {

    void DirectionalLight::OnAttached() {
        GetRenderScene().Do([this](SR_GRAPH_NS::RenderScene *ptr) {
            ptr->GetLightSystem()->Register(this);
        });
        Component::OnAttached();
    }
}
