//
// Created by Monika on 16.06.2022.
//

#include <Utils/Input/InputDevice.h>

namespace SR_UTILS_NS {
    InputDeviceType MouseInputData::GetType() const {
        return InputDeviceType::Mouse;
    }

    SR_MATH_NS::FVector2 MouseInputData::GetDrag() const {
        return m_position - m_prevPos;
    }

    bool MouseInputData::IsDrag() const {
        return !GetDrag().Empty();
    }

    InputDeviceType KeyboardInputData::GetType() const {
        return InputDeviceType::Keyboard;
    }

    KeyCode KeyboardInputData::GetKeyCode() const {
        return m_code;
    }
}
