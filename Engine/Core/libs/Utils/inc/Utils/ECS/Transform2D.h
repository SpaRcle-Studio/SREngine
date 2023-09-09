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
    SR_ENUM_NS_STRUCT_T(Stretch, uint32_t,
          None = 1 << 0,
          Width = 1 << 1,
          Height = 1 << 2,
          WidthHeight = Width | Height
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

        void SetAnchor(const SR_MATH_NS::FRect& rect);
        void SetStretch(StretchFlag stretch);

        SR_NODISCARD SR_MATH_NS::FVector3 GetTranslation() const override { return m_translation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetRotation() const override { return m_rotation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetScale() const override { return m_scale; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetSkew() const override { return m_skew; }

        SR_NODISCARD Measurement GetMeasurement() const override { return Measurement::Space2D; }

        SR_NODISCARD Transform* Copy() const override;

        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetMatrix() override;

        SR_NODISCARD SR_MATH_NS::FRect GetAnchor() const { return m_anchor; }
        SR_NODISCARD StretchFlag GetStretch() const { return m_stretch; }

    protected:
        void UpdateMatrix() override;

    public:
        SR_INLINE static constexpr SR_MATH_NS::FVector2 RIGHT = Math::FVector2(1, 0);
        SR_INLINE static constexpr SR_MATH_NS::FVector2 UP    = Math::FVector2(0, 1);

    protected:
        SR_MATH_NS::FRect m_anchor;

        StretchFlag m_stretch = Stretch::None;

        SR_MATH_NS::Matrix4x4 m_localMatrix = SR_MATH_NS::Matrix4x4::Identity();
        SR_MATH_NS::Matrix4x4 m_matrix = SR_MATH_NS::Matrix4x4::Identity();

        SR_MATH_NS::FVector3 m_translation = SR_MATH_NS::FVector3::Zero();
        SR_MATH_NS::FVector3 m_rotation = SR_MATH_NS::FVector3::Zero();
        SR_MATH_NS::FVector3 m_scale = SR_MATH_NS::FVector3::One();
        SR_MATH_NS::FVector3 m_skew = SR_MATH_NS::FVector3::One();

    };
}

#endif //SRENGINE_TRANSFORM2D_H
