

# File Time.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**Time.h**](Time_8h.md)

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
        void Update() {
            SR_TRACY_ZONE;
            m_timeInfo = TimeInfo {
                ClockT::now(),
                static_cast<uint64_t>(clock())
            };
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
            TimePointType m_point;
            uint64_t m_clock = 0;
        };

        std::atomic<TimeInfo> m_timeInfo;
    };
}

#endif // SR_ENGINE_TIME_H
```


