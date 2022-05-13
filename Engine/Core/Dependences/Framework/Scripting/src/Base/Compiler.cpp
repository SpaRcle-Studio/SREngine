//
// Created by Nikita on 11.07.2021.
//

#include <Base/Compiler.h>

void Framework::Scripting::Compiler::UpdateAll() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    for (auto& script : m_scripts)
        script->Update();
}

void Framework::Scripting::Compiler::FixedUpdateAll() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    for (auto& script : m_scripts)
        script->FixedUpdate();
}

void Framework::Scripting::Compiler::StartAll() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    for (auto& script : m_scripts)
        script->Start();
}

void Framework::Scripting::Compiler::RegisterScript(Script *script) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_scriptsToAdd.count(script) != 0) {
        SR_ERROR("Compiler::RegisterScript() : script is already add to pool!");
    }
    else
        m_scriptsToAdd.insert(script);
}

void Framework::Scripting::Compiler::RemoveScript(Framework::Scripting::Script *script) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_scriptsToDel.count(script) != 0) {
        SR_ERROR("Compiler::RemoveScript() : script is already add to pool!");
    }
    else
        m_scriptsToDel.insert(script);
}

void Framework::Scripting::Compiler::PollEvents() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

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
                if (add->IsNeedFreeAfterDestroy()) {
                    add->ForcedFree();
                }
            }
            else
                SR_ERROR("Compiler::PollEvents() : script isn't exists!");
        }

        m_scriptsToDel.clear();
    }

}

bool Framework::Scripting::Compiler::Contains(Framework::Scripting::Script *script) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    return m_scripts.count(script) != 0;
}
