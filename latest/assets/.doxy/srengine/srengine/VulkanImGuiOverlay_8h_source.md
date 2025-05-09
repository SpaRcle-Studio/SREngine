

# File VulkanImGuiOverlay.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Overlay**](dir_32af8277f8900af675cc0c06167c7d00.md) **>** [**VulkanImGuiOverlay.h**](VulkanImGuiOverlay_8h.md)

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

        bool m_undockingActive = false;

    };
}

#endif //SR_ENGINE_GRAPHICS_VULKAN_IMGUI_OVERLAY_H
```


