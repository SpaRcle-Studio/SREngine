

# File InputDispatcher.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Input**](dir_64c7271ada2dca618cc461f22cf20f1f.md) **>** [**InputDispatcher.h**](InputDispatcher_8h.md)

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

#endif //SR_ENGINE_INPUTDISPATCHER_H
```


