

# File WidgetPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**WidgetPass.h**](WidgetPass_8h.md)

[Go to the documentation of this file](WidgetPass_8h.md)


```C++
//
// Created by Monika on 14.07.2022.
//

#ifndef SR_ENGINE_WIDGETPASS_H
#define SR_ENGINE_WIDGETPASS_H

#include <Graphics/Pass/BasePass.h>

namespace SR_GRAPH_NS {
    class WidgetPass : public BasePass {
        SR_REGISTER_LOGICAL_NODE(WidgetPass, Widget Pass, { "Passes" })
        using Super = BasePass;
    public:
        void Prepare() override;
        bool Overlay() override;

    };
}


#endif //SR_ENGINE_WIDGETPASS_H
```


