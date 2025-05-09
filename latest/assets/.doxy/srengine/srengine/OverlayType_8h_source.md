

# File OverlayType.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Overlay**](dir_32af8277f8900af675cc0c06167c7d00.md) **>** [**OverlayType.h**](OverlayType_8h.md)

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


