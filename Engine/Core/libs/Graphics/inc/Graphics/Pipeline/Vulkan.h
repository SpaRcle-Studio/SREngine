//
// Created by Nikita on 25.03.2021.
//

#ifndef GAMEENGINE_VULKAN_H
#define GAMEENGINE_VULKAN_H

#include <Utils/Debug.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Events/EventManager.h>
#include <Utils/Platform/Platform.h>

#include <Graphics/Pipeline/Environment.h>
#include <Graphics/Pipeline/Vulkan/VulkanMemory.h>
#include <Graphics/Pipeline/Vulkan/AbstractCasts.h>
#include <Graphics/Pipeline/Vulkan/VulkanImGUI.h>
#include <Graphics/Pipeline/Vulkan/VulkanTracy.h>
#include <Graphics/Window/Window.h>
#include <Graphics/Pipeline/FrameBufferQueue.h>

#include <EvoVulkan/VulkanKernel.h>
#include <EvoVulkan/Tools/VulkanInsert.h>
#include <EvoVulkan/Tools/FileSystem.h>
#include <EvoVulkan/Tools/VulkanInitializers.h>
#include <EvoVulkan/Tools/VulkanConverter.h>
#include <EvoVulkan/Types/VmaBuffer.h>
#include <EvoVulkan/Complexes/FrameBufferLayer.h>

namespace SR_GRAPH_NS {
    // Reusable buffers used for rendering 1 current in-flight frame, for ImGui_ImplVulkan_RenderDrawData()
    // [Please zero-clear before use!]
    struct ImGui_ImplVulkanH_FrameRenderBuffers
    {
        VkDeviceMemory      VertexBufferMemory;
        VkDeviceMemory      IndexBufferMemory;
        VkDeviceSize        VertexBufferSize;
        VkDeviceSize        IndexBufferSize;
        VkBuffer            VertexBuffer;
        VkBuffer            IndexBuffer;
    };

    // Each viewport will hold 1 ImGui_ImplVulkanH_WindowRenderBuffers
    // [Please zero-clear before use!]
    struct ImGui_ImplVulkanH_WindowRenderBuffers
    {
        uint32_t            Index;
        uint32_t            Count;
        ImGui_ImplVulkanH_FrameRenderBuffers*   FrameRenderBuffers;
    };

    // Vulkan data
    struct ImGui_ImplVulkan_Data
    {
        ImGui_ImplVulkan_InitInfo   VulkanInitInfo;
        VkRenderPass                RenderPass;
        VkDeviceSize                BufferMemoryAlignment;
        VkPipelineCreateFlags       PipelineCreateFlags;
        VkDescriptorSetLayout       DescriptorSetLayout;
        VkPipelineLayout            PipelineLayout;
        VkPipeline                  Pipeline;
        uint32_t                    Subpass;
        VkShaderModule              ShaderModuleVert;
        VkShaderModule              ShaderModuleFrag;

        // Font data
        VkSampler                   FontSampler;
        VkDeviceMemory              FontMemory;
        VkImage                     FontImage;
        VkImageView                 FontView;
        VkDescriptorSet             FontDescriptorSet;
        VkDeviceMemory              UploadBufferMemory;
        VkBuffer                    UploadBuffer;

        // Render buffers for main window
        ImGui_ImplVulkanH_WindowRenderBuffers MainWindowRenderBuffers;

        ImGui_ImplVulkan_Data()
        {
            memset(this, 0, sizeof(*this));
            BufferMemoryAlignment = 256;
        }
    };

    class SRVulkan : public EvoVulkan::Core::VulkanKernel {
    protected:
        ~SRVulkan() override = default;

    public:
        bool OnResize() override;

        void PollWindowEvents() override;

        SR_NODISCARD bool IsWindowValid() const override;
        SR_NODISCARD bool IsRayTracingRequired() const noexcept override;

        bool BuildCmdBuffers() override {
            return true;
        }

        bool OnComplete() override {
            return true;
        }

        void SetGUIEnabled(bool enabled) override;

        bool Destroy() override {
            return EvoVulkan::Core::VulkanKernel::Destroy();
        }

    private:
        EvoVulkan::Core::RenderResult Render() override;
        EvoVulkan::Core::FrameResult PrepareFrame() override;
        EvoVulkan::Core::FrameResult SubmitFrame() override;
        EvoVulkan::Core::FrameResult QueuePresent() override;
        EvoVulkan::Core::FrameResult WaitIdle() override;

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

        EvoVulkan::Complexes::FrameBuffer*              m_currentVkFramebuffer = nullptr;
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
        static const std::vector<const char*> m_deviceExtensions;

        bool m_enableValidationLayers = false;

    public:
        SR_NODISCARD SR_FORCE_INLINE PipelineType GetType()       const override { return PipelineType::Vulkan; }
        SR_NODISCARD SR_FORCE_INLINE uint8_t  GetCountBuildIter() const override { return m_kernel->GetCountBuildIterations(); }
        SR_NODISCARD VulkanTypes::VkImGUI* GetVkImGUI() const { return m_imgui; }
        SR_NODISCARD std::string GetPipeLineName()   const override { return "Vulkan";         }
        SR_NODISCARD VulkanTools::MemoryManager* GetMemoryManager() const { return m_memory; }
        SR_NODISCARD EvoVulkan::Core::VulkanKernel* GetKernel() const { return m_kernel; }
        SR_NODISCARD void* GetCurrentFBOHandle() const override;
        SR_NODISCARD std::set<void*> GetFBOHandles() const override;

        uint64_t GetVRAMUsage() override;

        bool OnResize(const SR_MATH_NS::UVector2& size) override;
        void UpdateMultiSampling() override;
        void PrepareFrame() override;

        bool PreInit(
                unsigned int smooth_samples,
                const std::string& appName,
                const std::string& engineName,
                const std::string& glslc) override;

        bool Init(const WindowPtr& windowPtr, int swapInterval) override;
        bool PostInit() override;

        void DeInitialize() override;

        bool InitGUI() override;
        bool StopGUI() override;
        void SetGUIEnabled(bool enabled) override {
            if (m_guiEnabled == enabled) {
                return;
            }

            m_guiEnabled = enabled;

            m_kernel->SetGUIEnabled(enabled);
        }
        bool BeginDrawGUI() override;
        void EndDrawGUI() override;

        SR_MATH_NS::IVector2 GetScreenSize() const override;

        SR_NODISCARD InternalTexture GetTexture(uint32_t id) const override;

        SR_NODISCARD void* TryGetDescriptorSetFromTexture(uint32_t id, bool imgui) const override {
            if (id == SR_ID_INVALID) {
                SR_ERROR("Vulkan::GetDescriptorSetFromTexture() : invalid id!");
                return nullptr;
            }

            if (!imgui) {
                SR_ERROR("Vulkan::GetDescriptorSetFromTexture() : todo!");
                return nullptr;
            }

            if (auto texture = m_memory->m_textures[id]) {
                auto&& layout = ((ImGui_ImplVulkan_Data*)ImGui::GetIO().BackendRendererUserData)->DescriptorSetLayout;
                return reinterpret_cast<void *>(texture->GetDescriptorSet(layout).m_self);
            }
            else {
                return nullptr;
            }
        }

        SR_NODISCARD void* GetDescriptorSetFromTexture(uint32_t id, bool imgui) const override {
            if (id == SR_ID_INVALID) {
                SR_ERROR("Vulkan::GetDescriptorSetFromTexture() : invalid id!");
                return nullptr;
            }

            if (!imgui) {
                SR_ERROR("Vulkan::GetDescriptorSetFromTexture() : todo!");
                return nullptr;
            }

            if (auto texture = m_memory->m_textures[id]) {
                auto&& layout = ((ImGui_ImplVulkan_Data*)ImGui::GetIO().BackendRendererUserData)->DescriptorSetLayout;
                return reinterpret_cast<void *>(texture->GetDescriptorSet(layout).m_self);
            }
            else {
                SR_ERROR("Vulkan::GetDescriptorSetFromTexture() : texture does not exist!\n\tTexture id: " + std::to_string(id));
                SRHalt("Something went wrong...");
                return nullptr;
            }
        }
        //[[nodiscard]] void* GetDescriptorSetFromDTDSet(uint32_t id) const override;

        void SetBuildState(bool isBuild) override;

        [[nodiscard]] SR_FORCE_INLINE bool IsGUISupport()       const override { return true; }
        [[nodiscard]] SR_FORCE_INLINE std::string GetVendor()   const override { return m_kernel->GetDevice()->GetName(); }
        [[nodiscard]] SR_FORCE_INLINE std::string GetRenderer() const override { return "Vulkan"; }
        [[nodiscard]] SR_FORCE_INLINE std::string GetVersion()  const override { return "VK_API_VERSION_1_2"; }

        SR_FORCE_INLINE void SetLineWidth(float_t width) const override {
            vkCmdSetLineWidth(m_currentCmd, width);
        }

        bool SetContextCurrent() override { return true; }
        void SetViewport(int32_t width, int32_t height) override;
        void SetScissor(int32_t width, int32_t height) override;

        SR_FORCE_INLINE bool BeginCmdBuffer() override {
            vkBeginCommandBuffer(m_currentCmd, &m_cmdBufInfo);
            return true;
        }

        uint8_t GetFramebufferSampleCount() const override;

        SR_FORCE_INLINE bool BeginRender() override {
            if (!m_renderPassBI.pClearValues) {
                SRAssert2Once(false, "pClearValues is nullptr! Please, call ClearBuffers before BeginRender");
                return false;
            }

            vkCmdBeginRenderPass(m_currentCmd, &m_renderPassBI, VK_SUBPASS_CONTENTS_INLINE);

            return true;
        }

        SR_FORCE_INLINE void EndCmdBuffer() override {
            vkEndCommandBuffer(m_currentCmd);
        }

        SR_FORCE_INLINE void EndRender() override {
            vkCmdEndRenderPass(m_currentCmd);
        }

        SR_FORCE_INLINE void ClearFramebuffersQueue() override {
            m_fboQueue.Clear();
        }

        /** \Vulkan Clear next frame buffer usage */
        SR_FORCE_INLINE void ClearBuffers() override {
            if (m_currentFBOid < 0) {
                SR_ERROR("Vulkan::ClearBuffers() : frame buffer is not attached!");
                return;
            }
            else if (m_currentFBOid > 0) {
                m_renderPassBI.clearValueCount = m_memory->m_FBOs[m_currentFBOid - 1]->GetCountClearValues();
                m_renderPassBI.pClearValues    = m_memory->m_FBOs[m_currentFBOid - 1]->GetClearValues();
            }
            else {
                /// в какой ситуации это может случиться?
                SRHalt("Vulkan::ClearBuffers() : TODO!");
            }
        }

        void ClearBuffers(float r, float g, float b, float a, float depth, uint8_t colorCount) override;
        void ClearBuffers(const std::vector<SR_MATH_NS::FColor>& colors, float_t depth) override;

        SR_FORCE_INLINE void DrawFrame() override {
            switch (m_kernel->NextFrame()) {
                case EvoVulkan::Core::RenderResult::Fatal:
                    SR_UTILS_NS::EventManager::Instance().Broadcast(SR_UTILS_NS::EventManager::Event::FatalError);
                    m_hasErrors = true;
                    break;
                case EvoVulkan::Core::RenderResult::Error:
                    SR_ERROR("Vulkan::DrawFrame() : ex error has been occurred!");
                    m_hasErrors = true;
                    break;
                case EvoVulkan::Core::RenderResult::DeviceLost:
                    SR_ERROR("Vulkan::DrawFrame() : device lost! Terminate...");
                    SR_PLATFORM_NS::Terminate();
                    break;
                default:
                    break;
            }
        }

        SR_FORCE_INLINE bool ReCreateShader(uint32_t shaderProgram) override {
            if (auto shader = m_memory->m_ShaderPrograms[shaderProgram]) {
                if (m_currentFBOid < 0) {
                    SR_ERROR("Vulkan::ReCreateShader() : frame buffer is not attached!");
                    return false;
                }

                if (auto renderPass = (m_currentFBOid == 0 ? m_kernel->GetRenderPass() : m_memory->m_FBOs[m_currentFBOid - 1]->GetRenderPass())) {
                    if (!shader->ReCreatePipeLine(renderPass)) {
                        SR_ERROR("Vulkan::ReCreateShader() : failed to re-create pipeLine!");
                        return true;
                    }
                } else {
                    SR_ERROR("Vulkan::ReCreateShader() : failed to get render pass!");
                    return false;
                }
            }
            else {
                SR_ERROR("Vulkan::ReCreateShader() : shader does not exist!");
                return false;
            }

            return true;
        }

        int32_t AllocateShaderProgram(const SRShaderCreateInfo& createInfo, int32_t fbo) override;

        SR_FORCE_INLINE void UseShader(SR_SHADER_PROGRAM shaderProgram) override {
            if (shaderProgram >= m_memory->m_countShaderPrograms.first) {
                SR_ERROR("Vulkan::UseShader() : index out of range!");
                return;
            }

            m_currentShaderID = (int)shaderProgram;
            m_currentShader   = m_memory->m_ShaderPrograms[shaderProgram];
            if (!m_currentShader) {
                SR_ERROR("Vulkan::UseShader() : shader is nullptr!");
                return;
            }
            m_currentLayout = m_currentShader->GetPipelineLayout();

            m_currentShader->Bind(m_currentCmd);
        }

        void OnMultiSampleChanged() override;

        bool CreateFrameBuffer(const SR_MATH_NS::IVector2& size, int32_t& FBO, DepthLayer* pDepth, std::vector<ColorLayer>& colors, uint8_t sampleCount, uint32_t layersCount) override;

        SR_FORCE_INLINE bool DeleteShader(SR_SHADER_PROGRAM shaderProgram) override {
            if (!m_memory->FreeShaderProgram(shaderProgram)) {
                SR_ERROR("Vulkan::DeleteShader() : failed free shader program!");
                return false;
            }
            return true;
        }

        SR_FORCE_INLINE void UnUseShader() override {
            m_currentShader   = nullptr;
            m_currentShaderID = -1;
            m_currentLayout   = VK_NULL_HANDLE;
        }
    public:

        void PushConstants(void* pData, uint64_t size) override;

        SR_FORCE_INLINE void ResetDescriptorSet() override {
            Environment::ResetDescriptorSet();
            m_currentDesrSets = VK_NULL_HANDLE;
        }

        SR_FORCE_INLINE void DrawIndices(const uint32_t& countIndices) const override {
            if (m_currentDesrSets != VK_NULL_HANDLE)
                vkCmdBindDescriptorSets(m_currentCmd, VK_PIPELINE_BIND_POINT_GRAPHICS, m_currentLayout, 0, 1, &m_currentDesrSets, 0, NULL);

            vkCmdDrawIndexed(m_currentCmd, countIndices, 1, 0, 0, 0);
        }

        SR_FORCE_INLINE void BindUBO(const uint32_t& UBO) override {
            m_currentUBOid = UBO;
        }

        SR_FORCE_INLINE void Draw(const uint32_t& countVerts) const override {
            if (m_currentDesrSets != VK_NULL_HANDLE)
                vkCmdBindDescriptorSets(m_currentCmd, VK_PIPELINE_BIND_POINT_GRAPHICS, m_currentLayout, 0, 1, &m_currentDesrSets, 0, NULL);

            vkCmdDraw(m_currentCmd, countVerts, 1, 0, 0);
        }

        [[nodiscard]] SR_FORCE_INLINE int32_t AllocateUBO(uint32_t uboSize) const override {
            SRAssert2(uboSize > 0, "Incorrect UBO size!");

            if (auto&& id = m_memory->AllocateUBO(uboSize); id < 0) {
                SR_ERROR("Vulkan::AllocateUBO() : failed to allocate uniform buffer object!");
                return SR_ID_INVALID;
            }
            else
                return id;
        }

        SR_FORCE_INLINE void UpdateUBO(const uint32_t& UBO, void* data, const uint64_t& uboSize) override {
            if (UBO >= m_memory->m_countUBO.first) { // TODO: add check debug/release
                SRAssert2(false, "Vulkan::UpdateUBO() : uniform index out of range! \n\tCount uniforms: " +
                                     std::to_string(m_memory->m_countUBO.first) + "\n\tIndex: " + std::to_string(UBO));
                return;
            }

            if (!m_memory->m_UBOs[UBO]) {
                SRAssertOnce(false);
                return;
            }

            m_memory->m_UBOs[UBO]->CopyToDevice(data, uboSize);
        }

        SR_FORCE_INLINE bool UpdateDescriptorSets(uint32_t descriptorSet, const std::vector<std::pair<DescriptorType, std::pair<uint32_t, uint32_t>>>& updateValues) override {
            std::vector<VkWriteDescriptorSet> writeDescriptorSets = {};
            for (const auto& value : updateValues) {
                switch (value.first) {
                    case DescriptorType::Uniform: {
                        auto vkDescriptorSet = m_memory->m_descriptorSets[descriptorSet].m_self;
                        if (value.second.second >= m_memory->m_countUBO.first) {
                            SRAssert2(false, "Vulkan::UpdateDescriptorSets() : uniform index out of range! \n\tCount uniforms: " +
                                                 std::to_string(m_memory->m_countUBO.first) + "\n\tIndex: " + std::to_string(value.second.second));
                            return false;
                        }
                        auto vkUBODescriptor = m_memory->m_UBOs[value.second.second]->GetDescriptorRef();
                        writeDescriptorSets.emplace_back(EvoVulkan::Tools::Initializers::WriteDescriptorSet(
                                vkDescriptorSet,
                                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                                value.second.first,
                                vkUBODescriptor));
                        break;
                    }
                    default:
                        SR_ERROR("Vulkan::UpdateDescriptorSets() : unknown type!");
                        return false;
                }
            }

            if (writeDescriptorSets.empty()) {
                SRAssert(false);
                return false;
            }

            vkUpdateDescriptorSets(*m_kernel->GetDevice(), writeDescriptorSets.size(), writeDescriptorSets.data(), 0, NULL);

            return true;
        }

        SR_FORCE_INLINE bool FreeDescriptorSet(int32_t* descriptorSet) override {
            if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Full)
                SR_GRAPH_LOG("Vulkan::FreeDescriptorSet() : free descriptor set...");

            if (!m_memory->FreeDescriptorSet(*descriptorSet)) {
                SR_ERROR("Vulkan::FreeDescriptorSet() : failed to free descriptor set!");
                *descriptorSet = SR_ID_INVALID;
                return false;
            }

            *descriptorSet = SR_ID_INVALID;

            return true;
        }
        SR_FORCE_INLINE int32_t AllocDescriptorSet(std::vector<uint64_t> types) override {
            types = VulkanTools::CastAbsDescriptorTypeToVk(std::move(types));

		#ifdef SR_DEBUG
            if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Full) {
                SR_GRAPH_LOG("Vulkan::AllocDescriptorSet() : allocate new descriptor set...");
            }
		#endif

            if (m_currentShaderID < 0) {
                SR_ERROR("Vulkan::AllocDescriptorSet() : shader program do not set!");
                SRHaltOnce0();
                return SR_ID_INVALID;
            }

            if (auto&& id = m_memory->AllocateDescriptorSet(m_currentShaderID, types); id >= 0) {
                return id;
            }
            else {
                SR_ERROR("Vulkan::AllocDescriptorSet() : failed to allocate descriptor set!");
                return SR_ID_INVALID;
            }
        }

        SR_FORCE_INLINE int32_t AllocDescriptorSetFromTexture(uint32_t textureID) override {
            if (!m_memory->m_textures[textureID]) {
                SR_ERROR("Vulkan::AllocDescriptorSetFromTexture() : texture is not exists!");
                return -1;
            }

            if (m_currentShaderID < 0) {
                SR_ERROR("Vulkan::AllocDescriptorSetFromTexture() : shader is not attached!");
                return -1;
            }

            const static std::vector<uint64_t> types = {
                    static_cast<uint64_t>(VulkanTools::CastAbsDescriptorTypeToVk(DescriptorType::CombinedImage))
            };

            int32_t descriptorSetID = m_memory->AllocateDescriptorSet(m_currentShaderID, types);
            if (descriptorSetID < 0) {
                SR_ERROR("Vulkan::AllocDescriptorSetFromTexture() : failed to allocate descriptor set!");
                return -1;
            }

            auto descriptorSet = EvoVulkan::Tools::Initializers::WriteDescriptorSet(
                    m_memory->m_descriptorSets[descriptorSetID].m_self,
                    VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 0,
                    m_memory->m_textures[textureID]->GetDescriptorRef());

            vkUpdateDescriptorSets(*m_kernel->GetDevice(), 1, &descriptorSet, 0, nullptr);

            return descriptorSetID;
        }

        SR_FORCE_INLINE void BindDescriptorSet(const uint32_t& descriptorSet) override {
            Environment::BindDescriptorSet(descriptorSet);

            if (descriptorSet >= m_memory->m_countDescriptorSets.first) {
                SR_ERROR("Vulkan::BindDescriptorSet() : incorrect range! (" + std::to_string(descriptorSet) + ")");
                return;
            }

            m_currentDesrSets = m_memory->m_descriptorSets[descriptorSet].m_self;
        }
        int32_t CalculateTexture(
                uint8_t* data,
                ImageFormat format,
                uint32_t w, uint32_t h,
                TextureFilter filter,
                TextureCompression compression,
                uint8_t mipLevels,
                bool alpha,
                bool cpuUsage) const override;

        int32_t CalculateVBO(void* vertices, Vertices::VertexType type, size_t count) override;
        int32_t CalculateIBO(void* indices, uint32_t indxSize, size_t , int32_t VBO) override;
        [[nodiscard]] int32_t CalculateCubeMap(uint32_t w, uint32_t h, const std::array<uint8_t*, 6>& data, bool cpuUsage) override {
            if (auto id = m_memory->AllocateTexture(data, w, h, VK_FORMAT_R8G8B8A8_UNORM, VK_FILTER_LINEAR, 1, cpuUsage); id < 0) {
                SR_ERROR("Vulkan::CalculateCubeMap() : failed to allocate texture!");
                return -1;
            }
            else
                return id;
        }

        SR_NODISCARD SR_MATH_NS::FColor GetPixelColor(uint64_t textureId, uint32_t x, uint32_t y) override;

        void BindFrameBuffer(SR_GTYPES_NS::Framebuffer* pFBO) override {
            if (!pFBO) {
                m_renderPassBI.framebuffer = m_kernel->m_frameBuffers[m_currentBuildIteration];
                m_renderPassBI.renderPass  = m_kernel->GetRenderPass();
                m_renderPassBI.renderArea  = m_kernel->GetRenderArea();
                m_currentCmd               = m_kernel->m_drawCmdBuffs[m_currentBuildIteration];

                m_currentVkFramebuffer = nullptr;
                m_currentFBOid = 0;
            }
            else {
                auto&& FBO = pFBO->GetId();
                if (FBO == UINT32_MAX) {
                    SR_ERROR("Vulkan::BindFrameBuffer() : frame buffer index equals UINT32_MAX! Something went wrong...");
                    return;
                }

                auto&& pFramebuffer = m_memory->m_FBOs[FBO - 1];
                if (!pFramebuffer) {
                    SR_ERROR("Vulkan::BindFrameBuffer() : frame buffer object don't exist!");
                    return;
                }

                auto&& layers = pFramebuffer->GetLayers();
                uint32_t layerIndex = SR_MIN(m_frameBufferLayer, layers.size() - 1);
                auto&& vkFrameBuffer = layers.at(layerIndex)->GetFramebuffer();

                if (m_fboQueue.Contains(pFBO, layerIndex)) {
                    SR_ERROR("Vulkan::BindFrameBuffer() : frame buffer (\"" + std::to_string(FBO) + "\") is already added to FBO queue!");
                    SRHalt0();
                    return;
                }

                if (!m_fboQueue.Contains(pFBO)) {
                    m_fboQueue.AddFrameBuffer(pFBO, layerIndex);
                }

                m_renderPassBI.framebuffer = vkFrameBuffer;
                m_renderPassBI.renderPass  = pFramebuffer->GetRenderPass();
                m_renderPassBI.renderArea  = pFramebuffer->GetRenderPassArea();
                m_currentCmd               = pFramebuffer->GetCmd();

                m_currentVkFramebuffer = pFramebuffer;
                m_currentFBOid = FBO;
            }
        }

        SR_FORCE_INLINE void BindVBO(const uint32_t& VBO) override {
            if (VBO == SR_ID_INVALID) {
                return;
            }

            vkCmdBindVertexBuffers(m_currentCmd, 0, 1, m_memory->m_VBOs[VBO]->GetCRef(), m_offsets);
        }
        SR_FORCE_INLINE void BindIBO(const uint32_t& IBO) override {
            if (IBO == SR_ID_INVALID) {
                return;
            }

            // TODO: unsafe! VK_INDEX_TYPE_UINT32 can be different!
            vkCmdBindIndexBuffer(m_currentCmd, *m_memory->m_IBOs[IBO], 0, VK_INDEX_TYPE_UINT32);
        }

        SR_FORCE_INLINE void BindAttachment(const uint8_t activeTexture, const uint32_t& ID) const override {
            if (ID >= m_memory->m_countTextures.first) {
                SRHalt("Vulkan::BindTexture() : incorrect range! (" + std::to_string(ID) + ")");
                return;
            }

            EvoVulkan::Types::Texture* texture = m_memory->m_textures[ID];

            if (!texture) {
                SR_ERROR("Vulkan::BindTexture() : texture is not exists!");
                return;
            }

            auto&& descriptorSet = m_memory->m_countDescriptorSets.first <= m_currentDescriptorSetId ? nullptr : m_memory->m_descriptorSets[m_currentDescriptorSetId];
            if (!descriptorSet) {
                SRAssert2Once(false, "Vulkan::BindTexture() : incorrect descriptor set!");
                return;
            }

            auto&& imageDescriptorRef = texture->GetDescriptorRef();

            const auto&& descriptorSetWrite = EvoVulkan::Tools::Initializers::WriteDescriptorSet(
                    descriptorSet.m_self,
                    VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, activeTexture,
                    imageDescriptorRef);

            vkUpdateDescriptorSets(*m_kernel->GetDevice(), 1, &descriptorSetWrite, 0, nullptr);
        }

        SR_FORCE_INLINE void BindTexture(const uint8_t activeTexture, const uint32_t& ID) const override {
            if (ID >= m_memory->m_countTextures.first) {
                SRHalt("Vulkan::BindTexture() : incorrect range! (" + std::to_string(ID) + ")");
                return;
            }

            EvoVulkan::Types::Texture* texture = m_memory->m_textures[ID];

            if (!texture) {
                SR_ERROR("Vulkan::BindTexture() : texture is not exists!");
                return;
            }

            auto&& descriptorSet = m_memory->m_countDescriptorSets.first <= m_currentDescriptorSetId ? nullptr : m_memory->m_descriptorSets[m_currentDescriptorSetId];
            if (!descriptorSet) {
                SRAssert2Once(false, "Vulkan::BindTexture() : incorrect descriptor set!");
                return;
            }

            auto&& imageDescriptorRef = texture->GetDescriptorRef();

            const auto&& descriptorSetWrite = EvoVulkan::Tools::Initializers::WriteDescriptorSet(
                    descriptorSet.m_self,
                    VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, activeTexture,
                    imageDescriptorRef);

            vkUpdateDescriptorSets(*m_kernel->GetDevice(), 1, &descriptorSetWrite, 0, nullptr);
        }

        [[nodiscard]] SR_FORCE_INLINE bool FreeVBO(int32_t* ID) const override {
            const int32_t id = *ID; *ID = SR_ID_INVALID;
            return m_memory->FreeVBO(id);
        }
        [[nodiscard]] SR_FORCE_INLINE bool FreeIBO(int32_t* ID) const override {
            const int32_t id = *ID; *ID = SR_ID_INVALID;
            return m_memory->FreeIBO(id);
        }
        [[nodiscard]] SR_FORCE_INLINE bool FreeUBO(int32_t* ID) const override {
            const int32_t id = *ID; *ID = SR_ID_INVALID;
            return m_memory->FreeUBO(id);
        }

        SR_FORCE_INLINE bool FreeCubeMap(int32_t* ID) override {
            const int32_t id = *ID; *ID = SR_ID_INVALID;

            if (!m_memory->FreeTexture((uint32_t)id)) {
                SR_ERROR("Vulkan::FreeCubeMap() : failed to free texture! (" + std::to_string(id) + ")");
                return false;
            }
            else
                return true;
        }

        [[nodiscard]] bool FreeTextures(int32_t* IDs, uint32_t count) const override;

        [[nodiscard]] bool FreeTexture(int32_t* id) const override {
            if (!m_memory->FreeTexture(static_cast<uint32_t>(*id))) {
                SR_ERROR("Vulkan::FreeTexture() : failed to free texture!");
                return false;
            }

            *id = SR_ID_INVALID;

            return true;
        }

        [[nodiscard]] bool FreeFBO(uint32_t FBO) const override;

        void SetCurrentFramebuffer(Types::Framebuffer *pFramebuffer) override;
    };
}

#endif //GAMEENGINE_VULKAN_H
