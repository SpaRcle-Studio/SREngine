//
// Created by Monika on 13.04.2024.
//

#include <Engine/States/DelayedActionsState.h>

#include <Engine/Engine.h>

#include <Codegen/DelayedActionsState.generated.hpp>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult DelayedActionsState::ExecuteImpl() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        auto&& pEngine = GetContext().GetPointer<Engine>();
        if (!pEngine) {
            return SR_UTILS_NS::ThreadWorkerResult::Break;
        }

        while (!m_engineActions.empty()) {
            const auto action = m_engineActions.back();
            m_engineActions.pop_back();
            action(*pEngine);
        }

        m_engineActions = m_newEngineActions;

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }

    void DelayedActionsState::AddEngineAction(const EngineActionCallback& action) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;
        m_engineActions.emplace_back(action);
    }

    void DelayedActionsState::AddNewFrameEngineAction(const EngineActionCallback& action) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;
        m_newEngineActions.emplace_back(action);
    }

    SR_NODISCARD uint64_t DelayedActionsState::GetPendingActionsCount() const noexcept {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;
        return m_engineActions.size() + m_newEngineActions.size();
    }
}