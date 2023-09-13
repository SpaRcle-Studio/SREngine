//
// Created by Monika on 08.01.2022.
//

#ifndef SR_ENGINE_UTILS_CMDMANAGER_H
#define SR_ENGINE_UTILS_CMDMANAGER_H

#include <Utils/Types/Thread.h>
#include <Utils/CommandManager/ReversibleCommand.h>

namespace SR_UTILS_NS {
    enum class SyncType {
        Sync, Async, Force
    };

    class SR_DLL_EXPORT CmdManager : SR_UTILS_NS::NonCopyable {
    private:
        enum class CmdType {
            Redo, Undo, Execute
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
        bool Execute(ReversibleCommand* cmd, SyncType sync);
        bool Redo();
        bool Cancel();

        void Update();
        bool Close();

        void Clear();

    private:
        bool ExecuteImpl(ReversibleCommand* cmd, SyncType sync);
        bool Execute(ReversibleCommand* cmd);
        bool DoCmd(const Cmd& cmd);

    private:
        std::queue<Cmd> m_commands;
        std::vector<ReversibleCommand*> m_history;
        uint32_t m_historyPC = UINT32_MAX;
        uint32_t m_maxHistorySize = 128;

        mutable std::recursive_mutex m_mutex;
        std::string m_lastCmdName;

    };
}

#endif //SR_ENGINE_UTILS_CMDMANAGER_H
