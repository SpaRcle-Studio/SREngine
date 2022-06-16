//
// Created by Nikita on 30.12.2020.
//

#ifndef GAMEENGINE_INPUTSYSTEM_H
#define GAMEENGINE_INPUTSYSTEM_H

#include <Utils/Math/Vector2.h>
#include <Utils/Input/KeyCodes.h>
#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT Input : public Singleton<Input> {
        friend class Singleton<Input>;

        enum class State{
            UnPressed, Down, Pressed, Up
        };

    protected:
        ~Input() override = default;

    public:
        void SetMouseScroll(double_t xOffset, double_t yOffset){
            m_mouseScrollCurrent = { (float_t)xOffset, (float_t)yOffset };
        }

        void Check();
        void Reload();

        SR_MATH_NS::FVector2 GetMouseDrag();
        SR_MATH_NS::FVector2 GetMousePos() const { return m_mouse; }
        SR_MATH_NS::FVector2 GetPrevMousePos() const { return m_mousePrev; }

        int32_t GetMouseWheel();
        int32_t DebugKey();

        bool GetMouseDown(MouseCode code) { return GetKeyDown(static_cast<KeyCode>(code)); }
        bool GetMouseUp(MouseCode code) { return GetKeyUp(static_cast<KeyCode>(code)); }
        bool GetMouse(MouseCode code) { return GetKey(static_cast<KeyCode>(code)); }

        bool GetKeyDown(KeyCode key);
        bool GetKeyUp(KeyCode key);
        bool GetKey(KeyCode key);

    private:
        void Reset();

    private:
        SR_MATH_NS::FVector2 m_mousePrev;
        SR_MATH_NS::FVector2 m_mouse;
        SR_MATH_NS::FVector2 m_mouseScroll;
        SR_MATH_NS::FVector2 m_mouseScrollCurrent;

        uint8_t* m_arr = nullptr;
        std::atomic<bool> m_init = false;

        State m_keys[256] = { };

    };
}

#endif //GAMEENGINE_INPUTSYSTEM_H
