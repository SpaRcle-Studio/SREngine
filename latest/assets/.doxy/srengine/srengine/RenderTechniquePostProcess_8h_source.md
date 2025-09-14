

# File RenderTechniquePostProcess.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Loaders**](dir_d0a1daf921f47a1ee4283e6d14a9506b.md) **>** [**RenderTechniquePostProcess.h**](RenderTechniquePostProcess_8h.md)

[Go to the documentation of this file](RenderTechniquePostProcess_8h.md)


```C++
//
// Created by Monika on 14.09.2025.
//

#ifndef SR_ENGINE_GRAPHICS_RENDER_TECHNIQUE_POST_PROCESS_H
#define SR_ENGINE_GRAPHICS_RENDER_TECHNIQUE_POST_PROCESS_H

#include <Graphics/macros.h>

namespace SR_GRAPH_NS {
    class IRenderTechnique;
    class RenderContext;
}

namespace SR_GTYPES_NS {
    enum class CameraType : uint8_t;
}

namespace SR_GRAPH_NS::Details {
    void PostProcessRenderTechnique(IRenderTechnique* pTechnique, RenderContext* pContext, SR_GTYPES_NS::CameraType cameraType);
}

#endif //SR_ENGINE_GRAPHICS_RENDER_TECHNIQUE_POST_PROCESS_H
```


