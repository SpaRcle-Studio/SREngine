//
// Created by Monika on 20.11.2022.
//

#ifndef SR_ENGINE_UI_BUTTON_H
#define SR_ENGINE_UI_BUTTON_H

#include <Engine/stdInclude.h>

#include <Graphics/UI/Canvas.h>

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
    };

    /// @category(UI)
    class UIButton : public SR_UTILS_NS::Component, public SR_GRAPH_NS::UI::IFindCanvasOwner {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
        enum class State : uint8_t {
            Idle,
            Hovered,
            Pressed
        };
    public:
        void Update(float_t dt) override;

    private:
        State m_state = State::Idle;

    private:
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_idle;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_hovered;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_pressed;
        /// @property
        SR_UTILS_NS::Vector<UIButtonEvent> m_onClickEvents;

        /// @property @group(Mouse Events)
        bool m_leftClick = true;
        /// @property @group(Mouse Events)
        bool m_rightClick = false;
        /// @property @group(Mouse Events)
        bool m_middleClick = false;

    };
}

#endif //SR_ENGINE_UI_BUTTON_H
