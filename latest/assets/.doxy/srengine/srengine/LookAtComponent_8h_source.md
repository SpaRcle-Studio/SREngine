

# File LookAtComponent.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Game**](dir_8f1885d18d834cf9a317dd74a37ec10b.md) **>** [**LookAtComponent.h**](LookAtComponent_8h.md)

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
    class SR_COMMON_DLL_API LookAtComponent final : public Component {
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


