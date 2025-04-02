

# File RenderScene.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Render**](dir_5ea2fe9b8fa53724ec2c57fac60d8202.md) **>** [**RenderScene.h**](RenderScene_8h.md)

[Go to the documentation of this file](RenderScene_8h.md)


```C++
//
// Created by Monika on 16.05.2022.
//

#ifndef SR_ENGINE_RENDERSCENE_H
#define SR_ENGINE_RENDERSCENE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SafeVariable.h>

#include <Graphics/Render/MeshCluster.h>
#include <Graphics/Render/RenderStrategy.h>
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
    class IRenderer;
    class RenderStrategy;
    class LightSystem;
    class Window;
    class RenderContext;
    class IRenderTechnique;
    class Pipeline;
    class DebugRenderer;

    class RenderScene : public SR_HTYPES_NS::SharedPtr<RenderScene> {
        using Super = SR_HTYPES_NS::SharedPtr<RenderScene>;
    public:
        using WidgetManagerPtr = GUI::WidgetManager*;
        using WidgetManagers = std::vector<WidgetManagerPtr>;
        using ScenePtr = SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>;
        using WindowPtr = SR_HTYPES_NS::SharedPtr<Window>;
        using CameraPtr = SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Camera>;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
        using Ptr = SR_HTYPES_NS::SharedPtr<RenderScene>;

        struct CameraInfo {
            CameraPtr pCamera;
        };

    public:
        explicit RenderScene(const ScenePtr& scene, RenderContext* pContext);
        ~RenderScene() override;

    public:
        void Init();
        void DeInit();

        void Render();
        void Submit();

        void Synchronize();

        void OnResourceReloaded(SR_UTILS_NS::IResource* pResource);
        void OnResize(const SR_MATH_NS::UVector2& size);

        void SetDirty();

        void SetDirtyCameras();

        void SetTechnique(IRenderTechnique* pTechnique);
        void SetTechnique(const SR_UTILS_NS::Path& path);

        void Register(const CameraPtr& pCamera);
        void Register(WidgetManagerPtr pWidgetManager);
        void Register(MeshPtr pMesh);

        void Remove(const CameraPtr& pCamera);
        void Remove(WidgetManagerPtr pWidgetManager);
        void Remove(MeshPtr pMesh);

        void ReRegister(const MeshRegistrationInfo& info);

        void SetOverlayEnabled(bool enabled);
        void SetCurrentSkeleton(SR_ANIMATIONS_NS::Skeleton* pSkeleton) { m_currentSkeleton = pSkeleton;}

        void ForEachTechnique(const SR_HTYPES_NS::Function<void(IRenderTechnique*)>& callback);

        template<typename T> SR_HTYPES_NS::SharedPtr<T> AddRenderer() {
            return AddRenderer(T::GetClassStaticName()).template DynamicCast<T>();
        }

        template<typename T> SR_HTYPES_NS::SharedPtr<T> GetRenderer() const {
            return GetRenderer(T::GetClassStaticName()).template DynamicCast<T>();
        }

        SR_HTYPES_NS::SharedPtr<IRenderer> AddRenderer(SR_UTILS_NS::StringAtom name);

        SR_NODISCARD SR_HTYPES_NS::SharedPtr<IRenderer> GetRenderer(SR_UTILS_NS::StringAtom name) const;
        SR_NODISCARD bool IsDirty() const noexcept;
        SR_NODISCARD bool IsEmpty() const;
        SR_NODISCARD bool IsOverlayEnabled() const;
        SR_NODISCARD RenderContext* GetContext() const;
        SR_NODISCARD LightSystem* GetLightSystem() const { return m_lightSystem; }
        SR_NODISCARD SR_ANIMATIONS_NS::Skeleton* GetCurrentSkeleton() const { return m_currentSkeleton; }
        SR_NODISCARD const RenderScene::PipelinePtr& GetPipeline() const;
        SR_NODISCARD RenderScene::PipelinePtr GetPipeline();
        SR_NODISCARD WindowPtr GetWindow() const;
        SR_NODISCARD const WidgetManagers& GetWidgetManagers() const;
        SR_NODISCARD CameraPtr GetMainCamera() const;
        SR_NODISCARD RenderStrategy* GetRenderStrategy() { return m_renderStrategy.Get(); }
        SR_NODISCARD CameraPtr GetFirstOffScreenCamera() const;
        SR_NODISCARD SR_MATH_NS::UVector2 GetSurfaceSize() const;
        SR_NODISCARD const std::vector<CameraInfo>& GetCameras() { return m_cameras; }

    private:
        void SetMeshMaterial(MeshPtr pMesh);

        void SortCameras();
        void RenderBlackScreen();

        void PrepareFrame();
        void Overlay();
        void PrepareRender();
        void Build();
        void BuildQueue();
        void Update();
        void PostUpdate();

    private:
        SR_HTYPES_NS::SharedPtr<RenderStrategy> m_renderStrategy;

        SR_ANIMATIONS_NS::Skeleton* m_currentSkeleton = nullptr;

        LightSystem* m_lightSystem = nullptr;
        CameraPtr m_mainCamera;

        std::vector<CameraPtr> m_editorCameras;
        std::vector<CameraPtr> m_offScreenCameras;
        std::vector<CameraInfo> m_cameras;

        WidgetManagers m_widgetManagers;

        ScenePtr m_scene;

        std::map<SR_UTILS_NS::StringAtom, SR_HTYPES_NS::SharedPtr<IRenderer>> m_renderers;
        IRenderTechnique* m_technique = nullptr;
        RenderContext* m_context = nullptr;

        PassQueues m_queues;

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

#endif //SR_ENGINE_RENDERSCENE_H
```


