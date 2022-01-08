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
#include <EvoVulkan/Types/Texture.h>
#include <EvoVulkan/DescriptorManager.h>
#include <Environment/TextureHelper.h>
#include <Environment/Vulkan/DynamicTextureDescriptorSet.h>

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
            this->m_device = m_kernel->GetDevice();
            this->m_pool   = m_kernel->GetCmdPool();

            if (!m_descriptorManager || !m_device || !m_pool) {
                Helper::Debug::Error("MemoryManager::Initialize() : failed to get (descriptor manager/device/cmd pool)!");
                return false;
            }

            this->m_UBOs = (EvoVulkan::Types::Buffer**)malloc(sizeof(EvoVulkan::Types::Buffer*) * m_countUBO);
            for (uint32_t i = 0; i < m_countUBO; i++)
                m_UBOs[i] = nullptr;

            this->m_VBOs = (EvoVulkan::Types::Buffer**)malloc(sizeof(EvoVulkan::Types::Buffer*) * m_countVBO);
            for (uint32_t i = 0; i < m_countVBO; i++)
                m_VBOs[i] = nullptr;

            this->m_IBOs = (EvoVulkan::Types::Buffer**)malloc(sizeof(EvoVulkan::Types::Buffer*) * m_countIBO);
            for (uint32_t i = 0; i < m_countIBO; i++)
                m_IBOs[i] = nullptr;

            this->m_FBOs = (EvoVulkan::Complexes::FrameBuffer**)malloc(sizeof(EvoVulkan::Complexes::FrameBuffer*) * m_countFBO);
            for (uint32_t i = 0; i < m_countFBO; i++)
                m_FBOs[i] = nullptr;

            this->m_ShaderPrograms = (EvoVulkan::Complexes::Shader**)malloc(sizeof(EvoVulkan::Complexes::Shader*) * m_countShaderPrograms);
            for (uint32_t i = 0; i < m_countShaderPrograms; i++)
                m_ShaderPrograms[i] = nullptr;

            this->m_descriptorSets = (EvoVulkan::Core::DescriptorSet*)malloc(sizeof(EvoVulkan::Core::DescriptorSet) * m_countDescriptorSets);
            for (uint32_t i = 0; i < m_countDescriptorSets; i++)
                m_descriptorSets[i] = EvoVulkan::Core::DescriptorSet();

            this->m_textures = (EvoVulkan::Types::Texture**)malloc(sizeof(EvoVulkan::Types::Texture*) * m_countTextures);
            for (uint32_t i = 0; i < m_countTextures; i++)
                m_textures[i] = nullptr;

            //this->m_dynamicTextureDescSets = (VulkanTypes::DynamicTextureDescriptorSet*)malloc(sizeof(VulkanTypes::DynamicTextureDescriptorSet) * m_countDynamicTexDescSets);
            //for (uint32_t i = 0; i < m_countDynamicTexDescSets; i++)
            //    m_dynamicTextureDescSets[i] = { -1, VK_NULL_HANDLE };

            m_isInit = true;
            return true;
        }
    private:
        [[nodiscard]] int32_t FindFreeTextureIndex() const {
            for (uint32_t i = 0; i < m_countTextures; i++)
                if (m_textures[i] == nullptr)
                    return (int32_t)i;
            return -1;
        }

        /*[[nodiscard]] int32_t FindFreeDynamicTextureDescriptorSetIndex() const {
            for (uint32_t i = 0; i < m_countDynamicTexDescSets; i++)
                if (m_dynamicTextureDescSets[i].m_descriptor == VK_NULL_HANDLE)
                    return (int32_t)i;
            return -1;
        }*/
    public:
        static MemoryManager* Create(EvoVulkan::Core::VulkanKernel* kernel) {
            auto memory = new MemoryManager();

            if (!memory->Initialize(kernel)) {
                Helper::Debug::Error("MemoryManager::Create() : failed to initialize memory!");
                return nullptr;
            }

            return memory;
        }
        void Free();
    public:
        [[nodiscard]] bool FreeDescriptorSet(uint32_t ID) const;

        [[nodiscard]] bool FreeShaderProgram(uint32_t ID) const;

        [[nodiscard]] bool FreeVBO(uint32_t ID) const;
        [[nodiscard]] bool FreeUBO(uint32_t ID) const;
        [[nodiscard]] bool FreeIBO(uint32_t ID) const;
        [[nodiscard]] bool FreeFBO(uint32_t ID) const;

        [[nodiscard]] bool FreeTexture(uint32_t ID) const;
    public:
        [[nodiscard]] int32_t AllocateDescriptorSet(uint32_t shaderProgram, const std::set<VkDescriptorType>& types) const;

        [[nodiscard]] int32_t AllocateShaderProgram(EvoVulkan::Types::RenderPass renderPass);

        [[nodiscard]] int32_t AllocateVBO(uint32_t buffSize, void* data) const;
        [[nodiscard]] int32_t AllocateUBO(uint32_t UBOSize) const;
        [[nodiscard]] int32_t AllocateIBO(uint32_t buffSize, void* data);

        [[nodiscard]] bool ReAllocateFBO(
                uint32_t FBO,
                uint32_t w, uint32_t h,
                const std::vector<int32_t>& oldColorAttachments,
                uint32_t depth);

        [[nodiscard]] int32_t AllocateFBO(
                uint32_t w, uint32_t h,
                const std::vector<VkFormat>& inputColorAttachments,
                std::vector<int32_t>& outputColorAttachments,
                int32_t& depth);

        [[nodiscard]] int32_t AllocateTexture(
                uint8_t* pixels,
                uint32_t w,
                uint32_t h,
                VkFormat format,
                VkFilter filter,
                TextureCompression compression,
                uint8_t mipLevels);

        [[nodiscard]] int32_t AllocateTexture(
                std::array<uint8_t*, 6> pixels,
                uint32_t w,
                uint32_t h,
                VkFormat format,
                VkFilter filter,
                uint8_t mipLevels);

        //[[nodiscard]] int32_t AllocateDynamicTextureDescriptorSet(VkDescriptorSetLayout layout, uint32_t textureID);
    //public:
        //[[nodiscard]] VkDescriptorSet GetDynamicTextureDescriptorSet(uint32_t id);
    public:
        EvoVulkan::Core::DescriptorManager*       m_descriptorManager       = nullptr;
        EvoVulkan::Types::Device*                 m_device                  = nullptr;
        EvoVulkan::Types::CmdPool*                m_pool                    = nullptr;

        uint32_t                                  m_countUBO                = 10000;
        uint32_t                                  m_countVBO                = 1000;
        uint32_t                                  m_countIBO                = 1000;
        uint32_t                                  m_countFBO                = 15;
        uint32_t                                  m_countShaderPrograms     = 50;
        uint32_t                                  m_countDescriptorSets     = 10000;
        uint32_t                                  m_countTextures           = 1000;
        uint32_t                                  m_countDynamicTexDescSets = 100;

        EvoVulkan::Types::Buffer**                m_UBOs                    = nullptr;
        EvoVulkan::Types::Buffer**                m_VBOs                    = nullptr;
        EvoVulkan::Types::Buffer**                m_IBOs                    = nullptr;
        EvoVulkan::Complexes::FrameBuffer**       m_FBOs                    = nullptr;
        EvoVulkan::Complexes::Shader**            m_ShaderPrograms          = nullptr;
        EvoVulkan::Core::DescriptorSet*           m_descriptorSets          = nullptr;
        EvoVulkan::Types::Texture**               m_textures                = nullptr;
        //VulkanTypes::DynamicTextureDescriptorSet* m_dynamicTextureDescSets  = nullptr;
    };
}

#endif //GAMEENGINE_VULKANMEMORY_H
