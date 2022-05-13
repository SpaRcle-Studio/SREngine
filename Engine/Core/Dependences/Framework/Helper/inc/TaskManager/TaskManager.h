//
// Created by Monika on 19.03.2022.
//

#ifndef SRENGINE_TASKMANAGER_H
#define SRENGINE_TASKMANAGER_H

#include <Utils/Singleton.h>
#include <Utils/NonCopyable.h>
#include <Types/Thread.h>

namespace SR_UTILS_NS {
    class Task : public NonCopyable {
    public:
        enum class State {
            Unknown, Waiting, Launched, Stopped, Completed, Failed
        };

        using TaskFn = std::function<void(std::atomic<State>*)>;

    public:
        explicit Task(TaskFn fn);
        Task(Task&& task) noexcept;
        Task& operator=(Task&& task) noexcept;

        ~Task() override;

    public:
        bool Run(uint64_t id);
        bool Stop();

        SR_NODISCARD bool IsCompleted() const;
        SR_NODISCARD State GetResult() const;
        SR_NODISCARD uint64_t GetId() const;

    private:
        uint64_t m_id;
        Types::Thread::Ptr m_thread;
        TaskFn m_function;
        /// должен быть динамическим, иначе может потеряться ссылка при перемещении
        std::atomic<State>* m_state;

    };

    class TaskManager : public Singleton<TaskManager> {
        friend class Singleton<TaskManager>;
    public:
        ~TaskManager() override;

    public:
        bool Run();
        void Close();

        bool Execute(Task&& task);

        Task::State GetResult(uint64_t taskId) const;

    private:
        [[nodiscard]] uint64_t GetUniqueId() const;

    private:
        mutable std::mutex m_mutex;
        Types::Thread::Ptr m_thread;
        std::atomic<bool> m_isRun;
        std::list<Task> m_tasks;

        /// Предполагается, что задач не будет слишком много,
        /// и не будет надобности в unordered set/map
        std::set<uint64_t> m_ids;
        mutable std::map<uint64_t, Task::State> m_results;

    };
}

#endif // SRENGINE_TASKMANAGER_H
