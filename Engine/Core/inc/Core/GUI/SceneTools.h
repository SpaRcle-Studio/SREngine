//
// Created by Monika on 21.03.2024.
//

#ifndef SR_ENGINE_CORE_SCENE_TOOLS_H
#define SR_ENGINE_CORE_SCENE_TOOLS_H

#include <Core/GUI/EditorGizmo.h>

#include <Graphics/GUI/WidgetContainer.h>

namespace SR_GRAPH_UI_NS {
    class Gizmo;
}

namespace SR_CORE_GUI_NS {
    SR_ENUM_NS_CLASS_T(EditorSceneViewMode, uint8_t,
        FreeAspect, WindowSize
    );

    class SceneTools : public SR_GRAPH_GUI_NS::WidgetContainer {
        using Super = SR_GRAPH_GUI_NS::WidgetContainer;
    public:
        SceneTools()
            : Super("SceneTools")
        {
            SetSize(SR_MATH_NS::IVector2(0, 22));
        }

    public:
        void Init() override;

        SR_NODISCARD SR_GRAPH_UI_NS::GizmoOperationFlag GetGizmoOperation() const noexcept { return m_gizmoOperationFlag; }
        SR_NODISCARD SR_GRAPH_UI_NS::GizmoMode GetGizmoMode() const noexcept { return m_gizmoMode; }
        SR_NODISCARD float_t GetCameraVelocityFactor() const noexcept { return m_cameraVelocityFactor; }
        SR_NODISCARD EditorSceneViewMode GetViewMode() const noexcept { return m_viewMode; }
        SR_NODISCARD bool IsGizmo3D() const noexcept { return m_gizmoOperationFlag & SR_GRAPH_UI_NS::GizmoOperation::Z; }

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* pData) override;

    private:
        void SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperationFlag operation);
        void SetGizmoMode(SR_GRAPH_UI_NS::GizmoMode mode);

        SR_HTYPES_NS::SharedPtr<SR_CORE_GUI_NS::EditorGizmo> FindGizmo() const;

    private:
        SR_GRAPH_UI_NS::GizmoOperationFlag m_gizmoOperationFlag = SR_GRAPH_UI_NS::GizmoOperation::None;
        SR_GRAPH_UI_NS::GizmoMode m_gizmoMode = SR_GRAPH_UI_NS::GizmoMode::Local;
        EditorSceneViewMode m_viewMode = EditorSceneViewMode::FreeAspect;
        float_t m_cameraVelocityFactor = 1.f;

    };
}

#endif //SR_ENGINE_CORE_SCENE_TOOLS_H
