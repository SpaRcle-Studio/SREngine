//
// Created by Nikita on 19.07.2021.
//

#include <Engine/Engine.h>

#include <Engine/Settings/EditorSettings.h>

#include <Engine/EngineCommands.h>
#include <Engine/GUI/About.h>
#include <Engine/GUI/AnimatorEditor.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/GUI/EngineSettings.h>
#include <Engine/GUI/EngineStatistics.h>
#include <Engine/GUI/FileBrowser.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/Inspector.h>
#include <Engine/GUI/PhysicsMaterialEditor.h>
#include <Engine/GUI/RenderTechniqueEditor.h>
#include <Engine/GUI/SceneTools.h>
#include <Engine/GUI/SceneViewer.h>
#include <Engine/GUI/VisualScriptEditor.h>
#include <Engine/GUI/WorldEdit.h>

#include <Utils/Common/Features.h>
#include <Utils/Common/StringAtomLiterals.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/ECS/Prefab.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Profile/TracyContext.h>
#include <Utils/World/ScenePrefabLogic.h>
#include <Utils/World/SceneUpdater.h>

#include <Graphics/Render/RenderContext.h>
#include <Graphics/SRSL/Shader.h>
#include <Graphics/Types/Texture.h>
#include <Graphics/Window/Window.h>

namespace SR_CORE_GUI_NS {
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
        : Super() {
        m_cachedScenePath =
            SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("/PreviousScenePath").ConcatExt("cache");

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

        if (!SRVerifyFalse2(
                !(m_context = SR_THIS_THREAD->GetContext()->GetValue<RenderContextPtr>()), "Is not render context!"
            )) {
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
        } else {
            m_dragWindow = false;
        }

        if (m_imGuiDemo) {
            // ImGui::ShowDemoWindow(&m_imGuiDemo);
        }

        WidgetManager::Draw();
    }

    void EditorGUI::DrawDockingSpace() {
        m_dragWindow = false;

        SR_GRAPH_GUI_NS::Immediate::BeginDocking();

        if (SR_GRAPH_GUI_NS::Immediate::BeginMainMenuBar()) {
            auto&& pMenuBarWindow = SR_GRAPH_GUI_NS::Immediate::FindWindowByName("##MainMenuBar");

            if (m_click == Click::None &&
                SR_GRAPH_GUI_NS::Immediate::IsMouseDragging(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left)) {
                m_click = SR_GRAPH_GUI_NS::Immediate::GetWindowRect(pMenuBarWindow)
                                  .Contains(SR_GRAPH_GUI_NS::Immediate::GetMousePos())
                              ? Click::Drag
                              : Click::Miss;
            } else if (SR_GRAPH_GUI_NS::Immediate::IsMouseReleased(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left)) {
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
                pWindow->Close();
            }

            SR_GRAPH_GUI_NS::Immediate::SetCursorPosX(SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x - 45);
            SR_GRAPH_GUI_NS::Immediate::SetCursorPosY(0);
            if (pWindow->GetState() == Graphics::WindowState::Default &&
                SR_GRAPH_GUI_NS::Immediate::SmallButton("[ ]")) {
                pWindow->Maximize();
            }

            if (pWindow->GetState() == Graphics::WindowState::Maximized &&
                SR_GRAPH_GUI_NS::Immediate::SmallButton("[=]")) {
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
            const auto path =
                SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/EditorWidgets.xml");

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
                auto&& pos = pWin->GetPosition();
                pos += drag;
                pWin->Move(pos.x, pos.y);
            }
        }

        WidgetManager::OnMouseMove(data);
    }

    void EditorGUI::OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) { WidgetManager::OnKeyDown(data); }

    void EditorGUI::OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) { WidgetManager::OnKeyPress(data); }

    void EditorGUI::OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) { WidgetManager::OnKeyUp(data); }

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

    void* EditorGUI::GetIconDescriptor(EditorIcon icon) const {
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
            SR_LOG("EditorGUI::CacheScenePath() : scene path is \"NONE\". "
                   "Caching this value.");
            return;
        }

        if (scenePath.Contains(SR_WORLD_NS::Scene::RuntimeScenePath)) {
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
                SR_LOG("EditorGUI::LoadSceneFromCachedPath() : cached file of "
                       "scene path wasn't found!");
            }
            return false;
        }

        auto&& marshal = SR_HTYPES_NS::Marshal::Load(m_cachedScenePath);
        SR_UTILS_NS::Path scenePath = marshal.Read<std::string>();

        if (scenePath.IsEmpty()) {
            return false;
        }

        if (scenePath.ToStringView() == "NONE") {
            SR_LOG("EditorGUI::LoadSceneFromCachedPath() : cached scene path "
                   "is \"NONE\". No scene to load.");
            return false;
        }

        if (!SR_WORLD_NS::Scene::IsExists(scenePath)) {
            SR_WARN(
                "EditorGUI::LoadSceneFromCachedPath() : cached path is not "
                "usable! \n\tPath: " +
                scenePath.ToStringRef() + "\n\tUsing default scene."
            );
            scenePath = SR_UTILS_NS::Path(SR_WORLD_NS::Scene::NewScenePath).ConcatExt("scene");
        }

        if (!SR_WORLD_NS::Scene::IsExists(scenePath)) {
            SR_ERROR(
                "EditorGUI::LoadSceneFromCachedPath() : default scene does not "
                "exist! \n\tCreating new one by path: " +
                scenePath.ToStringRef()
            );
            m_engine->AddSceneToQueue(SR_WORLD_NS::Scene::NewScene(scenePath, SR_WORLD_NS::SceneLogicType::Asset));
            return true;
        }

        auto&& pScene = SR_WORLD_NS::Scene::LoadScene(scenePath);
        if (!pScene) {
            SR_ERROR(
                "EditorGUI::LoadSceneFromCachedPath() : failed to load scene "
                "by path: " +
                scenePath.ToStringRef()
            );
            return false;
        }

        m_engine->AddSceneToQueue(pScene);
        return true;
    }

    void EditorGUI::ReloadWindows() {
        const auto path =
            SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/EditorWidgets.xml");

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
                } else
                    pIt->second->Close();
            }
        }
    }

    void EditorGUI::ResetToDefault() {
        const auto&& defaultConfigPath =
            SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/ImGuiEditor.config");
        const auto&& defaultWidgetsPath =
            SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/EditorWidgets.xml");

        SR_UTILS_NS::Platform::Copy(
            SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Editor/Configs/ImGuiEditor.config"),
            defaultConfigPath
        );
        SR_UTILS_NS::Platform::Copy(
            SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Editor/Configs/EditorWidgets.xml"),
            defaultWidgetsPath
        );

        ReloadWindows();
        ShowAll();

        SR_GRAPH_GUI_NS::Immediate::LoadIniSettingsFromDisk();
    }

    void EditorGUI::DrawMenuBar() {
        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(
            SR_GRAPH_GUI_NS::Immediate::StyleVar::WindowPadding, SR_MATH_NS::FVector2(8, 8)
        );

        if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("File")) {
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("New scene")) {
                m_engine->AddSceneToQueue(
                    SR_WORLD_NS::Scene::NewScene(GetNewScenePath(), SR_WORLD_NS::SceneLogicType::Asset)
                );
                CacheScenePath(m_engine->GetScene()->GetPath());
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("New prefab")) {
                if (auto&& pScene = m_engine->GetScene(); pScene.RecursiveLockIfValid()) {
                    // TODO: проверку на то, что нынешний префаб не сохранён,
                    // чтобы не спамить ими
                    pScene->SaveScene();
                    CacheScenePath(m_engine->GetScene()->GetPath());
                    pScene.Unlock();
                }

                m_engine->AddSceneToQueue(
                    SR_WORLD_NS::Scene::NewScene(GetNewPrefabPath(), SR_WORLD_NS::SceneLogicType::Prefab)
                );
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Load")) {
                auto&& scenesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();

                if (auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(
                        scenesPath.ToString(), {{"Scene", "scene,prefab"}}
                    );
                    !path.IsEmpty()) {
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
                if (auto&& pScene = m_engine->GetScene(); pScene.RecursiveLockIfValid()) {
                    pScene->SaveScene();
                    pScene.Unlock();
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Save at")) {
                if (auto&& pScene = m_engine->GetScene(); pScene.RecursiveLockIfValid()) {
                    const auto scenesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();

                    if (auto&& path = SR_UTILS_NS::FileDialog::Instance().SaveDialog(
                            scenesPath.ToString(), {{"Scene", "scene,prefab"}}
                        );
                        !path.IsEmpty()) {
                        path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetCachePath());
                        path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

                        if (pScene->SaveSceneAt(path)) {
                            SR_SYSTEM_LOG(
                                "GUISystem::BeginMenuBar() : scene is saved as "
                                "\"" +
                                path.ToString() + "\""
                            );

                            if (auto&& pSavedScene = SR_WORLD_NS::Scene::LoadScene(path)) {
                                m_engine->AddSceneToQueue(pSavedScene);
                                CacheScenePath(path);
                            }
                        } else {
                            SR_ERROR(
                                "GUISystem::BeginMenuBar() : failed to save "
                                "scene! \n\tPath: \"" +
                                path.ToString() + "\""
                            );
                        }
                    }

                    pScene.Unlock();
                } else {
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

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Reload")) {
                m_engine->Reload();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Exit")) {
                m_engine->GetMainWindow()->GetBaseWindow()->Close();
            }

            SR_GRAPH_GUI_NS::Immediate::EndMenu();
        }

        if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("Editor")) {
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Instance from file")) {
                if (auto&& pScene = m_engine->GetScene(); pScene.RecursiveLockIfValid()) {
                    auto&& resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                    if (auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(
                            resourcesPath.ToString(), {{"Any model", "prefab,pmx,fbx,obj,blend,dae,abc,stl,ply,"
                                                                     "glb,gltf,x3d,sfg,bvh,3ds,gltf"}}
                        );
                        !path.IsEmpty()) {
                        InstantiateSO(pScene->InstanceFromFile(path));
                    }
                    pScene.Unlock();
                } else {
                    SR_WARN("GUISystem::BeginMenuBar() : scene is not valid!");
                }
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("Instantiate")) {
                if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Empty")) {
                    if (auto&& pScene = m_engine->GetScene()) {
                        InstantiateSO(
                            pScene->InstanceGameObject("New GameObject"_atom).StaticCast<SR_UTILS_NS::SceneObject>()
                        );
                    }
                }

                SR_GRAPH_GUI_NS::Immediate::Separator();

                if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Cube")) {
                    if (auto&& pScene = m_engine->GetScene()) {
                        auto&& pGameObject = pScene->InstanceGameObject("Cube"_atom);
                        if (auto&& pRigidbody = pGameObject->AddComponent<SR_PHYSICS_NS::Types::Rigidbody3D>()) {
                            pRigidbody->SetMass(1.0f);
                            pRigidbody->SetType(SR_PHYSICS_NS::ShapeType::Box3D);
                        }

                        auto&& meshes =
                            SR_GTYPES_NS::Mesh::Load("Engine/Models/cube.obj", SR_GRAPH_NS::MeshType::Static);
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
                            pRigidbody->SetType(SR_PHYSICS_NS::ShapeType::Sphere3D);
                        }

                        auto&& meshes =
                            SR_GTYPES_NS::Mesh::Load("Engine/Models/sphere.obj", SR_GRAPH_NS::MeshType::Static);
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
                            pRigidbody->SetType(SR_PHYSICS_NS::ShapeType::Capsule3D);
                        }

                        auto&& meshes =
                            SR_GTYPES_NS::Mesh::Load("Engine/Models/capsule.obj", SR_GRAPH_NS::MeshType::Static);
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
                            pRigidbody->SetType(SR_PHYSICS_NS::ShapeType::Cylinder3D);
                        }

                        auto&& meshes =
                            SR_GTYPES_NS::Mesh::Load("Engine/Models/cylinder.obj", SR_GRAPH_NS::MeshType::Static);
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
                            pRigidbody->SetType(SR_PHYSICS_NS::ShapeType::Plane3D);
                        }

                        auto&& meshes =
                            SR_GTYPES_NS::Mesh::Load("Engine/Models/plane.obj", SR_GRAPH_NS::MeshType::Static);
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
                            pRigidbody->SetType(SR_PHYSICS_NS::ShapeType::Convex3D);
                            pRigidbody->GetCollisionShape()->SetRawMesh("Engine/Models/statue.obj");
                        }

                        auto&& meshes =
                            SR_GTYPES_NS::Mesh::Load("Engine/Models/statue.obj", SR_GRAPH_NS::MeshType::Static);
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
                            pRigidbody->SetType(SR_PHYSICS_NS::ShapeType::Convex3D);
                            pRigidbody->GetCollisionShape()->SetRawMesh("Engine/Models/monkey.obj");
                        }

                        auto&& meshes =
                            SR_GTYPES_NS::Mesh::Load("Engine/Models/monkey.obj", SR_GRAPH_NS::MeshType::Static);
                        for (auto&& pMesh : meshes) {
                            pGameObject->AddComponent(pMesh.StaticCast<SR_UTILS_NS::Component>());
                        }
                        InstantiateSO(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
                    }
                }

                SR_GRAPH_GUI_NS::Immediate::EndMenu();
            }

            SR_GRAPH_GUI_NS::Immediate::EndMenu();
        }

        DrawWindowPage();

        if (SR_GRAPH_GUI_NS::Immediate::MenuItem("About")) {
            OpenWidget<About>();
        }

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(115);

        const float_t framerate = SR_GRAPH_GUI_NS::Immediate::GetFramerate();
        SR_GRAPH_GUI_NS::Immediate::LabelText(
            "##FPSLable", "|   FPS: %.2f (%.2gms)", framerate, framerate > 0.f ? 1000.0f / framerate : 0.0f
        );

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

            /// if (ImGui::MenuItem("Animator")) {
            ///    OpenWidget<AnimatorEditor>();
            /// }

            /// ImGui::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("World edit")) {
                OpenWidget<WorldEdit>();
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Physics material editor")) {
                OpenWidget<PhysicsMaterialEditor>();
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
                } else {
                    SRHalt("EditorGUI::InstantiateSO() : prefab root is nullptr!");
                    pSO->Destroy();
                    return;
                }
            }
        }

        if (pInstantiateTarget) {
            pInstantiateTarget->AddChild(pSO);
        }

        auto&& pCmd = new SR_CORE_NS::Commands::SceneObjectInstance(GetEngine(), pSO);
        GetEngine()->GetCmdManager()->Store(pCmd);
    }
} // namespace SR_CORE_GUI_NS
