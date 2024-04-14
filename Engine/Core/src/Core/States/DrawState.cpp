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
            return SR_UTILS_NS::ThreadWorkerResult::Break;
        }

        auto&& pWindow = pEngine->GetMainWindow();
        if (!pWindow || !pWindow->IsVisible()) {
            return SR_UTILS_NS::ThreadWorkerResult::Break;
        }

        auto&& pRenderScene = pEngine->GetRenderScene();
        if (!pRenderScene) {
            return SR_UTILS_NS::ThreadWorkerResult::Break;
        }

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

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}