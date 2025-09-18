//
// Created by Monika on 13.04.2024.
//

#include <Engine/States/StopState.h>

#include <Codegen/StopState.generated.hpp>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult StopState::ExecuteImpl() {
        GetThreadsWorker()->StopAsync();
        return SR_UTILS_NS::ThreadWorkerResult::Break;
    }
}