

# File KeyCodes.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Input**](dir_133fa8d60355654b3e9ec84c6210a08b.md) **>** [**KeyCodes.h**](KeyCodes_8h.md)

[Go to the documentation of this file](KeyCodes_8h.md)


```C++
//
// Created by Monika on 17.02.2022.
//

#ifndef SR_ENGINE_KEYCODES_H
#define SR_ENGINE_KEYCODES_H

#include <Utils/Debug.h>

namespace SR_UTILS_NS {
    enum class KeyboardLayout : uint8_t {
        EN, RU, UNKNOWN
    };

    enum class KeyState : uint8_t {
        None, Down, Up, Press
    };

    enum class MouseCode : uint8_t {
        MouseLeft = 0,
        MouseRight = 1,
        MouseMiddle = 2,
        MouseButton4 = 3,
        MouseButton5 = 4,
        None = std::numeric_limits<uint8_t>::max() - 1
    };

    const MouseCode MouseCodes[] = {
        MouseCode::MouseLeft,
        MouseCode::MouseRight,
        MouseCode::MouseMiddle,
        MouseCode::MouseButton4,
        MouseCode::MouseButton5,
    };

    SR_ENUM_NS_CLASS_T(KeyCode, uint8_t,
        MouseLeft = 0,
        MouseRight = 1,
        MouseMiddle = 2,
        MouseButton4 = 3,
        MouseButton5 = 4,
        BackSpace = 8,
        Tab = 9,
        Enter = 13,
        LShift = 16,
        Ctrl = 17,
        Alt = 18,
        Esc = 27,
        Escape = 27,
        Space = 32,
        LeftArrow = 37,
        UpArrow = 38,
        RightArrow = 39,
        DownArrow = 40,
        Del = 46,

        _0 = 48,
        _1 = 49,
        _2 = 50,
        _3 = 51,
        _4 = 52,
        _5 = 53,
        _6 = 54,
        _7 = 55,
        _8 = 56,
        _9 = 57,

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        S = 83,
        R = 82,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        F1 = 112,
        F2 = 113,
        F3 = 114,
        F4 = 115,
        F5 = 116,
        F6 = 117,
        F7 = 118,
        F8 = 119,
        F9 = 120,
        F10 = 121,
        F11 = 122,
        F12 = 123,
        Plus = 187,
        Minus = 189,
        Dot = 190,
        Tilde = 192,
        None = std::numeric_limits<uint8_t>::max() - 1
    );

    const KeyCode KeyCodes[] = {
            KeyCode::BackSpace,
            KeyCode::Tab,
            KeyCode::Enter,
            KeyCode::LShift,
            KeyCode::Ctrl,
            KeyCode::Alt,
            KeyCode::Esc,
            KeyCode::Space,
            KeyCode::LeftArrow,
            KeyCode::UpArrow,
            KeyCode::RightArrow,
            KeyCode::DownArrow,
            KeyCode::Del,

            KeyCode::_0,
            KeyCode::_1,
            KeyCode::_2,
            KeyCode::_3,
            KeyCode::_4,
            KeyCode::_5,
            KeyCode::_6,
            KeyCode::_7,
            KeyCode::_8,
            KeyCode::_9,

            KeyCode::A,
            KeyCode::B,
            KeyCode::C,
            KeyCode::D,
            KeyCode::E,
            KeyCode::F,
            KeyCode::G,
            KeyCode::H,
            KeyCode::I,
            KeyCode::J,
            KeyCode::K,
            KeyCode::L,
            KeyCode::M,
            KeyCode::N,
            KeyCode::O,
            KeyCode::P,
            KeyCode::Q,
            KeyCode::S,
            KeyCode::R,
            KeyCode::T,
            KeyCode::U,
            KeyCode::V,
            KeyCode::W,
            KeyCode::X,
            KeyCode::Y,
            KeyCode::Z,
            KeyCode::F1,
            KeyCode::F2,
            KeyCode::F3,
            KeyCode::F4,
            KeyCode::F5,
            KeyCode::F6,
            KeyCode::F7,
            KeyCode::F8,
            KeyCode::F9,
            KeyCode::F10,
            KeyCode::F11,
            KeyCode::F12,
            KeyCode::Plus,
            KeyCode::Minus,
            KeyCode::Dot,
            KeyCode::Tilde,
    };
}

#endif //SR_ENGINE_KEYCODES_H
```


