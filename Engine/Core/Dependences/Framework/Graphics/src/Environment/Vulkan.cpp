//
// Created by Nikita on 25.03.2021.
//

#include <Environment/Vulkan.h>
#include <imgui_impl_vulkan.h>
#include <ImGuizmo.h>

namespace Framework::Graphics{
    #define SR_VRAM ("{" + std::to_string(Environment::Get()->GetVRAMUsage() / 1024 / 1024) + "} ")

    bool Vulkan::PreInit(
            unsigned int smooth_samples,
            const std::string& appName,
            const std::string& engineName,
            const std::string& glslc)
    {
        EvoVulkan::Tools::VkDebug::Log   = [](const std::string& msg) { Helper::Debug::VulkanLog(SR_VRAM   + msg); };
        EvoVulkan::Tools::VkDebug::Warn  = [](const std::string& msg) { Helper::Debug::Warn(SR_VRAM        + msg); };
        EvoVulkan::Tools::VkDebug::Error = [](const std::string& msg) { Helper::Debug::VulkanError(SR_VRAM + msg); };
        EvoVulkan::Tools::VkDebug::Graph = [](const std::string& msg) { Helper::Debug::Vulkan(SR_VRAM      + msg); };

        this->m_imgui = new VulkanTypes::VkImGUI();

        this->m_kernel = new SRVulkan();
        Helper::Debug::Info("Vulkan::PreInit() : pre-initializing vulkan...");

        if (m_enableValidationLayers)
            m_kernel->SetValidationLayersEnabled(true);

        this->m_viewport     = EvoVulkan::Tools::Initializers::Viewport(0, 0, 0, 0);
        this->m_scissor      = EvoVulkan::Tools::Initializers::Rect2D(0, 0, 0, 0);
        this->m_cmdBufInfo   = EvoVulkan::Tools::Initializers::CommandBufferBeginInfo();
        this->m_renderPassBI = EvoVulkan::Tools::Insert::RenderPassBeginInfo(0, 0, VK_NULL_HANDLE, VK_NULL_HANDLE, nullptr, 0);

        this->m_kernel->SetMultisampling(smooth_samples);

        if (!this->m_kernel->PreInit(
                appName,
                engineName,
                glslc,
                m_instanceExtensions,
                m_validationLayers))
        {
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
            //g_callback(WinEvents::Resize, win, &w, &h);
        });

        m_basicWindow->SetCallbackScroll([this](BasicWindow* win, double xoffset, double yoffset) {
            for (const auto &a : g_scrollEvents)
                a(xoffset, yoffset);

            g_callback(WinEvents::Scroll, win, &xoffset, &yoffset);
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

        if (m_memory) {
            m_memory->Free();
            m_memory = nullptr;
        }

        return true;
    }

    bool Vulkan::Init(int swapInterval) {
        Helper::Debug::Graph("Vulkan::Init() : initializing vulkan...");

        auto window = m_basicWindow;

        auto createSurf = [window](const VkInstance& instance) -> VkSurfaceKHR {
#ifdef WIN32 // TODO: use VK_USE_PLATFORM_WIN32_KHR
            if (window->GetType() == BasicWindow::Type::Win32) {
                VkWin32SurfaceCreateInfoKHR surfaceInfo = {};
                surfaceInfo.sType     = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
                surfaceInfo.pNext     = nullptr;
                surfaceInfo.flags     = 0;
                surfaceInfo.hinstance = dynamic_cast<Win32Window *>(window)->GetHINSTANCE();
                surfaceInfo.hwnd      = dynamic_cast<Win32Window *>(window)->GetHWND();

                VkSurfaceKHR surface = VK_NULL_HANDLE;
                VkResult result = vkCreateWin32SurfaceKHR(instance, &surfaceInfo, nullptr, &surface);
                if (result != VK_SUCCESS)
                    return VK_NULL_HANDLE;
                else
                    return surface;
            }
            else {
                Helper::Debug::Error("Vulkan::Init() : window is not support this architecture!");
                return VK_NULL_HANDLE;
            }
#endif
        };

        if (!m_kernel->Init(createSurf, m_deviceExtensions, true, swapInterval > 0)) {
            Helper::Debug::Error("Vulkan::Init() : failed to initialize Evo Vulkan kernel!");
            return false;
        }

        Helper::Debug::Info("Vulkan::Init() : create vulkan memory manager...");
        this->m_memory = VulkanTools::MemoryManager::Create(this->m_kernel);
        if (!m_memory) {
            Helper::Debug::Error("Vulkan::Init() : failed to create vulkan memory manager!");
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

    bool Vulkan::CompileShader(
            const std::string &path,
            int32_t FBO,
            void **shaderData,
            const std::vector<uint64_t>& uniformSizes
            ) const
    {
        if (FBO < 0) {
            Helper::Debug::Error("Vulkan::CompileShader() : vulkan required valid FBO for shaders!");
            return false;
        }

        EvoVulkan::Types::RenderPass renderPass = {};
        if (FBO == 0)
            renderPass = m_kernel->GetRenderPass();
        else {
            auto fbo = m_memory->m_FBOs[FBO - 1];
            if (!fbo) {
                Helper::Debug::Error("Vulkan::CompileShader() : invalid FBO! SOMETHING WENT WRONG! MEMORY MAY BE CORRUPTED!");
                return false;
            }

            renderPass = fbo->GetRenderPass();
        }

        if (!renderPass.Ready()) {
            Helper::Debug::Error("Vulkan::CompileShader() : internal Evo Vulkan error! Render pass isn't ready!");
            return false;
        }

        int32_t ID = m_memory->AllocateShaderProgram(renderPass);
        if (ID < 0) {
            Helper::Debug::Error("Vulkan::CompileShader() : failed to allocate shader program ID!");
            return false;
        } else {
            int* dynamicID = new int();
            *dynamicID = ID;
            *shaderData = reinterpret_cast<void*>(dynamicID);
        }

        std::string shadersPath = Helper::ResourceManager::Instance().GetResourcesFolder() + "/Shaders/";

        std::string vertex_path = shadersPath + "Common/" + path + ".vert";
        std::string fragment_path = shadersPath + "Common/" + path + ".frag";

        {
            if (!Helper::FileSystem::FileExists(vertex_path))
                vertex_path = shadersPath + GetPipeLineName() + "/" + path + ".vert";

            if (!Helper::FileSystem::FileExists(fragment_path))
                fragment_path = shadersPath + GetPipeLineName() + "/" + path + ".frag";;
        }

        std::vector<SourceShader> modules = {};
        {
            std::string shaderName = Helper::StringUtils::GetFileNameFromFullPath(path);

            if (Helper::FileSystem::FileExists(vertex_path))
                modules.emplace_back(SourceShader(shaderName + ".vert", vertex_path, ShaderType::Vertex));

            if (Helper::FileSystem::FileExists(fragment_path))
                modules.emplace_back(SourceShader(shaderName + ".frag", fragment_path, ShaderType::Fragment));
        }

        bool errors = false;
        std::vector<std::pair<LayoutBinding, ShaderType>> bindings = Graphics::AnalyseShader(modules, &errors);
        if (errors) {
            Helper::Debug::Error("Vulkan::CompileShader() : failed to analyse shader!");
            return false;
        }

        std::vector<VkDescriptorSetLayoutBinding> descriptorLayoutBindings = {};
        {
            VkDescriptorType      type  = VK_DESCRIPTOR_TYPE_MAX_ENUM;
            VkShaderStageFlagBits stage = VK_SHADER_STAGE_ALL;

            for (uint32_t i = 0; i < bindings.size(); i++) {
                switch (bindings[i].first) {
                    case LayoutBinding::Sampler2D: type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER; break;
                    case LayoutBinding::Uniform:   type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;         break;
                    default:
                        Helper::Debug::Error("Vulkan::CompileShader() : unknown binding type!");
                        return false;
                }

                switch (bindings[i].second) {
                    case ShaderType::Vertex:   stage = VK_SHADER_STAGE_VERTEX_BIT;   break;
                    case ShaderType::Fragment: stage = VK_SHADER_STAGE_FRAGMENT_BIT; break;
                    default:
                        Helper::Debug::Error("Vulkan::CompileShader() : unknown binding stage!");
                        return false;
                }

                descriptorLayoutBindings.emplace_back(EvoVulkan::Tools::Initializers::DescriptorSetLayoutBinding(type, stage, i));
            }
        }

        std::vector<EvoVulkan::Complexes::SourceShader> vkModules;
        for (const auto& module : modules) {
            VkShaderStageFlagBits stage = VulkanTools::VkShaderShaderTypeToStage(module.m_type);
            vkModules.emplace_back(EvoVulkan::Complexes::SourceShader(module.m_name, module.m_path, stage));
        }

        if (!m_memory->m_ShaderPrograms[ID]->Load(
                Helper::ResourceManager::Instance().GetResourcesFolder() + "\\Cache\\Shaders",
                vkModules,
                descriptorLayoutBindings,
                uniformSizes
                )) {
            Helper::Debug::Error("Vulkan::CompileShader() : failed to load Evo Vulkan shader!");
            return false;
        }

        return true;
    }

    bool Vulkan::LinkShader(
            SR_SHADER_PROGRAM *shaderProgram,
            void **shaderData,
            const std::vector<SR_VERTEX_DESCRIPTION>& vertexDescriptions,
            const std::vector<std::pair<Vertices::Attribute, size_t>>& vertexAttributes,
            SRShaderCreateInfo shaderCreateInfo) const
    {
        if (!shaderData) {
            Helper::Debug::Error("Vulkan::LinkShader() : shader data is nullptr!");
            return false;
        }
        int* dynamicID = reinterpret_cast<int*>(*shaderData);
        if (!dynamicID) {
            Helper::Debug::Error("Vulkan::LinkShader() : dynamic ID is nullptr!");
            return false;
        }

        auto vkVertexDescriptions = VulkanTools::AbstractVertexDescriptionsToVk(vertexDescriptions);
        auto vkVertexAttributes   = VulkanTools::AbstractAttributesToVkAttributes(vertexAttributes);
        if (vkVertexAttributes.size() != vertexAttributes.size()) {
            Helper::Debug::Error("Vulkan::LinkShader() : vkVertexDescriptions size != vertexDescriptions size!");
            delete dynamicID;
            return false;
        }

        if (!m_memory->m_ShaderPrograms[*dynamicID]->SetVertexDescriptions(vkVertexDescriptions, vkVertexAttributes)) {
            Helper::Debug::Error("Vulkan::LinkShader() : failed to set vertex descriptions!");
            delete dynamicID;
            return false;
        }

        if (!m_memory->m_ShaderPrograms[*dynamicID]->Compile(
                VulkanTools::AbstractPolygonModeToVk(shaderCreateInfo.polygonMode),
                VulkanTools::AbstractCullModeToVk(shaderCreateInfo.cullMode),
                VulkanTools::AbstractDepthOpToVk(shaderCreateInfo.depthCompare),
                shaderCreateInfo.blendEnabled,
                shaderCreateInfo.depthWrite,
                shaderCreateInfo.depthTest,
                VulkanTools::AbstractPrimitiveTopologyToVk(shaderCreateInfo.primitiveTopology)))
        {
            Helper::Debug::Error("Vulkan::LinkShader() : failed to compile Evo Vulkan shader!");
            delete dynamicID;
            return false;
        }

        *shaderProgram = *dynamicID;

        delete dynamicID;
        return true;
    }

    bool Vulkan::CreateFrameBuffer(glm::vec2 size, int32_t &rboDepth, int32_t &FBO, std::vector<int32_t> &colorBuffers) {
        if (size.x == 0 || size.y == 0) {
            Helper::Debug::Error("Vulkan::CreateFrameBuffer() : width or height equals zero!");
            return false;
        }

        if (FBO == 0) {
            Helper::Debug::Error("Vulkan::CreateFrameBuffer() : zero frame buffer are default frame buffer!");
            return false;
        }

        if (FBO > 0) {
            if (!this->m_memory->ReAllocateFBO(FBO - 1 , size.x, size.y, colorBuffers, rboDepth)) {
                Helper::Debug::Error("Vulkan::CreateFrameBuffer() : failed to re-allocate frame buffer object!");
            }
            return true;
        }

        std::vector<VkFormat> formats = {};
        for (uint32_t i = 0; i < colorBuffers.size(); i++)
            formats.emplace_back(VK_FORMAT_R8G8B8A8_UNORM);

        FBO = m_memory->AllocateFBO(size.x, size.y, formats, colorBuffers, rboDepth) + 1;
        if (FBO <= 0) {
            Helper::Debug::Error("Vulkan::CreateFrameBuffer() : failed to allocate FBO!");
            return false;
        }

        // TODO: Depth color!

        return true;
    }

    [[nodiscard]] bool Vulkan::FreeTextures(int32_t *IDs, uint32_t count) const {
        if (!IDs) {
            Helper::Debug::Error("Vulkan::FreeTextures() : texture IDs is nullptr!");
            return false;
        }

        for (uint32_t i = 0; i < count; i++) {
            if (IDs[i] < 0) {
                Helper::Debug::Error("Vulkan::FreeTextures() : texture ID less zero!");
                return false;
            }

            if (!m_memory->FreeTexture((uint32_t)IDs[i])) {
                Helper::Debug::Error("Vulkan::FreeTextures() : failed to free texture!");
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] bool Vulkan::FreeFBO(uint32_t FBO) const {
        return this->m_memory->FreeFBO(FBO - 1);
    }

    int32_t Vulkan::CalculateTexture(
            uint8_t* data,
            TextureFormat format,
            uint32_t w,
            uint32_t h,
            TextureFilter filter,
            TextureCompression compression,
            uint8_t mipLevels,
            bool alpha // unused
    ) const {
        auto vkFormat = VulkanTools::AbstractTextureFormatToVkFormat(format, true /* alpha */);
        if (vkFormat == VK_FORMAT_MAX_ENUM) {
            Helper::Debug::Error("Vulkan::CalculateTexture() : unsupported format!");
            return -1;
        }

        if (compression != TextureCompression::None) {
            vkFormat = VulkanTools::AbstractTextureCompToVkFormat(compression, vkFormat);
            if (vkFormat == VK_FORMAT_MAX_ENUM) {
                Helper::Debug::Error("Vulkan::CalculateTexture() : unsupported format with compression!");
                return -1;
            }

            if (auto sz = MakeGoodSizes(w, h); sz != std::pair(w, h)) {
                data = ResizeToLess(w, h, sz.first, sz.second, data);
                w = sz.first;
                h = sz.second;
            }

            if (data == nullptr || w == 0 || h == 0) {
                Helper::Debug::Error("Vulkan::CalculateTexture() : failed to reconstruct image!");
                return -1;
            }

            Helper::Debug::Log("Vulkan::CalculateTexture() : compress " + std::to_string(w * h * 4 / 1024 / 1024) + "MB source image...");

            if (data = Graphics::Compress(w, h, data, compression); data == nullptr) {
                Helper::Debug::Error("Vulkan::CalculateTexture() : failed to compress image!");
                return -1;
            }
        }

        auto ID = this->m_memory->AllocateTexture(
                data, w, h, vkFormat,
                VulkanTools::AbstractTextureFilterToVkFilter(filter),
                compression, mipLevels);

        if (compression != TextureCompression::None)
            free(data); //! free compressed data. Original data isn't will free

        if (ID < 0) {
            Helper::Debug::Error("Vulkan::CalculateTexture() : failed to allocate texture!");
            return -1;
        }

        return ID;
    }

    bool Vulkan::InitGUI() {
        Helper::Debug::Graph("Vulkan::InitGUI() : initializing ImGUI library...");

        if (!m_kernel->GetDevice()) {
            Helper::Debug::Error("Vulkan::InitGUI() : device is nullptr!");
            return false;
        }

        this->m_basicWindow->InitGUI();

        if (!m_imgui->Init(m_kernel)) {
            Helper::Debug::Error("Vulkan::Init() : failed to init imgui!");
            return false;
        }

        return true;
    }

    bool Vulkan::StopGUI() {
        EVSafeFreeObject(m_imgui) else {
            Helper::Debug::Error("Vulkan::StopGUI() : failed to destroy vulkan imgui!");
            return false;
        }

        return Environment::StopGUI();
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
    }

    InternalTexture Vulkan::GetTexture(uint32_t id) const {
        auto texture = m_memory->m_textures[id];
        if (!texture)
            return {};
        return {
                .m_data   = reinterpret_cast<void*>(texture->GetImageView()),
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

    int32_t Vulkan::CalculateVBO(void *vertices, Vertices::Type type, size_t count)  {
        auto size = Vertices::GetVertexSize(type);
        if (auto id = this->m_memory->AllocateVBO(size * count, vertices); id >= 0) {
            return id;
        }
        else
            return SR_ID_INVALID;
    }

    int32_t Vulkan::CalculateIBO(void *indices, uint32_t indxSize, size_t count, int32_t VBO) {
        // ignore VBO
        if (auto id = this->m_memory->AllocateIBO(indxSize * count, indices); id >= 0) {
            return id;
        }
        else
            return SR_ID_INVALID;
    }

    //!-----------------------------------------------------------------------------------------------------------------

    bool SRVulkan::OnResize()  {
        vkQueueWaitIdle(m_device->GetGraphicsQueue());
        vkDeviceWaitIdle(*m_device);

        Environment::Get()->SetBuildState(false);

        uint32_t w = m_width;
        uint32_t h = m_height;

        Environment::Get()->g_callback(Environment::WinEvents::Resize, Environment::Get()->GetBasicWindow(), &w, &h);
        dynamic_cast<Framework::Graphics::Vulkan*>(Environment::Get())->GetVkImGUI()->ReSize(w, h);

        return true;
    }

    void SRVulkan::Render()  {
        if (this->PrepareFrame() == EvoVulkan::Core::FrameResult::OutOfDate)
            this->m_hasErrors = !this->ResizeWindow();

        for (const auto& submitInfo : m_framebuffersQueue)
            if (auto result = vkQueueSubmit(m_device->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE); result != VK_SUCCESS) {
                VK_ERROR("renderFunction() : failed to queue submit (frame buffer)! Reason: " + EvoVulkan::Tools::Convert::result_to_description(result));
                return;
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

        // Submit to queue
        if (auto result = vkQueueSubmit(m_device->GetGraphicsQueue(), 1, &m_submitInfo, VK_NULL_HANDLE); result != VK_SUCCESS) {
            VK_ERROR("renderFunction() : failed to queue submit! Reason: " + EvoVulkan::Tools::Convert::result_to_description(result));
            return;
        }

        if (this->SubmitFrame() == EvoVulkan::Core::FrameResult::OutOfDate)
            this->m_hasErrors = !this->ResizeWindow();
    }
}