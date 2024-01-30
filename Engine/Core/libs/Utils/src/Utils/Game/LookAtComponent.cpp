//
// Created by Monika on 03.05.2023.
//

#include <Utils/Game/LookAtComponent.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/ComponentManager.h>

namespace SR_UTILS_NS {
    SR_REGISTER_COMPONENT(LookAtComponent);

    LookAtComponent::LookAtComponent()
        : Super()
    {
        m_target.SetOwner(GetThis());
    }

    Component* LookAtComponent::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        auto&& pComponent = new LookAtComponent();

        //pComponent->GetTarget().Load(marshal);

        //pComponent->SetAxis(static_cast<LookAtAxis>(marshal.Read<uint8_t>()));
        //pComponent->SetExecuteInEditMode(marshal.Read<bool>());
        //pComponent->SetMirror(marshal.Read<bool>());
        //pComponent->SetDelay(marshal.Read<float_t>());
        //pComponent->SetOffset(marshal.Read<SR_MATH_NS::FVector3>());

        return pComponent;
    }

    Component* LookAtComponent::CopyComponent() const {
        auto&& pComponent = new LookAtComponent();

        pComponent->SetAxis(m_axis);
        pComponent->m_target = m_target.Copy(pComponent->GetThis().DynamicCast<Entity>());
        pComponent->m_editMode = m_editMode;
        pComponent->m_mirror = m_mirror;
        pComponent->m_delay = m_delay;
        pComponent->m_offset = m_offset;

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
            auto&& sourceTranslate = pTransform->GetMatrix().GetTranslate() + m_offset;
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

            const SR_MATH_NS::FVector3 up = GetUp();

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

    SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr LookAtComponent::Save(SR_UTILS_NS::SavableContext data) const {
        auto&& pMarshal = Super::Save(data);

        //pMarshal = m_target.Save(pMarshal);

        //pMarshal->Write<uint8_t>(static_cast<uint8_t>(m_axis));
        //pMarshal->Write<bool>(m_editMode);
        //pMarshal->Write<bool>(m_mirror);
        //pMarshal->Write<float_t>(m_delay);
        //pMarshal->Write<SR_MATH_NS::FVector3>(m_offset);

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

    void LookAtComponent::SetOffset(const SR_MATH_NS::FVector3& offset) {
        m_offset = offset;
        m_reached = false;
    }

    SR_MATH_NS::FVector3 LookAtComponent::GetUp() const noexcept {
        switch (m_axis) {
            case LookAtAxis::AxisX: return Transform3D::RIGHT;
            case LookAtAxis::AxisY: return Transform3D::UP;
            case LookAtAxis::AxisZ: return Transform3D::FORWARD;
            case LookAtAxis::InvAxisX: return -Transform3D::RIGHT;
            case LookAtAxis::InvAxisY: return -Transform3D::UP;
            case LookAtAxis::InvAxisZ: return -Transform3D::FORWARD;
            default:
                SRHalt0();
                return SR_MATH_NS::FVector3();
        }
    }

    SR_MATH_NS::IVector3 LookAtComponent::GetAngle() const {
        return GetUp().Angle(GetDirection()).Cast<int32_t>();
    }
}
