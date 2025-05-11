

# File InputHandler.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Input**](dir_133fa8d60355654b3e9ec84c6210a08b.md) **>** [**InputHandler.h**](InputHandler_8h.md)

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
    class SR_COMMON_DLL_API InputHandler : public Event<InputDeviceData*> {
    protected:
        InputHandler();
        ~InputHandler() override;

    public:
        virtual void OnMouseMove(const MouseInputData* data);
        virtual void OnMousePress(const MouseInputData* data);
        virtual void OnMouseDown(const MouseInputData* data);
        virtual void OnMouseUp(const MouseInputData* data);

        virtual void OnKeyPress(const KeyboardInputData* data);
        virtual void OnKeyDown(const KeyboardInputData* data);
        virtual void OnKeyUp(const KeyboardInputData* data);

    protected:
        bool IsKeyPressed(KeyCode code);

    private:
        void Trigger(InputDeviceData* inputDeviceData) override;

        void TriggerKeyboard(KeyboardInputData* keyboardInputData);
        void TriggerMouse(MouseInputData* mouseInputData);

    };
}

#endif //SR_ENGINE_INPUTHANDLER_H
```


