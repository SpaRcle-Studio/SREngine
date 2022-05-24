//
// Created by Nikita on 11.07.2021.
//

#include <Scripting/Base/Compiler.h>
#include <Types/Thread.h>

namespace SR_SCRIPTING_NS {
    void Compiler::UpdateAll() {
        SR_SCOPED_LOCK

        for (auto&& script : m_scripts) {
            script->Update();
        }
    }

    void Compiler::FixedUpdateAll() {
        SR_SCOPED_LOCK

        for (auto&& script : m_scripts) {
            script->FixedUpdate();
        }
    }

    void Compiler::StartAll() {
        SR_SCOPED_LOCK

        for (auto&& script : m_scripts) {
            script->Start();
        }
    }

    void Compiler::RegisterScript(Script *script) {
        SR_SCOPED_LOCK

        if (m_scriptsToAdd.count(script) != 0) {
            SR_ERROR("Compiler::RegisterScript() : script is already add to pool!");
        }
        else
            m_scriptsToAdd.insert(script);
    }

    void Compiler::RemoveScript(Script *script) {
        SR_SCOPED_LOCK

        if (m_scriptsToDel.count(script) != 0) {
            SR_ERROR("Compiler::RemoveScript() : script is already add to pool!");
        }
        else
            m_scriptsToDel.insert(script);
    }

    void Compiler::PollEvents() {
        SR_SCOPED_LOCK

        if (!m_scriptsToAdd.empty()) {
            for (auto &&add : m_scriptsToAdd) {
                if (m_scripts.count(add) == 0) {
                    m_scripts.insert(add);
                }
                else
                    SR_ERROR("Compiler::PollEvents() : script is already exists!");
            }

            m_scriptsToAdd.clear();
        }

        if (!m_scriptsToDel.empty()) {
            for (auto &&add : m_scriptsToDel) {
                if (m_scripts.count(add) != 0) {
                    m_scripts.erase(add);
                    if (add->IsAutoFree()) {
                        delete add;
                    }
                }
                else
                    SR_ERROR("Compiler::PollEvents() : script isn't exists!");
            }

            m_scriptsToDel.clear();
        }

    }

    bool Compiler::Contains(Framework::Scripting::Script *script) {
        SR_SCOPED_LOCK

        return m_scripts.count(script) != 0;
    }
}