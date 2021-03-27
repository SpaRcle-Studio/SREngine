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

#include <Environment/VulkanTools.h>
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

        VulkanTools::Swapchain            m_swapchain                   = {};
        VulkanTools::Device               m_device                      = {};
    public:
        [[nodiscard]] SR_FORCE_INLINE std::string GetPipeLineName() const noexcept override { return "Vulkan"; }
    public:
        bool PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) override;
        bool Init(int swapInterval) override;

        bool MakeWindow(const char* winName, Types::WindowFormat* format, bool fullScreen) override;
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
        SR_FORCE_INLINE void PollEvents() const noexcept override {
            this->m_basicWindow->PollEvents();
        }
    };
}

#endif //GAMEENGINE_VULKAN_H
