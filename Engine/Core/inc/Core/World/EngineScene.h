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
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderScene>;
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
