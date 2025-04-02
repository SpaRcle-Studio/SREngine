

# File XKeySymToKeyCode.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Platform**](dir_dff07e13fcd57a959fed4d2a16791af6.md) **>** [**XKeySymToKeyCode.h**](XKeySymToKeyCode_8h.md)

[Go to the documentation of this file](XKeySymToKeyCode_8h.md)


```C++
//
// Created by innerviewer on 2024-05-26.
//

#ifndef SR_COMMON_XKEYSYM_TO_KEYCODE_H
#define SR_COMMON_XKEYSYM_TO_KEYCODE_H

namespace SR_PLATFORM_NS {
    static std::map<KeySym, uint8_t> keysymToIndex = {
        {XK_BackSpace, 8}, // KeyCode::BackSpace = 8
        {XK_Tab, 9}, // KeyCode::Tab = 9
        {XK_Return, 13}, // KeyCode::Enter = 13
        {XK_Shift_L, 16}, // KeyCode::LShift = 16
        {XK_Control_L, 17}, // KeyCode::Ctrl = 17
        {XK_Alt_L, 18}, // KeyCode::Alt = 18
        {XK_Escape, 27}, // KeyCode::Esc = 27
        {XK_space, 32}, // KeyCode::Space = 32
        {XK_Left, 37}, // KeyCode::LeftArrow = 37
        {XK_Up, 38}, // KeyCode::UpArrow = 38
        {XK_Right, 39}, // KeyCode::RightArrow = 39
        {XK_Down, 40}, // KeyCode::DownArrow = 40
        {XK_Delete, 46}, // KeyCode::Del = 46
        {XK_0, 48}, // KeyCode::_0 = 48
        {XK_1, 49}, // KeyCode::_1 = 49
        {XK_2, 50}, // KeyCode::_2 = 50
        {XK_3, 51}, // KeyCode::_3 = 51
        {XK_4, 52}, // KeyCode::_4 = 52
        {XK_5, 53}, // KeyCode::_5 = 53
        {XK_6, 54}, // KeyCode::_6 = 54
        {XK_7, 55}, // KeyCode::_7 = 55
        {XK_8, 56}, // KeyCode::_8 = 56
        {XK_9, 57}, // KeyCode::_9 = 57
        {XK_A, 65}, // KeyCode::A = 65
        {XK_a, 65}, // KeyCode::A = 65
        {XK_B, 66}, // KeyCode::B = 66
        {XK_b, 66}, // KeyCode::B = 66
        {XK_C, 67}, // KeyCode::C = 67
        {XK_c, 67}, // KeyCode::C = 67
        {XK_D, 68}, // KeyCode::D = 68
        {XK_d, 68}, // KeyCode::D = 68
        {XK_E, 69}, // KeyCode::E = 69
        {XK_e, 69}, // KeyCode::E = 69
        {XK_F, 70}, // KeyCode::F = 70
        {XK_f, 70}, // KeyCode::F = 70
        {XK_G, 71}, // KeyCode::G = 71
        {XK_g, 71}, // KeyCode::G = 71
        {XK_H, 72}, // KeyCode::H = 72
        {XK_h, 72}, // KeyCode::H = 72
        {XK_I, 73}, // KeyCode::I = 73
        {XK_i, 73}, // KeyCode::I = 73
        {XK_J, 74}, // KeyCode::J = 74
        {XK_j, 74}, // KeyCode::J = 74
        {XK_K, 75}, // KeyCode::K = 75
        {XK_k, 75}, // KeyCode::K = 75
        {XK_L, 76}, // KeyCode::L = 76
        {XK_l, 76}, // KeyCode::L = 76
        {XK_M, 77}, // KeyCode::M = 77
        {XK_m, 77}, // KeyCode::M = 77
        {XK_N, 78}, // KeyCode::N = 78
        {XK_n, 78}, // KeyCode::N = 78
        {XK_O, 79}, // KeyCode::O = 79
        {XK_o, 79}, // KeyCode::O = 79
        {XK_P, 80}, // KeyCode::P = 80
        {XK_p, 80}, // KeyCode::P = 80
        {XK_Q, 81}, // KeyCode::Q = 81
        {XK_q, 81}, // KeyCode::Q = 81
        {XK_R, 82}, // KeyCode::R = 82
        {XK_r, 82}, // KeyCode::R = 82
        {XK_S, 83}, // KeyCode::S = 83
        {XK_s, 83}, // KeyCode::S = 83
        {XK_T, 84}, // KeyCode::T = 84
        {XK_t, 84}, // KeyCode::T = 84
        {XK_U, 85}, // KeyCode::U = 85
        {XK_u, 85}, // KeyCode::U = 85
        {XK_V, 86}, // KeyCode::V = 86
        {XK_v, 86}, // KeyCode::V = 86
        {XK_W, 87}, // KeyCode::W = 87
        {XK_w, 87}, // KeyCode::W = 87
        {XK_X, 88}, // KeyCode::X = 88
        {XK_x, 88}, // KeyCode::X = 88
        {XK_Y, 89}, // KeyCode::Y = 89
        {XK_y, 89}, // KeyCode::Y = 89
        {XK_Z, 90}, // KeyCode::Z = 90
        {XK_z, 90}, // KeyCode::Z = 90
        {XK_F1, 112}, // KeyCode::F1 = 112
        {XK_F2, 113}, // KeyCode::F2 = 113
        {XK_F3, 114}, // KeyCode::F3 = 114
        {XK_F4, 115}, // KeyCode::F4 = 115
        {XK_F5, 116}, // KeyCode::F5 = 116
        {XK_F6, 117}, // KeyCode::F6 = 117
        {XK_F7, 118}, // KeyCode::F7 = 118
        {XK_F8, 119}, // KeyCode::F8 = 119
        {XK_F9, 120}, // KeyCode::F9 = 120
        {XK_F10, 121}, // KeyCode::F10 = 121
        {XK_F11, 122}, // KeyCode::F11 = 122
        {XK_F12, 123}, // KeyCode::F12 = 123
        {XK_plus, 187}, // KeyCode::Plus = 187
        {XK_minus, 189}, // KeyCode::Minus = 189
        {XK_period, 190}, // KeyCode::Dot = 190
        {XK_asciitilde, 192} // KeyCode::Tilde = 192
    };

}

#endif //SR_COMMON_XKEYSYM_TO_KEYCODE_H
```


