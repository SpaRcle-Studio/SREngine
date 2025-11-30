//
// Created by Monika on 29.11.2025.
//

#ifndef SR_ENGINE_CORE_ENGINE_RUNTIME_SMOKE_TEST_H
#define SR_ENGINE_CORE_ENGINE_RUNTIME_SMOKE_TEST_H

#include <Engine/stdInclude.h>

#include <Utils/Tests/TestManager.h>

namespace SR_CORE_NS {
    class Launcher;
    class DelayedActionsState;
}

namespace SR_CORE_NS::Tests {
    class EngineRuntimeSmokeTest : public SR_UTILS_NS::ITestController {
        SR_CLASS()
        enum class State : uint8_t {
            Initializing,
            PlayMode,
            Completed,
        };
    public:
        SR_UTILS_NS::TestExecutionResult Run() override;

    private:
        SR_HTYPES_NS::SharedPtr<DelayedActionsState> GetDelayedActionState(Launcher* pLauncher);

    private:
        std::atomic<bool> m_hasErrors = false;

    };
}

#endif //SR_ENGINE_CORE_ENGINE_RUNTIME_SMOKE_TEST_H
