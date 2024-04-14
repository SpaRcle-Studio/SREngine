//
// Created by Monika on 10.04.2024.
//

#include <Core/States/SceneUpdateState.h>
#include <Core/Engine.h>
#include <Core/World/EngineScene.h>

#include <Graphics/Render/RenderScene.h>

#include <Utils/World/Scene.h>
#include <Utils/World/SceneLogic.h>
#include <Utils/DebugDraw.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult SceneUpdateState::ExecuteImpl() {
        SR_TRACY_ZONE_N("SceneUpdateState");

        const auto dt = GetContext().GetValue<float_t>("DeltaTime");

        auto&& pEngine = GetContext().GetPointer<Engine>();
        if (auto&& pEngineScene = pEngine->GetEngineScene()) {
            pEngineScene->Update(dt);
        }

        if (auto&& pEditor = pEngine->GetEditor(); pEditor && pEngine->IsApplicationFocused()) {
            pEditor->Update(dt);
        }

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}
