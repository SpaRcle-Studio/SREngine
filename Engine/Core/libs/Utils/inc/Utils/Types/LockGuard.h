//
// Created by Monika on 18.10.2023.
//

#ifndef SRENGINE_LOCKGUARD_H
#define SRENGINE_LOCKGUARD_H

#include <Utils/Common/NonCopyable.h>

namespace SR_HTYPES_NS {
    template<typename T> class SR_DLL_EXPORT LockGuard : public NonCopyable {
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

#endif //SRENGINE_LOCKGUARD_H
