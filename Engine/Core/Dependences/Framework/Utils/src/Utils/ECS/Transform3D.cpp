//
// Created by Monika on 19.02.2022.
//

#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/GameObject.h>

namespace SR_UTILS_NS {
    void Transform3D::Translate(const Math::FVector3& translation) {
        const auto &&direction = TransformDirection(translation);
        SetTranslation(m_translation + direction);
    }

    void Transform3D::Rotate(const Math::FVector3& eulers) {
        Math::Matrix4x4 &&worldRotateMatrix = Math::Matrix4x4::FromEulers(m_rotation);
        Math::Matrix4x4 &&rotatedMatrix = worldRotateMatrix * Math::Matrix4x4::FromEulers(eulers);
        SetRotation(rotatedMatrix.GetQuat().EulerAngle());
    }

    void Transform3D::GlobalTranslate(const Math::FVector3& translation) {
        SetTranslation(m_translation + translation);
    }

    void Transform3D::GlobalRotate(const Math::FVector3& eulers) {
        SetRotation(m_rotation + eulers);
    }

    void Transform3D::GlobalScale(const Math::FVector3 &scale) {
        SetScale(m_scale * scale);
    }

    void Transform3D::GlobalSkew(const Math::FVector3 &skew) {
        SetSkew(m_skew * skew);
    }

    Math::FVector3 Transform3D::TransformDirection(const Math::FVector3& direction) const {
        return Math::Quaternion::FromEuler(m_rotation) * direction;
    }

    void Transform3D::SetTranslation(const Math::FVector3& translation) {
        Math::FVector3 delta = translation - m_translation;

        if (delta.Empty()) {
            return;
        }

        m_translation = translation;
        UpdateComponents();

        if (m_gameObject) {
            for (auto &&child : m_gameObject->m_children) {
                child->m_transform->GlobalTranslate(delta);
            }
        }
    }

    void Transform3D::SetRotation(const Math::FVector3& euler) {
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

    void Transform3D::SetScale(const Math::FVector3& rawScale) {
        Math::FVector3 scale = rawScale;

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

    void Transform3D::SetSkew(const Math::FVector3& rawSkew) {
        SR_MATH_NS::FVector3 skew = rawSkew;

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

    void Transform3D::RotateAround(const Math::FVector3& point, const Math::FVector3& eulers) {
        const Math::Quaternion &&q = Math::Quaternion::FromEuler(eulers);
        const Math::Quaternion &&rotation = q * Math::Quaternion::FromEuler(m_rotation);

        const Math::FVector3 &&worldPos = m_translation - point;
        const Math::FVector3 &&rotatedPos = q * worldPos;

        SetTranslationAndRotation(point + rotatedPos, rotation.EulerAngle());
    }

    void Transform3D::RotateAroundParent(const Math::FVector3& eulers) {
        if (auto&& pTransform = GetParentTransform()) {
            RotateAround(pTransform->GetTranslation(), eulers);
        }
        else {
            Rotate(eulers); /// TODO: check working
        }
    }

    void Transform3D::Scale(const Math::FVector3& scale) {
        SetScale(m_scale * scale);
    }
}



