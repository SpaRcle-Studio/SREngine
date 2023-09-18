//
// Created by Monika on 13.05.2023.
//

#ifndef SR_ENGINE_GRAPHICS_VULKAN_TRACY_H
#define SR_ENGINE_GRAPHICS_VULKAN_TRACY_H

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
