//
// Created by Monika on 17.02.2022.
//

#include <Utils/Input/InputDispatcher.h>
#include <Utils/Input/InputHandler.h>
#include <Utils/Profile/TracyContext.h>

namespace SR_UTILS_NS {
    InputDispatcher::InputDispatcher()
        : Super()
    {
        m_keyboardData = new KeyboardInputData();
        m_mouseData = new MouseInputData();
    }

    InputDispatcher::~InputDispatcher() {
        SR_SAFE_DELETE_PTR(m_keyboardData);
        SR_SAFE_DELETE_PTR(m_mouseData);
    }

    void InputDispatcher::Check() {
        SR_TRACY_ZONE;
        CheckKeyboard();
        CheckMouse();
    }

    void InputDispatcher::CheckKeyboard() {
        SR_TRACY_ZONE;

        auto&& input = Input::Instance();

        for (auto&& code : KeyCodes) {
            if (input.GetKeyDown(code)) {
                m_keyboardData->m_state = KeyState::Down;
            }
            else if (input.GetKeyUp(code)) {
                m_keyboardData->m_state = KeyState::Up;
            }
            else if (input.GetKey(code)) {
                m_keyboardData->m_state = KeyState::Press;
            }
            else
                continue;

            m_keyboardData->m_code = code;

            Dispatch<InputHandler>(dynamic_cast<InputDeviceData*>(m_keyboardData));
        }
    }

    void InputDispatcher::CheckMouse() {
        SR_TRACY_ZONE;

        auto&& input = Input::Instance();

        for (auto&& code : MouseCodes) {
            if (input.GetMouseDown(code)) {
                m_mouseData->m_state = KeyState::Down;
            }
            else if (input.GetMouseUp(code)) {
                m_mouseData->m_state = KeyState::Up;
            }
            else if (input.GetMouse(code)) {
                m_mouseData->m_state = KeyState::Press;
            }
            else
                continue;

            m_mouseData->m_code = code;
            m_mouseData->m_wheel = input.GetMouseWheel();
            m_mouseData->m_position = input.GetMousePos();
            m_mouseData->m_prevPos = input.GetPrevMousePos();

            Dispatch<InputHandler>(dynamic_cast<InputDeviceData*>(m_mouseData));
        }
    }
}
