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
        if (!this->m_basicWindow->Create(winName, 0, 0, m_winFormat->Width(), m_winFormat->Height(), fullScreen, resizable)) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create window!");
            return false;
        }

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

        this->m_screenSize = m_basicWindow->GetScreenResolution(0).ToGLM();

        m_basicWindow->SetCallbackResize([this](BasicWindow* win, int w, int h) {
            g_callback(WinEvents::Resize, win, &w, &h);
        });

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
}