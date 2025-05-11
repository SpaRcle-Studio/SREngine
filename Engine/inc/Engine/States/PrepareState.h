//
// Created by Monika on 13.04.2024.
//

#ifndef SR_ENGINE_CORE_PREPARE_STATE_H
#define SR_ENGINE_CORE_PREPARE_STATE_H

#include <Utils/TaskManager/ThreadWorker.h>

namespace SR_CORE_NS {
    class PrepareState : public SR_UTILS_NS::ThreadWorkerStateBase {
        SR_REGISTER_THREAD_STATE(PrepareState)
        using Super = SR_UTILS_NS::ThreadWorkerStateBase;
    public:
        SR_UTILS_NS::ThreadWorkerResult ExecuteImpl() override;

    };
}

#endif //SR_ENGINE_CORE_PREPARE_STATE_H
