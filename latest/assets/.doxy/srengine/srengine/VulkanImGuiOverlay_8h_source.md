

# File VulkanImGuiOverlay.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Overlay**](dir_4a8795eb8ad690bf07364b6c276aac2d.md) **>** [**VulkanImGuiOverlay.h**](VulkanImGuiOverlay_8h.md)

[Go to the documentation of this file](VulkanImGuiOverlay_8h.md)


```C++
//
// Created by Monika on 15.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_VULKAN_IMGUI_OVERLAY_H
#define SR_ENGINE_GRAPHICS_VULKAN_IMGUI_OVERLAY_H

#include <Graphics/macros.h>

#include <Graphics/Overlay/ImGuiOverlay.h>
#include <Graphics/Overlay/ImGuiInternal.h>

namespace SR_GRAPH_NS {
    class VulkanImGuiOverlay : public ImGuiOverlay {
        using Super = ImGuiOverlay;
    public:
        explicit VulkanImGuiOverlay(PipelinePtr pPipeline)
            : Super(std::move(pPipeline))
        { }

        ~VulkanImGuiOverlay() override {
            SRAssert2(m_frameBuffs.empty(), "Vulkan ImGUI Overlay frame buffers are not empty");
            SRAssert2(m_cmdPools.empty(), "Vulkan ImGUI Overlay command pools are not empty");
            SRAssert2(m_cmdBuffs.empty(), "Vulkan ImGUI Overlay command buffers are not empty");
        }

    public:
        SR_NODISCARD bool Init() override;
        SR_NODISCARD bool ReCreate() override;

        SR_NODISCARD std::string GetName() const override { return "Vulkan ImGUI"; }
        SR_NODISCARD bool IsDynamicRenderingEnabled() const override { return m_dynamicRendering; }

        SR_NODISCARD EvoVulkan::SubmitInfo& Render(uint32_t frame);
        SR_NODISCARD void* GetTextureDescriptorSet(uint32_t textureId) override;

        SR_NODISCARD VkSemaphore GetSemaphore() { return m_semaphore; }
        SR_NODISCARD EvoVulkan::SubmitInfo& GetSubmitInfo() { return m_submitInfo; }

        void ResetSubmitInfo();
        void ReloadFonts() override;

        void Destroy() override;

        bool BeginDraw() override;
        void EndDraw() override;

    private:
        bool InitializeRenderer();
        void DeInitializeRenderer();
        void DestroyBuffers();

        uint32_t GetCountImages() const;

    private:
        static const std::vector<VkDescriptorPoolSize> POOL_SIZES;

    private:
        EvoVulkan::SubmitInfo m_submitInfo = { };

        bool m_dynamicRendering = false;

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

        PFN_vkCmdBeginRendering m_pVkCmdBeginRendering = nullptr;
        PFN_vkCmdEndRendering m_pVkCmdEndRendering = nullptr;

        bool m_undockingActive = false;

    };
}

#endif //SR_ENGINE_GRAPHICS_VULKAN_IMGUI_OVERLAY_H
```


