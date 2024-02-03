//
// Created by Monika on 03.02.2024.
//

#include <Core/GUI/EditorGizmo.h>

namespace SR_CORE_GUI_NS {
    EditorGizmo::EditorGizmo()
        : Super()
    { }

    SR_MATH_NS::Matrix4x4 EditorGizmo::GetGizmoMatrix() const {
        if (!m_hierarchy || m_hierarchy->GetSelected().size() != 1) {
            return SR_MATH_NS::Matrix4x4::Identity();
        }

        return (*m_hierarchy->GetSelected().begin())->GetTransform()->GetMatrix();
    }

    void EditorGizmo::OnGizmoTranslated(const SR_MATH_NS::FVector3& delta) {
        if (!m_hierarchy) {
            return;
        }

        for (auto&& pGameObject : m_hierarchy->GetSelected()) {
            pGameObject->GetTransform()->Translate(delta);
        }
    }
}