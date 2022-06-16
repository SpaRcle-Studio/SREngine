//
// Created by Monika on 16.06.2022.
//

#ifndef SRENGINE_INPUTDEVICE_H
#define SRENGINE_INPUTDEVICE_H

#include <Utils/Common/NonCopyable.h>

namespace SR_UTILS_NS {
    SR_ENUM_CLASS_T(InputDeviceType, uint8_t,
        Unknown,
        Mouse,
        Keyboard,
        Joystick
    );

    class SR_DLL_EXPORT InputDeviceData : public NonCopyable {
    public:
        ~InputDeviceData() override = default;

    public:
        virtual InputDeviceType GetType() const = 0;

    };

    class SR_DLL_EXPORT MouseInputData : public InputDeviceData {
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

    class SR_DLL_EXPORT KeyboardInputData : public InputDeviceData {
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

#endif //SRENGINE_INPUTDEVICE_H
