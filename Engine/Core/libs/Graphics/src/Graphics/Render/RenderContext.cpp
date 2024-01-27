//
// Created by Monika on 18.07.2022.
//

#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/IRenderTechnique.h>

#include <Graphics/Window/Window.h>
#include <Graphics/Memory/ShaderProgramManager.h>
#include <Graphics/Pipeline/Vulkan/VulkanPipeline.h>
#include <Graphics/Pass/FramebufferPass.h>

#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Texture.h>
#include <Graphics/Types/RenderTexture.h>
#include <Graphics/Types/Skybox.h>

#include <Utils/Locale/Encoding.h>

namespace SR_GRAPH_NS {
    RenderContext::RenderContext(const RenderContext::WindowPtr& pWindow)
        : Super(this)
        , m_window(pWindow)
    { }

    void RenderContext::Update() noexcept {
        SR_TRACY_ZONE;

        /**
         * Все ресурсы при завершении работы рендера должны остаться только с одним use-point'ом.
         * В противном случае память никогда не освободится.
        */

        bool dirty = false;

        m_updateState = static_cast<RCUpdateQueueState>(static_cast<uint8_t>(m_updateState) + 1);

        switch (m_updateState) {
            case RCUpdateQueueState::Framebuffers: dirty |= Update(m_framebuffers); break;
            case RCUpdateQueueState::Shaders: dirty |= Update(m_shaders); break;
            case RCUpdateQueueState::Textures: dirty |= Update(m_textures); break;
            case RCUpdateQueueState::Techniques: dirty |= Update(m_techniques); break;
            case RCUpdateQueueState::Materials: dirty |= Update(m_materials); break;
            case RCUpdateQueueState::Skyboxes: dirty |= Update(m_skyboxes); break;
            case RCUpdateQueueState::ShadersGC:
                SR_GRAPH_NS::Memory::ShaderProgramManager::Instance().CollectUnusedShaders();
                break;
            case RCUpdateQueueState::End:
                m_updateState = RCUpdateQueueState::Begin;
                break;
            default:
                SRHaltOnce0();
                break;
        }

        for (auto pIt = std::begin(m_scenes); pIt != std::end(m_scenes); ) {
            auto&& [pScene, pRenderScene] = *pIt;

            /// Нет смысла синхронизировать сцену рендера, так как она еще способна сама позаботиться о себе
            if (pScene.Valid()) {
                if (dirty) {
                    pRenderScene->SetDirty();
                }

                ++pIt;
                continue;
            }

            /// Синхронизируем и проверяем, есть ли еще на сцене объекты
            if (!pRenderScene.Do<bool>([](RenderScene* pRScene) -> bool {
                pRScene->Synchronize();
                return pRScene->IsEmpty();
            }, false)) {
                ++pIt;
                continue;
            }

            /// Как только уничтожается основная сцена, уничтожаем сцену рендера
            SR_LOG("RenderContext::Update() : destroy render scene...");
            pRenderScene.AutoFree();
            pIt = m_scenes.erase(pIt);
        }
    }

    bool RenderContext::Init() {
        SR_TRACY_ZONE;

        SR_INFO("RenderContext::Init() : initializing render context...");

        m_pipeline = new VulkanPipeline(GetThis());

        if (!InitPipeline()) {
            SR_ERROR("RenderContext::Init() : failed to initialize pipeline!");
            return false;
        }

        SR_INFO("RenderContext::Init() : initializing overlay...");

        if (!m_pipeline->InitOverlay()) {
            SR_ERROR("RenderContext::Init() : failed to initialize overlay!");
            return false;
        }

        Memory::UBOManager::Instance().SetPipeline(m_pipeline);
        Memory::CameraManager::Instance().SetPipeline(m_pipeline);
        Memory::ShaderProgramManager::Instance().SetPipeline(m_pipeline);

        /// ----------------------------------------------------------------------------

        Memory::TextureConfig config;

        config.m_format = ImageFormat::RGBA8_UNORM;
        config.m_filter = TextureFilter::NEAREST;
        config.m_compression = TextureCompression::None;
        config.m_mipLevels = 1;
        config.m_alpha = SR_UTILS_NS::BoolExt::None;
        config.m_cpuUsage = false;

        /// ----------------------------------------------------------------------------

        if ((m_defaultTexture = SR_GTYPES_NS::Texture::Load("Engine/Textures/default_improved.png", config))) {
            m_defaultTexture->AddUsePoint();
        }
        else {
            SR_ERROR("RenderContext::Init() : failed to load default texture!");
        }

        /// ----------------------------------------------------------------------------

        /// так как вписать в код данные текстуры невозможно, то она хранится в виде base64, текстура размером 1x1 белого цвета формата png
        const std::string image = "iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAYAAAAfFcSJAAAABmJLR0QA/wD/AP+gvaeTAAAADUlEQVQI12N48eIFOwAINALALwGcPAAAAABJRU5ErkJggg==";

        if ((m_noneTexture = SR_GTYPES_NS::Texture::LoadFromMemory(SR_UTILS_NS::StringUtils::Base64Decode(image), config))) {
            m_noneTexture->AddUsePoint();
        }
        else {
            SR_ERROR("RenderContext::Init() : failed to create none texture!");
            return false;
        }

        /// ----------------------------------------------------------------------------

        if ((m_defaultUIMaterial = SR_GTYPES_NS::Material::Load("Engine/Materials/UI/ui.mat"))) {
            m_defaultUIMaterial->AddUsePoint();
        }
        else {
            SR_ERROR("RenderContext::Init() : failed to load default UI material!");
        }

        /// ----------------------------------------------------------------------------

        if ((m_defaultMaterial = SR_GTYPES_NS::Material::Load("Engine/Materials/default.mat"))) {
            m_defaultMaterial->AddUsePoint();
        }
        else {
            SR_ERROR("RenderContext::Init() : failed to load default material!");
        }

        /// ----------------------------------------------------------------------------

        return true;
    }

    void RenderContext::Close() {
        if (m_noneTexture) {
            m_noneTexture->RemoveUsePoint();
            m_noneTexture = nullptr;
        }

        if (m_defaultTexture) {
            m_defaultTexture->RemoveUsePoint();
            m_defaultTexture = nullptr;
        }

        if (m_defaultMaterial) {
            m_defaultMaterial->RemoveUsePoint();
            m_defaultMaterial = nullptr;
        }

        if (m_defaultUIMaterial) {
            m_defaultUIMaterial->RemoveUsePoint();
            m_defaultUIMaterial = nullptr;
        }
    }

    RenderContext::RenderScenePtr RenderContext::CreateScene(const SR_WORLD_NS::Scene::Ptr &scene) {
        SR_TRACY_ZONE;

        RenderScenePtr pRenderScene;

        if (scene.RecursiveLockIfValid()) {
            auto&& dataStorage = scene->GetDataStorage();

            /// У каждой сцены может быть только одна сцена рендера
            if (dataStorage.GetValueDef<RenderScenePtr>(RenderScenePtr())) {
                SR_ERROR("RenderContext::CreateScene() : render scene is already exists!");
                scene.Unlock();
                return pRenderScene;
            }

            pRenderScene = new RenderScene(scene, this);

            m_scenes.emplace_back(std::make_pair(
                scene,
                pRenderScene
            ));

            dataStorage.SetValue<RenderScenePtr>(pRenderScene);
            scene.Unlock();
        }
        else {
            SR_ERROR("RenderContext::CreateScene() : scene is invalid!");
        }

        return pRenderScene;
    }

    void RenderContext::Register(SR_GTYPES_NS::Framebuffer* pResource) {
        if (!RegisterResource(pResource)) {
            return;
        }
        m_framebuffers.emplace_back(pResource);
    }

    void RenderContext::Register(SR_GTYPES_NS::Shader *pResource) {
        if (!RegisterResource(pResource)) {
            return;
        }
        m_shaders.emplace_back(pResource);
    }

    void RenderContext::Register(SR_GTYPES_NS::Texture* pResource) {
        if (!RegisterResource(pResource)) {
            return;
        }
        m_textures.emplace_back(pResource);
    }

    void RenderContext::Register(IRenderTechnique* pResource) {
        if (!RegisterResource(pResource)) {
            return;
        }
        m_techniques.emplace_back(pResource);
    }

    void RenderContext::Register(RenderContext::MaterialPtr pResource) {
        if (!RegisterResource(pResource)) {
            return;
        }
        m_materials.emplace_back(pResource);
    }

    void RenderContext::Register(RenderContext::SkyboxPtr pResource) {
        if (!RegisterResource(pResource)) {
            return;
        }
        m_skyboxes.emplace_back(pResource);
    }

    bool RenderContext::IsEmpty() const {
        return
            m_shaders.empty() &&
            m_framebuffers.empty() &&
            m_textures.empty() &&
            m_materials.empty() &&
            m_skyboxes.empty() &&
            m_scenes.empty() &&
            m_techniques.empty();
    }

    RenderContext::PipelinePtr RenderContext::GetPipeline() const {
        return m_pipeline;
    }

    PipelineType RenderContext::GetPipelineType() const {
        return m_pipeline->GetType();
    }

    RenderContext::MaterialPtr RenderContext::GetDefaultMaterial() const {
        return m_defaultMaterial;
    }

    void RenderContext::SetDirty() {
        for (auto&& [pScene, pRenderScene] : m_scenes) {
            pRenderScene->SetDirty();
        }
    }

    RenderContext::TexturePtr RenderContext::GetDefaultTexture() const {
        return m_defaultTexture ? m_defaultTexture : m_noneTexture;
    }

    RenderContext::TexturePtr RenderContext::GetNoneTexture() const {
        return m_noneTexture;
    }

    void RenderContext::OnResize(const SR_MATH_NS::UVector2& size) {
        SR_TRACY_ZONE;

        if (m_pipeline) {
            m_pipeline->OnResize(size);
        }

        for (auto pIt = std::begin(m_scenes); pIt != std::end(m_scenes); ++pIt) {
            auto&&[pScene, pRenderScene] = *pIt;

            if (!pScene.Valid()) {
                continue;
            }

            pRenderScene.Do([&size](RenderScene *pRScene) {
                pRScene->OnResize(size);
            });
        }
    }

    SR_MATH_NS::UVector2 RenderContext::GetWindowSize() const {
        return m_window->GetSize();
    }

    RenderContext::FramebufferPtr RenderContext::FindFramebuffer(const std::string &name, CameraPtr pCamera) const {
        SR_TRACY_ZONE;

        for (auto&& pTechnique : m_techniques) {
            if (pTechnique->GetCamera() != pCamera) {
                continue;
            }

            auto&& pPass = pTechnique->FindPass(name);

            if (auto&& pFbPass = dynamic_cast<FramebufferPass*>(pPass)) {
                return pFbPass->GetFramebuffer();
            }
        }

        return nullptr;
    }

    RenderContext::FramebufferPtr RenderContext::FindFramebuffer(const std::string &name) const {
        SR_TRACY_ZONE;

        for (auto&& pTechnique : m_techniques) {
            auto&& pPass = pTechnique->FindPass(name);

            if (auto&& pFbPass = dynamic_cast<FramebufferPass*>(pPass)) {
                return pFbPass->GetFramebuffer();
            }
        }

        return nullptr;
    }

    RenderContext::ShaderPtr RenderContext::GetCurrentShader() const noexcept {
        return m_pipeline->GetCurrentShader();
    }

    void RenderContext::SetCurrentShader(RenderContext::ShaderPtr pShader) {
        m_pipeline->SetCurrentShader(pShader);
        SRAssert2(!pShader || pShader->IsAvailable(), "The shader was not bound and not available!");
    }

    RenderContext::WindowPtr RenderContext::GetWindow() const {
        return m_window;
    }

    void RenderContext::UpdateFramebuffers() {
        SR_TRACY_ZONE;

        for (auto&& pFrameBuffer : m_framebuffers) {
            if (!pFrameBuffer->IsDirty()) {
                continue;
            }

            pFrameBuffer->Update();
        }
    }

    const std::vector<SR_GTYPES_NS::Shader*>& RenderContext::GetShaders() const noexcept {
        return m_shaders;
    }

    const std::vector<SR_GTYPES_NS::Framebuffer*>& RenderContext::GetFramebuffers() const noexcept {
        return m_framebuffers;
    }

    const std::vector<SR_GTYPES_NS::Texture*>& RenderContext::GetTextures() const noexcept {
        return m_textures;
    }

    const std::vector<IRenderTechnique*>& RenderContext::GetRenderTechniques() const noexcept {
        return m_techniques;
    }

    const std::vector<SR_GTYPES_NS::Material*>& RenderContext::GetMaterials() const noexcept {
        return m_materials;
    }

    const std::vector<SR_GTYPES_NS::Skybox*>& RenderContext::GetSkyboxes() const noexcept {
        return m_skyboxes;
    }

    void RenderContext::OnMultiSampleChanged() {
        SR_TRACY_ZONE;

        for (auto&& pFrameBuffer : m_framebuffers) {
            pFrameBuffer->SetDirty();
        }

        for (auto&& pRenderTechnique : m_techniques) {
            pRenderTechnique->OnSamplesChanged();
        }
    }

    RenderContext::~RenderContext() {
        SRAssert(IsEmpty());

        m_pipeline.AutoFree([](auto&& pPipeline) {
            pPipeline->Destroy();
            delete pPipeline;
        });
    }

    bool RenderContext::InitPipeline() {
        SR_GRAPH("RenderContext::InitPipeline() : initializing the render pipeline...");

        PipelinePreInitInfo pipelinePreInitInfo;
        pipelinePreInitInfo.appName = "SpaRcle Engine";
        pipelinePreInitInfo.engineName = "SREngine";
        pipelinePreInitInfo.samplesCount = 64;
        pipelinePreInitInfo.vsync = false;
    #if defined(SR_WIN32)
        pipelinePreInitInfo.GLSLCompilerPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Utilities/glslc.exe");
    #elif defined(SR_LINUX)
        pipelinePreInitInfo.GLSLCompilerPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Utilities/glslc");
    #endif
        if (!m_pipeline->PreInit(pipelinePreInitInfo)) {
            SR_ERROR("Engine::InitializeRender() : failed to pre-initialize the pipeline!");
            return false;
        }

        if (!m_pipeline->Init()) {
            SR_ERROR("Engine::InitializeRender() : failed to initialize the pipeline!");
            return false;
        }

        if (!m_pipeline->PostInit()) {
            SR_ERROR("Engine::InitializeRender() : failed to post-initialize pipeline!");
            return false;
        }

        SR_LOG("Engine::InitializeRender() : vendor is "   + m_pipeline->GetVendor());
        SR_LOG("Engine::InitializeRender() : renderer is " + m_pipeline->GetRenderer());
        SR_LOG("Engine::InitializeRender() : version is "  + m_pipeline->GetVersion());

        return true;
    }

    bool RenderContext::IsDirty() const {
        for (auto&& [pScene, pRenderScene] : m_scenes) {
            if (pRenderScene->IsDirty()) {
                return true;
            }
        }

        return false;
    }
}
