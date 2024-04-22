//
// Created by Monika on 13.04.2024.
//

#include <Core/States/ChunkSystemState.h>
#include <Core/Engine.h>
#include <Core/World/EngineScene.h>

#include <Graphics/Render/RenderScene.h>
#include <Graphics/Types/Camera.h>

#include <Utils/World/Scene.h>
#include <Utils/World/SceneCubeChunkLogic.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult ChunkSystemState::ExecuteImpl() {
        if (!m_worldTimer.Update()) {
            return SR_UTILS_NS::ThreadWorkerResult::Success;
        }

        auto&& pEngine = GetContext().GetPointer<Engine>();
        auto&& pScene = pEngine->GetScene();
        auto&& pEngineScene = pEngine->GetEngineScene();

        if (!pEngineScene || !pScene) {
            return SR_UTILS_NS::ThreadWorkerResult::Success;
        }

        auto&& pMainCamera = pEngineScene->GetMainCamera();
        if (!pMainCamera) {
            return SR_UTILS_NS::ThreadWorkerResult::Success;
        }

        else if (auto&& gameObject = dynamic_cast<SR_UTILS_NS::GameObject*>(pMainCamera->GetParent())) {
            auto&& pLogic = pScene->GetLogicBase().DynamicCast<SR_WORLD_NS::SceneCubeChunkLogic>();
            if (pLogic && gameObject) {
                pLogic->SetObserver(gameObject);
            }
        }

        pScene->GetLogicBase()->Update(m_worldTimer.GetDeltaTime());

        pEngineScene->UpdateChunkDebug();

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}
