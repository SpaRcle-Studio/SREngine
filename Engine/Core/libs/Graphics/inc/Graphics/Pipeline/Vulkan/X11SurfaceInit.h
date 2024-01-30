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
        static VkSurfaceKHR Init(const SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::Window>& window, VkInstance instance);
        static const char* GetSurfaceExtensionName();
    };
}

#endif //SR_ENGINE_X11SURFACEINIT_H
