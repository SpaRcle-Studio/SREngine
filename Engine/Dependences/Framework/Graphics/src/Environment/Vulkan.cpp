//
// Created by Nikita on 25.03.2021.
//

#include <Environment/Vulkan.h>
#include <ResourceManager/ResourceManager.h>
#include <FileSystem/FileSystem.h>

namespace Framework::Graphics{
    bool Vulkan::PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) {
        Helper::Debug::Graph("Vulkan::PreInit() : init vulkan application...");

        VulkanTools::VulkanStaticMemory::Alloc(
                60, // frame buffers
                20 // frame buffer groups
                );

        Helper::Debug::Graph("Vulkan::PreInit() : check vulkan validation support...");
        if (m_enableValidationLayers && !checkValidationLayerSupport()) {
            Helper::Debug::Error("Vulkan::PreInit() : validation layers requested, but not available!");
            return false;
        }

        VkApplicationInfo appInfo  = {};
        appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName   = appName.data();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName        = engineName.data();
        appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion         = VK_API_VERSION_1_2;

        auto extensions = getRequiredExtensions();

        this->m_vkInstance = VulkanTools::CreateInstance(appInfo, extensions,
                m_validationLayers, m_enableValidationLayers);

        if (m_enableValidationLayers) {
            this->m_debugMessenger = VulkanTools::SetupDebugMessenger(m_vkInstance);

            /*{
                VkDebugReportCallbackCreateInfoEXT debugReportCallbackCreateInfoExt = {};
                debugReportCallbackCreateInfoExt.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
                debugReportCallbackCreateInfoExt.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
                debugReportCallbackCreateInfoExt.pfnCallback = DebugVulkanCallback;

                auto vkCreateDebugReportCallbackEXT =
                        (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(
                                m_vkInstance, "vkCreateDebugReportCallbackEXT");

                if (vkCreateDebugReportCallbackEXT(
                        m_vkInstance,
                        &debugReportCallbackCreateInfoExt,
                        nullptr, &(this->m_validationReportCallBack)) != VK_SUCCESS) {
                    Helper::Debug::Error("VulkanTools::CreateInstance() : failed create vulkan debug report callback info!");
                    return false;
                } else
                    Helper::Debug::Graph("VulkanTools::CreateInstance() : successfully create vulkan debug report callback!");
            }*/
        }

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

        Helper::Debug::Graph("Vulkan::MakeWindow() : create vulkan surface...");
        this->m_surface = VulkanTools::CreateSurface(m_vkInstance, m_basicWindow);
        if (!m_surface.m_ready) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create surface!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::MakeWindow() : initialize vulkan device...");
        this->m_device = VulkanTools::InitDevice(
                m_vkInstance, m_surface,
                m_deviceExtensions, m_validationLayers,
                m_enableValidationLayers);
        if(!m_device.m_ready) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create logical device!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::MakeWindow() : create vulkan swapchain...");
        this->m_swapchain = VulkanTools::CreateSwapchain(m_device, m_surface, m_basicWindow);
        if(!m_swapchain.m_ready) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create swapchain!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::MakeWindow() : create vulkan render pass...");
        this->m_renderPass = VulkanTools::CreateRenderPass(m_device, m_swapchain);
        if (m_renderPass == VK_NULL_HANDLE) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create render pass!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::MakeWindow() : create vulkan synchronizations...");
        this->m_sync = VulkanTools::CreateSync(m_device, m_swapchain);
        if(!m_sync.m_ready) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create synchronizations!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::MakeWindow() : create vulkan command pool...");
        this->m_commandPool = VulkanTools::CreateCommandPool(m_device);
        if (m_commandPool == VK_NULL_HANDLE) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create command pool!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::MakeWindow() : create vulkan image views for swapchain...");
        this->m_swapchain.m_swapChainImageViews = VulkanTools::CreateImageViews(
                m_device,
                m_swapchain.m_swapChainImages,
                m_swapchain.m_swapChainImageFormat);
        createFramebuffers();

        createGraphicsPipeline();

        createCommandBuffers();

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