//
// Created by Monika on 01.08.2022.
//

#ifndef SRENGINE_TRANSFORM2D_H
#define SRENGINE_TRANSFORM2D_H

#include <Utils/ECS/Transform.h>

namespace SR_UTILS_NS {
    class GameObject;

    class SR_DLL_EXPORT Transform2D : public Transform {
        friend class GameObject;
    public:
        Transform2D()
            : Transform()
        { }

        ~Transform2D() override = default;

    public:
        void SetTranslation(const SR_MATH_NS::FVector3& translation) override;
        void SetTranslationAndRotation(const SR_MATH_NS::FVector3& translation, const SR_MATH_NS::FVector3& euler) override;
        void SetRotation(const SR_MATH_NS::FVector3& euler) override;
        void SetScale(const SR_MATH_NS::FVector3& scale) override;
        void SetSkew(const SR_MATH_NS::FVector3& skew) override;

        SR_NODISCARD SR_MATH_NS::FVector3 GetTranslation() const override { return m_translation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetRotation() const override { return m_rotation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetScale() const override { return m_scale; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetSkew() const override { return m_skew; }
        SR_NODISCARD Measurement GetMeasurement() const override { return Measurement::Space2D; }

    public:
        SR_INLINE static constexpr SR_MATH_NS::FVector2 RIGHT = Math::FVector2(1, 0);
        SR_INLINE static constexpr SR_MATH_NS::FVector2 UP    = Math::FVector2(0, 1);

    protected:
        SR_MATH_NS::FVector2 m_pivot = SR_MATH_NS::FVector2::Zero();
        SR_MATH_NS::FVector2 m_size = SR_MATH_NS::FVector2(100.f);

        SR_MATH_NS::FVector2 m_anchorMin = SR_MATH_NS::FVector2::Zero();
        SR_MATH_NS::FVector2 m_anchorMax = SR_MATH_NS::FVector2::Zero();

        SR_MATH_NS::FVector3 m_translation = SR_MATH_NS::FVector3::Zero();
        SR_MATH_NS::FVector3 m_rotation = SR_MATH_NS::FVector3::Zero();
        SR_MATH_NS::FVector3 m_scale = SR_MATH_NS::FVector3::One();
        SR_MATH_NS::FVector3 m_skew = SR_MATH_NS::FVector3::One();

    };
}

#endif //SRENGINE_TRANSFORM2D_H
