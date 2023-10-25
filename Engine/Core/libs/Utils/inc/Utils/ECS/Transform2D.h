//
// Created by Monika on 01.08.2022.
//

#ifndef SRENGINE_TRANSFORM2D_H
#define SRENGINE_TRANSFORM2D_H

#include <Utils/ECS/Transform.h>
#include <Utils/Math/Rect.h>

namespace SR_UTILS_NS {
    class GameObject;

    /// растяжение по ширине родительского элемента
    SR_ENUM_NS_CLASS_T(Stretch, uint8_t ,
        ShowAll,
        NoBorder,
        ChangeAspect,
        WidthControlsHeight,
        HeightControlsWidth
    );

    SR_ENUM_NS_CLASS_T(Anchor, uint8_t,
        None,
        TopLeft, TopCenter, TopRight,
        MiddleLeft, MiddleCenter, MiddleRight,
        BottomLeft, BottomCenter, BottomRight
    );

    class SR_DLL_EXPORT Transform2D : public Transform {
        friend class GameObject;
    public:
        Transform2D();
        ~Transform2D() override = default;

    public:
        void SetTranslation(const SR_MATH_NS::FVector3& translation) override;
        void SetTranslationAndRotation(const SR_MATH_NS::FVector3& translation, const SR_MATH_NS::FVector3& euler) override;
        void SetRotation(const SR_MATH_NS::FVector3& euler) override;
        void SetScale(const SR_MATH_NS::FVector3& scale) override;
        void SetSkew(const SR_MATH_NS::FVector3& skew) override;

        void SetGlobalTranslation(const SR_MATH_NS::FVector3& translation) override;
        void SetGlobalRotation(const SR_MATH_NS::FVector3& eulers) override;

        void SetAnchor(Anchor anchorType);
        void SetStretch(Stretch stretch);

        void SetLocalPriority(int32_t priority) { m_localPriority = priority; m_isDirtyPriority = true; }
        void SetRelativePriority(bool relative) { m_relativePriority = relative; m_isDirtyPriority = true; }

        SR_NODISCARD SR_MATH_NS::FVector3 GetTranslation() const override { return m_translation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetRotation() const override { return m_rotation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetScale() const override { return m_scale; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetSkew() const override { return m_skew; }

        SR_NODISCARD Measurement GetMeasurement() const override { return Measurement::Space2D; }

        SR_NODISCARD Transform* Copy() const override;

        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetMatrix() override;

        SR_NODISCARD Anchor GetAnchor() const { return m_anchor; }
        SR_NODISCARD Stretch GetStretch() const { return m_stretch; }

        SR_NODISCARD int32_t GetPriority();
        SR_NODISCARD int32_t GetLocalPriority() const noexcept { return m_localPriority; }

        SR_NODISCARD bool IsRelativePriority() const noexcept { return m_relativePriority; }

    protected:
        void UpdateMatrix() override;
        SR_NODISCARD SR_MATH_NS::FVector3 CalculateStretch() const;
        SR_NODISCARD SR_MATH_NS::FVector3 CalculateAnchor(const SR_MATH_NS::FVector3& scale) const;

    public:
        SR_INLINE static constexpr SR_MATH_NS::FVector2 RIGHT = Math::FVector2(1, 0);
        SR_INLINE static constexpr SR_MATH_NS::FVector2 UP    = Math::FVector2(0, 1);

    protected:
        Anchor m_anchor = Anchor::None;
        Stretch m_stretch = Stretch::ShowAll;

        int32_t m_priority = 0;
        int32_t m_localPriority = 0;
        bool m_relativePriority = false;
        bool m_isDirtyPriority = true;

        SR_MATH_NS::Matrix4x4 m_localMatrix = SR_MATH_NS::Matrix4x4::Identity();
        SR_MATH_NS::Matrix4x4 m_matrix = SR_MATH_NS::Matrix4x4::Identity();

        SR_MATH_NS::FVector3 m_translation = SR_MATH_NS::FVector3::Zero();
        SR_MATH_NS::FVector3 m_rotation = SR_MATH_NS::FVector3::Zero();
        SR_MATH_NS::FVector3 m_scale = SR_MATH_NS::FVector3::One();
        SR_MATH_NS::FVector3 m_skew = SR_MATH_NS::FVector3::One();

    };
}

#endif //SRENGINE_TRANSFORM2D_H
