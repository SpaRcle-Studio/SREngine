//
// Created by Nikita on 15.06.2021.
//

#include <Environment/Vulkan/VulkanMemory.h>

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateFBO(
        uint32_t w, uint32_t h,
        const std::vector<VkFormat> &inputColorAttachments,
        std::vector<int32_t> &outputColorAttachments,
        int32_t &depth)
{
    if (inputColorAttachments.size() != outputColorAttachments.size())
        Helper::Debug::Warn("MemoryManager::AllocateFBO() : input colors not equal output colors count! Something went wrong...");

    outputColorAttachments.clear();

    for (uint32_t i = 0; i < m_countFBO; i++)
        if (m_FBOs[i] == nullptr) {
            m_FBOs[i] = EvoVulkan::Complexes::FrameBuffer::Create(
                    m_kernel->GetDevice(),
                    m_kernel->GetSwapchain(),
                    m_kernel->GetCmdPool(),
                    inputColorAttachments,
                    w, h);

            if (m_FBOs[i] == nullptr) {
                Helper::Debug::Error("MemoryManager::AllocateFBO() : failed to create Evo Vulkan frame buffer object!");
                return -1;
            }

            for (auto texture : m_FBOs[i]->AllocateColorTextureReferences()) {
                int32_t id = this->FindFreeTextureIndex();
                if (id < 0) {
                    Helper::Debug::Error("MemoryManager::AllocateFBO() : failed to allocate index for FBO attachment!");
                    return -1;
                } else {
                    m_textures[id] = texture;
                    outputColorAttachments.push_back(id);
                }
            }

            //TODO: depth buffer!

            return (int32_t)i;
        }

    return -1;
}

bool Framework::Graphics::VulkanTools::MemoryManager::ReAllocateFBO(
        uint32_t FBO, uint32_t w, uint32_t h,
        const std::vector<int32_t> &oldColorAttachments,
        uint32_t depth)
{
    if (FBO >= m_countFBO || m_FBOs[FBO] == nullptr) {
        Helper::Debug::Error("MemoryManager::ReAllocateFBO() : incorrect FBO index!");
        return false;
    }

    if (!m_FBOs[FBO]->ReCreate(w, h)) {
        Helper::Debug::Error("MemoryManager::ReAllocateFBO() : failed to re-create frame buffer object!");
        return false;
    }

    // Texture-attachments

    auto textures = m_FBOs[FBO]->AllocateColorTextureReferences();
    if (textures.size() != oldColorAttachments.size()) {
        Helper::Debug::Error("MemoryManager::ReAllocateFBO() : incorrect old color attachments!");
        return false;
    }

    for (uint32_t i = 0; i < textures.size(); i++) {
        if (oldColorAttachments[i] < 0 || oldColorAttachments[i] >= m_countTextures) {
            Helper::Debug::Error("MemoryManager::ReAllocateFBO() : incorrect old color attachment at index " + std::to_string(i) + ", range problem!");
            return false;
        }

        if (m_textures[oldColorAttachments[i]] == nullptr) {
            Helper::Debug::Error("MemoryManager::ReAllocateFBO() : incorrect old color attachment at index " + std::to_string(i) + ", texture not exists!");
            return false;
        }

        m_textures[oldColorAttachments[i]]->Free();
        m_textures[oldColorAttachments[i]] = textures[i];
    }

    return true;
}

bool Framework::Graphics::VulkanTools::MemoryManager::FreeDescriptorSet(uint32_t ID) const  {
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

bool Framework::Graphics::VulkanTools::MemoryManager::FreeVBO(uint32_t ID) const  {
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

bool Framework::Graphics::VulkanTools::MemoryManager::FreeUBO(uint32_t ID) const  {
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

bool Framework::Graphics::VulkanTools::MemoryManager::FreeIBO(uint32_t ID) const  {
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

bool Framework::Graphics::VulkanTools::MemoryManager::FreeFBO(uint32_t ID) const {
    if (ID >= m_countFBO) {
        Helper::Debug::Error("MemoryManager::FreeFBO() : list index out of range! Index: " + std::to_string(ID));
        return false;
    }

    auto* memory = this->m_FBOs[ID];
    if (!memory) {
        Helper::Debug::Error("MemoryManager::FreeFBO() : frame buffer object is not exists! Index: " + std::to_string(ID));
        return false;
    }

    memory->Destroy();
    memory->Free();

    this->m_FBOs[ID] = nullptr;

    return true;
}

bool Framework::Graphics::VulkanTools::MemoryManager::FreeShaderProgram(uint32_t ID) const {
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

bool Framework::Graphics::VulkanTools::MemoryManager::FreeTexture(uint32_t ID) const  {
    if (ID >= m_countTextures) {
        Helper::Debug::Error("MemoryManager::FreeTexture() : list index out of range!");
        return false;
    }

    auto* memory = this->m_textures[ID];
    if (!memory) {
        Helper::Debug::Error("MemoryManager::FreeTexture() : texture is not exists!");
        return false;
    }

    memory->Destroy(); // if can't destroy (FBO attachment) will be skipped
    memory->Free();

    this->m_textures[ID] = nullptr;

    return true;
}

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateUBO(uint32_t UBOSize) const  {
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

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateDescriptorSet(
        uint32_t shaderProgram,
        const std::set<VkDescriptorType> &types
) const {
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

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateVBO(uint32_t buffSize, void *data) const  {
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

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateIBO(uint32_t buffSize, void *data)  {
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

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateShaderProgram(EvoVulkan::Types::RenderPass renderPass)  {
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

int32_t Framework::Graphics::VulkanTools::MemoryManager::AllocateTexture(
    uint8_t *pixels, uint32_t w, uint32_t h,
    VkFormat format,
    VkFilter filter,
    Framework::Graphics::TextureCompression compression, // unused
    uint8_t mipLevels)
{
    for (uint32_t i = 0; i < m_countTextures; i++) {
        if (m_textures[i] == nullptr) {
            if (mipLevels == 0)
                m_textures[i] = EvoVulkan::Types::Texture::LoadAutoMip(m_device, m_pool, pixels, format, w, h, filter);
            else if (mipLevels == 1)
                m_textures[i] = EvoVulkan::Types::Texture::LoadWithoutMip(m_device, m_pool, pixels, format, w, h, filter);
            else
                m_textures[i] = EvoVulkan::Types::Texture::Load(m_device, m_pool, pixels, format, w, h, mipLevels, filter);

            if (!m_textures[i]) {
                Helper::Debug::Error("MemoryManager::AllocateTexture() : failed to load Evo Vulkan texture!");
                return -1;
            }

            return (int32_t)i;
        }
    }

    Helper::Debug::Error("MemoryManager::AllocateTexture() : overflow textures buffer!");

    return -1;
}

