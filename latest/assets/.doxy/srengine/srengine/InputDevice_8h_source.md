

# File InputDevice.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Input**](dir_133fa8d60355654b3e9ec84c6210a08b.md) **>** [**InputDevice.h**](InputDevice_8h.md)

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


