//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_INPUT_H
#define GAMEENGINE_INPUT_H

#include <iostream>
#include <string>
#include <map>
#include <thread>

#ifdef WIN32
    #include <Windows.h>
#else
    #include <conio.h>
    #include <stdio.h>
#endif

#define GetKeyDown(key) Input::BaseGetKeyDown(key, __FILE__, __LINE__)
#define GetKeyUp(key) Input::BaseGetKeyUp(key, __FILE__, __LINE__)
#define GetKey(key) Input::BaseGetKey(key)

#include <glm/glm.hpp>

namespace Framework::Helper {
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
    private:
        inline static auto m_registred_calls = std::map<const char *, std::map<int, bool>>();
    private:
        Input() = default;
        ~Input() = default;
    public:
        static glm::vec2 GetMouseDrag(){
            static glm::vec2 old;

            glm::vec2 now = GetMousePos();
            glm::vec2 res = old - now;
            old = now;

            return res;
        }

        inline static void SetMousePosition(int x, int y){
#ifdef WIN32
            SetCursorPos(x, y);
#else

#endif
        }

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
        /* Need for debugging input system */ // TODO: NOT WORK
        [[noreturn]]
        static inline void PrintPressedKeys() noexcept {
            while(true){
                int k = GetKeyPressedId();
                if (k != 0)
                    std::cout << k << std::endl;
            }
        }
        static int GetKeyPressedId();

        static bool BaseGetKey(KeyCode key);

        static bool BaseGetKeyDown(KeyCode key, const char *file, int line) noexcept {
            bool is_pressed = BaseGetKey(key);

            auto find_file = m_registred_calls.find(file);
            if (find_file == m_registred_calls.end())
                m_registred_calls.insert(std::make_pair(file, std::map<int, bool>()));
            auto &found_file = m_registred_calls[file];

            auto find_line = found_file.find(line);
            if (find_line == found_file.end()) {
                found_file.insert(std::make_pair(line, is_pressed));
                return is_pressed;
            } else {
                bool &temp = find_line->second;
                if (is_pressed && temp)
                    return false;
                else if (!is_pressed && !temp)
                    return false;
                else {
                    temp = is_pressed;
                    return is_pressed;
                }
            }
        }

        static bool BaseGetKeyUp(KeyCode key, const char *file, int line) noexcept {
            bool is_pressed = BaseGetKey(key);

            auto find_file = m_registred_calls.find(file);
            if (find_file == m_registred_calls.end())
                m_registred_calls.insert(std::make_pair(file, std::map<int, bool>()));
            auto &found_file = m_registred_calls[file];

            auto find_line = found_file.find(line);
            if (find_line == found_file.end()) {
                found_file.insert(std::make_pair(line, is_pressed));
                return is_pressed;
            } else {
                bool &temp = find_line->second;
                if (is_pressed && temp)
                    return false;
                else if (!is_pressed && !temp)
                    return false;
                else {
                    temp = is_pressed;
                    return !is_pressed;
                }
            }
        }
    };
}

#endif //GAMEENGINE_INPUT_H
