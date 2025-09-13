

# File LightType.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Lighting**](dir_b94c38cb0a82e06a7dce50d9e5876b41.md) **>** [**LightType.h**](LightType_8h.md)

[Go to the documentation of this file](LightType_8h.md)


```C++
//
// Created by Monika on 13.09.2025.
//

#ifndef SR_ENGINE_RENDER_LIGHT_TYPE_H
#define SR_ENGINE_RENDER_LIGHT_TYPE_H

#include <Graphics/macros.h>

#include <Utils/Common/Enumerations.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(LightType, uint8_t,
        Directional, Point, Spot, Area, Probe
    )

    SR_ENUM_NS_CLASS_T(ShadowType, uint8_t,
        Soft, Hard
    )
}

#endif //SR_ENGINE_RENDER_LIGHT_TYPE_H
```


