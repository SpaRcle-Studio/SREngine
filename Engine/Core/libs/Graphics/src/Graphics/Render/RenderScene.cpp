//
// Created by Monika on 16.05.2022.
//

#include <Utils/DebugDraw.h>
#include <Utils/Types/SafePtrLockGuard.h>

#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Memory/CameraManager.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/Types/Geometry/DebugLine.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/Render/DebugRenderer.h>
#include <Graphics/Lighting/LightSystem.h>

namespace SR_GRAPH_NS {
    RenderScene::RenderScene(const ScenePtr& scene, RenderContext* pContext)
        : SR_HTYPES_NS::SafePtr<RenderScene>(this)
        , m_lightSystem(new LightSystem())
        , m_scene(scene)
        , m_debugRender(new DebugRenderer(this))
        , m_context(pContext)
        , m_opaque(&m_transparent)
        , m_transparent(&m_opaque)
    {
        m_debugRender->Init();
    }

    RenderScene::~RenderScene() {
        SR_SAFE_DELETE_PTR(m_lightSystem);

        if (m_debugRender) {
            m_debugRender->DeInit();
            delete m_debugRender;
            m_debugRender = nullptr;
        }

        if (m_technique) {
            m_technique->RemoveUsePoint();
            m_technique = nullptr;
        }

        SRAssert(IsEmpty());
    }

    void RenderScene::Render() noexcept {
        SR_TRACY_ZONE_N("Render scene");

        PrepareFrame();

        /// ImGui будет нарисован поверх независимо оторядка отрисовки.
        /// Однако, если его нарисовать в конце, то пользователь может
        /// изменить данные отрисовки сцены и сломать уже нарисованную сцену
        Overlay();

        PrepareRender();

        if (IsDirty() || GetPipeline()->IsNeedReBuild()) {
            Build();
        }

        Update();

        if (!m_hasDrawData) {
            RenderBlackScreen();
        }

        Submit();
    }

    void RenderScene::SetDirty() {
        m_dirty.Do([](uint32_t& data) {
            ++data;
        });
    }

    bool RenderScene::IsDirty() const noexcept {
        return m_dirty.Get() > 0;
    }

    void RenderScene::SetDirtyCameras() {
        m_dirtyCameras = true;
    }

    bool RenderScene::IsEmpty() const {
        if (m_debugRender && !m_debugRender->IsEmpty()) {
            return false;
        }

        return
            m_transparent.Empty() &&
            m_opaque.Empty() &&
            m_debug.Empty() &&
            m_cameras.empty();
    }

    RenderContext *RenderScene::GetContext() const {
        return m_context;
    }

    void RenderScene::Build() {
        SR_TRACY_ZONE_N("Build render");

        GetPipeline()->ClearFramebuffersQueue();

        m_hasDrawData = false;

        SR_RENDER_TECHNIQUES_RETURN_CALL(Render)

        m_dirty.Do([](uint32_t& data) {
            data = data > 1 ? 1 : 0;
        });

        GetPipeline()->SetBuildState(true);
    }

    void RenderScene::Update() noexcept {
        SR_TRACY_ZONE_N("Update render");

        SR_RENDER_TECHNIQUES_CALL(Update)
    }

    void RenderScene::Submit() noexcept {
        SR_TRACY_ZONE_N("Submit frame");

        GetPipeline()->DrawFrame();
    }

    void RenderScene::SetTechnique(RenderTechnique *pTechnique) {
        if (m_technique) {
            m_technique->RemoveUsePoint();
            m_technique = nullptr;
        }

        if ((m_technique = pTechnique)) {
            m_technique->AddUsePoint();
            m_technique->SetRenderScene(GetThis());
        }
        else {
            SR_ERROR("RenderScene::SetTechnique() : failed to load render technique!");
        }

        SetDirty();
    }

    void RenderScene::SetTechnique(const SR_UTILS_NS::Path &path) {
        SetTechnique(RenderTechnique::Load(path));
    }

    const RenderScene::WidgetManagers &RenderScene::GetWidgetManagers() const {
        return m_widgetManagers;
    }

    void RenderScene::Overlay() {
        SR_TRACY_ZONE;

        GetPipeline()->SetGUIEnabled(m_bOverlay);

        if (!m_bOverlay) {
            return;
        }

        SR_RENDER_TECHNIQUES_RETURN_CALL(Overlay)
    }

    void RenderScene::PrepareFrame() {
        if (auto&& pPipeline = GetPipeline()) {
            pPipeline->PrepareFrame();
        }

        m_context->UpdateFramebuffers();
    }

    void RenderScene::PrepareRender() {
        SR_TRACY_ZONE;

        if (m_debugRender) {
            m_debugRender->Prepare();
        }

        if (m_dirtyCameras) {
            SortCameras();
        }

        if (m_opaque.Update()) {
            SetDirty();
        }

        if (m_transparent.Update()) {
            SetDirty();
        }

        if (m_debug.Update()) {
            SetDirty();
        }

        SR_RENDER_TECHNIQUES_CALL(Prepare)
    }

    void RenderScene::Register(RenderScene::WidgetManagerPtr pWidgetManager) {
        if (!pWidgetManager) {
            return;
        }

        pWidgetManager->SetRenderScene(GetThis());

        m_widgetManagers.emplace_back(pWidgetManager);
    }

    void RenderScene::Register(RenderScene::MeshPtr pMesh) {
        if (!pMesh) {
            SRHalt("RenderScene::Register() : mesh is nullptr!");
            return;
        }

        if (!pMesh->GetMaterial()) {
            if (auto&& pDefaultMat = GetContext()->GetDefaultMaterial()) {
                pMesh->SetMaterial(pDefaultMat);
            }
            else {
                SR_ERROR("RenderScene::Register() : mesh material and default material is nullptr!");
                return;
            }
        }

        if (!pMesh->GetMaterial()->GetShader()) {
            SR_ERROR("RenderScene::Register() : mesh have not shader!");
            return;
        }

        pMesh->SetRenderContext(m_context);

        if (pMesh->IsDebugMesh()) {
            m_debug.Add(pMesh);
        }
        else {
            if (pMesh->GetMaterial()->IsTransparent()) {
                m_transparent.Add(pMesh);
            }
            else {
                m_opaque.Add(pMesh);
            }
        }

        m_dirty = true;
    }

    void RenderScene::Remove(RenderScene::WidgetManagerPtr pWidgetManager) {
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

    void RenderScene::Register(RenderScene::CameraPtr pCamera) {
        CameraInfo info;

        info.isDestroyed = false;
        info.pCamera = pCamera;

        m_cameras.emplace_back(info);

        m_dirtyCameras = true;
    }

    void RenderScene::Remove(RenderScene::CameraPtr pCamera) {
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
        m_dirty = true;
        m_dirtyCameras = false;
        m_mainCamera = nullptr;

        const uint64_t offScreenCamerasCount = m_offScreenCameras.size();
        m_offScreenCameras.clear();
        m_offScreenCameras.reserve(offScreenCamerasCount);

        /// Удаляем уничтоженные камеры
        for (auto&& pIt = m_cameras.begin(); pIt != m_cameras.end(); ) {
            if (pIt->isDestroyed) {
                SR_LOG("RenderScene::SortCameras() : free camera...");

                pIt->pCamera->AutoFree([](auto&& pData) {
                    delete pData;
                });

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

            /// Выбирается камера, чей приоритет выше
            if (!m_mainCamera || cameraInfo.pCamera->GetPriority() > m_mainCamera->GetPriority()) {
                m_mainCamera = cameraInfo.pCamera;
            }
        }

        /// TODO: убедиться, что сортируется так, как нужно
        std::stable_sort(m_offScreenCameras.begin(), m_offScreenCameras.end(), [](CameraPtr lhs, CameraPtr rhs) {
            return lhs->GetPriority() < rhs->GetPriority();
        });
    }

    RenderScene::PipelinePtr RenderScene::GetPipeline() const {
        return GetContext()->GetPipeline();
    }

    RenderScene::WindowPtr RenderScene::GetWindow() const {
        return GetContext()->GetWindow();
    }

    void RenderScene::RenderBlackScreen() {
        SR_TRACY_ZONE;

        auto&& pipeline = GetPipeline();

        pipeline->SetCurrentFramebuffer(nullptr);

        for (uint8_t i = 0; i < pipeline->GetCountBuildIter(); ++i) {
            pipeline->SetBuildIteration(i);

            pipeline->BindFrameBuffer(0);
            pipeline->ClearBuffers(0.0f, 0.0f, 0.0f, 1.f, 1.f, 1);

            pipeline->BeginCmdBuffer();
            {
                pipeline->BeginRender();
                pipeline->SetViewport();
                pipeline->SetScissor();
                pipeline->EndRender();
            }
            pipeline->EndCmdBuffer();
        }
    }

    bool RenderScene::IsOverlayEnabled() const {
        return m_bOverlay;
    }

    void RenderScene::SetOverlayEnabled(bool enabled) {
        m_bOverlay = enabled;
    }

    MeshCluster &RenderScene::GetOpaque() {
        return m_opaque;
    }

    MeshCluster &RenderScene::GetTransparent() {
        return m_transparent;
    }

    MeshCluster &RenderScene::GetDebugCluster() {
        return m_debug;
    }

    RenderScene::CameraPtr RenderScene::GetMainCamera() const {
        return m_mainCamera;
    }

    RenderScene::CameraPtr RenderScene::GetFirstOffScreenCamera() const {
        if (m_offScreenCameras.empty()) {
            return nullptr;
        }

        return m_offScreenCameras.front();
    }

    void RenderScene::Synchronize() {
        /// отладочной геометрией ничто не управляет, она уничтожается по истечению времени.
        /// ее нужно принудительно освобождать при закрытии сцены.
        if (m_debugRender && !m_scene.Valid()) {
            m_debugRender->Clear();
        }

        SortCameras();

        m_opaque.Update();
        m_transparent.Update();
        m_debug.Update();
    }

    void RenderScene::OnResize(const SR_MATH_NS::UVector2 &size) {
        m_surfaceSize = size;

        if (!m_context->GetWindow()->IsWindowCollapsed()) {
            for (auto&& cameraInfo : m_cameras) {
                if (cameraInfo.isDestroyed) {
                    continue;
                }

                cameraInfo.pCamera->UpdateProjection(m_surfaceSize.x, m_surfaceSize.y);
            }
        }

        if (m_technique) {
            m_technique->OnResize(size);
        }
    }

    SR_MATH_NS::UVector2 RenderScene::GetSurfaceSize() const {
        return m_surfaceSize;
    }

    DebugRenderer *RenderScene::GetDebugRenderer() const {
        return m_debugRender;
    }

    void RenderScene::OnResourceReloaded(SR_UTILS_NS::IResource::Ptr pResource) {
        m_debug.OnResourceReloaded(pResource);
        m_opaque.OnResourceReloaded(pResource);
        m_transparent.OnResourceReloaded(pResource);

        SetDirty();
    }
}
