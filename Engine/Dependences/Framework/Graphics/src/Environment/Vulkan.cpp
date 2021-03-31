//
// Created by Nikita on 25.03.2021.
//

#include <Environment/Vulkan.h>
#include <ResourceManager/ResourceManager.h>
#include <FileSystem/FileSystem.h>

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

    bool Vulkan::CreateSwapchain() {
        Helper::Debug::Graph("Vulkan::CreateSwapchain() : initializing swapchain...");
        this->m_swapchain = VulkanTools::InitSwapchain(m_device, m_vkSurface);
        if (!m_swapchain.m_ready) {
            Helper::Debug::Error("Vulkan::CreateSwapchain() : failed to initialize swapchain!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::CreateSwapchain() : create image views for swapchain...");
        if (!VulkanTools::CreateImageViews(m_device, &m_swapchain)) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create image views!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::CreateSwapchain() : create command pool for swapchain...");
        if (!VulkanTools::CreateCommandPool(&m_device, &m_swapchain)) {
            Helper::Debug::Error("Vulkan::CreateSwapchain() : failed to create command pool!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::CreateSwapchain() : create semaphore for swapchain ...");
        if (!VulkanTools::CreateVulkanSemaphore(m_device, &m_swapchain)) {
            Helper::Debug::Error("Vulkan::CreateSwapchain() : failed to create semaphore!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::CreateSwapchain() : initializing synchronization for swapchain...");
        if (!VulkanTools::InitSynchronizations(m_device, &m_swapchain)) {
            Helper::Debug::Error("Vulkan::CreateSwapchain() : failed to initialize synchronization!");
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

        this->m_basicWindow = new Win32Window();
        if (!this->m_basicWindow->Create(winName, 0, 0, m_winFormat->Width(), m_winFormat->Height(), fullScreen, resizable)) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create window!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::MakeWindow() : initializing window surface...");
        this->m_vkSurface = VulkanTools::InitWindowSurface(m_vkInstance, m_basicWindow);
        if (!m_vkSurface) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to initialize window surface!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::MakeWindow() : creating device...");
        this->m_device = VulkanTools::InitDevice(
                this->m_vkInstance, this->m_vkSurface,
                { VK_KHR_SWAPCHAIN_EXTENSION_NAME }, //VK_KHR_SURFACE_EXTENSION_NAME
                { "VK_LAYER_KHRONOS_validation" }, //  VK_LAYER_LUNARG_standard_validation
                false);
        if (!m_device.IsReady()) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to initialize device!");
            Helper::Debug::Error("Vulkan::MakeWindow() : you need install Vulkan drivers on your PC!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::MakeWindow() : create create swapchain...");
        if (!CreateSwapchain()) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create swapchain!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::MakeWindow() : create depth stencil image...");
        this->m_depthStencil = CreateDepthStencilImage(m_device,
                Helper::Math::Vector2(m_basicWindow->GetWidth(), m_basicWindow->GetHeight()));
        if (!m_depthStencil.IsReady()) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create depth stencil image!");
            return false;
        }

        /*!Helper::Debug::Graph("Vulkan::MakeWindow() : initialize render pass...");
        this->m_vkRenderPass = VulkanTools::InitRenderPass(m_device, m_swapchain, m_depthStencil);
        if (m_vkRenderPass == VK_NULL_HANDLE) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to init render pass!");
            return false;
        }

        Helper::Debug::Graph("Vulkan::MakeWindow() : creating frame buffers...");
        this->m_vkFrameBuffers.resize(m_swapchain.m_swapchainImages.size());
        for (unsigned __int32 i = 0; i < m_swapchain.m_swapchainImages.size(); ++i) {
            m_vkFrameBuffers[i] = VulkanTools::CreateFrameBuffer(
                    m_vkRenderPass,
                    m_device,
                    { m_depthStencil.m_depthStencilImageView, m_swapchain.m_swapchainImageViews[i] },
                    Helper::Math::Vector2(m_basicWindow->GetWidth(), m_basicWindow->GetHeight()));

            if (m_vkFrameBuffers[i] == VK_NULL_HANDLE) {
                Helper::Debug::Error("Vulkan::MakeWindow() : failed to create frame buffer!");
                return false;
            }
        }*/

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

        //!=============================================================================================================

        //VulkanTools::DeInitSynchronizations(m_device, &m_swapchainImageAvailable);
        //Helper::Debug::Graph("Vulkan::CloseWindow() : vulkan synchronization successfully destroyed!");

        Helper::Debug::Graph("Vulkan::CloseWindow() : destroying vulkan swapchain...");
        VulkanTools::DeInitSwapchain(this->m_device, &this->m_swapchain);

        Helper::Debug::Graph("Vulkan::CloseWindow() : destroying vulkan device...!");
        VulkanTools::DeInitDevice(&this->m_device);

        if (m_vkSurface == VK_NULL_HANDLE)
            return false;
        else {
            Helper::Debug::Graph("Vulkan::CloseWindow() : destroying vulkan surface...");
            VulkanTools::DeInitWindowSurface(m_vkInstance, &m_vkSurface);
        }

        if (m_vkInstance == VK_NULL_HANDLE)
            return false;
        else {
            Helper::Debug::Graph("Vulkan::CloseWindow() : destroying vulkan instance...!");

            vkDestroyInstance(m_vkInstance, nullptr);
            m_vkInstance = VK_NULL_HANDLE;
        }

        return true;
    }

    bool Vulkan::Init(int swapInterval) {
        Helper::Debug::Graph("Vulkan::Init() : initializing vulkan...");

        if (m_renderCompleteSemaphore == VK_NULL_HANDLE) { // TODO
            VkSemaphoreCreateInfo semaphoreCreateInfo = {};
            semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
            vkCreateSemaphore(m_device.m_logicalDevice, &semaphoreCreateInfo, nullptr, &m_renderCompleteSemaphore);
            this->m_waitSemaphores.push_back(m_renderCompleteSemaphore);
        }

        Helper::Debug::Graph("Vulkan::Init() : init array for vertex buffers...");
        {
            g_VertexBuffers       = (VkBuffer*)malloc(sizeof(VkBuffer)             * g_maxCountVBOs);
            g_VertexBuffersMemory = (VkDeviceMemory*)malloc(sizeof(VkDeviceMemory) * g_maxCountVBOs);

            for (unsigned __int32 i = 0; i < g_maxCountVBOs; i++) {
                g_VertexBuffers[i]       = VK_NULL_HANDLE;
                g_VertexBuffersMemory[i] = VK_NULL_HANDLE;
            }
        }

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


    bool Vulkan::CompileShader(const std::string &name, IShaderProgram *shaderProgram) const noexcept {
        if (!shaderProgram)
            return false;

        std::string vertex_path   = Helper::ResourceManager::GetResourcesFolder() + "\\Shaders\\" + GetPipeLineName() + "\\" + name + "_vertex.glsl";
        std::string fragment_path = Helper::ResourceManager::GetResourcesFolder() + "\\Shaders\\" + GetPipeLineName() + "\\" + name + "_fragment.glsl";;

        std::string vertCode = Helper::FileSystem::ReadAllText(vertex_path);
        std::string fragCode = Helper::FileSystem::ReadAllText(fragment_path);

        if (vertCode.empty() || fragCode.empty()) {
            Helper::Debug::Error("Vulkan::CompileShader() : failed to read shader code!");
            return false;
        }

        auto* vkShader = reinterpret_cast<VulkanShader*>(shaderProgram);

        vkShader->m_vertShaderModule = VulkanTools::CreateShaderModule(m_device, vertCode);
        vkShader->m_fragShaderModule = VulkanTools::CreateShaderModule(m_device, fragCode);

        if (!vkShader->IsReady()) {
            Helper::Debug::Error("Vulkan::CompileShader() : failed to compile \""+name + "\" shader!");
            return false;
        }

        VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
        vertShaderStageInfo.sType   = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage   = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module  = vkShader->m_vertShaderModule;
        vertShaderStageInfo.pName   = "main";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
        fragShaderStageInfo.sType   = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage   = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module  = vkShader->m_fragShaderModule;
        fragShaderStageInfo.pName   = "main";

        vkShader->m_shaderStages = (VkPipelineShaderStageCreateInfo*)malloc(sizeof(VkPipelineShaderStageCreateInfo) * 2);
        {
            vkShader->m_shaderStages[0] = vertShaderStageInfo;
            vkShader->m_shaderStages[1] = fragShaderStageInfo;
        }

        return true;
    }

    void Vulkan::SetWindowSize(unsigned int w, unsigned int h) {
        if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
            Helper::Debug::Log("Vulkan::SetWindowSize() : width = " + std::to_string(w) + "; height = "+ std::to_string(h));

        this->m_basicWindow->Resize(w, h);
    }

    bool Vulkan::ReCreateAfterResize() {
        auto size = Helper::Math::Vector2(m_basicWindow->GetWidth(), m_basicWindow->GetHeight());

        Helper::Debug::Log("Vulkan::ReCreateAfterResize() : new window size = " + size.ToString());

        if (m_depthStencil.IsReady()) {
            VulkanTools::DestroyDepthStencilImage(m_device, &m_depthStencil);
            this->m_depthStencil = VulkanTools::CreateDepthStencilImage(m_device, size);

            if (!m_depthStencil.IsReady()) {
                Helper::Debug::Error("Vulkan::ReCreateAfterResize() : failed to re-create depth stencil image!");
                return false;
            }
        }

        if (m_swapchain.IsReady()) {
            VulkanTools::DeInitSwapchain(m_device, &m_swapchain);
            if (!CreateSwapchain())
                return false;
        }

        return true;
    }

    void Vulkan::SetWindowPosition(int x, int y) {
        this->m_basicWindow->Move(x, y);
    }
}