//
// Created by Monika on 16.05.2022.
//

#include <Render/RenderScene.h>
#include <Render/RenderContext.h>
#include <Memory/CameraManager.h>
#include <Types/Camera.h>
#include <Render/RenderTechnique.h>
#include <Utils/Types/SafePtrLockGuard.h>

namespace SR_GRAPH_NS {
    RenderScene::RenderScene(const ScenePtr& scene, RenderContext* pContext)
        : SR_HTYPES_NS::SafePtr<RenderScene>(this)
        , m_scene(scene)
        , m_context(pContext)
    { }

    RenderScene::~RenderScene() {
        if (m_technique) {
            m_technique->RemoveUsePoint();
            m_technique = nullptr;
        }

        SRAssert(IsEmpty());
    }

    void RenderScene::Render() {
        /// ImGui будет нарисован поверх независимо оторядка отрисовки.
        /// Однако, если его нарисовать в конце, то пользователь может
        /// изменить данные отрисовки сцены и сломать уже нарисованную сцену
        Overlay();

        if (m_dirtyCameras) {
            SortCameras();
        }

        if (m_dirty || GetPipeline()->IsNeedReBuild()) {
            Build();
        }
        else {
            Update();
        }

        if (!m_hasDrawData) {
            RenderBlackScreen();
        }

        Submit();
    }

    void RenderScene::SetDirty() {
        m_dirty = true;
    }

    void RenderScene::SetDirtyCameras() {
        m_dirtyCameras = true;
        m_dirty = true;
    }

    bool RenderScene::IsEmpty() const {
        return m_transparent.Empty() && m_opaque.Empty() && m_cameras.empty();
    }

    RenderContext *RenderScene::GetContext() const {
        return m_context;
    }

    void RenderScene::Build() {
        GetPipeline()->ClearFramebuffersQueue();

        m_hasDrawData = false;

        for (auto&& pCamera : m_offScreenCameras) {
            if (auto&& pRenderTechnique = pCamera->GetRenderTechnique()) {
                pRenderTechnique->Render();
                m_hasDrawData = true;
            }
        }

        if (m_mainCamera) {
            if (auto&& pRenderTechnique = m_mainCamera->GetRenderTechnique()) {
                pRenderTechnique->Render();
                m_hasDrawData = true;
            }
        }

        if (m_technique) {
            m_technique->Render();
        }

        m_dirty = false;

        GetPipeline()->SetBuildState(true);
    }

    void RenderScene::Update() {
        for (auto&& pCamera : m_offScreenCameras) {
            if (auto&& pRenderTechnique = pCamera->GetRenderTechnique()) {
                pRenderTechnique->Update();
            }
        }

        if (m_mainCamera) {
            if (auto&& pRenderTechnique = m_mainCamera->GetRenderTechnique()) {
                pRenderTechnique->Update();
            }
        }

        if (m_technique) {
            m_technique->Update();
        }
    }

    void RenderScene::Submit() {
        if (!m_hasDrawData && (!m_technique || m_technique->IsEmpty())) {
            return;
        }

        GetPipeline()->DrawFrame();
    }

    void RenderScene::SetTechnique(const SR_UTILS_NS::Path &path) {
        if (m_technique) {
            m_technique->RemoveUsePoint();
            m_technique = nullptr;
        }

        if ((m_technique = RenderTechnique::Load(path))) {
            m_technique->AddUsePoint();
            m_technique->SetRenderScene(GetThis());
        }
        else {
            SR_ERROR("RenderScene::SetTechnique() : failed to load render technique!");
        }

        SetDirty();
    }

    const RenderScene::WidgetManagers &RenderScene::GetWidgetManagers() const {
        return m_widgetManagers;
    }

    void RenderScene::Overlay() {
        GetPipeline()->SetGUIEnabled(m_bOverlay);

        if (!m_bOverlay) {
            return;
        }

        if (m_technique) {
            m_technique->Overlay();
        }
    }

    void RenderScene::RegisterWidgetManager(RenderScene::WidgetManagerPtr pWidgetManager) {
        if (!pWidgetManager) {
            return;
        }

        m_widgetManagers.emplace_back(pWidgetManager);
    }

    void RenderScene::RemoveWidgetManager(RenderScene::WidgetManagerPtr pWidgetManager) {
        if (!pWidgetManager) {
            return;
        }

        for (auto&& pIt = m_widgetManagers.begin(); pIt != m_widgetManagers.end(); ) {
            if (*pIt == pWidgetManager) {
                pIt = m_widgetManagers.erase(pIt);
                return;
            }
            else {
                ++pIt;
            }
        }

        SRHalt("RenderScene::RemoveWidgetManager() : the widget manager not found!");
    }

    void RenderScene::RegisterCamera(RenderScene::CameraPtr pCamera) {
        CameraInfo info;

        info.isDestroyed = false;
        info.pCamera = pCamera;

        m_cameras.emplace_back(info);

        m_dirtyCameras = true;
    }

    void RenderScene::DestroyCamera(RenderScene::CameraPtr pCamera) {
        for (auto&& cameraInfo : m_cameras) {
            if (cameraInfo.pCamera != pCamera) {
                continue;
            }

            SRAssert(!cameraInfo.isDestroyed);

            cameraInfo.isDestroyed = true;
            m_dirtyCameras = true;

            return;
        }

        SRHalt("RenderScene::DestroyCamera() : the camera not found!");
    }

    void RenderScene::SortCameras() {
        m_dirtyCameras = false;
        m_offScreenCameras.clear();
        m_mainCamera = nullptr;

        /// Удаляем уничтоженные камеры
        for (auto&& pIt = m_cameras.begin(); pIt != m_cameras.end(); ) {
            if (pIt->isDestroyed) {
                SR_LOG("RenderScene::SortCameras() : free camera...");

                delete pIt->pCamera;

                pIt = m_cameras.erase(pIt);
            }
            else {
                ++pIt;
            }
        }

        /// Ищем главную камеру и закадровые камеры
        for (auto&& cameraInfo : m_cameras) {
            if (!cameraInfo.pCamera->IsActive()) {
                continue;
            }

            if (cameraInfo.pCamera->GetPriority() < 0) {
                m_offScreenCameras.emplace_back(cameraInfo.pCamera);
                continue;
            }

            /// Выбирается камера, чей приоритет ближе к нулю
            if (!m_mainCamera || m_mainCamera->GetPriority() > cameraInfo.pCamera->GetPriority()) {
                m_mainCamera = cameraInfo.pCamera;
            }
        }

        std::stable_sort(m_offScreenCameras.begin(), m_offScreenCameras.end(), [](CameraPtr lhs, CameraPtr rhs) {
            return lhs->GetPriority() < rhs->GetPriority();
        });
    }

    RenderScene::PipelinePtr RenderScene::GetPipeline() const {
        return GetContext()->GetPipeline();
    }

    void RenderScene::RenderBlackScreen() {
        auto&& pipeline = GetPipeline();

        pipeline->ClearBuffers(0.0f, 0.0f, 0.0f, 1.f, 1.f, 1);

        for (uint8_t i = 0; i < pipeline->GetCountBuildIter(); ++i) {
            pipeline->SetBuildIteration(i);

            pipeline->BindFrameBuffer(0);

            pipeline->BeginRender();
            {
                pipeline->SetViewport();
                pipeline->SetScissor();
            }
            pipeline->EndRender();
        }
    }

    bool RenderScene::IsOverlayEnabled() const {
        return m_bOverlay;
    }

    void RenderScene::SetOverlayEnabled(bool enabled) {
        m_bOverlay = enabled;
    }
}
