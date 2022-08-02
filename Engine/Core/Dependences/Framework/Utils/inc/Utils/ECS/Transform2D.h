//
// Created by Monika on 01.08.2022.
//

#ifndef SRENGINE_TRANSFORM2D_H
#define SRENGINE_TRANSFORM2D_H

#include <Utils/ECS/Transform3D.h>

namespace SR_UTILS_NS {
    class GameObject;

    class SR_DLL_EXPORT Transform2D : public Transform3D {
        friend class GameObject;
    public:
        Transform2D()
            : Transform3D()
        { }

        ~Transform2D() override = default;

    public:
        void SetTranslation(const SR_MATH_NS::FVector3& translation) override;
        void SetTranslationAndRotation(const SR_MATH_NS::FVector3& translation, const SR_MATH_NS::FVector3& euler) override;
        void SetRotation(const SR_MATH_NS::FVector3& euler) override;
        void SetScale(const SR_MATH_NS::FVector3& scale) override;
        void SetSkew(const SR_MATH_NS::FVector3& skew) override;

        SR_NODISCARD Measurement GetMeasurement() const override { return Measurement::Space2D; }

    public:
        SR_INLINE static const SR_MATH_NS::FVector2 RIGHT = Math::FVector2(1, 0);
        SR_INLINE static const SR_MATH_NS::FVector2 UP    = Math::FVector2(0, 1);

    };
}

#endif //SRENGINE_TRANSFORM2D_H
