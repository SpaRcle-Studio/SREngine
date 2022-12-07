//
// Created by Nikita on 15.06.2021.
//

#include <Graphics/Pipeline/Vulkan/VulkanMemory.h>
#include <Graphics/Pipeline/PipelineType.h>

#include <EvoVulkan/Types/VmaBuffer.h>

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateFBO(
        uint32_t w, uint32_t h,
        const std::vector<VkFormat> &inputColorAttachments,
        std::vector<int32_t> &outputColorAttachments,
        std::optional<int32_t> &depth,
        uint8_t sampleCount)
{
    if (inputColorAttachments.size() != outputColorAttachments.size()) {
        SR_WARN("MemoryManager::AllocateFBO() : input colors not equal output colors count! Something went wrong...");
    }

    outputColorAttachments.clear();

    for (uint32_t i = 0; i < m_countFBO.first; ++i) {
        if (m_FBOs[i] == nullptr) {
            m_FBOs[i] = EvoVulkan::Complexes::FrameBuffer::Create(
                    m_kernel->GetDevice(),
                    m_kernel->GetAllocator(),
                    m_kernel->GetDescriptorManager(),
                    m_kernel->GetSwapchain(),
                    m_kernel->GetCmdPool(),
                    inputColorAttachments,
                    w, h,
                    1.f /** scale */,
                    sampleCount,
                    depth.has_value() /** depth enabled */
            );

            if (m_FBOs[i] == nullptr) {
                SR_ERROR("MemoryManager::AllocateFBO() : failed to create Evo Vulkan frame buffer object!");
                return SR_ID_INVALID;
            }

            for (auto&& texture : m_FBOs[i]->AllocateColorTextureReferences()) {
                int32_t id = FindFreeTextureIndex();
                if (id < 0) {
                    SR_ERROR("MemoryManager::AllocateFBO() : failed to allocate index for FBO attachment!");
                    return SR_ID_INVALID;
                }
                else {
                    m_textures[id] = texture;
                    ++m_countTextures.second;
                    outputColorAttachments.push_back(id);
                }
            }

            if (auto&& depthTexture = m_FBOs[i]->AllocateDepthTextureReference()) {
                int32_t id = FindFreeTextureIndex();
                if (id < 0) {
                    SR_ERROR("MemoryManager::AllocateFBO() : failed to allocate index for FBO depth!");
                    return SR_ID_INVALID;
                }
                else {
                    m_textures[id] = depthTexture;
                    ++m_countTextures.second;
                    depth = id;
                }
            }

            ++m_countFBO.second;

            return (int32_t)i;
        }
    }

    return SR_ID_INVALID;
}

bool Framework::Graphics::VulkanTools::MemoryManager::ReAllocateFBO(
        uint32_t FBO, uint32_t w, uint32_t h,
        const std::vector<int32_t> &oldColorAttachments,
        std::optional<int32_t> depthBuffer,
        uint8_t sampleCount)
{
    if (FBO >= m_countFBO.first || m_FBOs[FBO] == nullptr) {
        SR_ERROR("MemoryManager::ReAllocateFBO() : incorrect FBO index!");
        return false;
    }

    m_FBOs[FBO]->SetSampleCount(sampleCount);

    if (!m_FBOs[FBO]->ReCreate(w, h)) {
        SR_ERROR("MemoryManager::ReAllocateFBO() : failed to re-create frame buffer object!");
        return false;
    }

    /// Texture attachments

    auto textures = m_FBOs[FBO]->AllocateColorTextureReferences();
    if (textures.size() != oldColorAttachments.size()) {
        SR_ERROR("MemoryManager::ReAllocateFBO() : incorrect old color attachments!");
        return false;
    }

    for (uint32_t i = 0; i < textures.size(); ++i) {
        if (oldColorAttachments[i] < 0 || oldColorAttachments[i] >= m_countTextures.first) {
            SR_ERROR("MemoryManager::ReAllocateFBO() : incorrect old color attachment at index " + std::to_string(i) + ", range problem!");
            return false;
        }

        if (m_textures[oldColorAttachments[i]] == nullptr) {
            SR_ERROR("MemoryManager::ReAllocateFBO() : incorrect old color attachment at index " + std::to_string(i) + ", texture not exists!");
            return false;
        }

        m_textures[oldColorAttachments[i]]->Destroy();
        m_textures[oldColorAttachments[i]]->Free();
        m_textures[oldColorAttachments[i]] = textures[i];
    }

    if (depthBuffer.has_value()) {
        m_textures[depthBuffer.value()]->Destroy();
        m_textures[depthBuffer.value()]->Free();
        m_textures[depthBuffer.value()] = m_FBOs[FBO]->AllocateDepthTextureReference();
    }

    return true;
}

bool Framework::Graphics::VulkanTools::MemoryManager::FreeDescriptorSet(uint32_t ID) {
    if (ID >= m_countDescriptorSets.first) {
        SR_ERROR("MemoryManager::FreeDescriptorSet() : list index out of range!");
        return false;
    }

    auto&& memory = m_descriptorSets[ID];
    if (memory.m_self == VK_NULL_HANDLE) {
        SR_ERROR("MemoryManager::FreeDescriptorSet() : descriptor set is not exists!");
        return false;
    }

    if (!m_descriptorManager->FreeDescriptorSet(&memory)){
        SR_ERROR("MemoryManager::FreeDescriptorSet() : failed free descriptor set!");
        return false;
    }

    m_descriptorSets[ID] = EvoVulkan::Types::DescriptorSet();

    --m_countDescriptorSets.second;

    return true;
}

bool Framework::Graphics::VulkanTools::MemoryManager::FreeVBO(uint32_t ID) {
    SRVerifyFalse(--m_countVBO.second < 0);
    return FreeMemory(ID, m_countVBO.first, m_VBOs);
}
bool Framework::Graphics::VulkanTools::MemoryManager::FreeUBO(uint32_t ID) {
    SRVerifyFalse(--m_countUBO.second < 0);
    return FreeMemory(ID, m_countUBO.first, m_UBOs);
}
bool Framework::Graphics::VulkanTools::MemoryManager::FreeIBO(uint32_t ID) {
    SRVerifyFalse(--m_countIBO.second < 0);
    return FreeMemory(ID, m_countIBO.first, m_IBOs);
}
bool Framework::Graphics::VulkanTools::MemoryManager::FreeFBO(uint32_t ID) {
    SRVerifyFalse(--m_countFBO.second < 0);
    return FreeMemory(ID, m_countFBO.first, m_FBOs);
}
bool Framework::Graphics::VulkanTools::MemoryManager::FreeShaderProgram(uint32_t ID) {
    SRVerifyFalse(--m_countShaderPrograms.second < 0);
    return FreeMemory(ID, m_countShaderPrograms.first, m_ShaderPrograms);
}
bool Framework::Graphics::VulkanTools::MemoryManager::FreeTexture(uint32_t ID) {
    SRVerifyFalse(--m_countTextures.second < 0);
    return FreeMemory(ID, m_countTextures.first, m_textures);
}

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateUBO(uint32_t UBOSize) {
    for (uint32_t i = 0; i < m_countUBO.first; ++i) {
        if (m_UBOs[i] == nullptr) {
            m_UBOs[i] = EvoVulkan::Types::VmaBuffer::Create(
                    m_kernel->GetAllocator(),
                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                    VMA_MEMORY_USAGE_CPU_TO_GPU,
                    UBOSize);

            ++m_countUBO.second;

            return (int32_t)i;
        }
    }

    SR_ERROR("MemoryManager::AllocateUBO() : overflow uniform buffer objects buffer!");

    return -1;
}

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateDescriptorSet(uint32_t shaderProgram, const std::set<VkDescriptorType> &types) {
    if (shaderProgram >= m_countShaderPrograms.first) {
        SRHalt("MemoryManager::AllocateDescriptorSet() : shader list index out of range! (" + std::to_string(shaderProgram) + ")");
        return -1;
    }

    for (uint32_t i = 0; i < m_countDescriptorSets.first; ++i) {
        if (m_descriptorSets[i].m_self == VK_NULL_HANDLE) {
            m_descriptorSets[i] = m_descriptorManager->AllocateDescriptorSet(
                    m_ShaderPrograms[shaderProgram]->GetDescriptorSetLayout(),
                    types
            );

            if (m_descriptorSets[i].m_self == VK_NULL_HANDLE) {
                SR_ERROR("MemoryManager::AllocateDescriptorSet() : failed allocate descriptor set! Something went wrong...");
                return SR_ID_INVALID;
            }

            ++m_countDescriptorSets.second;

            return (int32_t)i;
        }
    }

    SR_ERROR("MemoryManager::AllocateDescriptorSet() : overflow descriptor sets buffer!");

    return -1;
}

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateVBO(uint32_t buffSize, void *data) {
    for (uint32_t i = 0; i < m_countVBO.first; ++i) {
        if (m_VBOs[i] == nullptr) {
            m_VBOs[i] = EvoVulkan::Types::VmaBuffer::Create(
                    m_kernel->GetAllocator(),
                    VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                    VMA_MEMORY_USAGE_CPU_TO_GPU,
                    buffSize, data);

            ++m_countVBO.second;

            return (int32_t)i;
        }
    }

    SR_ERROR("MemoryManager::AllocateVBO() : overflow vertex buffer objects buffer!");

    return SR_ID_INVALID;
}

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateIBO(uint32_t buffSize, void *data)  {
    for (uint32_t i = 0; i < m_countIBO.first; ++i) {
        if (m_IBOs[i] == nullptr) {
            m_IBOs[i] = EvoVulkan::Types::VmaBuffer::Create(
                    m_kernel->GetAllocator(),
                    VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                    VMA_MEMORY_USAGE_CPU_TO_GPU,
                    buffSize, data);

            ++m_countIBO.second;

            return (int32_t)i;
        }
    }

    SR_ERROR("MemoryManager::AllocateIBO() : overflow index buffer objects buffer!");

    return SR_ID_INVALID;
}

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateShaderProgram(EvoVulkan::Types::RenderPass renderPass)  {
    for (uint32_t i = 0; i < m_countShaderPrograms.first; ++i) {
        if (m_ShaderPrograms[i] == nullptr) {
            m_ShaderPrograms[i] = new EvoVulkan::Complexes::Shader(
                    m_kernel->GetDevice(),
                    renderPass,
                    m_kernel->GetPipelineCache());

            ++m_countShaderPrograms.second;

            return (int32_t)i;
        }
    }

    SR_ERROR("MemoryManager::AllocateShaderProgram() : overflow shader programs buffer!");

    return -1;
}

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateTexture(
        std::array<uint8_t *, 6> pixels,
        uint32_t w,
        uint32_t h,
        VkFormat format,
        VkFilter /*filter*/,
        uint8_t mipLevels,
        bool cpuUsage)
{
    for (uint32_t i = 0; i < m_countTextures.first; ++i)
        if (m_textures[i] == nullptr) {
            m_textures[i] = EvoVulkan::Types::Texture::LoadCubeMap(m_device, m_allocator, m_pool, format, w, h, pixels, mipLevels, cpuUsage);

            if (!m_textures[i]) {
                SR_ERROR("MemoryManager::AllocateTexture() : failed to load Evo Vulkan texture!");
                return -1;
            }

            ++m_countTextures.second;

            return (int32_t)i;
        }

    SR_ERROR("MemoryManager::AllocateTexture() : overflow textures buffer!");

    return -1;
}

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateTexture(
    uint8_t *pixels, uint32_t w, uint32_t h,
    VkFormat format,
    VkFilter filter,
    Framework::Graphics::TextureCompression /*compression*/,
    uint8_t mipLevels,
    bool cpuUsage)
{
    for (uint32_t i = 0; i < m_countTextures.first; ++i) {
        if (m_textures[i] == nullptr) {
            if (mipLevels == 0)
                m_textures[i] = EvoVulkan::Types::Texture::LoadAutoMip(m_device, m_allocator, m_descriptorManager, m_pool, pixels, format, w, h, filter, cpuUsage);
            else if (mipLevels == 1)
                m_textures[i] = EvoVulkan::Types::Texture::LoadWithoutMip(m_device, m_allocator, m_descriptorManager, m_pool, pixels, format, w, h, filter, cpuUsage);
            else
                m_textures[i] = EvoVulkan::Types::Texture::Load(m_device, m_allocator, m_descriptorManager, m_pool, pixels, format, w, h, mipLevels, filter, cpuUsage);

            if (!m_textures[i]) {
                SR_ERROR("MemoryManager::AllocateTexture() : failed to load Evo Vulkan texture!");
                return -1;
            }

            ++m_countTextures.second;

            return (int32_t)i;
        }
    }

    SR_ERROR("MemoryManager::AllocateTexture() : overflow textures buffer!");

    return -1;
}

#define VULKAN_MEMORY_MANAGER_SAFE_FREE(memory) if (memory) { delete[] memory; memory = nullptr; }

void Framework::Graphics::VulkanTools::MemoryManager::Free() {
    SRAssert2(m_countShaderPrograms.second == 0, "Shaders are not empty!");
    SRAssert2(m_countDescriptorSets.second == 0, "Descriptor sets are not empty!");
    SRAssert2(m_countTextures.second == 0, "Textures are not empty!");
    SRAssert2(m_countFBO.second == 0, "FBOs are not empty!");
    SRAssert2(m_countVBO.second == 0, "VBOs are not empty!");
    SRAssert2(m_countIBO.second == 0, "IBOs are not empty!");
    SRAssert2(m_countUBO.second == 0, "UBOs are not empty!");

    VULKAN_MEMORY_MANAGER_SAFE_FREE(m_ShaderPrograms)
    VULKAN_MEMORY_MANAGER_SAFE_FREE(m_descriptorSets)
    VULKAN_MEMORY_MANAGER_SAFE_FREE(m_textures)
    VULKAN_MEMORY_MANAGER_SAFE_FREE(m_FBOs)
    VULKAN_MEMORY_MANAGER_SAFE_FREE(m_VBOs)
    VULKAN_MEMORY_MANAGER_SAFE_FREE(m_IBOs)
    VULKAN_MEMORY_MANAGER_SAFE_FREE(m_UBOs)

    delete this;
}

