//
// Created by Nikita on 25.03.2021.
//

#include <Environment/Vulkan.h>
#include <ResourceManager/ResourceManager.h>
#include <FileSystem/FileSystem.h>

namespace Framework::Graphics{
    bool Vulkan::PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) {
        this->m_kernel = new SRVulkan();
        Helper::Debug::Info("Vulkan::PreInit() : pre-initializing vulkan...");

        if (m_enableValidationLayers)
            m_kernel->SetValidationLayersEnabled(true);

        EvoVulkan::Tools::VkDebug::Log   = [](const std::string& msg) { Helper::Debug::VulkanLog(msg); };
        EvoVulkan::Tools::VkDebug::Warn  = [](const std::string& msg) { Helper::Debug::Warn(msg);      };
        EvoVulkan::Tools::VkDebug::Error = [](const std::string& msg) { Helper::Debug::Error(msg);     };
        EvoVulkan::Tools::VkDebug::Graph = [](const std::string& msg) { Helper::Debug::Vulkan(msg);    };

        if (!this->m_kernel->PreInit(appName, engineName, m_instanceExtensions, m_validationLayers)) {
            Helper::Debug::Error("Vulkan::PreInit() : failed to pre-init Evo Vulkan kernel!");
            return false;
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

        m_basicWindow->SetCallbackResize([this](BasicWindow* win, int w, int h) {
            m_kernel->SetSize(w, h);
            g_callback(WinEvents::Resize, win, &w, &h);
        });

        if (!this->m_basicWindow->Create(winName, 0, 0, m_winFormat->Width(), m_winFormat->Height(), fullScreen, resizable)) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create window!");
            return false;
        }

        this->m_kernel->SetSize(m_basicWindow->GetRealWidth(), m_basicWindow->GetRealHeight());

        return true;
    }

    bool Vulkan::CloseWindow() {
        Helper::Debug::Graph("Vulkan::CloseWindow() : close window...");

        if (m_kernel)
            if (!this->m_kernel->Destroy()) {
                Helper::Debug::Error("Vulkan::CloseWindow() : failed to destroy Evo Vulkan kernel!");
                return false;
            }

        return true;
    }

    bool Vulkan::Init(int swapInterval) {
        Helper::Debug::Graph("Vulkan::Init() : initializing vulkan...");

        auto window = m_basicWindow;

        auto createSurf = [window](const VkInstance& instance) -> VkSurfaceKHR {
//#ifdef VK_USE_PLATFORM_WIN32_KHR
            //if (window->GetType() == BasicWindow::Type::Win32) {
                VkWin32SurfaceCreateInfoKHR surfaceInfo = {};
                surfaceInfo.sType     = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
                surfaceInfo.pNext     = NULL;
                surfaceInfo.flags     = 0;
                surfaceInfo.hinstance = dynamic_cast<Win32Window *>(window)->GetHINSTANCE();
                surfaceInfo.hwnd      = dynamic_cast<Win32Window *>(window)->GetHWND();

                VkSurfaceKHR surface = VK_NULL_HANDLE;
                VkResult result = vkCreateWin32SurfaceKHR(instance, &surfaceInfo, NULL, &surface);
                if (result != VK_SUCCESS)
                    return VK_NULL_HANDLE;
                else
                    return surface;
            //}
           // else {
            //    Helper::Debug::Error("Vulkan::Init() : window is not support this architecture!");
            //    return VK_NULL_HANDLE;
            //}
//#endif
        };

        if (!m_kernel->Init(createSurf, m_deviceExtensions, true, swapInterval > 0)) {
            Helper::Debug::Error("Vulkan::Init() : failed to initialize Evo Vulkan kernel!");
            return false;
        }

        this->m_screenSize = m_basicWindow->GetScreenResolution(0).ToGLM();

        return true;
    }

    void Vulkan::SetWindowSize(unsigned int w, unsigned int h) {
        if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
            Helper::Debug::Log("Vulkan::SetWindowSize() : width = " + std::to_string(w) + "; height = "+ std::to_string(h));

        this->m_basicWindow->Resize(w, h);
    }

    void Vulkan::SetWindowPosition(int x, int y) {
        this->m_basicWindow->Move(x, y);
    }

    bool Vulkan::PostInit() {
        Helper::Debug::Graph("Vulkan::PostInit() : post-initializing vulkan...");

        if (!m_kernel->PostInit()) {
            Helper::Debug::Error("Vulkan::PostInit() : failed to post-initialize Evo Vulkan kernel!");
            return false;
        }

        return true;
    }
}