

# File InputDevice.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Input**](dir_64c7271ada2dca618cc461f22cf20f1f.md) **>** [**InputDevice.h**](InputDevice_8h.md)

[Go to the documentation of this file](InputDevice_8h.md)


```C++
//
// Created by Monika on 16.06.2022.
//

#ifndef SR_ENGINE_INPUTDEVICE_H
#define SR_ENGINE_INPUTDEVICE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Input/KeyCodes.h>
#include <Utils/Math/Vector2.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(InputDeviceType, uint8_t,
        Unknown,
        Mouse,
        Keyboard,
        Joystick
    );

    class SR_COMMON_DLL_API InputDeviceData : public NonCopyable {
    public:
        ~InputDeviceData() override = default;

    public:
        virtual InputDeviceType GetType() const = 0;

    };

    class SR_COMMON_DLL_API MouseInputData : public InputDeviceData {
    public:
        ~MouseInputData() override = default;

        MouseInputData(MouseCode code, KeyState state,
            const SR_MATH_NS::FVector2& pos,
            const SR_MATH_NS::FVector2& prevPos,
            const SR_MATH_NS::FVector2& wheel
        )
            : m_code(code)
            , m_state(state)
            , m_position(pos)
            , m_prevPos(prevPos)
            , m_wheel(wheel)
        { }

        MouseInputData()
            : m_code(MouseCode::None)
            , m_state(KeyState::None)
        { }

    public:
        InputDeviceType GetType() const override;

        SR_NODISCARD SR_MATH_NS::FVector2 GetDrag() const;
        SR_NODISCARD bool IsDrag() const;

    public:
        MouseCode m_code;
        KeyState m_state;
        SR_MATH_NS::FVector2 m_position;
        SR_MATH_NS::FVector2 m_prevPos;
        SR_MATH_NS::FVector2 m_wheel;

    };

    class SR_COMMON_DLL_API KeyboardInputData : public InputDeviceData {
    public:
        KeyboardInputData(KeyCode code, KeyState state)
            : m_code(code)
            , m_state(state)
        { }

        KeyboardInputData()
            : KeyboardInputData(KeyCode::None, KeyState::None)
        { }

    public:
        InputDeviceType GetType() const override;
        SR_NODISCARD KeyCode GetKeyCode() const;

    public:
        KeyCode m_code;
        KeyState m_state;

    };
}

#endif //SR_ENGINE_INPUTDEVICE_H
```


