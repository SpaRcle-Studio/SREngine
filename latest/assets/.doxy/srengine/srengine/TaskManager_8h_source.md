

# File TaskManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**TaskManager**](dir_13d04ea2f847395a194669a63cd5046e.md) **>** [**TaskManager.h**](TaskManager_8h.md)

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


