

# File UICanvasComponent.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**UI**](dir_4db2cc8eada578aa57e9f12bf4119b9f.md) **>** [**UICanvasComponent.h**](UICanvasComponent_8h.md)

[Go to the documentation of this file](UICanvasComponent_8h.md)


```C++
//
// Created by Monika on 19.01.2025.
//

#ifndef SR_UTILS_UI_CANVAS_COMPONENT_H
#define SR_UTILS_UI_CANVAS_COMPONENT_H

#include <Utils/UI/UIModifier.h>

namespace SR_GRAPH_UI_NS {
    class UICanvasComponent : public SR_UTILS_NS::UI::UIModifierComponent {
        using Super = SR_UTILS_NS::UI::UIModifierComponent;
        SR_CLASS()
    public:
        void Prepare(SR_UTILS_NS::UI::UIModifierContext& context) const override;

    };
}

#endif //SR_UTILS_UI_CANVAS_COMPONENT_H
```


