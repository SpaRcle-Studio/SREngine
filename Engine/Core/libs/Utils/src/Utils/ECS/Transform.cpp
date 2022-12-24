#include "..\..\..\inc\Utils\ECS\Transform.h"
//
// Created by Nikita on 27.11.2020.
//

#include <Utils/ECS/Transform.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/TransformZero.h>

namespace SR_UTILS_NS {
    Transform::~Transform() {
        m_gameObject = nullptr;
    }

    void Transform::SetGameObject(GameObject *gameObject) {
        m_gameObject = gameObject;
        UpdateTree();
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

    SR_NODISCARD SR_HTYPES_NS::SharedPtr<GameObject> Transform::GetGameObject() const {
        return m_gameObject->GetThis();
    }

    void Transform::GlobalTranslate(const Math::FVector3& translation) {
        SetTranslation(GetTranslation() + translation);
    }

    void Transform::GlobalRotate(const Math::FVector3& eulers) {
        SetRotation(GetRotation() + eulers);
    }

    void Transform::GlobalScale(const Math::FVector3 &scale) {
        SetScale(GetScale() * scale);
    }

    void Transform::GlobalSkew(const Math::FVector3 &skew) {
        SetSkew(GetSkew() * skew);
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

    SR_HTYPES_NS::Marshal::Ptr Transform::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SavableFlags flags) const {
        pMarshal = ISavable::Save(pMarshal, flags);
        pMarshal->Write(static_cast<int8_t>(GetMeasurement()));

        switch (GetMeasurement()) {
            case Measurement::SpaceZero:
                break;
            case Measurement::Space2D:
                pMarshal->Write(GetTranslation(), Math::FVector3(0.f));
                pMarshal->Write(GetRotation(), Math::FVector3(0.f));
                pMarshal->Write(GetScale(), Math::FVector3(1.f));
                pMarshal->Write(GetSkew(), Math::FVector3(1.f));
                break;
            case Measurement::Space3D: {
                if (m_gameObject->GetParent()) {
                    pMarshal->Write(GetTranslation(), Math::FVector3(0.f));
                }
                else {
                    auto &&offset = SR_THIS_THREAD->GetContext()->GetValueDef<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3());
                    pMarshal->Write(offset + GetTranslation(), Math::FVector3(0.f));
                }

                pMarshal->Write(GetRotation(), Math::FVector3(0.f));
                pMarshal->Write(GetScale(), Math::FVector3(1.f));
                pMarshal->Write(GetSkew(), Math::FVector3(1.f));
                break;
            }
            case Measurement::Space4D:
                break;
            case Measurement::Space1D:
                break;
        }

        return pMarshal;
    }

    Transform *Transform::Load(SR_HTYPES_NS::Marshal &marshal, GameObject* pGameObject) {
        Transform* transform = nullptr;

        auto&& measurement = static_cast<Measurement>(marshal.Read<int8_t>());

        switch (measurement) {
            case Measurement::SpaceZero:
                transform = new TransformZero();
                break;
            case Measurement::Space2D:
                transform = new Transform2D();
                break;
            case Measurement::Space3D:
                transform = new Transform3D();
                break;
            case Measurement::Space4D:
            default:
                SRHalt0();
                return nullptr;
        }

        transform->SetGameObject(pGameObject);

        switch (measurement) {
            case Measurement::SpaceZero:
                break;
            case Measurement::Space2D:
            case Measurement::Space3D:
                transform->SetTranslation(marshal.Read<Math::FVector3>(Math::FVector3(0.f)));
                transform->SetRotation(marshal.Read<Math::FVector3>(Math::FVector3(0.f)));
                transform->SetScale(marshal.Read<Math::FVector3>(Math::FVector3(1.f)));
                transform->SetSkew(marshal.Read<Math::FVector3>(Math::FVector3(1.f)));
                break;
            case Measurement::Space4D:
            default:
                SRHalt0();
                return nullptr;
        }

        return transform;
    }

    SR_MATH_NS::FVector2 Transform::GetTranslation2D() const {
        return GetTranslation().XY();
    }

    SR_MATH_NS::FVector2 Transform::GetScale2D() const {
        return GetScale().XY();
    }

    const SR_MATH_NS::Matrix4x4 &Transform::GetMatrix() {
        static SR_MATH_NS::Matrix4x4 matrix4X4 = SR_MATH_NS::Matrix4x4::Identity();
        return matrix4X4;
    }

    void Transform::UpdateTree() {
        m_dirtyMatrix = true;

        m_gameObject->OnMatrixDirty();

        for (auto&& child : m_gameObject->GetChildrenRef()) {
            child->GetTransform()->UpdateTree();
        }
    }

    bool Transform::IsDirty() const noexcept {
        return m_dirtyMatrix;
    }
}