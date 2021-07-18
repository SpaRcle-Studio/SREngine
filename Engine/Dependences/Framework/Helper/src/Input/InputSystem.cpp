//
// Created by Nikita on 30.12.2020.
//

#include "Input/InputSystem.h"

void Framework::Helper::Input::Check() {
    if (!Input::g_init) {
        for (auto &g_key : g_keys)
            g_key = State::UnPressed;
        g_init = true;
    }

    g_mouseScroll = g_mouseScrollCurrent;
    g_mouseScrollCurrent = glm::vec2(0,0);

    g_mouse_old = g_mouse;
    g_mouse = Helper::GetMousePos();

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

bool Framework::Helper::Input::GetKeyDown(Framework::Helper::KeyCode key) {
    return g_keys[(int)key] == State::Down;
}

bool Framework::Helper::Input::GetKeyUp(Framework::Helper::KeyCode key) {
    return g_keys[(int)key] == State::Up;
}

bool Framework::Helper::Input::GetKey(KeyCode key) {
    return (g_keys[(int)key] == State::Pressed || g_keys[(int)key] == State::Down);
}

Framework::Helper::Math::Vector2 Framework::Helper::Input::GetMouseDrag() {
    return g_mouse - g_mouse_old;
}

int Framework::Helper::Input::GetMouseWheel() {
    return g_mouseScroll.y;
}
