

# File InputSystem.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Input**](dir_64c7271ada2dca618cc461f22cf20f1f.md) **>** [**InputSystem.h**](InputSystem_8h.md)

[Go to the documentation of this file](InputSystem_8h.md)


```C++
//
// Created by Nikita on 30.12.2020.
//

#ifndef SR_ENGINE_INPUTSYSTEM_H
#define SR_ENGINE_INPUTSYSTEM_H

#include <Utils/Math/Vector2.h>
#include <Utils/Input/KeyCodes.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Common/SubscriptionHolder.h>

namespace SR_UTILS_NS {
    class Input : public Singleton<Input>, public SubscriptionHolder {
        SR_REGISTER_SINGLETON(Input)

        enum class State {
            UnPressed, Down, Pressed, Up
        };
        using CursorLockCallback = SR_HTYPES_NS::Function<void()>;

    protected:
        ~Input() override;

    public:
        void SetMouseScroll(double_t xOffset, double_t yOffset);

        void Check();
        void Reload();
        void ResetMouse();

        SR_NODISCARD SR_MATH_NS::FVector2 GetMouseDrag();
        SR_NODISCARD SR_MATH_NS::FVector2 GetMousePos() const;
        SR_NODISCARD SR_MATH_NS::FVector2 GetPrevMousePos() const;
        SR_NODISCARD bool IsMouseMoved() const;

        int32_t GetMouseWheel();

        bool GetMouseDown(MouseCode code);
        bool GetMouseUp(MouseCode code);
        bool GetMouse(MouseCode code);

        bool GetKeyDown(KeyCode key);
        bool GetKeyUp(KeyCode key);
        bool GetKey(KeyCode key);

        void SetCursorVisible(bool isVisible);
        void SetCursorLockCallback(CursorLockCallback&& callback);

        void LockCursor();
        void UnlockCursor();
        void ForceUnlockCursor();

    private:
        void Reset();
        void SetState(uint16_t keyIndex, State state);

    private:
        uint32_t m_counterLock = 0;
        CursorLockCallback m_lockCursorCallback;

        SR_MATH_NS::FVector2 m_mouseDrag;
        SR_MATH_NS::FVector2 m_mousePrev;
        SR_MATH_NS::FVector2 m_mouse;
        SR_MATH_NS::FVector2 m_mouseScroll;
        SR_MATH_NS::FVector2 m_mouseScrollCurrent;

        std::atomic<bool> m_init = false;
        std::atomic<bool> m_isVisible = true;

        State m_keys[256] = { };
        uint8_t* m_arr = nullptr;
    };

    class CursorLock : public NonCopyable {
    public:
        CursorLock();
        ~CursorLock();
        CursorLock(CursorLock&& ref) noexcept;
        CursorLock& operator=(CursorLock&& other) noexcept;

    private:
        bool m_isLock = false;

    };
}

#endif //SR_ENGINE_INPUTSYSTEM_H
```


