//
// Created by Monika on 19.02.2022.
//

#ifndef SRENGINE_TRANSFORM3D_H
#define SRENGINE_TRANSFORM3D_H

#include <Utils/ECS/Transform.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT Transform3D : public Transform {
        friend class GameObject;
    public:
        Transform3D()
            : Transform()
        { }

    public:
        void UpdateMatrix() override;

        void Translate(const SR_MATH_NS::FVector3& translation) override;
        void Rotate(const SR_MATH_NS::FVector3& eulers) override;
        void Scale(const SR_MATH_NS::FVector3& scale) override;

        void RotateAround(const SR_MATH_NS::FVector3& point, const SR_MATH_NS::FVector3& eulers) override;
        void RotateAroundParent(const SR_MATH_NS::FVector3& eulers) override;

        /// Transforms direction from local space to world space
        SR_NODISCARD SR_MATH_NS::FVector3 TransformDirection(const SR_MATH_NS::FVector3& direction) const;

        void SetMatrix(const SR_MATH_NS::Matrix4x4& matrix) override;

        void SetTranslation(const SR_MATH_NS::FVector3& translation) override;
        void SetTranslationAndRotation(const SR_MATH_NS::FVector3& translation, const SR_MATH_NS::FVector3& euler) override;
        void SetRotation(const SR_MATH_NS::FVector3& euler) override;
        void SetScale(const SR_MATH_NS::FVector3& scale) override;
        void SetSkew(const SR_MATH_NS::FVector3& skew) override;

        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetMatrix() override;

        SR_NODISCARD SR_MATH_NS::FVector3 GetTranslation() const override { return m_translation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetRotation() const override { return m_rotation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetScale() const override { return m_scale; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetSkew() const override { return m_skew; }

        SR_NODISCARD Measurement GetMeasurement() const override { return Measurement::Space3D; }

    public:
        SR_INLINE static constexpr SR_MATH_NS::FVector3 RIGHT   = SR_MATH_NS::FVector3(1, 0, 0);
        SR_INLINE static constexpr SR_MATH_NS::FVector3 UP      = SR_MATH_NS::FVector3(0, 1, 0);
        SR_INLINE static constexpr SR_MATH_NS::FVector3 FORWARD = SR_MATH_NS::FVector3(0, 0, 1);

    protected:
        SR_MATH_NS::Matrix4x4 m_localMatrix = SR_MATH_NS::Matrix4x4::Identity();
        SR_MATH_NS::Matrix4x4 m_matrix = SR_MATH_NS::Matrix4x4::Identity();

        SR_MATH_NS::FVector3 m_translation = SR_MATH_NS::FVector3::Zero();
        SR_MATH_NS::FVector3 m_rotation = SR_MATH_NS::FVector3::Zero();;
        SR_MATH_NS::FVector3 m_scale = SR_MATH_NS::FVector3::One();
        SR_MATH_NS::FVector3 m_skew = SR_MATH_NS::FVector3::One();

    };
}


#endif //SRENGINE_TRANSFORM3D_H
