//
// Created by Monika on 13.04.2024.
//

#include <Engine/States/DeltaTimeState.h>

#include <Utils/Types/DataStorage.h>

#include <Codegen/DeltaTimeState.generated.hpp>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult DeltaTimeState::ExecuteImpl() {
        SR_HTYPES_NS::Time::Instance().Update();

        const auto now = SR_HTYPES_NS::Time::Instance().Now();

        if (!m_timeStart.has_value()) {
            m_timeStart = now;
        }

        const auto deltaTime = now - m_timeStart.value(); /// nanoseconds
        const auto dt = static_cast<float_t>(deltaTime.count()) / SR_CLOCKS_PER_SEC / SR_CLOCKS_PER_SEC / SR_CLOCKS_PER_SEC; /// Seconds
        m_timeStart = now;

        static const std::string deltaTimeKey = "DeltaTime";
        GetContext().SetValue(deltaTimeKey, dt);

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}