//
// Created by Monika on 12.04.2024.
//

#include <Core/States/SubmitState.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult SubmitState::ExecuteImpl() {
        SR_TRACY_ZONE_N("SubmitState");

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}
