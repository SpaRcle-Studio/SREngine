

# File Transform.h

[**File List**](files.md) **>** [**ECS**](dir_df4674c010a45d2af7a2a452a0d36896.md) **>** [**Transform.h**](Transform_8h.md)

[Go to the documentation of this file](Transform_8h.md)


```C++
//
// Created by Nikita on 27.11.2020.
//

#ifndef SR_ENGINE_TRANSFORM_H
#define SR_ENGINE_TRANSFORM_H

#include <Utils/Serialization/Serializable.h>
#include <Utils/Common/Measurement.h>

#include <Utils/Math/Mathematics.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Matrix4x4.h>
#include <Utils/Math/Quaternion.h>

#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/Function.h>

namespace SR_UTILS_NS {
    class GameObject;

    SR_ENUM_NS_CLASS_T(LookAtAxis, uint8_t,
        AxisX,
        AxisY,
        AxisZ,
        InvAxisX,
        InvAxisY,
        InvAxisZ
    );

    class Transform : public Serializable, public SR_HTYPES_NS::SharedPtr<Transform> {
        SR_CLASS()
        friend class GameObject;
        using Super = Serializable;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Transform>;

    public:
        Transform();
        ~Transform() override;

    public:
        void SetGameObject(GameObject* pGameObject);

        virtual void Translate(const SR_MATH_NS::FVector3& translation);
        virtual void Translate(SR_MATH_NS::Unit x, SR_MATH_NS::Unit y, SR_MATH_NS::Unit z);
        virtual void Rotate(const SR_MATH_NS::FVector3& eulers);
        virtual void Rotate(const SR_MATH_NS::Quaternion& q);
        virtual void Rotate(SR_MATH_NS::Unit x, SR_MATH_NS::Unit y, SR_MATH_NS::Unit z);
        virtual void Scale(const SR_MATH_NS::FVector3& scale);
        virtual void Scale(SR_MATH_NS::Unit x, SR_MATH_NS::Unit y, SR_MATH_NS::Unit z);

        virtual void GlobalTranslate(const SR_MATH_NS::FVector3& translation);
        virtual void GlobalRotate(const SR_MATH_NS::FVector3& eulers);
        virtual void GlobalRotate(const SR_MATH_NS::Quaternion& quaternion);
        virtual void GlobalRotate(SR_MATH_NS::Unit x, SR_MATH_NS::Unit y, SR_MATH_NS::Unit z);
        virtual void GlobalScale(const SR_MATH_NS::FVector3& scale);
        virtual void GlobalSkew(const SR_MATH_NS::FVector3& skew);

        virtual void RotateAround(const SR_MATH_NS::FVector3& point, const SR_MATH_NS::FVector3& eulers);
        virtual void RotateAroundParent(const SR_MATH_NS::FVector3& eulers);

        virtual void SetMatrix(const std::optional<SR_MATH_NS::FVector3>& translation,
                               const std::optional<SR_MATH_NS::Quaternion>& rotation,
                               const std::optional<SR_MATH_NS::FVector3>& scale);

        virtual void SetGlobalTranslation(const SR_MATH_NS::FVector3& translation);

        virtual void SetGlobalRotation(const SR_MATH_NS::FVector3& eulers);

        virtual void SetGlobalRotation(const SR_MATH_NS::Quaternion& quaternion);

        virtual void SetTranslation(const SR_MATH_NS::FVector3& translation);
        virtual void SetTranslation(SR_MATH_NS::Unit x, SR_MATH_NS::Unit y, SR_MATH_NS::Unit z);
        virtual void SetTranslationAndRotation(const SR_MATH_NS::FVector3& translation, const SR_MATH_NS::FVector3& euler);
        virtual void SetRotation(const SR_MATH_NS::FVector3& euler);
        virtual void SetRotation(const SR_MATH_NS::Quaternion& quaternion);
        virtual void SetRotation(SR_MATH_NS::Unit yaw, SR_MATH_NS::Unit pitch, SR_MATH_NS::Unit roll);
        virtual void SetScale(const SR_MATH_NS::FVector3& scale);
        virtual void SetScale(SR_MATH_NS::Unit x, SR_MATH_NS::Unit y, SR_MATH_NS::Unit z);
        virtual void SetSkew(const SR_MATH_NS::FVector3& skew);
        virtual void SetSkew(SR_MATH_NS::Unit x, SR_MATH_NS::Unit y, SR_MATH_NS::Unit z);

        virtual void LookAt(const SR_MATH_NS::FVector3& position);
        virtual void LookAt(const SR_MATH_NS::FVector3& position, LookAtAxis axis);

        SR_NODISCARD virtual const SR_MATH_NS::Matrix4x4& GetMatrix() const;

        SR_NODISCARD virtual SR_MATH_NS::Quaternion GetQuaternion() const;

        SR_NODISCARD virtual SR_MATH_NS::FVector3 Right() const;
        SR_NODISCARD virtual SR_MATH_NS::FVector3 Up() const;
        SR_NODISCARD virtual SR_MATH_NS::FVector3 Forward() const;

        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetTranslation() const;
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetRotation() const;
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetScale() const;
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetSkew() const;

        SR_NODISCARD virtual SR_MATH_NS::FVector2 GetTranslation2D() const;
        SR_NODISCARD virtual SR_MATH_NS::FVector2 GetScale2D() const;

        SR_NODISCARD Transform* GetParentTransform() const;
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<GameObject> GetGameObject() const;

        SR_NODISCARD virtual Measurement GetMeasurement() const = 0;
        SR_NODISCARD SR_FORCE_INLINE bool IsDirty() const noexcept { return m_dirtyMatrix; }

        void UpdateTree();
        virtual void OnHierarchyChanged();

    protected:
        virtual void UpdateMatrix() const;

    protected:
        GameObject* m_gameObject = nullptr;

    private:
        mutable bool m_dirtyMatrix = false;

    };
}

#endif //SR_ENGINE_TRANSFORM_H
```


