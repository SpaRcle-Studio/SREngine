//
// Created by Monika on 13.04.2024.
//

#ifndef SR_ENGINE_CORE_DELTA_TIME_STATE_H
#define SR_ENGINE_CORE_DELTA_TIME_STATE_H

#include <Utils/TaskManager/ThreadWorker.h>
#include <Utils/Types/Time.h>

namespace SR_CORE_NS {
    class DeltaTimeState : public SR_UTILS_NS::ThreadWorkerStateBase {
        SR_REGISTER_THREAD_STATE(DeltaTimeState)
        using Super = SR_UTILS_NS::ThreadWorkerStateBase;
    public:
        SR_UTILS_NS::ThreadWorkerResult ExecuteImpl() override;

    private:
        std::optional<SR_UTILS_NS::TimePointType> m_timeStart;

    };
}

#endif //SR_ENGINE_CORE_DELTA_TIME_STATE_H