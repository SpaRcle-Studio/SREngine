//
// Created by Monika on 21.03.2024.
//

#include <Core/GUI/SceneTools.h>

namespace SR_CORE_GUI_NS {
    void SceneTools::Init() {
        AddElement("2D")
            .SetIsActive([this]() { return m_gizmoOperationFlag & SR_GRAPH_UI_NS::GizmoOperation::Z; })
            .SetOnClick([this](bool isActive) { SetGizmo2D(!isActive); });

        AddElement("T")
            .SetIsActive([this]() { return m_gizmoOperationFlag & SR_GRAPH_UI_NS::GizmoOperation::Translate; })
            .SetOnClick([this](bool isActive) {
                if (isActive) { SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::None); }
                else { SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::Translate); }
            });

        AddElement("R")
            .SetIsActive([this]() { return m_gizmoOperationFlag & SR_GRAPH_UI_NS::GizmoOperation::Rotate; })
            .SetOnClick([this](bool isActive) {
                if (isActive) { SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::None); }
                else { SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::Rotate); }
            });

        AddElement("S")
            .SetIsActive([this]() { return m_gizmoOperationFlag & SR_GRAPH_UI_NS::GizmoOperation::Scale; })
            .SetOnClick([this](bool isActive) {
                if (isActive) { SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::None); }
                else { SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::Scale); }
            });

        Super::Init();
    }

    void SceneTools::SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperationFlag operation) {
        m_gizmoOperationFlag &= ~SR_GRAPH_UI_NS::GizmoOperation::Translate;
        m_gizmoOperationFlag &= ~SR_GRAPH_UI_NS::GizmoOperation::Rotate;
        m_gizmoOperationFlag &= ~SR_GRAPH_UI_NS::GizmoOperation::Scale;
        m_gizmoOperationFlag &= ~SR_GRAPH_UI_NS::GizmoOperation::Bounds;

        if (operation != SR_GRAPH_UI_NS::GizmoOperation::None) {
            m_gizmoOperationFlag |= operation;
        }
    }

    void SceneTools::SetGizmo2D(bool isActive) {
        if (isActive) {
            m_gizmoOperationFlag |= SR_GRAPH_UI_NS::GizmoOperation::Z;
        }
        else {
            m_gizmoOperationFlag &= ~SR_GRAPH_UI_NS::GizmoOperation::Z;
        }
    }
}
