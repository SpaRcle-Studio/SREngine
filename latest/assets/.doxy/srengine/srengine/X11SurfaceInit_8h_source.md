

# File X11SurfaceInit.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pipeline**](dir_5b8a811d805f0a9bb3b25de386a42645.md) **>** [**Vulkan**](dir_8e9bc433d1305450ae178a7c83320a15.md) **>** [**X11SurfaceInit.h**](X11SurfaceInit_8h.md)

[Go to the documentation of this file](X11SurfaceInit_8h.md)


```C++
//
// Created by innerviewer on 07/11/23.
//

#ifndef SR_ENGINE_X11SURFACEINIT_H
#define SR_ENGINE_X11SURFACEINIT_H

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


