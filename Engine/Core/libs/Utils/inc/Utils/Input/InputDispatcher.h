//
// Created by Monika on 17.02.2022.
//

#ifndef SRENGINE_INPUTDISPATCHER_H
#define SRENGINE_INPUTDISPATCHER_H

#include <Utils/Events/EventDispatcher.h>
#include <Utils/Input/InputDevice.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT InputDispatcher : public EventDispatcher {
        using Super = EventDispatcher;
    public:
        InputDispatcher();
        ~InputDispatcher() override;

    public:
        void Check();

    private:
        void CheckKeyboard();
        void CheckMouse();

    private:
        KeyboardInputData* m_keyboardData;
        MouseInputData* m_mouseData;

    };
}

#endif //SRENGINE_INPUTDISPATCHER_H
