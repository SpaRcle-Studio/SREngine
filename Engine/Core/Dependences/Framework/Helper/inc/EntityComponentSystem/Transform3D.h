//
// Created by Monika on 19.02.2022.
//

#ifndef SRENGINE_TRANSFORM3D_H
#define SRENGINE_TRANSFORM3D_H

#include <Math/Mathematics.h>

#include <Math/Vector3.h>
#include <Math/Matrix4x4.h>
#include <Math/Quaternion.h>

#include <Types/SafePointer.h>
#include <EntityComponentSystem/ISavable.h>

namespace SR_UTILS_NS {
    class GameObject;

    class Transform3D : public ISavable {
        friend class GameObject;
    public:
        explicit Transform3D(GameObject* parent);

        Transform3D()
            : Transform3D(nullptr)
        { }

    public:
        void Translate(Math::FVector3 translation);
        void Rotate(Math::FVector3 eulers);
        void Rotate(Math::Unit x, Math::Unit y, Math::Unit z);

        void GlobalTranslate(Math::FVector3 translation);
        void GlobalRotate(Math::FVector3 eulers);
        void GlobalRotate(Math::Unit x, Math::Unit y, Math::Unit z);

        void GlobalScale(const Math::FVector3& scale);
        void GlobalSkew(const Math::FVector3& skew);

        void RotateAround(Math::FVector3 point, Math::FVector3 eulers);
        void RotateAroundParent(Math::FVector3 eulers);

        /// Transforms direction from local space to world space
        SR_NODISCARD Math::FVector3 TransformDirection(Math::FVector3 direction) const;

        SR_NODISCARD Math::FVector3 GetTranslation() const { return m_translation; }
        SR_NODISCARD Math::FVector3 GetRotation() const { return m_rotation; }
        SR_NODISCARD Math::FVector3 GetScale() const { return m_scale; }
        SR_NODISCARD Math::FVector3 GetSkew() const { return m_skew; }

        void SetTranslation(Math::FVector3 translation);
        void SetTranslation(Math::Unit x, Math::Unit y, Math::Unit z);
        void SetTranslationAndRotation(const Math::FVector3& translation, const Math::FVector3& euler);
        void SetRotation(Math::FVector3 euler);
        void SetRotation(Math::Unit yaw, Math::Unit pitch, Math::Unit roll);
        void SetScale(Math::FVector3 scale);
        void SetScale(Math::Unit x, Math::Unit y, Math::Unit z);
        void SetSkew(Math::FVector3 skew);
        void SetSkew(Math::Unit x, Math::Unit y, Math::Unit z);

        SR_NODISCARD MarshalEncodeNode Save(SavableFlags flags) const override;
        static Transform3D* Load(const MarshalDecodeNode& node);

    private:
        void SetGameObject(GameObject* gameObject);
        void OnParentSet(Transform3D* parent);
        void UpdateComponents();

    public:
        inline static const Math::FVector3 RIGHT   = Math::FVector3(1, 0, 0);
        inline static const Math::FVector3 UP      = Math::FVector3(0, 1, 0);
        inline static const Math::FVector3 FORWARD = Math::FVector3(0, 0, 1);

    private:
        Transform3D* m_parent     = nullptr;
        GameObject*  m_gameObject = nullptr;

        Math::FVector3 m_translation;
        Math::FVector3 m_rotation;
        Math::FVector3 m_scale;
        Math::FVector3 m_skew;

    };
}


#endif //SRENGINE_TRANSFORM3D_H
