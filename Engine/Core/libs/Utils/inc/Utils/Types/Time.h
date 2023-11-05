//
// Created by Nikita on 30.12.2020.
//

#ifndef SR_ENGINE_TIME_H
#define SR_ENGINE_TIME_H

#include <Utils/Debug.h>
#include <Utils/Common/Singleton.h>

namespace SR_HTYPES_NS {
    class SR_DLL_EXPORT Time : public Singleton<Time> {
        friend class Singleton<Time>;
    public:
        using ClockT = std::chrono::high_resolution_clock;

    public:
        void Update() {
            m_point = ClockT::now();
            m_clock = clock();
        }

        SR_NODISCARD TimePointType Now() const noexcept { return m_point; }
        SR_NODISCARD uint64_t Count() const noexcept { return m_point.time_since_epoch().count(); }
        SR_NODISCARD float_t FClock() const noexcept { return static_cast<float_t>(Count()) / CLOCKS_PER_SEC / CLOCKS_PER_SEC; }
        SR_NODISCARD clock_t Clock() const noexcept { return m_clock; }

    private:
        TimePointType m_point;
        clock_t m_clock = 0;

    };
}

#endif // SR_ENGINE_TIME_H
