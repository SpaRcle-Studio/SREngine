//
// Created by Monika on 03.02.2024.
//

#include <Engine/GUI/EditorGizmo.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/EngineCommands.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/GUI/EditorCamera.h>

#include <Physics/3D/Rigidbody3D.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/Reflection/Value.h>

#include <Enum/GizmoOperation.hpp>

#include <Codegen/EditorGizmo.generated.hpp>

namespace SR_CORE_GUI_NS {
    static const SR_MATH_NS::AABB OBJECT_BOUNDS = SR_MATH_NS::AABB::UnitCube();

    SR_MATH_NS::Matrix4x4 EditorGizmo::GetGizmoMatrix() const {
        if (!m_hierarchy || m_hierarchy->GetSelected().empty()) {
            return SR_MATH_NS::Matrix4x4::Identity();
        }

        if (m_hierarchy->GetSelected().size() == 1) {
            if (!(*m_hierarchy->GetSelected().begin())) {
                return SR_MATH_NS::Matrix4x4::Identity();
            }
            if (auto&& pGameObject = m_hierarchy->GetSelected().begin()->DynamicCast<SR_UTILS_NS::GameObject>()) {
                auto&& pTransform = pGameObject->GetTransform();
                return pTransform->GetMatrix();
            }
        }

        SR_MATH_NS::FVector3 center;

        for (auto&& pSceneObject : m_hierarchy->GetSelected()) {
            if (auto&& pGameObject = m_hierarchy->GetSelected().begin()->DynamicCast<SR_UTILS_NS::GameObject>()) {
                center += pGameObject->GetTransform()->GetMatrix().GetTranslate();
            }
        }

        center /= m_hierarchy->GetSelected().size();

        return SR_MATH_NS::Matrix4x4::FromTranslate(center);
    }

    void EditorGizmo::OnGizmoTranslated(const SR_MATH_NS::FVector3& delta) {
        if (!m_hierarchy) {
            return;
        }

        for (auto&& pSceneObject : m_hierarchy->GetSelected()) {
            if (!pSceneObject) {
                continue;
            }

            auto&& pGameObject = pSceneObject.DynamicCast<SR_UTILS_NS::GameObject>();
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

        for (auto&& pSceneObject : m_hierarchy->GetSelected()) {
            if (!pSceneObject) {
                continue;
            }

            auto&& pGameObject = pSceneObject.DynamicCast<SR_UTILS_NS::GameObject>();
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

        if (IsBoundsMode()) {
            if (IsObjectBoundsEdit()) {
                return GetObjectBoundsTarget().Valid();
            }
            return IsBoundsEditValid();
        }

        std::optional<bool> is2D;

        for (auto pSceneObject : m_hierarchy->GetSelected()) {
            if (!pSceneObject) {
                continue;
            }

            auto&& pGameObject = pSceneObject.DynamicCast<SR_UTILS_NS::GameObject>();
            if (!pGameObject) {
                continue;
            }

            if (pGameObject == GetGameObject()) {
                return false;
            }

            if (pGameObject->GetComponent<EditorCamera>()) {
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

        for (auto pSceneObject : m_hierarchy->GetSelected()) {
            if (!pSceneObject) {
                continue;
            }

            auto&& pGameObject = pSceneObject.DynamicCast<SR_UTILS_NS::GameObject>();
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
        if (IsBoundsMode() && IsObjectBoundsEdit()) {
            auto&& pGameObject = GetObjectBoundsTarget();
            if (!pGameObject) {
                return;
            }

            m_objectTranslationStart = pGameObject->GetTransform()->GetTranslation();
            m_objectScaleStart = pGameObject->GetTransform()->GetScale();
        }
        else if (IsBoundsMode()) {
            if (IsBoundsEditValid()) {
                m_boundsSerializer = SR_CORE_NS::Commands::CreateSerializer();
                SR_UTILS_NS::Serialization::Save(*m_boundsSerializer, *m_boundsComponent, SR_UTILS_NS::COMMAND_DATA_ID);
            }
            Super::BeginGizmo();
            return;
        }

        if (!m_hierarchy || m_hierarchy->GetSelected().empty()) {
            return;
        }

        if (!*m_hierarchy->GetSelected().begin()) {
            return;
        }

        m_pSerializers.clear();
        m_pSerializers.reserve(m_hierarchy->GetSelected().size());

        for (auto&& pSceneObject : m_hierarchy->GetSelected()) {
            if (!pSceneObject) {
                continue;
            }

            auto&& pGameObject = pSceneObject.DynamicCast<SR_UTILS_NS::GameObject>();
            if (!pGameObject) {
                continue;
            }

            auto&& pSerializer = SR_CORE_NS::Commands::CreateSerializer();
            SR_UTILS_NS::Serialization::Save(*pSerializer, pGameObject->GetTransform(), SR_UTILS_NS::COMMAND_DATA_ID);
            m_pSerializers.emplace_back(std::make_pair(pGameObject->GetEntityId(), std::move(pSerializer)));
        }

        m_holding = true;
        Super::BeginGizmo();
    }

    void EditorGizmo::EndGizmo() {
        m_holding = false;

        if (m_boundsSerializer) {
            if (m_hierarchy && IsBoundsEditValid()) {
                auto&& pEngine = dynamic_cast<EditorGUI*>(m_hierarchy->GetManager())->GetEngine();
                auto&& pCmd = new SR_CORE_NS::Commands::ComponentChange(pEngine, m_boundsComponent, std::move(m_boundsSerializer));
                pEngine->GetCmdManager()->Store(pCmd);
            }
            m_boundsSerializer.reset();
            Super::EndGizmo();
            return;
        }

        if (!m_hierarchy || m_hierarchy->GetSelected().empty()) {
            return;
        }

        if (!*m_hierarchy->GetSelected().begin()) {
            return;
        }


        auto&& pEngine = dynamic_cast<EditorGUI*>(m_hierarchy->GetManager())->GetEngine();
        SR_UTILS_NS::Vector<SR_UTILS_NS::ReversibleCommand*> commands;
        commands.reserve(m_hierarchy->GetSelected().size());

        for (auto&& pSceneObject : m_hierarchy->GetSelected()) {
            if (!pSceneObject) {
                continue;
            }

            auto&& pGameObject = pSceneObject.DynamicCast<SR_UTILS_NS::GameObject>();
            if (!pGameObject) {
                continue;
            }

            for (auto&& [entityId, pSerializer] : m_pSerializers) {
                if (entityId == pGameObject->GetEntityId()) {
                    commands.push_back(new SR_CORE_NS::Commands::GameObjectTransform(
                        pEngine, pGameObject, std::move(pSerializer)
                    ));
                    break;
                }
            }
        }

        if (!commands.empty()) {
            auto&& pCmd = new SR_UTILS_NS::GroupCommand(std::move(commands));
            pEngine->GetCmdManager()->Store(pCmd);
        }

        Super::EndGizmo();
    }

    void EditorGizmo::Update(float_t dt) {
        if (m_boundsComponent && (!IsBoundsMode() || !IsBoundsEditValid())) {
            StopBoundsEdit();
        }

        Super::Update(dt);

        if (!m_holding) {
            return;
        }

        for (auto&& pSceneObject : m_hierarchy->GetSelected()) {
            if (!pSceneObject) {
                continue;
            }

            if (auto&& pRigidbody = pSceneObject->GetComponent<SR_PTYPES_NS::Rigidbody3D>()) {
                pRigidbody->ClearForces();
            }
        }
    }

    void EditorGizmo::PrepareGizmo() {
        if (IsBoundsMode()) {
            Super::PrepareGizmo();
            return;
        }

        auto&& pSceneObject = *m_hierarchy->GetSelected().begin();
        if (!pSceneObject) {
            return;
        }

        auto&& pGameObject = pSceneObject.DynamicCast<SR_UTILS_NS::GameObject>();
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

    void EditorGizmo::BeginBoundsEdit(const SR_UTILS_NS::Component::Ptr& pComponent, const SR_UTILS_NS::Reflection::Property* pProperty) {
        if (!pComponent || !pProperty) {
            return;
        }

        if (!m_boundsComponent) {
            m_operationBeforeBounds = GetOperation();
        }

        m_boundsComponent = pComponent;
        m_boundsProperty = pProperty;
        m_boundsSerializer.reset();

        SetOperation(SR_GRAPH_UI_NS::GizmoOperation::Bounds);
    }

    void EditorGizmo::StopBoundsEdit() {
        const bool wasBoundsMode = IsBoundsMode() && m_boundsComponent;

        m_boundsComponent = nullptr;
        m_boundsProperty = nullptr;
        m_boundsSerializer.reset();

        if (wasBoundsMode) {
            SetOperation(m_operationBeforeBounds);
        }
    }

    bool EditorGizmo::IsBoundsEdit(const SR_UTILS_NS::Component* pComponent, const SR_UTILS_NS::Reflection::Property* pProperty) const {
        return IsBoundsMode() && m_boundsComponent.Get() == pComponent && m_boundsProperty == pProperty;
    }

    bool EditorGizmo::IsBoundsEditValid() const {
        if (!m_boundsComponent || !m_boundsProperty || !m_hierarchy) {
            return false;
        }

        if (!m_boundsComponent->IsAttached()) {
            return false;
        }

        auto&& pSceneObject = m_boundsComponent->GetSceneObject();
        return pSceneObject && m_hierarchy->GetSelected().contains(pSceneObject);
    }

    bool EditorGizmo::GetBounds(SR_MATH_NS::AABB& bounds, SR_MATH_NS::Matrix4x4& matrix) const {
        if (IsObjectBoundsEdit()) {
            auto&& pGameObject = GetObjectBoundsTarget();
            if (!pGameObject) {
                return false;
            }
            bounds = OBJECT_BOUNDS;
            matrix = pGameObject->GetTransform()->GetMatrix();
            return true;
        }

        if (!IsBoundsEditValid()) {
            return false;
        }

        auto&& pTransform = m_boundsComponent->GetTransform();
        if (!pTransform) {
            return false;
        }

        const SR_UTILS_NS::Reflection::Value value = m_boundsProperty->Get(const_cast<SR_UTILS_NS::Component*>(m_boundsComponent.Get()));
        auto&& pBounds = value.Cast<SR_MATH_NS::AABB>();
        if (!pBounds) {
            return false;
        }

        bounds = *pBounds;
        matrix = pTransform->GetMatrix();

        return true;
    }

    void EditorGizmo::OnBoundsChanged(const SR_MATH_NS::AABB& bounds) {
        if (IsObjectBoundsEdit()) {
            auto&& pGameObject = GetObjectBoundsTarget();
            if (!pGameObject) {
                return;
            }

            auto&& pTransform = pGameObject->GetTransform();

            /// bounds - локальный куб OBJECT_BOUNDS в матрице на момент начала перетаскивания
            const SR_MATH_NS::FVector3 startSize = OBJECT_BOUNDS.GetSize();
            const SR_MATH_NS::FVector3 newSize = bounds.GetSize();

            SR_MATH_NS::FVector3 ratio = SR_MATH_NS::FVector3::One();
            for (uint8_t i = 0; i < 3; ++i) {
                if (startSize[i] > SR_BIG_EPSILON) {
                    ratio[i] = SR_MAX(newSize[i] / startSize[i], static_cast<float_t>(SR_BIG_EPSILON));
                }
            }

            /// противоположная грань остается на месте за счет смещения объекта (в пространстве родителя)
            const SR_MATH_NS::FVector3 centerDelta = bounds.GetCenter() - OBJECT_BOUNDS.GetCenter() * ratio;

            const SR_MATH_NS::FVector3 offset = pTransform->GetQuaternion() * (centerDelta * m_objectScaleStart);

            pTransform->SetScale(m_objectScaleStart * ratio);
            pTransform->SetTranslation(m_objectTranslationStart + offset);
            return;
        }

        if (!IsBoundsEditValid()) {
            return;
        }

        m_boundsProperty->Set(m_boundsComponent.Get(), SR_UTILS_NS::Reflection::Value::Create(SR_MATH_NS::AABB(bounds)));
        m_boundsProperty->OnChanged(m_boundsComponent.Get());
    }

    SR_UTILS_NS::GameObject::Ptr EditorGizmo::GetObjectBoundsTarget() const {
        if (!m_hierarchy || m_hierarchy->GetSelected().size() != 1) {
            return nullptr;
        }

        auto&& pSceneObject = *m_hierarchy->GetSelected().begin();
        if (!pSceneObject) {
            return nullptr;
        }

        auto&& pGameObject = pSceneObject.DynamicCast<SR_UTILS_NS::GameObject>();
        if (!pGameObject || pGameObject == GetGameObject() || pGameObject->GetComponent<EditorCamera>()) {
            return nullptr;
        }

        if (pGameObject->GetTransform()->GetMeasurement() == SR_UTILS_NS::Measurement::Space2D) {
            return nullptr;
        }

        return pGameObject;
    }

    EditorGizmo::~EditorGizmo() = default;
}
