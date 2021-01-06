//
// Created by Nikita on 30.12.2020.
//

#ifndef GAMEENGINE_INPUTSYSTEM_H
#define GAMEENGINE_INPUTSYSTEM_H

#include <Input/Input.h>

namespace Framework::Helper {
    class InputSystem {
        enum class State{
            UnPressed, Down, Pressed, Up
        };

        InputSystem() = delete;
        InputSystem(InputSystem&) = delete;
        ~InputSystem() = delete;
    private:
        inline static glm::vec2 g_mouse_old     = glm::vec2();
        inline static glm::vec2 g_mouse         = glm::vec2();
    private:
        inline static bool g_init = false;
        inline static State g_keys[256];
    public:
        static void Check();

        static glm::vec2 MouseDrag();

        static bool IsDown(KeyCode key);
        static bool IsUp(KeyCode key);
        static bool IsPressed(KeyCode key);
    };
}

#endif //GAMEENGINE_INPUTSYSTEM_H
