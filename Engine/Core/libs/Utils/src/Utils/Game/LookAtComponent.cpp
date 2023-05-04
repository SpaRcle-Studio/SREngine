//
// Created by Monika on 03.05.2023.
//

#include <Utils/Game/LookAtComponent.h>

namespace SR_UTILS_NS {
    SR_REGISTER_COMPONENT(LookAtComponent);

    LookAtComponent::LookAtComponent()
        : Super()
    {
        m_target.SetOwner(GetThis());
    }

    Component* LookAtComponent::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        auto&& pComponent = new LookAtComponent();

        pComponent->GetTarget().Load(marshal);

        pComponent->SetAxis(static_cast<LookAtAxis>(marshal.Read<uint8_t>()));
        pComponent->SetExecuteInEditMode(marshal.Read<bool>());
        pComponent->SetMirror(marshal.Read<bool>());
        pComponent->SetDelay(marshal.Read<float_t>());

        return pComponent;
    }

    Component* LookAtComponent::CopyComponent() const {
        auto&& pComponent = new LookAtComponent();

        pComponent->SetAxis(m_axis);
        pComponent->m_target = m_target.Copy(pComponent->GetThis().DynamicCast<Entity>());
        pComponent->m_editMode = m_editMode;
        pComponent->m_mirror = m_mirror;
        pComponent->m_delay = m_delay;

        return pComponent;
    }

    void LookAtComponent::Update(float_t dt) {
        auto&& pTarget = m_target.GetGameObject();
        if (!pTarget) {
            Super::Update(dt);
            return;
        }

        auto&& pTargetTransform = pTarget->GetTransform();
        if (!pTargetTransform) {
            Super::Update(dt);
            return;
        }

        if (auto&& pTransform = GetTransform()) {
            auto&& sourceTranslate = pTransform->GetMatrix().GetTranslate();
            auto&& destinationTranslate = pTargetTransform->GetMatrix().GetTranslate();

            SR_MATH_NS::FVector3 direction;

            if (m_mirror) {
                direction = destinationTranslate - sourceTranslate;
            }
            else {
                direction = sourceTranslate - destinationTranslate;
            }

            if (direction == m_direction && m_reached) {
                Super::Update(dt);
                return;
            }

            m_direction = direction;

            SR_MATH_NS::FVector3 up;

            switch (m_axis) {
                case LookAtAxis::AxisX: up = Transform3D::RIGHT; break;
                case LookAtAxis::AxisY: up = Transform3D::UP; break;
                case LookAtAxis::AxisZ: up = Transform3D::FORWARD; break;
                case LookAtAxis::InvAxisX: up = -Transform3D::RIGHT; break;
                case LookAtAxis::InvAxisY: up = -Transform3D::UP; break;
                case LookAtAxis::InvAxisZ: up = -Transform3D::FORWARD; break;
                default:
                    SRHalt0();
                    break;
            }

            SR_MATH_NS::Quaternion q = SR_MATH_NS::Quaternion::LookAt(m_direction.Normalize(), up);

            if (!SR_EQUALS(m_delay, 0.f)) {
                auto&& sourceQ = pTransform->GetQuaternion();
                q = q.Slerp(q, SR_MIN(dt * (1.f / m_delay), 1.f));
                m_reached = q == sourceQ;
            }

            pTransform->SetRotation(q);
        }

        Super::Update(dt);
    }

    SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr LookAtComponent::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = Super::Save(pMarshal, flags);

        pMarshal = m_target.Save(pMarshal);

        pMarshal->Write<uint8_t>(static_cast<uint8_t>(m_axis));
        pMarshal->Write<bool>(m_editMode);
        pMarshal->Write<bool>(m_mirror);
        pMarshal->Write<float_t>(m_delay);

        return pMarshal;
    }

    void LookAtComponent::OnDestroy() {
        Super::OnDestroy();

        GetThis().AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    void LookAtComponent::SetExecuteInEditMode(bool enabled) {
        m_editMode = enabled;

        if (auto&& pParent = GetParent()) {
            pParent->SetDirty(true);
        }
    }

    void LookAtComponent::SetAxis(LookAtAxis axis) {
        m_axis = axis;
        m_reached = false;
    }

    void LookAtComponent::SetMirror(bool mirror) {
        m_mirror = mirror;
        m_reached = false;
    }
}
