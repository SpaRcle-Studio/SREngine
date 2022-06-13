//
// Created by Monika on 28.01.2022.
//

#ifndef SRENGINE_SEMAPHORE_H
#define SRENGINE_SEMAPHORE_H

#include <Debug.h>

namespace Framework::Helper::Types {
    class SignalSemaphore {
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

#endif //SRENGINE_SEMAPHORE_H
