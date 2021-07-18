//
// Created by Nikita on 11.07.2021.
//

#include <Debug.h>
#include "Base/Compiler.h"

void Framework::Scripting::Compiler::UpdateAll() {
    m_mutex.lock();

    for (auto& script : m_scripts)
        script->Update();

    m_mutex.unlock();
}

void Framework::Scripting::Compiler::RegisterScript(Script *script) {
    m_mutex.lock();

    if (m_scripts.contains(script))
        Helper::Debug::Error("Compiler::RegisterScript() : script is already exist!");
    else
        m_scripts.insert(script);

    m_mutex.unlock();
}

void Framework::Scripting::Compiler::RemoveScript(Framework::Scripting::Script *script) {
    m_mutex.lock();

    if (!m_scripts.contains(script))
        Helper::Debug::Error("Compiler::RemoveScript() : script isn't exist!");
    else
        m_scripts.erase(script);

    m_mutex.unlock();
}

void Framework::Scripting::Compiler::FixedUpdateAll() {
    m_mutex.lock();

    for (auto& script : m_scripts)
        script->FixedUpdate();

    m_mutex.unlock();
}
