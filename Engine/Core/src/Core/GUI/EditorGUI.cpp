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
#include <Utils/Common/Features.h>
#include <Core/Settings/EditorSettings.h>

#include <Graphics/Types/Texture.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Window/Window.h>
#include <Core/GUI/AnimatorEditor.h>

namespace SR_CORE_NS::GUI {
    EditorGUI::EditorGUI()
    {
        m_window = Engine::Instance().GetWindow();

        AddWidget(new FileBrowser());
        AddWidget(new Hierarchy());
        AddWidget(new VisualScriptEditor());
        AddWidget(new SceneViewer(m_window, GetWidget<Hierarchy>()));
        AddWidget(new Inspector(GetWidget<Hierarchy>()));
        AddWidget(new WorldEdit());
        AddWidget(new EngineSettings());
        AddWidget(new AnimatorEditor());
        AddWidget(new EngineStatistics());

        for (auto& [id, widget] : m_widgets) {
            Register(widget);
        }

        GetWidget<FileBrowser>()->SetFolder(Helper::ResourceManager::Instance().GetResPath());
    }

    EditorGUI::~EditorGUI() {
        for (auto&& [icon, pTexture] : m_icons) {
            pTexture->RemoveUsePoint();
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

        if (!SRVerifyFalse2(!(m_context = SR_THIS_THREAD->GetContext()->GetValue<RenderContextPtr>()), "Is not render context!")) {
            m_hasErrors = true;
            return false;
        }

        Load();

        m_isInit = true;

        return true;
    }

    void EditorGUI::Draw() {
        SR_LOCK_GUARD

        if (m_hasErrors)
            return;

        if (!m_isInit) {
            if (!Init())
                return;
        }

        if (m_useDocking) {
            m_dragWindow = GUISystem::Instance().BeginDockSpace(m_window->GetImplementation<Graphics::BasicWindowImpl>());
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

        /// widgets
        {
            const auto path = Helper::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/EditorWidgets.xml");

            auto document = Helper::Xml::Document::New();
            auto widgets = document.Root().AppendChild("Widgets");

            for (auto&& [name, widget] : GetWidgets())
                widgets.AppendChild("Widget").NAppendAttribute("Name", name).NAppendAttribute("Open", widget->IsOpen());

            document.Save(path.ToString());
        }

        /// scene 
        if (!m_scenePath.Empty())
        {
            const auto path = Helper::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/Scene.xml");

            auto document = Helper::Xml::Document::New();
            auto sceneXml = document.Root().AppendChild("Scene");

            sceneXml.AppendAttribute(m_scenePath);

            document.Save(path.ToString());
        }
    }

    void EditorGUI::Load() {
        m_loaded = true;

        auto&& settings = EditorSettings::Instance();

        for (auto&& [icon, path] : settings.GetIcons()) {
            auto&& pTexture = SR_GTYPES_NS::Texture::Load(path);
            if (!pTexture) {
                SR_WARN("EditorGUI::Load() : icon not found!\n\tPath: " + path.ToString());
                pTexture = m_context->GetNoneTexture();
            }

            pTexture->AddUsePoint();

            m_icons[icon] = pTexture;
        }

        m_useDocking = SR_UTILS_NS::Features::Instance().Enabled("EditorWidgetsDocking", true);

        const auto path = Helper::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/EditorWidgets.xml");

        if (!path.Exists()) {
            path.Make();
            auto document = Helper::Xml::Document::New();
            auto widgets = document.Root().AppendChild("Widgets");

            for (auto&& [name, widget] : GetWidgets())
                widgets.AppendChild("Widget").NAppendAttribute("Name", name).NAppendAttribute("Open", true);

            document.Save(path.ToString());
        }

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
            if (auto&& pViewer = GetWidget<SceneViewer>()) {
                pViewer->Enable(value);
            }
            m_enabled = value;
        }
    }

    void EditorGUI::Update() {
        SR_LOCK_GUARD

        if (Enabled()) {
            GetWidget<Hierarchy>()->Update();
            GetWidget<Inspector>()->Update();
        }

        if (auto&& pViewer = GetWidget<SceneViewer>()) {
            pViewer->Update();
        }
    }

    void EditorGUI::OnMouseMove(const SR_UTILS_NS::MouseInputData* data) {
        if (m_dragWindow) {
            if (auto&& pWin = m_window->GetImplementation<SR_GRAPH_NS::BasicWindowImpl>()) {
                auto&& drag = data->GetDrag();
                auto &&pos = pWin->GetPosition();
                pos += drag;
                pWin->Move(pos.x, pos.y);
            }
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

    void EditorGUI::CloseAllWidgets() {
        for (auto& [id, widget] : m_widgets) {
            widget->Close();
        }
    }

    SR_GTYPES_NS::Texture *EditorGUI::GetIcon(EditorIcon icon) const {
        if (m_icons.count(icon) == 1) {
            return m_icons.at(icon);
        }

        return m_context->GetNoneTexture();
    }

    void *EditorGUI::GetIconDescriptor(EditorIcon icon) const {
        if (auto&& iconTexture = GetIcon(icon)) {
            if (!iconTexture->GetDescriptor()) {
                iconTexture = m_context->GetNoneTexture();
            }

            return iconTexture->GetDescriptor();
        }

        return nullptr;
    }
}


