//
// Created by Monika on 01.08.2022.
//

#include <Utils/ECS/Transform2D.h>

namespace SR_UTILS_NS {
    void Transform2D::SetTranslation(const SR_MATH_NS::FVector3 &translation) {
        SR_MATH_NS::FVector3 delta = translation - m_translation;

        if (delta.Empty()) {
            return;
        }

        m_translation = translation;

        UpdateComponents();
    }

    void Transform2D::SetTranslationAndRotation(const SR_MATH_NS::FVector3 &translation, const SR_MATH_NS::FVector3 &euler) {
        SR_MATH_NS::FVector3 deltaTranslation = translation - m_translation;

        SR_MATH_NS::FVector3 deltaRotation = (SR_MATH_NS::Quaternion::FromEuler(euler) *
                SR_MATH_NS::Quaternion::FromEuler(m_rotation).Inverse()).EulerAngle();

        m_translation = translation;
        m_rotation = euler.Limits(360);

        UpdateComponents();
    }

    void Transform2D::SetRotation(const SR_MATH_NS::FVector3& euler) {
        SR_MATH_NS::FVector3 delta = (SR_MATH_NS::Quaternion::FromEuler(euler.FixEulerAngles()) *
                SR_MATH_NS::Quaternion::FromEuler(m_rotation).Inverse()).EulerAngle();

        m_rotation = euler.Limits(360);

        UpdateComponents();
    }

    void Transform2D::SetScale(const SR_MATH_NS::FVector3& rawScale) {
        SR_MATH_NS::FVector3 scale = rawScale;

        if (scale.ContainsNaN()) {
            SR_WARN("Transform2D::SetScale() : scale contains NaN! Reset...");
            scale = SR_MATH_NS::FVector3::One();
        }

        SR_MATH_NS::FVector3 delta = scale / m_scale;

        m_scale = scale;
        UpdateComponents();
    }

    void Transform2D::SetSkew(const SR_MATH_NS::FVector3& rawSkew) {
        SR_MATH_NS::FVector3 skew = rawSkew;

        if (skew.ContainsNaN()) {
            SR_WARN("Transform2D::GlobalSkew() : skew contains NaN! Reset...");
            skew = Math::FVector3::One();
        }

        Math::FVector3 delta = skew / m_skew;

        m_skew = skew;
        UpdateComponents();
    }
}