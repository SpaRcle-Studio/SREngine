//
// Created by Monika on 15.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_VULKAN_IMGUI_OVERLAY_H
#define SR_ENGINE_GRAPHICS_VULKAN_IMGUI_OVERLAY_H

#include <Graphics/Overlay/ImGuiOverlay.h>

namespace SR_GRAPH_NS {
    class VulkanImGuiOverlay : public ImGuiOverlay {
        using Super = ImGuiOverlay;
    public:
        explicit VulkanImGuiOverlay(PipelinePtr pPipeline)
            : Super(std::move(pPipeline))
        { }

    public:
        SR_NODISCARD bool Init() override;
        SR_NODISCARD bool ReCreate() override;

        SR_NODISCARD virtual std::string GetName() const { return "Vulkan ImGUI"; }

        void Destroy() override;

        bool BeginDraw() override;
        void EndDraw() override;

    private:
        bool InitializeRenderer();
        void DeInitializeRenderer();
        void DestroyBuffers();

    private:
        static const std::vector<VkDescriptorPoolSize> POOL_SIZES;

    private:
        VkSemaphore m_semaphore = VK_NULL_HANDLE;

        VkCommandBufferBeginInfo m_cmdBuffBI = { };
        VkRenderPassBeginInfo m_renderPassBI = { };
        std::vector<VkClearValue> m_clearValues;

        std::vector<VkFramebuffer> m_frameBuffs;
        std::vector<VkCommandPool> m_cmdPools;
        std::vector<VkCommandBuffer> m_cmdBuffs;

        EvoVulkan::Types::RenderPass m_renderPass = { };

        EvoVulkan::Types::DescriptorPool* m_pool = nullptr;
        EvoVulkan::Types::Device* m_device = nullptr;
        EvoVulkan::Types::Swapchain* m_swapChain = nullptr;
        EvoVulkan::Types::MultisampleTarget* m_multiSample = nullptr;

    };
}

#endif //SR_ENGINE_GRAPHICS_VULKAN_IMGUI_OVERLAY_H
