//
// Created by Nikita on 19.07.2021.
//

#include <Debug.h>
#include <ResourceManager/ResourceManager.h>
#include <Xml.h>

#include <GUI/EditorGUI.h>
#include <Engine.h>
#include <GUI/Editor/FileBrowser.h>
#include <GUI/Inspector.h>
#include <GUI/VisualScriptEditor.h>
#include <GUI/WorldEdit.h>

using namespace SR_CORE_NS::GUI;
using namespace SR_GRAPH_NS::GUI;

EditorGUI::EditorGUI(Framework::Scripting::Compiler *compiler)
        : m_compiler(compiler)
{
    m_window = Engine::Instance().GetWindow();

    Register(m_fileBrowser = new FileBrowser());
    Register(m_hierarchy = new Hierarchy());
    Register(m_scriptEditor = new VisualScriptEditor());
    Register(m_sceneViewer = new SceneViewer(m_window));
    Register(m_inspector = new Inspector());
    Register(m_worldEdit = new WorldEdit());

    m_fileBrowser->SetFolder(Helper::ResourceManager::Instance().GetResPath());
}

EditorGUI::~EditorGUI() {
    Remove(m_fileBrowser);
    Remove(m_scriptEditor);
    Remove(m_hierarchy);
    Remove(m_sceneViewer);
    Remove(m_inspector);
    Remove(m_worldEdit);

    SR_SAFE_DELETE_PTR(m_fileBrowser);
    SR_SAFE_DELETE_PTR(m_scriptEditor);
    SR_SAFE_DELETE_PTR(m_hierarchy);
    SR_SAFE_DELETE_PTR(m_sceneViewer);
    SR_SAFE_DELETE_PTR(m_inspector);
    SR_SAFE_DELETE_PTR(m_worldEdit);
}

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

    this->m_script = Scripting::Script::Allocate("Engine/Editor", m_compiler, Scripting::ScriptType::EvoScript);
    if (!m_script || !m_script->Compile()) {
        Helper::Debug::Error("EditorGUI::Init() : failed to allocate/compile script!");
        m_hasErrors = true;
        return false;
    }

    Load();

    this->m_isInit = true;

    return true;
}

bool EditorGUI::Destroy() {
    Save();

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
    delete this;
}

void EditorGUI::Draw() {
    if (m_hasErrors)
        return;

    if (!m_isInit) {
        if (!Init())
            return;
    }

    m_script->OnGUI();

    WidgetManager::Draw();
}

void EditorGUI::Save() {
    const auto path = Helper::ResourceManager::Instance().GetConfigPath().Concat("EditorWidgets.xml");
    auto document = Helper::Xml::Document::New();
    auto widgets = document.Root().AppendChild("Widgets");
    for (auto&& [name, widget] : GetWidgets())
        widgets.AppendChild("Widget").NAppendAttribute("Name", name).NAppendAttribute("Open", widget->IsOpen());
    document.Save(path.ToString());
}

void EditorGUI::Load() {
    const auto path = Helper::ResourceManager::Instance().GetConfigPath().Concat("EditorWidgets.xml");

    if (!path.Exists())
        return;

    auto document = Helper::Xml::Document::Load(path);
    for (const auto& widget : document.Root().TryGetNode("Widgets").TryGetNodes()) {
        const auto& name = widget.GetAttribute("Name").ToString();
        if (auto&& pIt = GetWidgets().find(name); pIt != GetWidgets().end()) {
            if (widget.GetAttribute("Open").ToBool()) {
                pIt->second->Open();
            }
            else
                pIt->second->Close();
        }
    }
}

void EditorGUI::Enable(bool value) {
    if (m_enabled != value) {
        m_window->Synchronize();
        m_sceneViewer->Enable(value);
        m_window->SetGUIEnabled(!m_window->IsGUIEnabled());
        m_enabled = value;
    }
}

void EditorGUI::Update() {
    if (Enabled())
        m_inspector->Update();

    m_sceneViewer->Update();
}


