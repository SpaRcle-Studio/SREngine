

# File OverlayType.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Overlay**](dir_4a8795eb8ad690bf07364b6c276aac2d.md) **>** [**OverlayType.h**](OverlayType_8h.md)

[Go to the documentation of this file](OverlayType_8h.md)


```C++
//
// Created by Monika on 15.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_OVERLAY_TYPE_H
#define SR_ENGINE_GRAPHICS_OVERLAY_TYPE_H

#include <Graphics/macros.h>

#include <Utils/Types/SharedPtr.h>
#include <Utils/Common/Enumerations.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(OverlayType, uint8_t,
        None, All,
        ImGui, Steam, EpicGames
    );
}

#endif //SR_ENGINE_GRAPHICS_OVERLAY_TYPE_H
```


