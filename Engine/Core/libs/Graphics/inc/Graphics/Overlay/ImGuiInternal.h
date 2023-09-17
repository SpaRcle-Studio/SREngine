//
// Created by Monika on 17.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_IMGUI_INTERNAL_H
#define SR_ENGINE_GRAPHICS_IMGUI_INTERNAL_H

#include <Utils/stdInclude.h>

namespace SR_GRAPH_NS {
    /// Reusable buffers used for rendering 1 current in-flight frame, for ImGui_ImplVulkan_RenderDrawData()
    /// [Please zero-clear before use!]
    struct ImGui_ImplVulkanH_FrameRenderBuffers
    {
        VkDeviceMemory      VertexBufferMemory;
        VkDeviceMemory      IndexBufferMemory;
        VkDeviceSize        VertexBufferSize;
        VkDeviceSize        IndexBufferSize;
        VkBuffer            VertexBuffer;
        VkBuffer            IndexBuffer;
    };

    /// Each viewport will hold 1 ImGui_ImplVulkanH_WindowRenderBuffers
    /// [Please zero-clear before use!]
    struct ImGui_ImplVulkanH_WindowRenderBuffers
    {
        uint32_t            Index;
        uint32_t            Count;
        ImGui_ImplVulkanH_FrameRenderBuffers*   FrameRenderBuffers;
    };

    /// Vulkan data
    struct ImGui_ImplVulkan_Data
    {
        ImGui_ImplVulkan_InitInfo   VulkanInitInfo;
        VkRenderPass                RenderPass;
        VkDeviceSize                BufferMemoryAlignment;
        VkPipelineCreateFlags       PipelineCreateFlags;
        VkDescriptorSetLayout       DescriptorSetLayout;
        VkPipelineLayout            PipelineLayout;
        VkPipeline                  Pipeline;
        uint32_t                    Subpass;
        VkShaderModule              ShaderModuleVert;
        VkShaderModule              ShaderModuleFrag;

        /// Font data
        VkSampler                   FontSampler;
        VkDeviceMemory              FontMemory;
        VkImage                     FontImage;
        VkImageView                 FontView;
        VkDescriptorSet             FontDescriptorSet;
        VkDeviceMemory              UploadBufferMemory;
        VkBuffer                    UploadBuffer;

        /// Render buffers for main window
        ImGui_ImplVulkanH_WindowRenderBuffers MainWindowRenderBuffers;

        ImGui_ImplVulkan_Data()
        {
            memset(this, 0, sizeof(*this));
            BufferMemoryAlignment = 256;
        }
    };
}

#endif //SR_ENGINE_GRAPHICS_IMGUI_INTERNAL_H
