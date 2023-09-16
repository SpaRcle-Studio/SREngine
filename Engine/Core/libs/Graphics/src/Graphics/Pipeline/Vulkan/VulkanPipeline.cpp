//
// Created by Monika on 15.09.2023.
//

#include <Graphics/Pipeline/Vulkan/VulkanPipeline.h>
#include <Graphics/Pipeline/Vulkan/VulkanKernel.h>

#ifdef SR_USE_IMGUI
    #include <Graphics/Overlay/VulkanImGuiOverlay.h>
#endif

namespace SR_GRAPH_NS {
    std::string VulkanPipeline::GetVendor() const {
        if (m_kernel && m_kernel->GetDevice()) {
            return m_kernel->GetDevice()->GetName();
        }
        return "Invalid";
    }

    VulkanPipeline::~VulkanPipeline() {
        SR_SAFE_DELETE_PTR(m_kernel);
    }

    bool VulkanPipeline::InitOverlay() {
    #ifdef SR_USE_IMGUI
        auto&& pImGuiOverlay = m_overlays[OverlayType::ImGui];
        pImGuiOverlay = new VulkanImGuiOverlay(GetThis());
        if (!pImGuiOverlay->Init()) {
            PipelineError("VulkanPipeline::InitOverlay() : failed to initialize ImGui overlay!");
            return false;
        }
    #endif

        return Pipeline::InitOverlay();
    }

    bool VulkanPipeline::Destroy() {
        if (m_kernel) {
            m_kernel->Destroy();
        }

        return Super::Destroy();
    }

    bool VulkanPipeline::PreInit(const PipelinePreInitInfo& info) {
        if (!Pipeline::PreInit(info)) {
            PipelineError("VulkanPipeline::PreInit() : failed to pre-initialize pipeline!");
            return false;
        }

        if (!InitEvoVulkanHooks()) {
            PipelineError("VulkanPipeline::PreInit() : failed to initialize evo vulkan hooks!");
            return false;
        }

    #ifdef SR_ANDROID
        m_enableValidationLayers = false;
    #else
        m_enableValidationLayers = SR_UTILS_NS::Features::Instance().Enabled("VulkanValidation", false);
    #endif

        m_kernel = new SR_GRAPH_NS::VulkanKernel(GetThis());

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

        if (!m_kernel->PreInit(info.appName, info.engineName, info.GLSLCompilerPath.ToStringRef(),
            instanceExtensions,
            validationLayers
        )) {
            PipelineError("VulkanPipeline::PreInit() : failed to pre-init Evo Vulkan kernel!");
            return false;
        }

    #ifdef SR_TRACY_ENABLE
        SR_UTILS_NS::TracyContextManager::Instance().VulkanDestroy = [](void* pContext) {
            TracyVkDestroy((tracy::VkCtx*)pContext);
        };
    #endif

        return true;
    }

    bool VulkanPipeline::Init() {
        SR_GRAPH_LOG("VulkanPipeline::Init() : initializing vulkan...");

        auto&& createSurfaceFn = [this](const VkInstance &instance) -> VkSurfaceKHR {
        #ifdef VK_USE_PLATFORM_WIN32_KHR
            if (auto&& pImpl = m_window->GetImplementation<Win32Window>()) {
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
                PipelineError("VulkanPipeline::Init() : window is not support this architecture!");
                return VK_NULL_HANDLE;
            }
        #elif defined(SR_ANDROID)
            if (auto&& pImpl = m_window->GetImplementation<AndroidWindow>()) {
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
                PipelineError("VulkanPipeline::Init() : window is not support this architecture!");
                return VK_NULL_HANDLE;
            }
        #else
            SR_UNUSED_VARIABLE(window);
            SRHalt("Unsupported platform!");
            return VK_NULL_HANDLE;
        #endif
        };

        if (auto&& pImpl = m_window->GetImplementation<BasicWindowImpl>()) {
            m_kernel->SetSize(pImpl->GetSurfaceWidth(), pImpl->GetSurfaceHeight());
        }

        static const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            VK_EXT_LINE_RASTERIZATION_EXTENSION_NAME,
        };

        if (!m_kernel->Init(createSurfaceFn, m_window->GetHandle(), deviceExtensions, true, false /** V-Sync */)) {
            PipelineError("VulkanPipeline::Init() : failed to initialize Evo Vulkan kernel!");
            return false;
        }

        SR_INFO("VulkanPipeline::Init() : create vulkan memory manager...");
        m_memory = VulkanTools::MemoryManager::Create(m_kernel);
        if (!m_memory) {
            PipelineError("VulkanPipeline::Init() : failed to create vulkan memory manager!");
            return false;
        }

        m_supportedSampleCount = m_kernel->GetDevice()->GetMSAASamplesCount();

        return Super::Init();
    }

    uint64_t VulkanPipeline::GetUsedMemory() const {
        return m_kernel->GetAllocator() ? m_kernel->GetAllocator()->GetGPUMemoryUsage() : 0;
    }

    int32_t VulkanPipeline::AllocateUBO(uint32_t uboSize) {
        ++m_state.operations;
        ++m_state.allocations;
        m_state.allocatedMemory += uboSize;

        SRAssert2(uboSize > 0, "Incorrect UBO size!");

        if (auto&& id = m_memory->AllocateUBO(uboSize); id >= 0) {
            return id;
        }

        PipelineError("VulkanPipeline::AllocateUBO() : failed to allocate uniform buffer object!");
        return SR_ID_INVALID;
    }

    int32_t VulkanPipeline::AllocDescriptorSet(const std::vector<uint64_t>& types) {
        ++m_state.operations;
        ++m_state.allocations;

        auto&& vkTypes = VulkanTools::CastAbsDescriptorTypeToVk(types);

    #ifdef SR_DEBUG
        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Full) {
            SR_GRAPH_LOG("VulkanPipeline::AllocDescriptorSet() : allocate new descriptor set...");
        }
    #endif

        if (m_state.shaderId < 0) {
            PipelineError("VulkanPipeline::AllocDescriptorSet() : shader program do not set!");
            SRHaltOnce0();
            return SR_ID_INVALID;
        }

        if (auto&& id = m_memory->AllocateDescriptorSet(m_state.shaderId, vkTypes); id >= 0) {
            return id;
        }

        PipelineError("VulkanPipeline::AllocDescriptorSet() : failed to allocate descriptor set!");
        return SR_ID_INVALID;
    }

    void* VulkanPipeline::GetCurrentFBOHandle() const {
        void* pHandle = m_kernel->GetRenderPass(); /// Ну типо кадровый буфер

        if (m_state.pFrameBuffer) {
            if (auto&& FBO = m_state.pFrameBuffer->GetId(); FBO == SR_ID_INVALID) {
                PipelineError("Vulkan::GetCurrentFBOHandle() : invalid FBO!");
            }
            else if (auto&& framebuffer = m_memory->m_FBOs[FBO - 1]; !framebuffer) {
                PipelineError("Vulkan::GetCurrentFBOHandle() : frame buffer object don't exist!");
            }
            else {
                if (auto&& layers = framebuffer->GetLayers(); !layers.empty()) {
                    pHandle = layers.at(SR_MIN(layers.size() - 1, m_state.frameBufferLayer))->GetFramebuffer();
                }
                else {
                    PipelineError("Vulkan::GetCurrentFBOHandle() : frame buffer have not layers!");
                }
            }
        }

        return pHandle;
    }

    std::set<void*> VulkanPipeline::GetFBOHandles() const {
        std::set<void*> handles;

        if (void* pHandle = m_kernel->GetRenderPass()) {
            handles.insert(pHandle);
        }

        for (uint64_t i = 0; i < m_memory->m_countFBO.first; ++i) {
            auto&& pFBO = m_memory->m_FBOs[i];
            if (!pFBO) {
                continue;
            }

            for (auto&& layer : pFBO->GetLayers()) {
                if (auto&& pVkFrameBuffer = layer->GetFramebuffer()) {
                    handles.insert(pVkFrameBuffer);
                }
            }
        }

        return handles;
    }

    void VulkanPipeline::UseShader(uint32_t shaderProgram) {
        Pipeline::UseShader(shaderProgram);

        if (shaderProgram >= m_memory->m_countShaderPrograms.first) {
            PipelineError("Vulkan::UseShader() : index out of range!");
            return;
        }

        m_currentVkShader = m_memory->m_ShaderPrograms[shaderProgram];
        if (!m_currentVkShader) {
            PipelineError("Vulkan::UseShader() : shader is nullptr!");
            return;
        }
        m_currentLayout = m_currentVkShader->GetPipelineLayout();

        m_currentVkShader->Bind(m_currentCmd);
    }

    int32_t VulkanPipeline::AllocateShaderProgram(const SRShaderCreateInfo& createInfo, int32_t fbo) {
        ++m_state.operations;
        ++m_state.allocations;

        if (fbo < 0) {
            SRHalt("VulkanPipeline::AllocateShaderProgram() : vulkan required valid FBO for shaders!");
            return false;
        }

        if (!createInfo.Validate()) {
            PipelineError("VulkanPipeline::AllocateShaderProgram() : failed to validate shader create info! Create info:"
                 "\n\tPolygon mode: " + SR_UTILS_NS::EnumReflector::ToString(createInfo.polygonMode) +
                 "\n\tCull mode: " + SR_UTILS_NS::EnumReflector::ToString(createInfo.cullMode) +
                 "\n\tDepth compare: " + SR_UTILS_NS::EnumReflector::ToString(createInfo.depthCompare) +
                 "\n\tPrimitive topology: " + SR_UTILS_NS::EnumReflector::ToString(createInfo.primitiveTopology)
            );
            return false;
        }

        EvoVulkan::Types::RenderPass renderPass = m_kernel->GetRenderPass();
        if (fbo != 0) {
            if (auto&& pFBO = m_memory->m_FBOs[fbo - 1]; pFBO) {
                renderPass = pFBO->GetRenderPass();
            }
            else {
                PipelineError("VulkanPipeline::CompileShader() : invalid FBO! SOMETHING WENT WRONG! MEMORY MAY BE CORRUPTED!");
                return false;
            }
        }

        if (!renderPass.IsReady()) {
            PipelineError("VulkanPipeline::CompileShader() : internal Evo Vulkan error! Render pass isn't ready!");
            return false;
        }

        ShaderProgram shaderProgram = m_memory->AllocateShaderProgram(renderPass);
        if (shaderProgram < 0) {
            PipelineError("VulkanPipeline::CompileShader() : failed to allocate shader program ID!");
            return false;
        }

        auto&& pShaderProgram = m_memory->m_ShaderPrograms[shaderProgram];

        std::vector<SourceShader> modules = { };

        for (auto&& [shaderStage, stage] : createInfo.stages) {
            SourceShader module(stage.path.ToString(), shaderStage);
            modules.emplace_back(module);
        }

        if (modules.empty()) {
            SRHalt("No shader modules were found!");
            return false;
        }

        auto&& pushConstants = VulkanTools::AbstractPushConstantToVkPushConstants(createInfo);

        auto&& descriptorLayoutBindings = VulkanTools::UniformsToDescriptorLayoutBindings(createInfo.uniforms);
        if (!descriptorLayoutBindings.has_value()) {
            SRHalt("VulkanPipeline::AllocateShaderProgram() : failed to create descriptor layout bindings!");
            return false;
        }

        std::vector<EvoVulkan::Complexes::SourceShader> vkModules;
        for (auto&& module : modules) {
            VkShaderStageFlagBits stage = VulkanTools::VkShaderShaderTypeToStage(module.m_stage);
            vkModules.emplace_back(EvoVulkan::Complexes::SourceShader(module.m_path, stage)); /// NOLINT
        }

        EVK_PUSH_LOG_LEVEL(EvoVulkan::Tools::LogLevel::ErrorsOnly);

        if (!pShaderProgram->Load(
                SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("/Cache/Shaders"),
                vkModules,
                descriptorLayoutBindings.value(),
                pushConstants
        )) {
            EVK_POP_LOG_LEVEL();
            DeleteShader(&shaderProgram);
            PipelineError("VulkanPipeline::CompileShader() : failed to load Evo Vulkan shader!");
            return false;
        }

        EVK_POP_LOG_LEVEL();

        auto&& vkVertexDescriptions = VulkanTools::AbstractVertexDescriptionsToVk(createInfo.vertexDescriptions);
        auto&& vkVertexAttributes = VulkanTools::AbstractAttributesToVkAttributes(createInfo.vertexAttributes);
        if (vkVertexAttributes.size() != createInfo.vertexAttributes.size()) {
            PipelineError("VulkanPipeline::LinkShader() : vkVertexDescriptions size != vertexDescriptions size!");
            DeleteShader(&shaderProgram);
            return false;
        }

        if (!pShaderProgram->SetVertexDescriptions(vkVertexDescriptions, vkVertexAttributes)) {
            PipelineError("VulkanPipeline::LinkShader() : failed to set vertex descriptions!");
            DeleteShader(&shaderProgram);
            return false;
        }

        const CullMode cullMode = createInfo.cullMode;
        const uint8_t sampleCount = GetFrameBufferSampleCount();
        const VkSampleCountFlagBits vkSampleCount = EvoVulkan::Tools::Convert::IntToSampleCount(sampleCount);
        const bool depthEnabled = m_currentVkFrameBuffer ? m_currentVkFrameBuffer->IsDepthEnabled() : true; /// NOLINT

        EVK_PUSH_LOG_LEVEL(EvoVulkan::Tools::LogLevel::ErrorsOnly);

        if (!pShaderProgram->Compile(
            VulkanTools::AbstractPolygonModeToVk(createInfo.polygonMode),
            VulkanTools::AbstractCullModeToVk(cullMode),
            VulkanTools::AbstractDepthOpToVk(createInfo.depthCompare),
            createInfo.blendEnabled && depthEnabled,
            createInfo.depthWrite,
            createInfo.depthTest,
            VulkanTools::AbstractPrimitiveTopologyToVk(createInfo.primitiveTopology),
            vkSampleCount
        )) {
            EVK_POP_LOG_LEVEL();
            PipelineError("VulkanPipeline::LinkShader() : failed to compile Evo Vulkan shader!");
            DeleteShader(&shaderProgram);
            return false;
        }

        EVK_POP_LOG_LEVEL();

        return shaderProgram;
    }

    uint8_t VulkanPipeline::GetFrameBufferSampleCount() const {
        ++m_state.operations;

        if (m_state.pFrameBuffer) {
            return m_state.pFrameBuffer->GetSamplesCount();
        }

        return GetSamplesCount();
    }

    void VulkanPipeline::ResetDescriptorSet() {
        Pipeline::ResetDescriptorSet();
        m_currentDescriptorSets = VK_NULL_HANDLE;
    }

    int32_t VulkanPipeline::AllocateTexture(const SRTextureCreateInfo& createInfo) {
        SRTextureCreateInfo textureCreateInfo = createInfo;

        ++m_state.allocations;
        ++m_state.operations;

        auto vkFormat = VulkanTools::AbstractTextureFormatToVkFormat(textureCreateInfo.format);
        if (vkFormat == VK_FORMAT_MAX_ENUM) {
            PipelineError("VulkanPipeline::AllocateTexture() : unsupported format!");
            return SR_ID_INVALID;
        }

        if (textureCreateInfo.compression != TextureCompression::None) {
            vkFormat = VulkanTools::AbstractTextureCompToVkFormat(textureCreateInfo.compression, vkFormat);
            if (vkFormat == VK_FORMAT_MAX_ENUM) {
                PipelineError("VulkanPipeline::AllocateTexture() : unsupported format with compression!");
                return SR_ID_INVALID;
            }

            if (auto&& size = MakeGoodSizes(textureCreateInfo.width, textureCreateInfo.height); size != std::pair(textureCreateInfo.width, textureCreateInfo.height)) {
                textureCreateInfo.pData = ResizeToLess(textureCreateInfo.width, textureCreateInfo.height, size.first, size.second, textureCreateInfo.pData);
                textureCreateInfo.width = size.first;
                textureCreateInfo.height = size.second;
            }

            if (textureCreateInfo.pData == nullptr || textureCreateInfo.width == 0 || textureCreateInfo.height == 0) {
                PipelineError("VulkanPipeline::AllocateTexture() : failed to reconstruct image!");
                return SR_ID_INVALID;
            }

            SR_LOG("VulkanPipeline::CalculateTexture() : compress " + SR_UTILS_NS::ToString(textureCreateInfo.width * textureCreateInfo.height * 4 / 1024 / 1024) + "MB source image...");

            textureCreateInfo.pData = Graphics::Compress(textureCreateInfo.width, textureCreateInfo.height, textureCreateInfo.pData, textureCreateInfo.compression);
            if (textureCreateInfo.pData == nullptr) {
                PipelineError("VulkanPipeline::AllocateTexture() : failed to compress image!");
                return SR_ID_INVALID;
            }
        }

        m_state.allocatedMemory += GetPixelSize(textureCreateInfo.format) * textureCreateInfo.width * textureCreateInfo.height;

        auto&& id = m_memory->AllocateTexture(
            textureCreateInfo.pData, textureCreateInfo.width, textureCreateInfo.height, vkFormat,
            VulkanTools::AbstractTextureFilterToVkFilter(textureCreateInfo.filter),
            textureCreateInfo.compression, textureCreateInfo.mipLevels, textureCreateInfo.cpuUsage
        );

        if (textureCreateInfo.compression != TextureCompression::None) {
            free(textureCreateInfo.pData); //! free compressed data. Original data isn't will free
        }

        if (id < 0) {
            PipelineError("VulkanPipeline::AllocateTexture() : failed to allocate texture!");
            return SR_ID_INVALID;
        }

        return id;
    }

    void VulkanPipeline::UnUseShader() {
        Super::UnUseShader();
        m_currentVkShader = nullptr;
        m_currentLayout = VK_NULL_HANDLE;
    }

    void VulkanPipeline::UpdateDescriptorSets(uint32_t descriptorSet, const SRDescriptorUpdateInfos& updateInfo) {
        Super::UpdateDescriptorSets(descriptorSet, updateInfo);

        std::vector<VkWriteDescriptorSet> writeDescriptorSets;

        for (auto&& info : updateInfo) {
            switch (info.descriptorType) {
                case DescriptorType::Uniform: {
                    auto&& vkDescriptorSet = m_memory->m_descriptorSets[descriptorSet].m_self;

                    if (info.ubo >= m_memory->m_countUBO.first) {
                        SRHalt(SR_FORMAT("VulkanPipeline::UpdateDescriptorSets() : uniform index out of range! \n\tCount uniforms: %i\n\tIndex: %i", m_memory->m_countUBO.first, info.ubo));
                        continue;
                    }

                    auto&& vkUBODescriptor = m_memory->m_UBOs[info.ubo]->GetDescriptorRef();

                    writeDescriptorSets.emplace_back(EvoVulkan::Tools::Initializers::WriteDescriptorSet(
                        vkDescriptorSet,
                        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                        info.binding,
                        vkUBODescriptor
                    ));

                    break;
                }
                default:
                    PipelineError("VulkanPipeline::UpdateDescriptorSets() : unknown type!");
                    return;
            }
        }

        if (writeDescriptorSets.empty()) {
            SRHalt("writeDescriptorSets is empty!");
            return;
        }

        vkUpdateDescriptorSets(*m_kernel->GetDevice(), writeDescriptorSets.size(), writeDescriptorSets.data(), 0, nullptr);
    }

    void VulkanPipeline::UpdateUBO(uint32_t UBO, void* pData, uint64_t size) {
        Super::UpdateUBO(UBO, pData, size);

        if (UBO >= m_memory->m_countUBO.first) {
            SRHalt(SR_FORMAT("VulkanPipeline::UpdateUBO() : uniform index out of range! \n\tCount uniforms: %i\n\tIndex: %i", m_memory->m_countUBO.first, UBO));
            return;
        }

        if (!m_memory->m_UBOs[UBO]) {
            SRHaltOnce0();
            return;
        }

        m_memory->m_UBOs[UBO]->CopyToDevice(pData, size);
    }

    uint8_t VulkanPipeline::GetBuildIterationsCount() const noexcept {
        return m_kernel ? m_kernel->GetCountBuildIterations() : 0;
    }

    void VulkanPipeline::SetViewport(int32_t width, int32_t height) {
        Super::SetViewport(width, height);

        if (width > 0 && height > 0) {
            m_viewport = EvoVulkan::Tools::Initializers::Viewport(
                static_cast<float_t>(width),
                static_cast<float_t>(height),
                0.f, 1.f
            );
        }
        else {
            if (m_state.frameBufferId == 0) {
                m_viewport = m_kernel->GetViewport();
            }
            else if (m_state.pFrameBuffer && m_currentVkFrameBuffer) {
                m_viewport = m_currentVkFrameBuffer->GetViewport();
            }
            else {
                SRHalt("Unresolved situation!");
                return;
            }
        }

        vkCmdSetViewport(m_currentCmd, 0, 1, &m_viewport);
    }

    void VulkanPipeline::SetScissor(int32_t width, int32_t height) {
        Super::SetScissor(width, height);

        if (width > 0 && height > 0) {
            m_scissor = EvoVulkan::Tools::Initializers::Rect2D(width, height, 0, 0);
        }
        else {
            if (m_state.frameBufferId == 0) {
                m_scissor = m_kernel->GetScissor();
            }
            else if (m_state.pFrameBuffer && m_currentVkFrameBuffer) {
                m_scissor = m_currentVkFrameBuffer->GetScissor();
            }
            else {
                SRHalt("Unresolved situation!");
                return;
            }
        }

        vkCmdSetScissor(m_currentCmd, 0, 1, &m_scissor);
    }

    void VulkanPipeline::BindFrameBuffer(Pipeline::FramebufferPtr pFBO) {
        Super::BindFrameBuffer(pFBO);

        if (!pFBO) {
            m_renderPassBI.framebuffer = m_kernel->m_frameBuffers[m_state.buildIteration];
            m_renderPassBI.renderPass  = m_kernel->GetRenderPass();
            m_renderPassBI.renderArea  = m_kernel->GetRenderArea();
            m_currentCmd = m_kernel->m_drawCmdBuffs[m_state.buildIteration];

            m_currentVkFrameBuffer = nullptr;
            m_state.frameBufferId = 0;
        }
        else {
            auto&& FBO = pFBO->GetId();
            if (FBO == UINT32_MAX) {
                PipelineError("VulkanPipeline::BindFrameBuffer() : frame buffer index equals UINT32_MAX! Something went wrong...");
                return;
            }

            auto&& pFrameBuffer = m_memory->m_FBOs[FBO - 1];
            if (!pFrameBuffer) {
                PipelineError("VulkanPipeline::BindFrameBuffer() : frame buffer object don't exist!");
                return;
            }

            auto&& layers = pFrameBuffer->GetLayers();
            uint32_t layerIndex = SR_MIN(m_state.frameBufferLayer, layers.size() - 1);
            auto&& vkFrameBuffer = layers.at(layerIndex)->GetFramebuffer();

            if (m_fboQueue.Contains(pFBO, layerIndex)) {
                PipelineError("VulkanPipeline::BindFrameBuffer() : frame buffer (\"" + std::to_string(FBO) + "\") is already added to FBO queue!");
                SRHalt0();
                return;
            }

            if (!m_fboQueue.Contains(pFBO)) {
                m_fboQueue.AddFrameBuffer(pFBO, layerIndex);
            }

            m_renderPassBI.framebuffer = vkFrameBuffer;
            m_renderPassBI.renderPass  = pFrameBuffer->GetRenderPass();
            m_renderPassBI.renderArea  = pFrameBuffer->GetRenderPassArea();
            m_currentCmd               = pFrameBuffer->GetCmd();

            m_currentVkFrameBuffer = pFrameBuffer;
            m_state.frameBufferId = FBO;
        }
    }

    int32_t VulkanPipeline::AllocateFrameBuffer(const SRFrameBufferCreateInfo& createInfo) {
        ++m_state.allocations;
        ++m_state.operations;

        std::vector<int32_t> colorBuffers;
        colorBuffers.reserve((*createInfo.colors).size());

        std::vector<VkFormat> formats;
        formats.reserve((*createInfo.colors).size());

        for (auto&& color : (*createInfo.colors)) {
            colorBuffers.emplace_back(color.texture);
            formats.emplace_back(VulkanTools::AbstractTextureFormatToVkFormat(color.format));
        }

        if (createInfo.size.x == 0 || createInfo.size.y == 0) {
            PipelineError("VulkanPipeline::AllocateFrameBuffer() : width or height equals zero!");
            return false;
        }

        if (*createInfo.pFBO == 0) {
            PipelineError("VulkanPipeline::AllocateFrameBuffer() : zero frame buffer are default frame buffer!");
            return false;
        }

        if (*createInfo.pFBO > 0) {
            if (!m_memory->ReAllocateFBO(*createInfo.pFBO - 1, createInfo.size.x, createInfo.size.y, colorBuffers, createInfo.pDepth, createInfo.sampleCount, createInfo.layersCount)) {
                PipelineError("VulkanPipeline::AllocateFrameBuffer() : failed to re-allocate frame buffer object!");
            }
            goto success;
        }

        *createInfo.pFBO = m_memory->AllocateFBO(createInfo.size.x, createInfo.size.y, formats, colorBuffers, createInfo.pDepth, createInfo.sampleCount, createInfo.layersCount) + 1;
        if (*createInfo.pFBO <= 0) {
            *createInfo.pFBO = SR_ID_INVALID;
            PipelineError("VulkanPipeline::AllocateFrameBuffer() : failed to allocate FBO!");
            return false;
        }

    success:
        for (uint32_t i = 0; i < static_cast<uint32_t>((*createInfo.colors).size()); ++i) {
            (*createInfo.colors)[i].texture = colorBuffers[i];
        }

        return true;
    }

    SR_MATH_NS::FColor VulkanPipeline::GetPixelColor(uint32_t textureId, uint32_t x, uint32_t y) {
        ++m_state.operations;

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

    bool VulkanPipeline::InitEvoVulkanHooks() {
        SR_GRAPH("VulkanPipeline::InitEvoVulkanHooks() : initialize evo vulkan hooks...");

        auto&& GetUsedMemoryFn = [pPipeline = GetThis()]() -> uint32_t {
            return pPipeline ? pPipeline->GetUsedMemory() / 1024 / 1024 : 0;
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().LogCallback = [GetUsedMemoryFn](const std::string& msg) {
            SR_VULKAN_LOG(SR_FORMAT("{%i} %s", GetUsedMemoryFn(), msg.c_str()));
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().WarnCallback = [GetUsedMemoryFn](const std::string& msg) {
            SR_WARN(SR_FORMAT("{%i} %s", GetUsedMemoryFn(), msg.c_str()));
        };
        EvoVulkan::Tools::VkFunctionsHolder::Instance().ErrorCallback = [GetUsedMemoryFn](const std::string& msg) {
            SR_VULKAN_ERROR(SR_FORMAT("{%i} %s", GetUsedMemoryFn(), msg.c_str()));
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().GraphCallback = [GetUsedMemoryFn](const std::string& msg) {
            SR_VULKAN_MSG(SR_FORMAT("{%i} %s", GetUsedMemoryFn(), msg.c_str()));
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().AssertCallback = [GetUsedMemoryFn](const std::string &msg) {
            SRHalt(SR_FORMAT("{%i} %s", GetUsedMemoryFn(), msg.c_str()));
            return false;
        };

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

        return true;
    }

    bool VulkanPipeline::PostInit() {
        SR_GRAPH_LOG("VulkanPipeline::PostInit() : post-initializing vulkan...");

        if (!m_kernel || !m_kernel->PostInit()) {
            SR_ERROR("VulkanPipeline::PostInit() : failed to post-initialize Evo Vulkan kernel!");
            return false;
        }

    #ifdef SR_TRACY_ENABLE
        if (SR_UTILS_NS::Features::Instance().Enabled("Tracy", false)) {
            if (auto&& pSingleTimeCmd = m_kernel->CreateCmd()) {
                SR_GRAPH_LOG("VulkanPipeline::PostInit() : initializing tracy...");
                SR_TRACY_VK_CREATE(*pSingleTimeCmd, m_kernel, "EvoVulkan");
                delete pSingleTimeCmd;
            }
        }
    #endif

        return Super::PostInit();
    }

    bool VulkanPipeline::BeginCmdBuffer() {
        if (!m_currentCmd) {
            PipelineError("VulkanPipeline::BeginCmdBuffer() : cmd buffer is nullptr!");
            return false;
        }

        vkBeginCommandBuffer(m_currentCmd, &m_cmdBufInfo);
        return Super::BeginCmdBuffer();
    }

    void VulkanPipeline::EndCmdBuffer() {
        if (!m_currentCmd) {
            PipelineError("VulkanPipeline::EndCmdBuffer() : cmd buffer is nullptr!");
            return;
        }

        vkEndCommandBuffer(m_currentCmd);
        Super::EndCmdBuffer();
    }

    bool VulkanPipeline::BeginRender() {
        if (!m_renderPassBI.pClearValues) {
            SRHaltOnce("pClearValues is nullptr! Please, call ClearBuffers before BeginRender");
            return false;
        }

        vkCmdBeginRenderPass(m_currentCmd, &m_renderPassBI, VK_SUBPASS_CONTENTS_INLINE);
        return Super::BeginRender();
    }

    void VulkanPipeline::EndRender() {
        Super::EndRender();

        if (!m_currentCmd) {
            PipelineError("VulkanPipeline::EndRender() : cmd buffer is nullptr!");
            return;
        }

        vkCmdEndRenderPass(m_currentCmd);
    }

    void VulkanPipeline::DrawFrame() {
        Super::DrawFrame();

        switch (m_kernel->NextFrame()) {
            case EvoVulkan::Core::RenderResult::Fatal:
                SR_UTILS_NS::EventManager::Instance().Broadcast(SR_UTILS_NS::EventManager::Event::FatalError);
                ++m_errorsCount;
                break;
            case EvoVulkan::Core::RenderResult::Error:
                PipelineError("VulkanPipeline::DrawFrame() : an error has been occurred!");
                break;
            case EvoVulkan::Core::RenderResult::DeviceLost:
                PipelineError("VulkanPipeline::DrawFrame() : device lost! Terminate...");
                SR_PLATFORM_NS::Terminate();
                break;
            default:
                break;
        }
    }

    void VulkanPipeline::ClearBuffers() {
        Super::ClearBuffers();

        if (m_state.frameBufferId < 0) {
            PipelineError("VulkanPipeline::ClearBuffers() : frame buffer is not attached!");
            return;
        }
        else if (m_state.frameBufferId > 0) {
            m_renderPassBI.clearValueCount = m_memory->m_FBOs[m_state.frameBufferId - 1]->GetCountClearValues();
            m_renderPassBI.pClearValues    = m_memory->m_FBOs[m_state.frameBufferId - 1]->GetClearValues();
        }
        else {
            /// в какой ситуации это может случиться?
            SRHalt("VulkanPipeline::ClearBuffers() : TODO!");
        }
    }

    void VulkanPipeline::ClearBuffers(float_t r, float_t g, float_t b, float_t a, float_t depth, uint8_t colorCount) {
        Super::ClearBuffers(r, g, b, a, depth, colorCount);

        const uint8_t sampleCount = GetFrameBufferSampleCount();

        colorCount *= sampleCount > 1 ? 2 : 1;

        m_clearValues.resize(colorCount + 1);

        for (uint8_t i = 0; i < colorCount; ++i) {
            m_clearValues[i] = { .color = {{ r, g, b, a }} };
        }

        m_clearValues[colorCount] = VkClearValue { .depthStencil = { depth, 0 } };

        m_renderPassBI.clearValueCount = colorCount + 1;
        m_renderPassBI.pClearValues    = m_clearValues.data();
    }

    void VulkanPipeline::ClearBuffers(const std::vector<SR_MATH_NS::FColor>& colors, float_t depth) {
        Super::ClearBuffers(colors, depth);

        const uint8_t sampleCount = GetFrameBufferSampleCount();

        auto colorCount = static_cast<uint8_t>(colors.size());
        colorCount *= sampleCount > 1 ? 2 : 1;

        m_clearValues.resize(colorCount + 1); /// TODO: а если буфера глубины нет??????

        for (uint8_t i = 0; i < colorCount; ++i) {
            auto&& color = colors[i / (sampleCount > 1 ? 2 : 1)];

            m_clearValues[i] = {
                .color = { {
                       static_cast<float_t>(color.r),
                       static_cast<float_t>(color.g),
                       static_cast<float_t>(color.b),
                       static_cast<float_t>(color.a)
                   }
                }
            };
        }

        m_clearValues[colorCount] = VkClearValue { .depthStencil = { depth, 0 } };

        m_renderPassBI.clearValueCount = colorCount + 1;
        m_renderPassBI.pClearValues  = m_clearValues.data();
    }

    void VulkanPipeline::OnResize(const SR_MATH_NS::UVector2& size) {
        m_kernel->SetSize(size.x, size.y);
        Super::OnResize(size);
    }

    bool VulkanPipeline::FreeTexture(int32_t *id) {
        ++m_state.operations;
        ++m_state.deletions;

        if (!m_memory || !m_memory->FreeTexture(static_cast<uint32_t>(*id))) {
            SR_ERROR("VulkanPipeline::FreeTexture() : failed to free texture!");
            return false;
        }

        *id = SR_ID_INVALID;

        return true;
    }
}