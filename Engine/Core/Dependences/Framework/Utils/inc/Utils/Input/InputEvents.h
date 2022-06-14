//
// Created by Monika on 17.02.2022.
//

#ifndef SRENGINE_INPUTEVENTS_H
#define SRENGINE_INPUTEVENTS_H

#include <Utils/Input/KeyCodes.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT KeyPressEvent {
    public:
        KeyPressEvent(KeyCode code)
            : m_code(code)
        { }

        SR_NODISCARD KeyCode GetKeyCode() const { return m_code; }

    private:
        KeyCode m_code;

    };

    class KeyDownEvent {
    public:
        KeyDownEvent(KeyCode code)
            : m_code(code)
        { }

        [[nodiscard]] KeyCode GetKeyCode() const { return m_code; }

    private:
        KeyCode m_code;

    };

    class KeyUpEvent {
    public:
        KeyUpEvent(KeyCode code)
            : m_code(code)
        { }

        [[nodiscard]] KeyCode GetKeyCode() const { return m_code; }

    private:
        KeyCode m_code;

    };

    class MouseDownEvent {
    public:
        MouseDownEvent(MouseCode code)
            : m_code(code)
        { }

        [[nodiscard]] MouseCode GetKeyCode() const { return m_code; }

    private:
        MouseCode m_code;

    };

    class MouseUpEvent {
    public:
        MouseUpEvent(MouseCode code)
            : m_code(code)
        { }

        [[nodiscard]] MouseCode GetKeyCode() const { return m_code; }

    private:
        MouseCode m_code;

    };
}

#endif //SRENGINE_INPUTEVENTS_H
