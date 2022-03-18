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
        Thread()
            : m_thread(std::thread())
        { }

        explicit Thread(std::thread thread)
            : m_thread(std::move(thread))
        { }

        explicit Thread(const std::function<void()>& fn)
                : m_thread(fn)
        { }

        Thread(Thread&& thread)  noexcept {
            m_thread.swap(thread.m_thread);
        }

        Thread& operator=(Thread&& thread) noexcept {
            m_thread.swap(thread.m_thread);
            return *this;
        }

        ~Thread() {
            SRAssert(!Joinable());
        }

    public:
        [[nodiscard]] bool Joinable() const { return m_thread.joinable(); }
        void Join() { m_thread.join(); }
        bool TryJoin() {
            if (Joinable()) {
                Join();
                return true;
            }

            return false;
        }
        void Detach() { m_thread.detach(); }

        static void Sleep(uint64_t milliseconds);

    private:
        std::thread m_thread;
    };
}

#endif //GAMEENGINE_THREAD_H
