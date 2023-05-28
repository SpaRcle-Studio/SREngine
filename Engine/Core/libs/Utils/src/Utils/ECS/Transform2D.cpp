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
        if (auto&& pParent = dynamic_cast<Transform2D*>(GetParentTransform())) {
            auto scale = m_scale;
            auto translation = m_translation;

            auto&& aspect = pParent->GetScale().XY().Aspect();

            if (aspect < 1 && !(m_stretch & STRETCH_FLAGS_V)) {
                if (translation.y > 0) {
                    translation.y += (1.f - aspect) * scale.y;
                }
                else if (translation.y < 0) {
                    translation.y -= (1.f - aspect) * scale.y;
                }

                scale.y *= aspect;
            }
            else if (aspect > 1 && !(m_stretch & STRETCH_FLAGS_H)) {
                scale.x *= 1.f / aspect;

                if (translation.x > 0) {
                    translation.x += (aspect - 1.f) * scale.x;
                }
                else if (translation.x < 0) {
                    translation.x -= (aspect - 1.f) * scale.x;
                }
            }

            m_localMatrix = SR_MATH_NS::Matrix4x4(
                    translation,
                    m_rotation.Radians().ToQuat(),
                    scale,
                    m_skew
            );
        }
        else {
            m_localMatrix = SR_MATH_NS::Matrix4x4(
                    m_translation,
                    m_rotation.Radians().ToQuat(),
                    m_scale,
                    m_skew
            );
        }

        Transform::UpdateMatrix();
    }

    void Transform2D::SetGlobalTranslation(const SR_MATH_NS::FVector3 &translation) {
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

    void Transform2D::SetGlobalRotation(const SR_MATH_NS::FVector3& eulers) {
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

    void Transform2D::SetAnchor(const SR_MATH_NS::FRect &rect) {
        m_anchor = rect;
        UpdateTree();
    }

    void Transform2D::SetStretch(StretchFlags stretch) {
        m_stretch = stretch;
        UpdateTree();
    }

    Transform *Transform2D::Copy() const {
        auto&& pTransform = new Transform2D();

        pTransform->m_anchor = m_anchor;

        pTransform->m_stretch = m_stretch;

        pTransform->m_translation = m_translation;
        pTransform->m_rotation = m_rotation;
        pTransform->m_scale = m_scale;
        pTransform->m_skew = m_skew;

        return pTransform;
    }
}