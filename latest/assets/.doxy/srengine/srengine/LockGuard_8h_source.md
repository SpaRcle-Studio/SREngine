

# File LockGuard.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**LockGuard.h**](LockGuard_8h.md)

[Go to the documentation of this file](LockGuard_8h.md)


```C++
//
// Created by Monika on 18.10.2023.
//

#ifndef SR_ENGINE_LOCKGUARD_H
#define SR_ENGINE_LOCKGUARD_H

#include <Utils/Common/NonCopyable.h>

namespace SR_HTYPES_NS {
    template<typename T> class SR_COMMON_DLL_API LockGuard : public NonCopyable {
    public:
        explicit LockGuard(T& mutex)
            : m_mutex(mutex)
        {
            m_mutex.lock();
        }

        ~LockGuard() override {
            m_mutex.unlock();
        }

        LockGuard(LockGuard&& other) noexcept = delete;
        LockGuard& operator=(LockGuard&& rhs) noexcept = delete;

    private:
        T& m_mutex;

    };
}

#endif //SR_ENGINE_LOCKGUARD_H
```


