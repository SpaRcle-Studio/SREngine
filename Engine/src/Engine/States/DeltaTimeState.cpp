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

        auto delta = now - m_timeStart.value();
        float_t dt = std::chrono::duration<float_t>(delta).count();

        /// ограничение dt, чтобы не было слишком больших скачков
        dt = std::min(dt, 0.1f);

        m_timeStart = now;

        static const SR_UTILS_NS::StringAtom deltaTimeKey = "DeltaTime";
        GetContext().SetValue(deltaTimeKey, dt);

        SR_HTYPES_NS::Time::Instance().SetDeltaTime(dt);

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }
}