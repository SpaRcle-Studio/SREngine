//
// Created by Monika on 07.07.2026.
//

#ifndef SR_ENGINE_IMMEDIATE_GUI_VULKAN_RENDERER_H
#define SR_ENGINE_IMMEDIATE_GUI_VULKAN_RENDERER_H

#include <ImmediateGUI/stdInclude.h>

#include <ImmediateGUI/Backend/PlatformBackend.h>

#ifdef SR_USE_VULKAN

#include <vulkan/vulkan.h>

namespace SR_GRAPH_GUI_NS::Immediate {
    struct SR_IMMEDIATE_GUI_DLL_API VulkanFrameInfo {
        VkImage image = VK_NULL_HANDLE;
        VkImageView imageView = VK_NULL_HANDLE;
        uint32_t width = 0;
        uint32_t height = 0;
    };

    struct SR_IMMEDIATE_GUI_DLL_API VulkanRendererCreateInfo {
        VkInstance instance = VK_NULL_HANDLE;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device = VK_NULL_HANDLE;
        VkQueue graphicsQueue = VK_NULL_HANDLE;
        uint32_t graphicsQueueFamily = 0;

        VkPipelineCache pipelineCache = VK_NULL_HANDLE;

        VkFormat swapchainColorFormat = VK_FORMAT_UNDEFINED;
        VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

        bool enableDynamicRendering = false;
        bool enableViewports = false;

        /// Needed for ImGui multi-viewport surface creation.
        /// For Win32: HWND (main viewport)
        void* mainViewportPlatformHandleRaw = nullptr;
    };

    using VulkanRendererHandle = void*;

    SR_IMMEDIATE_GUI_DLL_API extern VulkanRendererHandle VulkanCreateRenderer(const VulkanRendererCreateInfo& info, const VulkanFrameInfo* frames, uint32_t frameCount);
    SR_IMMEDIATE_GUI_DLL_API extern void VulkanDestroyRenderer(VulkanRendererHandle renderer);

    SR_IMMEDIATE_GUI_DLL_API extern bool VulkanRecreateRenderer(VulkanRendererHandle renderer, const VulkanFrameInfo* frames, uint32_t frameCount);

    /// Call once per ImGui frame before ImGui::NewFrame().
    SR_IMMEDIATE_GUI_DLL_API extern void VulkanNewFrame(VulkanRendererHandle renderer);

    /// Records the ImGui draw data into internal command buffer for given frame index.
    SR_IMMEDIATE_GUI_DLL_API extern VkCommandBuffer VulkanRecordFrame(VulkanRendererHandle renderer, uint32_t frameIndex, bool tracyEnabled);

    SR_IMMEDIATE_GUI_DLL_API extern VkSemaphore VulkanGetRenderSemaphore(VulkanRendererHandle renderer);
    SR_IMMEDIATE_GUI_DLL_API extern VkDescriptorSetLayout VulkanGetTextureDescriptorSetLayout(VulkanRendererHandle renderer);

    /// Registers a Vulkan image view as ImGui texture and returns VkDescriptorSet usable as ImTextureID.
    /// Internally uses imgui vulkan backend (ImGui_ImplVulkan_AddTexture/RemoveTexture).
    SR_IMMEDIATE_GUI_DLL_API extern VkDescriptorSet VulkanAddTexture(VulkanRendererHandle renderer, VkImageView imageView, VkImageLayout imageLayout);
    SR_IMMEDIATE_GUI_DLL_API extern void VulkanRemoveTexture(VulkanRendererHandle renderer, VkDescriptorSet descriptorSet);

    SR_IMMEDIATE_GUI_DLL_API extern void VulkanReloadFonts(VulkanRendererHandle renderer);
}

#endif // SR_USE_VULKAN

#endif // SR_ENGINE_IMMEDIATE_GUI_VULKAN_RENDERER_H
