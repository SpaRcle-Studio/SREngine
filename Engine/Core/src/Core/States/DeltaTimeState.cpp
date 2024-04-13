//
// Created by Monika on 13.04.2024.
//

#include <Core/States/DeltaTimeState.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult DeltaTimeState::ExecuteImpl() {
        SR_HTYPES_NS::Time::Instance().Update();

        const auto now = SR_HTYPES_NS::Time::Instance().Now();
        const auto deltaTime = now - m_timeStart; /// nanoseconds
        const auto dt = static_cast<float_t>(deltaTime.count()) / SR_CLOCKS_PER_SEC / SR_CLOCKS_PER_SEC / SR_CLOCKS_PER_SEC; /// Seconds
        m_timeStart = now;

        GetContext().SetValue("DeltaTime", dt);

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}