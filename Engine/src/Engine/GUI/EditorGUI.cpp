//
// Created by Nikita on 19.07.2021.
//

#include <Engine/Engine.h>

#include <Engine/Settings/EditorSettings.h>
#include <Engine/Settings/ProjectSettings.h>

#include <Engine/GUI/EditorGUI.h>
#include <Engine/GUI/SoundDebug.h>
#include <Engine/GUI/Inspector.h>
#include <Engine/GUI/EngineSettings.h>
#include <Engine/GUI/EngineStatistics.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/AssetInspector.h>
#include <Engine/GUI/AssetsStore.h>
#include <Engine/GUI/TextureInspector.h>
#include <Engine/GUI/SceneViewer.h>
#include <Engine/GUI/FileBrowser.h>
#include <Engine/GUI/About.h>
#include <Engine/GUI/Welcome.h>
#include <Engine/GUI/CreateNewProject.h>
#include <Engine/GUI/GameBuildExporter.h>
#include <Engine/GUI/SceneTools.h>
#include <Engine/EngineCommands.h>
#include <Engine/UI/UIButton.h>
#include <Engine/UI/UIScrollRect.h>

#include <Graphics/Types/Texture.h>
#include <Graphics/Types/RenderTarget.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/Types/Mesh.h>
#include <Graphics/Types/SkyboxComponent.h>
#include <Graphics/Clouds/VolumetricClouds.h>
#include <Graphics/Fog/VolumetricFog.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Window/BasicWindowImpl.h>
#include <Graphics/Window/Window.h>
#include <Graphics/SRSL/Shader.h>
#include <Graphics/Lighting/DirectionalLight.h>
#include <Graphics/Lighting/PointLight.h>
#include <Graphics/Lighting/SpotLight.h>
#include <Graphics/Lighting/AreaLight.h>
#include <Graphics/Lighting/ProbeLight.h>
#include <Graphics/Particles/ParticleEmitter.h>
#include <Graphics/Font/Text.h>
#include <Graphics/Font/TextMesh.h>
#include <Graphics/Types/Geometry/Sprite.h>

#include <Physics/3D/Rigidbody3D.h>

#include <Scripting/Base/ScriptSystem.h>

#include <Utils/Common/Features.h>
#include <Utils/UI/LayoutGroup.h>
#include <Utils/UI/LayoutElement.h>
#include <Utils/ECS/Prefab.h>
#include <Utils/ECS/TransformRect.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Platform/Process.h>
#include <Utils/FileSystem/FileDialog.h>
#include <Utils/Profile/TracyContext.h>
#include <Utils/World/SceneUpdater.h>
#include <Utils/World/ScenePrefabLogic.h>
#include <Utils/Common/StringAtomLiterals.h>
#include <Utils/Common/CLIManager.h>
#include <Utils/Common/StoreUtils.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/Resources/Xml.h>

#include <Enum/EditorIcon.hpp>

namespace SR_CORE_GUI_NS {
    /// Группы меню Window (имена фабрик виджетов)
    static const std::array<SR_UTILS_NS::StringAtom, 4> g_mainWindowWidgets = {
        "SceneViewer", "Hierarchy", "Inspector", "FileBrowser"
    };

    static const std::array<SR_UTILS_NS::StringAtom, 3> g_editorWindowWidgets = {
        "AnimatorEditor", "AnimatorEditorStateMachine", "FluxEditor"
    };

    static const std::array<SR_UTILS_NS::StringAtom, 3> g_inspectorWindowWidgets = {
        "AssetInspector", "TextureInspector", "RawMeshInspector"
    };

    static const std::array<SR_UTILS_NS::StringAtom, 2> g_debugWindowWidgets = {
        "EngineStatistics", "SoundDebug"
    };

    /// Открываются из File/Tools/Help, в Window не дублируются
    static const std::array<SR_UTILS_NS::StringAtom, 7> g_nonWindowWidgets = {
        "About", "Welcome", "CreateNewProject", "GameBuildExporter", "AssetsStore", "EngineSettings", "WidgetContainer"
    };

    static const std::array<std::span<const SR_UTILS_NS::StringAtom>, 5> g_knownWidgetGroups = {
        g_mainWindowWidgets, g_editorWindowWidgets, g_inspectorWindowWidgets, g_debugWindowWidgets, g_nonWindowWidgets
    };

    static bool IsWidgetInGroups(SR_UTILS_NS::StringAtom name) {
        for (auto&& group : g_knownWidgetGroups) {
            for (auto&& groupName : group) {
                if (groupName == name) {
                    return true;
                }
            }
        }

        return false;
    }

    static SR_UTILS_NS::Path GetNewPrefabPath() {
        auto&& scenePath = CoreResLoader::GetCachePath().Concat(SR_WORLD_NS::Scene::NewPrefabPath).ConcatExt("prefab");

        uint64_t index = 0;
        while (scenePath.IsExists()) {
            scenePath = SR_FORMAT("{}-{}.prefab", CoreResLoader::GetCachePath().Concat(SR_WORLD_NS::Scene::NewPrefabPath), index);
            ++index;
        }

        return scenePath;
    }

    EditorGUI::EditorGUI(const EnginePtr& pEngine)
        : Super()
        , m_engine(pEngine)
    {
        m_pSettings = SR_UTILS_NS::Asset::Load<EditorSettings>("Editor/Configs/EditorSettings.sras");
        if (m_pSettings) {
            m_pSettings->AddUsePoint();
            SR_IMMEDIATE_GUI_NS::SetTheme(m_pSettings->GetTheme().GetId());
        }

        m_cachedScenePath = SR_PLATFORM_NS::GetApplicationUserDataDirectory()
            .Concat("User")
            .Concat(SR_PLATFORM_NS::GetApplicationInfo().project)
            .Concat("PreviousScenePath.cache");
    }

    EditorGUI::~EditorGUI() {
        if (IsInitialized()) {
            DeInit();
        }

        AssetsStore::UnMountPackages(this);

        if (m_pSettings) {
            m_pSettings->RemoveUsePoint();
            m_pSettings = nullptr;
        }
    }

    bool EditorGUI::Init() {
        SR_TRACY_ZONE;

        if (!Super::Init()) {
            return false;
        }

        if (m_isInit) {
            SR_ERROR("EditorGUI::Init() : editor gui is already initialized!");
            return false;
        }

        SR_INFO("EditorGUI::Init() : initializing editor gui...");

        m_context = (SR_GRAPH_NS::RenderContext*)SR_UTILS_NS::StoreUtils::Temp::GetPointer("RenderContext");
        if (!m_context) {
            SRHalt("EditorGUI::Init() : failed to get render context!");
            m_hasErrors = true;
            return false;
        }

        Load();

        m_windowPageWidgets.clear();
        for (auto&& [name, pWidget] : GetWidgets()) {
            if (name.empty() || !pWidget) {
                SRHalt("EditorGUI::Init() : invalid widget name or pointer!");
                continue;
            }
            if (IsWidgetInGroups(name)) {
                continue;
            }
            m_windowPageWidgets.emplace_back(name, pWidget->GetName());
        }
        std::stable_sort(m_windowPageWidgets.begin(), m_windowPageWidgets.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.second.ToStringView() < rhs.second.ToStringView();
        });

        m_isInit = true;

        AssetsStore::ReMountPackages(this);

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

        Super::DeInit();
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

        if (m_showMetricsWindow) {
            SR_IMMEDIATE_GUI_NS::ShowMetricsWindow(&m_showMetricsWindow);
        }

        if (!m_welcomeChecked) {
            ShowWelcomeOnFirstLaunch();
        }

        WidgetManager::Draw();
    }

    void EditorGUI::ShowWelcomeOnFirstLaunch() {
        m_welcomeChecked = true;

        auto&& cliManager = SR_UTILS_NS::CLIManager::Instance();
        if (cliManager.IsHeadlessMode() || cliManager.IsFlagPresent(SR_UTILS_NS::CLIFlags::UnitTests)) {
            return;
        }

        if (SR_UTILS_NS::StoreUtils::User::GetBool(Welcome::ShownStoreKey, false)) {
            return;
        }

        SR_LOG("EditorGUI::ShowWelcomeOnFirstLaunch() : first launch, showing welcome window.");

        SR_UTILS_NS::StoreUtils::User::SetBool(Welcome::ShownStoreKey, true);
        SR_UTILS_NS::StoreUtils::Storage::Instance().Save();

        OpenWidget<Welcome>();
    }

    void EditorGUI::DrawDockingSpace() {
        SR_TRACY_ZONE;
        m_dragWindow = false;

        SR_IMMEDIATE_GUI_NS::BeginDocking();

        if (SR_IMMEDIATE_GUI_NS::BeginMainMenuBar()) {
            if (SR_IMMEDIATE_GUI_NS::IsMouseDragging(SR_IMMEDIATE_GUI_NS::MouseButton::Left) && SR_IMMEDIATE_GUI_NS::IsWindowHovered()) {
                m_click = Click::Drag;
            }
            else if (SR_IMMEDIATE_GUI_NS::IsMouseReleased(SR_IMMEDIATE_GUI_NS::MouseButton::Left)) {
                m_click = Click::None;
            }

            m_dragWindow = m_click == Click::Drag;

            SR_IMMEDIATE_GUI_NS::BeginHorizontal("EditorGUI::MainMenuBar");

            SR_IMMEDIATE_GUI_NS::Text(" | ");
            SR_IMMEDIATE_GUI_NS::Text("%s", "SpaRcle Engine");
            SR_IMMEDIATE_GUI_NS::Text(" | ");

            DrawMenuBar();

        #ifndef SR_EMSCRIPTEN
            SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameRounding, 0.f);
            SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, { 0.f, 0.f });
            SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameBorderSize, 1.f);

            SR_IMMEDIATE_GUI_NS::Spring();

            auto&& pWindow = m_engine->GetMainWindow()->GetBaseWindow();

            SR_MATH_NS::FVector2 buttonSize = { SR_IMMEDIATE_GUI_NS::GetFontSize() * 3.0f, 0.f };

            if (SR_IMMEDIATE_GUI_NS::Button("_", buttonSize)) {
                pWindow->Collapse();
            }

            if (pWindow->GetState() == Graphics::WindowState::Default && SR_IMMEDIATE_GUI_NS::Button("[ ]", buttonSize)) {
                pWindow->Maximize();
            }
            else if (pWindow->GetState() == Graphics::WindowState::Maximized && SR_IMMEDIATE_GUI_NS::Button("[=]", buttonSize)) {
                pWindow->Restore();
            }

            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Button, { 0.8f, 0.1f, 0.1f, 1.f });
            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonHovered, { 0.9f, 0.1f, 0.1f, 1.f });
            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonActive, { 1.f, 0.1f, 0.1f, 1.f });
            if (SR_IMMEDIATE_GUI_NS::Button("×", buttonSize)) {
                SR_LOG("EditorGUI::DrawDockingSpace() : close button was clicked!");
                m_engine->StopEngine();
            }
            SR_IMMEDIATE_GUI_NS::PopStyleColor(3);

            SR_IMMEDIATE_GUI_NS::PopStyleVar(3);
        #endif
            SR_IMMEDIATE_GUI_NS::EndHorizontal();

            SR_IMMEDIATE_GUI_NS::EndMenuBar();
            SR_IMMEDIATE_GUI_NS::FocusTopMostWindowUnderOne();
            SR_IMMEDIATE_GUI_NS::End();
        }

        SR_IMMEDIATE_GUI_NS::EndDocking();
    }

    void EditorGUI::Save() {
        if (!m_loaded) {
            return;
        }

        /// widgets
        {
            SR_UTILS_NS::Path path = SR_PLATFORM_NS::GetApplicationUserDataDirectory()
                .Concat("User")
                .Concat(SR_PLATFORM_NS::GetApplicationInfo().project)
                .Concat("Editor")
                .Concat("EditorWidgets.xml");

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

        if (m_pSettings) {
            for (auto&& [icon, iconInfo] : m_pSettings->GetIcons()) {
                if (m_icons.count(icon) == 1) {
                    SRHalt("EditorGUI::Load() : icon already loaded! Icon: {}", icon);
                    continue;
                }

                auto&& pTexture = CoreResLoader::Load<SR_GTYPES_NS::Texture>(iconInfo.path);
                if (!pTexture) {
                    SR_WARN("EditorGUI::Load() : icon wasn't not found!\n\tPath: {}", iconInfo.path);
                    pTexture = m_context->GetNoneTexture();
                }

                pTexture->AddUsePoint();

                m_icons[icon] = pTexture;
            }
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
            if (auto&& pWidget = GetWidget<Hierarchy>()) {
                pWidget->Update(dt);
            }
            if (auto&& pWidget = GetWidget<Inspector>()) {
                pWidget->Update(dt);
            }
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

    const SR_GTYPES_NS::Texture* EditorGUI::GetIcon(EditorIcon icon) const {
        if (m_icons.count(icon) == 1) {
            return m_icons.at(icon).Get();
        }

        return m_context->GetNoneTexture().Get();
    }

    void *EditorGUI::GetIconDescriptor(EditorIcon icon) const {
        if (auto&& pIconTexture = const_cast<SR_GTYPES_NS::Texture*>(GetIcon(icon))) {
            if (!pIconTexture->CanBeUsed() || !pIconTexture->GetDescriptor()) {
                pIconTexture = m_context->GetNoneTexture().Get();
            }

            return pIconTexture->GetDescriptor();
        }

        return nullptr;
    }

    void EditorGUI::CacheScenePath(const SR_UTILS_NS::Path& scenePath) {
        if (scenePath.ToStringView() == "NONE") {
            SR_LOG("EditorGUI::CacheScenePath() : scene path is \"NONE\". Caching this value.");
            return;
        }

        if (scenePath.Contains(SR_WORLD_NS::Scene::RuntimeScenePath)) {
            return;
        }

        if (scenePath.GetExtension() == SR_UTILS_NS::Prefab::GetMetaStatic()->GetExtension()) {
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
        if (!m_cachedScenePath.IsFile()) {
            if (SR_UTILS_NS::Debug::Instance().GetLevel() == SR_UTILS_NS::Debug::Level::High) {
                SR_LOG("EditorGUI::LoadSceneFromCachedPath() : cached file of scene path wasn't found!");
            }
            return false;
        }

        auto&& marshal = SR_HTYPES_NS::Marshal::Load(m_cachedScenePath);
        if (!marshal) {
            SR_ERROR("EditorGUI::LoadSceneFromCachedPath() : failed to load cached scene path!");
            return false;
        }
        SR_UTILS_NS::Path scenePath = marshal.Read<SR_UTILS_NS::String>();

        if (scenePath.IsEmpty()) {
            return false;
        }

        if (scenePath.ToStringView() == "NONE") {
            SR_LOG("EditorGUI::LoadSceneFromCachedPath() : cached scene path is \"NONE\". No scene to load.");
            return false;
        }

        if (!SR_UTILS_NS::VFS::Instance().IsExists(scenePath)) {
            SR_LOG("EditorGUI::LoadSceneFromCachedPath() : cached scene no longer exists!\n\tPath: {}", scenePath);
            return false;
        }

        auto&& pScene = SR_WORLD_NS::Scene::LoadScene(scenePath);
        if (!pScene) {
            SR_ERROR("EditorGUI::LoadSceneFromCachedPath() : failed to load scene by path: {}", scenePath);
            return false;
        }

        m_engine->AddSceneToQueue(pScene);
        return true;
    }

    void EditorGUI::ReloadWindows() {
        SR_UTILS_NS::Path path = SR_PLATFORM_NS::GetApplicationUserDataDirectory()
            .Concat("User")
            .Concat(SR_PLATFORM_NS::GetApplicationInfo().project)
            .Concat("Editor")
            .Concat("EditorWidgets.xml");

        if (!path.IsFile()) {
            auto document = SR_XML_NS::Document::New();
            auto widgets = document.Root().AppendChild("Widgets");

            for (auto&& [name, widget] : GetWidgets())
                widgets.AppendChild("Widget").NAppendAttribute("Name", name).NAppendAttribute("Open", true);

            document.Save(path);
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

        /// приветствие открывается только явно (первый запуск или Help), а не из сохраненной раскладки
        if (auto&& pWelcome = GetWidget<Welcome>()) {
            pWelcome->Close();
        }
    }

    void EditorGUI::ResetToDefault() {
        SR_UTILS_NS::Path defaultConfigPath = SR_PLATFORM_NS::GetApplicationUserDataDirectory()
            .Concat("User")
            .Concat(SR_PLATFORM_NS::GetApplicationInfo().project)
            .Concat("Editor")
            .Concat("ImGuiEditor.config");

        SR_UTILS_NS::Path defaultWidgetsPath = SR_PLATFORM_NS::GetApplicationUserDataDirectory()
            .Concat("User")
            .Concat(SR_PLATFORM_NS::GetApplicationInfo().project)
            .Concat("Editor")
            .Concat("EditorWidgets.xml");

        SR_UTILS_NS::VFS::Instance().Copy(SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Editor/Configs/ImGuiEditor.config"), defaultConfigPath);
        SR_UTILS_NS::VFS::Instance().Copy(SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Editor/Configs/EditorWidgets.xml"), defaultWidgetsPath);

        ReloadWindows();
        ShowAll();

        SR_IMMEDIATE_GUI_NS::LoadIniSettingsFromDisk();
    }

    void EditorGUI::DrawEditorInstanceMenu() {
        SR_TRACY_ZONE;

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Instance from file")) {
            if (auto&& pScene = m_engine->GetScene()) {
                auto&& resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                if (auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesPath.ToString(), { { "Any model", "prefab,pmx,fbx,obj,blend,dae,abc,stl,ply,glb,gltf,x3d,sfg,bvh,3ds,gltf" } }); !path.IsEmpty()) {
                    InstantiateSO(pScene->InstanceFromFile(path));
                }
            }
            else {
                SR_WARN("GUISystem::BeginMenuBar() : scene is not valid!");
            }
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::BeginMenu("UI")) {
            if (SR_IMMEDIATE_GUI_NS::BeginMenu("Elements")) {
                static SR_UTILS_NS::StringView presets[] = {
                    "Fill",
                    "Top Left",
                    "Top Center",
                    "Top Right",
                    "Middle Left",
                    "Middle Center",
                    "Middle Right",
                    "Bottom Left",
                    "Bottom Center",
                    "Bottom Right"
                };
                for (uint32_t i = 0; i < sizeof(presets) / sizeof(presets[0]); ++i) {
                    if (SR_IMMEDIATE_GUI_NS::MenuItem(presets[i].c_str())) {
                        if (auto&& pScene = m_engine->GetScene()) {
                            auto&& pSO = pScene->InstanceGameObject(presets[i]);
                            auto&& pTransform = new SR_UTILS_NS::TransformRect();
                            pTransform->SetAnchors(SR_UTILS_NS::GetRectAnchorsPresets()[i]);
                            pSO->SetTransform(pTransform);
                            InstantiateSO(pSO.StaticCast<SR_UTILS_NS::SceneObject>());
                        }
                    }
                    SR_IMMEDIATE_GUI_NS::Separator();
                }
                if (SR_IMMEDIATE_GUI_NS::MenuItem("Custom")) {
                    if (auto&& pScene = m_engine->GetScene()) {
                        auto&& pSO = pScene->InstanceGameObject("Custom");
                        pSO->SetTransform(new SR_UTILS_NS::TransformRect());
                        InstantiateSO(pSO.StaticCast<SR_UTILS_NS::SceneObject>());
                    }
                }
                SR_IMMEDIATE_GUI_NS::EndMenu();
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::BeginMenu("Layouts")) {
                if (SR_IMMEDIATE_GUI_NS::MenuItem("Vertical layout group")) {
                    if (auto&& pScene = m_engine->GetScene()) {
                        auto&& pSO = pScene->InstanceGameObject("Vertical layout group"_atom);
                        auto&& pGroup = pSO->AddComponent<SR_UTILS_NS::LayoutGroup>();
                        pGroup->SetDirection(SR_UTILS_NS::LayoutGroupDirection::Vertical);
                        pSO->SetTransform(new SR_UTILS_NS::TransformRect());
                        InstantiateSO(pSO.StaticCast<SR_UTILS_NS::SceneObject>());
                    }
                }

                SR_IMMEDIATE_GUI_NS::Separator();

                if (SR_IMMEDIATE_GUI_NS::MenuItem("Horizontal layout group")) {
                    if (auto&& pScene = m_engine->GetScene()) {
                        auto&& pSO = pScene->InstanceGameObject("Horizontal layout group"_atom);
                        auto&& pGroup = pSO->AddComponent<SR_UTILS_NS::LayoutGroup>();
                        pGroup->SetDirection(SR_UTILS_NS::LayoutGroupDirection::Horizontal);
                        pSO->SetTransform(new SR_UTILS_NS::TransformRect());
                        InstantiateSO(pSO.StaticCast<SR_UTILS_NS::SceneObject>());
                    }
                }

                SR_IMMEDIATE_GUI_NS::Separator();

                if (SR_IMMEDIATE_GUI_NS::MenuItem("Layout group")) {
                    if (auto&& pScene = m_engine->GetScene()) {
                        auto&& pSO = pScene->InstanceGameObject("Layout group"_atom);
                        auto&& pGroup = pSO->AddComponent<SR_UTILS_NS::LayoutGroup>();
                        pSO->SetTransform(new SR_UTILS_NS::TransformRect());
                        InstantiateSO(pSO.StaticCast<SR_UTILS_NS::SceneObject>());
                    }
                }

                SR_IMMEDIATE_GUI_NS::Separator();

                if (SR_IMMEDIATE_GUI_NS::MenuItem("Layout element")) {
                    if (auto&& pScene = m_engine->GetScene()) {
                        auto&& pSO = pScene->InstanceGameObject("Layout element"_atom);
                        pSO->AddComponent<SR_UTILS_NS::LayoutElement>();
                        pSO->SetTransform(new SR_UTILS_NS::TransformRect());
                        InstantiateSO(pSO.StaticCast<SR_UTILS_NS::SceneObject>());
                    }
                }

                SR_IMMEDIATE_GUI_NS::EndMenu();
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Canvas")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pSO = pScene->InstanceGameObject("Canvas"_atom);
                    pSO->AddComponent<SR_GRAPH_UI_NS::Canvas>();
                    pSO->AddComponent<SR_GRAPH_UI_NS::CanvasScaler>();
                    pSO->SetTransform(new SR_UTILS_NS::TransformRect());
                    pSO->SetLayer("UI"_atom);
                    InstantiateSO(pSO.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Scroll View")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pSO = pScene->InstanceFromFile("Engine/Prefabs/ScrollView.prefab").StaticCast<SR_UTILS_NS::SceneObject>();
                    InstantiateSO(pSO);
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Button")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pSO = pScene->InstanceFromFile("Engine/Prefabs/Button.prefab").StaticCast<SR_UTILS_NS::SceneObject>();
                    InstantiateSO(pSO);
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Text")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pSO = pScene->InstanceGameObject("Text"_atom);
                    if (auto&& pText = pSO->AddComponent<SR_GTYPES_NS::Text>()) {
                        pText->SetText(SR_UTILS_NS::StringView("Text"));
                    }
                    pSO->SetTransform(new SR_UTILS_NS::TransformRect());
                    InstantiateSO(pSO.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Text Mesh")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pSO = pScene->InstanceGameObject("Text Mesh"_atom);
                    if (auto&& pText = pSO->AddComponent<SR_GTYPES_NS::TextMesh>()) {
                        pText->SetText("Text");
                    }
                    pSO->SetTransform(new SR_UTILS_NS::TransformRect());
                    InstantiateSO(pSO.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Sprite")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pSO = pScene->InstanceGameObject("Sprite"_atom);
                    pSO->AddComponent<SR_GTYPES_NS::Sprite>();
                    pSO->SetTransform(new SR_UTILS_NS::TransformRect());
                    InstantiateSO(pSO.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::EndMenu();
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::BeginMenu("Instantiate")) {
            if (SR_IMMEDIATE_GUI_NS::MenuItem("Empty")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    InstantiateSO(pScene->InstanceGameObject("New GameObject"_atom).StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Cube")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Cube"_atom);
                    if (auto&& pRigidbody = pGameObject->AddComponent<SR_PHYSICS_NS::Types::Rigidbody3D>()) {
                        pRigidbody->SetMass(1.0f);
                        pRigidbody->AddCollider(SR_PHYSICS_NS::ShapeType::Box3D);
                    }

                    auto&& meshes = SR_GTYPES_NS::Mesh::Load("Engine/Models/cube.obj");
                    for (auto&& pMesh : meshes) {
                        pGameObject->AddComponent(pMesh.StaticCast<SR_UTILS_NS::Component>());
                    }
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Sphere")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Sphere"_atom);
                    if (auto&& pRigidbody = pGameObject->AddComponent<SR_PHYSICS_NS::Types::Rigidbody3D>()) {
                        pRigidbody->SetMass(1.0f);
                        pRigidbody->AddCollider(SR_PHYSICS_NS::ShapeType::Sphere3D);
                    }

                    auto&& meshes = SR_GTYPES_NS::Mesh::Load("Engine/Models/sphere.obj");
                    for (auto&& pMesh : meshes) {
                        pGameObject->AddComponent(pMesh.StaticCast<SR_UTILS_NS::Component>());
                    }
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Capsule")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Capsule"_atom);
                    if (auto&& pRigidbody = pGameObject->AddComponent<SR_PHYSICS_NS::Types::Rigidbody3D>()) {
                        pRigidbody->SetMass(1.0f);
                        pRigidbody->AddCollider(SR_PHYSICS_NS::ShapeType::Capsule3D);
                    }

                    auto&& meshes = SR_GTYPES_NS::Mesh::Load("Engine/Models/capsule.obj");
                    for (auto&& pMesh : meshes) {
                        pGameObject->AddComponent(pMesh.StaticCast<SR_UTILS_NS::Component>());
                    }
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Cylinder")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Cylinder"_atom);
                    if (auto&& pRigidbody = pGameObject->AddComponent<SR_PHYSICS_NS::Types::Rigidbody3D>()) {
                        pRigidbody->SetMass(1.0f);
                        pRigidbody->AddCollider(SR_PHYSICS_NS::ShapeType::Cylinder3D);
                    }

                    auto&& meshes = SR_GTYPES_NS::Mesh::Load("Engine/Models/cylinder.obj");
                    for (auto&& pMesh : meshes) {
                        pGameObject->AddComponent(pMesh.StaticCast<SR_UTILS_NS::Component>());
                    }
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Plane")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Plane"_atom);
                    if (auto&& pRigidbody = pGameObject->AddComponent<SR_PHYSICS_NS::Types::Rigidbody3D>()) {
                        pRigidbody->SetMass(1.0f);
                        pRigidbody->AddCollider(SR_PHYSICS_NS::ShapeType::Plane3D);
                    }

                    auto&& meshes = SR_GTYPES_NS::Mesh::Load("Engine/Models/plane.obj");
                    for (auto&& pMesh : meshes) {
                        pGameObject->AddComponent(pMesh.StaticCast<SR_UTILS_NS::Component>());
                    }
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Statue")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Statue"_atom);
                    pGameObject->GetTransform()->SetScale(10.f, 10.f, 10.f);
                    if (auto&& pRigidbody = pGameObject->AddComponent<SR_PHYSICS_NS::Types::Rigidbody3D>()) {
                        pRigidbody->SetMass(1.0f);
                        auto&& pCollider = pRigidbody->AddCollider(SR_PHYSICS_NS::ShapeType::Convex3D);
                        pCollider->SetRawMesh("Engine/Models/statue.obj");
                    }

                    auto&& meshes = SR_GTYPES_NS::Mesh::Load("Engine/Models/statue.obj");
                    for (auto&& pMesh : meshes) {
                        pGameObject->AddComponent(pMesh.StaticCast<SR_UTILS_NS::Component>());
                    }
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Monkey")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Monkey"_atom);
                    if (auto&& pRigidbody = pGameObject->AddComponent<SR_PHYSICS_NS::Types::Rigidbody3D>()) {
                        pRigidbody->SetMass(1.0f);
                        auto&& pCollider = pRigidbody->AddCollider(SR_PHYSICS_NS::ShapeType::Convex3D);
                        pCollider->SetRawMesh("Engine/Models/monkey.obj");
                    }

                    auto&& meshes = SR_GTYPES_NS::Mesh::Load("Engine/Models/monkey.obj");
                    for (auto&& pMesh : meshes) {
                        pGameObject->AddComponent(pMesh.StaticCast<SR_UTILS_NS::Component>());
                    }
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::EndMenu();
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::BeginMenu("Render")) {
            if (SR_IMMEDIATE_GUI_NS::MenuItem("Camera")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Camera"_atom);
                    auto&& pCamera = pGameObject->AddComponent<SR_GTYPES_NS::Camera>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Skybox")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Skybox"_atom);
                    auto&& pSkybox = pGameObject->AddComponent<SR_GTYPES_NS::SkyboxComponent>();
                    pSkybox->SetParams("Engine/Skyboxes/Sun.png", "Engine/Shaders/skybox.srsl", false);
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Skybox procedural")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Skybox"_atom);
                    auto&& pSkybox = pGameObject->AddComponent<SR_GTYPES_NS::SkyboxComponent>();
                    pSkybox->SetParams(SR_UTILS_NS::Path(), "Engine/Shaders/skybox-procedural.srsl", false);
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Volumetric Clouds")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Volumetric Clouds"_atom);
                    pGameObject->AddComponent<SR_GRAPH_NS::VolumetricClouds>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Volumetric Fog")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Volumetric Fog"_atom);
                    pGameObject->AddComponent<SR_GRAPH_NS::VolumetricFog>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Render Target")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Render Target"_atom);
                    auto&& pRenderTarget = pGameObject->AddComponent<SR_GTYPES_NS::RenderTarget>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Particle Emitter")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Particle Emitter"_atom);
                    pGameObject->SetLayer("Particles");
                    auto&& pEmitter = pGameObject->AddComponent<SR_GRAPH_NS::ParticleEmitter>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_IMMEDIATE_GUI_NS::EndMenu();
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::BeginMenu("Lights")) {
            if (SR_IMMEDIATE_GUI_NS::MenuItem("Directional light")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Directional light"_atom);
                    auto&& pSun = pGameObject->AddComponent<SR_GRAPH_NS::DirectionalLight>();
                    pSun->SetDiskIntensity(25.f);
                    pGameObject->GetTransform()->SetRotation(60, -45, 0);

                    /// луна - второй directional light внутри солнца, повернутый в противоположную сторону
                    auto&& pMoon = pScene->InstanceGameObject("Moon"_atom);
                    pGameObject->AddChild(pMoon.StaticCast<SR_UTILS_NS::SceneObject>());
                    pMoon->GetTransform()->SetRotation(180, 15, 0);
                    if (auto&& pMoonLight = pMoon->AddComponent<SR_GRAPH_NS::DirectionalLight>()) {
                        pMoonLight->SetTemperature(8000.f);
                        pMoonLight->SetIntensity(0.08f);
                        pMoonLight->SetSkyColors(
                            SR_MATH_NS::FColor(0.002f, 0.003f, 0.008f),
                            SR_MATH_NS::FColor(0.02f, 0.035f, 0.08f),
                            SR_MATH_NS::FColor(0.4f, 0.4f, 0.45f)
                        );
                        pMoonLight->SetCelestialBody(SR_GRAPH_NS::CelestialBodyShading::ReflectLight, 2.f, 1.f, SR_MATH_NS::FColor(0.9f, 0.92f, 1.f));
                    }

                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }
            if (SR_IMMEDIATE_GUI_NS::MenuItem("Point light")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Point light"_atom);
                    auto&& pLight = pGameObject->AddComponent<SR_GRAPH_NS::PointLight>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }
            if (SR_IMMEDIATE_GUI_NS::MenuItem("Spot light")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Spot light"_atom);
                    auto&& pLight = pGameObject->AddComponent<SR_GRAPH_NS::SpotLight>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }
            if (SR_IMMEDIATE_GUI_NS::MenuItem("Area light")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Area light"_atom);
                    auto&& pLight = pGameObject->AddComponent<SR_GRAPH_NS::AreaLight>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }
            if (SR_IMMEDIATE_GUI_NS::MenuItem("Probe light")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Probe light"_atom);
                    auto&& pLight = pGameObject->AddComponent<SR_GRAPH_NS::ProbeLight>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }
            SR_IMMEDIATE_GUI_NS::EndMenu();
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::BeginMenu("World")) {
            if (SR_IMMEDIATE_GUI_NS::MenuItem("Terrain")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pSO = pScene->InstanceFromFile("Engine/Prefabs/Terrain.prefab").StaticCast<SR_UTILS_NS::SceneObject>();
                    InstantiateSO(pSO);
                }
            }
            SR_IMMEDIATE_GUI_NS::EndMenu();
        }
    }

    void EditorGUI::DrawMenuBar() {
        SR_TRACY_ZONE;

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::WindowPadding, SR_MATH_NS::FVector2(8, 8));

        DrawFileMenu();

        if (SR_IMMEDIATE_GUI_NS::BeginMenu("Editor")) {
            DrawEditorInstanceMenu();
            SR_IMMEDIATE_GUI_NS::EndMenu();
        }

        DrawToolsMenu();
        DrawWindowPage();
        DrawHelpMenu();

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PushItemWidth(200);

        const float_t framerate = SR_IMMEDIATE_GUI_NS::GetFramerate();
        SR_IMMEDIATE_GUI_NS::LabelText("##FPSLable", "|   FPS: %.2f (%.2gms)", framerate, framerate > 0.f ? 1000.0f / framerate : 0.0f);

        SR_IMMEDIATE_GUI_NS::PopItemWidth();

        //auto&& pBuilder = m_engine->GetSceneBuilder();
        //if (pBuilder) {
        //    auto&& now = SR_HTYPES_NS::Time::Instance().Now();
        //    auto&& time = now - pBuilder->GetLastBuildTime();

        //    using ms = std::chrono::duration<double_t, std::milli>;

        //    const float_t timeLeft = (float_t)std::chrono::duration_cast<ms>(time).count() / (float_t)SR_CLOCKS_PER_SEC;

        //    SR_IMMEDIATE_GUI_NS::Text("|   Last scene build: %.2f sec", timeLeft);
        //}
    }

    void EditorGUI::DrawFileMenu() {
        SR_TRACY_ZONE;

        if (!SR_IMMEDIATE_GUI_NS::BeginMenu("File")) {
            return;
        }

        const bool hasScene = m_engine->GetScene().Valid();

        if (SR_IMMEDIATE_GUI_NS::MenuItem("New Scene")) {
            m_engine->AddSceneToQueue(SR_WORLD_NS::Scene::NewScene(SR_WORLD_NS::SceneLogicType::Asset));
            CacheScenePath(m_engine->GetScene()->GetPath());
        }

        if (SR_IMMEDIATE_GUI_NS::MenuItem("New Prefab")) {
            if (auto&& pScene = m_engine->GetScene()) {
                //TODO: проверку на то, что нынешний префаб не сохранён, чтобы не спамить ими
                pScene->SaveScene();
                CacheScenePath(m_engine->GetScene()->GetPath());
            }

            m_engine->AddSceneToQueue(SR_WORLD_NS::Scene::NewScene(GetNewPrefabPath(), SR_WORLD_NS::SceneLogicType::Prefab));
        }

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Open Scene...")) {
            auto&& scenesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();

            if (auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(scenesPath.ToString(), { { "Scene", "scene,prefab" } }); !path.IsEmpty()) {
                SR_UTILS_NS::VFS::Instance().UnResolvePath(path);
                if (auto&& pScene = SR_WORLD_NS::Scene::LoadScene(path)) {
                    m_engine->AddSceneToQueue(pScene);
                    CacheScenePath(path);
                }
            }
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Save", nullptr, false, hasScene)) {
            if (auto&& pScene = m_engine->GetScene()) {
                pScene->SaveScene();
            }
        }

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Save As...", nullptr, false, hasScene)) {
            if (auto&& pScene = m_engine->GetScene()) {
                const auto scenesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                if (auto&& path = SR_UTILS_NS::FileDialog::Instance().SaveDialog(scenesPath.ToString(), { { "Scene", "scene,prefab" } }); !path.IsEmpty()) {
                    SR_UTILS_NS::VFS::Instance().UnResolvePath(path);
                    if (pScene->SaveSceneAt(path)) {
                        SR_SYSTEM_LOG("EditorGUI::DrawFileMenu() : scene is saved as \"{}\"", path);

                        if (auto&& pSavedScene = SR_WORLD_NS::Scene::LoadScene(path)) {
                            m_engine->AddSceneToQueue(pSavedScene);
                            CacheScenePath(path);
                        }
                    }
                    else {
                        SR_ERROR("EditorGUI::DrawFileMenu() : failed to save scene! \n\tPath: \"" + path.ToString() + "\"");
                    }
                }
            }
            else {
                SR_WARN("EditorGUI::DrawFileMenu() : scene is not valid!");
            }
        }

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Close Scene", nullptr, false, hasScene)) {
            if (auto&& pScene = m_engine->GetScene()) {
                pScene->SaveScene();
            }
            m_engine->AddSceneToQueue(SR_WORLD_NS::Scene::CreateEmptyScene());
            CacheScenePath("NONE");
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::BeginMenu("Project")) {
            const bool hasProjectSettings = SR_UTILS_NS::VFS::Instance().IsFileExists(".srproject");
            const bool isProjectOpened = SR_UTILS_NS::CLIManager::Instance().GetProjectPath().has_value();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("New Project...")) {
                OpenWidget<CreateNewProject>();
            }

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Project Settings", nullptr, false, hasProjectSettings)) {
                OpenWidget<AssetInspector>()->Inspect(".srproject");
            }

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Close Project", nullptr, false, isProjectOpened)) {
                SR_UTILS_NS::CLIManager::Instance().SetProjectPath(std::nullopt);
                GetEngine()->Reload();
            }

            SR_IMMEDIATE_GUI_NS::EndMenu();
        }

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Build Game...")) {
            OpenWidget<GameBuildExporter>();
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Exit")) {
            m_engine->StopEngine();
        }

        SR_IMMEDIATE_GUI_NS::EndMenu();
    }

    void EditorGUI::DrawToolsMenu() {
        SR_TRACY_ZONE;

        if (!SR_IMMEDIATE_GUI_NS::BeginMenu("Tools")) {
            return;
        }

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Assets Store")) {
            OpenWidget<AssetsStore>();
        }

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Engine Settings")) {
            OpenWidget<EngineSettings>();
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Reload Scripts")) {
            SR_SCRIPTING_NS::ScriptSystem::Instance().SetReloadRequest();
        }

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Clear Shaders Cache")) {
            SR_SRSL_NS::SRSLShader::ClearShadersCache();
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Reload Engine")) {
            m_engine->Reload();
        }

        SR_IMMEDIATE_GUI_NS::EndMenu();
    }

    void EditorGUI::DrawWidgetMenuItems(std::span<const SR_UTILS_NS::StringAtom> names) {
        for (auto&& name : names) {
            auto&& pWidget = GetWidget(name);
            if (!pWidget) {
                continue;
            }

            /// пункт работает как переключатель: галочка показывает, открыто ли окно
            const bool isOpen = pWidget->IsOpen();
            if (SR_IMMEDIATE_GUI_NS::MenuItem(pWidget->GetName().c_str(), nullptr, isOpen)) {
                if (isOpen) {
                    pWidget->Close();
                }
                else {
                    pWidget->Open();
                }
            }
        }
    }

    void EditorGUI::DrawWindowPage() {
        SR_TRACY_ZONE;

        if (!SR_IMMEDIATE_GUI_NS::BeginMenu("Window")) {
            return;
        }

        DrawWidgetMenuItems(g_mainWindowWidgets);

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::BeginMenu("Editors")) {
            DrawWidgetMenuItems(g_editorWindowWidgets);
            SR_IMMEDIATE_GUI_NS::EndMenu();
        }

        if (SR_IMMEDIATE_GUI_NS::BeginMenu("Inspectors")) {
            DrawWidgetMenuItems(g_inspectorWindowWidgets);
            SR_IMMEDIATE_GUI_NS::EndMenu();
        }

        if (SR_IMMEDIATE_GUI_NS::BeginMenu("Debug")) {
            DrawWidgetMenuItems(g_debugWindowWidgets);

            SR_IMMEDIATE_GUI_NS::Separator();

            if (SR_IMMEDIATE_GUI_NS::MenuItem("ImGui Metrics", nullptr, m_showMetricsWindow)) {
                m_showMetricsWindow = !m_showMetricsWindow;
            }

            SR_IMMEDIATE_GUI_NS::EndMenu();
        }

        /// виджеты, которые еще не распределены по группам
        if (!m_windowPageWidgets.empty() && SR_IMMEDIATE_GUI_NS::BeginMenu("Other")) {
            for (auto&& widget : m_windowPageWidgets) {
                DrawWidgetMenuItems(std::span<const SR_UTILS_NS::StringAtom>(&widget.first, 1));
            }
            SR_IMMEDIATE_GUI_NS::EndMenu();
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::BeginMenu("Layout")) {
            if (SR_IMMEDIATE_GUI_NS::MenuItem("Reset to Default")) {
                ResetToDefault();
            }

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Close All Windows")) {
                CloseAllWidgets();
            }

            SR_IMMEDIATE_GUI_NS::EndMenu();
        }

        SR_IMMEDIATE_GUI_NS::EndMenu();
    }

    void EditorGUI::DrawHelpMenu() {
        SR_TRACY_ZONE;

        if (!SR_IMMEDIATE_GUI_NS::BeginMenu("Help")) {
            return;
        }

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Welcome")) {
            OpenWidget<Welcome>();
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Documentation")) {
            SR_PLATFORM_NS::OpenAssociated("https://docs.sparcles.dev/");
        }

        if (SR_IMMEDIATE_GUI_NS::MenuItem("GitHub")) {
            SR_PLATFORM_NS::OpenAssociated("https://github.com/SpaRcle-Studio/SREngine");
        }

        if (SR_IMMEDIATE_GUI_NS::MenuItem("Discord")) {
            SR_PLATFORM_NS::OpenAssociated("https://discord.gg/NHuhNwFtYQ");
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::MenuItem("About SpaRcle Engine")) {
            OpenWidget<About>();
        }

        SR_IMMEDIATE_GUI_NS::EndMenu();
    }

    void EditorGUI::InstantiateSO(const SR_UTILS_NS::SceneObject::Ptr& pSO) {
        if (!pSO) {
            return;
        }

        SR_UTILS_NS::SceneObject::Ptr pInstantiateTarget;
        if (auto&& pHierarchy = GetWidget<Hierarchy>(); pHierarchy) {
            if (auto&& selected = pHierarchy->GetSelected(); selected.size() == 1 && *selected.begin()) {
                pInstantiateTarget = *selected.begin();
            }
        }

        if (auto&& pScene = GetEngine()->GetScene(); pScene && !pInstantiateTarget) {
            if (auto&& pLogic = pScene->GetLogicBase().DynamicCast<SR_WORLD_NS::ScenePrefabLogic>()) {
                if (auto&& pPrefabRoot = pLogic->GetPrefabRoot()) {
                    pInstantiateTarget = pPrefabRoot;
                }
                else {
                    SRHalt("EditorGUI::InstantiateSO() : prefab root is nullptr!");
                    pSO->Destroy();
                    return;
                }
            }
        }

        if (pInstantiateTarget) {
            auto&& pTargetGO = pInstantiateTarget->DynamicCast<SR_UTILS_NS::GameObject>();
            auto&& pGO = pSO->DynamicCast<SR_UTILS_NS::GameObject>();

            if (pTargetGO && pGO && pTargetGO->GetTransform()->GetMeasurement() == SR_UTILS_NS::Measurement::Space2D && pGO->GetTransform()->GetMeasurement() == SR_UTILS_NS::Measurement::Space3D) {
                pGO->SetTransform(SRNew<SR_UTILS_NS::TransformRect>());
            }

            pInstantiateTarget->AddChild(pSO);
        }

        auto&& pCmd = new SR_CORE_NS::Commands::SceneObjectInstance(GetEngine(), pSO);
        GetEngine()->GetCmdManager()->Store(pCmd);
    }
}
