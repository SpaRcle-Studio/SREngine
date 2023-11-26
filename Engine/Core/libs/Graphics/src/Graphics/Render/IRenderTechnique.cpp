//
// Created by Monika on 10.10.2023.
//

#include <Graphics/Render/IRenderTechnique.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Pass/GroupPass.h>
#include <Graphics/Pass/IColorBufferPass.h>

namespace SR_GRAPH_NS {
    IRenderTechnique::IRenderTechnique()
        : Super()
        , m_dirty(true)
        , m_uboManager(Memory::UBOManager::Instance())
    { }

    IRenderTechnique::~IRenderTechnique() {
        for (auto&& pPass : m_passes) {
            delete pPass;
        }
        m_passes.clear();
    }

    bool IRenderTechnique::Render() {
        SR_TRACY_ZONE;

        if (m_dirty || !m_camera || !m_camera->IsActive()) {
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

    void IRenderTechnique::Prepare() {
        SR_TRACY_ZONE;

        if ((m_dirty && !Build()) || !m_camera || !m_camera->IsActive()) {
            return;
        }

        for (auto&& pass : m_passes) {
            pass->Prepare();
        }
    }

    void IRenderTechnique::Update() {
        SR_TRACY_ZONE;

        if (m_dirty || !m_camera || !m_camera->IsActive()) {
            return;
        }

        m_uboManager.SetIdentifier(GetCamera());

        for (auto&& pass : m_passes) {
            pass->Update();
        }
    }

    bool IRenderTechnique::Overlay() {
        SR_TRACY_ZONE;

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

    void IRenderTechnique::OnResize(const SR_MATH_NS::UVector2 &size) {
        SR_TRACY_ZONE;

        for (auto&& pass : m_passes) {
            pass->OnResize(size);
        }
    }


    void IRenderTechnique::SetDirty() {
        m_dirty = true;

        /// Авось что-то изменилось, нужно попробовать еще раз сбилдить
        m_hasErrors = false;

        if (m_renderScene) {
            m_renderScene->SetDirty();
        }
    }

    void IRenderTechnique::SetCamera(IRenderTechnique::CameraPtr pCamera) {
        m_camera = pCamera;
    }

    void IRenderTechnique::SetRenderScene(const IRenderTechnique::RenderScenePtr& pRScene) {
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

    IRenderTechnique::RenderScenePtr IRenderTechnique::GetRenderScene() const {
        SRAssert(m_renderScene.Valid());
        return m_renderScene;
    }

    void IRenderTechnique::FreeVideoMemory() {
        for (auto&& pPass : m_passes) {
            if (!pPass->IsInit()) {
                continue;
            }

            pPass->DeInit();
        }
    }

    bool IRenderTechnique::IsEmpty() const {
        /// Не делаем блокировки, так как взаимодействие
        /// идет только из графического потока
        return m_passes.empty();
    }

    BasePass* IRenderTechnique::FindPass(const SR_UTILS_NS::StringAtom& name) const {
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

    std::string_view IRenderTechnique::GetName() const {
        return m_name;
    }

    void IRenderTechnique::OnSamplesChanged() {
        for (auto&& pPass : m_passes) {
            pPass->OnSamplesChanged();
        }
    }

    void IRenderTechnique::DeInitPasses() {
        for (auto&& pPass : m_passes) {
            if (pPass->IsInit()) {
                pPass->DeInit();
            }
            delete pPass;
        }
        m_passes.clear();
    }

    bool IRenderTechnique::ForEachPass(const SR_HTYPES_NS::Function<bool(BasePass*)>& callback) const {
        for (auto&& pPass : m_passes) {
            if (!callback(pPass)) {
                return false;
            }

            if (auto&& pGroupPass = dynamic_cast<GroupPass*>(pPass)) {
                if (!pGroupPass->ForEachPass(callback)) {
                    return false;
                }
            }
        }
        return true;
    }

    SR_GTYPES_NS::Mesh* IRenderTechnique::PickMeshAt(float_t x, float_t y, const std::vector<SR_UTILS_NS::StringAtom>& passFilter) const {
        for (auto&& filter : passFilter) {
            if (auto&& pPass = dynamic_cast<SR_GRAPH_NS::IColorBufferPass*>(FindPass(filter))) {
                if (auto&& pMesh = pPass->GetMesh(x, y)) {
                    return pMesh;
                }
            }
        }
        return nullptr;
    }
}