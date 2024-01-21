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

        hasDrawData |= GroupPass::PreRender();
        hasDrawData |= GroupPass::Render();
        hasDrawData |= GroupPass::PostRender();

        return hasDrawData;
    }

    void IRenderTechnique::Prepare() {
        SR_TRACY_ZONE;

        if ((m_dirty && !Build()) || !m_camera || !m_camera->IsActive()) {
            return;
        }

        GroupPass::Prepare();
    }

    void IRenderTechnique::Update() {
        SR_TRACY_ZONE;

        if (m_dirty || !m_camera || !m_camera->IsActive()) {
            return;
        }

        m_uboManager.SetIdentifier(GetCamera());

        GroupPass::Update();
    }

    bool IRenderTechnique::Overlay() {
        SR_TRACY_ZONE;

        if (m_dirty) {
            return false;
        }

        m_uboManager.SetIdentifier(GetCamera());

        return GroupPass::Overlay();
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
            SetContext(m_renderScene->GetContext());
            GetContext()->Register(this);
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

    void IRenderTechnique::DeInitPasses() {
        for (auto&& pPass : m_passes) {
            if (pPass->IsInit()) {
                pPass->DeInit();
            }
            delete pPass;
        }
        m_passes.clear();
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