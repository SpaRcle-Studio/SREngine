//
// Created by Monika on 22.05.2023.
//

#include <Core/World/EngineScene.h>
#include <Core/GUI/EditorGUI.h>

#include <Physics/3D/Raycast3D.h>

#include <Scripting/Impl/EvoScriptManager.h>

#include <Graphics/Types/Camera.h>

#include <Utils/DebugDraw.h>
#include <Utils/Common/Features.h>
#include <Utils/World/SceneCubeChunkLogic.h>

namespace SR_CORE_NS {
    EngineScene::EngineScene(const EngineScene::ScenePtr& pScene, Engine* pEngine)
        : Super()
        , pEngine(pEngine)
        , pScene(pScene)
    { }

    EngineScene::~EngineScene() {
        pRenderScene.Do([this](SR_GRAPH_NS::RenderScene* pData) {
            pData->Remove(pEngine->GetEditor());
            pData->Remove(&SR_GRAPH_NS::GUI::GlobalWidgetManager::Instance());
        });

        pScene.AutoFree([](SR_WORLD_NS::Scene* pData) {
            pData->Destroy();
            delete pData;
        });

        pPhysicsScene.AutoFree([](SR_PHYSICS_NS::PhysicsScene* pData) {
            delete pData;
        });
    }

    bool EngineScene::Init() {
        SetSpeed(1.f);

        SRAssert(pScene);

        pScene->Init();

        m_accumulateDt = SR_UTILS_NS::Features::Instance().Enabled("AccumulateDt", true);

        if (SR_UTILS_NS::Features::Instance().Enabled("Renderer", true)) {
            if (auto&& pContext = pEngine->GetRenderContext(); pContext.LockIfValid()) {
                pRenderScene = pContext->CreateScene(pScene);
                pContext.Unlock();
            }
            else {
                SR_ERROR("EngineScene::Init() : failed to get render context!");
                return false;
            }

            if (pRenderScene) {
                pRenderScene->SetTechnique("Editor/Configs/OverlayRenderTechnique.xml");

                pRenderScene->Register(pEngine->GetEditor());
                pRenderScene->Register(&Graphics::GUI::GlobalWidgetManager::Instance());

                pRenderScene->SetOverlayEnabled(pEngine->GetEditor()->Enabled());
            }
        }

        if (SR_UTILS_NS::Features::Instance().Enabled("Physics", true)) {
            pPhysicsScene = new SR_PHYSICS_NS::PhysicsScene(pScene);

            if (!pPhysicsScene->Init()) {
                SR_ERROR("InitializeScene() : failed to initialize physics scene!");
                return false;
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
        UpdateFrequency();
        m_accumulator = m_updateFrequency;
    }

    void EngineScene::SkipDraw() {
        m_accumulator = 0.f;
    }

    void EngineScene::UpdateMainCamera() {
        SR_TRACY_ZONE;
        pMainCamera = pRenderScene.Do<SR_GTYPES_NS::Camera::Ptr>([](SR_GRAPH_NS::RenderScene* ptr) -> SR_GTYPES_NS::Camera::Ptr {
            return ptr->GetMainCamera();
        }, SR_GTYPES_NS::Camera::Ptr());
    }

    void EngineScene::SetActive(bool active) {
        pSceneUpdater->SetDirty();
    }

    void EngineScene::SetPaused(bool pause) {
        pSceneUpdater->SetDirty();
    }

    void EngineScene::SetGameMode(bool gameMode) {
        pRenderScene.Do([gameMode](SR_GRAPH_NS::RenderScene *ptr) {
            ptr->SetOverlayEnabled(!gameMode);
        });
    }

    void EngineScene::UpdateChunkDebug() {
        SR_TRACY_ZONE;

        if (auto&& pEditor = pEngine->GetEditor(); !pEditor || !pEditor->Enabled()) {
            return;
        }

        if (!EditorSettings::Instance().IsNeedDebugChunks()) {
            return;
        }

        if (!pScene.LockIfValid()) {
            return;
        }

        if (auto&& pLogic = pScene->GetLogicBase().DynamicCast<SR_WORLD_NS::SceneCubeChunkLogic>()) {
            pLogic->UpdateDebug();
        }

        pScene.Unlock();
    }

    void EngineScene::UpdateFrequency() {
        const uint32_t framesPerSecond = 60;
        m_updateFrequency = (1.f / (static_cast<float_t>(framesPerSecond) * m_speed));
    }

    void EngineScene::FixedStep(bool isPaused) {
        SR_TRACY_ZONE;
        SR_TRACY_ZONE_TEXT(SR_UTILS_NS::ToString(m_accumulator));

        if (!isPaused && pPhysicsScene) {
            pPhysicsScene->FixedUpdate();
        }

        pEngine->FixedUpdate();

        pSceneUpdater->FixedUpdate(isPaused);
    }

    void EngineScene::Update(float_t dt) {
        SR_TRACY_ZONE;

        pScene->GetLogicBase()->PostLoad();
        pScene->Prepare();

        const bool isPaused = pEngine->IsPaused() || !pEngine->IsActive() || pEngine->HasSceneInQueue();

        pSceneUpdater->Build(isPaused);
        pSceneUpdater->Update(dt, isPaused);

        UpdateFrequency();

        if (m_accumulateDt) {
            m_accumulator += dt;
        }
        else {
            m_accumulator += SR_MIN(dt, m_updateFrequency);
        }

        /// fixed update
        if (m_accumulator >= m_updateFrequency)
        {
            while (m_accumulator >= m_updateFrequency)
            {
                FixedStep(isPaused);
                m_accumulator -= m_updateFrequency;
            }
        }

        pEngine->SetOneFramePauseSkip(false);
    }
}