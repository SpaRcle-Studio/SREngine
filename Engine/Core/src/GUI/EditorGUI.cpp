//
// Created by Nikita on 19.07.2021.
//

#include <Debug.h>
#include <Xml.h>

#include <GUI/EditorGUI.h>
#include <Engine.h>
#include <GUI/Editor/FileBrowser.h>
#include <GUI/Inspector.h>
#include <GUI/VisualScriptEditor.h>
#include <GUI/WorldEdit.h>
#include <GUI/EngineSettings.h>
#include <GUI/EngineStatistics.h>
#include <GUI/Hierarchy.h>
#include <GUI/SceneViewer.h>

using namespace SR_CORE_NS::GUI;
using namespace SR_GRAPH_NS::GUI;

EditorGUI::EditorGUI(Framework::Scripting::Compiler *compiler)
    : m_compiler(compiler)
{
    m_window = Engine::Instance().GetWindow();

    AddWindow(new FileBrowser());
    AddWindow(new Hierarchy());
    AddWindow(new VisualScriptEditor());
    AddWindow(new SceneViewer(m_window, GetWindow<Hierarchy>()));
    AddWindow(new Inspector(GetWindow<Hierarchy>()));
    AddWindow(new WorldEdit());
    AddWindow(new EngineSettings());
    AddWindow(new EngineStatistics());

    for (auto& [id, widget] : m_widgets)
        Register(widget);

    GetWindow<FileBrowser>()->SetFolder(Helper::ResourceManager::Instance().GetResPath());
}

EditorGUI::~EditorGUI() {
    for (auto& [id, widget] : m_widgets) {
        Remove(widget);
        SR_SAFE_DELETE_PTR(widget);
    }
    m_widgets.clear();
}

bool EditorGUI::Init() {
    if (m_isInit) {
        SR_ERROR("EditorGUI::Init() : editor gui is already initialized!");
        return false;
    }
    SR_INFO("EditorGUI::Init() : initializing editor gui...");

    if (!m_compiler) {
        SR_ERROR("EditorGUI::Init() : compiler is nullptr!");
        return false;
    }

    m_script = Scripting::Script::Allocate("Engine/Editor", m_compiler, Scripting::ScriptType::EvoScript);
    if (!m_script || !m_script->Compile()) {
        SR_ERROR("EditorGUI::Init() : failed to allocate/compile script!");
        m_hasErrors = true;
        return false;
    }

    Load();

    m_isInit = true;

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

    if (m_script)
        m_script->OnGUI();

    WidgetManager::Draw();
}

void EditorGUI::Save() {
    if (!m_loaded) {
        return;
    }

    const auto path = Helper::ResourceManager::Instance().GetConfigPath().Concat("EditorWidgets.xml");

    auto document = Helper::Xml::Document::New();
    auto widgets = document.Root().AppendChild("Widgets");

    for (auto&& [name, widget] : GetWidgets())
        widgets.AppendChild("Widget").NAppendAttribute("Name", name).NAppendAttribute("Open", widget->IsOpen());

    document.Save(path.ToString());
}

void EditorGUI::Load() {
    m_loaded = true;

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
        GetWindow<SceneViewer>()->Enable(value);
        m_window->SetGUIEnabled(!m_window->IsGUIEnabled());
        m_enabled = value;
    }
}

void EditorGUI::Update() {
    if (Enabled()) {
        GetWindow<Inspector>()->Update();
    }

    GetWindow<SceneViewer>()->Update();
}

void EditorGUI::OnKeyDown(const KeyDownEvent &event) {
    WidgetManager::OnKeyDown(event);
}

void EditorGUI::OnKeyPress(const KeyPressEvent &event) {
    WidgetManager::OnKeyPress(event);
}

void EditorGUI::OnKeyUp(const KeyUpEvent &event) {
    WidgetManager::OnKeyUp(event);
}


