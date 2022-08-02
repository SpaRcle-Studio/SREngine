//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_TRANSFORM_H
#define GAMEENGINE_TRANSFORM_H

#include <Utils/ECS/ISavable.h>

#include <Utils/Math/Mathematics.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Matrix4x4.h>
#include <Utils/Math/Quaternion.h>

#include <Utils/Types/SafePointer.h>

namespace SR_UTILS_NS {
    class GameObject;

    SR_ENUM_CLASS(Measurement,
        Space2D,
        Space3D,
        Space4D,
    );

    class SR_DLL_EXPORT Transform : public ISavable {
        friend class GameObject;
    public:
        Transform() = default;
        ~Transform() override = default;

    public:
        static Transform* Load(SR_HTYPES_NS::Marshal& marshal, GameObject* pGameObject);

    public:
        void SetGameObject(GameObject *gameObject);

        virtual void Translate(const Math::FVector3& translation) { }
        virtual void Translate(Math::Unit x, Math::Unit y, Math::Unit z);
        virtual void Rotate(const Math::FVector3& eulers) { }
        virtual void Rotate(Math::Unit x, Math::Unit y, Math::Unit z);
        virtual void Scale(const Math::FVector3& scale) { }
        virtual void Scale(Math::Unit x, Math::Unit y, Math::Unit z);

        virtual void GlobalTranslate(const Math::FVector3& translation);
        virtual void GlobalRotate(const Math::FVector3& eulers);
        virtual void GlobalRotate(Math::Unit x, Math::Unit y, Math::Unit z);
        virtual void GlobalScale(const Math::FVector3& scale);
        virtual void GlobalSkew(const Math::FVector3& skew);

        virtual void RotateAround(const Math::FVector3& point, const Math::FVector3& eulers) { }
        virtual void RotateAroundParent(const Math::FVector3& eulers) { }

        virtual void SetMatrix(const SR_MATH_NS::Matrix4x4& matrix) { }

        virtual void SetTranslation(const Math::FVector3& translation) { }
        virtual void SetTranslation(Math::Unit x, Math::Unit y, Math::Unit z);
        virtual void SetTranslationAndRotation(const Math::FVector3& translation, const Math::FVector3& euler) { }
        virtual void SetRotation(const Math::FVector3& euler) { }
        virtual void SetRotation(Math::Unit yaw, Math::Unit pitch, Math::Unit roll);
        virtual void SetScale(const Math::FVector3& scale) { }
        virtual void SetScale(Math::Unit x, Math::Unit y, Math::Unit z);
        virtual void SetSkew(const Math::FVector3& skew) { }
        virtual void SetSkew(Math::Unit x, Math::Unit y, Math::Unit z);

        SR_NODISCARD virtual const SR_MATH_NS::Matrix4x4& GetMatrix();

        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetTranslation() const { return SR_MATH_NS::FVector3(); }
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetRotation() const { return SR_MATH_NS::FVector3(); }
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetScale() const { return SR_MATH_NS::FVector3(); }
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetSkew() const { return SR_MATH_NS::FVector3(); }

        SR_NODISCARD virtual SR_MATH_NS::FVector2 GetScale2D() const;

        SR_NODISCARD Transform* GetParentTransform() const;

        SR_NODISCARD virtual Measurement GetMeasurement() const = 0;

        SR_NODISCARD SR_HTYPES_NS::Marshal Save(SavableFlags flags) const override;

    protected:
        virtual void UpdateMatrix() { }
        virtual void UpdateTree();

    protected:
        GameObject* m_gameObject = nullptr;
        bool m_dirtyMatrix = true;

    };
}

#endif //GAMEENGINE_TRANSFORM_H
