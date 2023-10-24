//
// Created by Monika on 01.08.2022.
//

#include <Utils/ECS/Transform2D.h>

namespace SR_UTILS_NS {
    Transform2D::Transform2D()
        : Transform()
    { }

    void Transform2D::SetTranslation(const SR_MATH_NS::FVector3& translation) {
        if (translation == m_translation) {
            return;
        }

        m_translation = translation;

        UpdateTree();
    }

    void Transform2D::SetTranslationAndRotation(const SR_MATH_NS::FVector3& translation, const SR_MATH_NS::FVector3& euler) {
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

    const SR_MATH_NS::Matrix4x4& Transform2D::GetMatrix() {
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
        auto&& scale = CalculateStretch();
        auto&& translation = CalculateAnchor(scale);

        m_localMatrix = SR_MATH_NS::Matrix4x4(
            translation,
            m_rotation.Radians().ToQuat(),
            m_scale * scale,
            m_skew
        );

        Transform::UpdateMatrix();
    }

    void Transform2D::SetGlobalTranslation(const SR_MATH_NS::FVector3& translation) {
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

    void Transform2D::SetGlobalRotation(const SR_MATH_NS::FVector3& euler) {
        if (auto&& pParent = GetParentTransform()) {
            auto&& matrix = SR_MATH_NS::Matrix4x4::FromScale(SR_MATH_NS::FVector3(1) / m_skew);
            matrix *= SR_MATH_NS::Matrix4x4::FromEulers(euler);
            matrix *= SR_MATH_NS::Matrix4x4::FromScale(m_scale);

            matrix = pParent->GetMatrix().Inverse() * matrix;

            SetRotation(matrix.GetEulers());
        }
        else {
            auto&& matrix = SR_MATH_NS::Matrix4x4::FromScale(SR_MATH_NS::FVector3(1) / m_skew);
            matrix *= SR_MATH_NS::Matrix4x4::FromEulers(euler);
            matrix *= SR_MATH_NS::Matrix4x4::FromScale(m_scale);

            SetRotation(matrix.GetEulers());
        }
    }

    void Transform2D::SetAnchor(Anchor anchorType) {
        m_anchor = anchorType;
        UpdateTree();
    }

    void Transform2D::SetStretch(Stretch stretch) {
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

    SR_MATH_NS::FVector3 Transform2D::CalculateStretch() const {
        auto&& pParent = dynamic_cast<Transform2D*>(GetParentTransform());
        if (!pParent) {
            return SR_MATH_NS::FVector3::One();
        }

        auto&& aspect = pParent->GetScale().XY().Aspect();
        if (SR_EQUALS(aspect, 0.f)) {
            return SR_MATH_NS::FVector3();
        }

        auto scale = SR_MATH_NS::FVector3::One();

        auto&& fitWidth = [&]() {
            scale.x *= 1.f / aspect;
        };

        auto&& fitHeight = [&]() {
            scale.y *= aspect;
        };

        /// Компенсация растяжения родительской ноды
        switch (m_stretch) {
            case Stretch::ChangeAspect:
                break;
            case Stretch::WidthControlsHeight:
                fitWidth();
                break;
            case Stretch::HeightControlsWidth:
                fitHeight();
                break;
            case Stretch::ShowAll: {
                if (aspect > 1.f) {
                    fitWidth();
                }
                else {
                    fitHeight();
                }
                break;
            }
            case Stretch::NoBorder: {
                if (aspect > 1.f) {
                    fitHeight();
                }
                else {
                    fitWidth();
                }
                break;
            }
            default:
                break;
        }

        return scale;
    }

    SR_MATH_NS::FVector3 Transform2D::CalculateAnchor(const SR_MATH_NS::FVector3& scale) const {
        auto&& pParent = dynamic_cast<Transform2D*>(GetParentTransform());
        if (!pParent) {
            return SR_MATH_NS::FVector3();
        }

        const auto parentScale = pParent->GetScale();

        SR_MATH_NS::FVector3 stretch;

        if (m_stretch == Stretch::ShowAll) {
            if (scale.XY().Aspect() > 1.f) {
                stretch = SR_MATH_NS::FVector3(1.f, 1.f, 1.f);
            }
            else {
                stretch = SR_MATH_NS::FVector3(scale.y, scale.x, 1.f);
            }
        }
        else if (m_stretch == Stretch::WidthControlsHeight) {
            stretch = parentScale;
        }
        else if (m_stretch == Stretch::ChangeAspect || m_stretch == Stretch::HeightControlsWidth) {
            stretch = SR_MATH_NS::FVector3(1.f);
        }
        else if (m_stretch == Stretch::NoBorder) {
            if (scale.XY().Aspect() > 1.f) {
                stretch = parentScale;
            }
            else {
                stretch = SR_MATH_NS::FVector3(1.f);
            }
        }

        const auto horizontalAspect = SR_MATH_NS::FVector2(stretch.XY() / m_scale.x).Aspect();
        const auto horizontalAnchor = (horizontalAspect - 1.f) * (1.f / horizontalAspect);

        const auto verticalAspect = SR_MATH_NS::FVector2(stretch.XY() / m_scale.y).AspectInv();
        const auto verticalAnchor = (verticalAspect - 1.f) * (1.f / verticalAspect);

        SR_MATH_NS::FVector3 translation = m_translation;

        if (m_anchor != Anchor::None) {
            translation = SR_MATH_NS::FVector3(
                m_translation.x * (1.f / horizontalAspect),
                m_translation.y * (1.f / verticalAspect),
                m_translation.z
            );
        }

        switch (m_anchor) {
            case Anchor::None:
            case Anchor::MiddleCenter:
                return translation;

            case Anchor::MiddleLeft:
                return translation + SR_MATH_NS::FVector3(-horizontalAnchor, 0.f, 0.f);
            case Anchor::MiddleRight:
                return translation + SR_MATH_NS::FVector3(horizontalAnchor, 0.f, 0.f);

            case Anchor::TopCenter:
                return translation + SR_MATH_NS::FVector3(0.f, verticalAnchor, 0.f);
            case Anchor::BottomCenter:
                return translation + SR_MATH_NS::FVector3(0.f, -verticalAnchor, 0.f);

            case Anchor::TopLeft:
                return translation + SR_MATH_NS::FVector3(-horizontalAnchor, verticalAnchor, 0.f);
            case Anchor::TopRight:
                return translation + SR_MATH_NS::FVector3(horizontalAnchor, verticalAnchor, 0.f);

            case Anchor::BottomLeft:
                return translation + SR_MATH_NS::FVector3(-horizontalAnchor, -verticalAnchor, 0.f);
            case Anchor::BottomRight:
                return translation + SR_MATH_NS::FVector3(horizontalAnchor, -verticalAnchor, 0.f);

            default:
                return SR_MATH_NS::FVector3();
        }
    }

    int32_t Transform2D::GetPriority() { /// NOLINT
        if (!m_isDirtyPriority) {
            return m_priority;
        }

        if (m_relativePriority) {
            if (auto&& pParentTransform = dynamic_cast<Transform2D*>(GetParentTransform())) {
                m_priority = m_localPriority + pParentTransform->GetPriority();
            }
            else {
                m_priority = m_localPriority;
            }
        }
        else {
            m_priority = m_localPriority;
        }

        m_isDirtyPriority = false;

        return m_priority;
    }
}