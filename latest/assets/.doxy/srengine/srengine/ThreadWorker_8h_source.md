

# File ThreadWorker.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**TaskManager**](dir_0825f073fd7f240c8cad7fad96459c9f.md) **>** [**ThreadWorker.h**](ThreadWorker_8h.md)

[Go to the documentation of this file](ThreadWorker_8h.md)


```C++
//
// Created by Monika on 10.04.2024.
//

#ifndef SR_ENGINE_UTILS_THREAD_WORKER_H
#define SR_ENGINE_UTILS_THREAD_WORKER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Serialization/Serializable.h>
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

    class ThreadWorkerStateBase : public SR_HTYPES_NS::SharedPtr<ThreadWorkerStateBase>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<ThreadWorkerStateBase>;
        SR_CLASS()
    public:
        ThreadWorkerStateBase();
        virtual ~ThreadWorkerStateBase() = default;

        void AddStartCondition(SR_UTILS_NS::StringAtom name, ThreadWorkerState state);
        void AddFinishCondition(SR_UTILS_NS::StringAtom name, ThreadWorkerState state);
        void AddSkipCondition(SR_UTILS_NS::StringAtom name, ThreadWorkerState state);

        ThreadWorkerResult Execute();
        void Finalize();

        void SetThreadWorker(ThreadWorker* pThreadWorker) { m_threadWorker = pThreadWorker; }

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
}

#endif //SR_ENGINE_UTILS_THREAD_WORKER_H
```


