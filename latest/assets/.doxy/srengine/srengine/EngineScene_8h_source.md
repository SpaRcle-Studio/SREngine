

# File EngineScene.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**World**](dir_61ddcda44ab5988dd2bd052e2f237885.md) **>** [**EngineScene.h**](EngineScene_8h.md)

[Go to the documentation of this file](EngineScene_8h.md)


```C++
//
// Created by Monika on 25.12.2022.
//

#ifndef SR_ENGINE_ENGINE_SCENE_H
#define SR_ENGINE_ENGINE_SCENE_H

#include <Utils/World/SceneUpdater.h>
#include <Utils/World/Scene.h>

#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/RenderTechnique.h>

#include <Physics/PhysicsScene.h>

namespace SR_CORE_NS {
    class Engine;

    struct EngineScene : public SR_UTILS_NS::NonCopyable {
    public:
        using Super = SR_UTILS_NS::NonCopyable;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<SR_PHYSICS_NS::PhysicsScene>;
        using ScenePtr = SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>;
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::RenderScene>;
        using CameraPtr = SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Camera>;

    public:
        EngineScene(const ScenePtr& scene, Engine* pEngine);
        ~EngineScene() override;

    public:
        SR_NODISCARD bool Init();

        SR_NODISCARD CameraPtr GetMainCamera() const { return pMainCamera; }

        void SetActive(bool active);
        void SetPaused(bool pause);
        void SetGameMode(bool gameMode);

        void UpdateMainCamera();
        void Update(float_t dt);
        void SkipDraw();
        void SetSpeed(float_t speed);
        void UpdateChunkDebug();

    private:
        void UpdateFrequency();
        void FixedStep(bool isPaused);

    public:
        ScenePtr pScene;
        RenderScenePtr pRenderScene;
        PhysicsScenePtr pPhysicsScene;
        SR_WORLD_NS::SceneUpdater* pSceneUpdater = nullptr;
        CameraPtr pMainCamera;
        Engine* pEngine = nullptr;

        float_t m_speed = 1.f;
        float_t m_updateFrequency = 1.f;
        float_t m_accumulator = 1.f;
        bool m_accumulateDt = false;

    };
}

#endif //SR_ENGINE_ENGINESCENE_H
```


