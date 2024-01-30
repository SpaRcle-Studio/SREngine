//
// Created by Monika on 22.05.2023.
//

#ifndef SR_ENGINE_I_RENDER_COMPONENT_H
#define SR_ENGINE_I_RENDER_COMPONENT_H

#include <Utils/ECS/Component.h>

namespace SR_GTYPES_NS {
    class Camera;

    class IRenderComponent : public SR_UTILS_NS::Component {
    public:
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
        using CameraPtr = SR_HTYPES_NS::SharedPtr<Camera>;
        using Super = SR_UTILS_NS::Component;

    protected:
        IRenderComponent() = default;

    public:
        void OnEnable() override;
        void OnDisable() override;

        SR_NODISCARD CameraPtr GetCamera() const;
        SR_NODISCARD RenderScenePtr TryGetRenderScene() const;
        SR_NODISCARD RenderScenePtr GetRenderScene() const;

    protected:
        mutable RenderScenePtr m_renderScene;

    };
}

#endif //SR_ENGINE_I_RENDER_COMPONENT_H
