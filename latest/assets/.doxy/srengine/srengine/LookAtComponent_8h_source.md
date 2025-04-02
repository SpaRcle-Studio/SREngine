

# File LookAtComponent.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Game**](dir_29b5b52e34c278ad0cd05efb71f95f71.md) **>** [**LookAtComponent.h**](LookAtComponent_8h.md)

[Go to the documentation of this file](LookAtComponent_8h.md)


```C++
//
// Created by Monika on 03.05.2023.
//

#ifndef SR_ENGINE_LOOKATCOMPONENT_H
#define SR_ENGINE_LOOKATCOMPONENT_H

#include <Utils/ECS/EntityRef.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT LookAtComponent final : public Component {
        SR_CLASS()
        using Super = Component;
    public:
        LookAtComponent();

    public:
        void Update(float_t dt) override;

        void OnDestroy() override;

        void SetTarget(const GameObject::Ptr& target) { m_target.SetPathTo(target->GetThis().DynamicCast<Entity>()); }
        void SetAxis(LookAtAxis axis);
        void SetExecuteInEditMode(bool enabled);
        void SetDelay(float_t delay) { m_delay = SR_MAX(delay, 0.f); }
        void SetMirror(bool mirror);
        void SetOffset(const SR_MATH_NS::FVector3& offset);

        SR_NODISCARD bool ExecuteInEditMode() const override { return m_editMode; }
        SR_NODISCARD bool GetMirror() const noexcept { return m_mirror; }
        SR_NODISCARD SR_MATH_NS::IVector3 GetAngle() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetOffset() const noexcept { return m_offset; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetUp() const noexcept;
        SR_NODISCARD SR_MATH_NS::FVector3 GetDirection() const noexcept { return m_direction; }
        SR_NODISCARD SR_UTILS_NS::EntityRef& GetTarget() { return m_target; }
        SR_NODISCARD float_t GetDelay() const noexcept { return m_delay; }
        SR_NODISCARD LookAtAxis GetAxis() const noexcept { return m_axis; }

    private:
        SR_MATH_NS::FVector3 m_direction;
        bool m_reached = false;

        SR_UTILS_NS::EntityRef m_target;
        LookAtAxis m_axis = LookAtAxis::AxisY;
        SR_MATH_NS::FVector3 m_offset;
        bool m_mirror = false;
        bool m_editMode = false;
        float_t m_delay = 0.f;

    };
}

#endif //SR_ENGINE_LOOKATCOMPONENT_H
```


