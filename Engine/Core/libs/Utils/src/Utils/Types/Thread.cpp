//
// Created by Monika on 18.03.2022.
//

#include <Utils/Types/Thread.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Profile/TracyContext.h>

namespace SR_HTYPES_NS {
    Thread::Thread(std::thread &&thread)
        : m_thread(std::exchange(thread, {}))
    {
        m_isCreated = true;
        m_isRan = true;
        m_id = SR_UTILS_NS::GetThreadId(m_thread);
        m_context = new DataStorage();
    }

    Thread::~Thread() {
        SRAssert(!Joinable());
        if (m_context) {
            delete m_context;
            m_context = nullptr;
        }
    }

    Thread::Thread(Thread::ThreadId id)
        : m_id(id)
        , m_thread(std::thread())
    {
        m_context = new DataStorage();
    }

    Thread::Thread()
        : Thread(std::thread())
    { }

    void Thread::Sleep(uint64_t milliseconds) {
        SR_TRACY_ZONE;
        Platform::Sleep(milliseconds);
    }

    void Thread::SetPriority(ThreadPriority priority) {
        Platform::SetThreadPriority(reinterpret_cast<void*>(m_thread.native_handle()), priority);
    }

    SR_NODISCARD Thread::Ptr Thread::Factory::CreateEmpty() {
        SR_SCOPED_LOCK
        SR_LOG("Thread::Factory::CreateEmpty() : create empty thread...");
        return new Thread();
    }

    Thread::Ptr Thread::Factory::Create(std::thread thread) {
        SR_SCOPED_LOCK

        auto&& pThread = new Thread(std::move(thread));

        SR_LOG("Thread::Factory::Create() : create new \"{}\" thread...", pThread->m_id);

        m_threads.insert(std::make_pair(pThread->GetId(), pThread));

        return pThread;
    }

    Thread::Ptr Thread::Factory::Create(const std::function<void()> &fn) {
        return Create(std::thread(fn));
    }

    bool Thread::TryJoin() {
        if (Joinable()) {
            Join();
            return true;
        }

        return false;
    }

    Thread::Ptr Thread::Factory::GetMainThread() {
        SR_LOCK_GUARD
        SRAssert2(m_main, "Main thread isn't initialized!");
        return m_main;
    }

    Thread::Ptr Thread::Factory::GetThisThread() {
        SR_SCOPED_LOCK

        auto&& threadId = SR_UTILS_NS::GetThisThreadId();

        if (auto&& pIt = m_threads.find(threadId); pIt != m_threads.end()) {
            return pIt->second;
        }

        auto&& main = GetMainThread();

        if (main && threadId == main->m_id) {
            return main;
        }

    #ifdef SR_DEBUG
        SR_MAYBE_UNUSED std::string threads;
        for (auto&& [id, pThread] : m_threads) {
            threads.append("\tThread [" + id + "]\n");
        }
        SRHalt("Thread::Factory::GetThisThread() : unknown thread!\n" + threads);
    #endif

        return nullptr;
    }

    void Thread::Factory::Remove(Thread* pThread) {
        SR_SCOPED_LOCK

        SR_LOG("Thread::Free() : free \"{}\" thread...", pThread->GetId());

        if (pThread == m_main) {
            m_main = nullptr;
        }
        else {
            m_threads.erase(pThread->GetId());
        }
    }

    Thread::ThreadId Thread::GetId() {
        return m_id;
    }

    void Thread::Free() {
        Factory::Instance().Remove(this);
        delete this;
    }

    void Thread::Synchronize() {
        SR_WRITE_LOCK

    #if defined(SR_DEBUG) && SR_THREAD_SAFE_CHECKS
        auto&& thread = Thread::Factory::Instance().GetThisThread();

        if (GetId() != thread->GetId()) {
            SRHalt("Synchronization can only be performed by the owner thread!");
            return;
        }
    #endif

        if (m_function) {
            m_executeResult = (*m_function)();
            m_function = nullptr;
        }
    }

    bool Thread::Execute(const SR_HTYPES_NS::Function<bool()>& function) const {
        /// сначала дожидаемся предыдущей работы. Операция атомарная.
        while (m_function) {
            SR_NOOP;
            continue;
        }

        /// синхронно записываем
        {
            SR_WRITE_LOCK
            m_function = &function;
        }

        /// синхронно ждем выволнения работы. Операция атомарная.
        while (m_function) {
            SR_NOOP;
            continue;
        }

        return m_executeResult;
    }

    void Thread::SetName(const std::string& name) {
        SR_WRITE_LOCK;
        m_name = name;
    }

    uint32_t Thread::Factory::GetThreadsCount() {
        SR_SCOPED_LOCK

        return m_threads.size();
    }

    void Thread::Factory::SetMainThread() {
        SR_LOCK_GUARD

        SRAssert2(!m_main, "Main thread already initialized!");

        SR_LOG("Thread::Factory::SetMainThread() : initializing main thread...");

        m_main = new Thread(SR_UTILS_NS::GetThisThreadId());

        SR_LOG("Thread::Factory::SetMainThread() : main thread id: \"{}\"", m_main->GetId());
    }

    void Thread::Factory::PrintThreads() {
        SR_LOCK_GUARD

        if (m_threads.empty()) {
            return;
        }

        std::string log = "Thread::Factory::PrintThreads() : threads:\n";

        for (auto&& [id, pThread] : m_threads) {
            if (pThread == m_main) {
                log += "\tThread [Main]\n";
            }
            else if (!pThread->m_name.empty()) {
                log += "\tThread [" + id + "] - " + pThread->m_name + "\n";
            }
            else {
                log += "\tThread [" + id + "]\n";
            }
        }

        SR_SYSTEM_LOG(log);
    }
}

