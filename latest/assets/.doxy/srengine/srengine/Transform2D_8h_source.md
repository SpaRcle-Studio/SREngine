

# File Transform2D.h

[**File List**](files.md) **>** [**ECS**](dir_df4674c010a45d2af7a2a452a0d36896.md) **>** [**Transform2D.h**](Transform2D_8h.md)

[Go to the documentation of this file](Transform2D_8h.md)


```C++
//
// Created by Monika on 01.08.2022.
//

#ifndef SR_ENGINE_TRANSFORM2D_H
#define SR_ENGINE_TRANSFORM2D_H

#include <Utils/ECS/Transform.h>
#include <Utils/UI/UIModifier.h>
#include <Utils/Math/Rect.h>

namespace SR_UTILS_NS {
    class GameObject;

    class SR_COMMON_DLL_API Transform2D : public Transform {
        SR_CLASS()
        friend class GameObject;
    public:
        Transform2D();

    public:
        void SetTranslation(const SR_MATH_NS::FVector3& translation) override;
        void SetTranslationAndRotation(const SR_MATH_NS::FVector3& translation, const SR_MATH_NS::FVector3& euler) override;
        void SetRotation(const SR_MATH_NS::FVector3& euler) override;
        void SetRotation(const SR_MATH_NS::Quaternion& quaternion) override;
        void SetScale(const SR_MATH_NS::FVector3& scale) override;
        void SetSkew(const SR_MATH_NS::FVector3& skew) override;

        void Translate(const SR_MATH_NS::FVector3& translation) override;
        void Rotate(const SR_MATH_NS::Quaternion& quaternion) override;
        void Scale(const SR_MATH_NS::FVector3& scale) override;

        void SetGlobalTranslation(const SR_MATH_NS::FVector3& translation) override;
        void SetGlobalRotation(const SR_MATH_NS::Quaternion& quaternion) override;

        void SetLocalPriority(int32_t priority);
        void SetRelativePriority(bool relative);

        SR_NODISCARD SR_MATH_NS::FVector3 GetTranslation() const override { return m_translation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetRotation() const override { return m_rotation; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetScale() const override { return m_scale; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetSkew() const override { return m_skew; }

        SR_NODISCARD Measurement GetMeasurement() const override { return Measurement::Space2D; }

        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetMatrix() const override;

        SR_NODISCARD int32_t GetPriority();
        SR_NODISCARD int32_t GetLocalPriority() const noexcept { return m_localPriority; }

        SR_NODISCARD bool IsRelativePriority() const noexcept { return m_relativePriority; }

        void OnHierarchyChanged() override;

        void AddModifier(UI::UIModifierComponent* pModifier) { m_modifiers.emplace_back(pModifier); }
        void RemoveModifier(UI::UIModifierComponent* pModifier);

        void OnUITreeChanged();

    protected:
        void UpdateMatrix() const override;
        void BuildUITree();

        SR_NODISCARD SR_MATH_NS::FVector2 GetSize() const;

    public:
        SR_INLINE static constexpr SR_MATH_NS::FVector2 RIGHT = Math::FVector2(1, 0);
        SR_INLINE static constexpr SR_MATH_NS::FVector2 UP    = Math::FVector2(0, 1);

    private:
        void UpdatePriorityTree();

    protected:
        mutable SR_MATH_NS::FSize2 m_contentSize;
        mutable SR_MATH_NS::Matrix4x4 m_localMatrix = SR_MATH_NS::Matrix4x4::Identity();
        mutable SR_MATH_NS::Matrix4x4 m_matrix = SR_MATH_NS::Matrix4x4::Identity();

        std::vector<UI::UIModifierComponent*> m_modifiers;

        bool m_isDirtyPriority = true;
        int32_t m_priority = 0;

        SR_MATH_NS::FVector3 m_translation = SR_MATH_NS::FVector3::Zero();
        SR_MATH_NS::FVector3 m_rotation = SR_MATH_NS::FVector3::Zero();
        SR_MATH_NS::Quaternion m_quaternion = SR_MATH_NS::Quaternion::Identity();
        SR_MATH_NS::FVector3 m_scale = SR_MATH_NS::FVector3::One();
        SR_MATH_NS::FVector3 m_skew = SR_MATH_NS::FVector3::One();

        int32_t m_localPriority = 0;
        bool m_relativePriority = true;

    };
}

#endif //SR_ENGINE_TRANSFORM2D_H
```


