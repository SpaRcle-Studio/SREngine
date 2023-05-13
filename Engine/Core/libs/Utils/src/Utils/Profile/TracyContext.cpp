//
// Created by Monika on 13.05.2023.
//

#include <Utils/Profile/TracyContext.h>

#ifdef SR_TRACY_ENABLE

namespace SR_UTILS_NS {
    void TracyContextManager::Destroy(TracyTypeFlag type) {
        if (type == TracyType::All) {
            for (auto&& contextMap : m_contexts) {
                for (auto&& [pIdentifier, pContext] : contextMap) {
                   Destroy(pContext, type);
                }
                contextMap.clear();
            }
            return;
        }

        for (auto&& [pIdentifier, pContext] : m_contexts[type]) {
            Destroy(pContext, type);
        }
        m_contexts[type].clear();
    }

    void TracyContextManager::Destroy(TracyContextPtr pContext, TracyTypeFlag type) {
        if (!pContext) {
            return;
        }

        switch (type) {
            #ifdef SR_USE_VULKAN
            case TracyType::Vulkan:
                if (VulkanDestroy) {
                    VulkanDestroy(pContext);
                }
                return;
            #endif
            default:
                break;
        }


        SRHalt("Failed to free tracy context!");
    }
}

#endif