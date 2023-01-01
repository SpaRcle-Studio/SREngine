//
// Created by Monika on 01.08.2022.
//

#ifndef SRENGINE_CANVAS_H
#define SRENGINE_CANVAS_H

#include <Utils/ECS/Component.h>
#include <Graphics/Render/RenderScene.h>

namespace SR_GRAPH_NS {
    class RenderContext;
    class RenderScene;
}

namespace SR_GRAPH_NS::UI {
    class Canvas : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(Canvas);
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;
    public:
        Canvas();
        ~Canvas() override = default;

    public:
        static SR_UTILS_NS::Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        bool ExecuteInEditMode() const override;
        void OnAttached() override;
        void OnDestroy() override;

    protected:
        void Update(float_t dt) override;

    private:
        SR_MATH_NS::UVector2 m_size;

        RenderContextPtr m_context;
        RenderScenePtr m_renderScene;

    };
}

#endif //SRENGINE_CANVAS_H
