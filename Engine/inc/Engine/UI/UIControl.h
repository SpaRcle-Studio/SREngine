//
// Created by Codex on 15.11.2026.
//

#ifndef SR_ENGINE_UI_CONTROL_H
#define SR_ENGINE_UI_CONTROL_H

#include <Engine/stdInclude.h>

#include <Graphics/UI/Canvas.h>

#include <Utils/UI/IUIInputTarget.h>
#include <Utils/UI/UIComponent.h>
#include <Utils/ECS/SceneObject.h>

namespace SR_CORE_UI_NS {
    struct UIButtonEvent : public SR_UTILS_NS::Serializable {
        SR_STRUCT()
    public:
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::Component> object;
        /// @property
        SR_UTILS_NS::StringAtom method;

        bool operator==(const UIButtonEvent& other) const noexcept {
            return object == other.object && method == other.method;
        }

        bool operator!=(const UIButtonEvent& other) const noexcept {
            return !(*this == other);
        }

        bool Invoke() const;
    };

    SR_ENUM_NS_CLASS_T(UIControlState, uint8_t, Idle, Hovered, Pressed, Selected, Disabled);

    /// @category(UI)
    class UIControl : public SR_UTILS_NS::UIComponent, public SR_GRAPH_UI_NS::IFindCanvasOwner, public SR_UTILS_NS::IUIInputTarget {
        SR_CLASS()
    public:
        SR_UTILS_NS::IUIInputTarget* GetUIInputTarget() noexcept override { return this; }
        bool HitTest(const SR_UTILS_NS::PointerEvent& event) override;
        int32_t GetInputPriority() const override;
        bool RequiresInputPolling() const override;
        void OnMatrixDirty() override;
        void OnPostLoad() override;
        /// @method @evaluate
        bool IsInteractable() const override { return m_interactable; }
        bool IsFocusable() const override { return m_focusable && m_interactable; }
        bool IsModal() const override { return m_modal; }
        void SetInputState(bool hovered, bool pressed, bool focused) override;
        void Cancel() override;
        /// @method
        void SetInteractable(bool value);
        /// @method @evaluate
        UIControlState GetState() const noexcept { return m_state; }
        /// @method
        void Focus();

    protected:
        void InvokeEvents(const SR_UTILS_NS::Vector<UIButtonEvent>& events);

    private:
        const SR_UTILS_NS::TransformRect* m_pHitRect = nullptr;
        SR_MATH_NS::Matrix4x4 m_hitInverse;
        bool m_hitMatrixDirty = true;
        /// @property @readOnly @dontSave
        UIControlState m_state = UIControlState::Idle;
        /// @property @setter(SetInteractable)
        bool m_interactable = true;
        /// @property @onChanged(InvalidateUIInput)
        bool m_focusable = true;
        /// @property @onChanged(InvalidateUIInput)
        bool m_modal = false;
        /// @property @onChanged(InvalidateUIInput)
        bool m_raycastTarget = true;
        /// @property
        SR_UTILS_NS::Vector<UIButtonEvent> m_onCancelEvents;
        /// @property @onChanged(InvalidateUIInput)
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_idle;
        /// @property @onChanged(InvalidateUIInput)
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_hovered;
        /// @property @onChanged(InvalidateUIInput)
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_pressed;
        /// @property @onChanged(InvalidateUIInput)
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_selected;
        /// @property @onChanged(InvalidateUIInput)
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_disabled;
    };
}

#endif // SR_ENGINE_UI_CONTROL_H
