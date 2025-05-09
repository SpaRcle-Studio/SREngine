

# File CameraManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Memory**](dir_cc5176abae198c1d3b7945975349bd99.md) **>** [**CameraManager.h**](CameraManager_8h.md)

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


