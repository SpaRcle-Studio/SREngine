//
// Created by Monika on 17.02.2022.
//

#ifndef SRENGINE_INPUTHANDLER_H
#define SRENGINE_INPUTHANDLER_H

#include <Utils/Input/InputEvents.h>
#include <Utils/Events/Event.h>
#include <Utils/Input/InputSystem.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT InputHandler : public Event<KeyCode, MouseCode, KeyState> {
    protected:
        InputHandler()
            : Event(typeid(InputHandler).name())
        { }

        ~InputHandler() override = default;

    public:
        virtual void OnMousePress(const MouseDownEvent& event) { }
        virtual void OnMouseDown(const MouseDownEvent& event) { }
        virtual void OnMouseUp(const MouseUpEvent& event) { }

        virtual void OnKeyPress(const KeyPressEvent& event) { }
        virtual void OnKeyDown(const KeyDownEvent& event) { }
        virtual void OnKeyUp(const KeyUpEvent& event) { }

    protected:
        bool IsKeyPressed(KeyCode code) {
            return Input::GetKey(code);
        }

    private:
        void Trigger(KeyCode key, MouseCode mouse, KeyState state) override {
            if (key != KeyCode::None) {
                switch (state) {
                    case KeyState::Press: OnKeyPress(key); break;
                    case KeyState::Down: OnKeyDown(key); break;
                    case KeyState::Up: OnKeyUp(key); break;
                }
            }

            if (mouse != MouseCode::None) {
                switch (state) {
                    case KeyState::Press: OnMousePress(mouse); break;
                    case KeyState::Down: OnMouseDown(mouse); break;
                    case KeyState::Up: OnMouseUp(mouse); break;
                }
            }
        }
    };
}

#endif //SRENGINE_INPUTHANDLER_H
