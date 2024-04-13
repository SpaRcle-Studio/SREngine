//
// Created by Monika on 13.04.2024.
//

#include <Core/States/DrawState.h>

#include <Graphics/Window/Window.h>

#include <Core/Engine.h>
#include <Core/World/EngineScene.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult DrawState::ExecuteImpl() {
        auto&& pEngine = GetContext().GetPointer<Engine>();
        auto&& pEngineScene = pEngine->GetEngineScene();

        if (!pEngineScene) {
            return SR_UTILS_NS::ThreadWorkerResult::Success;
        }

        auto&& pWindow = pEngine->GetWindow();
        if (!pWindow || !pWindow->IsVisible()) {
            return SR_UTILS_NS::ThreadWorkerResult::Success;
        }




        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}