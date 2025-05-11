

# File Semaphore.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**Semaphore.h**](Semaphore_8h.md)

[Go to the documentation of this file](Semaphore_8h.md)


```C++
//
// Created by Monika on 28.01.2022.
//

#ifndef SR_ENGINE_SEMAPHORE_H
#define SR_ENGINE_SEMAPHORE_H

#include <Utils/Debug.h>

namespace SR_HTYPES_NS {
    class SR_COMMON_DLL_API SignalSemaphore {
    public:
        SignalSemaphore()
            : m_lock(false)
        { }

        void Wait() {
            m_lock = true;
            while (m_lock);
        }

        void Signal() {
            m_lock = false;
        }

    private:
        std::atomic<bool> m_lock;

    };
}

#endif //SR_ENGINE_SEMAPHORE_H
```


