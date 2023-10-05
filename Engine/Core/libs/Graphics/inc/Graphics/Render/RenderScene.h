//
// Created by Monika on 16.05.2022.
//

#ifndef SRENGINE_RENDERSCENE_H
#define SRENGINE_RENDERSCENE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SafeVariable.h>

#include <Graphics/Render/MeshCluster.h>
#include <Graphics/Render/FlatCluster.h>
#include <Graphics/Render/SortedMeshQueue.h>
#include <Graphics/GUI/WidgetManager.h>
#include <Graphics/Pass/PassQueue.h>

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_ANIMATIONS_NS {
    class Skeleton;
}

namespace SR_GTYPES_NS {
    class Camera;
    class Mesh;
}

namespace SR_GRAPH_NS {
    class LightSystem;
    class Window;
    class RenderContext;
    class RenderTechnique;
    class Pipeline;
    class DebugRenderer;

    class RenderScene : public SR_HTYPES_NS::SafePtr<RenderScene> {
    public:
        using WidgetManagerPtr = GUI::WidgetManager*;
        using WidgetManagers = std::vector<WidgetManagerPtr>;
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;
        using WindowPtr = SR_HTYPES_NS::SafePtr<Window>;
        using CameraPtr = SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Camera>;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
        using Ptr = SR_HTYPES_NS::SafePtr<RenderScene>;

        struct CameraInfo {
            CameraPtr pCamera;
        };

    public:
        explicit RenderScene(const ScenePtr& scene, RenderContext* pContext);
        virtual ~RenderScene();

    public:
        void Render() noexcept;
        void Synchronize();

        void OnResourceReloaded(SR_UTILS_NS::IResource* pResource);
        void OnResize(const SR_MATH_NS::UVector2& size);

        /// Можно вызывать не синхронно
        void SetDirty();

        void SetDirtyCameras();

        void SetTechnique(RenderTechnique* pTechnique);
        void SetTechnique(const SR_UTILS_NS::Path& path);

        void Register(const CameraPtr& pCamera);
        void Register(WidgetManagerPtr pWidgetManager);
        void Register(MeshPtr pMesh);

        void Remove(const CameraPtr& pCamera);
        void Remove(WidgetManagerPtr pWidgetManager);

        void SetOverlayEnabled(bool enabled);
        void SetCurrentSkeleton(SR_ANIMATIONS_NS::Skeleton* pSkeleton) { m_currentSkeleton = pSkeleton;}

        void ForEachTechnique(const SR_HTYPES_NS::Function<void(RenderTechnique*)>& callback);

        SR_NODISCARD bool IsDirty() const noexcept;
        SR_NODISCARD bool IsEmpty() const;
        SR_NODISCARD bool IsOverlayEnabled() const;
        SR_NODISCARD RenderContext* GetContext() const;
        SR_NODISCARD LightSystem* GetLightSystem() const { return m_lightSystem; }
        SR_NODISCARD SR_ANIMATIONS_NS::Skeleton* GetCurrentSkeleton() const { return m_currentSkeleton; }
        SR_NODISCARD PipelinePtr GetPipeline() const;
        SR_NODISCARD WindowPtr GetWindow() const;
        SR_NODISCARD const WidgetManagers& GetWidgetManagers() const;
        SR_NODISCARD MeshCluster& GetOpaque();
        SR_NODISCARD MeshCluster& GetTransparent();
        SR_NODISCARD MeshCluster& GetDebugCluster();
        SR_NODISCARD CameraPtr GetMainCamera() const;
        SR_NODISCARD DebugRenderer* GetDebugRenderer() const;
        SR_NODISCARD CameraPtr GetFirstOffScreenCamera() const;
        SR_NODISCARD SR_MATH_NS::UVector2 GetSurfaceSize() const;

    private:
        void SortCameras();
        void RenderBlackScreen();

        void PrepareFrame();
        void Overlay();
        void PrepareRender();
        void Build();
        void BuildQueue();
        void Update() noexcept;
        void Submit() noexcept;

    private:
        SR_ANIMATIONS_NS::Skeleton* m_currentSkeleton = nullptr;

        LightSystem* m_lightSystem = nullptr;

        CameraPtr m_mainCamera = nullptr;

        std::vector<CameraPtr> m_offScreenCameras;
        std::vector<CameraInfo> m_cameras;

        WidgetManagers m_widgetManagers;

        ScenePtr m_scene;

        DebugRenderer* m_debugRender = nullptr;
        RenderTechnique* m_technique = nullptr;
        RenderContext* m_context = nullptr;

        PassQueues m_queues;

        OpaqueMeshCluster m_opaque;
        TransparentMeshCluster m_transparent;
        FlatMeshCluster m_flat;
        DebugMeshCluster m_debug;

        SR_MATH_NS::UVector2 m_surfaceSize;

        SR_HTYPES_NS::SafeVar<uint32_t> m_dirty = 0;

        bool m_dirtyCameras = true;
        bool m_hasDrawData  = false;
        bool m_bOverlay     = false;

    };
}

#define SR_RENDER_TECHNIQUES_CALL(FunctionName, ...)                        \
    for (auto&& pCamera : m_offScreenCameras) {                             \
        if (!pCamera) { continue; }                                         \
        if (auto&& pRenderTechnique = pCamera->GetRenderTechnique()) {      \
            pRenderTechnique->FunctionName(##__VA_ARGS__);                  \
        }                                                                   \
    }                                                                       \
    if (m_mainCamera) {                                                     \
        if (auto&& pRenderTechnique = m_mainCamera->GetRenderTechnique()) { \
            pRenderTechnique->FunctionName(##__VA_ARGS__);                  \
        }                                                                   \
    }                                                                       \
    if (m_technique) {                                                      \
        m_technique->FunctionName(##__VA_ARGS__);                           \
    }                                                                       \

#define SR_RENDER_TECHNIQUES_RETURN_CALL(FunctionName, ...)                 \
    for (auto&& pCamera : m_offScreenCameras) {                             \
        if (!pCamera) { continue; }                                         \
        if (auto&& pRenderTechnique = pCamera->GetRenderTechnique()) {      \
            m_hasDrawData |= pRenderTechnique->FunctionName(##__VA_ARGS__); \
        }                                                                   \
    }                                                                       \
    if (m_mainCamera) {                                                     \
        if (auto&& pRenderTechnique = m_mainCamera->GetRenderTechnique()) { \
            m_hasDrawData |= pRenderTechnique->FunctionName(##__VA_ARGS__); \
        }                                                                   \
    }                                                                       \
    if (m_technique) {                                                      \
        m_hasDrawData |= m_technique->FunctionName(##__VA_ARGS__);          \
    }                                                                       \

#endif //SRENGINE_RENDERSCENE_H
