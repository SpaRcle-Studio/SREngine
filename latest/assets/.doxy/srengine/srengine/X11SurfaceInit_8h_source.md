

# File X11SurfaceInit.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pipeline**](dir_b95270d167403b29f5d572cffd5b214a.md) **>** [**Vulkan**](dir_f68684f6785c69ede334c05a5da1778e.md) **>** [**X11SurfaceInit.h**](X11SurfaceInit_8h.md)

[Go to the documentation of this file](X11SurfaceInit_8h.md)


```C++
//
// Created by innerviewer on 07/11/23.
//

#ifndef SR_ENGINE_X11SURFACEINIT_H
#define SR_ENGINE_X11SURFACEINIT_H

#include <Graphics/macros.h>

#include <EvoVulkan/macros.h>

#include <Utils/Types/SafePointer.h>

namespace SR_GRAPH_NS {
    class X11SurfaceInit {
    public:
        static VkSurfaceKHR Init(const SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::Window>& window, VkInstance instance);
        static const char* GetSurfaceExtensionName();
    };
}

#endif //SR_ENGINE_X11SURFACEINIT_H
```


