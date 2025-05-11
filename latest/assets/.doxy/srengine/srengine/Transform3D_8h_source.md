

# File Transform3D.h

[**File List**](files.md) **>** [**ECS**](dir_df4674c010a45d2af7a2a452a0d36896.md) **>** [**Transform3D.h**](Transform3D_8h.md)

[Go to the documentation of this file](Transform3D_8h.md)


```C++
//
// Created by Monika on 19.02.2022.
//

#ifndef SR_ENGINE_TRANSFORM3D_H
#define SR_ENGINE_TRANSFORM3D_H

#include <Utils/ECS/Transform.h>

namespace SR_UTILS_NS {
    class SR_COMMON_DLL_API Transform3D : public Transform {
        SR_CLASS()
        friend class GameObject;
        using Super = Transform;
    public:
        void Translate(const SR_MATH_NS::FVector3& translation) override;
        void Rotate(const SR_MATH_NS::FVector3& eulers) override;
        void Scale(const SR_MATH_NS::FVector3& scale) override;
        void Rotate(const SR_MATH_NS::Quaternion& q) override;

        void RotateAround(const SR_MATH_NS::FVector3& point, const SR_MATH_NS::FVector3& eulers) override;
        void RotateAroundParent(const SR_MATH_NS::FVector3& eulers) override;

        SR_NODISCARD SR_MATH_NS::FVector3 TransformDirection(const SR_MATH_NS::FVector3& direction) const;

        void SetMatrix(const std::optional<SR_MATH_NS::FVector3>& translation,
                       const std::optional<SR_MATH_NS::Quaternion>& rotation,
                       const std::optional<SR_MATH_NS::FVector3>& scale) override;

        void SetGlobalTranslation(const SR_MATH_NS::FVector3& translation) override;
        void SetGlobalRotation(const SR_MATH_NS::Quaternion& quaternion) override;

        void SetTranslation(const SR_MATH_NS::FVector3& translation) override;
        void SetTranslationAndRotation(const SR_MATH_NS::FVector3& translation, const SR_MATH_NS::FVector3& euler) override;
        void SetRotation(const SR_MATH_NS::FVector3& euler) override;
        void SetRotation(const SR_MATH_NS::Quaternion& quaternion) override;
        void SetScale(const SR_MATH_NS::FVector3& scale) override;
        void SetSkew(const SR_MATH_NS::FVector3& skew) override;

        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetMatrix() const override;

        SR_NODISCARD SR_MATH_NS::Quaternion GetQuaternion() const override { return m_quaternion; }

        SR_NODISCARD SR_MATH_NS::FVector3 GetTranslation() const override { return m_translation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetRotation() const override {
            if (m_eulersDirty) {
                m_rotation = m_quaternion.EulerAngle();
                m_eulersDirty = false;
            }
            return m_rotation;
        }
        SR_NODISCARD SR_MATH_NS::FVector3 GetScale() const override { return m_scale; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetSkew() const override { return m_skew; }

        void LookAt(const SR_MATH_NS::FVector3& position) override;
        void LookAt(const SR_MATH_NS::FVector3& position, LookAtAxis axis) override;

        SR_NODISCARD Measurement GetMeasurement() const override { return Measurement::Space3D; }

    private:
        void UpdateMatrix() const override;

    public:
        SR_INLINE static SR_MATH_NS::FVector3 RIGHT   = SR_MATH_NS::FVector3(1, 0, 0);
        SR_INLINE static SR_MATH_NS::FVector3 UP      = SR_MATH_NS::FVector3(0, 1, 0);
        SR_INLINE static SR_MATH_NS::FVector3 FORWARD = SR_MATH_NS::FVector3(0, 0, 1);

    protected:
        mutable SR_MATH_NS::Matrix4x4 m_localMatrix = SR_MATH_NS::Matrix4x4::Identity();
        mutable SR_MATH_NS::Matrix4x4 m_matrix = SR_MATH_NS::Matrix4x4::Identity();

        mutable bool m_eulersDirty = true;

        SR_MATH_NS::FVector3 m_translation = SR_MATH_NS::FVector3::Zero();
        mutable SR_MATH_NS::FVector3 m_rotation = SR_MATH_NS::FVector3::Zero();
        SR_MATH_NS::Quaternion m_quaternion = SR_MATH_NS::Quaternion::Identity();
        SR_MATH_NS::FVector3 m_scale = SR_MATH_NS::FVector3::One();
        SR_MATH_NS::FVector3 m_skew = SR_MATH_NS::FVector3::One();

    };
}


#endif //SR_ENGINE_TRANSFORM3D_H
```


