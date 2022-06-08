//
// Created by Nikita on 30.12.2020.
//

#include <Input/InputSystem.h>
#include <Platform/Platform.h>

namespace SR_UTILS_NS {
    void Input::Check() {
        if (!Input::g_init) {
            Reset();
            g_init = true;
        }

        g_mouseScroll = g_mouseScrollCurrent;
        g_mouseScrollCurrent = glm::vec2(0,0);

        g_mouse_old = g_mouse;
        g_mouse = Helper::Platform::GetMousePos();

        if (!g_arr) {
            g_arr = new BYTE[256];
            memset(g_arr, 0, sizeof(256));
        }

        GetKeyState(0);
        if (GetKeyboardState(g_arr)) {
            for (int i = 0; i < 256; i++)
                if (g_arr[i] >> 7 != 0) {
                    switch (g_keys[i]) {
                        case State::UnPressed:
                            g_keys[i] = State::Down;
                            break;
                        case State::Down:
                            g_keys[i] = State::Pressed;
                            break;
                        case State::Pressed:
                            //skip
                            break;
                        case State::Up:
                            g_keys[i] = State::Down;
                            break;
                    }
                } else {
                    switch (g_keys[i]) {
                        case State::UnPressed:
                            //skip
                            break;
                        case State::Down:
                            g_keys[i] = State::Up;
                            break;
                        case State::Pressed:
                            g_keys[i] = State::Up;
                            break;
                        case State::Up:
                            g_keys[i] = State::UnPressed;
                            break;
                    }
                }
        }

        //delete[] arr;
    }

    bool Input::GetKeyDown(Framework::Helper::KeyCode key) {
        return g_keys[(int)key] == State::Down;
    }

    bool Input::GetKeyUp(Framework::Helper::KeyCode key) {
        return g_keys[(int)key] == State::Up;
    }

    bool Input::GetKey(KeyCode key) {
        return (g_keys[(int)key] == State::Pressed || g_keys[(int)key] == State::Down);
    }

    SR_MATH_NS::FVector2 Framework::Helper::Input::GetMouseDrag() {
        return g_mouse - g_mouse_old;
    }

    int Input::GetMouseWheel() {
        return g_mouseScroll.y;
    }

    int Input::DebugKey() {
        if (!g_arr) {
            g_arr = new BYTE[256];
            memset(g_arr, 0, sizeof(256));
        }

        GetKeyState(0);
        if (GetKeyboardState(g_arr))
            for (int i = 0; i < 256; i++)
                if (g_arr[i] >> 7 != 0)
                    return i;
        return -1;
    }

    void Input::Reset() {
        for (auto &g_key : g_keys)
            g_key = State::UnPressed;
        g_mouse_old = g_mouse = Helper::Platform::GetMousePos();
        g_mouseScroll = g_mouseScrollCurrent = glm::vec2(0,0);
    }

    void Input::Reload() {
        g_init = false;
        Reset();
    }
}