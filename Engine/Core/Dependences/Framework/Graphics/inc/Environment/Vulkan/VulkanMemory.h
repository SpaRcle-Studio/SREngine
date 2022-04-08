//
// Created by Nikita on 27.05.2021.
//

#ifndef GAMEENGINE_VULKANMEMORY_H
#define GAMEENGINE_VULKANMEMORY_H

#include <Utils/NonCopyable.h>

#include <EvoVulkan/Types/VulkanBuffer.h>
#include <EvoVulkan/Complexes/Framebuffer.h>
#include <EvoVulkan/VulkanKernel.h>
#include <EvoVulkan/Complexes/Shader.h>
#include <EvoVulkan/Types/Texture.h>
#include <EvoVulkan/DescriptorManager.h>
#include <Environment/TextureHelper.h>
#include <Environment/Vulkan/DynamicTextureDescriptorSet.h>

#define ZERO_VULKAN_MEMORY_MANAGER(type, count, array) { \
    array = (type*)malloc(sizeof(type) * count);         \
    for (uint32_t i = 0; i < count; ++i)                 \
        array[i] = nullptr;                              \
}                                                        \

namespace Framework::Graphics::VulkanTools {
    class MemoryManager : Helper::NonCopyable {
    public:
        MemoryManager(const MemoryManager&) = delete;
    private:
        MemoryManager() = default;
        ~MemoryManager() override = default;

    private:
        bool Initialize(EvoVulkan::Core::VulkanKernel* kernel) {
            if (m_isInit) {
                return false;
            }

            m_kernel = kernel;
            m_descriptorManager = m_kernel->GetDescriptorManager();
            m_allocator = m_kernel->GetAllocator();
            m_device = m_kernel->GetDevice();
            m_pool   = m_kernel->GetCmdPool();

            if (!m_descriptorManager || !m_device || !m_pool) {
                Helper::Debug::Error("MemoryManager::Initialize() : failed to get (descriptor manager/device/cmd pool)!");
                return false;
            }

            ZERO_VULKAN_MEMORY_MANAGER(EvoVulkan::Types::VmaBuffer*, m_countUBO, m_UBOs)
            ZERO_VULKAN_MEMORY_MANAGER(EvoVulkan::Types::VmaBuffer*, m_countVBO, m_VBOs)
            ZERO_VULKAN_MEMORY_MANAGER(EvoVulkan::Types::VmaBuffer*, m_countIBO, m_IBOs)
            ZERO_VULKAN_MEMORY_MANAGER(EvoVulkan::Complexes::FrameBuffer*, m_countFBO, m_FBOs)
            ZERO_VULKAN_MEMORY_MANAGER(EvoVulkan::Complexes::Shader*, m_countShaderPrograms, m_ShaderPrograms)
            ZERO_VULKAN_MEMORY_MANAGER(EvoVulkan::Core::DescriptorSet, m_countDescriptorSets, m_descriptorSets)
            ZERO_VULKAN_MEMORY_MANAGER(EvoVulkan::Types::Texture*, m_countTextures, m_textures)

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

        template<typename T> bool FreeMemory(uint32_t id, uint32_t maxCount, T** pool) const {
            if (id >= maxCount) {
                Helper::Debug::Error("MemoryManager::FreeMemory() : list index out of range!");
                return false;
            }

            if (auto* memory = pool[id]) {
                memory->Destroy();
                memory->Free();

                pool[id] = nullptr;

                return true;
            }
            else
                Helper::Debug::Error("MemoryManager::FreeMemory() : id is not exists! (" + std::to_string(id) + ")");

            return false;
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
                uint8_t mipLevels,
                bool cpuUsage);

        [[nodiscard]] int32_t AllocateTexture(
                std::array<uint8_t*, 6> pixels,
                uint32_t w,
                uint32_t h,
                VkFormat format,
                VkFilter filter,
                uint8_t mipLevels,
                bool cpuUsage);

    public:
        EvoVulkan::Core::DescriptorManager*       m_descriptorManager       = nullptr;
        EvoVulkan::Types::Device*                 m_device                  = nullptr;
        EvoVulkan::Memory::Allocator*             m_allocator               = nullptr;
        EvoVulkan::Types::CmdPool*                m_pool                    = nullptr;

        uint32_t                                  m_countUBO                = 10000;
        uint32_t                                  m_countVBO                = 1000;
        uint32_t                                  m_countIBO                = 1000;
        uint32_t                                  m_countFBO                = 15;
        uint32_t                                  m_countShaderPrograms     = 50;
        uint32_t                                  m_countDescriptorSets     = 10000;
        uint32_t                                  m_countTextures           = 1000;

        EvoVulkan::Types::VmaBuffer**             m_UBOs                    = nullptr;
        EvoVulkan::Types::VmaBuffer**             m_VBOs                    = nullptr;
        EvoVulkan::Types::VmaBuffer**             m_IBOs                    = nullptr;
        EvoVulkan::Complexes::FrameBuffer**       m_FBOs                    = nullptr;
        EvoVulkan::Complexes::Shader**            m_ShaderPrograms          = nullptr;
        EvoVulkan::Core::DescriptorSet*           m_descriptorSets          = nullptr;
        EvoVulkan::Types::Texture**               m_textures                = nullptr;

    private:
        bool                                      m_isInit                  = false;
        EvoVulkan::Core::VulkanKernel*            m_kernel                  = nullptr;

    };
}

#endif //GAMEENGINE_VULKANMEMORY_H
