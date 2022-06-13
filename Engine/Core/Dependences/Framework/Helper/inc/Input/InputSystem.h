//
// Created by Nikita on 30.12.2020.
//

#ifndef GAMEENGINE_INPUTSYSTEM_H
#define GAMEENGINE_INPUTSYSTEM_H

#include <Math/Vector2.h>
#include <Input/KeyCodes.h>

namespace Framework::Helper {
    // TODO: make singleton!
    class Input {
        enum class State{
            UnPressed, Down, Pressed, Up
        };

    public:
        Input() = delete;
        Input(Input&) = delete;
        ~Input() = delete;
    private:
        inline static Math::FVector2 g_mouse_old             = Math::FVector2();
        inline static Math::FVector2 g_mouse                 = Math::FVector2();

        inline static Math::FVector2 g_mouseScroll           = Math::FVector2();
        inline static Math::FVector2 g_mouseScrollCurrent    = Math::FVector2();

        inline static unsigned char* g_arr                        = nullptr;
    private:
        inline static std::atomic<bool> g_init = false;
        inline static State g_keys[256];
    public:
        inline static void SetMouseScroll(double xoffset, double yoffset){
            g_mouseScrollCurrent = { (float_t)xoffset, (float_t)yoffset };
        }

        static void Check();
        static void Reload();

        static Math::FVector2 GetMouseDrag();

        static int GetMouseWheel();

        static int DebugKey();

        static bool GetMouseDown(MouseCode code) { return GetKeyDown(static_cast<KeyCode>(code)); }
        static bool GetMouseUp(MouseCode code) { return GetKeyUp(static_cast<KeyCode>(code)); }
        static bool GetMouse(MouseCode code) { return GetKey(static_cast<KeyCode>(code)); }

        static bool GetKeyDown(KeyCode key);
        static bool GetKeyUp(KeyCode key);
        static bool GetKey(KeyCode key);
    private:
        static void Reset();

    };
}

#endif //GAMEENGINE_INPUTSYSTEM_H
