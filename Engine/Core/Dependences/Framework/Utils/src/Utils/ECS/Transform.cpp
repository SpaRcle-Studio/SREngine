//
// Created by Nikita on 27.11.2020.
//

#include <Utils/ECS/Transform.h>

namespace SR_UTILS_NS {
    void Transform::SetGameObject(GameObject *gameObject) {
        if (m_gameObject) {
            SR_WARN("Transform::SetGameObject() : game object already set!");
        }

        m_gameObject = gameObject;

        UpdateComponents();
    }

    Transform* Transform::GetParentTransform() const {
        if (!m_gameObject) {
            return nullptr;
        }

        if (auto&& pParent = m_gameObject->GetParent()) {
            return pParent->GetTransform();
        }

        return nullptr;
    }

    void Transform::UpdateComponents() {
        if (m_gameObject) {
            m_gameObject->UpdateComponents();
        }
    }

    void Transform::Rotate(Math::Unit x, Math::Unit y, Math::Unit z) {
        Rotate(Math::FVector3(x, y, z));
    }

    void Transform::GlobalRotate(Math::Unit x, Math::Unit y, Math::Unit z) {
        GlobalRotate(Math::FVector3(x, y, z));
    }

    void Transform::SetTranslation(Math::Unit x, Math::Unit y, Math::Unit z) {
        SetTranslation(Math::FVector3(x, y, z));
    }

    void Transform::SetRotation(Math::Unit yaw, Math::Unit pitch, Math::Unit roll) {
        SetRotation(Math::FVector3(yaw, pitch, roll));
    }

    void Transform::SetScale(Math::Unit x, Math::Unit y, Math::Unit z) {
        SetScale(Math::FVector3(x, y, z));
    }

    void Transform::SetSkew(Math::Unit x, Math::Unit y, Math::Unit z) {
        SetSkew(Math::FVector3(x, y, z));
    }

    void Transform::Translate(Math::Unit x, Math::Unit y, Math::Unit z) {
        Translate(Math::FVector3(x, y, z));
    }

    void Transform::Scale(Math::Unit x, Math::Unit y, Math::Unit z) {
        Scale(Math::FVector3(x, y, z));
    }

    SR_HTYPES_NS::Marshal Transform::Save(SavableFlags flags) const {
        SR_HTYPES_NS::Marshal marshal;

        marshal.Write(static_cast<int8_t>(GetMeasurement()));

        switch (GetMeasurement()) {
            case Measurement::Space2D:
                marshal.Write(GetTranslation(), Math::FVector3(0.f));
                marshal.Write(GetRotation(), Math::FVector3(0.f));
                marshal.Write(GetScale(), Math::FVector3(1.f));
                marshal.Write(GetSkew(), Math::FVector3(1.f));
                break;
            case Measurement::Space3D: {
                auto&& offset = SR_THIS_THREAD->GetContext()->GetValueDef<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3());

                marshal.Write(offset + GetTranslation(), Math::FVector3(0.f));
                marshal.Write(GetRotation(), Math::FVector3(0.f));
                marshal.Write(GetScale(), Math::FVector3(1.f));
                marshal.Write(GetSkew(), Math::FVector3(1.f));
                break;
            }
            case Measurement::Space4D:
                break;
        }

        return marshal;
    }

    Transform *Transform::Load(SR_HTYPES_NS::Marshal &marshal) {
        Transform* transform = nullptr;

        switch (static_cast<Measurement>(marshal.Read<int8_t>())) {
            case Measurement::Space2D:
                transform = new Transform2D();
                break;
            case Measurement::Space3D:
                transform = new Transform3D();
                break;
            case Measurement::Space4D:
                break;
        }

        transform->SetTranslation(marshal.Read<Math::FVector3>(Math::FVector3(0.f)));
        transform->SetRotation(marshal.Read<Math::FVector3>(Math::FVector3(0.f)));
        transform->SetScale(marshal.Read<Math::FVector3>(Math::FVector3(1.f)));
        transform->SetSkew(marshal.Read<Math::FVector3>(Math::FVector3(1.f)));

        return transform;
    }

    SR_MATH_NS::FVector2 Transform::GetScale2D() const {
        return GetScale().XY();
    }
}