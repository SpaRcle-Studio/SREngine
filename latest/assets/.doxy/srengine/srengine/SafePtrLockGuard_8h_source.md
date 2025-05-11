

# File SafePtrLockGuard.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**SafePtrLockGuard.h**](SafePtrLockGuard_8h.md)

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


