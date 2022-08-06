//
// Created by Monika on 22.07.2022.
//

#ifndef SRENGINE_SAFEPTRLOCKGUARD_H
#define SRENGINE_SAFEPTRLOCKGUARD_H

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

    /// -------------------------------------------------------

    template<typename T> class SafePtrRecursiveLockGuard : NonCopyable {
    public:
        explicit SafePtrRecursiveLockGuard(const T& ptr)
            : m_ptr(ptr)
        {
            m_locked = m_ptr.RecursiveLockIfValid();
        }

        ~SafePtrRecursiveLockGuard() override {
            if (m_locked) {
                m_ptr.Unlock();
            }
        }

    private:
        T m_ptr;
        bool m_locked = false;

    };
}

#endif //SRENGINE_SAFEPTRLOCKGUARD_H
