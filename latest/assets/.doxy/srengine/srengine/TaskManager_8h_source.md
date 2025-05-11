

# File TaskManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**TaskManager**](dir_0825f073fd7f240c8cad7fad96459c9f.md) **>** [**TaskManager.h**](TaskManager_8h.md)

[Go to the documentation of this file](TaskManager_8h.md)


```C++
//
// Created by Monika on 19.03.2022.
//

#ifndef SR_ENGINE_TASKMANAGER_H
#define SR_ENGINE_TASKMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/Function.h>

namespace SR_UTILS_NS {
    class SR_COMMON_DLL_API Task : public NonCopyable {
    public:
        enum class State {
            Unknown, Waiting, Launched, Stopped, Completed, Failed
        };
        using StatePtr = std::atomic<State>*;

        using TaskFn = SR_HTYPES_NS::Function<void(StatePtr)>;

    public:
        explicit Task(TaskFn fn, bool createThread);
        Task(Task&& task) noexcept;
        Task& operator=(Task&& task) noexcept;

        ~Task() override;

    public:
        bool Run();
        bool Stop();

        void SetId(uint64_t id);

        SR_NODISCARD bool IsCompleted() const;
        SR_NODISCARD bool IsWaiting() const;
        SR_NODISCARD State GetResult() const;
        SR_NODISCARD uint64_t GetId() const;

    private:
        bool m_createThread;
        uint64_t m_id;
        Types::Thread::Ptr m_thread;
        TaskFn m_function;
        StatePtr m_state;

    };

    class SR_COMMON_DLL_API TaskManager : public Singleton<TaskManager> {
        SR_REGISTER_SINGLETON(TaskManager)
        using TaskFn = SR_HTYPES_NS::Function<void(std::atomic<Task::State>*)>;
        using TaskId = uint64_t;
    public:
        ~TaskManager() override;

    public:
        TaskId Execute(Task&& task);
        TaskId Execute(const TaskFn& function, bool createThread = false);

        Task::State GetResult(TaskId taskId) const;

    private:
        SR_NODISCARD uint64_t GetUniqueId() const;
        void OnSingletonDestroy() override;
        void InitSingleton() override;

    private:
        Types::Thread::Ptr m_thread;
        std::atomic<bool> m_isRun;
        std::list<Task> m_tasks;

        std::set<TaskId> m_ids;
        mutable std::map<TaskId, Task::State> m_results;

    };
}

#endif // SR_ENGINE_TASKMANAGER_H
```


