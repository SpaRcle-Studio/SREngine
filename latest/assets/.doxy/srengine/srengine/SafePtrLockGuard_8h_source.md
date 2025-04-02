

# File SafePtrLockGuard.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**SafePtrLockGuard.h**](SafePtrLockGuard_8h.md)

[Go to the documentation of this file](SafePtrLockGuard_8h.md)


```C++
//
// Created by Monika on 22.07.2022.
//

#ifndef SR_ENGINE_SAFEPTRLOCKGUARD_H
#define SR_ENGINE_SAFEPTRLOCKGUARD_H

#include <Utils/Common/NonCopyable.h>

namespace SR_HTYPES_NS {
    template<typename T> class SafePtrLockGuard : NonCopyable {
    public:
        explicit SafePtrLockGuard(const T& ptr)
            : m_ptr(ptr)
        {
            m_locked = m_ptr.LockIfValid();
        }

        ~SafePtrLockGuard() override {
            if (m_locked) {
                m_ptr.Unlock();
            }
        }

    private:
        T m_ptr;
        bool m_locked = false;

    };


    template<typename T> class SafePtrRecursiveLockGuard : NonCopyable {
    public:
        explicit SafePtrRecursiveLockGuard(const T& ptr)
            : m_ptr(ptr)
        {
            if constexpr (std::is_pointer_v<T>) {
                m_locked = m_ptr->RecursiveLockIfValid();
            }
            else {
                m_locked = m_ptr.RecursiveLockIfValid();
            }
        }

        ~SafePtrRecursiveLockGuard() override {
            if (!m_locked) {
                return;
            }

            if constexpr (std::is_pointer_v<T>) {
                m_ptr->Unlock();
            }
            else {
                m_ptr.Unlock();
            }
        }

    private:
        T m_ptr;
        bool m_locked = false;

    };


    template<typename T> class SingletonRecursiveLockGuard : NonCopyable {
    public:
        explicit SingletonRecursiveLockGuard(const T& ptr)
            : m_ptr(ptr)
        {
            if constexpr (std::is_pointer_v<T>) {
                m_ptr->LockSingleton();
            }
            else {
                m_ptr.LockSingleton();
            }
        }

        ~SingletonRecursiveLockGuard() override {
            if constexpr (std::is_pointer_v<T>) {
                m_ptr->UnlockSingleton();
            }
            else {
                m_ptr.UnlockSingleton();
            }
        }

    private:
        T m_ptr;

    };
}

#endif //SR_ENGINE_SAFEPTRLOCKGUARD_H
```


