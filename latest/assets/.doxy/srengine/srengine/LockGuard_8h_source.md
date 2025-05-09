

# File LockGuard.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**LockGuard.h**](LockGuard_8h.md)

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


