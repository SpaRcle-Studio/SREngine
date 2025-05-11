

# File FrameBufferFeatures.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pipeline**](dir_b95270d167403b29f5d572cffd5b214a.md) **>** [**FrameBufferFeatures.h**](FrameBufferFeatures_8h.md)

[Go to the documentation of this file](FrameBufferFeatures_8h.md)


```C++
//
// Created by Monika on 07.02.2024.
//

#ifndef SR_ENGINE_FRAME_BUFFER_FEATURES_H
#define SR_ENGINE_FRAME_BUFFER_FEATURES_H

#include <Graphics/macros.h>

#include <Utils/Debug.h>

namespace SR_GRAPH_NS {
    struct FrameBufferFeatures {
        bool depthLoad = false;
        bool colorLoad = false;
        bool depthTransferSrc = false;
        bool colorTransferSrc = false;
        bool depthTransferDst = false;
        bool colorTransferDst = false;
        bool depthShaderRead = false;
        bool colorShaderRead = true;
    };
}

#endif //SR_ENGINE_FRAME_BUFFER_FEATURES_H
```


