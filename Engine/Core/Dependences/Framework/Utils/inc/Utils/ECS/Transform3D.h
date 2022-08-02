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
        void Translate(const Math::FVector3& translation) override;
        void Rotate(const Math::FVector3& eulers) override;
        void Scale(const Math::FVector3& scale) override;

        void GlobalTranslate(const Math::FVector3& translation) override;
        void GlobalRotate(const Math::FVector3& eulers) override;

        void GlobalScale(const Math::FVector3& scale) override;
        void GlobalSkew(const Math::FVector3& skew) override;

        void RotateAround(const Math::FVector3& point, const Math::FVector3& eulers) override;
        void RotateAroundParent(const Math::FVector3& eulers) override;

        /// Transforms direction from local space to world space
        SR_NODISCARD Math::FVector3 TransformDirection(const Math::FVector3& direction) const;

        void SetTranslation(const Math::FVector3& translation) override;
        void SetTranslationAndRotation(const Math::FVector3& translation, const Math::FVector3& euler) override;
        void SetRotation(const Math::FVector3& euler) override;
        void SetScale(const Math::FVector3& scale) override;
        void SetSkew(const Math::FVector3& skew) override;

        SR_NODISCARD SR_MATH_NS::FVector3 GetTranslation() const override { return m_translation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetRotation() const override { return m_rotation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetScale() const override { return m_scale; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetSkew() const override { return m_skew; }

        SR_NODISCARD Measurement GetMeasurement() const override { return Measurement::Space3D; }

    public:
        SR_INLINE static const Math::FVector3 RIGHT   = Math::FVector3(1, 0, 0);
        SR_INLINE static const Math::FVector3 UP      = Math::FVector3(0, 1, 0);
        SR_INLINE static const Math::FVector3 FORWARD = Math::FVector3(0, 0, 1);

    protected:
        Math::FVector3 m_translation = Math::FVector3::Zero();
        Math::FVector3 m_rotation = Math::FVector3::Zero();;
        Math::FVector3 m_scale = Math::FVector3::One();
        Math::FVector3 m_skew = Math::FVector3::One();

    };
}


#endif //SRENGINE_TRANSFORM3D_H
