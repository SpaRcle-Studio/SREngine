//
// Created by Monika on 08.01.2022.
//

#include "CommandManager/CmdManager.h"
#include <Debug.h>

ICommand *CmdManager::MakeCommand(const std::string &id) const {
    return m_allocators.at(id)();
}

bool CmdManager::MakeAndExecute(const std::string &id, SyncType sync) {
    return Execute(MakeCommand(id), sync);
}

bool CmdManager::Execute(ICommand *cmd, SyncType sync) {
    bool result = true;

    switch (sync) {
        case SyncType::Async: {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_commands.push(cmd);
            break;
        }
        case SyncType::Sync: {
            std::lock_guard<std::mutex> lock(m_mutex);

            while(!m_commands.empty()) {
                m_commands.front()->Redo();
                m_commands.pop();
            }

            result = cmd->Redo();
            delete cmd;

            break;
        }
        case SyncType::Force:
            result = cmd->Redo();
            delete cmd;
            break;
        default:
            SRAssert(false);
            result = false;
            break;
    }

    return result;
}

void CmdManager::RegisterCommand(const std::string &id, const CmdAllocator &allocator) {
    if (m_allocators.contains(id)) {
        Helper::Debug::Error("CmdManager::RegisterCommand() : command \"" + id + "\" already is registered!");
    } else
        m_allocators.insert(std::make_pair(id, allocator));
}
