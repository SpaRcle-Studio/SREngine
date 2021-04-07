//
// Created by Nikita on 29.03.2021.
//

#ifndef GAMEENGINE_VULKANSHADERPROGRAM_H
#define GAMEENGINE_VULKANSHADERPROGRAM_H

#include <vulkan/vulkan.h>
#include <Environment/Basic/IShaderProgram.h>

namespace Framework::Graphics {
    class VulkanShader : public IShaderProgram {
    public:
        VkShaderModule m_vertShaderModule = VK_NULL_HANDLE;
        VkShaderModule m_fragShaderModule = VK_NULL_HANDLE;

        VkPipelineShaderStageCreateInfo* m_shaderStages        = nullptr;
        unsigned __int8                  m_countStages         = 0;

        VkPipeline                       m_graphicsPipeline    = VK_NULL_HANDLE;
        VkPipelineLayout                 m_pipelineLayout      = VK_NULL_HANDLE;

        [[nodiscard]] bool IsReady() const {
            return m_vertShaderModule != VK_NULL_HANDLE &&
                   m_fragShaderModule != VK_NULL_HANDLE &&
                   m_graphicsPipeline != VK_NULL_HANDLE;
        }
    };
}

#endif //GAMEENGINE_VULKANSHADERPROGRAM_H
