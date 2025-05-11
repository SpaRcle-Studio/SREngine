

# File ImGuiInternal.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Overlay**](dir_4a8795eb8ad690bf07364b6c276aac2d.md) **>** [**ImGuiInternal.h**](ImGuiInternal_8h.md)

[Go to the documentation of this file](ImGuiInternal_8h.md)


```C++
//
// Created by Monika on 17.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_IMGUI_INTERNAL_H
#define SR_ENGINE_GRAPHICS_IMGUI_INTERNAL_H

#include <Graphics/macros.h>

#include <Utils/stdInclude.h>

namespace SR_GRAPH_NS {
    struct ImGui_ImplVulkanH_FrameRenderBuffers
    {
        VkDeviceMemory      VertexBufferMemory;
        VkDeviceMemory      IndexBufferMemory;
        VkDeviceSize        VertexBufferSize;
        VkDeviceSize        IndexBufferSize;
        VkBuffer            VertexBuffer;
        VkBuffer            IndexBuffer;
    };

    struct ImGui_ImplVulkanH_WindowRenderBuffers
    {
        uint32_t            Index;
        uint32_t            Count;
        ImGui_ImplVulkanH_FrameRenderBuffers*   FrameRenderBuffers;
    };

    struct ImGui_ImplVulkan_Data
    {
        ImGui_ImplVulkan_InitInfo   VulkanInitInfo;
        VkDeviceSize                BufferMemoryAlignment;
        VkPipelineCreateFlags       PipelineCreateFlags;
        VkDescriptorSetLayout       DescriptorSetLayout;
        VkPipelineLayout            PipelineLayout;
        VkPipeline                  Pipeline;
        VkShaderModule              ShaderModuleVert;
        VkShaderModule              ShaderModuleFrag;

        // Font data
        VkSampler                   FontSampler;
        VkDeviceMemory              FontMemory;
        VkImage                     FontImage;
        VkImageView                 FontView;
        VkDescriptorSet             FontDescriptorSet;
        VkCommandPool               FontCommandPool;
        VkCommandBuffer             FontCommandBuffer;

        ImGui_ImplVulkanH_WindowRenderBuffers MainWindowRenderBuffers;

        ImGui_ImplVulkan_Data()
        {
            memset(this, 0, sizeof(*this));
            BufferMemoryAlignment = 256;
        }
    };
}

#endif //SR_ENGINE_GRAPHICS_IMGUI_INTERNAL_H
```


