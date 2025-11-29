//
// Created by Monika on 12.04.2024.
//

#ifndef SR_ENGINE_CORE_SUBMIT_STATE_H
#define SR_ENGINE_CORE_SUBMIT_STATE_H

#include <Engine/stdInclude.h>

#include <Utils/TaskManager/ThreadWorker.h>

namespace SR_CORE_NS {
    class SubmitState : public SR_UTILS_NS::ThreadWorkerStateBase {
        SR_CLASS()
        using Super = SR_UTILS_NS::ThreadWorkerStateBase;
    public:
        SR_UTILS_NS::ThreadWorkerResult ExecuteImpl() override;

    };
}

#endif //SR_ENGINE_CORE_SUBMIT_STATE_H
