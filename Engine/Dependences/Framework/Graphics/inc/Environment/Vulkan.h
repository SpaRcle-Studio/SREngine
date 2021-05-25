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

#include <EvoVulkan/VulkanKernel.h>

namespace Framework::Graphics {
    class SRVulkan : public EvoVulkan::Core::VulkanKernel {
    public:
        bool OnResize() override {
            return true;
        }

        bool BuildCmdBuffers() override {
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
        EvoVulkan::Core::VulkanKernel* m_kernel = nullptr;
    private:
        const std::vector<const char*> m_validationLayers = {
                "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> m_instanceExtensions = {
                VK_KHR_SURFACE_EXTENSION_NAME,
                VK_KHR_WIN32_SURFACE_EXTENSION_NAME
        };

        const std::vector<const char*> m_deviceExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

#ifdef NDEBUG
        const bool m_enableValidationLayers = false;
#else
        const bool m_enableValidationLayers = true;
#endif
    public:
        [[nodiscard]] SR_FORCE_INLINE std::string GetPipeLineName() const noexcept override { return "Vulkan"; }
        [[nodiscard]] SR_FORCE_INLINE PipeLine GetPipeLine() const noexcept override { return PipeLine::Vulkan; }
    public:
        bool PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) override;
        bool Init(int swapInterval) override;

        bool MakeWindow(const char* winName, bool fullScreen, bool resizable) override;
        bool CloseWindow() override;
        bool SetContextCurrent() override { return true; }

        [[nodiscard]] glm::vec2 GetWindowSize() const noexcept override {
            return { this->m_basicWindow->GetWidth(), this->m_basicWindow->GetHeight() };
        }

        [[nodiscard]] SR_FORCE_INLINE bool IsWindowOpen() const noexcept override {
             return m_basicWindow->IsWindowOpen();
        }

        SR_FORCE_INLINE void PollEvents() const noexcept override {
            this->m_basicWindow->PollEvents();
        }

        void SetWindowPosition(int x, int y) override;
        void SetWindowSize(unsigned int w, unsigned int h) override;
    };
}

#endif //GAMEENGINE_VULKAN_H
