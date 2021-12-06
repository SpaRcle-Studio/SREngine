//
// Created by Monika on 17.11.2021.
//

#ifndef GAMEENGINE_THREAD_H
#define GAMEENGINE_THREAD_H

#include <thread>
#include <functional>
#include <atomic>

#include <Debug.h>

namespace Framework::Helper::Types {
    class Thread {
    public:
        explicit Thread(std::thread thread)
            : m_thread(std::move(thread))
        { }

        explicit Thread(const std::function<void()>& fn)
                : m_thread(fn)
        { }

        ~Thread() {
            SRAssert(!Joinable());
        }

    public:
        [[nodiscard]] bool Joinable() const { return m_thread.joinable(); }
        void Join() { m_thread.join(); }
        void TryJoin() {
            if (Joinable())
                Join();
        }
        void Detach() { m_thread.detach(); }

    private:
        std::thread m_thread;
    };
}

#endif //GAMEENGINE_THREAD_H
