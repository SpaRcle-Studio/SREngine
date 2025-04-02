

# File Button.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**UI**](dir_cc73cebd6e5b9422e99f13db48e24fb3.md) **>** [**Button.h**](Button_8h.md)

[Go to the documentation of this file](Button_8h.md)


```C++
//
// Created by Monika on 20.11.2022.
//

#ifndef SR_ENGINE_UI_BUTTON_H
#define SR_ENGINE_UI_BUTTON_H

#include <Core/UI/IButton.h>

namespace SR_CORE_UI_NS {
    class Button : public IButton {
        using Super = IButton;
        SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_BUTTON_IDLE_PROP_NAME = "Idle";
        SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_BUTTON_HOVERED_PROP_NAME = "Hovered";
        SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_BUTTON_PRESSED_PROP_NAME = "Pressed";
    public:
        bool InitializeEntity() noexcept override;
        void OnDestroy() override;
        void Update(float_t dt) override;

    };
}

#endif //SR_ENGINE_UI_BUTTON_H
```


