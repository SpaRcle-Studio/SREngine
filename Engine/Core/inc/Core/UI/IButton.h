//
// Created by innerviewer on 2024-01-12.
//
#ifndef SR_ENGINE_IBUTTON_H
#define SR_ENGINE_IBUTTON_H

#include <Utils/ECS/Component.h>

namespace SR_GRAPH_NS {
    class RenderScene;
    class IColorBufferPass;
}

namespace SR_CORE_UI_NS {
    class IButton : public SR_UTILS_NS::Component {
        using Super = SR_UTILS_NS::Component;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderScene>;
    public:
        IButton();

    public:
        SR_NODISCARD bool IsHovered();

    protected:
        SR_GRAPH_NS::IColorBufferPass* GetIColorBufferPass();

    private:
        SR_GTYPES_NS::Mesh3D* m_mesh = nullptr;
        RenderScenePtr m_renderScene;
    };
}

#endif //SR_ENGINE_IBUTTON_H
