//
// Created by Nikita on 19.07.2021.
//

#include <Core/Engine.h>

#include <Core/Settings/EditorSettings.h>

#include <Core/GUI/EditorGUI.h>
#include <Core/GUI/AnimatorEditor.h>
#include <Core/GUI/Inspector.h>
#include <Core/GUI/VisualScriptEditor.h>
#include <Core/GUI/WorldEdit.h>
#include <Core/GUI/EngineSettings.h>
#include <Core/GUI/PhysicsMaterialEditor.h>
#include <Core/GUI/EngineStatistics.h>
#include <Core/GUI/Hierarchy.h>
#include <Core/GUI/SceneViewer.h>
#include <Core/GUI/RenderTechniqueEditor.h>
#include <Core/GUI/FileBrowser.h>
#include <Core/GUI/About.h>
#include <Core/GUI/SceneTools.h>

#include <Utils/Common/Features.h>
#include <Utils/ECS/Prefab.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Profile/TracyContext.h>
#include <Utils/World/SceneUpdater.h>

#include <Graphics/Types/Texture.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Window/Window.h>
#include <Graphics/SRSL/Shader.h>

namespace SR_CORE_GUI_NS {
    static SR_UTILS_NS::Path GetNewScenePath() {
        auto&& scenePath = SR_WORLD_NS::Scene::NewScenePath.ConcatExt("scene");

        uint64_t index = 0;
        while (SR_WORLD_NS::Scene::IsExists(scenePath)) {
            scenePath = SR_FORMAT("{}-{}.scene", SR_WORLD_NS::Scene::NewScenePath.CStr(), index);
            ++index;
        }

        return scenePath;
    }

    static SR_UTILS_NS::Path GetNewPrefabPath() {
        auto&& scenePath = SR_WORLD_NS::Scene::NewPrefabPath.ConcatExt("prefab");

        uint64_t index = 0;
        while (SR_WORLD_NS::Scene::IsExists(scenePath)) {
            scenePath = SR_FORMAT("{}-{}.prefab", SR_WORLD_NS::Scene::NewPrefabPath.CStr(), index);
            ++index;
        }

        return scenePath;
    }

    EditorGUI::EditorGUI(const EnginePtr& pEngine)
        : Super()
    {
        m_cachedScenePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("/PreviousScenePath").ConcatExt("cache");

        m_engine = pEngine;

        AddWidget(new FileBrowser());
        AddWidget(new Hierarchy());
        AddWidget(new VisualScriptEditor());
        AddWidget(new Inspector(GetWidget<Hierarchy>()));
        AddWidget(new WorldEdit());
        AddWidget(new EngineSettings());
        AddWidget(new AnimatorEditor());
        AddWidget(new EngineStatistics());
		AddWidget(new PhysicsMaterialEditor());
		AddWidget(new About());
		AddWidget(new SoundDebug());
        AddWidget(new RenderTechniqueEditor());
        AddWidget(new SceneViewer(m_engine, GetWidget<Hierarchy>()));

        for (auto& [id, widget] : m_widgets) {
            Register(widget);
        }

        GetWidget<FileBrowser>()->SetFolder(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
    }

    EditorGUI::~EditorGUI() {
        if (IsInitialized()) {
            DeInit();
        }

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

    void EditorGUI::DeInit() {
        SR_TRACY_ZONE;

        if (!m_isInit) {
            SR_ERROR("EditorGUI::DeInit() : editor gui is not initialized!");
            return;
        }

        SR_INFO("EditorGUI::DeInit() : deinitializing editor gui...");

        for (auto&& [icon, pTexture] : m_icons) {
            pTexture->RemoveUsePoint();
        }
        m_icons.clear();

        m_isInit = false;
    }

    void EditorGUI::Draw() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        if (m_hasErrors || !m_enabled)
            return;

        if (!m_isInit) {
            SR_ERROR("EditorGUI::Draw() : editor gui is not initialized!");
            return;
        }

        if (m_useDocking) {
            DrawDockingSpace();
        }
        else {
            m_dragWindow = false;
        }

        if (m_imGuiDemo) {
            ImGui::ShowDemoWindow(&m_imGuiDemo);
        }

        WidgetManager::Draw();
    }

    void EditorGUI::DrawDockingSpace() {
        m_dragWindow = false;

        ImGuiViewport* pViewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(pViewport->Pos);
        ImGui::SetNextWindowSize(pViewport->Size);
        ImGui::SetNextWindowViewport(pViewport->ID);

        static constexpr ImGuiWindowFlags windowFlags = 0
            | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
            | ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGui::Begin("SpaRcle Engine", nullptr, windowFlags);
        ImGuiID dockMain = ImGui::GetID("Dockspace");

        if (ImGui::BeginMainMenuBar()) {
            ImGuiWindow* pMenuBarWindow = ImGui::FindWindowByName("##MainMenuBar");

            if (m_click == Click::None && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                m_click = pMenuBarWindow->Rect().Contains(ImGui::GetMousePos()) ? Click::Drag : Click::Miss;
            }
            else if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
                m_click = Click::None;
            }

            m_dragWindow = m_click == Click::Drag;

            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

            ImGui::PopStyleVar();

            ImGui::Text(" | ");

            ImGui::Text("%s", "SpaRcle Engine");

            ImGui::Text(" | ");

            DrawMenuBar();

            ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 20);
            ImGui::SetCursorPosY(0);

            auto&& pWindow = m_engine->GetMainWindow()->GetBaseWindow();

            if (ImGui::SmallButton("×")) {
                pWindow->Close();
            }

            ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 45);
            ImGui::SetCursorPosY(0);
            if (pWindow->GetState() == Graphics::WindowState::Default && ImGui::SmallButton("[ ]")) {
                pWindow->Maximize();
            }

            if (pWindow->GetState() == Graphics::WindowState::Maximized && ImGui::SmallButton("[=]")) {
                pWindow->Restore();
            }
            ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 70);
            ImGui::SetCursorPosY(0);
            if (ImGui::SmallButton("_")) {
                pWindow->Collapse();
            }

            {
                ImGui::EndMenuBar();

                ImGuiContext& g = *GImGui;
                if (g.CurrentWindow == g.NavWindow && g.NavLayer == ImGuiNavLayer_Main && !g.NavAnyRequest) {
                    ImGui::FocusTopMostWindowUnderOne(g.NavWindow, nullptr);
                    //ImGui::FocusTopMostWindowUnderOne(g.NavWindow, nullptr, nullptr, ImGuiFocusedFlags_None);
                }

                ImGui::End();
            }
        }

        ImGui::DockSpace(dockMain, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
        ImGui::End();
        ImGui::PopStyleVar(3);
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

        if (auto&& pScene = m_engine->GetScene()) {
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
            if (auto&& pWin = m_engine->GetMainWindow()->GetImplementation<SR_GRAPH_NS::BasicWindowImpl>()) {
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

    SR_GTYPES_NS::Texture* EditorGUI::GetIcon(EditorIcon icon) const {
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
            SR_LOG("EditorGUI::CacheScenePath() : scene path is \"NONE\". Caching this value.");
            return;
        }

        if (scenePath.Contains(SR_WORLD_NS::Scene::RuntimeScenePath.ToStringRef())) {
            return;
        }

        if (scenePath.GetExtension() == SR_UTILS_NS::Prefab::EXTENSION) {
            return;
        }

        if (scenePath.IsEmpty()) {
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
                SR_LOG("EditorGUI::LoadSceneFromCachedPath() : cached file of scene path wasn't found!");
            }
            return false;
        }

        auto&& marshal = SR_HTYPES_NS::Marshal::Load(m_cachedScenePath);
        SR_UTILS_NS::Path scenePath = marshal.Read<std::string>();

        if (scenePath.IsEmpty()) {
            return false;
        }

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
            return m_engine->SetScene(SR_WORLD_NS::Scene::New(scenePath));
        }

        return m_engine->SetScene(SR_WORLD_NS::Scene::Load(scenePath));
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

    void EditorGUI::DrawMenuBar() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));

        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New scene")) {
                m_engine->SetScene(SR_WORLD_NS::Scene::New(GetNewScenePath()));
                CacheScenePath(m_engine->GetScene()->GetPath());
            }

            ImGui::Separator();

            if (ImGui::MenuItem("New prefab")) {
                if (auto&& pScene = m_engine->GetScene(); pScene.RecursiveLockIfValid()) {
                    //TODO: проверку на то, что нынешний префаб не сохранён, чтобы не спамить ими
                    pScene->Save();
                    CacheScenePath(m_engine->GetScene()->GetPath());
                    pScene.Unlock();
                }

                m_engine->SetScene(SR_WORLD_NS::Scene::New(GetNewPrefabPath()));
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Load")) {
                auto&& scenesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();

                if (auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(scenesPath.ToString(), { { "Scene", "scene,prefab" } }); !path.IsEmpty()) {
                    path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetCachePath());
                    path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

                    if (path.GetExtensionView() == "scene") {
                        auto&& folder = SR_UTILS_NS::StringUtils::GetDirToFileFromFullPath(path);

                        if (auto&& pScene = SR_WORLD_NS::Scene::Load(folder)) {
                            m_engine->SetScene(pScene);
                            CacheScenePath(folder);
                        }
                    }
                    else {
                        if (auto&& pScene = SR_WORLD_NS::Scene::Load(path)) {
                            m_engine->SetScene(pScene);
                            CacheScenePath(path);
                        }
                    }
                }
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Save")) {
                if (auto&& pScene = m_engine->GetScene(); pScene.RecursiveLockIfValid()) {
                    pScene->Save();
                    pScene.Unlock();
                }
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Save at")) {
                if (auto&& pScene = m_engine->GetScene(); pScene.RecursiveLockIfValid())
                {
                    const auto scenesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();

                    if (auto&& path = SR_UTILS_NS::FileDialog::Instance().SaveDialog(scenesPath.ToString(), { { "Scene", "scene,prefab" } }); !path.IsEmpty())
                    {
                        path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetCachePath());
                        path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

                        if (pScene->SaveAt(path)) {
                            SR_SYSTEM_LOG("GUISystem::BeginMenuBar() : scene is saved as \"" + path.ToString() + "\"");

                            if (auto&& pSavedScene = SR_WORLD_NS::Scene::Load(path)) {
                                m_engine->SetScene(pSavedScene);
                                CacheScenePath(path);
                            }
                        }
                        else {
                            SR_ERROR("GUISystem::BeginMenuBar() : failed to save scene! \n\tPath: \"" + path.ToString() + "\"");
                        }
                    }

                    pScene.Unlock();
                }
                else {
                    SR_WARN("GUISystem::BeginMenuBar() : scene is not valid!");
                }
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Close scene")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    pScene->Save();
                }
                m_engine->SetScene(SR_WORLD_NS::Scene::Empty());
                CacheScenePath("NONE");
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Clear shaders cache")) {
                SR_SRSL_NS::SRSLShader::ClearShadersCache();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Reload")) {
                m_engine->Reload();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit")) {
                m_engine->GetMainWindow()->GetBaseWindow()->Close();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Editor")) {
            if (ImGui::MenuItem("Empty GameObject")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    pScene->Instance("New GameObject");
                }
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Instance from file")) {
                if (auto&& pScene = m_engine->GetScene(); pScene.RecursiveLockIfValid()) {
                    auto&& resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                    if (auto path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesPath.ToString(), { { "Any model", "prefab,pmx,fbx,obj,blend,dae,abc,stl,ply,glb,gltf,x3d,sfg,bvh,3ds,gltf" } }); !path.IsEmpty()) {
                        /// TODO:Сделать обратимость
                        pScene->InstanceFromFile(path);
                    }
                    pScene.Unlock();
                }
                else {
                    SR_WARN("GUISystem::BeginMenuBar() : scene is not valid!");
                }
            }

            ImGui::EndMenu();
        }

        DrawWindowPage();

        if (ImGui::MenuItem("About")) {
            OpenWidget<About>();
        }

        ImGui::PopStyleVar();

        auto&& io = ImGui::GetIO();

        ImGui::PushItemWidth(115);

        ImGui::LabelText("##FPSLable", "|   FPS: %.2f (%.2gms)", io.Framerate, io.Framerate > 0.f ? 1000.0f / io.Framerate : 0.0f);

        ImGui::PopItemWidth();

        auto&& pBuilder = m_engine->GetSceneBuilder();
        if (pBuilder) {
            auto&& now = SR_HTYPES_NS::Time::Instance().Now();
            auto&& time = now - pBuilder->GetLastBuildTime();

            using ms = std::chrono::duration<double_t, std::milli>;

            const float_t timeLeft = (float_t)std::chrono::duration_cast<ms>(time).count() / (float_t)SR_CLOCKS_PER_SEC;

            ImGui::Text("|   Last build: %.2f sec", timeLeft);
        }
    }

    void EditorGUI::DrawWindowPage() {
        if (ImGui::BeginMenu("Window")) {
            if (ImGui::MenuItem("Assets")) {
                OpenWidget<FileBrowser>();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Hierarchy")) {
                OpenWidget<Hierarchy>();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Inspector")) {
                OpenWidget<Inspector>();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Scene")) {
                OpenWidget<SceneViewer>();
            }


            ImGui::Separator();

            if (ImGui::MenuItem("Sound debug")) {
                OpenWidget<SoundDebug>();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Render Technique")) {
                OpenWidget<RenderTechniqueEditor>();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Animator")) {
                OpenWidget<AnimatorEditor>();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("ImGui Demo Window")) {
                m_imGuiDemo = true;
            }

            ImGui::Separator();

            /// if (ImGui::MenuItem("Animator")) {
            ///    OpenWidget<AnimatorEditor>();
            /// }

            /// ImGui::Separator();

            if (ImGui::MenuItem("World edit")) {
               OpenWidget<WorldEdit>();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Physics material editor")) {
                OpenWidget<PhysicsMaterialEditor>();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Settings")) {
                OpenWidget<EngineSettings>();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Statistics")) {
                OpenWidget<EngineStatistics>();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Reset to default")) {
                ResetToDefault();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Close all")) {
                CloseAllWidgets();
            }

            ImGui::EndMenu();
        }
    }

    SR_GRAPH_GUI_NS::Widget* EditorGUI::GetWidget(const SR_UTILS_NS::StringAtom& name) const {
        for (auto&& [hashCode, pWidget] : m_widgets) {
            if (pWidget->GetName() == name) {
                return pWidget;
            }
        }
        return nullptr;
    }
}
