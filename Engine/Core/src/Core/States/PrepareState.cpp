//
// Created by Monika on 13.04.2024.
//

#include <Core/States/PrepareState.h>
#include <Core/World/EngineScene.h>
#include <Core/Engine.h>

#include <Scripting/Impl/EvoScriptManager.h>

#include <Physics/3D/Raycast3D.h>
#include <Physics/PhysicsScene.h>

#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/DebugRenderer.h>

#include <Utils/CommandManager/CmdManager.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/DebugDraw.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult PrepareState::ExecuteImpl() {
        auto&& pEngine = GetContext().GetPointer<Engine>();

        pEngine->FlushScene();

        SR_SCRIPTING_NS::EvoScriptManager::Instance().Update(false);

        if (auto&& pRenderContext = pEngine->GetRenderContext()) {
            pRenderContext->Update();
        }

        if (auto&& pRenderScene = pEngine->GetRenderScene()) {
            SR_UTILS_NS::DebugDraw::Instance().SwitchCallbacks(pRenderScene->GetDebugRenderer());
        }

        if (auto&& pPhysicsScene = pEngine->GetPhysicsScene()) {
            SR_PHYSICS_NS::Raycast3D::Instance().SwitchPhysics(pPhysicsScene->Get3DWorld());
        }

        if (auto&& pCommandManager = pEngine->GetCmdManager()) {
            pCommandManager->Update();
        }

        if (auto&& pEngineScene = pEngine->GetEngineScene()) {
            pEngineScene->UpdateMainCamera();
        }

        const auto dt = GetContext().GetValue<float_t>("DeltaTime");

        SR_UTILS_NS::ResourceManager::Instance().UpdateWatchers(dt);

        if (pEngine->IsNeedReloadResources()) {
            SR_UTILS_NS::ResourceManager::Instance().ReloadResources(dt);
        }

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}
