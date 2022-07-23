//
// Created by Monika on 16.05.2022.
//

#ifndef SRENGINE_RENDERSCENE_H
#define SRENGINE_RENDERSCENE_H

#include <Utils/Common/NonCopyable.h>
#include <Render/MeshCluster.h>
#include <Utils/Types/SafePointer.h>

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_GTYPES_NS {
    class Camera;
}

namespace SR_GRAPH_NS {
    class RenderContext;
    class RenderTechnique;

    class RenderScene : public SR_HTYPES_NS::SafePtr<RenderScene> {
        using WidgetManagerPtr = GUI::WidgetManager*;
        using WidgetManagers = std::list<WidgetManagerPtr>;
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;
        using CameraPtr = SR_GTYPES_NS::Camera*;
        using PipelinePtr = Environment*;

        struct CameraInfo {
            bool isDestroyed = false;
            CameraPtr pCamera = nullptr;
        };

    public:
        explicit RenderScene(const ScenePtr& scene, RenderContext* pContext);
        virtual ~RenderScene();

    public:
        void Render();

        void SetDirty();
        void SetDirtyCameras();

        void SetTechnique(const SR_UTILS_NS::Path& path);

        void RegisterWidgetManager(WidgetManagerPtr pWidgetManager);
        void RemoveWidgetManager(WidgetManagerPtr pWidgetManager);

        void RegisterCamera(CameraPtr pCamera);
        void DestroyCamera(CameraPtr pCamera);

        void SetOverlayEnabled(bool enabled);

        SR_NODISCARD bool IsEmpty() const;
        SR_NODISCARD bool IsOverlayEnabled() const;
        SR_NODISCARD RenderContext* GetContext() const;
        SR_NODISCARD PipelinePtr GetPipeline() const;
        SR_NODISCARD const WidgetManagers& GetWidgetManagers() const;

    private:
        void SortCameras();
        void RenderBlackScreen();

        void Build();
        void Update();
        void Overlay();
        void Submit();

    private:
        CameraPtr m_mainCamera = nullptr;
        std::list<CameraPtr> m_offScreenCameras;
        std::list<CameraInfo> m_cameras;

        WidgetManagers m_widgetManagers;

        ScenePtr m_scene;

        RenderTechnique* m_technique   = nullptr;
        RenderContext*   m_context     = nullptr;

        MeshCluster      m_opaque      = { };
        MeshCluster      m_transparent = { };

        bool m_dirtyCameras = true;
        bool m_dirty        = true;
        bool m_hasDrawData  = false;
        bool m_bOverlay     = false;

    };
}

#endif //SRENGINE_RENDERSCENE_H
