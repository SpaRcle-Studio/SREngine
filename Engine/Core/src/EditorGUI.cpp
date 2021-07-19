//
// Created by Nikita on 19.07.2021.
//

#include <Debug.h>
#include "../inc/EditorGUI.h"

bool Framework::EditorGUI::Init() {
    if (m_isInit) {
        Helper::Debug::Error("EditorGUI::Init() : editor gui is already initialized!");
        return false;
    }
    Helper::Debug::Info("EditorGUI::Init() : initializing editor gui...");

    if (!m_compiler) {
        Helper::Debug::Error("EditorGUI::Init() : compiler is nullptr!");
        return false;
    }

    this->m_script = Scripting::Script::Allocate(
            "SpaRcle Editor", "Engine/Editor",
            m_compiler, Scripting::ScriptType::EvoScript);
    if (!m_script || !m_script->Compile()) {
        Helper::Debug::Error("EditorGUI::Init() : failed to allocate/compile script!");
        return false;
    }

    this->m_isInit = true;

    return true;
}

bool Framework::EditorGUI::Destroy() {
    if (m_compiler)
        m_compiler = nullptr;

    if (m_script) {
        m_script->DelayedDestroyAndFree();
        m_script = nullptr;
    }

    if (m_isInit)
        m_isInit = false;

    return true;
}

void Framework::EditorGUI::Free() {
    delete this;
}

void Framework::EditorGUI::Draw() {
    if (m_hasErrors)
        return;

    if (!m_isInit)
        if (!Init()) {
            this->m_hasErrors = true;
            return;
        }

    this->m_script->OnGUI();
}
