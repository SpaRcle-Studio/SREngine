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

#include <vulkan/vulkan.h>

#include <Environment/Vulkan/VulkanTools.h>

#include <Environment/Vulkan/VulkanShader.h>

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
        std::vector<const char*> m_extRequired = {
                VK_KHR_SURFACE_EXTENSION_NAME,
                VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
                VK_EXT_DEBUG_REPORT_EXTENSION_NAME
        };
        std::vector<const char*> m_validLayersRequired = {
            "VK_LAYER_LUNARG_standard_validation"
        };


        VkInstance                        m_vkInstance                  = VK_NULL_HANDLE;
        VkDebugReportCallbackEXT          m_validationReportCallBack    = VK_NULL_HANDLE;
        VkSurfaceKHR                      m_vkSurface                   = VK_NULL_HANDLE;
        VkRenderPass                      m_vkRenderPass                = VK_NULL_HANDLE;
        VkFence                           m_swapchainImageAvailable     = VK_NULL_HANDLE;

        std::vector<VkFramebuffer>        m_vkFrameBuffers              = {};

        VulkanTools::Swapchain            m_swapchain                   = {};
        VulkanTools::Device               m_device                      = {};

        std::vector<VkSemaphore>          m_waitSemaphores              = {};
        VkResult                          m_presentResult               = VkResult::VK_RESULT_MAX_ENUM;
    private:
        [[nodiscard]] SR_FORCE_INLINE VkExtent2D GetVulkanSurfaceSize() const noexcept {
            return { m_basicWindow->GetWidth(), m_basicWindow->GetHeight() };
        }
        [[nodiscard]] SR_FORCE_INLINE VkFramebuffer GetVulkanActiveFramebuffer() const noexcept {
            return m_vkFrameBuffers[m_swapchain.m_activeSwapchainImageID];
        }
    public:
        [[nodiscard]] SR_FORCE_INLINE std::string GetPipeLineName() const noexcept override { return "Vulkan"; }
        [[nodiscard]] SR_FORCE_INLINE PipeLine GetPipeLine() const noexcept override { return PipeLine::Vulkan; }
    public:
        bool PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) override;
        bool Init(int swapInterval) override;

        bool MakeWindow(const char* winName, bool fullScreen, bool resizable) override;
        bool CloseWindow() override;
        bool SetContextCurrent() override {
            return true;
        }

        [[nodiscard]] SR_FORCE_INLINE bool IsWindowOpen() const noexcept override {
             return m_basicWindow->IsWindowOpen();
        }

        SR_FORCE_INLINE void SwapBuffers() const noexcept override  {
            this->m_basicWindow->SwapBuffers();
        }

        SR_FORCE_INLINE void BeginRender() override {
            SR_CHECK_ERROR(vkAcquireNextImageKHR(
                    m_device.m_logicalDevice,
                    m_swapchain.m_vkSwapchainKhr,
                    UINT64_MAX,
                    VK_NULL_HANDLE,
                    m_swapchainImageAvailable,
                    &m_swapchain.m_activeSwapchainImageID), VK_SUCCESS, "Vulkan::BeginRender() : failed to acquire next image!");

            SR_CHECK_ERROR(
                    vkWaitForFences(m_device.m_logicalDevice, 1, &m_swapchainImageAvailable, VK_TRUE, UINT64_MAX),
                    VK_SUCCESS,
                    "Vulkan::BeginRender() : failed to wait for fences!");

            SR_CHECK_ERROR(
                    vkResetFences(m_device.m_logicalDevice, 1, &m_swapchainImageAvailable),
                    VK_SUCCESS,
                    "Vulkan::BeginRender() : failed to reset fences!");

#ifdef SR_RELEASE
            vkQueueWaitIdle(m_device.m_queue.m_hQueue);
#else
            switch (vkQueueWaitIdle(m_device.m_queue.m_hQueue)) {
                case VK_SUCCESS:
                    break;
                case VK_ERROR_OUT_OF_HOST_MEMORY:
                    Helper::Debug::Error("Vulkan::BeginRender() : failed to queue wait idle! Out of host memory.");
                    break;
                case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                    Helper::Debug::Error("Vulkan::BeginRender() : failed to queue wait idle! Out of device memory.");
                    break;
                case VK_ERROR_DEVICE_LOST:
                    Helper::Debug::Error("Vulkan::BeginRender() : failed to queue wait idle! Device lost.");
                    break;
                default:
                    break;
            }
#endif
        }
        SR_FORCE_INLINE void EndRender() override {
            this->m_presentResult = VkResult::VK_RESULT_MAX_ENUM;

            VkPresentInfoKHR presentInfoKhr   = {};
            presentInfoKhr.sType			  = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
            presentInfoKhr.waitSemaphoreCount = m_waitSemaphores.size();
            presentInfoKhr.pWaitSemaphores	  = m_waitSemaphores.data();
            presentInfoKhr.swapchainCount	  = 1;
            presentInfoKhr.pSwapchains		  = &m_swapchain.m_vkSwapchainKhr;
            presentInfoKhr.pImageIndices	  = &m_swapchain.m_activeSwapchainImageID;
            presentInfoKhr.pResults			  = &m_presentResult;

            switch (vkQueuePresentKHR(m_device.m_queue.m_hQueue, &presentInfoKhr)) {
                case VK_SUCCESS: break;
                case VK_ERROR_OUT_OF_HOST_MEMORY:
                    Helper::Debug::Error("Vulkan::EndRender() : out of host memory!");
                    break;
                case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                    Helper::Debug::Error("Vulkan::EndRender() : out of device memory!");
                    break;
                case VK_ERROR_DEVICE_LOST:
                    Helper::Debug::Error("Vulkan::EndRender() : device lost!");
                    break;
                case VK_ERROR_OUT_OF_DATE_KHR:
                    Helper::Debug::Error("Vulkan::EndRender() : out of date KHR!");
                    break;
                case VK_ERROR_SURFACE_LOST_KHR:
                    Helper::Debug::Error("Vulkan::EndRender() : surface lost KHR!");
                    break;
                case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
                    Helper::Debug::Error("Vulkan::EndRender() : ful screen exclusive mode lost KHR!");
                    break;
                default:
                    Helper::Debug::Error("Vulkan::EndRender() : an exception has been occurred!");
                    break;
            };
        }

        SR_FORCE_INLINE void TestDrawing() override {
            static VkClearColorValue color = { 1.0, 0.0, 0.0 };

            static float color_rotator = 0.0f;
            static VkSemaphore renderCompleteSemaphore = VK_NULL_HANDLE;
            if (renderCompleteSemaphore == VK_NULL_HANDLE) {
                VkSemaphoreCreateInfo semaphoreCreateInfo = {};
                semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
                vkCreateSemaphore(m_device.m_logicalDevice, &semaphoreCreateInfo, nullptr, &renderCompleteSemaphore);
                this->m_waitSemaphores.push_back(renderCompleteSemaphore);
            }

            VkImageSubresourceRange imageSubresourceRange = {};
            imageSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageSubresourceRange.baseMipLevel = 0;
            imageSubresourceRange.levelCount = 1;
            imageSubresourceRange.baseArrayLayer = 0;
            imageSubresourceRange.layerCount = 1;

            // Record command buffer
            VkCommandBufferBeginInfo commandBufferBeginInfo = {};
            commandBufferBeginInfo.sType				    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            commandBufferBeginInfo.flags				    = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

            VkCommandBuffer commandBuffer = m_swapchain.m_commandBuffers[0];

            vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo);

            vkCmdClearColorImage(
                    commandBuffer,
                    m_swapchain.m_swapchainImages[m_swapchain.m_activeSwapchainImageID],
                    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                    &color, 1, &imageSubresourceRange);

            if (false)
            {
                VkRect2D renderArea = {};
                renderArea.offset.x = 0;
                renderArea.offset.y = 0;
                renderArea.extent = GetVulkanSurfaceSize();

                color_rotator += 0.001;

                std::array<VkClearValue, 2> clearValues = {};
                clearValues[0].depthStencil.depth = 0.0f;
                clearValues[0].depthStencil.stencil = 0;
                clearValues[1].color.float32[0] = std::sin(color_rotator + CIRCLE_THIRD_1) * 0.5 + 0.5;
                clearValues[1].color.float32[1] = std::sin(color_rotator + CIRCLE_THIRD_2) * 0.5 + 0.5;
                clearValues[1].color.float32[2] = std::sin(color_rotator + CIRCLE_THIRD_3) * 0.5 + 0.5;
                clearValues[1].color.float32[3] = 1.0f;

                VkRenderPassBeginInfo renderPassBeginInfo = {};
                renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
                renderPassBeginInfo.renderPass = m_vkRenderPass;
                renderPassBeginInfo.framebuffer = GetVulkanActiveFramebuffer();
                renderPassBeginInfo.renderArea = renderArea;
                renderPassBeginInfo.clearValueCount = clearValues.size();
                renderPassBeginInfo.pClearValues = clearValues.data();

                vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

                vkCmdEndRenderPass(commandBuffer);
            }
            vkEndCommandBuffer(commandBuffer);

            // Submit command buffer
            VkSubmitInfo submitInfo             = {};
            submitInfo.sType					= VK_STRUCTURE_TYPE_SUBMIT_INFO;
            submitInfo.waitSemaphoreCount		= 0;
            submitInfo.pWaitSemaphores			= nullptr;
            submitInfo.pWaitDstStageMask		= nullptr;
            submitInfo.commandBufferCount		= 1;
            submitInfo.pCommandBuffers			= &commandBuffer;
            submitInfo.signalSemaphoreCount	    = 1;
            submitInfo.pSignalSemaphores		= &renderCompleteSemaphore;

            vkQueueSubmit(m_device.m_queue.m_hQueue, 1, &submitInfo, VK_NULL_HANDLE);
        }

        SR_FORCE_INLINE void PollEvents() const noexcept override {
            this->m_basicWindow->PollEvents();
        }

        //!===============================================[SHADERS]=====================================================

        [[nodiscard]] IShaderProgram* AllocShaderProgram() const noexcept override {
            return (VulkanShader*)malloc(sizeof(VulkanShader));
        }
        SR_FORCE_INLINE void DeleteShader(IShaderProgram* shaderProgram) const noexcept override {
            VulkanTools::DestroyShader(m_device, &((VulkanShader*)shaderProgram)->m_vertShaderModule);
            VulkanTools::DestroyShader(m_device, &((VulkanShader*)shaderProgram)->m_fragShaderModule);
        }
        void FreeShaderProgram(IShaderProgram* shaderProgram) const noexcept override {
            if (shaderProgram != nullptr)
                free((VulkanShader*)shaderProgram);
        }
        bool CompileShader(const std::string& name, IShaderProgram* shaderProgram) const noexcept override;
        bool LinkShader(IShaderProgram* shaderProgram) const noexcept override { return true; };

        //!===============================================[SHADERS]=====================================================
    };
}

#endif //GAMEENGINE_VULKAN_H
