#include <TaskManager/TaskManager.h>

namespace SR_UTILS_NS {
    Task::Task(TaskFn fn)
        : m_id(SR_UINT64_MAX)
        , m_function(std::move(fn))
        , m_state(new std::atomic<State>())
    {
        m_state->store(State::Waiting);
    }

    Task::Task(Task &&task) noexcept {
        m_thread = std::exchange(task.m_thread, { });
        m_function = std::exchange(task.m_function, { });
        m_id = std::exchange(task.m_id, { });
        m_state = std::exchange(task.m_state, { });
    }

    Task &Task::operator=(Task &&task) noexcept {
        m_thread = std::exchange(task.m_thread, { });
        m_function = std::exchange(task.m_function, { });
        m_id = std::exchange(task.m_id, { });
        m_state = std::exchange(task.m_state, { });
        return *this;
    }

    Task::~Task() {
        SRAssert(m_state->load() == State::Completed && (m_thread && !m_thread->Joinable()));

        if (m_thread) {
            if (m_thread->Joinable()) {
                m_thread->Detach();
            }

            m_thread->Free();
            m_thread = nullptr;
        }

        delete m_state;
    }

    bool Task::Stop() {
        if (m_state->load() != State::Launched || !m_thread->Joinable()) {
            SRAssert(false);
            return false;
        }

        if (m_thread) {
            m_thread->Detach();
            m_thread->Free();
            m_thread = nullptr;
        }

        m_state->store(State::Stopped);

        return true;
    }

    bool Task::Run(uint64_t id) {
        if (m_state->load() != State::Waiting || !m_function || (m_thread && m_thread->Joinable())) {
            SRAssert(false);
            return false;
        }

        m_id = id;
        m_state->store(State::Launched);
        m_thread = SR_HTYPES_NS::Thread::Factory::Instance().Create(m_function, m_state);

        return true;
    }

    bool Task::IsCompleted() const {
        const State state = m_state->load();
        return state == State::Completed || state == State::Failed || state == State::Stopped;
    }

    Task::State Task::GetResult() const {
        return m_state->load();
    }

    uint64_t Task::GetId() const {
        return m_id;
    }


    Helper::TaskManager::~TaskManager() {
        if (!m_tasks.empty() || !m_ids.empty()) {
            SRAssert(false);

            for (Task& task : m_tasks) {
                task.Stop();
            }
        }

        m_tasks.clear();
        m_ids.clear();
    }

    uint64_t Helper::TaskManager::GetUniqueId() const {
        return 0;
    }

    bool TaskManager::Run() {
        if (m_isRun.load()) {
            SR_ERROR("TaskManager::Run() : task manager is already ran!");
            return false;
        }

        m_isRun.store(true);

        SR_INFO("TaskManager::Run() : run task manager thread...");

        m_thread = SR_HTYPES_NS::Thread::Factory::Instance().Create([this]() {
            while (m_isRun.load()) {
                m_thread->Sleep(10);

                std::lock_guard<std::mutex> lock(m_mutex);

                for (auto pIt = m_tasks.begin(); pIt != m_tasks.end(); ) {
                    if (pIt->IsCompleted()) {
                        m_results.insert(std::make_pair(pIt->GetId(), pIt->GetResult()));
                        m_ids.erase(pIt->GetId());
                        pIt = m_tasks.erase(pIt);
                    }
                    else
                        ++pIt;
                }
            }
        });

        return m_thread->Joinable();
    }

    void TaskManager::Close() {

    }

    bool TaskManager::Execute(Task &&task) {
        std::lock_guard<std::mutex> lock(m_mutex);

        const uint64_t uniqueId = GetUniqueId();
        m_ids.insert(uniqueId);
        return m_tasks.emplace_back(std::move(task)).Run(uniqueId);
    }

    Task::State Helper::TaskManager::GetResult(uint64_t taskId) const {
        if (m_ids.count(taskId) == 1) {
            return Task::State::Launched;
        }

        return Task::State::Unknown;
    }
}