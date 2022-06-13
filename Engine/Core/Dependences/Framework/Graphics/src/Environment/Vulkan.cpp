//
// Created by Nikita on 25.03.2021.
//

#include <Environment/Vulkan.h>
#include <GUI.h>
#include <Utils/Features.h>

#ifdef SR_WIN32
    #include <vulkan/vulkan_win32.h>
#endif

namespace Framework::Graphics {
    const std::vector<const char *> Vulkan::m_validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<const char *> Vulkan::m_instanceExtensions = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
            VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME,
#ifdef SR_WIN32
            VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif
#ifndef SR_RELEASE
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif
    };

    const std::vector<const char *> Vulkan::m_deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            //VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME
    };

#define SR_VRAM ("{" + std::to_string(Environment::Get()->GetVRAMUsage() / 1024 / 1024) + "} ")

    bool Vulkan::PreInit(
            unsigned int smooth_samples,
            const std::string &appName,
            const std::string &engineName,
            const std::string &glslc) {
        EvoVulkan::Tools::VkDebug::Instance().LogCallback = [](const std::string &msg) { Helper::Debug::VulkanLog(SR_VRAM + msg); };
        EvoVulkan::Tools::VkDebug::Instance().WarnCallback = [](const std::string &msg) { SR_WARN(SR_VRAM + msg); };
        EvoVulkan::Tools::VkDebug::Instance().ErrorCallback = [](const std::string &msg) { Helper::Debug::VulkanError(SR_VRAM + msg); };
        EvoVulkan::Tools::VkDebug::Instance().GraphCallback = [](const std::string &msg) { Helper::Debug::Vulkan(SR_VRAM + msg); };
        EvoVulkan::Tools::VkDebug::Instance().AssertCallback = [](const std::string &msg) {
            Helper::Debug::Assert(SR_VRAM + msg);
            return false;
        };

        m_imgui = new VulkanTypes::VkImGUI();

        m_kernel = new SRVulkan();
        Helper::Debug::Info("Vulkan::PreInit() : pre-initializing vulkan...");

        m_enableValidationLayers = SR_UTILS_NS::Features::Instance().Enabled("VulkanValidation", false);

        if (m_enableValidationLayers) {
            m_kernel->SetValidationLayersEnabled(true);
        }

        m_viewport = EvoVulkan::Tools::Initializers::Viewport(0, 0, 0, 0);
        m_scissor = EvoVulkan::Tools::Initializers::Rect2D(0, 0, 0, 0);
        m_cmdBufInfo = EvoVulkan::Tools::Initializers::CommandBufferBeginInfo();
        m_renderPassBI = EvoVulkan::Tools::Insert::RenderPassBeginInfo(0, 0, VK_NULL_HANDLE, VK_NULL_HANDLE, nullptr,
                                                                       0);

        m_kernel->SetMultisampling(smooth_samples);

        /// TOOD: вынести в конфиг
        m_kernel->SetSwapchainImagesCount(2);

        if (!m_kernel->PreInit(
                appName,
                engineName,
                glslc,
                m_instanceExtensions,
                m_validationLayers))
        {
            SR_ERROR("Vulkan::PreInit() : failed to pre-init Evo Vulkan kernel!");
            return false;
        }

        return true;
    }

    bool Vulkan::MakeWindow(const std::string &name, const SR_MATH_NS::IVector2 &size, bool fullScreen, bool resizable,
                            bool headerEnabled) {
        Helper::Debug::Graph("Vulkan::MakeWindow() : creating window...");

        m_basicWindow = new Win32Window(this->GetPipeLine());

        m_basicWindow->SetCallbackResize([this](BasicWindow *win, int w, int h) {
            m_kernel->SetSize(w, h);
        });

        m_basicWindow->SetCallbackScroll([this](BasicWindow *win, double xoffset, double yoffset) {
            for (const auto &a : g_scrollEvents)
                a(xoffset, yoffset);

            g_callback(WinEvents::Scroll, win, &xoffset, &yoffset);
        });

        m_basicWindow->SetCallbackFocus([this](BasicWindow *win, bool focus) {
            g_callback(WinEvents::Focus, win, &focus, nullptr);
        });

        if (!m_basicWindow->Create(name.c_str(), 0, 0, size.x, size.y, fullScreen, resizable)) {
            SR_ERROR("Vulkan::MakeWindow() : failed to create window!");
            return false;
        }
        m_basicWindow->Centralize();

        m_basicWindow->SetHeaderEnabled(headerEnabled);

        m_kernel->SetSize(m_basicWindow->GetSurfaceWidth(), m_basicWindow->GetSurfaceHeight());

        return true;
    }

    bool Vulkan::CloseWindow() {
        Helper::Debug::Graph("Vulkan::CloseWindow() : close window...");

        if (m_memory) {
            m_memory->Free();
            m_memory = nullptr;
        }

        if (m_kernel) {
            if (!m_kernel->Destroy()) {
                SR_ERROR("Vulkan::CloseWindow() : failed to destroy Evo Vulkan kernel!");
                return false;
            }
        }

        return true;
    }

    bool Vulkan::Init(int swapInterval) {
        Helper::Debug::Graph("Vulkan::Init() : initializing vulkan...");

        auto window = m_basicWindow;

        auto createSurf = [window](const VkInstance &instance) -> VkSurfaceKHR {
#ifdef SR_WIN32 // TODO: use VK_USE_PLATFORM_WIN32_KHR
            if (window->GetType() == BasicWindow::Type::Win32) {
                VkWin32SurfaceCreateInfoKHR surfaceInfo = {};
                surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
                surfaceInfo.pNext = nullptr;
                surfaceInfo.flags = 0;
                surfaceInfo.hinstance = dynamic_cast<Win32Window *>(window)->GetHINSTANCE();
                surfaceInfo.hwnd = dynamic_cast<Win32Window *>(window)->GetHWND();

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
#endif
        };

        if (!m_kernel->Init(createSurf, window->GetHandle(), m_deviceExtensions, true, swapInterval > 0)) {
            SR_ERROR("Vulkan::Init() : failed to initialize Evo Vulkan kernel!");
            return false;
        }

        Helper::Debug::Info("Vulkan::Init() : create vulkan memory manager...");
        this->m_memory = VulkanTools::MemoryManager::Create(this->m_kernel);
        if (!m_memory) {
            SR_ERROR("Vulkan::Init() : failed to create vulkan memory manager!");
            return false;
        }

        return true;
    }

    void Vulkan::SetWindowSize(unsigned int w, unsigned int h) {
        if (Helper::Debug::GetLevel() >= Helper::Debug::Level::Low)
            SR_LOG("Vulkan::SetWindowSize() : width = " + std::to_string(w) + "; height = " + std::to_string(h));

        m_basicWindow->Resize(w, h);
    }

    void Vulkan::SetWindowPosition(int x, int y) {
        m_basicWindow->Move(x, y);
    }

    bool Vulkan::PostInit() {
        Helper::Debug::Graph("Vulkan::PostInit() : post-initializing vulkan...");

        if (!m_kernel->PostInit()) {
            SR_ERROR("Vulkan::PostInit() : failed to post-initialize Evo Vulkan kernel!");
            return false;
        }

        return true;
    }

    bool Vulkan::CompileShader(const std::string &path, int32_t FBO, void **shaderData, const std::vector<uint64_t> &uniformSizes) {
        if (FBO < 0) {
            SRHalt("Vulkan::CompileShader() : vulkan required valid FBO for shaders!");
            return false;
        }

        EvoVulkan::Types::RenderPass renderPass = m_kernel->GetRenderPass();
        if (FBO != 0) {
            if (auto fbo = m_memory->m_FBOs[FBO - 1]; fbo) {
                renderPass = fbo->GetRenderPass();
            } else {
                SR_ERROR("Vulkan::CompileShader() : invalid FBO! SOMETHING WENT WRONG! MEMORY MAY BE CORRUPTED!");
                return false;
            }
        }

        if (!renderPass.Ready()) {
            SR_ERROR("Vulkan::CompileShader() : internal Evo Vulkan error! Render pass isn't ready!");
            return false;
        }

        const int32_t ID = m_memory->AllocateShaderProgram(renderPass);
        if (ID < 0) {
            SR_ERROR("Vulkan::CompileShader() : failed to allocate shader program ID!");
            return false;
        }
        else {
            /// TODO: memory leak possible
            int *dynamicID = new int();
            *dynamicID = ID;
            *shaderData = reinterpret_cast<void *>(dynamicID);
        }

        const std::vector<SR_UTILS_NS::Path> checkPatches = {
                SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Shaders/SRSL"),
                SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Shaders").Concat("Common"),
                SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Shaders").Concat(GetPipeLineName())
        };

        std::vector<SourceShader> modules = {};
        {
            for (auto &&checkPath : checkPatches) {
                if (auto &&modulePath = checkPath.Concat(path).ConcatExt(".vert"); modulePath.Exists()) {
                    modules.emplace_back(SourceShader(path, modulePath.ToString(), ShaderStage::Vertex));
                    break;
                }
            }

            for (auto &&checkPath : checkPatches) {
                if (auto &&modulePath = checkPath.Concat(path).ConcatExt(".frag"); modulePath.Exists()) {
                    modules.emplace_back(SourceShader(path, modulePath.ToString(), ShaderStage::Fragment));
                    break;
                }
            }

            if (modules.empty()) {
                SRAssert2(false, "No shader modules were found!");
                return false;
            }
        }

        bool errors = false;
        auto &&uniforms = Graphics::AnalyseShader(modules, &errors);
        if (errors) {
            SR_ERROR("Vulkan::CompileShader() : failed to analyse shader!");
            return false;
        }

        std::vector<VkDescriptorSetLayoutBinding> descriptorLayoutBindings = {};
        {
            VkDescriptorType type = VK_DESCRIPTOR_TYPE_MAX_ENUM;
            VkShaderStageFlagBits stage = VK_SHADER_STAGE_ALL;

            for (auto &&uniform : uniforms) {
                switch (uniform.type) {
                    case LayoutBinding::Sampler2D:
                        type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                        break;
                    case LayoutBinding::Uniform:
                        type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                        break;
                    default:
                        SR_ERROR("Vulkan::CompileShader() : unknown binding type!");
                        return false;
                }

                switch (uniform.stage) {
                    case ShaderStage::Vertex:
                        stage = VK_SHADER_STAGE_VERTEX_BIT;
                        break;
                    case ShaderStage::Fragment:
                        stage = VK_SHADER_STAGE_FRAGMENT_BIT;
                        break;
                    default:
                        SR_ERROR("Vulkan::CompileShader() : unknown binding stage!");
                        return false;
                }

                for (auto &&descriptor : descriptorLayoutBindings) {
                    if (descriptor.binding == uniform.binding) {
                        if (descriptor.descriptorType != type) {
                            SRHalt("Vulkan::CompileShader() : descriptor types are different! \n\tBinding: " +
                                           SR_UTILS_NS::ToString(uniform.binding) + "\n\tPath: " + path);
                            return false;
                        }

                        descriptor.stageFlags |= stage;
                        goto skip;
                    }
                }

                descriptorLayoutBindings.emplace_back(EvoVulkan::Tools::Initializers::DescriptorSetLayoutBinding(
                        type, stage, uniform.binding
                ));

                skip:
                SR_NOOP;
            }
        }

        std::vector<EvoVulkan::Complexes::SourceShader> vkModules;
        for (const auto &module : modules) {
            VkShaderStageFlagBits stage = VulkanTools::VkShaderShaderTypeToStage(module.m_stage);
            vkModules.emplace_back(EvoVulkan::Complexes::SourceShader(module.m_name, module.m_path, stage));
        }

        if (!m_memory->m_ShaderPrograms[ID]->Load(
                Helper::ResourceManager::Instance().GetResPath().Concat("/Cache/Shaders"),
                vkModules,
                descriptorLayoutBindings,
                uniformSizes
        )) {
            DeleteShader(ID);
            SR_ERROR("Vulkan::CompileShader() : failed to load Evo Vulkan shader!");
            return false;
        }

        return true;
    }

    bool Vulkan::LinkShader(
            SR_SHADER_PROGRAM *shaderProgram,
            void **shaderData,
            const std::vector<SR_VERTEX_DESCRIPTION> &vertexDescriptions,
            const std::vector<std::pair<Vertices::Attribute, size_t>> &vertexAttributes,
            SRShaderCreateInfo shaderCreateInfo) const {
        if (!shaderData) {
            SR_ERROR("Vulkan::LinkShader() : shader data is nullptr!");
            return false;
        }
        int *dynamicID = reinterpret_cast<int *>(*shaderData);
        if (!dynamicID) {
            SR_ERROR("Vulkan::LinkShader() : dynamic ID is nullptr!");
            return false;
        }

        auto &&vkVertexDescriptions = VulkanTools::AbstractVertexDescriptionsToVk(vertexDescriptions);
        auto &&vkVertexAttributes = VulkanTools::AbstractAttributesToVkAttributes(vertexAttributes);
        if (vkVertexAttributes.size() != vertexAttributes.size()) {
            SR_ERROR("Vulkan::LinkShader() : vkVertexDescriptions size != vertexDescriptions size!");
            delete dynamicID;
            return false;
        }

        if (!m_memory->m_ShaderPrograms[*dynamicID]->SetVertexDescriptions(vkVertexDescriptions, vkVertexAttributes)) {
            SR_ERROR("Vulkan::LinkShader() : failed to set vertex descriptions!");
            delete dynamicID;
            return false;
        }

        /** Так как геометрия грузится отзеркаленная по оси X, то она выворачивается наизнанку,
         * соответственно, нужно изменить отсечения полигонов на обратный */
        if (shaderCreateInfo.cullMode == CullMode::Back)
            shaderCreateInfo.cullMode = CullMode::Front;
        else if (shaderCreateInfo.cullMode == CullMode::Front)
            shaderCreateInfo.cullMode = CullMode::Back;

        if (!shaderCreateInfo.Validate()) {
            SR_ERROR("Vulkan::LinkShader() : failed to validate shader create info! Create info:"
                     "\n\tPolygon mode: " + EnumPolygonModeToString(shaderCreateInfo.polygonMode) +
                     "\n\tCull mode: " + EnumCullModeToString(shaderCreateInfo.cullMode) +
                     "\n\tDepth compare: " + EnumDepthCompareToString(shaderCreateInfo.depthCompare) +
                     "\n\tPrimitive topology: " + EnumPrimitiveTopologyToString(shaderCreateInfo.primitiveTopology)
            );

            return false;
        }

        if (!m_memory->m_ShaderPrograms[*dynamicID]->Compile(
                VulkanTools::AbstractPolygonModeToVk(shaderCreateInfo.polygonMode),
                VulkanTools::AbstractCullModeToVk(shaderCreateInfo.cullMode),
                VulkanTools::AbstractDepthOpToVk(shaderCreateInfo.depthCompare),
                shaderCreateInfo.blendEnabled,
                shaderCreateInfo.depthWrite,
                shaderCreateInfo.depthTest,
                VulkanTools::AbstractPrimitiveTopologyToVk(shaderCreateInfo.primitiveTopology))) {
            SR_ERROR("Vulkan::LinkShader() : failed to compile Evo Vulkan shader!");
            delete dynamicID;
            return false;
        }

        *shaderProgram = *dynamicID;

        delete dynamicID;
        return true;
    }

    bool Vulkan::CreateFrameBuffer(glm::vec2 size, int32_t &rboDepth, int32_t &FBO, std::vector<int32_t> &colorBuffers) {
        if (size.x == 0 || size.y == 0) {
            SR_ERROR("Vulkan::CreateFrameBuffer() : width or height equals zero!");
            return false;
        }

        if (FBO == 0) {
            SR_ERROR("Vulkan::CreateFrameBuffer() : zero frame buffer are default frame buffer!");
            return false;
        }

        if (FBO > 0) {
            if (!m_memory->ReAllocateFBO(FBO - 1, size.x, size.y, colorBuffers, rboDepth)) {
                SR_ERROR("Vulkan::CreateFrameBuffer() : failed to re-allocate frame buffer object!");
            }
            return true;
        }

        std::vector<VkFormat> formats = {};
        for (uint32_t i = 0; i < colorBuffers.size(); i++)
            formats.emplace_back(VK_FORMAT_R8G8B8A8_UNORM);

        FBO = m_memory->AllocateFBO(size.x, size.y, formats, colorBuffers, rboDepth) + 1;
        if (FBO <= 0) {
            SR_ERROR("Vulkan::CreateFrameBuffer() : failed to allocate FBO!");
            return false;
        }

        // TODO: Depth color!

        return true;
    }

    [[nodiscard]] bool Vulkan::FreeTextures(int32_t *IDs, uint32_t count) const {
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

    [[nodiscard]] bool Vulkan::FreeFBO(uint32_t FBO) const {
        return this->m_memory->FreeFBO(FBO - 1);
    }

    int32_t Vulkan::CalculateTexture(
            uint8_t *data,
            TextureFormat format,
            uint32_t w,
            uint32_t h,
            TextureFilter filter,
            TextureCompression compression,
            uint8_t mipLevels,
            bool alpha,
            bool cpuUsage// unused
    ) const {
        auto vkFormat = VulkanTools::AbstractTextureFormatToVkFormat(format, true /* alpha */);
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

        auto ID = this->m_memory->AllocateTexture(
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
        Helper::Debug::Graph("Vulkan::InitGUI() : initializing ImGUI library...");

        if (!m_kernel->GetDevice()) {
            SR_ERROR("Vulkan::InitGUI() : device is nullptr!");
            return false;
        }

        m_basicWindow->InitGUI();

        if (!m_imgui->Init(m_kernel)) {
            SR_ERROR("Vulkan::Init() : failed to init imgui!");
            return false;
        }

        return true;
    }

    bool Vulkan::StopGUI() {
        Helper::Debug::Vulkan("Vulkan::StopGUI() : stopping gui...");

        EVSafeFreeObject(m_imgui) else {
            SR_ERROR("Vulkan::StopGUI() : failed to destroy vulkan imgui!");
            return false;
        }

        return true;
    }

    bool Vulkan::BeginDrawGUI() {
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGuizmo::BeginFrame();
        ImGuizmo::Enable(true);

        return true;
    }

    void Vulkan::EndDrawGUI() {
        ImGui::Render();

        ImGuiIO &io = ImGui::GetIO();
        (void) io;

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
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

    /*int32_t Vulkan::GetImGuiTextureDescriptorFromTexture(uint32_t textureID) const {
        auto descriptorSet = m_memory->AllocateDynamicTextureDescriptorSet(ImGui_ImplVulkan_GetDescriptorSetLayout(), textureID);
        if (descriptorSet < 0) {
            Helper::Debug::Error("Vulkan::GetImGuiTextureDescriptorFromTexture() : failed to allocate dynamic texture descriptor set!");
            return -1;
        }
        else
            return descriptorSet;
    }

    void *Vulkan::GetDescriptorSet(uint32_t id) const { return reinterpret_cast<void*>(m_memory->m_descriptorSets[id].m_self); }

    void *Vulkan::GetDescriptorSetFromDTDSet(uint32_t id) const {
        return reinterpret_cast<void*>(m_memory->GetDynamicTextureDescriptorSet(id));
    }*/

    int32_t Vulkan::CalculateVBO(void *vertices, Vertices::Type type, size_t count) {
        const auto size = Vertices::GetVertexSize(type);
        if (auto id = m_memory->AllocateVBO(size * count, vertices); id >= 0) {
            return id;
        } else
            return SR_ID_INVALID;
    }

    int32_t Vulkan::CalculateIBO(void *indices, uint32_t indxSize, size_t count, int32_t VBO) {
        // ignore VBO
        if (auto id = m_memory->AllocateIBO(indxSize * count, indices); id >= 0) {
            return id;
        } else
            return SR_ID_INVALID;
    }

    Helper::Math::IVector2 Vulkan::GetScreenSize() const {
        return m_basicWindow->GetScreenResolution();
    }

    uint64_t Vulkan::GetVRAMUsage() {
        return m_kernel->GetAllocator() ? m_kernel->GetAllocator()->GetGPUMemoryUsage() : 0;
    }

    void Vulkan::SetViewport(int32_t width, int32_t height) {
        if (width > 0 && height > 0) {
            m_viewport = EvoVulkan::Tools::Initializers::Viewport(
                    static_cast<float_t>(width),
                    static_cast<float_t>(height),
                    0.f, 1.f
            );
        }
        else {
            if (m_currentFBOid == 0) {
                m_viewport = m_kernel->GetViewport();
            }
            else if (m_currentFramebuffer) {
                m_viewport = m_currentFramebuffer->GetViewport();
            }
        }

        vkCmdSetViewport(m_currentCmd, 0, 1, &m_viewport);
    }

    void Vulkan::SetScissor(int32_t width, int32_t height) {
        if (width > 0 && height > 0) {
            m_scissor = EvoVulkan::Tools::Initializers::Rect2D(width, height, 0, 0);
        }
        else {
            if (m_currentFBOid == 0) {
                m_scissor = m_kernel->GetScissor();
            }
            else if (m_currentFramebuffer) {
                m_scissor = m_currentFramebuffer->GetScissor();
            }
        }

        vkCmdSetScissor(m_currentCmd, 0, 1, &m_scissor);
    }

    glm::vec2 Vulkan::GetWindowSize() const {
        if (!m_basicWindow) {
            SRHalt("Vulkan::GetWindowSize() : Basic window is nullptr!");
            return glm::vec2(0, 0);
        }

        return {
            m_basicWindow->GetWidth(),
            m_basicWindow->GetHeight()
        };
    }

    //!-----------------------------------------------------------------------------------------------------------------

    bool SRVulkan::OnResize()  {
        vkQueueWaitIdle(m_device->GetGraphicsQueue());
        vkDeviceWaitIdle(*m_device);

        Environment::Get()->SetBuildState(false);

        uint32_t w = m_width;
        uint32_t h = m_height;

        Environment::Get()->g_callback(Environment::WinEvents::Resize, Environment::Get()->GetBasicWindow(), &w, &h);

        if (m_GUIEnabled) {
            dynamic_cast<Framework::Graphics::Vulkan *>(Environment::Get())->GetVkImGUI()->ReSize(w, h);
        }

        return true;
    }

    EvoVulkan::Core::RenderResult SRVulkan::Render()  {
        if (PrepareFrame() == EvoVulkan::Core::FrameResult::OutOfDate) {
            VK_LOG("SRVulkan::Render() : out of date...");
            m_hasErrors |= !ResizeWindow();

            if (m_hasErrors) {
                return EvoVulkan::Core::RenderResult::Fatal;
            }

            VK_LOG("SRVulkan::Render() : window are successfully resized!");

            return EvoVulkan::Core::RenderResult::Success;
        }

        for (const auto& submitInfo : m_framebuffersQueue)
            if (auto result = vkQueueSubmit(m_device->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE); result != VK_SUCCESS) {
                VK_ERROR("renderFunction() : failed to queue submit (frame buffer)! Reason: " + EvoVulkan::Tools::Convert::result_to_description(result));
                return EvoVulkan::Core::RenderResult::Error;
            }

        m_submitCmdBuffs[0] = m_drawCmdBuffs[m_currentBuffer];
        if (m_GUIEnabled) {
            m_submitCmdBuffs[1] =
                    dynamic_cast<Framework::Graphics::Vulkan*>(Environment::Get())->GetVkImGUI()->Render(m_currentBuffer);
            m_submitInfo.commandBufferCount = 2;
        } else
            m_submitInfo.commandBufferCount = 1;

        m_submitInfo.waitSemaphoreCount = 1;
        if (m_waitSemaphore)
            m_submitInfo.pWaitSemaphores = &m_waitSemaphore;
        else
            m_submitInfo.pWaitSemaphores = &m_syncs.m_presentComplete;

        m_submitInfo.pCommandBuffers = m_submitCmdBuffs;
        m_submitInfo.pSignalSemaphores = &m_syncs.m_renderComplete;

        /// Submit to queue
        if (auto result = vkQueueSubmit(m_device->GetGraphicsQueue(), 1, &m_submitInfo, VK_NULL_HANDLE); result != VK_SUCCESS) {
            VK_ERROR("renderFunction() : failed to queue submit! Reason: " + EvoVulkan::Tools::Convert::result_to_description(result));

            if (result == VK_ERROR_DEVICE_LOST) {
                Debug::Terminate();
            }

            return EvoVulkan::Core::RenderResult::Error;
        }

        switch (this->SubmitFrame()) {
            case EvoVulkan::Core::FrameResult::Success:
                return EvoVulkan::Core::RenderResult::Success;
            case EvoVulkan::Core::FrameResult::Error:
                return EvoVulkan::Core::RenderResult::Error;
            case EvoVulkan::Core::FrameResult::OutOfDate: {
                this->m_hasErrors |= !this->ResizeWindow();
                if (m_hasErrors)
                    return EvoVulkan::Core::RenderResult::Fatal;
                else
                    return EvoVulkan::Core::RenderResult::Success;
            }
            case EvoVulkan::Core::FrameResult::DeviceLost:
                SR_UTILS_NS::Debug::Terminate();
            default: {
                SRAssertOnce(false);
                return EvoVulkan::Core::RenderResult::Fatal;
            }
        }
    }
}