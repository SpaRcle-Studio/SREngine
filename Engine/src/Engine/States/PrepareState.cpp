//
// Created by Monika on 13.04.2024.
//

#include <Engine/States/PrepareState.h>
#include <Engine/World/EngineScene.h>
#include <Engine/Engine.h>

#include <Physics/3D/Raycast3D.h>
#include <Physics/PhysicsScene.h>

#include <Scripting/Cpp/ScriptSystem.h>

#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/DebugRenderer.h>
#include <Graphics/Pipeline/Pipeline.h>

#include <Utils/CommandManager/CmdManager.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/DebugDraw.h>

#include <Codegen/PrepareState.generated.hpp>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult PrepareState::ExecuteImpl() {
        SR_TRACY_ZONE;

        auto&& pEngine = GetContext().GetPointer<Engine>();

        pEngine->FlushScene();

        //SR_SCRIPTING_NS::EvoScriptManager::Instance().Update(false);

        if (auto&& pRenderContext = pEngine->GetRenderContext()) {
            pRenderContext->Update();
        }

        if (auto&& pRenderScene = pEngine->GetRenderScene()) {
            if (auto&& pDebugRenderer = pRenderScene->GetRenderer<SR_GRAPH_NS::DebugRenderer>()) {
                SR_UTILS_NS::DebugDraw::Instance().SwitchCallbacks(pDebugRenderer);
            }
            if (auto&& pDebugRenderer = pRenderScene->GetRenderer<SR_GRAPH_NS::DebugOverlayRenderer>()) {
                SR_UTILS_NS::DebugOverlayDraw::Instance().SwitchCallbacks(pDebugRenderer);
            }
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

        SR_UTILS_NS::ResourceManager::Instance().PullWatchers();

        if (pEngine->IsNeedReloadResources()) {
            if (auto&& pRenderContext = pEngine->GetRenderContext()) {
                if (auto&& pPipeline = pRenderContext->GetPipeline()) {
                    pPipeline->WaitDeviceIdle();
                    pPipeline->WaitRenderIdle();
                }
            }
            SR_UTILS_NS::ResourceManager::Instance().ReloadResources(dt);
        }

        SR_SCRIPTING_NS::ScriptSystem::Instance().ReloadModulesIfNeeded();

        pEngine->ProcessInput();

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}
