//
// Created by Monika on 25.12.2022.
//

#ifndef SRENGINE_ENGINESCENE_H
#define SRENGINE_ENGINESCENE_H

#include <Utils/World/SceneBuilder.h>
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
        using CameraPtr = SR_GTYPES_NS::Camera*;

    public:
        EngineScene(const ScenePtr& scene, Engine* pEngine);
        ~EngineScene() override;

    public:
        SR_NODISCARD bool Init();

        void SetActive(bool active);
        void SetPaused(bool pause);
        void SetGameMode(bool gameMode);

        void UpdateMainCamera();
        void Draw(float_t dt);
        void SkipDraw();
        void SetSpeed(float_t speed);

    private:
        void DrawChunkDebug();

    public:
        ScenePtr pScene;
        RenderScenePtr pRenderScene;
        PhysicsScenePtr pPhysicsScene;
        SR_WORLD_NS::SceneBuilder* pSceneBuilder = nullptr;
        CameraPtr pMainCamera = nullptr;
        Engine* pEngine = nullptr;

        float_t m_speed = 1.f;
        float_t m_updateFrequency = 1.f;
        float_t m_accumulator = 1.f;

    };
}

#endif //SRENGINE_ENGINESCENE_H
