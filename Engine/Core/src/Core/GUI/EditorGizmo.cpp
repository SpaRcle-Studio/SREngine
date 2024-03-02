//
// Created by Monika on 03.02.2024.
//

#include <Core/GUI/EditorGizmo.h>

namespace SR_CORE_GUI_NS {
    EditorGizmo::EditorGizmo()
        : Super()
    { }

    SR_MATH_NS::Matrix4x4 EditorGizmo::GetGizmoMatrix() const {
        if (!m_hierarchy || m_hierarchy->GetSelected().empty()) {
            return SR_MATH_NS::Matrix4x4::Identity();
        }

        if (m_hierarchy->GetSelected().size() == 1) {
            auto&& pTransform = (*m_hierarchy->GetSelected().begin())->GetTransform();
            return pTransform->GetMatrix();
        }

        SR_MATH_NS::FVector3 center;

        for (auto&& pGameObject : m_hierarchy->GetSelected()) {
            center += pGameObject->GetTransform()->GetMatrix().GetTranslate();
        }

        center /= m_hierarchy->GetSelected().size();

        return SR_MATH_NS::Matrix4x4::FromTranslate(center);
    }

    void EditorGizmo::OnGizmoTranslated(const SR_MATH_NS::FVector3& delta) {
        if (!m_hierarchy) {
            return;
        }

        for (auto&& pGameObject : m_hierarchy->GetSelected()) {
            auto&& scale = SR_MATH_NS::FVector3::One();

            auto&& pParentTransform = pGameObject->GetTransform()->GetParentTransform();
            if (pParentTransform) {
                scale = pParentTransform->GetMatrix().GetScale();
            }

            pGameObject->GetTransform()->Translate(pGameObject->GetTransform()->GetMatrix().GetQuat().Inverse() * (delta / scale));
        }
    }

    void EditorGizmo::OnGizmoRotated(const SR_MATH_NS::Quaternion& delta) {
        if (!m_hierarchy) {
            return;
        }

        for (auto&& pGameObject : m_hierarchy->GetSelected()) {
            pGameObject->GetTransform()->Rotate(delta);
        }
    }

    SR_GRAPH_UI_NS::GizmoMode EditorGizmo::GetMode() const {
        if (m_hierarchy->GetSelected().size() > 1) {
            return SR_GRAPH_UI_NS::GizmoMode::Global;
        }

        return Super::GetMode();
    }

    bool EditorGizmo::IsGizmoAvailable() const {
        return m_hierarchy && !m_hierarchy->GetSelected().empty();
    }
}