

# File Semaphore.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**Semaphore.h**](Semaphore_8h.md)

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


