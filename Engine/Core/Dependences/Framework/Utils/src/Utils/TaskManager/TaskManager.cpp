#include <Utils/TaskManager/TaskManager.h>

namespace SR_UTILS_NS {
    Task::Task(TaskFn fn, bool createThread)
        : m_createThread(createThread)
        , m_id(SR_UINT64_MAX)
        , m_function(std::move(fn))
        , m_state(new std::atomic<State>())
        , m_thread(nullptr)
    {
        m_state->store(State::Waiting);
    }

    Task::Task(Task &&task) noexcept {
        m_thread = std::exchange(task.m_thread, { });
        m_function = task.m_function;
        m_id = std::exchange(task.m_id, { });
        m_state = std::exchange(task.m_state, { });
        m_createThread = std::exchange(task.m_createThread, { });
    }

    Task &Task::operator=(Task &&task) noexcept {
        m_thread = std::exchange(task.m_thread, { });
        m_function = task.m_function;
        m_id = std::exchange(task.m_id, { });
        m_state = std::exchange(task.m_state, { });
        m_createThread = std::exchange(task.m_createThread, { });
        return *this;
    }

    Task::~Task() {
        SRAssert(!m_state || m_state->load() == State::Completed);
        SRAssert(!m_thread || !m_thread->Joinable());

        if (m_thread) {
            if (m_thread->Joinable()) {
                m_thread->Detach();
            }

            m_thread->Free();
            m_thread = nullptr;
        }

        if (m_state) {
            delete m_state;
        }
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

    bool Task::Run() {
        if (m_state->load() != State::Waiting || !m_function || (m_thread && m_thread->Joinable())) {
            SRAssert(false);
            return false;
        }

        m_state->store(State::Launched);

        if (m_createThread) {
            m_thread = SR_HTYPES_NS::Thread::Factory::Instance().Create(m_function, m_state);
        }
        else {
            m_function(m_state);
        }

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

    bool Task::IsWaiting() const {
        return m_state->load() == State::Waiting;
    }

    void Task::SetId(uint64_t id) {
        m_id = id;
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

        SRAssert(!m_thread);
    }

    uint64_t Helper::TaskManager::GetUniqueId() const {
        return 0;
    }

    void TaskManager::InitSingleton() {
        if (m_isRun.load()) {
            SR_ERROR("TaskManager::InitSingleton() : task manager is already ran!");
            return;
        }

        m_isRun.store(true);

        SR_INFO("TaskManager::InitSingleton() : run task manager thread...");

        m_thread = SR_HTYPES_NS::Thread::Factory::Instance().Create([this]() {
            while (m_isRun.load()) {
                m_thread->Sleep(10);

                SR_SCOPED_LOCK

                for (auto pIt = m_tasks.begin(); pIt != m_tasks.end(); ) {
                    if (pIt->IsWaiting()) {
                        pIt->Run();
                    }

                    if (pIt->IsCompleted()) {
                        m_results.insert(std::make_pair(pIt->GetId(), pIt->GetResult()));
                        m_ids.erase(pIt->GetId());
                        pIt = m_tasks.erase(pIt);
                    }
                    else {
                        ++pIt;
                    }
                }
            }
        });

        if (!m_thread->Joinable()) {
            SR_ERROR("TaskManager::InitSingleton() : failed to run a thread!");
        }

        Singleton::InitSingleton();
    }

    TaskManager::TaskId TaskManager::Execute(Task &&task) {
        SR_SCOPED_LOCK

        const uint64_t uniqueId = GetUniqueId();

        task.SetId(uniqueId);
        m_ids.insert(uniqueId);
        m_tasks.emplace_back(std::move(task));

        return uniqueId;
    }

    TaskManager::TaskId TaskManager::Execute(const TaskFn& function, bool createThread) {
        SR_SCOPED_LOCK

        Task task(function, createThread);

        return Execute(std::move(task));
    }

    Task::State Helper::TaskManager::GetResult(uint64_t taskId) const {
        if (m_ids.count(taskId) == 1) {
            return Task::State::Launched;
        }

        return Task::State::Unknown;
    }

    void TaskManager::OnSingletonDestroy() {
        m_isRun = false;

        if (m_thread) {
            m_thread->TryJoin();
            m_thread->Free();
            m_thread = nullptr;
        }

        Singleton::OnSingletonDestroy();
    }
}