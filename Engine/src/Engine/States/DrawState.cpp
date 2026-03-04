//
// Created by Monika on 13.04.2024.
//

#include <Engine/States/DrawState.h>
#include <Engine/Engine.h>
#include <Engine/World/EngineScene.h>

#include <Graphics/Window/Window.h>
#include <Graphics/Pipeline/Pipeline.h>
#include <Graphics/Window/BasicWindowImpl.h>

#include <Codegen/DrawState.generated.hpp>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult DrawState::ExecuteImpl() {
        SR_TRACY_ZONE;

        auto&& pEngine = GetContext().GetPointer<Engine>();
        auto&& pRenderContext = pEngine->GetRenderContext();

        if (pRenderContext) {
            pRenderContext->PrepareFrame();
        }

        auto&& pWindow = pEngine->GetMainWindow();
        if (!pWindow || !pWindow->IsVisible()) {
            return SR_UTILS_NS::ThreadWorkerResult::Break;
        }

        const bool isCollapsed = pWindow->IsWindowCollapsed();

        if (auto&& pRenderScene = pEngine->GetRenderScene(); pRenderScene && !isCollapsed) {
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
            pPipeline->BindCmdBuffer(SR_ID_INVALID);
            if (pPipeline->BeginCmdBuffer()) {
                SR_GRAPH_NS::RenderScene::RenderBlackScreen(pPipeline.Get(), false);
                pPipeline->EndCmdBuffer();
            }
            pPipeline->OnFrameBuildEnd();
        }

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}
