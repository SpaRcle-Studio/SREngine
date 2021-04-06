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

#include <Environment/Vulkan/VulkanTools.h>

constexpr double CIRCLE_RAD		= M_PI * 2;
constexpr double CIRCLE_THIRD	= CIRCLE_RAD / 3.0;
constexpr double CIRCLE_THIRD_1	= 0;
constexpr double CIRCLE_THIRD_2	= CIRCLE_THIRD;
constexpr double CIRCLE_THIRD_3	= CIRCLE_THIRD * 2;

namespace Framework::Graphics {
    VKAPI_ATTR VkBool32 VKAPI_CALL DebugVulkanCallback(
            VkDebugReportFlagsEXT flags,
            VkDebugReportObjectTypeEXT objType,
            uint64_t obj,
            size_t location,
            int32_t code,
            const char* layerPrefix,
            const char* msg,
            void* userData);

    class Vulkan : public Environment {
    public:
        Vulkan(Vulkan &) = delete;
    public:
        Vulkan() = default;
        ~Vulkan() = default;
    private:
        const std::vector<const char*> m_validationLayers = {
                "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> m_deviceExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

#ifdef NDEBUG
        const bool m_enableValidationLayers = false;
#else
        const bool m_enableValidationLayers = true;
#endif
        VkInstance                   m_vkInstance     = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT     m_debugMessenger = VK_NULL_HANDLE;

        VulkanTools::Surface         m_surface        = {};
        VulkanTools::Device          m_device         = {};
        VulkanTools::Synchronization m_sync           = {};

        VulkanTools::Swapchain       m_swapchain      = {};

        VkResult                     m_queuePresent   = VK_RESULT_MAX_ENUM;
        VkCommandPool                m_commandPool    = VK_NULL_HANDLE;
        VkRenderPass                 m_renderPass     = VK_NULL_HANDLE;

        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;

        std::vector<VkCommandBuffer> commandBuffers;
    public:
        [[nodiscard]] SR_FORCE_INLINE std::string GetPipeLineName() const noexcept override { return "Vulkan"; }
        [[nodiscard]] SR_FORCE_INLINE PipeLine GetPipeLine() const noexcept override { return PipeLine::Vulkan; }
    public:
        [[nodiscard]] std::vector<const char*> getRequiredExtensions() const {
            std::vector<const char*> extensions;

            extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
            extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

            if (m_enableValidationLayers)
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

            return extensions;
        }


        bool checkValidationLayerSupport() {
            uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

            for (const char* layerName : m_validationLayers) {
                bool layerFound = false;

                for (const auto& layerProperties : availableLayers) {
                    if (strcmp(layerName, layerProperties.layerName) == 0) {
                        layerFound = true;
                        break;
                    }
                }

                if (!layerFound) {
                    return false;
                }
            }

            return true;
        }

        void createGraphicsPipeline() {
            std::string name = "geometry";

            std::string vertex_path   = Helper::ResourceManager::GetResourcesFolder()
                                        + "\\Shaders\\" + GetPipeLineName() + "\\" + name + ".vert";
            std::string fragment_path = Helper::ResourceManager::GetResourcesFolder()
                                        + "\\Shaders\\" + GetPipeLineName() + "\\" + name + ".frag";

            std::string cache = Helper::ResourceManager::GetResourcesFolder() + R"(\Cache\Shaders\)";

            std::string vert_output = cache + name + ".vert.spv";
            std::string frag_output = cache + name + ".frag.spv";

            Helper::FileSystem::CreatePath(Helper::FileSystem::GetDirFromPath(vert_output));
            Helper::FileSystem::CreatePath(Helper::FileSystem::GetDirFromPath(frag_output));

            Helper::Debug::Shader("Vulkan::CompileShader() : compile source code...");

            system(("glslc " + vertex_path   + " -o " + vert_output).c_str());
            system(("glslc " + fragment_path + " -o " + frag_output).c_str());

            //!=============================================================================================================

            auto vertShaderCode = Helper::FileSystem::ReadBinary(vert_output);
            auto fragShaderCode = Helper::FileSystem::ReadBinary(frag_output);

            VkShaderModule vertShaderModule = CreateShaderModule(m_device, vertShaderCode);
            VkShaderModule fragShaderModule = CreateShaderModule(m_device, fragShaderCode);

            VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
            vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
            vertShaderStageInfo.module = vertShaderModule;
            vertShaderStageInfo.pName = "main";

            VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
            fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
            fragShaderStageInfo.module = fragShaderModule;
            fragShaderStageInfo.pName = "main";

            VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

            VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
            vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
            vertexInputInfo.vertexBindingDescriptionCount = 0;
            vertexInputInfo.vertexAttributeDescriptionCount = 0;

            VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
            inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
            inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
            inputAssembly.primitiveRestartEnable = VK_FALSE;

            VkViewport viewport{};
            viewport.x = 0.0f;
            viewport.y = 0.0f;
            viewport.width = (float) m_swapchain.m_swapChainExtent.width;
            viewport.height = (float) m_swapchain.m_swapChainExtent.height;
            viewport.minDepth = 0.0f;
            viewport.maxDepth = 1.0f;

            VkRect2D scissor{};
            scissor.offset = {0, 0};
            scissor.extent = m_swapchain.m_swapChainExtent;

            VkPipelineViewportStateCreateInfo viewportState{};
            viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
            viewportState.viewportCount = 1;
            viewportState.pViewports = &viewport;
            viewportState.scissorCount = 1;
            viewportState.pScissors = &scissor;

            VkPipelineRasterizationStateCreateInfo rasterizer{};
            rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
            rasterizer.depthClampEnable = VK_FALSE;
            rasterizer.rasterizerDiscardEnable = VK_FALSE;
            rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
            rasterizer.lineWidth = 1.0f;
            rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
            rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
            rasterizer.depthBiasEnable = VK_FALSE;

            VkPipelineMultisampleStateCreateInfo multisampling{};
            multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
            multisampling.sampleShadingEnable = VK_FALSE;
            multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

            VkPipelineColorBlendAttachmentState colorBlendAttachment{};
            colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
            colorBlendAttachment.blendEnable = VK_FALSE;

            VkPipelineColorBlendStateCreateInfo colorBlending{};
            colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
            colorBlending.logicOpEnable = VK_FALSE;
            colorBlending.logicOp = VK_LOGIC_OP_COPY;
            colorBlending.attachmentCount = 1;
            colorBlending.pAttachments = &colorBlendAttachment;
            colorBlending.blendConstants[0] = 0.0f;
            colorBlending.blendConstants[1] = 0.0f;
            colorBlending.blendConstants[2] = 0.0f;
            colorBlending.blendConstants[3] = 0.0f;

            VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
            pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
            pipelineLayoutInfo.setLayoutCount = 0;
            pipelineLayoutInfo.pushConstantRangeCount = 0;

            if (vkCreatePipelineLayout(m_device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
                throw std::runtime_error("failed to create pipeline layout!");
            }

            VkGraphicsPipelineCreateInfo pipelineInfo{};
            pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
            pipelineInfo.stageCount = 2;
            pipelineInfo.pStages = shaderStages;
            pipelineInfo.pVertexInputState = &vertexInputInfo;
            pipelineInfo.pInputAssemblyState = &inputAssembly;
            pipelineInfo.pViewportState = &viewportState;
            pipelineInfo.pRasterizationState = &rasterizer;
            pipelineInfo.pMultisampleState = &multisampling;
            pipelineInfo.pColorBlendState = &colorBlending;
            pipelineInfo.layout = pipelineLayout;
            pipelineInfo.renderPass = m_renderPass;
            pipelineInfo.subpass = 0;
            pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

            if (vkCreateGraphicsPipelines(m_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
                throw std::runtime_error("failed to create graphics pipeline!");
            }

            vkDestroyShaderModule(m_device, fragShaderModule, nullptr);
            vkDestroyShaderModule(m_device, vertShaderModule, nullptr);
        }

        void createFramebuffers() {
            m_swapchain.m_swapChainFramebuffers.resize(m_swapchain.m_swapChainImageViews.size());

            for (size_t i = 0; i < m_swapchain.m_swapChainImageViews.size(); i++) {
                VkImageView attachments[] = {
                        m_swapchain.m_swapChainImageViews[i]
                };

                VkFramebufferCreateInfo framebufferInfo{};
                framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
                framebufferInfo.renderPass = m_renderPass;
                framebufferInfo.attachmentCount = 1;
                framebufferInfo.pAttachments = attachments;
                framebufferInfo.width = m_swapchain.m_swapChainExtent.width;
                framebufferInfo.height = m_swapchain.m_swapChainExtent.height;
                framebufferInfo.layers = 1;

                if (vkCreateFramebuffer(m_device, &framebufferInfo, nullptr, &m_swapchain.m_swapChainFramebuffers[i]) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create framebuffer!");
                }
            }
        }

        void createCommandBuffers() {
            commandBuffers.resize(m_swapchain.m_swapChainFramebuffers.size());

            VkCommandBufferAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            allocInfo.commandPool = m_commandPool;
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

            if (vkAllocateCommandBuffers(m_device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
                throw std::runtime_error("failed to allocate command buffers!");
            }

            for (size_t i = 0; i < commandBuffers.size(); i++) {
                VkCommandBufferBeginInfo beginInfo{};
                beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

                if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
                    throw std::runtime_error("failed to begin recording command buffer!");
                }

                VkRenderPassBeginInfo renderPassInfo{};
                renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
                renderPassInfo.renderPass = m_renderPass;
                renderPassInfo.framebuffer = m_swapchain.m_swapChainFramebuffers[i];
                renderPassInfo.renderArea.offset = {0, 0};
                renderPassInfo.renderArea.extent = m_swapchain.m_swapChainExtent;

                VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
                renderPassInfo.clearValueCount = 1;
                renderPassInfo.pClearValues = &clearColor;

                vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

                vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

                vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

                vkCmdEndRenderPass(commandBuffers[i]);

                if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                    throw std::runtime_error("failed to record command buffer!");
                }
            }
        }
    public:
        bool PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) override;
        bool Init(int swapInterval) override;

        bool MakeWindow(const char* winName, bool fullScreen, bool resizable) override;
        bool CloseWindow() override;
        bool SetContextCurrent() override {
            return true;
        }

        [[nodiscard]] glm::vec2 GetWindowSize() const noexcept override {
            return { this->m_basicWindow->GetWidth(), this->m_basicWindow->GetHeight() };
        }

        [[nodiscard]] SR_FORCE_INLINE bool IsWindowOpen() const noexcept override {
             return m_basicWindow->IsWindowOpen();
        }

        SR_FORCE_INLINE void SwapBuffers() const noexcept override  {
            this->m_basicWindow->SwapBuffers();
        }

        SR_FORCE_INLINE void PollEvents() const noexcept override {
            this->m_basicWindow->PollEvents();
        }

        void SetWindowPosition(int x, int y) override;
        void SetWindowSize(unsigned int w, unsigned int h) override;

        //!===============================================[SHADERS]=====================================================

        SR_FORCE_INLINE void DrawFrame() override {
            vkWaitForFences(m_device, 1, &m_sync.m_inFlightFences[m_sync.m_currentFrame], VK_TRUE, UINT64_MAX);

            uint32_t imageIndex;
            vkAcquireNextImageKHR(m_device, m_swapchain, UINT64_MAX, m_sync.m_imageAvailableSemaphores[m_sync.m_currentFrame], VK_NULL_HANDLE, &imageIndex);

            if (m_sync.m_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
                vkWaitForFences(m_device, 1, &m_sync.m_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
            }
            m_sync.m_imagesInFlight[imageIndex] = m_sync.m_inFlightFences[m_sync.m_currentFrame];

            VkSubmitInfo submitInfo{};
            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

            VkSemaphore waitSemaphores[] = { m_sync.m_imageAvailableSemaphores[m_sync.m_currentFrame] };
            VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
            submitInfo.waitSemaphoreCount = 1;
            submitInfo.pWaitSemaphores = waitSemaphores;
            submitInfo.pWaitDstStageMask = waitStages;

            submitInfo.commandBufferCount = 1;
            submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

            VkSemaphore signalSemaphores[] = { m_sync.m_renderFinishedSemaphores[m_sync.m_currentFrame] };
            submitInfo.signalSemaphoreCount = 1;
            submitInfo.pSignalSemaphores = signalSemaphores;

            vkResetFences(m_device, 1, &m_sync.m_inFlightFences[m_sync.m_currentFrame]);

            if (vkQueueSubmit(m_device.m_queue.m_graphicsQueue, 1, &submitInfo, m_sync.m_inFlightFences[m_sync.m_currentFrame]) != VK_SUCCESS) {
                Helper::Debug::Error("Vulkan::DrawFrame() : failed to submit draw command buffer!");
                m_hasErrors = true;
                return;
            }

            VkPresentInfoKHR presentInfo{};
            presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

            presentInfo.waitSemaphoreCount = 1;
            presentInfo.pWaitSemaphores = signalSemaphores;

            presentInfo.swapchainCount = 1;
            presentInfo.pSwapchains = &m_swapchain.m_swapChain;

            presentInfo.pImageIndices = &imageIndex;

            m_queuePresent = vkQueuePresentKHR(m_device.m_queue.m_presentQueue, &presentInfo);
            switch (m_queuePresent) {
                case VK_SUCCESS: break;
                case VK_ERROR_OUT_OF_DATE_KHR:
                    Helper::Debug::System("Vulkan::DrawFrame() : out of date KHR.");
                    break;
                default:
                    Helper::Debug::Error("Vulkan::DrawFrame() : an exception has been occurred!");
                    m_hasErrors = true;
                    break;
            }

            m_sync.m_currentFrame = (m_sync.m_currentFrame + 1) % SR_MAX_FRAMES_IN_FLIGHT;
        }
        SR_FORCE_INLINE void TestDrawing() override {

        }
    };
}

#endif //GAMEENGINE_VULKAN_H
