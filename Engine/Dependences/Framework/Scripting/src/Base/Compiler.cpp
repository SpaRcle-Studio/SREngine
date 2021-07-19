//
// Created by Nikita on 11.07.2021.
//

#include <Debug.h>
#include "Base/Compiler.h"

void Framework::Scripting::Compiler::UpdateAll() {
    m_useMutex.lock();

    for (auto& script : m_scripts)
        script->Update();

    m_useMutex.unlock();
}

void Framework::Scripting::Compiler::FixedUpdateAll() {
    m_useMutex.lock();

    for (auto& script : m_scripts)
        script->FixedUpdate();

    m_useMutex.unlock();
}

void Framework::Scripting::Compiler::RegisterScript(Script *script) {
    m_operationMutex.lock();

    if (m_scriptsToAdd.contains(script))
        Helper::Debug::Error("Compiler::RegisterScript() : script is already add to pool!");
    else
        m_scriptsToAdd.insert(script);

    m_operationMutex.unlock();
}

void Framework::Scripting::Compiler::RemoveScript(Framework::Scripting::Script *script) {
    m_operationMutex.lock();

    if (m_scriptsToDel.contains(script))
        Helper::Debug::Error("Compiler::RemoveScript() : script is already add to pool!");
    else
        m_scriptsToDel.insert(script);

    m_operationMutex.unlock();
}

void Framework::Scripting::Compiler::PollEvents() {
    m_useMutex.lock();
    m_operationMutex.lock();

    for (auto add : m_scriptsToAdd)
        if (!m_scripts.contains(add))
            this->m_scripts.insert(add);
        else
            Helper::Debug::Error("Compiler::PollEvents() : script is already exists!");

    for (auto add : m_scriptsToDel)
        if (m_scripts.contains(add)) {
            this->m_scripts.erase(add);
            if (add->IsNeedFreeAfterDestroy())
                add->ForcedFree();
        }
        else
            Helper::Debug::Error("Compiler::PollEvents() : script isn't exists!");

    m_scriptsToDel.clear();
    m_scriptsToAdd.clear();

    m_useMutex.unlock();
    m_operationMutex.unlock();
}

bool Framework::Scripting::Compiler::Contains(Framework::Scripting::Script *script) {
    m_useMutex.lock();

    bool contains = m_scripts.contains(script);

    m_useMutex.unlock();

    return contains;
}
