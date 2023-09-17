//
// Created by Nikita on 25.03.2021.
//

#include <Utils/Common/Features.h>
#include <Utils/Platform/Platform.h>

#include <Graphics/Pipeline/Vulkan/AbstractCasts.h>
#include <Graphics/Pipeline/Vulkan.h>
#include <Graphics/Memory/MeshManager.h>
#include <Graphics/Types/Framebuffer.h>

#if defined(SR_WIN32)
    #include <vulkan/vulkan_win32.h>
    #include <Graphics/Window/Win32Window.h>
#elif defined(SR_ANDROID)
    #include <Graphics/Window/AndroidWindow.h>
    #include <vulkan/vulkan_android.h>
#endif

namespace SR_GRAPH_NS {
    const std::vector<const char *> Vulkan::m_deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            VK_EXT_LINE_RASTERIZATION_EXTENSION_NAME,
            //VK_KHR_SEPARATE_DEPTH_STENCIL_LAYOUTS_EXTENSION_NAME
            //VK_KHR_FRAGMENT_SHADING_RATE_EXTENSION_NAME,
            //VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME
    };

#define SR_VRAM ("{" + std::to_string(Environment::Get()->GetVRAMUsage() / 1024 / 1024) + "} ")

    bool Vulkan::PreInit(
            unsigned int smooth_samples,
            const std::string &appName,
            const std::string &engineName,
            const std::string &glslc)
    {
        m_requiredSampleCount = smooth_samples;

        SRAssert2(m_requiredSampleCount >= 1 && m_requiredSampleCount <= 64, "Sample count must be greater 0 and less 64!");

        //EvoVulkan::Tools::VkFunctionsHolder::Instance().LogCallback = [](const std::string &msg) { SR_VULKAN_LOG(SR_VRAM + msg); };
        //EvoVulkan::Tools::VkFunctionsHolder::Instance().WarnCallback = [](const std::string &msg) { SR_WARN(SR_VRAM + msg); };
        //EvoVulkan::Tools::VkFunctionsHolder::Instance().ErrorCallback = [](const std::string &msg) { SR_VULKAN_ERROR(SR_VRAM + msg); };
        //EvoVulkan::Tools::VkFunctionsHolder::Instance().GraphCallback = [](const std::string &msg) { SR_VULKAN_MSG(SR_VRAM + msg); };

        //EvoVulkan::Tools::VkFunctionsHolder::Instance().AssertCallback = [](const std::string &msg) {
        //    SRHalt(SR_VRAM + msg);
        //    return false;
        //};

        EvoVulkan::Tools::VkFunctionsHolder::Instance().CreateFolder = [](const std::string& path) -> bool {
            return SR_PLATFORM_NS::CreateFolder(path);
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().Delete = [](const std::string& path) -> bool {
            return SR_PLATFORM_NS::Delete(path);
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().IsExists = [](const std::string& path) -> bool {
            return SR_PLATFORM_NS::IsExists(path);
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().Copy = [](const std::string& from, const std::string& to) -> bool {
            return SR_PLATFORM_NS::Copy(from, to);
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().ReadHash = [](const std::string& path) -> uint64_t {
            return SR_UTILS_NS::FileSystem::ReadHashFromFile(SR_UTILS_NS::Path(path, true));
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().GetFileHash = [](const std::string& path) -> uint64_t {
            return SR_UTILS_NS::FileSystem::GetFileHash(SR_UTILS_NS::Path(path, true));
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().WriteHash = [](const std::string& path, uint64_t hash) -> bool {
            SR_UTILS_NS::FileSystem::WriteHashToFile(SR_UTILS_NS::Path(path, false), hash);
            return true;
        };

        m_imgui = new VulkanTypes::VkImGUI(this);

        /// m_kernel = new SRVulkan();

        SR_INFO("Vulkan::PreInit() : pre-initializing vulkan...");

    #ifdef SR_ANDROID
        m_enableValidationLayers = false;
    #else
        m_enableValidationLayers = SR_UTILS_NS::Features::Instance().Enabled("VulkanValidation", false);
    #endif

        if (m_enableValidationLayers) {
            m_kernel->SetValidationLayersEnabled(true);
        }

        m_viewport = EvoVulkan::Tools::Initializers::Viewport(1, 1, 0, 0);
        m_scissor = EvoVulkan::Tools::Initializers::Rect2D(0, 0, 0, 0);
        m_cmdBufInfo = EvoVulkan::Tools::Initializers::CommandBufferBeginInfo();
        m_renderPassBI = EvoVulkan::Tools::Insert::RenderPassBeginInfo(0, 0, VK_NULL_HANDLE, VK_NULL_HANDLE, nullptr, 0);

        m_kernel->SetMultisampling(m_requiredSampleCount);

        /// TODO: вынести в конфиг
        m_kernel->SetSwapchainImagesCount(2);

        std::vector<const char*>&& validationLayers = { };
        std::vector<const char*>&& instanceExtensions = {
                VK_KHR_SURFACE_EXTENSION_NAME,
                VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
                VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME,
                /// VK_KHR_SEPARATE_DEPTH_STENCIL_LAYOUTS_EXTENSION_NAME,
        #ifdef SR_WIN32
                VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
        #endif
        #ifdef SR_ANDROID
                VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
        #endif
        };

        if (m_enableValidationLayers) {
            instanceExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            validationLayers.emplace_back("VK_LAYER_KHRONOS_validation");
        }

        if (!m_kernel->PreInit(
                appName,
                engineName,
                glslc,
                instanceExtensions,
                validationLayers))
        {
            SR_ERROR("Vulkan::PreInit() : failed to pre-init Evo Vulkan kernel!");
            return false;
        }

    #ifdef SR_TRACY_ENABLE
        SR_UTILS_NS::TracyContextManager::Instance().VulkanDestroy = [](void* pContext) {
            TracyVkDestroy((tracy::VkCtx*)pContext);
        };
    #endif

        return true;
    }

    bool Vulkan::OnResize(const Helper::Math::UVector2 &size) {
        m_kernel->SetSize(size.x, size.y);

        return Environment::OnResize(size);
    }

    void Vulkan::DeInitialize() {
        SR_GRAPH_LOG("Vulkan::DeInitialize() : de-initialize pipeline...");

        /// SR_GRAPH_NS::Memory::MeshManager::Instance().PrintDump();

        SR_TRACY_DESTROY(SR_UTILS_NS::TracyType::Vulkan);

        if (m_memory) {
            m_memory->Free();
            m_memory = nullptr;
        }

        if (m_kernel && !m_kernel->Destroy()) {
            SR_ERROR("Vulkan::DeInitialize() : failed to destroy Evo Vulkan kernel!");
        }

        Environment::DeInitialize();
    }

    bool Vulkan::Init(const WindowPtr& window, int swapInterval) {
        SR_GRAPH_LOG("Vulkan::Init() : initializing vulkan...");

        m_window = window;

        auto createSurf = [window](const VkInstance &instance) -> VkSurfaceKHR {
    #ifdef SR_WIN32 // TODO: use VK_USE_PLATFORM_WIN32_KHR
            if (auto&& pImpl = window->GetImplementation<Win32Window>()) {
                VkWin32SurfaceCreateInfoKHR surfaceInfo = { };
                surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
                surfaceInfo.pNext = nullptr;
                surfaceInfo.flags = 0;
                surfaceInfo.hinstance = pImpl->GetHINSTANCE();
                surfaceInfo.hwnd = pImpl->GetHWND();

                VkSurfaceKHR surface = VK_NULL_HANDLE;
                VkResult result = vkCreateWin32SurfaceKHR(instance, &surfaceInfo, nullptr, &surface);
                if (result != VK_SUCCESS) {
                    return VK_NULL_HANDLE;
                }
                else
                    return surface;
            }
            else {
                SR_ERROR("Vulkan::Init() : window is not support this architecture!");
                return VK_NULL_HANDLE;
            }
    #elif defined(SR_ANDROID)
            if (auto&& pImpl = window->GetImplementation<AndroidWindow>()) {
                VkAndroidSurfaceCreateInfoKHR surfaceInfo = { };
                surfaceInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
                surfaceInfo.pNext = nullptr;
                surfaceInfo.flags = 0;
                surfaceInfo.window = pImpl->GetNativeWindow();

                VkSurfaceKHR surface = VK_NULL_HANDLE;
                VkResult result = vkCreateAndroidSurfaceKHR(instance, &surfaceInfo, nullptr, &surface);
                if (result != VK_SUCCESS) {
                    return VK_NULL_HANDLE;
                }
                else
                    return surface;
            }
            else {
                SR_ERROR("Vulkan::Init() : window is not support this architecture!");
                return VK_NULL_HANDLE;
            }
    #else
            SR_UNUSED_VARIABLE(window);
            SRHalt("Unsupported platform!");
            return VK_NULL_HANDLE;
    #endif
        };

        if (auto&& pImpl = window->GetImplementation<BasicWindowImpl>()) {
            m_kernel->SetSize(pImpl->GetSurfaceWidth(), pImpl->GetSurfaceHeight());
        }

        if (!m_kernel->Init(createSurf, window->GetHandle(), m_deviceExtensions, true, swapInterval > 0)) {
            SR_ERROR("Vulkan::Init() : failed to initialize Evo Vulkan kernel!");
            return false;
        }

        SR_INFO("Vulkan::Init() : create vulkan memory manager...");
        m_memory = VulkanTools::MemoryManager::Create(m_kernel);
        if (!m_memory) {
            SR_ERROR("Vulkan::Init() : failed to create vulkan memory manager!");
            return false;
        }

        m_supportedSampleCount = m_kernel->GetDevice()->GetMSAASamplesCount();

        return true;
    }

//   void Vulkan::SetWindowSize(unsigned int w, unsigned int h) {
//       if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Low) {
//           SR_LOG("Vulkan::SetWindowSize() : width = " + std::to_string(w) + "; height = " + std::to_string(h));
//       }

//       m_basicWindow->Resize(w, h);
//   }

//   void Vulkan::SetWindowPosition(int x, int y) {
//       m_basicWindow->Move(x, y);
//   }

    bool Vulkan::PostInit() {
        SR_GRAPH_LOG("Vulkan::PostInit() : post-initializing vulkan...");

        if (!m_kernel->PostInit()) {
            SR_ERROR("Vulkan::PostInit() : failed to post-initialize Evo Vulkan kernel!");
            return false;
        }

    #ifdef SR_TRACY_ENABLE
        if (SR_UTILS_NS::Features::Instance().Enabled("Tracy", false)) {
            if (auto &&pSingleTimeCmd = m_kernel->CreateCmd()) {
                SR_GRAPH_LOG("Vulkan::PostInit() : initializing tracy...");
                SR_TRACY_VK_CREATE(*pSingleTimeCmd, m_kernel, "EvoVulkan");
                delete pSingleTimeCmd;
            }
        }
    #endif

        return true;
    }

    bool Vulkan::CreateFrameBuffer(const SR_MATH_NS::IVector2 &size, int32_t &FBO, DepthLayer *pDepth, std::vector<ColorLayer> &colors, uint8_t sampleCount, uint32_t layersCount) {
        std::vector<int32_t> colorBuffers;
        colorBuffers.reserve(colors.size());

        std::vector<VkFormat> formats;
        formats.reserve(colors.size());

        for (auto&& color : colors) {
            colorBuffers.emplace_back(color.texture);
            formats.emplace_back(VulkanTools::AbstractTextureFormatToVkFormat(color.format));
        }

        if (size.x == 0 || size.y == 0) {
            SR_ERROR("Vulkan::CreateFrameBuffer() : width or height equals zero!");
            return false;
        }

        if (FBO == 0) {
            SR_ERROR("Vulkan::CreateFrameBuffer() : zero frame buffer are default frame buffer!");
            return false;
        }

        if (FBO > 0) {
            if (!m_memory->ReAllocateFBO(FBO - 1, size.x, size.y, colorBuffers, pDepth, sampleCount, layersCount)) {
                SR_ERROR("Vulkan::CreateFrameBuffer() : failed to re-allocate frame buffer object!");
            }
            goto success;
        }

        FBO = m_memory->AllocateFBO(size.x, size.y, formats, colorBuffers, pDepth, sampleCount, layersCount) + 1;
        if (FBO <= 0) {
            FBO = SR_ID_INVALID;
            SR_ERROR("Vulkan::CreateFrameBuffer() : failed to allocate FBO!");
            return false;
        }

    success:
        for (uint32_t i = 0; i < static_cast<uint32_t>(colors.size()); ++i) {
            colors[i].texture = colorBuffers[i];
        }

        return true;
    }

    bool Vulkan::FreeTextures(int32_t *IDs, uint32_t count) const {
        if (!IDs) {
            SR_ERROR("Vulkan::FreeTextures() : texture IDs is nullptr!");
            return false;
        }

        for (uint32_t i = 0; i < count; i++) {
            if (IDs[i] < 0) {
                SR_ERROR("Vulkan::FreeTextures() : texture ID less zero!");
                return false;
            }

            if (!m_memory->FreeTexture((uint32_t) IDs[i])) {
                SR_ERROR("Vulkan::FreeTextures() : failed to free texture!");
                return false;
            }
        }

        return true;
    }

    bool Vulkan::FreeFBO(uint32_t FBO) const {
        return m_memory->FreeFBO(FBO - 1);
    }

    int32_t Vulkan::CalculateTexture(
            uint8_t *data,
            ImageFormat format,
            uint32_t w,
            uint32_t h,
            TextureFilter filter,
            TextureCompression compression,
            uint8_t mipLevels,
            bool alpha,
            bool cpuUsage// unused
    ) const {
        auto vkFormat = VulkanTools::AbstractTextureFormatToVkFormat(format);
        if (vkFormat == VK_FORMAT_MAX_ENUM) {
            SR_ERROR("Vulkan::CalculateTexture() : unsupported format!");
            return -1;
        }

        if (compression != TextureCompression::None) {
            vkFormat = VulkanTools::AbstractTextureCompToVkFormat(compression, vkFormat);
            if (vkFormat == VK_FORMAT_MAX_ENUM) {
                SR_ERROR("Vulkan::CalculateTexture() : unsupported format with compression!");
                return -1;
            }

            if (auto sz = MakeGoodSizes(w, h); sz != std::pair(w, h)) {
                data = ResizeToLess(w, h, sz.first, sz.second, data);
                w = sz.first;
                h = sz.second;
            }

            if (data == nullptr || w == 0 || h == 0) {
                SR_ERROR("Vulkan::CalculateTexture() : failed to reconstruct image!");
                return -1;
            }

            SR_LOG("Vulkan::CalculateTexture() : compress " + std::to_string(w * h * 4 / 1024 / 1024) +
                   "MB source image...");

            if (data = Graphics::Compress(w, h, data, compression); data == nullptr) {
                SR_ERROR("Vulkan::CalculateTexture() : failed to compress image!");
                return -1;
            }
        }

        auto ID = m_memory->AllocateTexture(
                data, w, h, vkFormat,
                VulkanTools::AbstractTextureFilterToVkFilter(filter),
                compression, mipLevels, cpuUsage);

        if (compression != TextureCompression::None)
            free(data); //! free compressed data. Original data isn't will free

        if (ID < 0) {
            SR_ERROR("Vulkan::CalculateTexture() : failed to allocate texture!");
            return -1;
        }

        return ID;
    }

    bool Vulkan::InitGUI() {
        SR_GRAPH_LOG("Vulkan::InitGUI() : initializing ImGUI library...");

        if (!m_kernel->GetDevice()) {
            SR_ERROR("Vulkan::InitGUI() : device is nullptr!");
            return false;
        }

        UpdateMultiSampling();

        if (!m_imgui->Init()) {
            SR_ERROR("Vulkan::Init() : failed to init imgui!");
            return false;
        }

        return true;
    }

    bool Vulkan::StopGUI() {
        SR_VULKAN_MSG("Vulkan::StopGUI() : stopping gui...");

        EVSafeFreeObject(m_imgui) else {
            SR_ERROR("Vulkan::StopGUI() : failed to destroy vulkan imgui!");
            return false;
        }

        return true;
    }

    bool Vulkan::BeginDrawGUI() {

        ImGui_ImplVulkan_NewFrame();

    #ifdef SR_WIN32
        ImGui_ImplWin32_NewFrame();
    #endif

        ImGui::NewFrame();

        ImGuizmo::BeginFrame();
        ImGuizmo::Enable(true);

        return true;
    }

    void Vulkan::EndDrawGUI() {
        if (!m_imgui) {
            return;
        }

        ImGui::Render();

        ImGuiIO &io = ImGui::GetIO();
        (void) io;

        /// Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        const bool isUndockingActive = m_imgui->IsUndockingActive();

        if (m_undocking != isUndockingActive) {
            if ((m_undocking = isUndockingActive)) {
                SR_INFO("Vulkan::EndDrawGUI() : undocking was activated!");
            }
            else {
                SR_INFO("Vulkan::EndDrawGUI() : undocking was deactivated!");
            }
        }
    }

    InternalTexture Vulkan::GetTexture(uint32_t id) const {
        auto texture = m_memory->m_textures[id];
        if (!texture)
            return {};
        return {
                .m_data   = reinterpret_cast<void *>(texture->GetImageView()),
                .m_width  = texture->GetWidth(),
                .m_height = texture->GetHeight()
        };
    }

    SR_MATH_NS::FColor Vulkan::GetPixelColor(uint64_t textureId, uint32_t x, uint32_t y) {
        if (textureId == SR_ID_INVALID || textureId >= m_memory->m_countTextures.first) {
            return SR_MATH_NS::FColor(0.f);
        }

        auto&& pTexture = m_memory->m_textures[textureId];
        if (!pTexture) {
            return SR_MATH_NS::FColor(0.f);
        }

        auto&& pixel = pTexture->GetPixel(x, y, 0);
        return SR_MATH_NS::FColor(
                static_cast<SR_MATH_NS::Unit>(pixel.r),
                static_cast<SR_MATH_NS::Unit>(pixel.g),
                static_cast<SR_MATH_NS::Unit>(pixel.b),
                static_cast<SR_MATH_NS::Unit>(pixel.a)
        );
    }

    int32_t Vulkan::CalculateVBO(void *vertices, Vertices::VertexType type, size_t count) {
        const auto size = Vertices::GetVertexSize(type);
        if (auto id = m_memory->AllocateVBO(size * count, vertices); id >= 0) {
            return id;
        } else
            return SR_ID_INVALID;
    }

    int32_t Vulkan::CalculateIBO(void *indices, uint32_t indxSize, size_t count, int32_t VBO) {
        /// ignore VBO
        if (auto id = m_memory->AllocateIBO(indxSize * count, indices); id >= 0) {
            return id;
        }
        else
            return SR_ID_INVALID;
    }

    SR_MATH_NS::IVector2 Vulkan::GetScreenSize() const {
        /// TODO: это нужно?
        //     return m_basicWindow->GetScreenResolution();
        return SR_MATH_NS::IVector2();
    }

    uint64_t Vulkan::GetVRAMUsage() {
        return m_kernel->GetAllocator() ? m_kernel->GetAllocator()->GetGPUMemoryUsage() : 0;
    }

    void Vulkan::SetViewport(int32_t width, int32_t height) {

    }

    void Vulkan::SetScissor(int32_t width, int32_t height) {

    }

    int32_t Vulkan::AllocateShaderProgram(const SRShaderCreateInfo& createInfo, int32_t FBO) {
        return 0;
    }

    void Vulkan::OnMultiSampleChanged() {

    }

    void Vulkan::PrepareFrame() {

    }

    void Vulkan::UpdateMultiSampling() {
    }

    void Vulkan::ClearBuffers(const std::vector<SR_MATH_NS::FColor> &colors, float_t depth) {

    }

    void Vulkan::ClearBuffers(float r, float g, float b, float a, float depth, uint8_t colorCount) {

    }

    uint8_t Vulkan::GetFramebufferSampleCount() const {
        if (m_currentFramebuffer) {
            return m_currentFramebuffer->GetSamplesCount();
        }

        return GetSamplesCount();
    }

    std::set<void*> Vulkan::GetFBOHandles() const {
        std::set<void*> handles;
        return handles;
    }

    void* Vulkan::GetCurrentFBOHandle() const {
        return nullptr;
    }

    void Vulkan::SetBuildState(bool isBuild) {
    }

    void Vulkan::SetCurrentFramebuffer(SR_GTYPES_NS::Framebuffer* pFrameBuffer) {

    }

    void Vulkan::PushConstants(void* pData, uint64_t size) {

    }
}