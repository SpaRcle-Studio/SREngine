

# File Button.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**UI**](dir_f89d18ec897b372d467eb4c1a2d57055.md) **>** [**Button.h**](Button_8h.md)

[Go to the documentation of this file](Button_8h.md)


```C++
//
// Created by Monika on 20.11.2022.
//

#ifndef SR_ENGINE_UI_BUTTON_H
#define SR_ENGINE_UI_BUTTON_H

#include <Engine/UI/IButton.h>

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


