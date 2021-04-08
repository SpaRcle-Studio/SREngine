//
// Created by Nikita on 29.03.2021.
//

#ifndef GAMEENGINE_VULKANSHADERPROGRAM_H
#define GAMEENGINE_VULKANSHADERPROGRAM_H

#include <vulkan/vulkan.h>
//#include <Environment/Basic/IShaderProgram.h>
#include <Environment/Vulkan/VulkanTypes.h>

namespace Framework::Graphics {
    class VulkanShader { //: public IShaderProgram
    public:
        ~VulkanShader() {
            this->m_graphicsPipeline = VK_NULL_HANDLE;
            this->m_pipelineLayout   = VK_NULL_HANDLE;

            this->m_vertShaderModule = VK_NULL_HANDLE;
            this->m_fragShaderModule = VK_NULL_HANDLE;

            this->m_shaderStages     = nullptr;
            this->m_countStages      = 0;
        }
    public:
        VkPipelineShaderStageCreateInfo* m_shaderStages        = nullptr;
        unsigned __int8                  m_countStages         = 0;

        VkShaderModule                   m_vertShaderModule    = VK_NULL_HANDLE;
        VkShaderModule                   m_fragShaderModule    = VK_NULL_HANDLE;

        VkPipeline                       m_graphicsPipeline    = VK_NULL_HANDLE;
        VkPipelineLayout                 m_pipelineLayout      = VK_NULL_HANDLE;

        //! For resizing window need swapchain VkExtent2D
        VulkanTools::Swapchain*          m_swapchain           = nullptr;

        [[nodiscard]] bool IsReady() const {
            return m_vertShaderModule != VK_NULL_HANDLE &&
                   m_fragShaderModule != VK_NULL_HANDLE &&
                   m_graphicsPipeline != VK_NULL_HANDLE;
        }
    };
}

#endif //GAMEENGINE_VULKANSHADERPROGRAM_H
