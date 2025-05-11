

# File Thread.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**Thread.h**](Thread_8h.md)

[Go to the documentation of this file](Thread_8h.md)


```C++
//
// Created by Monika on 17.11.2021.
//

#ifndef SR_ENGINE_THREAD_H
#define SR_ENGINE_THREAD_H

#include <Utils/Debug.h>
#include <Utils/Common/ThreadUtils.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Types/Function.h>

#define SR_THREAD_SAFE_CHECKS 1

#define SR_THIS_THREAD (SR_HTYPES_NS::Thread::Factory::Instance().GetThisThread())

#define SR_LOCK_GUARD std::lock_guard<std::recursive_mutex> codegen_lock(m_mutex)
#define SR_LOCK_GUARD_INHERIT(baseClass) std::lock_guard<std::recursive_mutex> codegen_lock(baseClass::m_mutex)
#define SR_SCOPED_LOCK std::lock_guard<std::recursive_mutex> codegen_lock(m_mutex)
#define SR_WRITE_LOCK std::lock_guard<std::shared_mutex> SR_MACRO_CONCAT(codegen_write_lock, SR_LINE)(m_mutex)
#define SR_READ_LOCK std::shared_lock<std::shared_mutex> SR_MACRO_CONCAT(codegen_read_lock, SR_LINE)(m_mutex)

namespace SR_HTYPES_NS {
    class DataStorage;
    class Thread;

    class SR_COMMON_DLL_API Thread : public NonCopyable {
    public:
        using Ptr = Thread*;
        using ThreadId = SR_UTILS_NS::StringAtom;
        using ThreadsMap = std::unordered_map<ThreadId, Thread::Ptr>;

        SR_NODISCARD static ThreadId EmptyThreadId();

        class Factory : public Singleton<Factory> {
            SR_REGISTER_SINGLETON(Factory)
            friend class Thread;
        protected:
            Factory();
            ~Factory() override;

        public:
            void SetMainThread();
            void PrintThreads();

            SR_NODISCARD Ptr GetMainThread();
            SR_NODISCARD Ptr GetThisThread();
            SR_NODISCARD Ptr TryGetThisThread();
            SR_NODISCARD SR_DEPRECATED_EX("Not safe, use Create(Ptr& pThread, Functor&& fn, Args&&... args)") Ptr Create(std::thread thread);
            SR_NODISCARD SR_DEPRECATED_EX("Not safe, use Create(Ptr& pThread, Functor&& fn, Args&&... args)") Ptr Create(const std::function<void()>& fn);
            SR_NODISCARD uint32_t GetThreadsCount();

            SR_NODISCARD Ptr CreateEmpty();

            template<class Functor, typename... Args> bool Create(Ptr& pThread, Functor&& fn, Args&&... args);

        private:
            void Remove(Thread* pThread);

        private:
            ThreadsMap m_threads = ThreadsMap();
            Thread* m_main = nullptr;

        };

    private:
        Thread();

        explicit Thread(std::thread&& thread);
        explicit Thread(ThreadId id);

        ~Thread() override;

    public:
        SR_NODISCARD bool Joinable() const;
        SR_NODISCARD ThreadId GetId() const;
        SR_NODISCARD DataStorage* GetContext();

        void SetName(const std::string& name);

        void Synchronize();

        template<class Functor, typename... Args> SR_NODISCARD bool Run(Functor&& fn);

        bool Execute(const SR_HTYPES_NS::Function<bool()>& function) const;

        void Join();
        bool TryJoin();
        void Free();
        bool HasId() const;
        void Detach();
        void SetPriority(ThreadPriority priority);

        static void Sleep(uint64_t milliseconds);

    private:
        std::thread m_thread;
        ThreadId m_id;
        std::string m_name;
        DataStorage* m_context = nullptr;

        std::atomic<bool> m_nameChanged = false;
        std::atomic<bool> m_isCreated = false;
        std::atomic<bool> m_isRan = false;

        mutable std::shared_mutex m_mutex;
        mutable std::atomic<const SR_HTYPES_NS::Function<bool()>*> m_function = nullptr;
        mutable std::atomic<bool> m_executeResult = false;

    };

    template<class Functor, typename... Args>
    bool Thread::Factory::Create(Thread::Ptr& pThread, Functor&& fn, Args&&... args)  {
        SR_LOCK_GUARD;

        pThread = new Thread();

        std::thread thread([fn = std::forward<Functor>(fn), pThread, argsTuple = std::make_tuple(args...)]() mutable {
            while (!pThread->m_isCreated || !pThread->HasId()) {
                pThread->m_id = SR_UTILS_NS::GetThreadId(pThread->m_thread);
            }

            std::apply(fn, std::forward<decltype(argsTuple)>(argsTuple));
        });

        while (!pThread->HasId()) {
            pThread->m_id = SR_UTILS_NS::GetThreadId(thread);
        }

        m_threads.insert(std::make_pair(pThread->GetId(), pThread));

        pThread->m_thread = std::move(thread);
        pThread->m_isRan = true;
        pThread->m_isCreated = true;

        SR_LOG("Thread::Factory::Create() : creating new \"{}\" thread...", pThread->m_id.c_str());

        return true;
    }

    template<class Functor, typename... Args> bool Thread::Run(Functor &&fn)  {
        if (Joinable()) {
            SRHalt("Thread::Run() : thread is already running!");
            return false;
        }

        Factory::LockSingleton();

        auto&& thread = std::thread([function = std::forward<Functor>(fn), this]() {
            while (!m_isCreated || m_id == "0" || m_id.empty()) {
                m_id = SR_UTILS_NS::GetThreadId(m_thread);
            }
            Factory::Instance().m_threads.insert(std::make_pair(m_id, this));
            SR_LOG("Thread::Run() : run thread \"{}\"",  m_id);
            while (!m_isRan) {
                SR_NOOP;
            }
            function();
        });

        m_thread = std::move(thread);
        SR_LOG("Thread::Run() : thread is moved");
        m_isCreated = true;

        Factory::UnlockSingleton();

        m_isRan = true;

        return true;
    }
}

#endif //SR_ENGINE_THREAD_H
```


