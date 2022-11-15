//
// Created by Monika on 17.07.2022.
//

#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/RenderContext.h>

namespace SR_GRAPH_NS {
    RenderTechnique::RenderTechnique()
        : Super()
        , m_dirty(true)
        , m_uboManager(Memory::UBOManager::Instance())
    { }

    RenderTechnique::~RenderTechnique() {
        for (auto&& pPass : m_passes) {
            delete pPass;
        }
        m_passes.clear();
    }

    RenderTechnique *RenderTechnique::Load(const SR_UTILS_NS::Path &rawPath) {
        SR_GLOBAL_LOCK

        /// Данный ресурс может иметь копии

        auto&& path = SR_UTILS_NS::Path(rawPath).RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

        auto&& pRenderTechnique = new RenderTechnique();

        pRenderTechnique->SetId(path, false /** auto register */);

        if (!pRenderTechnique->Reload()) {
            SR_ERROR("RenderTechnique::Load() : failed to load render technique!\n\tPath: " + path.ToString());
            delete pRenderTechnique;
            return nullptr;
        }

        /// отложенная ручная регистрация
        SR_UTILS_NS::ResourceManager::Instance().RegisterResource(pRenderTechnique);

        return pRenderTechnique;
    }

    bool RenderTechnique::Render() {
        if ((m_dirty && !Build()) || !m_camera || !m_camera->IsActive()) {
            return false;
        }

        m_uboManager.SetIdentifier(GetCamera());

        bool hasDrawData = false;

        for (auto&& pass : m_passes) {
            hasDrawData |= pass->PreRender();
        }

        for (auto&& pass : m_passes) {
            hasDrawData |= pass->Render();
        }

        for (auto&& pass : m_passes) {
            hasDrawData |= pass->PostRender();
        }

        return hasDrawData;
    }

    void RenderTechnique::Prepare() {
        if (m_dirty) {
            return;
        }

        for (auto&& pass : m_passes) {
            pass->Prepare();
        }
    }

    void RenderTechnique::Update() {
        if (m_dirty || !m_camera || !m_camera->IsActive()) {
            return;
        }

        m_uboManager.SetIdentifier(GetCamera());

        for (auto&& pass : m_passes) {
            pass->Update();
        }
    }

    bool RenderTechnique::Overlay() {
        if (m_dirty) {
            return false;
        }

        m_uboManager.SetIdentifier(GetCamera());

        bool hasDrawData = false;

        for (auto&& pass : m_passes) {
            hasDrawData |= pass->Overlay();
        }

        return hasDrawData;
    }

    void RenderTechnique::OnResize(const SR_MATH_NS::IVector2 &size) {
        for (auto&& pass : m_passes) {
            pass->OnResize(size);
        }
    }

    bool RenderTechnique::Load() {
        SR_LOCK_GUARD

        SetDirty();

        m_loadState = LoadState::Loading;

        return true;
    }

    bool RenderTechnique::Unload() {
        SR_LOCK_GUARD

        m_loadState = LoadState::Unloading;

        return IResource::Unload();
    }

    void RenderTechnique::SetDirty() {
        m_dirty = true;

        /// Авось что-то изменилось, нужно попробовать еще раз сбилдить
        m_hasErrors = false;

        if (m_renderScene.LockIfValid()) {
            m_renderScene->SetDirty();
            m_renderScene.Unlock();
        }
    }

    void RenderTechnique::SetCamera(RenderTechnique::CameraPtr pCamera) {
        m_camera = pCamera;
    }

    bool RenderTechnique::Build() {
        /// Метод выполняется в графическом контексте

        if (m_hasErrors) {
            return false;
        }

        if (!m_dirty) {
            SRHalt("RenderTechnique::Build() : render technique isn't dirty!");
            return false;
        }

        SR_GRAPH_LOG("RenderTechnique::Build() : building render technique...");

        /// Очишаем старые данные, если они были
        ClearSettings();

        /// Загружаем новые данные
        auto&& document = LoadDocument();
        if (!document.Valid()) {
            SR_ERROR("RenderTechnique::Build() : failed to load xml document!");
            m_loadState = LoadState::Error;
            return false;
        }

        if (auto&& settings = document.Root().GetNode("Technique")) {
            if (!LoadSettings(settings)) {
                SR_ERROR("RenderTechnique::Build() : failed to load render technique!");
                m_loadState = LoadState::Error;
                return false;
            }
        }
        else {
            SR_ERROR("RenderTechnique::Build() : \"Technique\" node not found!");
            m_loadState = LoadState::Error;
            return false;
        }

        /// Инициализируем все успешно загруженнеы проходы
        for (auto&& pPass : m_passes) {
            pPass->Init();
        }

        m_loadState = LoadState::Loaded;
        m_dirty = false;

        return true;
    }

    bool RenderTechnique::LoadSettings(const SR_XML_NS::Node &node) {
        m_name = node.GetAttribute("Name").ToString();

        for (auto&& passNode : node.GetNodes()) {
            if (auto&& pPass = SR_ALLOCATE_RENDER_PASS(this, passNode, nullptr)) {
                m_passes.emplace_back(pPass);
            }
            else {
                SR_ERROR("RenderTechnique::LoadSettings() : failed to load \"" + passNode.Name() + "\" pass!");
            }
        }

        return true;
    }

    void RenderTechnique::ClearSettings() {
        for (auto&& pPass : m_passes) {
            if (pPass->IsInit()) {
                pPass->DeInit();
            }
            delete pPass;
        }
        m_passes.clear();
        m_name.clear();
    }

    void RenderTechnique::SetRenderScene(const RenderTechnique::RenderScenePtr& pRScene) {
        if (m_renderScene.Valid()) {
            SR_ERROR("RenderTechnique::SetRenderScene() : render scene already exists!");
            return;
        }

        m_renderScene = pRScene;

        if (m_renderScene.RecursiveLockIfValid()) {
            m_context = m_renderScene->GetContext();
            m_context->Register(this);
            m_renderScene.Unlock();
        }
        else {
            SR_ERROR("RenderTechnique::SetRenderScene() : render scene are invalid!");
        }
    }

    RenderTechnique::RenderScenePtr RenderTechnique::GetRenderScene() const {
        SRAssert(m_renderScene.Valid());
        return m_renderScene;
    }

    void RenderTechnique::FreeVideoMemory() {
        for (auto&& pPass : m_passes) {
            if (!pPass->IsInit()) {
                continue;
            }

            pPass->DeInit();
        }
    }

    bool RenderTechnique::IsEmpty() const {
        /// Не делаем блокировки, так как взаимодействие
        /// идет только из графического потока
        return m_passes.empty();
    }

    BasePass* RenderTechnique::FindPass(const std::string &name) const {
        for (auto&& pPass : m_passes) {
            if (auto&& pGroupPass = dynamic_cast<GroupPass*>(pPass)) {
                if (auto&& pFoundPass = pGroupPass->FindPass(name)) {
                    return pFoundPass;
                }
            }

            if (pPass->GetName() != name) {
                continue;
            }

            return pPass;
        }

        return nullptr;
    }

    std::string_view RenderTechnique::GetName() const {
        return m_name;
    }
}
