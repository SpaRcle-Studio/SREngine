//
// Created by Monika on 21.03.2024.
//

#ifndef SR_ENGINE_CORE_SCENE_TOOLS_H
#define SR_ENGINE_CORE_SCENE_TOOLS_H

#include <Graphics/GUI/WidgetContainer.h>
#include <Graphics/UI/Gizmo.h>

namespace SR_CORE_GUI_NS {
    class SceneTools : public SR_GRAPH_GUI_NS::WidgetContainer {
        using Super = SR_GRAPH_GUI_NS::WidgetContainer;
    public:
        SceneTools()
            : Super("SceneTools")
        {
            SetSize(100);
        }

    public:
        void Init() override;

    private:
        void SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperationFlag operation);
        void SetGizmo2D(bool isActive);

    private:
        SR_GRAPH_UI_NS::GizmoOperationFlag m_gizmoOperationFlag = SR_GRAPH_UI_NS::GizmoOperation::None;

    };
}

#endif //SR_ENGINE_CORE_SCENE_TOOLS_H
