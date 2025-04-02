

# File ThreadWorker.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**TaskManager**](dir_13d04ea2f847395a194669a63cd5046e.md) **>** [**ThreadWorker.h**](ThreadWorker_8h.md)

[Go to the documentation of this file](ThreadWorker_8h.md)


```C++
//
// Created by Monika on 10.04.2024.
//

#ifndef SR_ENGINE_UTILS_THREAD_WORKER_H
#define SR_ENGINE_UTILS_THREAD_WORKER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/StringAtom.h>
#include <Utils/FileSystem/Path.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(ThreadWorkerState, uint8_t,
        Idle, Working, Ready
    );

    SR_ENUM_NS_CLASS_T(ThreadWorkerResult, uint8_t,
        Success, Working, Repeat, Break
    );

    class ThreadsWorker;
    class ThreadWorker;

    class ThreadWorkerStateBase : public SR_HTYPES_NS::SharedPtr<ThreadWorkerStateBase> {
        using Super = SR_HTYPES_NS::SharedPtr<ThreadWorkerStateBase>;
    public:
        ThreadWorkerStateBase();
        virtual ~ThreadWorkerStateBase() = default;

        void AddStartCondition(SR_UTILS_NS::StringAtom name, ThreadWorkerState state);
        void AddFinishCondition(SR_UTILS_NS::StringAtom name, ThreadWorkerState state);
        void AddSkipCondition(SR_UTILS_NS::StringAtom name, ThreadWorkerState state);

        ThreadWorkerResult Execute();
        void Finalize();

        void SetThreadWorker(ThreadWorker* pThreadWorker) { m_threadWorker = pThreadWorker; }

        virtual StringAtom GetName() const = 0;

        SR_NODISCARD ThreadWorker* GetThreadWorker() const { return m_threadWorker; }
        SR_NODISCARD ThreadsWorker* GetThreadsWorker() const;
        SR_NODISCARD ThreadWorkerState GetState() const { return m_state; }
        SR_NODISCARD SR_HTYPES_NS::DataStorage& GetContext();

    protected:
        virtual ThreadWorkerResult ExecuteImpl() = 0;
        virtual void FinalizeImpl() { }

    private:
        ThreadWorker* m_threadWorker = nullptr;
        std::atomic<ThreadWorkerState> m_state = ThreadWorkerState::Idle;
        std::map<SR_UTILS_NS::StringAtom, ThreadWorkerState> m_skipConditions;
        std::map<SR_UTILS_NS::StringAtom, ThreadWorkerState> m_startConditions;
        std::map<SR_UTILS_NS::StringAtom, ThreadWorkerState> m_finishConditions;

    };

    class ThreadWorker final : public SR_HTYPES_NS::SharedPtr<ThreadWorker> {
        using Super = SR_HTYPES_NS::SharedPtr<ThreadWorker>;
    public:
        explicit ThreadWorker(std::string name);

        void AddState(ThreadWorkerStateBase::Ptr pState);

        void SetThreadsWorker(ThreadsWorker* pThreadsWorker) { m_threadsWorker = pThreadsWorker; }

        void Start();
        void Stop();

        SR_NODISCARD ThreadsWorker* GetThreadsWorker() const { return m_threadsWorker; }
        SR_NODISCARD const std::vector<ThreadWorkerStateBase::Ptr>& GetStates() const { return m_states; }

    private:
        void Work();
        void Update();

    private:
        ThreadsWorker* m_threadsWorker = nullptr;
        SR_HTYPES_NS::Thread::Ptr m_thread = nullptr;
        std::vector<ThreadWorkerStateBase::Ptr> m_states;
        uint32_t m_currentState = 0;
        std::string m_name;
        std::atomic<bool> m_isActive = false;

    };

    class ThreadsWorker final : public SR_HTYPES_NS::SharedPtr<ThreadsWorker> {
        using Super = SR_HTYPES_NS::SharedPtr<ThreadsWorker>;
    private:
        ThreadsWorker();

    public:
        SR_NODISCARD static ThreadsWorker::Ptr Load(const SR_UTILS_NS::Path& path);

        SR_NODISCARD ThreadWorkerState GetState(SR_UTILS_NS::StringAtom name) const;
        SR_NODISCARD bool IsActive() const { return m_isActive; }
        SR_NODISCARD SR_HTYPES_NS::DataStorage& GetContext() { return m_context; }
        SR_NODISCARD bool IsAlive() const;

        void AddThread(ThreadWorker::Ptr pThread);

        void Start();
        void Stop();
        void StopAsync() { m_isAlive = false; }

        SR_NODISCARD bool CheckFinalize(SR_UTILS_NS::StringAtom name);

    private:
        std::map<SR_UTILS_NS::StringAtom, ThreadWorkerStateBase::Ptr> m_states;
        std::list<SR_UTILS_NS::StringAtom> m_finalize;
        std::vector<ThreadWorker::Ptr> m_threadWorkers;
        bool m_isActive = false;
        std::atomic<bool> m_isAlive = true;
        SR_HTYPES_NS::DataStorage m_context;
        std::recursive_mutex m_mutex;

    };

    class ThreadWorkerStateRegistration final : public SR_UTILS_NS::Singleton<ThreadWorkerStateRegistration> {
        SR_REGISTER_SINGLETON(ThreadWorkerStateRegistration)
        using AllocateFn = SR_HTYPES_NS::Function<ThreadWorkerStateBase::Ptr()>;
    public:
        bool IsSingletonCanBeDestroyed() const override { return false; }

        bool RegisterState(SR_UTILS_NS::StringAtom name, AllocateFn&& allocateFn);

        SR_NODISCARD ThreadWorkerStateBase::Ptr AllocateState(SR_UTILS_NS::StringAtom name);

    private:
        std::map<SR_UTILS_NS::StringAtom, AllocateFn> m_states;

    };
}

#define SR_REGISTER_THREAD_STATE(name) \
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_CODEGEN_REGISTER_THREAD_STATE_NAME_##name =                             \
        [str = std::string(#name)]() {                                                                                  \
            const size_t index = str.find("State");                                                                     \
            if (index == std::string::npos) {                                                                           \
                std::cerr << "ThreadWorkerStateRegistration error: " << str << std::endl;                               \
                return std::string();                                                                                   \
            }                                                                                                           \
            return str.substr(0, index);                                                                                \
        }();                                                                                                            \
    static SR_UTILS_NS::ThreadWorkerStateBase::Ptr SR_CODEGEN_REGISTER_THREAD_STATE_ALLOCATE_##name() {                 \
        return dynamic_cast<SR_UTILS_NS::ThreadWorkerStateBase*>(new name());                                           \
    }                                                                                                                   \
    SR_INLINE_STATIC const bool SR_CODEGEN_REGISTER_THREAD_STATE_##name =                                               \
        SR_UTILS_NS::ThreadWorkerStateRegistration::Instance().RegisterState(                                           \
        SR_CODEGEN_REGISTER_THREAD_STATE_NAME_##name,                                                                   \
        []() {                                                                                                          \
            return SR_CODEGEN_REGISTER_THREAD_STATE_ALLOCATE_##name();                                                  \
        });                                                                                                             \
    SR_NODISCARD SR_UTILS_NS::StringAtom GetName() const final { return SR_CODEGEN_REGISTER_THREAD_STATE_NAME_##name; } \

#endif //SR_ENGINE_UTILS_THREAD_WORKER_H
```


