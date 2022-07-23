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
#include <Core/GUI/FileBrowser.h>
#include <Window/Window.h>
#include <Utils/Common/Features.h>
#include <Core/Settings/EditorSettings.h>
#include <Types/Texture.h>

using namespace SR_GRAPH_NS::GUI;

namespace SR_CORE_NS::GUI {
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
        for (auto&& [icon, pTexture] : m_icons) {
            if (pTexture->GetCountUses() <= 1 && pTexture->IsEnabledAutoRemove() && !pTexture->IsDestroyed())
                pTexture->Destroy();
        }
        m_icons.clear();

        Save();

        m_isInit = false;

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

        auto&& settings = EditorSettings::Instance();

        for (auto&& [icon, path] : settings.GetIcons()) {
            auto&& pTexture = SR_GTYPES_NS::Texture::Load(path);
            if (!pTexture) {
                SR_WARN("EditorGUI::Load() : icon not found!\n\tPath: " + path.ToString());
                pTexture = SR_GTYPES_NS::Texture::GetNone();
            }

            m_icons[icon] = pTexture;
        }

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
            //m_window->SetGUIEnabled(!m_window->IsGUIEnabled());
            m_enabled = value;
        }
    }

    void EditorGUI::Update() {
        if (Enabled()) {
            GetWindow<Inspector>()->Update();
        }

        GetWindow<SceneViewer>()->Update();
    }

    void EditorGUI::OnMouseMove(const SR_UTILS_NS::MouseInputData* data) {
        if (m_dragWindow) {
            auto&& drag = data->GetDrag();
            auto&& pos = Graphics::Environment::Get()->GetBasicWindow()->GetPosition();

            pos += drag;

            Graphics::Environment::Get()->GetBasicWindow()->Move(pos.x, pos.y);

            //SR_LOG(SR_UTILS_NS::Format("[%f, %f]", drag.x, drag.y));
        }

        WidgetManager::OnMouseMove(data);
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

    SR_GTYPES_NS::Texture *EditorGUI::GetIcon(EditorIcon icon) const {
        if (m_icons.count(icon) == 1) {
            return m_icons.at(icon);
        }

        return SR_GTYPES_NS::Texture::GetNone();
    }

    void *EditorGUI::GetIconDescriptor(EditorIcon icon) const {
        if (auto&& iconTexture = GetIcon(icon)) {
            if (!iconTexture->HasRender()) {
                auto&& render = SR_THIS_THREAD->GetContext()->GetPointer<SR_GRAPH_NS::Render>();


                if (!render) {
                    SRHalt("Is not in the rendering context!");
                    return nullptr;
                }

                render->RegisterTexture(iconTexture);
            }

            if (!iconTexture->GetDescriptor()) {
                iconTexture = SR_GTYPES_NS::Texture::GetNone();

                if (!iconTexture->HasRender()) {
                    auto&& render = SR_THIS_THREAD->GetContext()->GetPointer<SR_GRAPH_NS::Render>();

                    if (!render) {
                        SRHalt("Is not in the rendering context!");
                        return nullptr;
                    }

                    render->RegisterTexture(iconTexture);
                }
            }

            return iconTexture->GetDescriptor();
        }

        return nullptr;
    }
}


