//
// Created by Monika on 03.02.2024.
//

#include <Core/GUI/EditorGizmo.h>

namespace SR_CORE_GUI_NS {
    EditorGizmo::EditorGizmo()
        : Super()
    { }

    EditorGizmo::~EditorGizmo() {
        SR_SAFE_DELETE_PTR(m_marshal);
    }

    SR_MATH_NS::Matrix4x4 EditorGizmo::GetGizmoMatrix() const {
        if (!m_hierarchy || m_hierarchy->GetSelected().empty()) {
            return SR_MATH_NS::Matrix4x4::Identity();
        }

        if (m_hierarchy->GetSelected().size() == 1) {
            if (!(*m_hierarchy->GetSelected().begin())) {
                return SR_MATH_NS::Matrix4x4::Identity();
            }
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
            if (!pGameObject) {
                continue;
            }

            const auto invQuaternion = pGameObject->GetTransform()->GetMatrix().GetQuat().Inverse();

            if (IsGizmo2DSpace()) {
                const auto scale = pGameObject->GetTransform()->GetMatrix().GetScale();
                pGameObject->GetTransform()->Translate((delta / scale));
            }
            else {
                auto&& parentScale = SR_MATH_NS::FVector3::One();

                auto&& pParentTransform = pGameObject->GetTransform()->GetParentTransform();
                if (pParentTransform) {
                    parentScale = pParentTransform->GetMatrix().GetScale();
                }

                pGameObject->GetTransform()->Translate(invQuaternion * (delta / parentScale));
            }
        }
    }

    void EditorGizmo::OnGizmoRotated(const SR_MATH_NS::Quaternion& delta) {
        if (!m_hierarchy) {
            return;
        }

        for (auto&& pGameObject : m_hierarchy->GetSelected()) {
            if (!pGameObject) {
                continue;
            }

            if (IsLocal() || IsGizmo2DSpace()) {
                pGameObject->GetTransform()->Rotate(delta);
            }
            else {
                auto&& quaternion = pGameObject->GetTransform()->GetMatrix().GetQuat();
                pGameObject->GetTransform()->Rotate(quaternion.Inverse() * delta * quaternion);
            }
        }
    }

    SR_GRAPH_UI_NS::GizmoMode EditorGizmo::GetMode() const {
        if (m_hierarchy->GetSelected().size() > 1) {
            return SR_GRAPH_UI_NS::GizmoMode::Global;
        }

        return Super::GetMode();
    }

    bool EditorGizmo::IsGizmoAvailable() const {
        if (!m_hierarchy || m_hierarchy->GetSelected().empty()) {
            return false;
        }

        std::optional<bool> is2D;

        for (auto pGameObject : m_hierarchy->GetSelected()) {
            if (!pGameObject) {
                continue;
            }

            if (pGameObject == GetGameObject()) {
                return false;
            }

            if (!is2D.has_value()) {
                is2D = pGameObject->GetTransform()->GetMeasurement() == SR_UTILS_NS::Measurement::Space2D;
            }
            else if (is2D.value() != (pGameObject->GetTransform()->GetMeasurement() == SR_UTILS_NS::Measurement::Space2D)) {
                return false;
            }
        }

        return true;
    }

    void EditorGizmo::OnGizmoScaled(const SR_MATH_NS::FVector3& delta) {
        if (!m_hierarchy) {
            return;
        }

        for (auto&& pGameObject : m_hierarchy->GetSelected()) {
            if (!pGameObject) {
                continue;
            }

            auto&& pTransform = pGameObject->GetTransform();
            if (IsLocal()) {
                pTransform->Scale(delta);

                if (pTransform->GetScale().x <= SR_BIG_EPSILON) {
                    pTransform->SetScale(SR_MATH_NS::FVector3(SR_BIG_EPSILON, pTransform->GetScale().y, pTransform->GetScale().z));
                }

                if (pTransform->GetScale().y <= SR_BIG_EPSILON) {
                    pTransform->SetScale(SR_MATH_NS::FVector3(pTransform->GetScale().x, SR_BIG_EPSILON, pTransform->GetScale().z));
                }

                if (pTransform->GetScale().z <= SR_BIG_EPSILON) {
                    pTransform->SetScale(SR_MATH_NS::FVector3(pTransform->GetScale().x, pTransform->GetScale().y, SR_BIG_EPSILON));
                }
            }
            else {
                pGameObject->GetTransform()->GlobalSkew(delta);

                if (pTransform->GetSkew().x <= SR_BIG_EPSILON) {
                    pTransform->SetSkew(SR_MATH_NS::FVector3(SR_BIG_EPSILON, pTransform->GetSkew().y, pTransform->GetSkew().z));
                }

                if (pTransform->GetSkew().y <= SR_BIG_EPSILON) {
                    pTransform->SetSkew(SR_MATH_NS::FVector3(pTransform->GetSkew().x, SR_BIG_EPSILON, pTransform->GetSkew().z));
                }

                if (pTransform->GetSkew().z <= SR_BIG_EPSILON) {
                    pTransform->SetSkew(SR_MATH_NS::FVector3(pTransform->GetSkew().x, pTransform->GetSkew().y, SR_BIG_EPSILON));
                }
            }
        }
    }

    void EditorGizmo::BeginGizmo() {
        /// TODO: multiple selection

        if (!m_hierarchy || m_hierarchy->GetSelected().empty()) {
            return;
        }

        if (!*m_hierarchy->GetSelected().begin()) {
            return;
        }

        auto&& pGameObject = *m_hierarchy->GetSelected().begin();

        SR_SAFE_DELETE_PTR(m_marshal)
        m_marshal = pGameObject->GetTransform()->Save(SR_UTILS_NS::SavableContext(nullptr, SR_UTILS_NS::SavableFlagBits::SAVABLE_FLAG_NONE));

        Super::BeginGizmo();
    }

    void EditorGizmo::EndGizmo() {
        /// TODO: multiple selection

        if (!m_hierarchy || m_hierarchy->GetSelected().empty()) {
            return;
        }

        if (!*m_hierarchy->GetSelected().begin()) {
            return;
        }

        auto&& pGameObject = *m_hierarchy->GetSelected().begin();
        auto&& pEngine = dynamic_cast<EditorGUI*>(m_hierarchy->GetManager())->GetEngine();

        auto&& cmd = new SR_CORE_NS::Commands::GameObjectTransform(pEngine, pGameObject, m_marshal->CopyPtr());
        pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);

        SR_SAFE_DELETE_PTR(m_marshal)

        Super::EndGizmo();
    }

    void EditorGizmo::PrepareGizmo() {
        auto&& pGameObject = *m_hierarchy->GetSelected().begin();

        if (!pGameObject) {
            return;
        }

        if (pGameObject->GetTransform()->GetMeasurement() == SR_UTILS_NS::Measurement::Space2D) {
            if (SR_MATH_NS::IsMaskIncludedSubMask(GetOperation(), SR_GRAPH_UI_NS::GizmoOperation::Rotate)) {
                SetOperation(GetOperation()
                    & ~SR_GRAPH_UI_NS::GizmoOperation::X
                    & ~SR_GRAPH_UI_NS::GizmoOperation::Y
                    & ~SR_GRAPH_UI_NS::GizmoOperation::Center
                    | SR_GRAPH_UI_NS::GizmoOperation::Rotate2D
                );

                SRAssert2(SR_MATH_NS::IsMaskIncludedSubMask(GetOperation(), SR_GRAPH_UI_NS::GizmoOperation::Rotate), "Rotate operation is not set");
                SRAssert2(SR_MATH_NS::IsMaskIncludedSubMask(GetOperation(), SR_GRAPH_UI_NS::GizmoOperation::Rotate2D), "Rotate2D operation is not set");
                SRAssert2(SR_MATH_NS::IsMaskIncludedSubMask(GetOperation(), SR_GRAPH_UI_NS::GizmoOperation::Z), "Z operation is not set");
            }
            else {
                SetOperation(GetOperation() & ~SR_GRAPH_UI_NS::GizmoOperation::Z | SR_GRAPH_UI_NS::GizmoOperation::Space2D);
            }
        }
        else {
            SetOperation(GetOperation()
                & ~SR_GRAPH_UI_NS::GizmoOperation::Space2D
                | SR_GRAPH_UI_NS::GizmoOperation::Z
                | SR_GRAPH_UI_NS::GizmoOperation::X
                | SR_GRAPH_UI_NS::GizmoOperation::Y
                | SR_GRAPH_UI_NS::GizmoOperation::Center
            );
        }

        Super::PrepareGizmo();
    }
}