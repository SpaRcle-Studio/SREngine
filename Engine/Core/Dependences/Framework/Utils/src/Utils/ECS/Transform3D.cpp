//
// Created by Monika on 19.02.2022.
//

#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/GameObject.h>

namespace SR_UTILS_NS {
    void Transform3D::UpdateMatrix() {
        m_localMatrix = SR_MATH_NS::Matrix4x4::FromTranslate(m_translation);
        m_localMatrix *= SR_MATH_NS::Matrix4x4::FromScale(m_skew);
        m_localMatrix *= SR_MATH_NS::Matrix4x4::FromEulers(m_rotation);
        m_localMatrix *= SR_MATH_NS::Matrix4x4::FromScale(m_scale);

        Transform::UpdateMatrix();
    }

    void Transform3D::Rotate(const SR_MATH_NS::FVector3& eulers) {
        Math::Matrix4x4 &&worldRotateMatrix = Math::Matrix4x4::FromEulers(m_rotation);
        Math::Matrix4x4 &&rotatedMatrix = worldRotateMatrix * Math::Matrix4x4::FromEulers(eulers);
        SetRotation(rotatedMatrix.GetQuat().EulerAngle());
    }

    const SR_MATH_NS::Matrix4x4& Transform3D::GetMatrix() {
        if (IsDirty()) {
            UpdateMatrix();

            if (auto&& pTransform = m_gameObject->GetParentTransform()) {
                m_matrix = pTransform->GetMatrix() * m_localMatrix;
            }
            else {
                m_matrix = m_localMatrix;
            }
        }

        return m_matrix;
    }

    void Transform3D::Translate(const SR_MATH_NS::FVector3& translation) {
        const auto &&direction = TransformDirection(translation);
        SetTranslation(m_translation + direction);
    }

    SR_MATH_NS::FVector3 Transform3D::TransformDirection(const SR_MATH_NS::FVector3& direction) const {
        return SR_MATH_NS::Quaternion::FromEuler(m_rotation) * direction;
    }

    void Transform3D::SetTranslation(const SR_MATH_NS::FVector3& translation) {
        SR_MATH_NS::FVector3 delta = translation - m_translation;

        if (delta.Empty()) {
            return;
        }

        m_translation = translation;

        UpdateTree();
    }

    void Transform3D::SetRotation(const SR_MATH_NS::FVector3& euler) {
        SR_MATH_NS::FVector3 delta = (SR_MATH_NS::Quaternion::FromEuler(euler.FixEulerAngles()) *
                SR_MATH_NS::Quaternion::FromEuler(m_rotation).Inverse()).EulerAngle();

        m_rotation = euler.Limits(360);

        UpdateTree();
    }

    void Transform3D::SetTranslationAndRotation(const SR_MATH_NS::FVector3 &translation, const SR_MATH_NS::FVector3 &euler) {
        SR_MATH_NS::FVector3 deltaTranslation = translation - m_translation;
        SR_MATH_NS::FVector3 deltaRotation = (SR_MATH_NS::Quaternion::FromEuler(euler) *
                SR_MATH_NS::Quaternion::FromEuler(m_rotation).Inverse()).EulerAngle();

        m_translation = translation;
        m_rotation = euler.Limits(360);

        for (auto &&child : m_gameObject->m_children) {
            child->m_transform->GlobalTranslate(deltaTranslation);
            child->m_transform->RotateAroundParent(deltaRotation);
        }
    }

    void Transform3D::SetScale(const SR_MATH_NS::FVector3& rawScale) {
        SR_MATH_NS::FVector3 scale = rawScale;

        if (scale.ContainsNaN()) {
            SR_WARN("Transform3D::SetScale() : scale contains NaN! Reset...");
            scale = SR_MATH_NS::FVector3::One();
        }

        SR_MATH_NS::FVector3 delta = scale / m_scale;

        m_scale = scale;

        UpdateTree();
    }

    void Transform3D::SetSkew(const SR_MATH_NS::FVector3& rawSkew) {
        SR_MATH_NS::FVector3 skew = rawSkew;

        if (skew.ContainsNaN()) {
            SR_WARN("Transform3D::GlobalSkew() : skew contains NaN! Reset...");
            skew = SR_MATH_NS::FVector3::One();
        }

        SR_MATH_NS::FVector3 delta = skew / m_skew;

        m_skew = skew;

        UpdateTree();
    }

    void Transform3D::RotateAround(const SR_MATH_NS::FVector3& point, const SR_MATH_NS::FVector3& eulers) {
        const SR_MATH_NS::Quaternion &&q = SR_MATH_NS::Quaternion::FromEuler(eulers);
        const SR_MATH_NS::Quaternion &&rotation = q * SR_MATH_NS::Quaternion::FromEuler(m_rotation);

        const SR_MATH_NS::FVector3 &&worldPos = m_translation - point;
        const SR_MATH_NS::FVector3 &&rotatedPos = q * worldPos;

        SetTranslationAndRotation(point + rotatedPos, rotation.EulerAngle());
    }

    void Transform3D::RotateAroundParent(const SR_MATH_NS::FVector3& eulers) {
        if (auto&& pTransform = GetParentTransform()) {
            RotateAround(pTransform->GetTranslation(), eulers);
        }
        else {
            Rotate(eulers);
        }
    }

    void Transform3D::Scale(const SR_MATH_NS::FVector3& scale) {
        SetScale(m_scale * scale);
    }
}



