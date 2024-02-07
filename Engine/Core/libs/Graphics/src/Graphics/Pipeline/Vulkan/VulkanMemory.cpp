//
// Created by Nikita on 15.06.2021.
//

#include <Graphics/Pipeline/Vulkan/VulkanMemory.h>
#include <Graphics/Pipeline/PipelineType.h>

#include <EvoVulkan/Types/VmaBuffer.h>

int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateFBO(const VulkanFrameBufferAllocInfo& info) {
    if (info.inputColorAttachments.size() != info.pOutputColorAttachments->size()) {
        SR_WARN("MemoryManager::AllocateFBO() : input colors not equal output colors count! Something went wrong...");
    }

    info.pOutputColorAttachments->clear();

    for (uint32_t i = 0; i < m_countFBO.first; ++i) {
        VkImageAspectFlags vkImageAspect = VulkanTools::AbstractImageAspectToVkAspect(info.pDepth->aspect);
        VkFormat vkDepthFormat = m_device->GetDepthFormat();

        if (info.pDepth->format != ImageFormat::Auto) {
            vkDepthFormat = VulkanTools::AbstractTextureFormatToVkFormat(info.pDepth->format);
        }

        if (m_FBOs[i] == nullptr) {
            m_FBOs[i] = EvoVulkan::Complexes::FrameBuffer::Create(
                m_kernel->GetDevice(),
                m_kernel->GetAllocator(),
                m_kernel->GetDescriptorManager(),
                m_kernel->GetSwapchain(),
                m_kernel->GetCmdPool(),
                info.features,
                info.inputColorAttachments,
                info.width, info.height,
                info.layersCount,
                1.f /** scale */,
                info.sampleCount,
                vkImageAspect,
                vkDepthFormat
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
                    info.pOutputColorAttachments->push_back(id);
                }
            }

            if (info.pDepth->format != ImageFormat::None && info.pDepth->aspect != ImageAspect::None) {
                if (auto&& depthTexture = m_FBOs[i]->AllocateDepthTextureReference(-1)) {
                    int32_t id = FindFreeTextureIndex();
                    if (id < 0) {
                        SR_ERROR("MemoryManager::AllocateFBO() : failed to allocate index for FBO depth!");
                        return SR_ID_INVALID;
                    }
                    else {
                        m_textures[id] = depthTexture;
                        info.pDepth->texture = id;
                        ++m_countTextures.second;
                    }
                }
            }

            for (auto&& texture : m_FBOs[i]->AllocateDepthTextureReferences()) {
                int32_t id = FindFreeTextureIndex();
                if (id < 0) {
                    SR_ERROR("MemoryManager::AllocateFBO() : failed to allocate index for FBO depth attachment!");
                    return SR_ID_INVALID;
                }
                else {
                    m_textures[id] = texture;
                    ++m_countTextures.second;
                    info.pDepth->subLayers.emplace_back(id);
                }
            }

            ++m_countFBO.second;

            return (int32_t)i;
        }
    }

    SR_ERROR("MemoryManager::AllocateFBO() : buffer is overflow!");

    return SR_ID_INVALID;
}

bool SR_GRAPH_NS::VulkanTools::MemoryManager::ReAllocateFBO(const VulkanFrameBufferAllocInfo& info) {
    if (info.FBO >= m_countFBO.first || m_FBOs[info.FBO] == nullptr) {
        SR_ERROR("MemoryManager::ReAllocateFBO() : incorrect FBO index!");
        return false;
    }

    auto&& vkImageAspect = VulkanTools::AbstractImageAspectToVkAspect(info.pDepth->aspect);

    m_FBOs[info.FBO]->SetSampleCount(info.sampleCount);
    m_FBOs[info.FBO]->SetLayersCount(info.layersCount);
    m_FBOs[info.FBO]->SetDepthAspect(vkImageAspect);
    m_FBOs[info.FBO]->SetFeatures(info.features);

    if (!m_FBOs[info.FBO]->ReCreate(info.width, info.height)) {
        SR_ERROR("MemoryManager::ReAllocateFBO() : failed to re-create frame buffer object!");
        return false;
    }

    /// Texture attachments

    auto textures = m_FBOs[info.FBO]->AllocateColorTextureReferences();
    if (textures.size() != info.oldColorAttachments.size()) {
        SR_ERROR("MemoryManager::ReAllocateFBO() : incorrect old color attachments!");
        return false;
    }

    for (uint32_t i = 0; i < textures.size(); ++i) {
        if (info.oldColorAttachments[i] < 0 || info.oldColorAttachments[i] >= m_countTextures.first) {
            SR_ERROR("MemoryManager::ReAllocateFBO() : incorrect old color attachment at index " + std::to_string(i) + ", range problem!");
            return false;
        }

        if (m_textures[info.oldColorAttachments[i]] == nullptr) {
            SR_ERROR("MemoryManager::ReAllocateFBO() : incorrect old color attachment at index " + std::to_string(i) + ", texture not exists!");
            return false;
        }

        delete m_textures[info.oldColorAttachments[i]];
        m_textures[info.oldColorAttachments[i]] = textures[i];
    }

    /// Depth attachments

    auto depthTextures = m_FBOs[info.FBO]->AllocateDepthTextureReferences();
    if (depthTextures.size() != info.pDepth->subLayers.size()) {
        SR_ERROR("MemoryManager::ReAllocateFBO() : incorrect old depth attachments!");
        return false;
    }

    for (uint32_t i = 0; i < depthTextures.size(); ++i) {
        if (info.pDepth->subLayers[i] < 0 || info.pDepth->subLayers[i] >= m_countTextures.first) {
            SR_ERROR("MemoryManager::ReAllocateFBO() : incorrect old depth attachment at index " + std::to_string(i) + ", range problem!");
            return false;
        }

        if (m_textures[info.pDepth->subLayers[i]] == nullptr) {
            SR_ERROR("MemoryManager::ReAllocateFBO() : incorrect old depth attachment at index " + std::to_string(i) + ", texture not exists!");
            return false;
        }

        delete m_textures[info.pDepth->subLayers[i]];
        m_textures[info.pDepth->subLayers[i]] = depthTextures[i];
    }

    /// Depth attachment

    if (info.pDepth->texture != SR_ID_INVALID) {
        delete m_textures[info.pDepth->texture];
        m_textures[info.pDepth->texture] = m_FBOs[info.FBO]->AllocateDepthTextureReference(-1);
    }

    return true;
}

bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeDescriptorSet(uint32_t ID) {
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

bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeVBO(uint32_t ID) {
    SRVerifyFalse(--m_countVBO.second < 0);
    return FreeMemory(ID, m_countVBO.first, m_VBOs);
}
bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeUBO(uint32_t ID) {
    SRVerifyFalse(--m_countUBO.second < 0);
    return FreeMemory(ID, m_countUBO.first, m_UBOs);
}
bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeIBO(uint32_t ID) {
    SRVerifyFalse(--m_countIBO.second < 0);
    return FreeMemory(ID, m_countIBO.first, m_IBOs);
}
bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeFBO(uint32_t ID) {
    SRVerifyFalse(--m_countFBO.second < 0);
    return FreeMemory(ID, m_countFBO.first, m_FBOs);
}
bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeShaderProgram(uint32_t ID) {
    SRVerifyFalse(--m_countShaderPrograms.second < 0);
    return FreeMemory(ID, m_countShaderPrograms.first, m_ShaderPrograms);
}
bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeTexture(uint32_t ID) {
    SRVerifyFalse(--m_countTextures.second < 0);
    return FreeMemory(ID, m_countTextures.first, m_textures);
}

int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateUBO(uint32_t UBOSize) {
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

int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateDescriptorSet(uint32_t shaderProgram, const std::vector<uint64_t> &types) {
    if (shaderProgram >= m_countShaderPrograms.first) {
        SRHalt("MemoryManager::AllocateDescriptorSet() : shader list index out of range! (" + std::to_string(shaderProgram) + ")");
        return -1;
    }

    if (!m_ShaderPrograms[shaderProgram]) {
        SR_ERROR("MemoryManager::AllocateDescriptorSet() : shader program does not exists!");
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

int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateVBO(uint32_t buffSize, void *data) {
    VkBufferUsageFlags bufferUsageFlagBits = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

    if (m_kernel->GetDevice()->IsRayTracingSupported()) {
        bufferUsageFlagBits |= VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR;
    }

    for (uint32_t i = 0; i < m_countVBO.first; ++i) {
        if (m_VBOs[i] == nullptr) {
            m_VBOs[i] = EvoVulkan::Types::VmaBuffer::Create(
                    m_kernel->GetAllocator(),
                    bufferUsageFlagBits,
                    VMA_MEMORY_USAGE_CPU_TO_GPU,
                    buffSize, data
            );

            ++m_countVBO.second;

            return (int32_t)i;
        }
    }

    SR_ERROR("MemoryManager::AllocateVBO() : overflow vertex buffer objects buffer!");

    return SR_ID_INVALID;
}

int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateIBO(uint32_t buffSize, void *data)  {
    VkBufferUsageFlags bufferUsageFlagBits = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

    if (m_kernel->GetDevice()->IsRayTracingSupported()) {
        bufferUsageFlagBits |= VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR;
    }

    for (uint32_t i = 0; i < m_countIBO.first; ++i) {
        if (m_IBOs[i] == nullptr) {
            m_IBOs[i] = EvoVulkan::Types::VmaBuffer::Create(
                    m_kernel->GetAllocator(),
                    bufferUsageFlagBits,
                    VMA_MEMORY_USAGE_CPU_TO_GPU,
                    buffSize, data
            );

            ++m_countIBO.second;

            return (int32_t)i;
        }
    }

    SR_ERROR("MemoryManager::AllocateIBO() : overflow index buffer objects buffer!");

    return SR_ID_INVALID;
}

int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateShaderProgram(EvoVulkan::Types::RenderPass renderPass)  {
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

int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateTexture(
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

int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateTexture(
    uint8_t *pixels, uint32_t w, uint32_t h,
    VkFormat format,
    VkFilter filter,
    SR_GRAPH_NS::TextureCompression /*compression*/,
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

void SR_GRAPH_NS::VulkanTools::MemoryManager::Free() {
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

