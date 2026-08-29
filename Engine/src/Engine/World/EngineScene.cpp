//
// Created by Monika on 22.05.2023.
//

#include <Engine/Engine.h>
#include <Engine/World/EngineScene.h>
#include <Engine/GUI/EditorGUI.h>

#include <Physics/3D/Raycast3D.h>

#include <Scripting/Cpp/ScriptSystem.h>

#include <Graphics/Types/Camera.h>

#include <Utils/DebugDraw.h>
#include <Utils/Common/Features.h>
#include <Utils/Common/ToString.h>
#include <Utils/World/SceneCubeChunkLogic.h>
#include <Utils/Events/Broadcaster.h>

namespace SR_CORE_NS {
    EngineScene::EngineScene(const EngineScene::ScenePtr& pScene, Engine* pEngine)
        : Super()
        , pEngine(pEngine)
        , pScene(pScene)
    { }

    EngineScene::~EngineScene() {
        if (pRenderScene) {
            pRenderScene->Remove(pEngine->GetEditor());
            pRenderScene->Remove(&SR_GRAPH_NS::GUI::GlobalWidgetManager::Instance());
        }

        if (pScene) {
            pScene->Destroy();
        }

        pPhysicsScene.AutoFree([](SR_PHYSICS_NS::PhysicsScene* pData) {
            delete pData;
        });

        pScene.AutoFree();
    }

    bool EngineScene::Init() {
        SetSpeed(1.f);

        SRAssert(pScene);

        pScene->Init();

        m_accumulateDt = SR_UTILS_NS::Features::Instance().Enabled("AccumulateDt", true);

        if (SR_UTILS_NS::Features::Instance().Enabled("Renderer", true)) {
            auto&& pContext = pEngine->GetRenderContext();
            if (!pContext) {
                SR_ERROR("EngineScene::Init() : failed to get render context!");
                return false;
            }

            pRenderScene = pContext->CreateScene(pScene);

            if (pRenderScene) {
                pRenderScene->SetTechnique(pContext->GetSettings().overlayRenderTechnique);

                if (pEngine->GetEditor()) {
                    pRenderScene->Register(pEngine->GetEditor());
                }
                pRenderScene->Register(&Graphics::GUI::GlobalWidgetManager::Instance());

                if (pEngine->GetEditor()) {
                    pRenderScene->SetOverlayEnabled(pEngine->GetEditor()->Enabled());
                }
            }
        }

        if (SR_UTILS_NS::Features::Instance().Enabled("Physics", true)) {
            pPhysicsScene = new SR_PHYSICS_NS::PhysicsScene(pScene);

            if (!pPhysicsScene->Init()) {
                SR_ERROR("InitializeScene() : failed to initialize physics scene!");
                SR_ERROR("InitializeScene() : will work without physics!");
            }
        }

        pScene->GetDataStorage().SetValue(pRenderScene);
        pScene->GetDataStorage().SetPointer(pRenderScene.Get());
        pScene->GetDataStorage().SetValue(pPhysicsScene);

        pSceneUpdater = pScene->GetSceneUpdater();

        return true;
    }

    void EngineScene::SetSpeed(float_t speed) {
        m_speed = speed;
        if (pScene) {
            pScene->SetSpeed(m_speed);
        }
        UpdateFrequency();
        m_accumulator = m_updateFrequency;
    }

    void EngineScene::UpdateMainCamera() {
        SR_TRACY_ZONE;
        if (pRenderScene) {
            pMainCamera = pRenderScene->GetMainCamera();
        }
    }

    void EngineScene::SetActive(bool active) {
        pSceneUpdater->SetDirty();
    }

    void EngineScene::SetPaused(bool pause) {
        pSceneUpdater->SetDirty();
    }

    void EngineScene::SetGameMode(bool gameMode) {
        if (pRenderScene) {
            pRenderScene->SetOverlayEnabled(!gameMode);
        }

        if (pPhysicsScene) {
            pPhysicsScene->SetIsGameMode(gameMode);
        }
    }

    void EngineScene::UpdateChunkDebug() {
        SR_TRACY_ZONE;

        if (auto&& pEditor = pEngine->GetEditor(); !pEditor || !pEditor->Enabled()) {
            return;
        }

        /// if (!EditorSettings::Instance().IsNeedDebugChunks()) {
        ///     return;
        /// }

        if (!pScene) {
            return;
        }

        //if (auto&& pLogic = pScene->GetLogicBase().DynamicCast<SR_WORLD_NS::SceneCubeChunkLogic>()) {
        //    pLogic->UpdateDebug();
        //}
    }

    void EngineScene::UpdateFrequency() {
        const uint32_t framesPerSecond = 60;
        m_updateFrequency = (1.f / (static_cast<float_t>(framesPerSecond) * m_speed));
        SR_HTYPES_NS::Time::Instance().SetFixedDeltaTime(m_updateFrequency);
    }

    void EngineScene::FixedStep(bool isPaused) {
        SR_TRACY_ZONE;
        SR_TRACY_ZONE_VALUE(m_accumulator);

        if (!isPaused && pPhysicsScene) {
            pPhysicsScene->FixedUpdate();
        }

        pEngine->FixedUpdate();

        pSceneUpdater->FixedUpdate(isPaused);
    }

    void EngineScene::Update(float_t dt) {
        SR_TRACY_ZONE;

        if (dt < 0.f) {
            SR_WARN("EngineScene::Update() : delta time is negative! Reset it... dt: {}", dt);
            dt = 0.f;
        }

        pScene->GetLogicBase()->Prepare();
        pScene->Prepare();

        static const SR_UTILS_NS::StringAtom editorModeKey = "EditorMode";
        pScene->GetDataStorage().SetValue<bool>(editorModeKey, pEngine->GetEditor() && pEngine->GetEditor()->Enabled());

        const bool isPaused = pEngine->IsPaused() || !pEngine->IsActive() || pEngine->HasSceneInQueue();

        pSceneUpdater->Build(isPaused);
        pSceneUpdater->Update(dt * m_speed, isPaused);

        SR_UTILS_NS::Broadcaster::Instance().Broadcast(SR_UTILS_NS::Events::EVENT_ON_ENGINE_UPDATE_ID);

        UpdateFrequency();

        if (m_accumulateDt) {
            m_accumulator += dt;
        }
        else {
            m_accumulator += SR_MIN(dt, m_updateFrequency);
        }

        constexpr float_t maxDeltaTime = 60.f; /// seconds
        if (m_accumulator > maxDeltaTime) {
            SR_WARN("EngineScene::Update() : delta time is too big! Reset it... Accumulator: {}. Max delta time: {}", m_accumulator, maxDeltaTime);
            m_accumulator = 0.f;
        }

        if (m_accumulator < 0.f) {
            SR_WARN("EngineScene::Update() : delta time is negative! Reset it... Accumulator: {}", m_accumulator);
            m_accumulator = 0.f;
        }

        const auto steps = static_cast<uint32_t>(m_accumulator / m_updateFrequency);
        auto&& mouseDeltaOriginal = SR_UTILS_NS::Input::Instance().GetMouseDrag();
        if (steps > 0) {
            SR_MATH_NS::FVector2 mouseDelta = (m_mouseDragAccumulator + mouseDeltaOriginal) / static_cast<float_t>(steps);
            SR_UTILS_NS::Input::Instance().SetMouseDrag(mouseDelta);

            /// fixed update
            if (m_accumulator >= m_updateFrequency)
            {
                while (m_accumulator >= m_updateFrequency)
                {
                    FixedStep(isPaused);
                    m_accumulator -= m_updateFrequency;
                }
            }
            SR_UTILS_NS::Input::Instance().SetMouseDrag(mouseDeltaOriginal);
            m_mouseDragAccumulator = {};
        }
        else {
            m_mouseDragAccumulator += mouseDeltaOriginal;
        }

        pSceneUpdater->LateUpdate(isPaused);

        pEngine->SetOneFramePauseSkip(false);
    }
}
