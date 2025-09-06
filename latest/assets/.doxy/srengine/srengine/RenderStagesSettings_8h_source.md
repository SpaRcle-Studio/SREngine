

# File RenderStagesSettings.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Settings**](dir_a48bca76098a55b82b6b979c436fb568.md) **>** [**RenderStagesSettings.h**](RenderStagesSettings_8h.md)

[Go to the documentation of this file](RenderStagesSettings_8h.md)


```C++
//
// Created by Monika on 31.07.2025.
//

#ifndef SR_ENGINE_GRAPHICS_RENDER_STAGES_SETTINGS_H
#define SR_ENGINE_GRAPHICS_RENDER_STAGES_SETTINGS_H

#include <Graphics/Pipeline/IShaderProgram.h>

#include <Utils/Resources/Asset.h>

namespace SR_GRAPH_NS {
    class RenderStagesSettings : public SR_UTILS_NS::Asset {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<RenderStagesSettings>;

    };
}

#endif //SR_ENGINE_GRAPHICS_RENDER_STAGES_SETTINGS_H
```


