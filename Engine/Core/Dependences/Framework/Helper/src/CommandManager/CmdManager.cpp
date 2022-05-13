//
// Created by Monika on 08.01.2022.
//

#include "CommandManager/CmdManager.h"
#include <Debug.h>

namespace SR_UTILS_NS {
    ICommand *CmdManager::MakeCommand(const std::string &id) const {
        return m_allocators.at(id)();
    }

    bool CmdManager::MakeAndExecute(const std::string &id, SyncType sync) {
        return Execute(MakeCommand(id), sync);
    }

    bool CmdManager::Execute(ICommand *cmd) {
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

    bool CmdManager::Cancel(ICommand *cmd) {
        --m_historyPC;
        m_lastCmdName = cmd->GetName();
        return cmd->Undo();
    }

    bool CmdManager::Cancel() {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_history.empty() || m_historyPC == UINT32_MAX)
            return false;

        SRAssert(m_historyPC < m_history.size());

        return Cancel(m_history[m_historyPC]);
    }

    bool CmdManager::DoCmd(const Cmd& cmd) {
        switch (cmd.m_type) {
            case CmdType::Redo: {
                return Execute(cmd.m_cmd);
            }
            case CmdType::Undo:
                return Cancel(cmd.m_cmd);
            default:
                SRAssert(false);
                return false;
        }
    }

    bool CmdManager::Execute(ICommand *cmd, SyncType sync) {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_historyPC != UINT32_MAX) {
            for (uint32_t PC = m_history.size() - 1; PC > m_historyPC; --PC)
                delete m_history[PC];

            m_history.resize(m_historyPC + 1);
        }
        else {
            for (auto&& command : m_history)
                delete command;

            m_history.clear();
        }

        return ExecuteImpl(cmd, sync);
    }

    bool CmdManager::RegisterCommand(const std::string &id, const CmdAllocator &allocator) {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_allocators.count(id) == 1) {
            SR_ERROR("CmdManager::RegisterCommand() : command \"" + id + "\" already is registered!");
            return false;
        }

        m_allocators.insert(std::make_pair(id, allocator));

        return true;
    }

    bool CmdManager::Run() {
        if (m_isRun.load()) {
            SR_ERROR("CmdManager::Run() : command manager is already ran!");
            return false;
        }

        m_isRun.store(true);

        SR_INFO("CmdManager::Run() : run command manager thread...");

        m_maxHistorySize = 128;

        m_thread = SR_HTYPES_NS::Thread::Factory::Instance().Create([this]() {
            while(m_isRun.load()) {
                m_thread->Sleep(100);

                std::lock_guard<std::mutex> lock(m_mutex);

                while (!m_commands.empty()) {
                    SRVerifyFalse2(DoCmd(m_commands.front()), "Failed to execute command!");
                    m_commands.pop();
                }
            }
        });

        return m_thread->Joinable();
    }

    bool CmdManager::Close() {
        if (!m_isRun.load()) {
            SR_ERROR("CmdManager::Close() : command manager isn't ran!");
            return false;
        }

        SR_INFO("CmdManager::Close() : stopping command manager thread...");

        m_isRun.store(false);

        const bool result = m_thread && m_thread->TryJoin();

        if (m_thread) {
            m_thread->Free();
            m_thread = nullptr;
        }

        ClearHistory();

        return result;
    }

    bool CmdManager::ExecuteImpl(ICommand *cmd, SyncType sync) {
        bool result = false;

        switch (sync) {
            case SyncType::Async: {
                m_commands.push({cmd, CmdType::Redo});
                result = true;
                break;
            }
            case SyncType::Sync: {
                while (!m_commands.empty()) {
                    // TODO: check result
                    DoCmd(m_commands.front());
                    m_commands.pop();
                }

                result = DoCmd({cmd, CmdType::Redo});
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

    void CmdManager::ClearHistory() {
        for (auto&& command : m_history)
            delete command;

        m_history.clear();
        m_historyPC = UINT32_MAX;
    }

    bool CmdManager::Redo() {
        std::lock_guard<std::mutex> lock(m_mutex);

        if ((m_historyPC >= (m_history.size() - 1) && m_historyPC != UINT32_MAX) || m_history.empty())
            return false;

        auto&& cmd = m_history[++m_historyPC];

        m_lastCmdName = cmd->GetName();
        return cmd->Redo();
    }

    std::string CmdManager::GetLastCmdName() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_lastCmdName;
    }
}