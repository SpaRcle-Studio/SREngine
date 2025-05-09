

# File ImGuiInternal.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Overlay**](dir_32af8277f8900af675cc0c06167c7d00.md) **>** [**ImGuiInternal.h**](ImGuiInternal_8h.md)

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


