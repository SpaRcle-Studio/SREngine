

# File VulkanTracy.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pipeline**](dir_b95270d167403b29f5d572cffd5b214a.md) **>** [**Vulkan**](dir_f68684f6785c69ede334c05a5da1778e.md) **>** [**VulkanTracy.h**](VulkanTracy_8h.md)

[Go to the documentation of this file](VulkanTracy_8h.md)


```C++
//
// Created by Monika on 13.05.2023.
//

#ifndef SR_ENGINE_GRAPHICS_VULKAN_TRACY_H
#define SR_ENGINE_GRAPHICS_VULKAN_TRACY_H

#include <Graphics/macros.h>

#if defined(SR_TRACY_ENABLE) && defined(SR_USE_VULKAN)
    #include <Utils/Profile/TracyContext.h>

    #include <EvoVulkan/VulkanKernel.h>
    #include <TracyVulkan.hpp>

    #define SR_TRACY_VK_CREATE(singleTimeCmd, pKernel, name)                                                            \
        auto&& pTracyVkCreateContext = SR_TRACY_GET_CONTEXT(SR_UTILS_NS::TracyType::Vulkan, (void*)nullptr);            \
        if (!pTracyVkCreateContext) {                                                                                   \
            pTracyVkCreateContext = (void*)TracyVkContext(                                                              \
                *pKernel->GetDevice(),                                                                                  \
                *pKernel->GetDevice(),                                                                                  \
                pKernel->GetDevice()->GetQueues()->GetGraphicsQueue(),                                                  \
                singleTimeCmd                                                                                           \
            );                                                                                                          \
            TracyVkContextName(((tracy::VkCtx*)pTracyVkCreateContext), name, (uint16_t)strlen(name));                   \
        }                                                                                                               \

    #define SR_TRACY_VK_FRAME_ZONE_N(cmd, name)                                                                         \
        auto&& pTracyVkFrameContext = SR_TRACY_GET_CONTEXT(SR_UTILS_NS::TracyType::Vulkan, (void*)nullptr);             \
        if (!pTracyVkFrameContext) {                                                                                    \
            SRHalt("Tracy isn't created! Application will be crash...");                                                \
        }                                                                                                               \
                                                                                                                        \
        ZoneScoped;                                                                                                     \
        TracyVkZone(((tracy::VkCtx*)pTracyVkFrameContext), (VkCommandBuffer)cmd, name)                                  \

    #define SR_TRACY_VK_COLLECT(cmd)                                                                                    \
        auto&& pTracyVkCollectContext = SR_TRACY_GET_CONTEXT(SR_UTILS_NS::TracyType::Vulkan, (void*)nullptr);           \
        if (pTracyVkCollectContext) {                                                                                   \
            TracyVkCollect(((tracy::VkCtx*)pTracyVkCollectContext), (VkCommandBuffer)cmd);                              \
        }                                                                                                               \

#else
    #define SR_TRACY_VK_CREATE(singleTimeCmd, pKernel, name)
    #define SR_TRACY_VK_FRAME_ZONE_N(cmd, name)
    #define SR_TRACY_VK_COLLECT(cmd)
#endif

#endif //SR_ENGINE_GRAPHICS_VULKAN_TRACY_H
```


