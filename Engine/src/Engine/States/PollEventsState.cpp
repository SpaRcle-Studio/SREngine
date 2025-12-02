//
// Created by Monika on 13.04.2024.
//

#include <Engine/States/PollEventsState.h>
#include <Engine/Engine.h>

#include <Graphics/Window/Window.h>

#include <Utils/Types/DataStorage.h>

#include <Codegen/PollEventsState.generated.hpp>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult PollEventsState::ExecuteImpl() {
        auto&& pEngine = GetContext().GetPointer<Engine>();

        if (auto&& pWindow = pEngine->GetMainWindow()) {
            if (!pWindow->IsValid()) {
                SR_SYSTEM_LOG("PollEventsState::ExecuteImpl() : main window is invalid!");
                GetThreadsWorker()->StopAsync();
                return SR_UTILS_NS::ThreadWorkerResult::Break;
            }
            pWindow->PollEvents();
        }

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}