//
// Created by Monika on 19.02.2022.
//

#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/GameObject.h>

namespace SR_UTILS_NS {
    Transform3D::Transform3D(GameObject *parent)
            : m_gameObject(parent)
    {
        m_translation = Math::FVector3::Zero();
        m_rotation = Math::FVector3::Zero();
        m_scale = Math::FVector3::One();
        m_skew = Math::FVector3::One();
    }

    void Transform3D::OnParentSet(Transform3D *parent) {
        m_parent = parent;
    }

    void Transform3D::UpdateComponents() {
        if (m_gameObject)
            m_gameObject->UpdateComponents();
    }

    void Transform3D::Translate(Math::FVector3 translation) {
        const auto &&direction = TransformDirection(translation);
        SetTranslation(m_translation + direction);
    }

    void Transform3D::Rotate(Math::FVector3 eulers) {
        Math::Matrix4x4 &&worldRotateMatrix = Math::Matrix4x4::FromEulers(m_rotation);
        Math::Matrix4x4 &&rotatedMatrix = worldRotateMatrix * Math::Matrix4x4::FromEulers(eulers);
        SetRotation(rotatedMatrix.GetQuat().EulerAngle());
    }

    void Transform3D::Rotate(Math::Unit x, Math::Unit y, Math::Unit z) {
        Rotate(Math::FVector3(x, y, z));
    }

    void Transform3D::GlobalTranslate(Math::FVector3 translation) {
        SetTranslation(m_translation + translation);
    }

    void Transform3D::GlobalRotate(Math::FVector3 eulers) {
        SetRotation(m_rotation + eulers);
    }

    void Transform3D::GlobalRotate(Math::Unit x, Math::Unit y, Math::Unit z) {
        GlobalRotate(Math::FVector3(x, y, z));
    }

    void Transform3D::GlobalScale(const Math::FVector3 &scale) {
        SetScale(m_scale * scale);
    }

    void Transform3D::GlobalSkew(const Math::FVector3 &skew) {
        SetSkew(m_skew * skew);
    }

    Math::FVector3 Transform3D::TransformDirection(Math::FVector3 direction) const {
        return Math::Quaternion::FromEuler(m_rotation) * direction;
    }

    void Transform3D::SetTranslation(Math::FVector3 translation) {
        Math::FVector3 delta = translation - m_translation;

        m_translation = translation;
        UpdateComponents();

        if (m_gameObject) {
            for (auto &&child : m_gameObject->m_children) {
                child->m_transform->GlobalTranslate(delta);
            }
        }
    }

    void Transform3D::SetRotation(Math::FVector3 euler) {
        Math::FVector3 delta = (Math::Quaternion::FromEuler(euler.FixEulerAngles()) *
                Math::Quaternion::FromEuler(m_rotation).Inverse()).EulerAngle();

        m_rotation = euler.Limits(360);
        UpdateComponents();

        if (m_gameObject) {
            for (auto &&child : m_gameObject->m_children) {
                child->m_transform->RotateAroundParent(delta);
            }
        }
    }

    void Transform3D::SetTranslationAndRotation(const Math::FVector3 &translation, const Math::FVector3 &euler) {
        Math::FVector3 deltaTranslation = translation - m_translation;
        Math::FVector3 deltaRotation = (Math::Quaternion::FromEuler(euler) *
                Math::Quaternion::FromEuler(m_rotation).Inverse()).EulerAngle();

        m_translation = translation;
        m_rotation = euler.Limits(360);

        UpdateComponents();

        if (m_gameObject) {
            for (auto &&child : m_gameObject->m_children) {
                child->m_transform->GlobalTranslate(deltaTranslation);
                child->m_transform->RotateAroundParent(deltaRotation);
            }
        }
    }

    void Transform3D::SetScale(Math::FVector3 scale) {
        if (scale.ContainsNaN()) {
            SR_WARN("Transform3D::SetScale() : scale contains NaN! Reset...");
            scale = Math::FVector3::One();
        }

        Math::FVector3 delta = scale / m_scale;

        m_scale = scale;
        UpdateComponents();

        //Matrix4x4&& scaleMatrix = Matrix4x4::FromScale(delta);
        //Matrix4x4&& rotationMatrix = Matrix4x4::FromEulers(m_rotation);
        //delta = (rotationMatrix * scaleMatrix).GetScale();

        if (m_gameObject) {
            for (auto &&child : m_gameObject->m_children) {
                child->m_transform->GlobalSkew(delta);

                //Math::FVector3 childTranslation = (child->m_transform->GetTranslation() - m_translation) * delta + m_translation;
                //child->m_transform->SetTranslation(childTranslation);
            }
        }
    }

    void Transform3D::SetSkew(Math::FVector3 skew) {
        if (skew.ContainsNaN()) {
            SR_WARN("Transform3D::GlobalSkew() : skew contains NaN! Reset...");
            skew = Math::FVector3::One();
        }

        Math::FVector3 delta = skew / m_skew;

        m_skew = skew;
        UpdateComponents();

        if (m_gameObject) {
            for (auto &&child : m_gameObject->m_children) {
                child->m_transform->GlobalSkew(delta);

                Math::FVector3 childTranslation =
                        (child->m_transform->GetTranslation() - m_translation) * delta + m_translation;
                child->m_transform->SetTranslation(childTranslation);
            }
        }
    }

    void Transform3D::RotateAround(Math::FVector3 point, Math::FVector3 eulers) {
        const Math::Quaternion &&q = Math::Quaternion::FromEuler(eulers);
        const Math::Quaternion &&rotation = q * Math::Quaternion::FromEuler(m_rotation);

        const Math::FVector3 &&worldPos = m_translation - point;
        const Math::FVector3 &&rotatedPos = q * worldPos;

        SetTranslationAndRotation(point + rotatedPos, rotation.EulerAngle());
    }

    void Transform3D::RotateAroundParent(Math::FVector3 eulers) {
        if (m_parent) {
            RotateAround(m_parent->m_translation, eulers);
        }
        else {
            Rotate(eulers); /// TODO: check working
        }
    }

    SR_HTYPES_NS::Marshal Transform3D::Save(SavableFlags flags) const {
        SR_HTYPES_NS::Marshal marshal;

        marshal.Write(GetTranslation(), Math::FVector3(0.f));
        marshal.Write(GetRotation(), Math::FVector3(0.f));
        marshal.Write(GetScale(), Math::FVector3(1.f));
        marshal.Write(GetSkew(), Math::FVector3(1.f));

        return marshal;
    }

    Transform3D *Transform3D::Load(SR_HTYPES_NS::Marshal &marshal) {
        Transform3D *transform3D = new Transform3D();

        transform3D->SetTranslation(marshal.Read<Math::FVector3>(Math::FVector3(0.f)));
        transform3D->SetRotation(marshal.Read<Math::FVector3>(Math::FVector3(0.f)));
        transform3D->SetScale(marshal.Read<Math::FVector3>(Math::FVector3(1.f)));
        transform3D->SetSkew(marshal.Read<Math::FVector3>(Math::FVector3(1.f)));

        return transform3D;
    }

    void Transform3D::SetTranslation(Math::Unit x, Math::Unit y, Math::Unit z) {
        SetTranslation(Math::FVector3(x, y, z));
    }

    void Transform3D::SetRotation(Math::Unit yaw, Math::Unit pitch, Math::Unit roll) {
        SetRotation(Math::FVector3(yaw, pitch, roll));
    }

    void Transform3D::SetScale(Math::Unit x, Math::Unit y, Math::Unit z) {
        SetScale(Math::FVector3(x, y, z));
    }

    void Transform3D::SetSkew(Math::Unit x, Math::Unit y, Math::Unit z) {
        SetSkew(Math::FVector3(x, y, z));
    }

    void Transform3D::SetGameObject(GameObject *gameObject) {
        if (m_gameObject) {
            SR_WARN("Transform3D::SetGameObject() : game object already set!");
        }

        m_gameObject = gameObject;

        UpdateComponents();
    }

    void Transform3D::Translate(Math::Unit x, Math::Unit y, Math::Unit z) {
        Translate(Math::FVector3(x, y, z));
    }

    void Transform3D::Scale(Math::FVector3 scale) {
        SetScale(m_scale * scale);
    }

    void Transform3D::Scale(Math::Unit x, Math::Unit y, Math::Unit z) {
        Scale(Math::FVector3(x, y, z));
    }
}



