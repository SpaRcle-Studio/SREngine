//
// Created by Monika on 13.04.2024.
//

#include <Core/States/PrepareState.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult PrepareState::ExecuteImpl() {
        SR_TRACY_ZONE_N("PrepareState");

        auto&& pEngine = GetContext().GetPointer<Engine>();

        pEngine->FlushScene();

        SR_SCRIPTING_NS::EvoScriptManager::Instance().Update(false);

        if (auto&& pRenderScene = pEngine->GetRenderScene()) {
            SR_UTILS_NS::DebugDraw::Instance().SwitchCallbacks(pRenderScene->GetDebugRenderer());
        }

        if (auto&& pPhysicsScene = pEngine->GetPhysicsScene()) {
            SR_PHYSICS_NS::Raycast3D::Instance().SwitchPhysics(pPhysicsScene->Get3DWorld());
        }

        if (auto&& pCommandManager = pEngine->GetCmdManager()) {
            pCommandManager->Update();
        }

        const auto dt = GetContext().GetValue<float_t>("DeltaTime");

        SR_UTILS_NS::ResourceManager::Instance().UpdateWatchers(dt);

        if (pEngine->IsNeedReloadResources()) {
            SR_UTILS_NS::ResourceManager::Instance().ReloadResources(dt);
        }

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}
