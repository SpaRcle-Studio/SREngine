//
// Created by Nikita on 19.07.2021.
//

#include <Debug.h>
#include <ResourceManager/ResourceManager.h>

#include <GUI/EditorGUI.h>
#include <GUI/FileBrowser.h>
#include <GUI/VisualScriptEditor.h>

using namespace SR_CORE_NS::GUI;
using namespace SR_GRAPH_NS::GUI;

bool EditorGUI::Init() {
    if (m_isInit) {
        Helper::Debug::Error("EditorGUI::Init() : editor gui is already initialized!");
        return false;
    }
    Helper::Debug::Info("EditorGUI::Init() : initializing editor gui...");

    if (!m_compiler) {
        Helper::Debug::Error("EditorGUI::Init() : compiler is nullptr!");
        return false;
    }

    m_fileBrowser = new FileBrowser();
    m_scriptEditor = new VisualScriptEditor();

    m_fileBrowser->SetFolder(Helper::ResourceManager::Instance().GetResPath());

    this->m_script = Scripting::Script::Allocate("Engine/Editor", m_compiler, Scripting::ScriptType::EvoScript);
    if (!m_script || !m_script->Compile()) {
        Helper::Debug::Error("EditorGUI::Init() : failed to allocate/compile script!");
        return false;
    }

    this->m_isInit = true;

    return true;
}

bool EditorGUI::Destroy() {
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

void EditorGUI::Free() {
    SR_SAFE_DELETE_PTR(m_fileBrowser);
    SR_SAFE_DELETE_PTR(m_scriptEditor);

    delete this;
}

void EditorGUI::Draw() {
    if (m_hasErrors)
        return;

    if (!m_isInit)
        if (!Init()) {
            this->m_hasErrors = true;
            return;
        }

    this->m_script->OnGUI();
}
