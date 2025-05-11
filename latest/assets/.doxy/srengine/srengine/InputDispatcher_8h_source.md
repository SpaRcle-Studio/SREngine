

# File InputDispatcher.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Input**](dir_133fa8d60355654b3e9ec84c6210a08b.md) **>** [**InputDispatcher.h**](InputDispatcher_8h.md)

[Go to the documentation of this file](InputDispatcher_8h.md)


```C++
//
// Created by Monika on 17.02.2022.
//

#ifndef SR_ENGINE_INPUTDISPATCHER_H
#define SR_ENGINE_INPUTDISPATCHER_H

#include <Utils/Events/EventDispatcher.h>
#include <Utils/Input/InputDevice.h>

namespace SR_UTILS_NS {
    class SR_COMMON_DLL_API InputDispatcher : public EventDispatcher {
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

#endif //SR_ENGINE_INPUTDISPATCHER_H
```


