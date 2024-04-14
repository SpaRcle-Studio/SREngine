//
// Created by Nikita on 29.12.2020.
//

#include <Core/Engine.h>
#include <Core/EngineResources.h>
#include <Core/EngineMigrators.h>
#include <Core/GUI/EditorGUI.h>
#include <Core/World/EngineScene.h>

#include <Utils/Events/EventManager.h>
#include <Utils/World/Scene.h>
#include <Utils/World/SceneUpdater.h>
#include <Utils/Common/Features.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Localization/LocalizationManager.h>

#include <Graphics/GUI/WidgetManager.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/DebugRenderer.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Memory/CameraManager.h>
#include <Graphics/Window/Window.h>
#include <Graphics/Types/Geometry/SkinnedMesh.h>
#include <Graphics/GUI/Editor/Theme.h>
#include <Graphics/Pipeline/Vulkan/VulkanTracy.h>

#include <Physics/Rigidbody.h>
#include <Physics/LibraryImpl.h>
#include <Physics/PhysicsLib.h>
#include <Physics/PhysicsScene.h>
#include <Physics/3D/Raycast3D.h>
#include <Physics/PhysicsMaterial.h>

#include <Scripting/Impl/EvoScriptManager.h>

namespace SR_CORE_NS {
    Engine::Engine(Application* pApplication)
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        , m_application(pApplication)
    { }

    Engine::~Engine() {
        m_renderContext.AutoFree([](auto&& pContext) {
            delete pContext;
        });
    }

    bool Engine::Create() {
        SR_INFO("Engine::Create() : register all resources...");

        if (!Resources::RegisterResources(GetThis())) {
            SR_ERROR("Engine::Create() : failed to register engine resources!");
            return false;
        }

        if (!RegisterMigrators()) {
            SR_ERROR("Engine::Create() : failed to register engine migrators!");
            return false;
        }

        SR_INFO("Engine::Create() : create main window...");

        if (SR_UTILS_NS::Features::Instance().Enabled("MainWindow", true)) {
            AddWindow(CreateMainWindow());
        }

        SR_UTILS_NS::ComponentManager::Instance().SetContextInitializer([pEngine = GetThis()](auto&& context) {
            if (!pEngine) {
                SRHalt("Engine is nullptr!");
                return;
            }
            context.SetValue(pEngine->GetMainWindow());

            context.template SetPointer<SR_PHYSICS_NS::LibraryImpl>("2DPLib", SR_PHYSICS_NS::PhysicsLibrary::Instance().GetActiveLibrary(SR_UTILS_NS::Measurement::Space2D));
            context.template SetPointer<SR_PHYSICS_NS::LibraryImpl>("3DPLib", SR_PHYSICS_NS::PhysicsLibrary::Instance().GetActiveLibrary(SR_UTILS_NS::Measurement::Space3D));
        });

        SR_LOG("Engine::RegisterLibraries() : registering all libraries...");

        SpaRcle::API::RegisterEvoScriptClasses(this);

        m_localizationManager = new SR_UTILS_NS::Localization::LocalizationManager();

        ///TEST
        /// SR_UTILS_NS::Path configPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
        /// configPath = configPath.Concat(R"(Localization\Editor\loc_config.yml)");
        /// m_localizationManager->LoadInfoAsConfigFile(configPath);
        ///TEST

        m_renderContext = new SR_GRAPH_NS::RenderContext();

        m_cmdManager = new SR_UTILS_NS::CmdManager();
        m_input = new SR_UTILS_NS::InputDispatcher();

        if (SR_UTILS_NS::Features::Instance().Enabled("Editor")) {
            m_editor = new SR_CORE_GUI_NS::EditorGUI(GetThis());
        }

        if (m_isCreate) {
            SR_ERROR("Engine::Create() : game engine is already created!");
            return false;
        }

        SR_INFO("Engine::Create() : creating game engine...");

        m_input->Register(&Graphics::GUI::GlobalWidgetManager::Instance());

        if (m_editor) {
            m_input->Register(m_editor);
        }

        SetGameMode(!SR_UTILS_NS::Features::Instance().Enabled("EditorOnStartup", false));

        m_autoReloadResources = SR_UTILS_NS::Features::Instance().Enabled("AutoReloadResources", false);

        if (!m_engineScene && (m_editor && !m_editor->LoadSceneFromCachedPath())) {
            auto&& scenePath = SR_WORLD_NS::Scene::NewScenePath.ConcatExt("scene");

            if (SR_WORLD_NS::Scene::IsExists(scenePath)) {
                if (!SetScene(SR_WORLD_NS::Scene::Load(scenePath))) {
                    SR_ERROR("Engine::Create() : failed to load scene!\n\tPath: " + scenePath.ToString());
                }
            }
            else if (!SetScene(SR_WORLD_NS::Scene::New(scenePath))) {
                SR_ERROR("Engine::Create() : failed to create new scene!\n\tPath: " + scenePath.ToString());
            }
        }

        m_threadsWorker = SR_UTILS_NS::ThreadsWorker::Load("Engine/Configs/Threads.yml");
        if (!m_threadsWorker) {
            SR_ERROR("Engine::Create() : failed to load threads worker!");
            return false;
        }

        m_threadsWorker->GetContext().SetPointer(this);

        m_timeStart = Clock::now();

        m_isCreate = true;

        return true;
    }

    Engine::WindowPtr Engine::CreateMainWindow() {
        SR_LOG("Engine::CreateMainWindow() : try found screen resolution...");

        auto&& resolutions = SR_PLATFORM_NS::GetScreenResolutions();

        if (resolutions.empty()) {
            SR_ERROR("Engine::CreateMainWindow() : not found supported resolutions!");
            return nullptr;
        }
        else {
            SR_LOG("Engine::CreateMainWindow() : found " + std::to_string(resolutions.size()) + " resolutions");
        }

        SR_MATH_NS::UVector2 resolution = resolutions[SR_MAX(static_cast<uint32_t>(resolutions.size() / 2), 0)];

        if (resolution.HasZero()) {
            SR_ERROR("Engine::CreateMainWindow() : resolution can not be {}x{}!", resolution.x, resolution.y);
            return nullptr;
        }

        SR_GRAPH_NS::Window::Ptr pWindow = new SR_GRAPH_NS::Window();

        if (!pWindow->Initialize("SpaRcle Engine", resolution)) {
            SR_ERROR("Engine::CreateMainWindow() : failed to initialize window!");
            return nullptr;
        }

        SR_LOG("Engine::CreateMainWindow() : initializing window callbacks...");

        pWindow->SetFocusCallback([](bool focus) {
            SR_SYSTEM_LOG("Window focus state: {}", focus ? "True" : "False");
            SR_UTILS_NS::Input::Instance().Reload();
        });

        pWindow->SetScrollCallback([](double_t xOffset, double_t yOffset) {
            SR_UTILS_NS::Input::Instance().SetMouseScroll(xOffset, yOffset);
        });

        return pWindow;
    }

    bool Engine::Init() {
        if (!m_isCreate) {
            SR_ERROR("Engine::Init() : engine is not created!");
            return false;
        }

        if (m_isInit) {
            SR_ERROR("Engine::Init() : engine is already initialized!");
            return false;
        }

        SR_INFO("Engine::Init() : initializing game engine...");

        m_isInit = true;

        return true;
    }

    bool Engine::Run() {
        if (!m_isInit) {
            SR_ERROR("Engine::Run() : engine is not initialized!");
            return false;
        }

        if (m_isRun) {
            SR_ERROR("Engine::Run() : engine already running!");
            return false;
        }

        SR_INFO("Engine::Run() : running game engine...");

        m_isRun = true;

        if (m_threadsWorker) {
            m_threadsWorker->Start();
        }

        return true;
    }

    bool Engine::Close() {
        SR_TRACY_ZONE;

        SR_INFO("Engine::Close() : closing game engine...");

        m_isRun = false;

        if (m_threadsWorker) {
            if (m_threadsWorker->IsActive()) {
                m_threadsWorker->Stop();
            }
            m_threadsWorker.Reset();
        }

        SR_INFO("Engine::Close() : destroying the editor...");

        if (m_editor && m_editor->Enabled()) {
            SR_SYSTEM_LOG("Engine::Await() : disabling editor gui...");
            m_editor->Save();
            m_editor->Enable(false);
            m_input->Unregister(m_editor);
        }
        SR_SAFE_DELETE_PTR(m_editor);

        if (m_input) {
            m_input->UnregisterAll();
        }
        SR_SAFE_DELETE_PTR(m_input);

        SR_SAFE_DELETE_PTR(m_cmdManager);

        for (auto&& pWindow : m_windows) {
            pWindow.AutoFree([](auto&& pWindow) {
                pWindow->Close();
                delete pWindow;
            });
        }

        SR_SCRIPTING_NS::EvoScriptManager::Instance().Update(true);

        return true;
    }

    bool Engine::SetScene(const SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene> &scene)  {
        SRAssert(!scene.IsLocked());
        m_sceneQueue.Push(scene);
        return true;
    }

    void Engine::Reload() {
        m_application->Reload();
    }

    void Engine::FixedUpdate() {
        SR_TRACY_ZONE;

        ///В этом блоке находится обработка нажатия клавиш, которая не должна срабатывать, если окно не сфокусированно
        if (IsApplicationFocused())
        {
            SR_UTILS_NS::Input::Instance().Check();
            m_input->Check();

            bool lShiftPressed = SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::LShift);

            if (!IsGameMode() && SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Ctrl)) {
                if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::Z)) {
                    m_cmdManager->Cancel();
                }

                if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::Y)) {
                    if (!m_cmdManager->Redo()) {
                        SR_WARN("Engine::FixedUpdate() : failed to redo \"" + m_cmdManager->GetLastCmdName() + "\" command!");
                    }
                }
            }

            if (!IsGameMode() && m_editor && SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F1)) {
                m_editor->SetDockingEnabled(!m_editor->IsDockingEnabled());
            }

            if (m_editor && SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F9)) {
                SR_UTILS_NS::Input::Instance().LockCursor(!SR_UTILS_NS::Input::Instance().IsCursorLocked());
            }

            if (m_editor && IsActive() && SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F2)) {
                SetGameMode(!IsGameMode());
                SR_UTILS_NS::Input::Instance().LockCursor(IsGameMode());
                SR_UTILS_NS::Input::Instance().SetCursorVisible(!IsGameMode());
            }

            if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F3) && lShiftPressed) {
                Reload();
                return;
            }

            auto&& pMainWindow = GetMainWindow();

            if (pMainWindow && IsGameMode() && SR_UTILS_NS::Input::Instance().IsMouseMoved() && SR_UTILS_NS::Input::Instance().IsCursorLocked()) {
                auto&& resolution = pMainWindow->GetSize();
                resolution /= 2;
                SR_PLATFORM_NS::SetMousePos(pMainWindow->GetPosition() + resolution.Cast<int32_t>());
                SR_UTILS_NS::Input::Instance().ResetMouse();
            }
        }

        if (m_editor && IsApplicationFocused()) {
            m_editor->FixedUpdate();
        }
    }

    void Engine::SetActive(bool isActive) {
        if (m_isActive == isActive) {
            return;
        }

        m_isActive = isActive;

        if (m_engineScene) {
            m_engineScene->SetActive(isActive);
        }
    }

    void Engine::SetSpeed(float_t speed) {
        m_speed = speed;
    }

    void Engine::SetPaused(bool isPaused) {
        if (m_isPaused == isPaused) {
            return;
        }

        m_isPaused = isPaused;

        if (m_engineScene) {
            m_engineScene->SetPaused(isPaused);
        }
    }

    bool Engine::FlushScene() {
        SR_TRACY_ZONE;

        if (m_sceneQueue.Empty()) {
            return false;
        }

        m_sceneQueue.Flush([this](auto&& newScene) {
            if (m_cmdManager) {
                m_cmdManager->Clear();
            }

            if (m_engineScene && m_engineScene->pScene.RecursiveLockIfValid()) {
                m_engineScene->pScene->Save();
                m_engineScene->pScene.Unlock();
            }

            SR_SAFE_DELETE_PTR(m_engineScene);

            if (!newScene) {
                return;
            }

            m_engineScene = new EngineScene(newScene, this);
            if (!m_engineScene->Init()) {
                SR_ERROR("Engine::FlushScene() : failed to initialize scene!");
                SR_SAFE_DELETE_PTR(m_engineScene);
            }
        });

        if (m_editor && m_engineScene) {
            m_editor->SetScene(m_engineScene->pScene);
        }

        return true;
    }

    void Engine::SetGameMode(bool enabled) {
        m_isGameMode = enabled;

        if (m_editor) {
            if (m_isGameMode) {
                m_editor->HideAll();
            }
            else {
                m_editor->ShowAll();
            }
        }

        if (m_engineScene) {
            m_engineScene->SetGameMode(m_isGameMode);
        }

        if (m_editor) {
            m_editor->Enable(!m_isGameMode);
        }
    }

    bool Engine::IsNeedReloadResources() {
        return m_autoReloadResources && !IsGameMode();
    }

    Engine::ScenePtr Engine::GetScene() const {
        return m_engineScene ? m_engineScene->pScene : ScenePtr();
    }

    SR_WORLD_NS::SceneUpdater* Engine::GetSceneBuilder() const {
        return m_engineScene ? m_engineScene->pSceneUpdater : nullptr;
    }

    Engine::RenderScenePtr Engine::GetRenderScene() const {
        return m_engineScene ? m_engineScene->pRenderScene : RenderScenePtr();
    }

    Engine::PhysicsScenePtr Engine::GetPhysicsScene() const {
        return m_engineScene ? m_engineScene->pPhysicsScene : PhysicsScenePtr();
    }

    bool Engine::Execute() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        bool isAlive = true;

        if (!IsRun()) {
            SR_SYSTEM_LOG("Engine::Execute() : engine is not running!");
            isAlive = false;
        }

        if (!m_threadsWorker->IsAlive()) {
            SR_SYSTEM_LOG("Engine::Execute() : threads worker is not alive!");
            isAlive = false;
        }

        if (m_threadsWorker && !isAlive && m_threadsWorker->IsActive()) {
            m_threadsWorker->Stop();
            m_threadsWorker.Reset();
        }

        return isAlive;
    }

    void Engine::AddWindow(Engine::WindowPtr pWindow) {
        pWindow->SetResizeCallback([this](auto&& size) {
            if (m_renderContext) {
                m_renderContext->OnResize(size);
            }
        });

        m_windows.emplace_back(std::move(pWindow));
    }

    bool Engine::IsApplicationFocused() const {
        if (m_windows.empty()) {
            return true;
        }

        for (auto&& pWindow : m_windows) {
            if (pWindow->IsWindowFocus()) {
                return true;
            }
        }

        return false;
    }
}