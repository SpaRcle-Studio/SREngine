//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_CMDMANAGER_H
#define SRENGINE_CMDMANAGER_H

#include <Utils/Types/Thread.h>
#include <Utils/CommandManager/ReversibleCommand.h>

namespace SR_UTILS_NS {
    typedef std::function<ReversibleCommand*(void)> CmdAllocator;
    typedef std::unordered_map<std::string, CmdAllocator> CmdAllocators;

    enum class SyncType {
        Sync, Async, Force
    };

    class SR_DLL_EXPORT CmdManager : SR_UTILS_NS::NonCopyable {
    private:
        enum class CmdType {
            Redo, Undo
        };

        struct SR_DLL_EXPORT Cmd {
            ReversibleCommand* m_cmd;
            CmdType m_type;
        };

    public:
        CmdManager() = default;
        ~CmdManager() override = default;

    public:
        SR_NODISCARD std::string GetLastCmdName() const;
        SR_NODISCARD ReversibleCommand* MakeCommand(const std::string& id) const;
        SR_NODISCARD bool IsRun() const { return m_isRun; }

        bool MakeAndExecute(const std::string& id, SyncType sync);
        bool Execute(ReversibleCommand* cmd, SyncType sync);
        bool Redo();
        bool Cancel();
        bool RegisterCommand(const std::string& id, const CmdAllocator& allocator);

        bool Run();
        bool Close();

    private:
        bool ExecuteImpl(ReversibleCommand* cmd, SyncType sync);
        bool Execute(ReversibleCommand* cmd);
        bool Cancel(ReversibleCommand* cmd);
        bool DoCmd(const Cmd& cmd);
        void ClearHistory();

    private:
        std::queue<Cmd> m_commands;
        std::vector<ReversibleCommand*> m_history;
        uint32_t m_historyPC = UINT32_MAX;
        uint32_t m_maxHistorySize = 0;

        CmdAllocators m_allocators;
        mutable std::mutex m_mutex;
        Types::Thread::Ptr m_thread{};
        std::atomic<bool> m_isRun;
        std::string m_lastCmdName;

    };
}

#endif //SRENGINE_CMDMANAGER_H
