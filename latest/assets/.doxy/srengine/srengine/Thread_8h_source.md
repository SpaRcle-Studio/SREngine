

# File Thread.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**Thread.h**](Thread_8h.md)

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

    class SR_DLL_EXPORT Thread : public NonCopyable {
    public:
        using Ptr = Thread*;
        using ThreadId = SR_UTILS_NS::StringAtom;
        using ThreadsMap = std::unordered_map<ThreadId, Thread::Ptr>;

        SR_FORCE_INLINE static ThreadId EmptyThreadId() {
            static const auto id = SR_UTILS_NS::StringAtom("[EMPTY]");
            return id;
        }

        class SR_DLL_EXPORT Factory : public Singleton<Factory> {
            SR_REGISTER_SINGLETON(Factory)
            friend class Thread;
        protected:
            Factory()
                : Singleton<Factory>()
            { }
            ~Factory() override = default;

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

            template<class Functor, typename... Args> bool Create(Ptr& pThread, Functor&& fn, Args&&... args) {
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

        private:
            friend class Thread::Factory;

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
        SR_NODISCARD bool Joinable() const { return m_thread.joinable(); }
        SR_NODISCARD ThreadId GetId() const;
        SR_NODISCARD DataStorage* GetContext() { return m_context; }

        void SetName(const std::string& name);

        void Synchronize();

        template<class Functor, typename... Args> SR_NODISCARD bool Run(Functor&& fn) {
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

        bool Execute(const SR_HTYPES_NS::Function<bool()>& function) const;

        void Join() {
            SR_LOG("Thead::Join() : join thread \"{}\" with id \"{}\"...", m_name, m_id.c_str());
            m_thread.join();
        }

        bool TryJoin();

        void Free();

        bool HasId() const {
            if (m_id.empty()) {
                return false;
            }

            if (m_id == "0") {
                return false;
            }

            if (m_id == EmptyThreadId()) {
                return false;
            }

            return true;
        }

        void Detach() { m_thread.detach(); }

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
}

#endif //SR_ENGINE_THREAD_H
```


