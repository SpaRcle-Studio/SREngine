//
// Created by Nikita on 19.07.2021.
//

#include <Engine/Engine.h>

#include <Engine/Settings/EditorSettings.h>

#include <Engine/GUI/EditorGUI.h>
#include <Engine/GUI/SoundDebug.h>
#include <Engine/GUI/AnimatorEditor.h>
#include <Engine/GUI/Inspector.h>
#include <Engine/GUI/VisualScriptEditor.h>
#include <Engine/GUI/WorldEdit.h>
#include <Engine/GUI/EngineSettings.h>
#include <Engine/GUI/PhysicsMaterialEditor.h>
#include <Engine/GUI/EngineStatistics.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/AssetInspector.h>
#include <Engine/GUI/TextureInspector.h>
#include <Engine/GUI/SceneViewer.h>
#include <Engine/GUI/RenderTechniqueEditor.h>
#include <Engine/GUI/FileBrowser.h>
#include <Engine/GUI/About.h>
#include <Engine/GUI/CreateNewProject.h>
#include <Engine/GUI/SceneTools.h>
#include <Engine/EngineCommands.h>
#include <Engine/UI/UIButton.h>

#include <Graphics/Types/Texture.h>
#include <Graphics/Types/RenderTarget.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/Types/Mesh.h>
#include <Graphics/Types/SkyboxComponent.h>
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
#include <Graphics/Types/Geometry/Sprite.h>

#include <Physics/3D/Rigidbody3D.h>

#include <Scripting/Cpp/ScriptSystem.h>

#include <Utils/Common/Features.h>
#include <Utils/ECS/Prefab.h>
#include <Utils/ECS/TransformRect.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Platform/MessageBox.h>
#include <Utils/FileSystem/FileDialog.h>
#include <Utils/Profile/TracyContext.h>
#include <Utils/World/SceneUpdater.h>
#include <Utils/World/ScenePrefabLogic.h>
#include <Utils/Common/StringAtomLiterals.h>
#include <Utils/Common/CLIManager.h>
#include <Utils/Common/StoreUtils.h>

#include <Enum/EditorIcon.hpp>

namespace SR_CORE_GUI_NS {
    SR_UTILS_NS::Path SR_SAMPLES_PATH = "Samples";

    static SR_UTILS_NS::Path GetNewScenePath() {
        auto&& scenePath = SR_UTILS_NS::Path(SR_WORLD_NS::Scene::NewScenePath).ConcatExt("scene");

        uint64_t index = 0;
        while (SR_WORLD_NS::Scene::IsExists(scenePath)) {
            scenePath = SR_FORMAT("{}-{}.scene", SR_WORLD_NS::Scene::NewScenePath, index);
            ++index;
        }

        return scenePath;
    }

    static SR_UTILS_NS::Path GetNewPrefabPath() {
        auto&& scenePath = SR_UTILS_NS::Path(SR_WORLD_NS::Scene::NewPrefabPath).ConcatExt("prefab");

        uint64_t index = 0;
        while (SR_WORLD_NS::Scene::IsExists(scenePath)) {
            scenePath = SR_FORMAT("{}-{}.prefab", SR_WORLD_NS::Scene::NewPrefabPath, index);
            ++index;
        }

        return scenePath;
    }

    EditorGUI::EditorGUI(const EnginePtr& pEngine)
        : Super()
    {
        m_pSettings = SR_UTILS_NS::Asset::Load<EditorSettings>("Editor/Configs/EditorSettings.sras");
        if (m_pSettings) {
            m_pSettings->AddUsePoint();
        }

        m_cachedScenePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("User/PreviousScenePath.cache");

        m_engine = pEngine;

        AddWidget(new AssetInspector());
        AddWidget(new TextureInspector());
        AddWidget(new FileBrowser());
        AddWidget(new Hierarchy());
        AddWidget(new VisualScriptEditor());
        AddWidget(new Inspector(TryGetWidget<Hierarchy>()));
        AddWidget(new WorldEdit());
        AddWidget(new EngineSettings());
        AddWidget(new AnimatorEditor());
        AddWidget(new EngineStatistics());
		AddWidget(new About());
		AddWidget(new SoundDebug());
        AddWidget(new RenderTechniqueEditor());
        AddWidget(new CreateNewProject());
        AddWidget(new SceneViewer(m_engine, GetWidget<Hierarchy>()));

        for (auto& [id, widget] : m_widgets) {
            Register(widget);
        }

        if (auto&& pWidget = TryGetWidget<FileBrowser>()) {
            pWidget->SetFolder(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
        }
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

        if (m_pSettings) {
            m_pSettings->RemoveUsePoint();
            m_pSettings = nullptr;
        }
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
            //ImGui::ShowDemoWindow(&m_imGuiDemo);
        }

        if (!m_installSamplesAsked && m_samplesShowDelay <= 0.f) {
            m_installSamplesAsked = SR_UTILS_NS::StoreUtils::User::GetBool("InstallSamplesAsked", false);
            m_installSamplesAsked |= SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(SR_SAMPLES_PATH).IsDir();
            m_installSamplesAsked |= SR_UTILS_NS::CLIManager::Instance().IsHeadlessMode() || SR_UTILS_NS::CLIManager::Instance().IsFlagPresent(SR_UTILS_NS::CLIFlags::UnitTests);

            SR_UTILS_NS::StoreUtils::User::SetBool("InstallSamplesAsked", true);

            if (!m_installSamplesAsked) {
                SR_LOG("EditorGUI::Draw() : asking user to install samples...");
                const auto&& result = SR_PLATFORM_NS::ShowMessageBox(
                    "Samples are not installed",
                    "Do you want to install samples? It will download ~400mb of data. You can also install them later from the settings.",
                    SR_PLATFORM_NS::MessageBoxType::YesNo,
                    SR_PLATFORM_NS::MessageBoxIconType::Question,
                    SR_PLATFORM_NS::MessageBoxDefaultButtonType::YesOk
                );
                if (result == SR_PLATFORM_NS::MessageBoxResultType::YesOk) {
                    SR_LOG("EditorGUI::Draw() : user accepted to install samples! Installing...");
                    InstallOrUpdateSamples();
                    auto&& scenePath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(SR_SAMPLES_PATH).Concat("Female/demo.scene");
                    if (scenePath.IsFile()) {
                        if (auto&& pScene = m_engine->GetScene()) {
                            pScene->SaveScene();
                        }
                        if (auto&& pScene = SR_WORLD_NS::Scene::LoadScene(scenePath)) {
                            m_engine->AddSceneToQueue(pScene);
                        }
                    }
                }
                else {
                    SR_LOG("EditorGUI::Draw() : user declined to install samples.");
                }
                m_installSamplesAsked = true;
                SR_UTILS_NS::StoreUtils::Storage::Instance().Save();
            }
        }
        m_samplesShowDelay -= SR_HTYPES_NS::Time::Instance().DeltaTime();

        WidgetManager::Draw();
    }

    void EditorGUI::DrawDockingSpace() {
        SR_TRACY_ZONE;
        m_dragWindow = false;

        SR_GRAPH_GUI_NS::Immediate::BeginDocking();

        if (SR_GRAPH_GUI_NS::Immediate::BeginMainMenuBar()) {
            if (SR_GRAPH_GUI_NS::Immediate::IsMouseDragging(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left) && SR_GRAPH_GUI_NS::Immediate::IsWindowHovered()) {
                m_click = Click::Drag;
            }
            else if (SR_GRAPH_GUI_NS::Immediate::IsMouseReleased(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left)) {
                m_click = Click::None;
            }

            m_dragWindow = m_click == Click::Drag;

            SR_GRAPH_GUI_NS::Immediate::Text(" | ");
            SR_GRAPH_GUI_NS::Immediate::Text("%s", "SpaRcle Engine");
            SR_GRAPH_GUI_NS::Immediate::Text(" | ");

            DrawMenuBar();

            SR_GRAPH_GUI_NS::Immediate::SetCursorPosX(SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x - 20);
            SR_GRAPH_GUI_NS::Immediate::SetCursorPosY(0);

            auto&& pWindow = m_engine->GetMainWindow()->GetBaseWindow();

            if (SR_GRAPH_GUI_NS::Immediate::SmallButton("×")) {
                SR_LOG("EditorGUI::DrawDockingSpace() : close button was clicked!");
                m_engine->StopEngine();
            }

            SR_GRAPH_GUI_NS::Immediate::SetCursorPosX(SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x - 45);
            SR_GRAPH_GUI_NS::Immediate::SetCursorPosY(0);
            if (pWindow->GetState() == Graphics::WindowState::Default && SR_GRAPH_GUI_NS::Immediate::SmallButton("[ ]")) {
                pWindow->Maximize();
            }

            if (pWindow->GetState() == Graphics::WindowState::Maximized && SR_GRAPH_GUI_NS::Immediate::SmallButton("[=]")) {
                pWindow->Restore();
            }
            SR_GRAPH_GUI_NS::Immediate::SetCursorPosX(SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x - 70);
            SR_GRAPH_GUI_NS::Immediate::SetCursorPosY(0);
            if (SR_GRAPH_GUI_NS::Immediate::SmallButton("_")) {
                pWindow->Collapse();
            }

            SR_GRAPH_GUI_NS::Immediate::EndMenuBar();
            SR_GRAPH_GUI_NS::Immediate::FocusTopMostWindowUnderOne();
            SR_GRAPH_GUI_NS::Immediate::End();
        }

        SR_GRAPH_GUI_NS::Immediate::EndDocking();
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
            if (auto&& pViewer = TryGetWidget<SceneViewer>()) {
                pViewer->Enable(value);
            }
            m_enabled = value;
        }
    }

    void EditorGUI::FixedUpdate() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        if (auto&& pViewer = TryGetWidget<SceneViewer>()) {
            pViewer->FixedUpdate();
        }
    }

    void EditorGUI::Update(float_t dt) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        if (Enabled()) {
            if (auto&& pWidget = TryGetWidget<Hierarchy>()) {
                pWidget->Update(dt);
            }
            if (auto&& pWidget = TryGetWidget<Inspector>()) {
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

    void EditorGUI::CloseAllWidgets() {
        for (auto& [id, widget] : m_widgets) {
            widget->Close();
        }
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
        if (!m_cachedScenePath.Exists()) {
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
            SR_WARN("EditorGUI::LoadSceneFromCachedPath() : cached path is not usable! \n\tPath: {}\n\tUsing default scene.", scenePath);
            scenePath = SR_UTILS_NS::Path(SR_WORLD_NS::Scene::NewScenePath).ConcatExt("scene");
        }

        if (!SR_WORLD_NS::Scene::IsExists(scenePath)) {
            SR_ERROR("EditorGUI::LoadSceneFromCachedPath() : default scene does not exist! \n\tCreating new one by path: {}", scenePath);
            m_engine->AddSceneToQueue(SR_WORLD_NS::Scene::NewScene(scenePath, SR_WORLD_NS::SceneLogicType::Asset));
            return true;
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

        SR_GRAPH_GUI_NS::Immediate::LoadIniSettingsFromDisk();
    }

    void EditorGUI::DrawEditorInstanceMenu() {
        SR_TRACY_ZONE;

        if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Instance from file")) {
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

        SR_GRAPH_GUI_NS::Immediate::Separator();

        if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("UI")) {
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("UI Element")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pSO = pScene->InstanceGameObject("UI Element"_atom).StaticCast<SR_UTILS_NS::SceneObject>();
                    InstantiateSO(pSO);
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Button")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pSO = pScene->InstanceFromFile("Engine/Prefabs/Button.prefab").StaticCast<SR_UTILS_NS::SceneObject>();
                    InstantiateSO(pSO);
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Text")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pSO = pScene->InstanceGameObject("Text"_atom).StaticCast<SR_UTILS_NS::SceneObject>();
                    if (auto&& pText = pSO->AddComponent<SR_GTYPES_NS::Text>()) {
                        pText->SetText("Text");
                    }
                    InstantiateSO(pSO);
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Sprite")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pSO = pScene->InstanceGameObject("Sprite"_atom).StaticCast<SR_UTILS_NS::SceneObject>();
                    auto&& pSprite = pSO->AddComponent<SR_GTYPES_NS::Sprite>();
                    InstantiateSO(pSO);
                }
            }

            SR_GRAPH_GUI_NS::Immediate::EndMenu();
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("Instantiate")) {
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Empty")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    InstantiateSO(pScene->InstanceGameObject("New GameObject"_atom).StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Cube")) {
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

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Sphere")) {
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

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Capsule")) {
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

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Cylinder")) {
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

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Plane")) {
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

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Statue")) {
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

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Monkey")) {
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

            SR_GRAPH_GUI_NS::Immediate::EndMenu();
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("Render")) {
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Camera")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Camera"_atom);
                    auto&& pCamera = pGameObject->AddComponent<SR_GTYPES_NS::Camera>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Skybox")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Skybox"_atom);
                    auto&& pSkybox = pGameObject->AddComponent<SR_GTYPES_NS::SkyboxComponent>();
                    pSkybox->SetParams("Engine/Skyboxes/Sun.png", "Engine/Shaders/skybox.srsl", false);
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Render Target")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Render Target"_atom);
                    auto&& pRenderTarget = pGameObject->AddComponent<SR_GTYPES_NS::RenderTarget>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Particle Emitter")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Particle Emitter"_atom);
                    pGameObject->SetLayer("Particles");
                    auto&& pEmitter = pGameObject->AddComponent<SR_GRAPH_NS::ParticleEmitter>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            SR_GRAPH_GUI_NS::Immediate::EndMenu();
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("Lights")) {
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Directional light")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Directional light"_atom);
                    pGameObject->AddComponent<SR_GRAPH_NS::DirectionalLight>();
                    pGameObject->GetTransform()->SetRotation(60, -45, 0);
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Point light")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Point light"_atom);
                    auto&& pLight = pGameObject->AddComponent<SR_GRAPH_NS::PointLight>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Spot light")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Spot light"_atom);
                    auto&& pLight = pGameObject->AddComponent<SR_GRAPH_NS::SpotLight>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Area light")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Area light"_atom);
                    auto&& pLight = pGameObject->AddComponent<SR_GRAPH_NS::AreaLight>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Probe light")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    auto&& pGameObject = pScene->InstanceGameObject("Probe light"_atom);
                    auto&& pLight = pGameObject->AddComponent<SR_GRAPH_NS::ProbeLight>();
                    InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }
            SR_GRAPH_GUI_NS::Immediate::EndMenu();
        }
    }

    void EditorGUI::DrawMenuBar() {
        SR_TRACY_ZONE;

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::WindowPadding, SR_MATH_NS::FVector2(8, 8));

        if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("File")) {
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("New project")) {
                OpenWidget<CreateNewProject>();
            }

            if (SR_UTILS_NS::CLIManager::Instance().GetProjectPath().has_value()) {
                SR_GRAPH_GUI_NS::Immediate::Separator();
                if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Close project")) {
                    SR_UTILS_NS::CLIManager::Instance().SetProjectPath(std::nullopt);
                    GetEngine()->Reload();
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("New scene")) {
                m_engine->AddSceneToQueue(SR_WORLD_NS::Scene::NewScene(GetNewScenePath(), SR_WORLD_NS::SceneLogicType::Asset));
                CacheScenePath(m_engine->GetScene()->GetPath());
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("New prefab")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    //TODO: проверку на то, что нынешний префаб не сохранён, чтобы не спамить ими
                    pScene->SaveScene();
                    CacheScenePath(m_engine->GetScene()->GetPath());
                }

                m_engine->AddSceneToQueue(SR_WORLD_NS::Scene::NewScene(GetNewPrefabPath(), SR_WORLD_NS::SceneLogicType::Prefab));
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Load")) {
                auto&& scenesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();

                if (auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(scenesPath.ToString(), { { "Scene", "scene,prefab" } }); !path.IsEmpty()) {
                    path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetCachePath());
                    path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

                    if (auto&& pScene = SR_WORLD_NS::Scene::LoadScene(path)) {
                        m_engine->AddSceneToQueue(pScene);
                        CacheScenePath(path);
                    }
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Save")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    pScene->SaveScene();
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Save at")) {
                if (auto&& pScene = m_engine->GetScene())
                {
                    const auto scenesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();

                    if (auto&& path = SR_UTILS_NS::FileDialog::Instance().SaveDialog(scenesPath.ToString(), { { "Scene", "scene,prefab" } }); !path.IsEmpty())
                    {
                        path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetCachePath());
                        path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

                        if (pScene->SaveSceneAt(path)) {
                            SR_SYSTEM_LOG("GUISystem::BeginMenuBar() : scene is saved as \"" + path.ToString() + "\"");

                            if (auto&& pSavedScene = SR_WORLD_NS::Scene::LoadScene(path)) {
                                m_engine->AddSceneToQueue(pSavedScene);
                                CacheScenePath(path);
                            }
                        }
                        else {
                            SR_ERROR("GUISystem::BeginMenuBar() : failed to save scene! \n\tPath: \"" + path.ToString() + "\"");
                        }
                    }
                }
                else {
                    SR_WARN("GUISystem::BeginMenuBar() : scene is not valid!");
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Close scene")) {
                if (auto&& pScene = m_engine->GetScene()) {
                    pScene->SaveScene();
                }
                m_engine->AddSceneToQueue(SR_WORLD_NS::Scene::CreateEmptyScene());
                CacheScenePath("NONE");
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Clear shaders cache")) {
                SR_SRSL_NS::SRSLShader::ClearShadersCache();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Reload scripts")) {
                SR_SCRIPTING_NS::ScriptSystem::Instance().SetReloadRequest();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Install/Update samples")) {
                InstallOrUpdateSamples();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Reload")) {
                m_engine->Reload();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Exit")) {
                m_engine->StopEngine();
            }

            SR_GRAPH_GUI_NS::Immediate::EndMenu();
        }

        if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("Editor")) {
            DrawEditorInstanceMenu();
            SR_GRAPH_GUI_NS::Immediate::EndMenu();
        }

        DrawWindowPage();

        if (SR_GRAPH_GUI_NS::Immediate::MenuItem("About")) {
            OpenWidget<About>();
        }

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(115);

        const float_t framerate = SR_GRAPH_GUI_NS::Immediate::GetFramerate();
        SR_GRAPH_GUI_NS::Immediate::LabelText("##FPSLable", "|   FPS: %.2f (%.2gms)", framerate, framerate > 0.f ? 1000.0f / framerate : 0.0f);

        SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

        auto&& pBuilder = m_engine->GetSceneBuilder();
        if (pBuilder) {
            auto&& now = SR_HTYPES_NS::Time::Instance().Now();
            auto&& time = now - pBuilder->GetLastBuildTime();

            using ms = std::chrono::duration<double_t, std::milli>;

            const float_t timeLeft = (float_t)std::chrono::duration_cast<ms>(time).count() / (float_t)SR_CLOCKS_PER_SEC;

            SR_GRAPH_GUI_NS::Immediate::Text("|   Last scene build: %.2f sec", timeLeft);
        }
    }

    void EditorGUI::DrawWindowPage() {
        SR_TRACY_ZONE;

        if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("Window")) {
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Assets")) {
                OpenWidget<FileBrowser>();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Hierarchy")) {
                OpenWidget<Hierarchy>();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Inspector")) {
                OpenWidget<Inspector>();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Scene")) {
                OpenWidget<SceneViewer>();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Sound debug")) {
                OpenWidget<SoundDebug>();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Render Technique")) {
                OpenWidget<RenderTechniqueEditor>();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Animator")) {
                OpenWidget<AnimatorEditor>();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("ImGui Demo Window")) {
                m_imGuiDemo = true;
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Animator")) {
               OpenWidget<AnimatorEditor>();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("World edit")) {
               OpenWidget<WorldEdit>();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Settings")) {
                OpenWidget<EngineSettings>();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Statistics")) {
                OpenWidget<EngineStatistics>();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Reset to default")) {
                ResetToDefault();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Close all")) {
                CloseAllWidgets();
            }

            SR_GRAPH_GUI_NS::Immediate::EndMenu();
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

    void EditorGUI::InstallOrUpdateSamples() {
        auto&& fullPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(SR_SAMPLES_PATH);

        const auto repoUrl = "https://github.com/SpaRcle-Studio/SREngineSampleResources";

        if (fullPath.IsDir()) {
            /// Если нету гита, то сам виноват.
        #ifdef SR_WIN32
            std::string command = "{}: && cd {} && git pull -r --autostash"_format(fullPath[0], fullPath);
        #else
            std::string command = "cd {} && git pull -r --autostash"_format(fullPath);
        #endif
            SR_SYSTEM_LOG("EditorGUI::InstallOrUpdateSamples() : pulling repository...\n\tCommand: " + command);
            system(command.c_str());
        }
        else {
        #ifdef SR_WIN32
            auto&& gitPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Utilities/git2.exe");
        #else
            auto&& gitPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Utilities/git2");
        #endif
            std::string command = "{} clone {} {} --depth 1"_format(gitPath, repoUrl, fullPath);
            SR_SYSTEM_LOG("EditorGUI::InstallOrUpdateSamples() : cloning repository...\n\tCommand: " + command);
            system(command.c_str());
        }
    }
}
