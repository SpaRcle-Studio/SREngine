//
// Created by Monika on 17.11.2021.
//

#ifndef GAMEENGINE_THREAD_H
#define GAMEENGINE_THREAD_H

#include <Debug.h>
#include <Utils/ThreadUtils.h>
#include <Utils/Singleton.h>
#include <Types/DataStorage.h>

namespace SR_HTYPES_NS {
    class Thread : public NonCopyable {
    public:
        using Ptr = Thread*;
        using ThreadId = std::string;
        using ThreadsMap = std::unordered_map<ThreadId, Thread::Ptr>;
        using Mutex = std::mutex;

        class Factory : public Singleton<Factory> {
            friend class Singleton<Factory>;
            friend class Thread;
        protected:
            ~Factory() override = default;

        public:
            SR_NODISCARD Ptr GetMainThread();
            SR_NODISCARD Ptr GetThisThread();
            SR_NODISCARD Ptr Create(std::thread thread);
            SR_NODISCARD Ptr Create(const std::function<void()>& fn);
            SR_NODISCARD uint32_t GetThreadsCount();

            template<class Functor, typename... Args> SR_NODISCARD Ptr Create(Functor&& fn, Args&&... args) {
                std::thread thread(fn, std::forward<Args>(args)...);
                return Create(std::move(thread));
            }

        private:
            void Remove(Thread* pThread);

        private:
            Mutex m_mutex = Mutex();
            ThreadsMap m_threads = ThreadsMap();

        };

    private:
        Thread()
            : Thread(std::thread())
        { }

        explicit Thread(std::thread&& thread);

        ~Thread() override {
            SRAssert(!Joinable());
            delete m_context;
        }

    public:
        SR_NODISCARD bool Joinable() const { return m_thread.joinable(); }
        SR_NODISCARD ThreadId GetId();
        SR_NODISCARD DataStorage::Ptr GetContext() { return m_context; }

        void Join() { m_thread.join(); }
        bool TryJoin();

        void Free();

        void Detach() { m_thread.detach(); }

        void SetPriority(ThreadPriority priority);

        static void Sleep(uint64_t milliseconds);

    private:
        std::thread m_thread;
        ThreadId m_id;
        DataStorage::Ptr m_context;

    };
}

#define SR_THIS_THREAD (SR_HTYPES_NS::Thread::Factory::Instance().GetThisThread())

#define SR_LOCK_GUARD std::lock_guard<std::recursive_mutex> codegen_lock(m_mutex);

#endif //GAMEENGINE_THREAD_H
