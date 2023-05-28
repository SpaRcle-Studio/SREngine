//
// Created by Monika on 22.05.2023.
//

#include <Core/World/EngineScene.h>
#include <Physics/3D/Raycast3D.h>
#include <Scripting/Impl/EvoScriptManager.h>
#include <Utils/DebugDraw.h>

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

        if (SR_UTILS_NS::Features::Instance().Enabled("Renderer", true)) {
            if (auto&& pContext = pEngine->GetRenderContext(); pContext.LockIfValid()) {
                pRenderScene = pContext->CreateScene(pScene);
                pContext.Unlock();
            }
            else {
                SR_ERROR("InitializeScene() : failed to get window context!");
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
        pScene->GetDataStorage().SetValue(pPhysicsScene);

        pSceneBuilder = pScene->GetSceneBuilder();

        return true;
    }

    void EngineScene::Draw(float_t dt) {
        SR_TRACY_ZONE;

        DrawChunkDebug();

        if (pRenderScene.RecursiveLockIfValid()) {
            SR_UTILS_NS::DebugDraw::Instance().SwitchCallbacks(pRenderScene->GetDebugRenderer());
            pRenderScene.Unlock();
        }

        if (pPhysicsScene.LockIfValid()) {
            SR_PHYSICS_NS::Raycast3D::Instance().SwitchPhysics(pPhysicsScene->Get3DWorld());
            pPhysicsScene.Unlock();
        }

        if (pScene.LockIfValid()) {
            pEngine->GetCmdManager()->Update();

            pScene->GetLogicBase()->PostLoad();

            SR_SCRIPTING_NS::EvoScriptManager::Instance().Update(dt, false);

            pScene->Prepare();

            const bool isPaused = pEngine->IsPaused() || !pEngine->IsActive();

            pSceneBuilder->Build(isPaused);
            pSceneBuilder->Update(dt);

            /// fixed update
            if (m_accumulator >= m_updateFrequency)
            {
                while (m_accumulator >= m_updateFrequency)
                {
                    if (!isPaused && pPhysicsScene.RecursiveLockIfValid()) {
                        pPhysicsScene->FixedUpdate();
                        pPhysicsScene.Unlock();
                    }

                    pEngine->FixedUpdate();

                    pSceneBuilder->FixedUpdate();

                    m_accumulator -= m_updateFrequency;
                }
            }

            m_accumulator += dt;

            pScene.Unlock();
        }

        auto&& pRenderContext = pEngine->GetRenderContext();
        if (pRenderContext.LockIfValid()) {
            pRenderContext->Update();
            pRenderContext.Unlock();
        }

        auto&& pWindow = pEngine->GetWindow();

        if (pWindow->IsVisible() && pRenderScene.RecursiveLockIfValid()) {
            if (auto&& pWin = pWindow->GetImplementation<SR_GRAPH_NS::BasicWindowImpl>()) {
                const bool isOverlay = pRenderScene->IsOverlayEnabled();
                const bool isMaximized = pWin->IsMaximized();
                const bool isHeaderEnabled = pWin->IsHeaderEnabled();

                if (isHeaderEnabled != !isOverlay) {
                    pWin->SetHeaderEnabled(!isOverlay);
                    if (isMaximized) {
                        pWin->Maximize();
                    }
                }
            }

            pRenderScene->Render();
            /// В процессе отрисовки сцена могла быть заменена
            pRenderScene.TryUnlock();
        }
    }

    void EngineScene::SetSpeed(float_t speed) {
        m_speed = speed;
        m_updateFrequency = (1.f / (60.f * m_speed)) * SR_CLOCKS_PER_SEC;
        m_accumulator = m_updateFrequency;
    }

    void EngineScene::SkipDraw() {
        m_accumulator = 0.f;
    }

    void EngineScene::UpdateMainCamera() {
        pMainCamera = pRenderScene.Do<CameraPtr>([](SR_GRAPH_NS::RenderScene* ptr) -> CameraPtr {
            if (auto&& pCamera = ptr->GetMainCamera()) {
                return pCamera;
            }

            return ptr->GetFirstOffScreenCamera();
        }, nullptr);
    }

    void EngineScene::SetActive(bool active) {
        pSceneBuilder->SetDirty();
    }

    void EngineScene::SetPaused(bool pause) {
        pSceneBuilder->SetDirty();
    }

    void EngineScene::SetGameMode(bool gameMode) {
        pRenderScene.Do([gameMode](SR_GRAPH_NS::RenderScene *ptr) {
            ptr->SetOverlayEnabled(!gameMode);
        });
    }

    void EngineScene::DrawChunkDebug() {
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
}