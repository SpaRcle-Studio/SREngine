//
// Created by Monika on 01.08.2022.
//

#include <Utils/ECS/Transform2D.h>

namespace SR_UTILS_NS {
    Transform2D::Transform2D()
        : Transform()
    { }

    void Transform2D::SetTranslation(const SR_MATH_NS::FVector3 &translation) {
        if (translation == m_translation) {
            return;
        }

        m_translation = translation;

        UpdateTree();
    }

    void Transform2D::SetTranslationAndRotation(const SR_MATH_NS::FVector3 &translation, const SR_MATH_NS::FVector3 &euler) {
        m_translation = translation;
        m_rotation = euler.Limits(360);

        UpdateTree();
    }

    void Transform2D::SetRotation(const SR_MATH_NS::FVector3& euler) {
        m_rotation = euler.Limits(360);

        UpdateTree();
    }

    void Transform2D::SetScale(const SR_MATH_NS::FVector3& rawScale) {
        SR_MATH_NS::FVector3 scale = rawScale;

        if (scale.ContainsNaN()) {
            SR_WARN("Transform2D::SetScale() : scale contains NaN! Reset...");
            scale = SR_MATH_NS::FVector3::One();
        }

        m_scale = scale;

        UpdateTree();
    }

    void Transform2D::SetSkew(const SR_MATH_NS::FVector3& rawSkew) {
        SR_MATH_NS::FVector3 skew = rawSkew;

        if (skew.ContainsNaN()) {
            SR_WARN("Transform2D::SetSkew() : skew contains NaN! Reset...");
            skew = Math::FVector3::One();
        }

        m_skew = skew;

        UpdateTree();
    }

    const SR_MATH_NS::Matrix4x4 &Transform2D::GetMatrix() {
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

    void Transform2D::UpdateMatrix() {
        SR_MATH_NS::FVector3 scale = m_scale;

        if (auto&& pParent = GetParentTransform(); pParent && m_stretch != Stretch::None) {
            auto&& aspect = pParent->GetScale().XY().Aspect();
            switch (m_stretch) {
                case Stretch::StretchX:
                    scale.x *= aspect;
                    break;
                case Stretch::StretchY:
                    scale.y *= aspect;
                    break;
                case Stretch::StretchXY:
                    scale *= aspect;
                    break;
                default:
                    SRHalt0();
                    break;
            }
        }

        m_localMatrix = SR_MATH_NS::Matrix4x4(
                m_translation,
                m_rotation.Radians().ToQuat(),
                scale,
                m_skew
        );

        Transform::UpdateMatrix();
    }

    void Transform2D::SetStretch(Stretch stretch) {
        m_stretch = stretch;
        UpdateTree();
    }
}