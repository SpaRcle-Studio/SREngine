//
// Created by Nikita on 27.05.2021.
//

#ifndef GAMEENGINE_VULKANMEMORY_H
#define GAMEENGINE_VULKANMEMORY_H

#include <EvoVulkan/Types/VulkanBuffer.h>
#include <EvoVulkan/VulkanKernel.h>

namespace Framework::Graphics::VulkanTools {
    class Memory {
    private:
        bool                           m_isInit = false;
        EvoVulkan::Core::VulkanKernel* m_kernel = nullptr;
    public:
        bool Initialize(EvoVulkan::Core::VulkanKernel* kernel) {
            if (m_isInit) {
                return false;
            }

            this->m_kernel = kernel;

            this->m_UBOs = (EvoVulkan::Types::Buffer**)malloc(sizeof(EvoVulkan::Types::Buffer) * m_countUBO);
            for (uint32_t i = 0; i < m_countUBO; i++)
                m_UBOs[i] = nullptr;

            this->m_VBOs = (EvoVulkan::Types::Buffer**)malloc(sizeof(EvoVulkan::Types::Buffer) * m_countVBO);
            for (uint32_t i = 0; i < m_countVBO; i++)
                m_VBOs[i] = nullptr;

            this->m_IBOs = (EvoVulkan::Types::Buffer**)malloc(sizeof(EvoVulkan::Types::Buffer) * m_countIBO);
            for (uint32_t i = 0; i < m_countIBO; i++)
                m_IBOs[i] = nullptr;

            m_isInit = true;
            return true;
        }

        int32_t AllocateUBO(uint32_t UBOSize) {
            for (uint32_t i = 0; i < m_countUBO; i++) {
                if (m_UBOs[i] == nullptr) {
                    m_UBOs[i] = EvoVulkan::Types::Buffer::Create(
                            m_kernel->GetDevice(),
                            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                            UBOSize);

                    return (int32_t)i;
                }
            }

            return -1;
        }

        int32_t AllocateVBO(uint32_t buffSize, void* data) {
            for (uint32_t i = 0; i < m_countVBO; i++) {
                if (m_VBOs[i] == nullptr) {
                    m_VBOs[i] = EvoVulkan::Types::Buffer::Create(
                            m_kernel->GetDevice(),
                            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                            buffSize, data);

                    return (int32_t)i;
                }
            }

            return -1;
        }

        int32_t AllocateIBO(uint32_t buffSize, void* data) {
            for (uint32_t i = 0; i < m_countIBO; i++) {
                if (m_IBOs[i] == nullptr) {
                    m_IBOs[i] = EvoVulkan::Types::Buffer::Create(
                            m_kernel->GetDevice(),
                            VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                            buffSize, data);

                    return (int32_t)i;
                }
            }

            return -1;
        }
    public:
        uint32_t                   m_countUBO = 10000;
        uint32_t                   m_countVBO = 1000;
        uint32_t                   m_countIBO = 1000;

        EvoVulkan::Types::Buffer** m_UBOs     = nullptr;
        EvoVulkan::Types::Buffer** m_IBOs     = nullptr;
        EvoVulkan::Types::Buffer** m_VBOs     = nullptr;
    };
}

#endif //GAMEENGINE_VULKANMEMORY_H
