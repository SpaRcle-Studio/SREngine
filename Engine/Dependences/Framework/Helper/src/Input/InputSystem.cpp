//
// Created by Nikita on 30.12.2020.
//

#include "Input/InputSystem.h"

void Framework::Helper::InputSystem::Check() {
    if (!InputSystem::g_init) {
        for (auto &g_key : g_keys)
            g_key = State::UnPressed;
        g_init = true;
    }

    BYTE *arr = new BYTE[256];

    memset(arr, 0, sizeof(256));
    GetKeyState(0);
    if (GetKeyboardState(arr)) {
        for (int i = 0; i < 256; i++)
            if (arr[i] >> 7 != 0) {
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

    delete[] arr;
}

bool Framework::Helper::InputSystem::IsDown(Framework::Helper::KeyCode key) {
    return g_keys[(int)key] == State::Down;
}

bool Framework::Helper::InputSystem::IsUp(Framework::Helper::KeyCode key) {
    return g_keys[(int)key] == State::Up;
}

bool Framework::Helper::InputSystem::IsPressed(Framework::Helper::KeyCode key) {
    return (g_keys[(int)key] == State::Pressed || g_keys[(int)key] == State::Down);
}
