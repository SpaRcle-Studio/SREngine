

# File Time.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**Time.h**](Time_8h.md)

[Go to the documentation of this file](Time_8h.md)


```C++
//
// Created by Nikita on 30.12.2020.
//

#ifndef SR_ENGINE_TIME_H
#define SR_ENGINE_TIME_H

#include <Utils/Debug.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Profile/TracyContext.h>

namespace SR_HTYPES_NS {
    class Time : public Singleton<Time> {
        SR_REGISTER_SINGLETON(Time)
    public:
        using ClockT = std::chrono::high_resolution_clock;

    public:
        ~Time() override = default;

        void Update() {
            SR_TRACY_ZONE;

            m_timeInfo = TimeInfo(
                ClockT::now(),
                static_cast<uint64_t>(clock())
            );
        }

        SR_NODISCARD TimePointType Now() const noexcept { return m_timeInfo.load().m_point; }
        SR_NODISCARD uint64_t Count() const noexcept { return m_timeInfo.load().m_point.time_since_epoch().count(); }
        SR_NODISCARD float_t FClock() const noexcept { return static_cast<float_t>(Count()) / SR_CLOCKS_PER_SEC / SR_CLOCKS_PER_SEC; }

#ifdef SR_LINUX
        SR_NODISCARD uint64_t Clock() const noexcept { return static_cast<uint64_t>(m_timeInfo.load().m_clock) / SR_CLOCKS_PER_SEC; }
#else
        SR_NODISCARD uint64_t Clock() const noexcept { return static_cast<uint64_t>(m_timeInfo.load().m_clock); }
#endif

    private:
        struct TimeInfo {
            TimeInfo() = default;

            TimeInfo(TimePointType point, uint64_t clock)
                : m_point(point)
                , m_clock(clock)
            { }

            TimeInfo(const TimeInfo& other) = default;
            TimeInfo& operator=(const TimeInfo& other) = default;

            TimePointType m_point = TimePointType();
            uint64_t m_clock = 0;
        };

        std::atomic<TimeInfo> m_timeInfo = TimeInfo();
    };
}

#endif // SR_ENGINE_TIME_H
```


