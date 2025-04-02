

# File InputHandler.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Input**](dir_64c7271ada2dca618cc461f22cf20f1f.md) **>** [**InputHandler.h**](InputHandler_8h.md)

[Go to the documentation of this file](InputHandler_8h.md)


```C++
//
// Created by Monika on 17.02.2022.
//

#ifndef SR_ENGINE_INPUTHANDLER_H
#define SR_ENGINE_INPUTHANDLER_H

#include <Utils/Input/InputEvents.h>
#include <Utils/Events/Event.h>
#include <Utils/Input/InputSystem.h>
#include <Utils/Input/InputDevice.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT InputHandler : public Event<InputDeviceData*> {
    protected:
        InputHandler()
            : Event(typeid(InputHandler).name())
        { }

        ~InputHandler() override = default;

    public:
        virtual void OnMouseMove(const MouseInputData* data) { }
        virtual void OnMousePress(const MouseInputData* data) { }
        virtual void OnMouseDown(const MouseInputData* data) { }
        virtual void OnMouseUp(const MouseInputData* data) { }

        virtual void OnKeyPress(const KeyboardInputData* data) { }
        virtual void OnKeyDown(const KeyboardInputData* data) { }
        virtual void OnKeyUp(const KeyboardInputData* data) { }

    protected:
        bool IsKeyPressed(KeyCode code) {
            return Input::Instance().GetKey(code);
        }

    private:
        void Trigger(InputDeviceData* inputDeviceData) override;

        void TriggerKeyboard(KeyboardInputData* keyboardInputData);
        void TriggerMouse(MouseInputData* mouseInputData);

    };
}

#endif //SR_ENGINE_INPUTHANDLER_H
```


