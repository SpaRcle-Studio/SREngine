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

            //if (translation.x > 0) {
            //    translation.x += (aspect - 1.f) * scale.x;
            //}
            //else if (translation.x < 0) {
            //    translation.x -= (aspect - 1.f) * scale.x;
            //}
        };

        auto&& fitHeight = [&]() {
            scale.y *= aspect;

           //if (translation.y > 0) {
           //    translation.y += (1.f - aspect) * scale.y;
           //}
           //else if (translation.y < 0) {
           //    translation.y -= (1.f - aspect) * scale.y;
           //}
        };

        //auto&& otherAspect = (float)screenSize.Width() / (float)screenSize.Height();
        //auto&& myAspect = (float)_refferenceW / (float)_refferenceH;

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

        auto&& parentScale = pParent->GetScale();

        //auto&& parentTranslation = pParentTransform->GetTranslation2D();
        //auto&& parentScale = pParentTransform->GetScale2D();
        //SR_MATH_NS::FRect parentRect = SR_MATH_NS::FRect::FromTranslationAndScale(parentTranslation, parentScale);
        //SR_MATH_NS::FVector2 center =  SR_MATH_NS::FVector2(parentRect.x + (parentRect.w / 2), parentRect.y + (parentRect.h / 2));

        ///auto&& parentRect = SR_MATH_NS::FRect(0.f, 0.f, parentScale.x, parentScale.y);
        ///auto&& rect = SR_MATH_NS::FRect(0.f, 0.f, scale.x, scale.y);
        ///rect.x = (parentRect.w - rect.w) / 2.f;
        ///rect.y = (parentRect.h - rect.h) / 2.f;

        auto&& aspect = (parentScale / m_scale).XY().Aspect();
        auto&& horizontalAnchor = (aspect - 1.f) * (1.f / aspect);

        switch (m_anchor) {
            case Anchor::None:
                return m_translation + SR_MATH_NS::FVector3();
            case Anchor::MiddleLeft:
                return m_translation + SR_MATH_NS::FVector3(-horizontalAnchor, 0.f, 0.f);
            case Anchor::MiddleRight:
                return m_translation + SR_MATH_NS::FVector3(horizontalAnchor, 0.f, 0.f);
            default:
                return SR_MATH_NS::FVector3();
        }

        /*SR_MATH_NS::FRect rect = SR_MATH_NS::FRect::FromTranslationAndScale(center, scale.XY());

        switch (m_anchor) {
            case Anchor::None:
                return SR_MATH_NS::FVector3();
            case Anchor::TopLeft:
                rect.x -= parentRect.w / 2;
                rect.y -= parentRect.y / 2;
                break;
            case Anchor::TopCenter:
                rect.x = parentRect.x + (parentRect.w - rect.w) / 2;
                rect.y = parentRect.y;
                break;
            case Anchor::TopRight:
                rect.x = parentRect.x + parentRect.w - rect.w;
                rect.y = parentRect.y;
                break;
            case Anchor::MiddleLeft:
                rect.x = parentRect.x;
                rect.y = parentRect.y + (parentRect.h - rect.h) / 2;
                break;
            case Anchor::MiddleCenter:
                break;
            case Anchor::MiddleRight:
                rect.x = parentRect.x + parentRect.w - rect.w;
                rect.y = parentRect.y + (parentRect.h - rect.h) / 2;
                break;
            case Anchor::BottomLeft:
                rect.x = parentTranslation.x;
                rect.y = parentTranslation.y;
                break;
            case Anchor::BottomCenter:
                rect.x = parentRect.x + (parentRect.w - rect.w) / 2;
                rect.y = parentRect.y + parentRect.h - rect.h;
                break;
            case Anchor::BottomRight:
                rect.x = parentRect.x + parentRect.w - rect.w;
                rect.y = parentRect.y + parentRect.h - rect.h;
                break;
            default:
                SRHalt("Transform2D::CalculateAnchor() : unsupported anchor position!");
                return SR_MATH_NS::FVector3();
        }

        return SR_MATH_NS::FVector3(rect.x, rect.y, 0);*/
    }
}