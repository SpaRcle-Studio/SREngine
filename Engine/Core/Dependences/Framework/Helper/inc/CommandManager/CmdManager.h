//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_CMDMANAGER_H
#define SRENGINE_CMDMANAGER_H

#include <string>
#include <mutex>
#include <queue>
#include <functional>
#include <unordered_map>

#include <Types/Thread.h>
#include <CommandManager/ICommand.h>

namespace Framework::Helper {
    typedef std::function<ICommand*(void)> CmdAllocator;
    typedef std::unordered_map<std::string, CmdAllocator> CmdAllocators;

    class CmdManager {
    public:
        CmdManager() = default;
        ~CmdManager() = default;

        enum class SyncType {
            Sync, Async, Force
        };

    public:
        [[nodiscard]] ICommand* MakeCommand(const std::string& id) const;
        bool MakeAndExecute(const std::string& id, SyncType sync);
        bool Execute(ICommand* cmd, SyncType sync);
        void RegisterCommand(const std::string& id, const CmdAllocator& allocator);

    private:
        std::queue<ICommand*> m_commands;
        CmdAllocators m_allocators;
        std::mutex m_mutex;

    };
}

#endif //SRENGINE_CMDMANAGER_H
