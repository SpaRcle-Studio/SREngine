

# File CameraManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Memory**](dir_dc778743e05f6f13753dd9bf5a4bd428.md) **>** [**CameraManager.h**](CameraManager_8h.md)

[Go to the documentation of this file](CameraManager_8h.md)


```C++
//
// Created by Monika on 05.06.2022.
//

#ifndef SR_ENGINE_CAMERAMANAGER_H
#define SR_ENGINE_CAMERAMANAGER_H

#include <Graphics/macros.h>

#include <Utils/Common/Singleton.h>
#include <Utils/Types/SafePointer.h>

namespace SR_GRAPH_NS {
    class Window;
    class RenderScene;
    class Pipeline;
}

namespace SR_GRAPH_NS::Types {
    class Camera;
}

namespace SR_GRAPH_NS::Memory {
    class CameraManager : public SR_UTILS_NS::Singleton<CameraManager> {
        SR_REGISTER_SINGLETON(CameraManager)
        friend class SR_GTYPES_NS::Camera;
        using CameraPtr = Types::Camera*;
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<RenderScene>;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;

        struct CameraInfo {
            bool destroyed = false;
            RenderScenePtr pRenderScene;
        };

    protected:
        ~CameraManager() override = default;

    public:
        void SetPipeline(PipelinePtr pPipeline) { m_pipeline = std::move(pPipeline); }

        void Update();

        void OnWindowResized(Window* pWindow, uint32_t width, uint32_t height);

        SR_NODISCARD uint32_t GetCountCameras() const;
        SR_NODISCARD CameraPtr GetFirstCamera() const;
        SR_NODISCARD std::list<CameraPtr> GetCameras() const;
        SR_NODISCARD CameraPtr GetMainCamera(RenderScene* pRScene);
        SR_NODISCARD std::vector<CameraPtr> GetOffScreenCameras(RenderScene* pRScene);

        SR_NODISCARD bool IsRegistered(const CameraPtr& camera) const;
        SR_NODISCARD bool IsDestroyed(const CameraPtr& camera) const;

    protected:
        void OnSingletonDestroy() override;

    private:
        void RegisterCamera(const CameraPtr& camera);
        void UnRegisterCamera(const CameraPtr& camera);
        void DestroyCamera(const CameraPtr& camera);

    private:
        std::map<CameraPtr, CameraInfo> m_cameras;
        PipelinePtr m_pipeline;

    };
}

#endif //SR_ENGINE_CAMERAMANAGER_H
```


