//
// Created by Monika on 13.04.2024.
//

#ifndef SR_ENGINE_CORE_CHUNK_SYSTEM_STATE_H
#define SR_ENGINE_CORE_CHUNK_SYSTEM_STATE_H

#include <Utils/TaskManager/ThreadWorker.h>
#include <Utils/Types/Timer.h>

namespace SR_CORE_NS {
    class ChunkSystemState : public SR_UTILS_NS::ThreadWorkerStateBase {
        SR_REGISTER_THREAD_STATE(ChunkSystemState)
        using Super = SR_UTILS_NS::ThreadWorkerStateBase;
    public:
        SR_UTILS_NS::ThreadWorkerResult ExecuteImpl() override;

    private:
        SR_HTYPES_NS::Timer m_worldTimer;

    };
}

#endif //SR_ENGINE_CORE_CHUNK_SYSTEM_STATE_H
