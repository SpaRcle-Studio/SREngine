//
// Created by Nikita on 25.03.2021.
//

#include <Environment/Vulkan.h>

namespace Framework::Graphics{
    bool Vulkan::PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) {
        Helper::Debug::Graph("Vulkan::PreInit() : init vulkan application...");

        VkApplicationInfo applicationInfo   = {};
        applicationInfo.sType               = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pApplicationName    = appName.c_str();
        applicationInfo.pEngineName         = engineName.c_str();
        applicationInfo.applicationVersion  = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.engineVersion       = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.apiVersion          = VK_API_VERSION_1_2;

        VkInstanceCreateInfo instanceCreateInfo = {};
        instanceCreateInfo.sType                = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo     = &applicationInfo;

        bool validationQueried = false;

        if (!m_extRequired.empty()) {
            if (!VulkanTools::CheckInstanceExtensionSupported(m_extRequired)){
                Helper::Debug::Error("Vulkan::PreInit() : not supported required extensions!");
                return false;
            }

            instanceCreateInfo.enabledExtensionCount = (unsigned __int32)m_extRequired.size();
            instanceCreateInfo.ppEnabledExtensionNames = m_extRequired.data();

            validationQueried = true;
            Helper::Debug::Graph("Vulkan::PreInit() : vulkan validation enabled.");
        }

        if (vkCreateInstance(&instanceCreateInfo, nullptr, &(m_vkInstance)) != VK_SUCCESS) {
            Helper::Debug::Error("Vulkan::PreInit() : failed create vulkan instance!");
            return false;
        } else
            Helper::Debug::Graph("Vulkan::PreInit() : vulkan instance successfully created!");

        if (validationQueried) {
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
                Helper::Debug::Error("Vulkan::PreInit() : failed create vulkan debug report callback info!");
                return false;
            } else
                Helper::Debug::Graph("Vulkan::PreInit() : successfully create vulkan debug report callback!");
        }

        return true;
    }

    bool Vulkan::MakeWindow(const char *winName, Types::WindowFormat *format, bool fullScreen) {
        Helper::Debug::Graph("Vulkan::MakeWindow() : creating window..");

        this->m_winFormat = format;

        this->m_basicWindow = new Win32Window();
        if (!this->m_basicWindow->Create(winName, 0, 0, format->Width(), format->Height())) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed create window!");
            return false;
        }

        return true;
    }

    bool Vulkan::CloseWindow() {
        Helper::Debug::Graph("Vulkan::CloseWindow() : close window...");

        if (m_validationReportCallBack == VK_NULL_HANDLE)
            return false;
        else {
            auto vkDestroyDebugReportCallbackEXT =
                    (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(
                            m_vkInstance, "vkDestroyDebugReportCallbackEXT");

            vkDestroyDebugReportCallbackEXT(
                    m_vkInstance,
                    this->m_validationReportCallBack,
                    nullptr);

            this->m_validationReportCallBack = VK_NULL_HANDLE;
            Helper::Debug::Graph("Vulkan::CloseWindow() : vulkan validation report callback successfully destroyed!");
        }

        if (m_vkInstance == VK_NULL_HANDLE)
            return false;
        else {
            vkDestroyInstance(m_vkInstance, nullptr);
            m_vkInstance = VK_NULL_HANDLE;

            Helper::Debug::Graph("Vulkan::CloseWindow() : vulkan instance successfully destroyed!");
        }

        return true;
    }

    bool Vulkan::Init(int swapInterval) {
        Helper::Debug::Graph("Vulkan::Init() : initializing vulkan...");

        /*this->m_screenSize = { this->m_vidMode->width, this->m_vidMode->height };
        glfwSwapInterval(swapInterval);

        glfwSetWindowFocusCallback(m_window, [](GLFWwindow* win, int focus) {
            g_callback(WinEvents::Focus, win, &focus, nullptr);
        });

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* win, int w, int h) {
            g_callback(WinEvents::Resize, win, &w, &h);
        });

        glfwSetWindowCloseCallback(m_window, (GLFWwindowclosefun)[](GLFWwindow* win) {
            g_callback(WinEvents::Close, win, nullptr, nullptr);
        });

        glfwSetWindowPosCallback(m_window, [](GLFWwindow* win, int x, int y){
            g_callback(WinEvents::Move, win, &x, &y);
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* win, double xoffset, double yoffset){
            for (const auto& a : g_scrollEvents)
                a(xoffset, yoffset);

            g_callback(WinEvents::Scroll, win, &xoffset, &yoffset);
        });*/

        return true;
    }

    VkBool32 DebugVulkanCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj,
                                         size_t location, int32_t code, const char *layerPrefix, const char *msg,
                                         void *userData)
    {
        return 0;
    }
}