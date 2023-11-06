//
// Created by Nikita on 30.12.2020.
//

#include <Utils/Input/InputSystem.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Profile/TracyContext.h>

#ifdef SR_WIN32
    #include <Windows.h>
#endif

namespace SR_UTILS_NS {
    void Input::Check() {
        SR_TRACY_ZONE;

        if (!m_init) {
            Reset();
            m_init = true;
        }

        m_mouseScroll = m_mouseScrollCurrent;
        m_mouseScrollCurrent = glm::vec2(0, 0);

        m_mousePrev = m_mouse;
        m_mouse = SR_PLATFORM_NS::GetMousePos();

        m_mouseDrag = m_mouse - m_mousePrev;

        if (!m_arr) {
            m_arr = new uint8_t[256];
            memset(m_arr, 0, sizeof(256));
        }

    #ifdef SR_WIN32
        GetKeyState(0);
        if (!GetKeyboardState(m_arr)) {
            return;
        }
    #endif

        for (uint16_t i = 0; i < 256; ++i) {
            if (m_arr[i] >> 7 != 0) {
                switch (m_keys[i]) {
                    case State::UnPressed:
                        m_keys[i] = State::Down;
                        break;
                    case State::Down:
                        m_keys[i] = State::Pressed;
                        break;
                    case State::Pressed:
                        //skip
                        break;
                    case State::Up:
                        m_keys[i] = State::Down;
                        break;
                }
            }
            else {
                switch (m_keys[i]) {
                    case State::UnPressed:
                        //skip
                        break;
                    case State::Down:
                        m_keys[i] = State::Up;
                        break;
                    case State::Pressed:
                        m_keys[i] = State::Up;
                        break;
                    case State::Up:
                        m_keys[i] = State::UnPressed;
                        break;
                }
            }
        }
    }

    bool Input::GetKeyDown(KeyCode key) {
        return m_keys[(int)key] == State::Down;
    }

    bool Input::GetKeyUp(KeyCode key) {
        return m_keys[(int)key] == State::Up;
    }

    bool Input::GetKey(KeyCode key) {
        return (m_keys[(int)key] == State::Pressed || m_keys[(int)key] == State::Down);
    }

    SR_MATH_NS::FVector2 Input::GetMouseDrag() {
        return m_mouseDrag;
    }

    int32_t Input::GetMouseWheel() {
        return m_mouseScroll.y;
    }

    int32_t Input::DebugKey() {
        if (!m_arr) {
            m_arr = new uint8_t[256];
            memset(m_arr, 0, sizeof(256));
        }

    #ifdef SR_WIN32
        GetKeyState(0);
        if (!GetKeyboardState(m_arr)) {
            return -1;
        }
    #endif

        for (uint16_t i = 0; i < 256; ++i) {
            if (m_arr[i] >> 7 != 0) {
                return i;
            }
        }

        return -1;
    }

    void Input::Reset() {
        for (auto& key : m_keys) {
            key = State::UnPressed;
        }

        ResetMouse();
    }

    void Input::ResetMouse() {
        m_mousePrev = m_mouse = SR_UTILS_NS::Platform::GetMousePos();
        m_mouseScroll = m_mouseScrollCurrent = SR_MATH_NS::FVector2(0.f);
    }

    void Input::Reload() {
        m_init = false;
        Reset();
    }

    void Input::LockCursor(bool isLock) {
        m_isLocked = isLock;
    }

    bool Input::IsMouseMoved() const {
        return GetMousePos() != GetPrevMousePos();
    }
}