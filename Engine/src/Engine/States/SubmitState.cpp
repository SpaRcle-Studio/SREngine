//
// Created by Monika on 12.04.2024.
//

#include <Engine/States/SubmitState.h>

#include <Graphics/Window/Window.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Pipeline/Pipeline.h>

#include <Engine/Engine.h>
#include <Engine/World/EngineScene.h>

#include <Codegen/SubmitState.generated.hpp>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult SubmitState::ExecuteImpl() {
        auto&& pEngine = GetContext().GetPointer<Engine>();

        {
            SR_TRACY_ZONE_N("Submit frame");
            if (auto&& pContext = pEngine->GetRenderContext()) {
                pContext->GetPipeline()->DrawFrame();
            }
        }

        auto&& pWindow = pEngine->GetMainWindow();
        if (!pWindow || !pWindow->IsVisible()) {
            return SR_UTILS_NS::ThreadWorkerResult::Break;
        }

        if (auto&& pRenderScene = pEngine->GetRenderScene()) {
            const auto dt = GetContext().GetValue<float_t>("DeltaTime");

            const uint8_t frameIndex = pRenderScene->GetPipeline()->GetCurrentImageIndex();
            auto&& buildState = pRenderScene->GetPipeline()->GetBuildState(frameIndex);

            SR_TRACY_PLOT("Draw calls", static_cast<int64_t>(buildState.drawCalls));
            SR_TRACY_PLOT("Vertices", static_cast<int64_t>(buildState.vertices));
            SR_TRACY_PLOT("VMem Transfer", static_cast<int64_t>(buildState.transferredMemory));
            SR_TRACY_PLOT("FPS", static_cast<int64_t>(1.0f / dt));
        }

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}
