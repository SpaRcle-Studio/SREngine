

# File RenderSettings.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**RenderSettings.h**](RenderSettings_8h.md)

[Go to the documentation of this file](RenderSettings_8h.md)


```C++
//
// Created by Monika on 11.08.2023.
//

#ifndef SR_ENGINE_RENDERSETTINGS_H
#define SR_ENGINE_RENDERSETTINGS_H

#include <Graphics/macros.h>

#include <Graphics/Render/RenderSettings.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(Quality, uint8_t,
        None,
        Low,
        Medium,
        High,
        Ultra,
        Extreme
    );

    class RenderSettings : public SR_UTILS_NS::NonCopyable {
        Quality shadows = Quality::None;
        Quality ScreenSpaceAO = Quality::None;
        Quality particles = Quality::None;

    };
}

#endif //SR_ENGINE_RENDERSETTINGS_H
```


