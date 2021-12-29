//
// Created by Nikita on 01.07.2021.
//

#ifndef GAMEENGINE_VULKANIMGUI_H
#define GAMEENGINE_VULKANIMGUI_H

#include <EvoVulkan/VulkanKernel.h>

#include <GUI.h>

#include <EvoVulkan/DescriptorManager.h>
#include <EvoVulkan/Types/RenderPass.h>

namespace Framework::Graphics::VulkanTypes {
    class VkImGUI {
    public:
        VkImGUI() = default;
        VkImGUI(const VkImGUI&) = delete;
    private:
        ~VkImGUI() = default;
    private:
        const std::vector<VkDescriptorPoolSize> m_poolSizes = {
                { VK_DESCRIPTOR_TYPE_SAMPLER,                1000 },
                { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
                { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,          1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,          1000 },
                { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,   1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,   1000 },
                { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         1000 },
                { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
                { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,       1000 }
        };
    private:
        VkCommandBufferBeginInfo             m_cmdBuffBI    = {};
        VkRenderPassBeginInfo                m_renderPassBI = {};
        std::vector<VkClearValue>            m_clearValues  = {};

        std::vector<VkFramebuffer>           m_frameBuffs   = {};
        std::vector<VkCommandPool>           m_cmdPools     = {};
        std::vector<VkCommandBuffer>         m_cmdBuffs     = {};

        EvoVulkan::Core::DescriptorPool*     m_pool         = nullptr;
        EvoVulkan::Types::RenderPass         m_renderPass   = {};

        EvoVulkan::Types::Device*            m_device       = nullptr;
        EvoVulkan::Types::Swapchain*         m_swapchain    = nullptr;

        EvoVulkan::Types::MultisampleTarget* m_multisample  = nullptr;
    public:
        bool ReSize(uint32_t width, uint32_t height);
        VkCommandBuffer Render(uint32_t frame);
    public:
        bool Init(EvoVulkan::Core::VulkanKernel* kernel);
        bool Destroy();
        void Free();
    };
}

#endif //GAMEENGINE_VULKANIMGUI_H
