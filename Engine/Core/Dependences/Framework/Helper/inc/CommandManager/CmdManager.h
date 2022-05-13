//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_CMDMANAGER_H
#define SRENGINE_CMDMANAGER_H

#include <Types/Thread.h>
#include <CommandManager/ICommand.h>

namespace Framework::Helper {
    typedef std::function<ICommand*(void)> CmdAllocator;
    typedef std::unordered_map<std::string, CmdAllocator> CmdAllocators;

    enum class SyncType {
        Sync, Async, Force
    };

    class CmdManager {
    private:
        enum class CmdType {
            Redo, Undo
        };

        struct Cmd {
            ICommand* m_cmd;
            CmdType m_type;
        };

    public:
        CmdManager() = default;
        ~CmdManager() = default;

    public:
        [[nodiscard]] std::string GetLastCmdName() const;
        [[nodiscard]] ICommand* MakeCommand(const std::string& id) const;
        [[nodiscard]] bool IsRun() const { return m_isRun; }
        bool MakeAndExecute(const std::string& id, SyncType sync);
        bool Execute(ICommand* cmd, SyncType sync);
        bool Redo();
        bool Cancel();
        bool RegisterCommand(const std::string& id, const CmdAllocator& allocator);

        bool Run();
        bool Close();

    private:
        bool ExecuteImpl(ICommand* cmd, SyncType sync);
        bool Execute(ICommand* cmd);
        bool Cancel(ICommand* cmd);
        bool DoCmd(const Cmd& cmd);
        void ClearHistory();

    private:
        std::queue<Cmd> m_commands;
        std::vector<ICommand*> m_history;
        uint32_t m_historyPC = UINT32_MAX;
        uint32_t m_maxHistorySize = 0;

        CmdAllocators m_allocators;
        mutable std::mutex m_mutex;
        Types::Thread::Ptr m_thread;
        std::atomic<bool> m_isRun;
        std::string m_lastCmdName;

    };
}

#endif //SRENGINE_CMDMANAGER_H
