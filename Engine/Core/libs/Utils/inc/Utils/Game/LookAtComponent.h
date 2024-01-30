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
        SR_ENTITY_SET_VERSION(1003);
        SR_INITIALIZE_COMPONENT(LookAtComponent);
        using Super = Component;
    public:
        LookAtComponent();

    private:
        ~LookAtComponent() override = default;

    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

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

        SR_NODISCARD Component* CopyComponent() const override;

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SavableContext data) const override;

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
