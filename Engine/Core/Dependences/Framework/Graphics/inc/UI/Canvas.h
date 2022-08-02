//
// Created by Monika on 01.08.2022.
//

#ifndef SRENGINE_CANVAS_H
#define SRENGINE_CANVAS_H

#include <Utils/ECS/Component.h>
#include <Render/RenderScene.h>

namespace SR_GRAPH_NS {
    class RenderContext;
    class RenderScene;
}

namespace SR_GRAPH_NS::UI {
    class Canvas : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1000);
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;
    public:
        Canvas();
        ~Canvas() override = default;

    public:
        static SR_UTILS_NS::Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        void OnAttached() override;
        void OnWindowResized(const SR_MATH_NS::IVector2 &size) override;
        void OnDestroy() override;

        SR_NODISCARD SR_MATH_NS::IVector2 GetWindowSize() const;

    private:
        void TransformUI();

    private:
        RenderContextPtr m_context;
        RenderScenePtr m_renderScene;

    };
}

#endif //SRENGINE_CANVAS_H
