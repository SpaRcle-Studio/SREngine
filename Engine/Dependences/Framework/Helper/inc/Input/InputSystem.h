//
// Created by Nikita on 30.12.2020.
//

#ifndef GAMEENGINE_INPUTSYSTEM_H
#define GAMEENGINE_INPUTSYSTEM_H

//#include <Input/Input.h>

#include <glm/vec2.hpp>

#ifdef WIN32
    #include <Windows.h>
#include <Math/Vector2.h>

#else
    #include <conio.h>
    #include <stdio.h>
#endif

namespace Framework::Helper {
    static glm::vec2 GetMousePos() {
        #ifdef WIN32
                POINT p;
                GetCursorPos(&p);
                return { p.x, p.y };
        #else
                return {
                        wherex(),
                        wherey()
                    };
        #endif
    }

    enum class KeyboardLayout {
        EN, RU, UNKNOWN
    };

    enum class KeyCode {
        MouseLeft = 1,
        MouseRight = 2,
        MouseMiddle = 4,
        BackSpace = 8,
        Tab = 9,
        Enter = 13,
        LShift = 16,
        Ctrl = 17,
        Alt = 18,
        Esc = 27,
        Space = 32,
        LeftArrow = 37,
        UpArrow = 38,
        RightArrow = 39,
        DownArrow = 40,
        Del = 46,
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
        Plus = 187, Minus = 189,
        Dot = 190,
        Tilde = 192,

        _0 = 48,
        _1 = 49,
        _2 = 50,
        _3 = 51,
        _4 = 52,
        _5 = 53,
        _6 = 54,
        _7 = 55,
        _8 = 56,
        _9 = 57
    };

    class Input {
        enum class State{
            UnPressed, Down, Pressed, Up
        };

        Input() = delete;
        Input(Input&) = delete;
        ~Input() = delete;
    private:
        inline static glm::vec2 g_mouse_old             = glm::vec2();
        inline static glm::vec2 g_mouse                 = glm::vec2();

        inline static glm::vec2 g_mouseScroll           = glm::vec2();
        inline static glm::vec2 g_mouseScrollCurrent    = glm::vec2();

        inline static BYTE*     g_arr                   = nullptr;
    private:
        inline static bool g_init = false;
        inline static State g_keys[256];
    public:
        inline static void SetMouseScroll(double xoffset, double yoffset){
            g_mouseScrollCurrent = { xoffset, yoffset };
        }

        static void Check();

        static Math::Vector2 GetMouseDrag();

        static int GetMouseWheel();

        static int DebugKey();

        static bool GetKeyDown(KeyCode key);
        static bool GetKeyUp(KeyCode key);
        static bool GetKey(KeyCode key);
    };
}

#endif //GAMEENGINE_INPUTSYSTEM_H
