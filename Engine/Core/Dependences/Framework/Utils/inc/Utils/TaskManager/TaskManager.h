//
// Created by Monika on 19.03.2022.
//

#ifndef SRENGINE_TASKMANAGER_H
#define SRENGINE_TASKMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/Function.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT Task : public NonCopyable {
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
        /// должен быть динамическим, иначе может потеряться ссылка при перемещении
        StatePtr m_state;

    };

    class TaskManager : public Singleton<TaskManager> {
        friend class Singleton<TaskManager>;
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

        /// Предполагается, что задач не будет слишком много,
        /// и не будет надобности в unordered set/map
        std::set<TaskId> m_ids;
        mutable std::map<TaskId, Task::State> m_results;

    };
}

#endif // SRENGINE_TASKMANAGER_H
