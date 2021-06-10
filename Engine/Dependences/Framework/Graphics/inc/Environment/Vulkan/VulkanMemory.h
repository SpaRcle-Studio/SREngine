//
// Created by Nikita on 27.05.2021.
//

#ifndef GAMEENGINE_VULKANMEMORY_H
#define GAMEENGINE_VULKANMEMORY_H

#include <EvoVulkan/Types/VulkanBuffer.h>
#include <EvoVulkan/Complexes/Framebuffer.h>
#include <EvoVulkan/VulkanKernel.h>
#include <Debug.h>
#include <EvoVulkan/Complexes/Shader.h>
#include <EvoVulkan/DescriptorManager.h>

namespace Framework::Graphics::VulkanTools {
    class MemoryManager {
    public:
        MemoryManager(const MemoryManager&) = delete;
    private:
        MemoryManager()  = default;
        ~MemoryManager() = default;
    private:
        bool                           m_isInit = false;
        EvoVulkan::Core::VulkanKernel* m_kernel = nullptr;
    private:
        bool Initialize(EvoVulkan::Core::VulkanKernel* kernel) {
            if (m_isInit) {
                return false;
            }

            this->m_kernel = kernel;
            this->m_descriptorManager = m_kernel->GetDescriptorManager();
            if (!m_descriptorManager) {
                Helper::Debug::Error("MemoryManager::Initialize() : failed to get descriptor manager!");
                return false;
            }

            this->m_UBOs = (EvoVulkan::Types::Buffer**)malloc(sizeof(EvoVulkan::Types::Buffer) * m_countUBO);
            for (uint32_t i = 0; i < m_countUBO; i++)
                m_UBOs[i] = nullptr;

            this->m_VBOs = (EvoVulkan::Types::Buffer**)malloc(sizeof(EvoVulkan::Types::Buffer) * m_countVBO);
            for (uint32_t i = 0; i < m_countVBO; i++)
                m_VBOs[i] = nullptr;

            this->m_IBOs = (EvoVulkan::Types::Buffer**)malloc(sizeof(EvoVulkan::Types::Buffer) * m_countIBO);
            for (uint32_t i = 0; i < m_countIBO; i++)
                m_IBOs[i] = nullptr;

            this->m_FBOs = (EvoVulkan::Complexes::FrameBuffer**)malloc(sizeof(EvoVulkan::Complexes::FrameBuffer) * m_countFBO);
            for (uint32_t i = 0; i < m_countFBO; i++)
                m_FBOs[i] = nullptr;

            this->m_ShaderPrograms = (EvoVulkan::Complexes::Shader**)malloc(sizeof(EvoVulkan::Complexes::Shader) * m_countShaderPrograms);
            for (uint32_t i = 0; i < m_countShaderPrograms; i++)
                m_ShaderPrograms[i] = nullptr;

            this->m_descriptorSets = (EvoVulkan::Core::DescriptorSet*)malloc(sizeof(EvoVulkan::Core::DescriptorSet) * m_countDescriptorSets);
            for (uint32_t i = 0; i < m_countDescriptorSets; i++)
                m_descriptorSets[i] = { VK_NULL_HANDLE, VK_NULL_HANDLE };

            m_isInit = true;
            return true;
        }
    public:
        static MemoryManager* Create(EvoVulkan::Core::VulkanKernel* kernel) {
            auto memory = new MemoryManager();

            if (!memory->Initialize(kernel)) {
                Helper::Debug::Error("MemoryManager::Create() : failed to initialize memory!");
                return nullptr;
            }

            return memory;
        }
    public:
        [[nodiscard]] bool FreeDescriptorSet(uint32_t ID) const {
            if (ID >= m_countDescriptorSets) {
                Helper::Debug::Error("MemoryManager::FreeDescriptorSet() : list index out of range!");
                return false;
            }

            auto memory = this->m_descriptorSets[ID];
            if (memory.m_self == VK_NULL_HANDLE) {
                Helper::Debug::Error("MemoryManager::FreeDescriptorSet() : descriptor set is not exists!");
                return false;
            }

            if (!m_descriptorManager->FreeDescriptorSet(memory)){
                Helper::Debug::Error("MemoryManager::FreeDescriptorSet() : failed free descriptor set!");
                return false;
            }

            this->m_descriptorSets[ID] = { VK_NULL_HANDLE, VK_NULL_HANDLE };

            return true;
        }

        [[nodiscard]] bool FreeVBO(uint32_t ID) const {
            if (ID >= m_countVBO) {
                Helper::Debug::Error("MemoryManager::FreeVBO() : list index out of range!");
                return false;
            }

            auto* memory = this->m_VBOs[ID];
            if (!memory) {
                Helper::Debug::Error("MemoryManager::FreeVBO() : VBO is not exists!");
                return false;
            }

            memory->Destroy();
            memory->Free();

            this->m_VBOs[ID] = nullptr;

            return true;
        }
        [[nodiscard]] bool FreeUBO(uint32_t ID) const {
            if (ID >= m_countUBO) {
                Helper::Debug::Error("MemoryManager::FreeUBO() : list index out of range!");
                return false;
            }

            auto* memory = this->m_UBOs[ID];
            if (!memory) {
                Helper::Debug::Error("MemoryManager::FreeUBO() : uniform buffer object is not exists!");
                return false;
            }

            memory->Destroy();
            memory->Free();

            this->m_UBOs[ID] = nullptr;

            return true;
        }
        [[nodiscard]] bool FreeIBO(uint32_t ID) const {
            if (ID >= m_countIBO) {
                Helper::Debug::Error("MemoryManager::FreeIBO() : list index out of range!");
                return false;
            }

            auto* memory = this->m_IBOs[ID];
            if (!memory) {
                Helper::Debug::Error("MemoryManager::FreeIBO() : IBO is not exists!");
                return false;
            }

            memory->Destroy();
            memory->Free();

            this->m_IBOs[ID] = nullptr;

            return true;
        }

        [[nodiscard]] bool FreeShaderProgram(uint32_t ID) const {
            if (ID >= m_countShaderPrograms) {
                Helper::Debug::Error("MemoryManager::FreeShaderProgram() : list index out of range!");
                return false;
            }

            auto* memory = this->m_ShaderPrograms[ID];
            if (!memory) {
                Helper::Debug::Error("MemoryManager::FreeShaderProgram() : shader program is not exists!");
                return false;
            }

            memory->Destroy();
            memory->Free();

            this->m_ShaderPrograms[ID] = nullptr;

            return true;
        }
    public:
        [[nodiscard]] int32_t AllocateUBO(uint32_t UBOSize) const {
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

            Helper::Debug::Error("MemoryManager::AllocateUBO() : overflow uniform buffer objects buffer!");

            return -1;
        }

        [[nodiscard]] int32_t AllocateDescriptorSet(uint32_t shaderProgram, const std::set<VkDescriptorType>& types) const {
            if (shaderProgram >= m_countShaderPrograms) {
                Helper::Debug::Error("MemoryManager::AllocateDescriptorSet() : shader list index out of range! (" + std::to_string(shaderProgram) + ")");
                return -1;
            }

            for (uint32_t i = 0; i < m_countDescriptorSets; i++) {
                if (m_descriptorSets[i].m_self == VK_NULL_HANDLE) {
                    m_descriptorSets[i] = m_descriptorManager->AllocateDescriptorSets(
                            m_ShaderPrograms[shaderProgram]->GetDescriptorSetLayout(),
                            types);
                    if (m_descriptorSets->m_self == VK_NULL_HANDLE) {
                        Helper::Debug::Error("MemoryManager::AllocateDescriptorSet() : failed allocate descriptor set! Something went wrong...");
                        return -1;
                    }

                    return (int32_t)i;
                }
            }

            Helper::Debug::Error("MemoryManager::AllocateDescriptorSet() : overflow descriptor sets buffer!");

            return -1;
        }

        [[nodiscard]] int32_t AllocateVBO(uint32_t buffSize, void* data) const {
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

            Helper::Debug::Error("MemoryManager::AllocateVBO() : overflow vertex buffer objects buffer!");

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

            Helper::Debug::Error("MemoryManager::AllocateIBO() : overflow index buffer objects buffer!");

            return -1;
        }

        int32_t AllocateShaderProgram(EvoVulkan::Types::RenderPass renderPass) {
            for (uint32_t i = 0; i < m_countShaderPrograms; i++) {
                if (m_ShaderPrograms[i] == nullptr) {
                    m_ShaderPrograms[i] = new EvoVulkan::Complexes::Shader(
                            m_kernel->GetDevice(),
                            renderPass,
                            m_kernel->GetPipelineCache());

                    return (int32_t)i;
                }
            }

            Helper::Debug::Error("MemoryManager::AllocateShaderProgram() : overflow shader programs buffer!");

            return -1;
        }
    public:
        EvoVulkan::Core::DescriptorManager* m_descriptorManager   = nullptr;

        uint32_t                            m_countUBO            = 10000;
        uint32_t                            m_countVBO            = 1000;
        uint32_t                            m_countIBO            = 1000;
        uint32_t                            m_countFBO            = 15;
        uint32_t                            m_countShaderPrograms = 50;
        uint32_t                            m_countDescriptorSets = 10000;

        EvoVulkan::Types::Buffer**          m_UBOs                = nullptr;
        EvoVulkan::Types::Buffer**          m_VBOs                = nullptr;
        EvoVulkan::Types::Buffer**          m_IBOs                = nullptr;
        EvoVulkan::Complexes::FrameBuffer** m_FBOs                = nullptr;
        EvoVulkan::Complexes::Shader**      m_ShaderPrograms      = nullptr;
        EvoVulkan::Core::DescriptorSet*     m_descriptorSets      = nullptr;
    };
}

#endif //GAMEENGINE_VULKANMEMORY_H
