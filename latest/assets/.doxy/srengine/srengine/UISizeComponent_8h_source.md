

# File UISizeComponent.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**UI**](dir_0e9eeef58803927b1310c845186ea8b3.md) **>** [**UISizeComponent.h**](UISizeComponent_8h.md)

[Go to the documentation of this file](UISizeComponent_8h.md)


```C++
//
// Created by Monika on 19.01.2025.
//

#ifndef SR_GRAPHICS_UI_SIZE_COMPONENT_H
#define SR_GRAPHICS_UI_SIZE_COMPONENT_H

#include <Utils/UI/UIModifier.h>

namespace SR_GRAPH_UI_NS {
    class UISizeComponent : public SR_UTILS_NS::UI::UIModifierComponent {
        using Super = SR_UTILS_NS::UI::UIModifierComponent;
        SR_CLASS()
    public:
        void Prepare(SR_UTILS_NS::UI::UIModifierContext& context) const override;

    protected:
        void OnChanged();

    private:
        bool m_isWidthChangeable = true;
        bool m_isHeightChangeable = true;

    };
}

#endif //SR_GRAPHICS_UI_SIZE_COMPONENT_H
```


