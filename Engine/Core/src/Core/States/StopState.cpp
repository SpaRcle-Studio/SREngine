//
// Created by Monika on 13.04.2024.
//

#include <Core/States/StopState.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult StopState::ExecuteImpl() {
        GetThreadsWorker()->StopAsync();
        return SR_UTILS_NS::ThreadWorkerResult::Break;
    }
}