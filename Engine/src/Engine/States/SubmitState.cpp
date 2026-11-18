//
// Created by Monika on 12.04.2024.
//

#include <Engine/States/SubmitState.h>
#include <Engine/World/EngineScene.h>
#include <Engine/Engine.h>

#include <Graphics/Window/Window.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Pipeline/Pipeline.h>

#include <Utils/Common/StoreUtils.h>

#include <Codegen/SubmitState.generated.hpp>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult SubmitState::ExecuteImpl() {
        Engine::Ptr pEngine = (Engine*)SR_UTILS_NS::StoreUtils::Temp::GetPointer("Engine");

        auto&& pWindow = pEngine->GetMainWindow();
        if (!pWindow || !pWindow->IsVisible()) {
            m_lastFrameTime.reset();
            return SR_UTILS_NS::ThreadWorkerResult::Break;
        }

        if (auto&& pContext = pEngine->GetRenderContext()) {
            const uint32_t framerateLimit = pContext->GetActiveGraphicsSettings().framerateLimit.value_or(0);
            if (framerateLimit > 0) {
                if (m_lastFrameTime.has_value()) {
                    const auto frameDuration = std::chrono::duration_cast<std::chrono::steady_clock::duration>(
                        std::chrono::duration<double_t>(1.0 / static_cast<double_t>(framerateLimit)));
                    const auto deadline = m_lastFrameTime.value() + frameDuration;
                    if (std::chrono::steady_clock::now() < deadline) {
                        SR_TRACY_ZONE_N("Framerate limit");
                        SR_TRACY_ZONE_COLOR(0xFFAA33);
                        while (std::chrono::steady_clock::now() < deadline) {
                            std::this_thread::yield();
                        }
                    }
                }
                m_lastFrameTime = std::chrono::steady_clock::now();
            }
            else {
                m_lastFrameTime.reset();
            }
        }
        else {
            m_lastFrameTime.reset();
        }

        {
            SR_TRACY_ZONE_N("Submit frame");
            if (auto&& pContext = pEngine->GetRenderContext()) {
                pContext->GetPipeline()->DrawFrame();
            }
        }

        if (auto&& pRenderScene = pEngine->GetRenderScene()) {
            static const SR_UTILS_NS::StringAtom deltaTimeKey = "DeltaTime";
            const auto dt = SR_UTILS_NS::StoreUtils::Temp::GetFloat(deltaTimeKey);

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
