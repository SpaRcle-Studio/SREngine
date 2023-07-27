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
#include <Core/GUI/About.h>
#include <Utils/Common/Features.h>
#include <Core/Settings/EditorSettings.h>

#include <Graphics/Types/Texture.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Window/Window.h>
#include <Core/GUI/AnimatorEditor.h>
#include <Utils/ECS/Prefab.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Profile/TracyContext.h>

namespace SR_CORE_NS::GUI {
    EditorGUI::EditorGUI()
    {
        m_cachedScenePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("/PreviousScenePath").ConcatExt("cache");

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
        AddWidget(new About());

        for (auto& [id, widget] : m_widgets) {
            Register(widget);
        }

        GetWidget<FileBrowser>()->SetFolder(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
    }

    EditorGUI::~EditorGUI() {
        for (auto&& [icon, pTexture] : m_icons) {
            pTexture->RemoveUsePoint();
        }
        m_icons.clear();

        m_isInit = false;

        for (auto& [id, widget] : m_widgets) {
            Remove(widget);
            SR_SAFE_DELETE_PTR(widget);
        }
        m_widgets.clear();
    }

    bool EditorGUI::Init() {
        SR_TRACY_ZONE;

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
        SR_TRACY_ZONE;
        SR_LOCK_GUARD

        if (m_hasErrors || !m_enabled)
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
            const auto path = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/EditorWidgets.xml");

            auto document = SR_XML_NS::Document::New();
            auto widgets = document.Root().AppendChild("Widgets");

            for (auto&& [name, widget] : GetWidgets())
                widgets.AppendChild("Widget").NAppendAttribute("Name", name).NAppendAttribute("Open", widget->IsOpen());

            document.Save(path.ToString());
        }

        if (auto&& pScene = Engine::Instance().GetScene()) {
            CacheScenePath(pScene->GetPath());
        }
    }

    void EditorGUI::Load() {
        SR_TRACY_ZONE;

        m_loaded = true;

        auto&& settings = EditorSettings::Instance();

        for (auto&& [icon, path] : settings.GetIcons()) {
            auto&& pTexture = SR_GTYPES_NS::Texture::Load(path);
            if (!pTexture) {
                SR_WARN("EditorGUI::Load() : icon wasn't not found!\n\tPath: " + path.ToString());
                pTexture = m_context->GetNoneTexture();
            }

            pTexture->AddUsePoint();

            m_icons[icon] = pTexture;
        }

        m_useDocking = SR_UTILS_NS::Features::Instance().Enabled("EditorWidgetsDocking", true);

        ReloadWindows();
    }

    void EditorGUI::Enable(bool value) {
        if (m_enabled != value) {
            if (auto&& pViewer = GetWidget<SceneViewer>()) {
                pViewer->Enable(value);
            }
            m_enabled = value;
        }
    }

    void EditorGUI::FixedUpdate() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        if (auto&& pViewer = GetWidget<SceneViewer>()) {
            pViewer->FixedUpdate();
        }
    }

    void EditorGUI::Update(float_t dt) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        if (Enabled()) {
            GetWidget<Hierarchy>()->Update(dt);
            GetWidget<Inspector>()->Update(dt);
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

    void EditorGUI::CacheScenePath(const SR_UTILS_NS::Path& scenePath) {
        if (scenePath.ToStringView() == "NONE") {
            SR_LOG("EditorGUI::LoadSceneFromCachedPath : scene path is \"NONE\". Caching this value.");
            return;
        }

        if (scenePath.Contains(SR_WORLD_NS::Scene::RuntimeScenePath.ToStringRef())) {
            return;
        }

        if (!SR_WORLD_NS::Scene::IsExists(scenePath)) {
            SR_ERROR("EditorGUI::LoadSceneFromCachedPath : scene path is not valid or does not exist! Caching is aborted.");
            return;
        }

        if (scenePath.GetExtension() == SR_UTILS_NS::Prefab::EXTENSION) {
            return;
        }

        auto&& pMarshal = new SR_HTYPES_NS::Marshal();

        pMarshal->Write<std::string>(scenePath.ToString());
        pMarshal->Save(m_cachedScenePath.ToString());

        SR_SAFE_DELETE_PTR(pMarshal);
    }

    bool EditorGUI::LoadSceneFromCachedPath() {
        if (!m_cachedScenePath.Valid() && !m_cachedScenePath.Exists()) {
            if (SR_UTILS_NS::Debug::Instance().GetLevel() == SR_UTILS_NS::Debug::Level::High) {
                SR_LOG("EditorGUI::LoadSceneFromCachedPath : cached file of scene path wasn't found!");
            }
            return false;
        }

        auto&& marshal = SR_HTYPES_NS::Marshal::Load(m_cachedScenePath);
        SR_UTILS_NS::Path scenePath = marshal.Read<std::string>();

        if (scenePath.ToStringView() == "NONE") {
            SR_LOG("EditorGUI::LoadSceneFromCachedPath() : cached scene path is \"NONE\". No scene to load.");
            return false;
        }

        if (!SR_WORLD_NS::Scene::IsExists(scenePath)) {
            SR_WARN("EditorGUI::LoadSceneFromCachedPath() : cached path is not usable! \n\tPath: " + scenePath.ToStringRef() + "\n\tUsing default scene.");
            scenePath = SR_WORLD_NS::Scene::NewScenePath.ConcatExt("scene");
        }

        if (!SR_WORLD_NS::Scene::IsExists(scenePath)) {
            SR_ERROR("EditorGUI::LoadSceneFromCachedPath() : default scene does not exist! \n\tCreating new one by path: " + scenePath.ToStringRef());
            return Engine::Instance().SetScene(SR_WORLD_NS::Scene::New(scenePath));
        }

        return Engine::Instance().SetScene(SR_WORLD_NS::Scene::Load(scenePath));
    }

    void EditorGUI::ReloadWindows() {
        const auto path = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/EditorWidgets.xml");

        if (!path.Exists()) {
            path.Create();
            auto document = SR_XML_NS::Document::New();
            auto widgets = document.Root().AppendChild("Widgets");

            for (auto&& [name, widget] : GetWidgets())
                widgets.AppendChild("Widget").NAppendAttribute("Name", name).NAppendAttribute("Open", true);

            document.Save(path.ToString());
        }

        auto document = SR_XML_NS::Document::Load(path);
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

    void EditorGUI::ResetToDefault() {
        const auto&& defaultConfigPath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/ImGuiEditor.config");
        const auto&& defaultWidgetsPath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/EditorWidgets.xml");

        SR_UTILS_NS::Platform::Copy(SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Editor/Configs/ImGuiEditor.config"),defaultConfigPath);
        SR_UTILS_NS::Platform::Copy(SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Editor/Configs/EditorWidgets.xml"), defaultWidgetsPath);

        ReloadWindows();
        ShowAll();

        ImGuiContext& g = *GImGui;
        if (g.IO.IniFilename)
            ImGui::LoadIniSettingsFromDisk(g.IO.IniFilename);
        g.SettingsLoaded = true;
    }
}
