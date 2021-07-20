//
// Created by Nikita on 25.03.2021.
//

#ifndef GAMEENGINE_VULKAN_H
#define GAMEENGINE_VULKAN_H

//#include <easy/profiler.h>
#include <Environment/Environment.h>

#define GLFW_EXPOSE_NATIVE_WIN32

#include <glm/glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <Debug.h>

#define VK_PROTOTYPES

#ifdef WIN32
    #define VK_USE_PLATFORM_WIN32_KHR
    #include <Environment/Win32Window.h>
#endif

#include <ResourceManager/ResourceManager.h>
#include <FileSystem/FileSystem.h>

#include <Environment/Vulkan/VulkanMemory.h>

#include <Environment/Vulkan/AbstractCasts.h>
#include <EvoVulkan/VulkanKernel.h>
#include <EvoVulkan/Tools/VulkanInsert.h>
#include <EvoVulkan/Tools/VulkanInitializers.h>
#include <EvoVulkan/Tools/VulkanConverter.h>

#include <Environment/Vulkan/VulkanImGUI.h>

#include <imgui_impl_vulkan.h>

namespace Framework::Graphics {
    class SRVulkan : public EvoVulkan::Core::VulkanKernel {
    protected:
        void Render() override;
    public:
        bool OnResize() override;

        bool BuildCmdBuffers() override {
            return true;
        }

        bool OnComplete() override {
            return true;
        }

        bool Destroy() override {
            return EvoVulkan::Core::VulkanKernel::Destroy();
        }
    private:
        VkCommandBuffer m_submitCmdBuffs[2] = {0};
    };

    class Vulkan : public Environment {
    public:
        Vulkan(Vulkan &) = delete;
    public:
        Vulkan() = default;
        ~Vulkan() = default;
    private:
        VkDeviceSize                                    m_offsets[1]         = {0};

        VkViewport                                      m_viewport           = { };
        VkRect2D                                        m_scissor            = { };

        std::vector<VkClearValue>                       m_clearValues        = { };
        VkRenderPassBeginInfo                           m_renderPassBI       = { };

        std::vector<EvoVulkan::Complexes::FrameBuffer*> m_framebuffersQueue  = {};
        EvoVulkan::Complexes::FrameBuffer*              m_currentFramebuffer = nullptr;
        VkCommandBuffer                                 m_currentCmd         = VK_NULL_HANDLE;
        EvoVulkan::Complexes::Shader*                   m_currentShader      = nullptr;
        VkPipelineLayout                                m_currentLayout      = VK_NULL_HANDLE;

        VulkanTypes::VkImGUI*                           m_imgui              = nullptr;

        //! Descriptor sets in that moment, for render meshes
        VkDescriptorSet                                 m_currentDesrSets    = VK_NULL_HANDLE;

        VkCommandBufferBeginInfo                        m_cmdBufInfo         = { };

        VulkanTools::MemoryManager*                     m_memory             = nullptr;
        EvoVulkan::Core::VulkanKernel*                  m_kernel             = nullptr;
    private:
        const std::vector<const char*> m_validationLayers = {
                "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> m_instanceExtensions = {
                VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef WIN32
                VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif
#ifndef SR_RELEASE
                VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif
        };

        const std::vector<const char*> m_deviceExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

#ifdef SR_RELEASE
        const bool m_enableValidationLayers = false;
#else
        const bool m_enableValidationLayers = true;
#endif
    public:
        [[nodiscard]] SR_FORCE_INLINE std::string GetPipeLineName()   const noexcept override { return "Vulkan";         }
        [[nodiscard]] SR_FORCE_INLINE PipeLine    GetPipeLine()       const noexcept override { return PipeLine::Vulkan; }
        [[nodiscard]] SR_FORCE_INLINE uint8_t     GetCountBuildIter() const noexcept override { return m_kernel->GetCountBuildIterations(); }
    public:
        [[nodiscard]] VulkanTypes::VkImGUI* GetVkImGUI() const { return m_imgui; }
        [[nodiscard]] VulkanTools::MemoryManager* GetMemoryManager() const { return m_memory; }
    public:
        uint64_t GetVRAMUsage() override { return m_kernel->GetDevice() ? m_kernel->GetDevice()->GetAllocatedMemorySize() : 0; }

        bool PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) override;
        bool Init(int swapInterval) override;
        bool PostInit() override;

        bool InitGUI() override;
        bool StopGUI() override;
        void SetGUIEnabled(bool enabled) override { m_kernel->SetGUIEnabled(enabled); }
        bool BeginDrawGUI() override;
        void EndDrawGUI() override;

        [[nodiscard]] int32_t GetImGuiTextureDescriptorFromTexture(uint32_t textureID) const override;
        [[nodiscard]] InternalTexture GetTexture(uint32_t id) const override;
        [[nodiscard]] void* GetDescriptorSet(uint32_t id) const override;
        [[nodiscard]] void* GetDescriptorSetFromDTDSet(uint32_t id) const override;

        void SetBuildState(const bool& isBuild) override {
            if (isBuild)
                this->m_kernel->SetFramebuffersQueue(m_framebuffersQueue);
            Environment::SetBuildState(isBuild);
        }

        [[nodiscard]] SR_FORCE_INLINE bool IsGUISupport()       const noexcept override { return true; }
        [[nodiscard]] SR_FORCE_INLINE std::string GetVendor()   const noexcept override { return this->m_kernel->GetDevice()->GetName(); }
        [[nodiscard]] SR_FORCE_INLINE std::string GetRenderer() const noexcept override { return "Vulkan"; }
        [[nodiscard]] SR_FORCE_INLINE std::string GetVersion()  const noexcept override { return "VK_API_VERSION_1_2"; }
        [[nodiscard]] glm::vec2 GetWindowSize()                 const noexcept override { return { this->m_basicWindow->GetRealWidth(), this->m_basicWindow->GetRealHeight() }; }
        [[nodiscard]] SR_FORCE_INLINE bool IsWindowOpen()       const noexcept override { return m_basicWindow->IsWindowOpen(); }
        [[nodiscard]] SR_FORCE_INLINE bool IsWindowCollapsed()  const noexcept override { return m_basicWindow->IsCollapsed(); }

        bool MakeWindow(const char* winName, bool fullScreen, bool resizable) override;
        void SetWindowIcon(const char* path) override { this->m_basicWindow->SetIcon(path); }
        bool CloseWindow() override;
        bool SetContextCurrent() override { return true; }
        void SetViewport(int32_t width, int32_t height) override {
            if (m_currentFBOid == 0)
                this->m_viewport = this->m_kernel->GetViewport();
            else if (m_currentFramebuffer)
                m_viewport = m_currentFramebuffer->GetViewport();

            vkCmdSetViewport(m_currentCmd, 0, 1, &m_viewport);
        }
        void SetScissor(int32_t width, int32_t height) override {
            if (m_currentFBOid == 0)
                this->m_scissor = this->m_kernel->GetScissor();
            else if (m_currentFramebuffer)
                this->m_scissor = m_currentFramebuffer->GetScissor();

            vkCmdSetScissor(m_currentCmd, 0, 1, &m_scissor);
        }

        SR_FORCE_INLINE void BeginRender() override {
            vkBeginCommandBuffer(m_currentCmd, &m_cmdBufInfo);
            vkCmdBeginRenderPass(m_currentCmd, &m_renderPassBI, VK_SUBPASS_CONTENTS_INLINE);
        }
        SR_FORCE_INLINE void EndRender() override {
            vkCmdEndRenderPass(m_currentCmd);
            vkEndCommandBuffer(m_currentCmd);
        }

        SR_FORCE_INLINE void ClearFramebuffersQueue() override {
            m_framebuffersQueue.clear();
        }

        /** \Vulkan Clear next frame buffer usage */
        SR_FORCE_INLINE void ClearBuffers() noexcept override {
            if (m_currentFBOid < 0) {
                Helper::Debug::Error("Vulkan::ClearBuffers() : frame buffer isn't attached!");
                return;
            } else if (m_currentFBOid > 0) {
                this->m_renderPassBI.clearValueCount = m_memory->m_FBOs[m_currentFBOid - 1]->GetCountClearValues();
                this->m_renderPassBI.pClearValues    = m_memory->m_FBOs[m_currentFBOid - 1]->GetClearValues();
            } else {
                Helper::Debug::Error("Vulkan::ClearBuffers() : TODO!");
            }
        }

        SR_FORCE_INLINE void ClearBuffers(float r, float g, float b, float a, float depth, uint8_t colorCount) noexcept override {
            colorCount *= m_kernel->MultisamplingEnabled() ? 2 : 1;

            this->m_clearValues.resize(colorCount + 1);

            for (uint8_t i = 0; i < colorCount; i++)
                m_clearValues[i] = { .color = {{ r, g, b, a }} };

            m_clearValues[colorCount] = { .depthStencil = { depth, 0 } };

            this->m_renderPassBI.clearValueCount = colorCount + 1;
            this->m_renderPassBI.pClearValues    = m_clearValues.data();
        }

        SR_FORCE_INLINE void DrawFrame() override {
            this->m_kernel->NextFrame();
        }
        SR_FORCE_INLINE void PollEvents() const noexcept override { this->m_basicWindow->PollEvents(); }

        void SetWindowPosition(int x, int y) override;
        void SetWindowSize(unsigned int w, unsigned int h) override;

        bool CompileShader(
                const std::string& path,
                int32_t FBO,
                void** shaderData,
                const std::vector<uint64_t>& uniformSizes
                ) const noexcept override;
        bool LinkShader(
                SR_SHADER_PROGRAM* shaderProgram,
                void** shaderData,
                const std::vector<SR_VERTEX_DESCRIPTION>& vertexDescriptions,
                const std::vector<std::pair<Vertices::Attribute, size_t>>& vertexAttributes,
                SRShaderCreateInfo shaderCreateInfo) const noexcept override;

        SR_FORCE_INLINE void UseShader(SR_SHADER_PROGRAM shaderProgram) noexcept override {
            if (shaderProgram >= m_memory->m_countShaderPrograms) {
                Helper::Debug::Error("Vulkan::UseShader() : index out of range!");
                return;
            }

            this->m_currentShaderID = (int)shaderProgram;
            this->m_currentShader   = m_memory->m_ShaderPrograms[shaderProgram];
            if (!m_currentShader) {
                Helper::Debug::Error("Vulkan::UseShader() : shader is nullptr!");
                return;
            }
            this->m_currentLayout = m_currentShader->GetPipelineLayout();

            this->m_currentShader->Bind(this->m_currentCmd);
        }

        bool CreateFrameBuffer(glm::vec2 size, int32_t& rboDepth, int32_t& FBO, std::vector<int32_t>& colorBuffers) override;

        SR_FORCE_INLINE bool DeleteShader(SR_SHADER_PROGRAM shaderProgram) noexcept override {
            if (!m_memory->FreeShaderProgram(shaderProgram)) {
                Helper::Debug::Error("Vulkan::DeleteShader() : failed free shader program!");
                return false;
            } else
                return true;
        }
        SR_FORCE_INLINE void UnUseShader() override {
            this->m_currentShader   = nullptr;
            this->m_currentShaderID = -1;
            this->m_currentLayout   = VK_NULL_HANDLE;
        }
    public:
        SR_FORCE_INLINE void DrawIndices(const uint32_t& countIndices) const noexcept override {
            if (m_currentDesrSets != VK_NULL_HANDLE)
                vkCmdBindDescriptorSets(m_currentCmd, VK_PIPELINE_BIND_POINT_GRAPHICS, m_currentLayout, 0, 1, &m_currentDesrSets, 0, NULL);

            vkCmdDrawIndexed(m_currentCmd, countIndices, 1, 0, 0, 0);
        }
        SR_FORCE_INLINE void Draw(const uint32_t& countVerts) const noexcept override {
            if (m_currentDesrSets != VK_NULL_HANDLE)
                vkCmdBindDescriptorSets(m_currentCmd, VK_PIPELINE_BIND_POINT_GRAPHICS, m_currentLayout, 0, 1, &m_currentDesrSets, 0, NULL);

            vkCmdDraw(m_currentCmd, countVerts, 1, 0, 0);
        }

        [[nodiscard]] SR_FORCE_INLINE int32_t AllocateUBO(uint32_t uboSize) const noexcept override {
            auto id = this->m_memory->AllocateUBO(uboSize);
            if (id < 0) {
                Helper::Debug::Error("Vulkan::AllocateUBO() : failed to allocate uniform buffer object!");
                return -1;
            } else
                return id;
        }

        SR_FORCE_INLINE void UpdateUBO(const uint32_t& UBO, void* data, const uint64_t& uboSize) override {
            m_memory->m_UBOs[UBO]->CopyToDevice(data, uboSize);
        }

        SR_FORCE_INLINE void UpdateDescriptorSets(uint32_t descriptorSet, const std::vector<std::pair<DescriptorType, std::pair<uint32_t, uint32_t>>>& updateValues) override {
            std::vector<VkWriteDescriptorSet> writeDescriptorSets = {};
            for (const auto& value : updateValues) {
                switch (value.first) {
                    case DescriptorType::Uniform:
                        writeDescriptorSets.emplace_back(EvoVulkan::Tools::Initializers::WriteDescriptorSet(
                                this->m_memory->m_descriptorSets[descriptorSet].m_self,
                                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                                value.second.first,
                                &m_memory->m_UBOs[value.second.second]->m_descriptor));
                        break;
                    default:
                        Helper::Debug::Error("Vulkan::UpdateDescriptorSets() : unknown type!");
                        return;
                }
            }
            vkUpdateDescriptorSets(*m_kernel->GetDevice(), writeDescriptorSets.size(), writeDescriptorSets.data(), 0, NULL);
        }

        SR_FORCE_INLINE bool FreeDescriptorSet(const uint32_t& descriptorSet) override {
            Helper::Debug::Graph("Vulkan::FreeDescriptorSet() : free descriptor set...");

            if (!this->m_memory->FreeDescriptorSet(descriptorSet)) {
                Helper::Debug::Error("Vulkan::FreeDescriptorSet() : failed to free descriptor set!");
                return false;
            } else
                return true;
        }
        SR_FORCE_INLINE int32_t AllocDescriptorSet(const std::set<DescriptorType>& types) override {
            Helper::Debug::Graph("Vulkan::AllocDescriptorSet() : allocate new descriptor set...");

            auto vkTypes = VulkanTools::CastAbsDescriptorTypeToVk(types);
            if (vkTypes.size() != types.size()) {
                Helper::Debug::Error("Vulkan::AllocDescriptorSet() : failed to cast abstract descriptor types to vulkan descriptor types!");
                return -3;
            } else {
                auto id = this->m_memory->AllocateDescriptorSet(m_currentShaderID, vkTypes);
                if (id >= 0) {
                    return id;
                }
                else {
                    Helper::Debug::Error("Vulkan::AllocDescriptorSet() : failed to allocate descriptor set!");
                    return -1;
                }
            }
        }
        SR_FORCE_INLINE int32_t AllocDescriptorSetFromTexture(uint32_t textureID) override {
            if (!m_memory->m_textures[textureID]) {
                Helper::Debug::Error("Vulkan::AllocDescriptorSetFromTexture() : texture is not exists!");
                return -1;
            }

            if (m_currentShaderID < 0) {
                Helper::Debug::Error("Vulkan::AllocDescriptorSetFromTexture() : shader is not attached!");
                return -1;
            }

            const std::set<DescriptorType> types = { DescriptorType::CombinedImage };
            int32_t descriptorSetID = this->m_memory->AllocateDescriptorSet(m_currentShaderID, VulkanTools::CastAbsDescriptorTypeToVk(types));
            if (descriptorSetID < 0) {
                Helper::Debug::Error("Vulkan::AllocDescriptorSetFromTexture() : failed to allocate descriptor set!");
                return -1;
            }

            auto descriptorSet = EvoVulkan::Tools::Initializers::WriteDescriptorSet(
                    m_memory->m_descriptorSets[descriptorSetID].m_self,
                    VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 0,
                    m_memory->m_textures[textureID]->GetDescriptorRef());

            vkUpdateDescriptorSets(*this->m_kernel->GetDevice(), 1, &descriptorSet, 0, nullptr);

            return descriptorSetID;
        }

        SR_FORCE_INLINE void BindDescriptorSet(const uint32_t& descriptorSet) override { //const uint32_t& binding,
            //this->m_descriptorSets[binding] = m_memory->m_descriptorSets[descriptorSet].m_self;
            m_currentDescID = descriptorSet;
            this->m_currentDesrSets = m_memory->m_descriptorSets[descriptorSet].m_self;
        }
        int32_t CalculateTexture(
                uint8_t* data,
                TextureFormat format,
                uint32_t w, uint32_t h,
                TextureFilter filter,
                TextureCompression compression,
                uint8_t mipLevels,
                bool alpha) const noexcept override;

        SR_FORCE_INLINE bool CalculateVBO(int32_t& VBO, void* vertices, uint32_t vertSize, size_t count) const noexcept override {
            auto id = this->m_memory->AllocateVBO(vertSize * count, vertices);
            if (id >= 0) {
                VBO = id;
                return true;
            }
            else
                return false;
        }
        SR_FORCE_INLINE bool CalculateIBO(int32_t& IBO, void* indices, uint32_t indxSize, size_t count)  const noexcept override {
            auto id = this->m_memory->AllocateIBO(indxSize * count, indices);
            if (id >= 0) {
                IBO = id;
                return true;
            }
            else
                return false;
        }
        [[nodiscard]] int32_t CalculateCubeMap(uint32_t w, uint32_t h, const std::array<uint8_t*, 6>& data) override {
            if (auto id = m_memory->AllocateTexture(data, w, h, VK_FORMAT_R8G8B8A8_UNORM, VK_FILTER_LINEAR, 1); id < 0) {
                Helper::Debug::Error("Vulkan::CalculateCubeMap() : failed to allocate texture!");
                return -1;
            } else
                return id;
        }
        SR_FORCE_INLINE void BindFrameBuffer(const uint32_t& FBO) noexcept override {
            if (FBO == 0) {
                this->m_renderPassBI.framebuffer = m_kernel->m_frameBuffers[m_currentBuildIteration];
                this->m_renderPassBI.renderPass  = m_kernel->GetRenderPass();
                this->m_renderPassBI.renderArea  = m_kernel->GetRenderArea();
                this->m_currentCmd               = m_kernel->m_drawCmdBuffs[m_currentBuildIteration];

                this->m_currentFramebuffer = nullptr;
            } else {
                if (FBO == UINT32_MAX) {
                    Helper::Debug::Error(
                            "Vulkan::BindFrameBuffer() : frame buffer index equals UINT32_MAX! Something went wrong...");
                    return;
                }

                auto framebuffer = m_memory->m_FBOs[FBO - 1];
                if (!framebuffer) {
                    Helper::Debug::Error("Vulkan::BindFrameBuffer() : frame buffer object don't exist!");
                    return;
                }

                for (auto fbo : m_framebuffersQueue)
                    if (fbo == framebuffer) {
                        Helper::Debug::Error("Vulkan::BindFrameBuffer() : frame buffer (\"" + std::to_string(FBO) + "\") is already added to FBO queue!");
                        return;
                    }
                m_framebuffersQueue.push_back(framebuffer);

                this->m_renderPassBI.framebuffer = *framebuffer;
                this->m_renderPassBI.renderPass  = framebuffer->GetRenderPass();
                this->m_renderPassBI.renderArea  = framebuffer->GetRenderPassArea();
                this->m_currentCmd               = framebuffer->GetCmd();

                this->m_currentFramebuffer       = framebuffer;
            }

            this->m_currentFBOid = FBO;
        }

        SR_FORCE_INLINE void BindVBO(const unsigned int& VBO) const noexcept override {
            vkCmdBindVertexBuffers(m_currentCmd, 0, 1, &m_memory->m_VBOs[VBO]->m_buffer, m_offsets);
        }
        SR_FORCE_INLINE void BindIBO(const unsigned int& IBO) const noexcept override {
            // TODO: unsafe! VK_INDEX_TYPE_UINT32 can be different!
            vkCmdBindIndexBuffer(m_currentCmd, m_memory->m_IBOs[IBO]->m_buffer, 0, VK_INDEX_TYPE_UINT32);
        }
        SR_FORCE_INLINE void BindTexture(const uint8_t activeTexture, const uint32_t& ID) const noexcept override {
            if (ID >= m_memory->m_countTextures) {
                Helper::Debug::Error("Vulkan::BindTexture() : incorrect range! (" + std::to_string(ID) + ")");
                return;
            }

            EvoVulkan::Types::Texture* texture = m_memory->m_textures[ID];

            if (!texture) {
                Helper::Debug::Error("Vulkan::BindTexture() : texture is not exists!");
                return;
            }

            auto descriptorSet = EvoVulkan::Tools::Initializers::WriteDescriptorSet(
                    m_memory->m_descriptorSets[m_currentDescID].m_self,
                    VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, activeTexture,
                    texture->GetDescriptorRef());

            vkUpdateDescriptorSets(*this->m_kernel->GetDevice(), 1, &descriptorSet, 0, nullptr);
        }

        [[nodiscard]] SR_FORCE_INLINE bool FreeVBO(uint32_t ID) const noexcept override { return this->m_memory->FreeVBO(ID); }
        [[nodiscard]] SR_FORCE_INLINE bool FreeIBO(uint32_t ID) const noexcept override { return this->m_memory->FreeIBO(ID); }
        [[nodiscard]] SR_FORCE_INLINE bool FreeUBO(uint32_t ID) const noexcept override { return this->m_memory->FreeUBO(ID); }

        SR_FORCE_INLINE bool FreeCubeMap(int32_t ID) override {
            if (!m_memory->FreeTexture((uint32_t)ID)) {
                Helper::Debug::Error("Vulkan::FreeCubeMap() : failed to free texture! (" + std::to_string(ID) + ")");
                return false;
            } else
                return true;
        }

        [[nodiscard]] bool FreeTextures(int32_t* IDs, uint32_t count) const noexcept override;

        [[nodiscard]] bool FreeTexture(uint32_t ID) const noexcept override {
            if (!m_memory->FreeTexture((uint32_t)ID)) {
                Helper::Debug::Error("Vulkan::FreeTexture() : failed to free texture!");
                return false;
            }

            return true;
        }

        [[nodiscard]] bool FreeFBO(uint32_t FBO) const noexcept override;
    };
}

#endif //GAMEENGINE_VULKAN_H
