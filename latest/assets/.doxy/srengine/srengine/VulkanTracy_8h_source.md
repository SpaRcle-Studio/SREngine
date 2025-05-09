

# File VulkanTracy.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pipeline**](dir_5b8a811d805f0a9bb3b25de386a42645.md) **>** [**Vulkan**](dir_8e9bc433d1305450ae178a7c83320a15.md) **>** [**VulkanTracy.h**](VulkanTracy_8h.md)

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


