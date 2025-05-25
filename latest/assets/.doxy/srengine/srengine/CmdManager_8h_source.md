

# File CmdManager.h

[**File List**](files.md) **>** [**CommandManager**](dir_ccc40ac273e6f569bc0e58b2cdbc2be5.md) **>** [**CmdManager.h**](CmdManager_8h.md)

[Go to the documentation of this file](CmdManager_8h.md)


```C++
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

    class SR_COMMON_DLL_API CmdManager : SR_UTILS_NS::NonCopyable {
    private:
        enum class CmdType {
            Redo, Undo, Execute, Store
        };

        struct SR_COMMON_DLL_API Cmd {
            ReversibleCommand* m_cmd;
            CmdType m_type;
        };

    public:
        CmdManager() = default;
        ~CmdManager() override;

    public:
        SR_NODISCARD std::string GetLastCmdName() const;
        SR_NODISCARD uint32_t GetHistorySize() const;
        SR_NODISCARD uint32_t GetMaxHistorySize() const;
        SR_NODISCARD uint32_t GetHistoryPC() const;

        bool Execute(ReversibleCommand* cmd, SyncType sync);
        void Store(ReversibleCommand* cmd);
        bool Redo();
        bool Cancel();

        void SetMaxHistorySize(uint32_t size);

        void Update();

        void Clear();

        template<typename T, typename... Args> bool Execute(SyncType sync, Args&&... args) {
            auto&& pCmd = new T(std::forward<Args>(args)...);
            return Execute(pCmd, sync);
        }

    private:
        bool ExecuteImpl(ReversibleCommand* cmd, SyncType sync);
        bool Execute(ReversibleCommand* cmd, bool store);
        bool DoCmd(const Cmd& cmd);
        bool Close();

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
```


