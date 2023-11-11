//
// Created by Monika on 22.05.2023.
//

#ifndef SRENGINE_IRENDERCOMPONENT_H
#define SRENGINE_IRENDERCOMPONENT_H

#include <Utils/ECS/Component.h>

namespace SR_GTYPES_NS {
    class IRenderComponent : public SR_UTILS_NS::Component {
    public:
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
        using Super = SR_UTILS_NS::Component;

    protected:
        IRenderComponent() = default;

    public:
        void OnEnable() override;
        void OnDisable() override;

        SR_NODISCARD RenderScenePtr TryGetRenderScene();
        SR_NODISCARD RenderScenePtr GetRenderScene();

    protected:
        RenderScenePtr m_renderScene;

    };
}

#endif //SRENGINE_IRENDERCOMPONENT_H
