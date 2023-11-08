//
// Created by innerviewer on 07/11/23.
//

#ifndef SRENGINE_X11SURFACEINIT_H
#define SRENGINE_X11SURFACEINIT_H

#include <EvoVulkan/macros.h>

#include <Utils/Types/SafePointer.h>

namespace SR_GRAPH_NS {
    class X11SurfaceInit {
    public:
        static VkSurfaceKHR Init(const SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::Window>& window, VkInstance instance);
        static const char* GetSurfaceExtensionName();
    };
}

#endif //SRENGINE_X11SURFACEINIT_H
