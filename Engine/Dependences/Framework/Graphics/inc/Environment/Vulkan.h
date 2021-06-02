//
// Created by Nikita on 25.03.2021.
//

#ifndef GAMEENGINE_VULKAN_H
#define GAMEENGINE_VULKAN_H

#include <easy/profiler.h>
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

#include <EvoVulkan/VulkanKernel.h>

namespace Framework::Graphics {
    class SRVulkan : public EvoVulkan::Core::VulkanKernel {
    protected:
        void Render() override {
            if (this->PrepareFrame() == EvoVulkan::Core::FrameResult::OutOfDate)
                this->m_hasErrors = !this->ResizeWindow();

            m_submitInfo.commandBufferCount = 1;
            m_submitInfo.pCommandBuffers    = &m_drawCmdBuffs[m_currentBuffer];

            // Submit to queue
            auto result = vkQueueSubmit(m_device->m_familyQueues->m_graphicsQueue, 1, &m_submitInfo, VK_NULL_HANDLE);
            if (result != VK_SUCCESS) {
                VK_ERROR("renderFunction() : failed to queue submit!");
                return;
            }

            if (this->SubmitFrame() == EvoVulkan::Core::FrameResult::OutOfDate)
                this->m_hasErrors = !this->ResizeWindow();
        }
    public:
        bool OnResize() override {
            vkQueueWaitIdle(m_device->GetGraphicsQueue());
            vkDeviceWaitIdle(*m_device);

            Environment::Get()->SetBuildState(false);

            return true;
        }

        bool BuildCmdBuffers() override {
            /*VkCommandBufferBeginInfo cmdBufInfo = EvoVulkan::Tools::Initializers::CommandBufferBeginInfo();

            VkClearValue clearValues[2] {
                    { .color = {{0.5f, 0.5f, 0.5f, 1.0f}} },
                    { .depthStencil = { 1.0f, 0 } }
            };

            auto renderPassBI = EvoVulkan::Tools::Insert::RenderPassBeginInfo(
                    m_swapchain->GetSurfaceWidth(), m_swapchain->GetSurfaceHeight(), m_renderPass.m_self,
                    VK_NULL_HANDLE, &clearValues[0], 2);

            for (int i = 0; i < 3; i++) {
                renderPassBI.framebuffer = m_frameBuffers[i];

                vkBeginCommandBuffer(m_drawCmdBuffs[i], &cmdBufInfo);
                vkCmdBeginRenderPass(m_drawCmdBuffs[i], &renderPassBI, VK_SUBPASS_CONTENTS_INLINE);

                vkCmdEndRenderPass(m_drawCmdBuffs[i]);
                vkEndCommandBuffer(m_drawCmdBuffs[i]);
            }
            */
            return true;
        }

        bool OnComplete() override {
            //return BuildCmdBuffers();
            return true;
        }

        bool Destroy() override {
            return EvoVulkan::Core::VulkanKernel::Destroy();
        }
    };

    class Vulkan : public Environment {
    public:
        Vulkan(Vulkan &) = delete;
    public:
        Vulkan() = default;
        ~Vulkan() = default;
    private:
        VkViewport                     m_viewport      = { };
        VkRect2D                       m_scissor       = { };

        std::vector<VkClearValue>      m_clearValues   = { };
        VkRenderPassBeginInfo          m_renderPassBI  = { };

        VkCommandBuffer                m_currentCmd    = VK_NULL_HANDLE;
        EvoVulkan::Complexes::Shader*  m_currentShader = nullptr;

        VkCommandBufferBeginInfo       m_cmdBufInfo    = { };

        VulkanTools::MemoryManager*    m_memory        = nullptr;
        EvoVulkan::Core::VulkanKernel* m_kernel        = nullptr;
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
        bool PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) override;
        bool Init(int swapInterval) override;
        bool PostInit() override;

        [[nodiscard]] SR_FORCE_INLINE std::string GetVendor()   const noexcept override { return this->m_kernel->GetDevice()->GetName(); }
        [[nodiscard]] SR_FORCE_INLINE std::string GetRenderer() const noexcept override { return "Vulkan"; }
        [[nodiscard]] SR_FORCE_INLINE std::string GetVersion()  const noexcept override { return "VK_API_VERSION_1_2"; }
        [[nodiscard]] glm::vec2 GetWindowSize()                 const noexcept override { return { this->m_basicWindow->GetRealWidth(), this->m_basicWindow->GetRealHeight() }; }
        [[nodiscard]] SR_FORCE_INLINE bool IsWindowOpen()       const noexcept override { return m_basicWindow->IsWindowOpen(); }

        bool MakeWindow(const char* winName, bool fullScreen, bool resizable) override;
        void SetWindowIcon(const char* path) override { this->m_basicWindow->SetIcon(path); }
        bool CloseWindow() override;
        bool SetContextCurrent() override { return true; }
        void SetViewport(int32_t width, int32_t height) override {
            if (m_currentFBO == 0)
                this->m_viewport = this->m_kernel->GetViewport();
            else {
                Helper::Debug::Error("Vulkan::SetViewport() : TODO!");
            }

            vkCmdSetViewport(m_currentCmd, 0, 1, &m_viewport);
        }
        void SetScissor(int32_t width, int32_t height) override {
            if (m_currentFBO == 0)
                this->m_scissor = this->m_kernel->GetScissor();
            else {
                Helper::Debug::Error("Vulkan::SetScissor() : TODO!");
            }

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

        /**
         \Vulkan Clear next frame buffer usage
         */
        SR_FORCE_INLINE void ClearBuffers(float r, float g, float b, float a, float depth, uint8_t colorCount) noexcept override {
            this->m_clearValues.resize(colorCount + 1);
            for (uint8_t i = 0; i < colorCount; i++)
                m_clearValues[i] = { .color = {{ r, g, b, a }} };
            m_clearValues[colorCount] = { .depthStencil = { depth, 0 } };
            this->m_renderPassBI.clearValueCount = colorCount + 1;
            this->m_renderPassBI.pClearValues    = m_clearValues.data();
        }

        SR_FORCE_INLINE void DrawFrame() override { this->m_kernel->NextFrame(); }
        SR_FORCE_INLINE void PollEvents() const noexcept override { this->m_basicWindow->PollEvents(); }

        void SetWindowPosition(int x, int y) override;
        void SetWindowSize(unsigned int w, unsigned int h) override;

        bool CompileShader(
                const std::string& path,
                int32_t FBO,
                void** shaderData,
                const std::vector<uint64_t>& uniformSizes = {}) const noexcept override;
        bool LinkShader(
                SR_SHADER_PROGRAM* shaderProgram,
                void** shaderData,
                const std::vector<SR_VERTEX_DESCRIPTION>& vertexDescriptions = {},
                const std::vector<std::pair<Vertices::Attribute, size_t>>& vertexAttributes = {},
                SRShaderCreateInfo shaderCreateInfo = {}) const noexcept override;

        SR_FORCE_INLINE void UseShader(SR_SHADER_PROGRAM shaderProgram) noexcept override {
            if (shaderProgram >= m_memory->m_countShaderPrograms) {
                Helper::Debug::Error("Vulkan::UseShader() : index out of range!");
                return;
            }

            this->m_currentShader = m_memory->m_ShaderPrograms[shaderProgram];

            if (!m_currentShader) {
                Helper::Debug::Error("Vulkan::UseShader() : shader is nullptr!");
                return;
            }

            this->m_currentShader->Bind(this->m_currentCmd);
        }

        SR_FORCE_INLINE void DeleteShader(SR_SHADER_PROGRAM shaderProgram) noexcept override {
            if (!m_memory->FreeShaderProgram(shaderProgram))
                Helper::Debug::Error("Vulkan::DeleteShader() : failed free shader program!");
        }
    public:
        SR_FORCE_INLINE bool CalculateVBO(unsigned int& VBO, void* vertices, uint32_t vertSize, size_t count) const noexcept override {
            auto id = this->m_memory->AllocateVBO(vertSize * count, vertices);
            if (id >= 0) {
                VBO = id;
                return true;
            }
            else
                return false;
        }
        SR_FORCE_INLINE bool CalculateIBO(unsigned int& IBO, void* indices, uint32_t indxSize, size_t count)  const noexcept override {
            auto id = this->m_memory->AllocateIBO(indxSize * count, indices);
            if (id >= 0) {
                IBO = id;
                return true;
            }
            else
                return false;
        }
        SR_FORCE_INLINE void BindFrameBuffer(const unsigned int& FBO) noexcept override {
            if (FBO == 0) {
                this->m_renderPassBI.framebuffer = m_kernel->m_frameBuffers[m_currentBuildIteration];
                this->m_renderPassBI.renderPass  = m_kernel->GetRenderPass().m_self;
                this->m_renderPassBI.renderArea  = m_kernel->GetRenderArea();
                this->m_currentCmd               = m_kernel->m_drawCmdBuffs[m_currentBuildIteration];
            } else {
                Helper::Debug::Error("Vulkan::BindFrameBuffer() : TODO!");
            }

            this->m_currentFBO = FBO;
        }

        [[nodiscard]] SR_FORCE_INLINE bool FreeVBO(uint32_t ID) const noexcept override { return this->m_memory->FreeVBO(ID); }
        [[nodiscard]] SR_FORCE_INLINE bool FreeIBO(uint32_t ID) const noexcept override { return this->m_memory->FreeIBO(ID); }
    };
}

#endif //GAMEENGINE_VULKAN_H
