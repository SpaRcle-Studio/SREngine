//
// Created by Monika on 13.04.2024.
//

#include <Engine/States/DrawState.h>

#include <Graphics/Window/Window.h>
#include <Graphics/Pipeline/Pipeline.h>

#include <Engine/Engine.h>
#include <Engine/World/EngineScene.h>

#include <Codegen/DrawState.generated.hpp>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult DrawState::ExecuteImpl() {
        auto&& pEngine = GetContext().GetPointer<Engine>();
        auto&& pRenderContext = pEngine->GetRenderContext();

        if (pRenderContext) {
            pRenderContext->PrepareFrame();
        }

        auto&& pWindow = pEngine->GetMainWindow();
        if (!pWindow || !pWindow->IsVisible()) {
            return SR_UTILS_NS::ThreadWorkerResult::Break;
        }

        if (auto&& pRenderScene = pEngine->GetRenderScene()) {
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
        }
        else if (auto&& pPipeline = pRenderContext->GetPipeline()) {
            pPipeline->OnFrameBuildBegin();
            SR_GRAPH_NS::RenderScene::RenderBlackScreen(pPipeline.Get(), false);
            pPipeline->OnFrameBuildEnd();
        }

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}
