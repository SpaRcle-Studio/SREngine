//
// Created by Monika on 29.11.2025.
//

#ifndef SR_ENGINE_CORE_DELAYED_ACTIONS_STATE_H
#define SR_ENGINE_CORE_DELAYED_ACTIONS_STATE_H

#include <Engine/stdInclude.h>

#include <Utils/TaskManager/ThreadWorker.h>

namespace SR_CORE_NS {
    class Engine;

    class DelayedActionsState : public SR_UTILS_NS::ThreadWorkerStateBase {
        SR_CLASS()
        using Super = SR_UTILS_NS::ThreadWorkerStateBase;
        using EngineActionCallback = SR_HTYPES_NS::Function<void(SR_CORE_NS::Engine&)>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<DelayedActionsState>;

    public:
        SR_UTILS_NS::ThreadWorkerResult ExecuteImpl() override;

    public:
        void AddEngineAction(const EngineActionCallback& action);
        void AddNewFrameEngineAction(const EngineActionCallback& action);

        SR_NODISCARD uint64_t GetPendingActionsCount() const noexcept;

    private:
        mutable std::recursive_mutex m_mutex;
        std::vector<EngineActionCallback> m_engineActions;
        std::vector<EngineActionCallback> m_newEngineActions;

    };
}

#endif //SR_ENGINE_CORE_DELAYED_ACTIONS_STATE_H
