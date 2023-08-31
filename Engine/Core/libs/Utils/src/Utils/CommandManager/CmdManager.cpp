//
// Created by Monika on 08.01.2022.
//

#include <Utils/CommandManager/CmdManager.h>
#include <Utils/Profile/TracyContext.h>
#include <Utils/Debug.h>

namespace SR_UTILS_NS {
    ReversibleCommand *CmdManager::MakeCommand(const std::string &id) const {
        return m_allocators.at(id)();
    }

    bool CmdManager::MakeAndExecute(const std::string &id, SyncType sync) {
        return Execute(MakeCommand(id), sync);
    }

    bool CmdManager::Execute(ReversibleCommand *cmd) {
        SR_TRACY_ZONE;

        if (m_historyPC != UINT32_MAX) {
            /// если следущая команада будет перезаписывать историю,
            /// например когда мы отменили действия, и пытаемся сделать что-то другое,
            /// то нум нужно затереть все отмененные изменения,
            /// это нельзя делать сразу, так как мы можем вернуть изменения без перезаписи
            while(m_history.size() - 1 != m_historyPC) {
                auto&& pIt = std::prev(m_history.end());
                delete *pIt;
                m_history.erase(pIt);
            }
        }

        m_history.emplace_back(cmd);
        ++m_historyPC;

        /// если происходит переполнение истории,
        /// то нужно удалить самый первый элемент
        if (m_historyPC >= m_maxHistorySize) {
            auto&& pIt = m_history.begin();
            delete *pIt;
            m_history.erase(pIt);
        }

        m_lastCmdName = cmd->GetName();
        return cmd->Redo();
    }

    bool CmdManager::DoCmd(const Cmd& cmd) {
        SR_TRACY_ZONE;

        switch (cmd.m_type) {
            case CmdType::Redo: {
                if ((m_historyPC >= (m_history.size() - 1) && m_historyPC != UINT32_MAX) || m_history.empty()) {
                    SR_INFO("CmdManager::DoCmd() : have not commands for redo!");
                    return true;
                }

                auto&& pNextCmp = m_history[++m_historyPC];
                m_lastCmdName = pNextCmp->GetName();

                return pNextCmp->Redo();
            }
            case CmdType::Undo: {
                if (m_history.empty() || m_historyPC == UINT32_MAX) {
                    SR_INFO("CmdManager::DoCmd() : have not commands for undo!");
                    return true;
                }

                if (m_historyPC >= m_history.size()) {
                    SRHalt("Invalid history PC!");
                    return false;
                }

                auto&& pPrevCmd = m_history[m_historyPC];

                --m_historyPC;
                m_lastCmdName = pPrevCmd->GetName();

                return pPrevCmd->Undo();
            }
            case CmdType::Execute: {
                return Execute(cmd.m_cmd);
            }
            default:
                SRHalt("Unknown command type!");
                return false;
        }
    }

    bool CmdManager::Execute(ReversibleCommand *cmd, SyncType sync) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD

        if (m_historyPC != UINT32_MAX) {
            for (uint32_t PC = m_history.size() - 1; PC > m_historyPC; --PC) {
                SR_SAFE_DELETE_PTR(m_history[PC])
            }

            m_history.resize(m_historyPC + 1);
        }
        else {
            for (auto&& pCommand : m_history) {
                SR_SAFE_DELETE_PTR(pCommand)
            }

            m_history.clear();
        }

        return ExecuteImpl(cmd, sync);
    }

    bool CmdManager::RegisterCommand(const std::string &id, const CmdAllocator &allocator) {
        SR_LOCK_GUARD

        if (m_allocators.count(id) == 1) {
            SR_ERROR("CmdManager::RegisterCommand() : command \"" + id + "\" already is registered!");
            return false;
        }

        m_allocators.insert(std::make_pair(id, allocator));

        return true;
    }

    void CmdManager::Update() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD

        while (!m_commands.empty()) {
            SRVerifyFalse2(!DoCmd(m_commands.front()), "Failed to execute command!");
            m_commands.pop();
        }
    }

    bool CmdManager::Close() {
        Clear();
        return true;
    }

    bool CmdManager::ExecuteImpl(ReversibleCommand *cmd, SyncType sync) {
        SR_TRACY_ZONE;

        bool result = false;

        switch (sync) {
            case SyncType::Async: {
                m_commands.push({cmd, CmdType::Execute});
                result = true;
                break;
            }
            case SyncType::Sync: {
                while (!m_commands.empty()) {
                    // TODO: check result
                    DoCmd(m_commands.front());
                    m_commands.pop();
                }

                result = DoCmd({cmd, CmdType::Execute});
                break;
            }
            case SyncType::Force:
                /// команду не нужно сохранять в историю,
                /// так как она выполнилась ни синхронно,
                /// ни асинхронно, следовательно она нарушит историю,
                /// поэтому отменить ее нельзя
                result = cmd->Redo();
                delete cmd;
                break;
            default: SRAssert(false);
                break;
        }

        return result;
    }

    void CmdManager::Clear() {
        SR_LOCK_GUARD

        while (!m_commands.empty()) {
            m_history.emplace_back(m_commands.front().m_cmd);
            m_commands.pop();
        }

        for (auto&& pCommand : m_history) {
            SR_SAFE_DELETE_PTR(pCommand)
        }

        m_history.clear();
        m_historyPC = UINT32_MAX;
    }

    bool CmdManager::Redo() {
        SR_LOCK_GUARD

        m_commands.push({ nullptr, CmdType::Redo });

        return true;
    }

    bool CmdManager::Cancel() {
        SR_LOCK_GUARD

        m_commands.push({ nullptr, CmdType::Undo });

        return true;
    }

    std::string CmdManager::GetLastCmdName() const {
        SR_LOCK_GUARD
        return m_lastCmdName;
    }
}