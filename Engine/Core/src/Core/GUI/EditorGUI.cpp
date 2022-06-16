//
// Created by Nikita on 19.07.2021.
//

#include <Core/GUI/EditorGUI.h>
#include <Core/Engine.h>
#include <Core/GUI/GUISystem.h>
#include <Core/GUI/Inspector.h>
#include <Core/GUI/VisualScriptEditor.h>
#include <Core/GUI/WorldEdit.h>
#include <Core/GUI/EngineSettings.h>
#include <Core/GUI/EngineStatistics.h>
#include <Core/GUI/Hierarchy.h>
#include <Core/GUI/SceneViewer.h>

#include <Utils/Xml.h>

#include <GUI/Editor/FileBrowser.h>
#include <Window/Window.h>
#include <Utils/Common/Features.h>
#include <Utils/ResourceManager/ResourceManager.h>

using namespace SR_CORE_NS::GUI;
using namespace SR_GRAPH_NS::GUI;

EditorGUI::EditorGUI()
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

    Load();

    m_isInit = true;

    return true;
}

bool EditorGUI::Destroy() {
    Save();

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


    if (m_useDocking) {
        m_dragWindow = GUISystem::Instance().BeginDockSpace();
    }
    else {
        m_dragWindow = false;
    }

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

    m_useDocking = SR_UTILS_NS::Features::Instance().Enabled("EditorWidgetsDocking", true);

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
        if (!m_isInit) {
            Init();
        }
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

void EditorGUI::OnMouseDrag(const SR_UTILS_NS::MouseInputData* data) {
    if (m_dragWindow) {
        auto&& drag = data->GetDrag();
        auto&& pos = Graphics::Environment::Get()->GetBasicWindow()->GetPosition();

        pos += drag;

        Graphics::Environment::Get()->GetBasicWindow()->Move(pos.x, pos.y);

        //SR_LOG(SR_UTILS_NS::Format("[%f, %f]", drag.x, drag.y));
    }

    WidgetManager::OnMouseDrag(data);
}

void EditorGUI::OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) {
    WidgetManager::OnKeyDown(data);
}

void EditorGUI::OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) {
    WidgetManager::OnKeyPress(data);
}

void EditorGUI::OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) {
    WidgetManager::OnKeyUp(data);
}

void EditorGUI::CloseAllWindows() {
    for (auto& [id, widget] : m_widgets)
        widget->Close();
}



