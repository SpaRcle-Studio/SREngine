//
// Created by Monika on 19.02.2022.
//

#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/GameObject.h>

namespace SR_UTILS_NS {
    void Transform3D::UpdateMatrix() {
        m_localMatrix = SR_MATH_NS::Matrix4x4(
                m_translation,
                m_quaternion,
                m_scale,
                m_skew
        );

        Transform::UpdateMatrix();
    }

    void Transform3D::Rotate(const SR_MATH_NS::FVector3& eulers) {
        Rotate(eulers.Radians().ToQuat());
    }

    void Transform3D::Rotate(const SR_MATH_NS::Quaternion &q) {
        SetRotation((m_quaternion * q).EulerAngle());
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
        return m_quaternion * direction;
    }

    void Transform3D::SetTranslation(const SR_MATH_NS::FVector3& translation) {
        SR_MATH_NS::FVector3 delta = translation - m_translation;

        if (delta.Empty()) {
            return;
        }

        m_translation = translation;

        if (!m_translation.IsFinite()) {
            SRHaltOnce("Translation is broke!");
            m_translation = SR_MATH_NS::FVector3::Zero();
        }

        UpdateTree();
    }

    void Transform3D::SetRotation(const SR_MATH_NS::FVector3& euler) {
        if (!euler.IsFinite()) {
            SRHaltOnce("Rotation is broke!");
            m_rotation = SR_MATH_NS::FVector3::Zero();
            m_quaternion = SR_MATH_NS::Quaternion::Identity();
        }
        else {
            m_rotation = euler.Limits(360);
            m_quaternion = euler.Radians().ToQuat();
        }

        UpdateTree();
    }


    void Transform3D::SetRotation(const SR_MATH_NS::Quaternion& quaternion) {
        if (!quaternion.IsFinite()) {
            SRHaltOnce("Rotation is broke!");
            m_rotation = SR_MATH_NS::FVector3::Zero();
            m_quaternion = SR_MATH_NS::Quaternion::Identity();
        }
        else {
            m_rotation = quaternion.EulerAngle();
            m_quaternion = quaternion;
        }

        UpdateTree();
    }

    void Transform3D::SetTranslationAndRotation(const SR_MATH_NS::FVector3 &translation, const SR_MATH_NS::FVector3 &euler) {
        SR_MATH_NS::FVector3 deltaTranslation = translation - m_translation;
        SR_MATH_NS::FVector3 deltaRotation = (SR_MATH_NS::Quaternion::FromEuler(euler) *
                SR_MATH_NS::Quaternion::FromEuler(m_rotation).Inverse()).EulerAngle();

        m_translation = translation;
        SetRotation(euler);

        for (auto&& child : m_gameObject->GetChildrenRef()) {
            child->GetTransform()->GlobalTranslate(deltaTranslation);
            child->GetTransform()->RotateAroundParent(deltaRotation);
        }
    }

    void Transform3D::SetScale(const SR_MATH_NS::FVector3& rawScale) {
        SR_MATH_NS::FVector3 scale = rawScale;

        if (scale.ContainsNaN()) {
            SR_WARN("Transform3D::SetScale() : scale contains NaN! Reset...");
            scale = SR_MATH_NS::FVector3::One();
        }

        m_scale = scale;

        UpdateTree();
    }

    void Transform3D::SetSkew(const SR_MATH_NS::FVector3& rawSkew) {
        SR_MATH_NS::FVector3 skew = rawSkew;

        if (skew.ContainsNaN()) {
            SR_WARN("Transform3D::GlobalSkew() : skew contains NaN! Reset...");
            skew = SR_MATH_NS::FVector3::One();
        }

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

    void Transform3D::SetGlobalTranslation(const SR_MATH_NS::FVector3 &translation) {
        if (auto&& pParent = GetParentTransform()) {
            auto matrix = SR_MATH_NS::Matrix4x4::FromTranslate(translation);
            matrix *= SR_MATH_NS::Matrix4x4::FromScale(m_skew);
            matrix *= SR_MATH_NS::Matrix4x4::FromEulers(m_rotation.Inverse());
            matrix *= SR_MATH_NS::Matrix4x4::FromScale(m_scale);

            matrix = pParent->GetMatrix().Inverse() * matrix;

            m_translation = matrix.GetTranslate();

            UpdateTree();
        }
        else {
            SetTranslation(translation);
        }
    }

    void Transform3D::SetGlobalRotation(const SR_MATH_NS::FVector3 &eulers) {
        if (auto&& pParent = GetParentTransform()) {
            auto&& matrix = SR_MATH_NS::Matrix4x4::FromScale(SR_MATH_NS::FVector3(1) / m_skew);
            matrix *= SR_MATH_NS::Matrix4x4::FromEulers(eulers);
            matrix *= SR_MATH_NS::Matrix4x4::FromScale(m_scale);

            matrix = pParent->GetMatrix().Inverse() * matrix;

            SetRotation(matrix.GetEulers());
        }
        else {
            auto&& matrix = SR_MATH_NS::Matrix4x4::FromScale(SR_MATH_NS::FVector3(1) / m_skew);
            matrix *= SR_MATH_NS::Matrix4x4::FromEulers(eulers);
            matrix *= SR_MATH_NS::Matrix4x4::FromScale(m_scale);

            SetRotation(matrix.GetEulers());
        }
    }

    Transform *Transform3D::Copy() const {
        auto&& pTransform = new Transform3D();

        pTransform->m_quaternion = m_quaternion;

        pTransform->m_translation = m_translation;
        pTransform->m_rotation = m_rotation;
        pTransform->m_scale = m_scale;
        pTransform->m_skew = m_skew;

        return pTransform;
    }

    void Transform3D::LookAt(const SR_MATH_NS::FVector3& position) {
        LookAt(position, LookAtAxis::AxisZ);
    }

    void Transform3D::LookAt(const SR_MATH_NS::FVector3& position, LookAtAxis axis) {
        /*SR_MATH_NS::FVector3 target;

        switch (axis) {
            case LookAtAxis::AxisX: target = Transform3D::RIGHT; break;
            case LookAtAxis::AxisY: target = Transform3D::UP; break;
            case LookAtAxis::AxisZ: target = Transform3D::FORWARD; break;
            case LookAtAxis::InvAxisX: target = -Transform3D::RIGHT; break;
            case LookAtAxis::InvAxisY: target = -Transform3D::UP; break;
            case LookAtAxis::InvAxisZ: target = -Transform3D::FORWARD; break;
            default:
                SRHalt0();
                break;
        }*/

        //auto&& source = GetMatrix().GetTranslate();

        //SetRotation(m_quaternion.LookAt(source - position));
    }
}



