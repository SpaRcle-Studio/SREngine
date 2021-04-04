//
// Created by Nikita on 25.03.2021.
//

#include <Environment/Vulkan.h>
#include <ResourceManager/ResourceManager.h>
#include <FileSystem/FileSystem.h>

namespace Framework::Graphics{
    bool Vulkan::PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) {
        Helper::Debug::Graph("Vulkan::PreInit() : init vulkan application...");

        createInstance();
        setupDebugMessenger();

        return true;
    }

    bool Vulkan::MakeWindow(const char *winName, bool fullScreen, bool resizable) {
        Helper::Debug::Graph("Vulkan::MakeWindow() : creating window...");

        if (!this->m_winFormat) {
            Helper::Debug::Error("Vulkan::MakeWindow() : format isn't initialized!");
            return false;
        }

        this->m_basicWindow = new Win32Window(this->GetPipeLine());
        if (!this->m_basicWindow->Create(winName, 0, 0, m_winFormat->Width(), m_winFormat->Height(), fullScreen, resizable)) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create window!");
            return false;
        }

        createSurface();
        //pickPhysicalDevice();
        this->m_device.m_physicalDevice = VulkanTools::PickPhysicalDevice(instance, surface, m_deviceExtensions);

        createLogicalDevice();
        createSwapChain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline();
        createFramebuffers();
        createCommandPool();
        createCommandBuffers();
        createSyncObjects();

        return true;
    }

    bool Vulkan::CloseWindow() {
        Helper::Debug::Graph("Vulkan::CloseWindow() : close window...");

        return true;
    }

    bool Vulkan::Init(int swapInterval) {
        Helper::Debug::Graph("Vulkan::Init() : initializing vulkan...");

        this->m_screenSize = m_basicWindow->GetScreenResolution(0).ToGLM();

        m_basicWindow->SetCallbackResize([this](BasicWindow* win, int w, int h) {
            g_callback(WinEvents::Resize, win, &w, &h);
        });

        return true;
    }

    VkBool32 DebugVulkanCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj,
                                         size_t location, int32_t code, const char *layerPrefix, const char *msg,
                                         void *userData)
    {
        Helper::Debug::Error("DebugVulkanCallback() : " + std::string(msg));
        return VK_FALSE;
    }

    void Vulkan::SetWindowSize(unsigned int w, unsigned int h) {
        if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
            Helper::Debug::Log("Vulkan::SetWindowSize() : width = " + std::to_string(w) + "; height = "+ std::to_string(h));

        this->m_basicWindow->Resize(w, h);
    }

    void Vulkan::SetWindowPosition(int x, int y) {
        this->m_basicWindow->Move(x, y);
    }
}