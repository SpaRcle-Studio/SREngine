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
#include <Utils/World/SceneBuilder.h>
#include <Utils/Common/Features.h>
#include <Utils/ECS/ComponentManager.h>

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
        : Super(this)
        , m_application(pApplication)
    { }

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

        if (!CreateMainWindow()) {
            SR_ERROR("Engine::Create() : failed to create main window!");
            return false;
        }

        if (!InitializeRender()) {
            SR_ERROR("Engine::Create() : failed to initialize render!");
            return false;
        }

        SR_UTILS_NS::ComponentManager::Instance().SetContextInitializer([pEngine = GetThis()](auto&& context) {
            if (!pEngine) {
                SRHalt("Engine is nullptr!");
                return;
            }
            context.SetValue(pEngine->GetWindow());

            context.template SetPointer<SR_PHYSICS_NS::LibraryImpl>("2DPLib", SR_PHYSICS_NS::PhysicsLibrary::Instance().GetActiveLibrary(SR_UTILS_NS::Measurement::Space2D));
            context.template SetPointer<SR_PHYSICS_NS::LibraryImpl>("3DPLib", SR_PHYSICS_NS::PhysicsLibrary::Instance().GetActiveLibrary(SR_UTILS_NS::Measurement::Space3D));
        });

        SR_LOG("Engine::RegisterLibraries() : registering all libraries...");

        SpaRcle::API::RegisterEvoScriptClasses(this);

        m_cmdManager = new SR_UTILS_NS::CmdManager();
        m_input      = new SR_UTILS_NS::InputDispatcher();
        m_editor     = new SR_CORE_GUI_NS::EditorGUI(GetThis());

        m_worldTimer = SR_HTYPES_NS::Timer(1u);

        if (m_isCreate) {
            SR_ERROR("Engine::Create() : game engine is already created!");
            return false;
        }

        SR_INFO("Engine::Create() : creating game engine...");

        m_input->Register(&Graphics::GUI::GlobalWidgetManager::Instance());
        m_input->Register(m_editor);

        SetGameMode(!SR_UTILS_NS::Features::Instance().Enabled("EditorOnStartup", false));

        m_autoReloadResources = SR_UTILS_NS::Features::Instance().Enabled("AutoReloadResources", false);

        if (!m_engineScene && !m_editor->LoadSceneFromCachedPath()) {
            auto&& scenePath = SR_WORLD_NS::Scene::NewScenePath.ConcatExt("scene");

            if (SR_WORLD_NS::Scene::IsExists(scenePath)) {
                if (!SetScene(SR_WORLD_NS::Scene::Load(scenePath))) {
                    SR_ERROR("Engine::Create() : failed to load scene!\n\tPath: " + scenePath.ToString())
                }
            }
            else if (!SetScene(SR_WORLD_NS::Scene::New(scenePath))) {
                SR_ERROR("Engine::Create() : failed to create new scene!\n\tPath: " + scenePath.ToString())
            }
        }

        FlushScene();

        m_timeStart = Clock::now();

        m_isCreate = true;

        return true;
    }

    bool Engine::CreateMainWindow() {
        SR_LOG("Engine::CreateMainWindow() : try found screen resolution...");

        SR_MATH_NS::UVector2 resolution;
        SR_MATH_NS::IVector2 position;
        bool isMaximized = true;

        auto&& cachePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();
        auto&& windowSettingsPath = cachePath.Concat("WindowSettings.xml");

        const bool windowSettingsExist = windowSettingsPath.Exists();

        if (windowSettingsExist) {
            auto&& windowSettings = SR_XML_NS::Document::Load(windowSettingsPath);

            auto&& rootNode = windowSettings.Root().TryGetNode("Settings");

            resolution = rootNode.TryGetNode("Size").GetAttribute<SR_MATH_NS::UVector2>();
            position = rootNode.TryGetNode("Position").GetAttribute<SR_MATH_NS::IVector2>();
            isMaximized = rootNode.GetAttribute("IsMaximized").ToBool();
        }
        else {
            auto&& resolutions = SR_PLATFORM_NS::GetScreenResolutions();

            if (resolutions.empty()) {
                SR_ERROR("Engine::CreateMainWindow() : not found supported resolutions!");
                return false;
            }
            else {
                SR_LOG("Engine::CreateMainWindow() : found " + std::to_string(resolutions.size()) + " resolutions");
            }

            resolution = resolutions[SR_MAX(static_cast<uint32_t>(resolutions.size() / 2), 0)];
        }

        if (resolution.x == 0 || resolution.y == 0) {
            SR_ERROR("Engine::CreateMainWindow() : resolution can not be " +
                    std::to_string(resolution.x) + "x" + std::to_string(resolution.y) + "!");
            return false;
        }

        m_window = new SR_GRAPH_NS::Window();
        if (!m_window->Initialize("SpaRcle Engine", resolution)) {
            SR_ERROR("Engine::CreateMainWindow() : failed to initialize window!");
            return false;
        }

        if (auto&& pWin = m_window->GetImplementation<SR_GRAPH_NS::BasicWindowImpl>()) {
            if (windowSettingsExist) {
                pWin->Move(position.x, position.y);
            }
            else {
                pWin->Centralize();
            }

            if (isMaximized) {
                pWin->Maximize();
            }
        }

        SR_LOG("Engine::CreateMainWindow() : initializing window callbacks...");

        m_window->SetDrawCallback([this]() {
            DrawCallback();
        });

        m_window->SetFocusCallback([](bool focus) {
            SR_SYSTEM_LOG(SR_UTILS_NS::Format("Window focus state: %s", focus ? "True" : "False"));
            SR_UTILS_NS::Input::Instance().Reload();
        });

        m_window->SetResizeCallback([this](auto&& size) {
            if (m_renderContext) {
                m_renderContext->OnResize(size);
            }
        });

        m_window->SetScrollCallback([](double_t xOffset, double_t yOffset) {
            SR_UTILS_NS::Input::Instance().SetMouseScroll(xOffset, yOffset);
        });

        m_window->SetCloseCallback([this]() {
            m_renderContext.Do([](auto&& pContext) {
                pContext->Close();
            });

            SynchronizeFreeResources();

            m_renderContext.AutoFree([](auto&& pContext) {
                delete pContext;
            });
        });

        return true;
    }

    void Engine::SynchronizeFreeResources() {
        SR_TRACY_ZONE;

        SR_SYSTEM_LOG("Engine::SynchronizeFreeResources() : synchronizing resources...");

        SR_UTILS_NS::ResourceManager::Instance().SetWatchingEnabled(false);

        std::atomic<bool> syncComplete = false;

        /** Ждем, пока все графические ресурсы не освободятся */
        auto&& thread = SR_HTYPES_NS::Thread::Factory::Instance().Create([&syncComplete, this]() {
            SR_TRACY_ZONE_N("Sync free resources thread");

            uint32_t syncStep = 0;
            const uint32_t maxErrStep = 50;

            SR_UTILS_NS::ResourceManager::Instance().UpdateWatchers(0.f);
            SR_UTILS_NS::ResourceManager::Instance().ReloadResources(0.f);

            SR_UTILS_NS::ResourceManager::Instance().Synchronize(true);

            while (!m_renderContext->IsEmpty()) {
                SR_TRACY_ZONE_N("Sync free resources iteration");

                SR_SYSTEM_LOG("Engine::SynchronizeFreeResources() : synchronizing resources (step " + std::to_string(++syncStep) + ")");

                SR_UTILS_NS::ResourceManager::Instance().Synchronize(true);

                if (maxErrStep == syncStep) {
                    SR_ERROR("Engine::SynchronizeFreeResources() : [FATAL] resources can not be released!");
                    SR_UTILS_NS::ResourceManager::Instance().PrintMemoryDump();
                    SR_PLATFORM_NS::Terminate();
                    break;
                }

                SR_HTYPES_NS::Thread::Sleep(50);
            }

            SR_SYSTEM_LOG("Engine::SynchronizeFreeResources() : close synchronization thread...");

            syncComplete = true;
        });

        thread->SetName("Synchronize");

        /** Так как некоторые ресурсы, такие как материалы, имеют вложенные ресурсы,
         * то они могут ожидать пока графический поток уберет метку использования с них */
        while (!syncComplete) {
            m_renderContext.Do([](auto&& pContext) {
                pContext->Update();
            });
        }

        SR_UTILS_NS::ResourceManager::Instance().Synchronize(true);

        thread->TryJoin();
        thread->Free();

        SR_SYSTEM_LOG("Engine::SynchronizeFreeResources() : synchronizing is complete!");
    }

    bool Engine::InitializeRender() {
        m_renderContext = new SR_GRAPH_NS::RenderContext(m_window);

        return m_window->GetThread()->Execute([this]() -> bool {
            if (!m_renderContext->Init()) {
                SR_ERROR("Engine::InitializeRender() : failed to initialize the render context!");
                return false;
            }

            SR_THIS_THREAD->GetContext()->SetValue<RenderContextPtr>(m_renderContext);
            SR_THIS_THREAD->GetContext()->SetValue<WindowPtr>(m_window);

            return true;
        });
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

        if (SR_UTILS_NS::Features::Instance().Enabled("ChunkSystem", true)) {
            SR_INFO("Engine::Run() : running world thread...");

            m_worldThread = SR_HTYPES_NS::Thread::Factory::Instance().Create(&Engine::WorldThread, this);
            m_worldThread->SetName("World");
        }

        return true;
    }

    bool Engine::Close() {
        SR_INFO("Engine::Close() : closing game engine...");

        m_isRun = false;

        while (!m_sceneQueue.Empty()) {
            FlushScene();
        }

        if (m_editor && m_editor->Enabled()) {
            SR_SYSTEM_LOG("Engine::Await() : disabling editor gui...");
            m_editor->Save();
            m_editor->Enable(false);
        }

        if (m_input) {
            m_input->UnregisterAll();
        }
        SR_SAFE_DELETE_PTR(m_input);

        if (m_engineScene) {
            SetScene(ScenePtr());
        }

        FlushScene();

        SR_INFO("Engine::Close() : destroying the editor...");
        SR_SAFE_DELETE_PTR(m_editor);

        if (m_cmdManager) {
            SR_INFO("Engine::Close() : close the command manager...");
            m_cmdManager->Close();
        }
        SR_SAFE_DELETE_PTR(m_cmdManager);

        if (m_worldThread) {
            SR_INFO("Engine::Close() : destroying world thread...");
            m_worldThread->TryJoin();
            m_worldThread->Free();
            m_worldThread = nullptr;
        }

        m_window.AutoFree([](auto&& pWindow) {
            pWindow->Close();
            delete pWindow;
        });

        SR_SCRIPTING_NS::EvoScriptManager::Instance().Update(0.f, true);

        return true;
    }

    void Engine::DrawCallback() {
        if (!m_isRun || !m_window || m_window->IsWindowCollapsed()) {
            if (m_engineScene) {
                m_engineScene->SkipDraw();
            }
            return;
        }

        SR_TRACY_ZONE_N("Main frame");

        SR_HTYPES_NS::Time::Instance().Update();

        const auto now = SR_HTYPES_NS::Time::Instance().Now();
        const auto deltaTime = now - m_timeStart; /// nanoseconds
        const auto dt = static_cast<float_t>(deltaTime.count()) / SR_CLOCKS_PER_SEC / SR_CLOCKS_PER_SEC / SR_CLOCKS_PER_SEC; /// Seconds
        m_timeStart = now;

        SR_UTILS_NS::ResourceManager::Instance().UpdateWatchers(dt);

        if (IsNeedReloadResources()) {
            SR_UTILS_NS::ResourceManager::Instance().ReloadResources(dt);
        }

        /// синхронно отрисовываем сцену
        {
            auto&& readLock = m_sceneQueue.ReadLock();

            if (m_engineScene) {
                m_engineScene->Draw(dt);
            }
        }

        if (m_editor && m_window->IsWindowFocus()) {
            m_editor->Update(dt);
        }
    }

    bool Engine::SetScene(const SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene> &scene)  {
        SRAssert(!scene.IsLocked());
        m_sceneQueue.Push(scene);
        return true;
    }

    void Engine::Reload() {
        m_application->Reload();
    }

    void Engine::WorldThread() {
        while (m_isRun) {
            SR_HTYPES_NS::Thread::Sleep(250);

            SR_TRACY_ZONE_N("World");

            SR_MAYBE_UNUSED auto&& readLock = m_sceneQueue.ReadLock();

            if (!m_engineScene) {
                continue;
            }

            m_engineScene->UpdateMainCamera();

            auto&& pScene = m_engineScene->pScene;

            if (m_worldTimer.Update() && pScene.LockIfValid()) {
                auto&& pMainCamera = m_engineScene->pMainCamera;

                if (!pMainCamera) {
                    SR_NOOP;
                }

                else if (auto&& gameObject = dynamic_cast<SR_UTILS_NS::GameObject*>(pMainCamera->GetParent())) {
                    auto&& pLogic = pScene->GetLogicBase().DynamicCast<SR_WORLD_NS::SceneCubeChunkLogic>();
                    if (pLogic && gameObject) {
                        pLogic->SetObserver(gameObject);
                    }
                }

                pScene->GetLogicBase()->Update(m_worldTimer.GetDeltaTime());
                pScene.Unlock();
            }
        }

        SR_SYSTEM_LOG("Engine::WorldThread() : world thread completed!");
    }

    void Engine::FixedUpdate() {
        SR_TRACY_ZONE;

        ///В этом блоке находится обработка нажатия клавиш, которая не должна срабатывать, если окно не сфокусированно
        if (m_window->IsWindowFocus())
        {
            SR_UTILS_NS::Input::Instance().Check();
            m_input->Check();

            bool lShiftPressed = SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::LShift);

            if (!IsGameMode() && SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Ctrl)) {
                if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::Z))
                    m_cmdManager->Cancel();

                if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::Y))
                    if (!m_cmdManager->Redo())
                        SR_WARN("Engine::Await() : failed to redo \"" + m_cmdManager->GetLastCmdName() + "\" command!");
            }

            if (!IsGameMode() && m_editor && SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F1)) {
                m_editor->SetDockingEnabled(!m_editor->IsDockingEnabled());
            }

            if (m_editor && SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F9)) {
                SR_UTILS_NS::Input::Instance().LockCursor(!SR_UTILS_NS::Input::Instance().IsCursorLocked());
            }

            if (m_editor && IsActive() && SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F2)) {
                SetGameMode(!IsGameMode());
            }

            if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F3) && lShiftPressed) {
                Reload();
                return;
            }

            if (IsGameMode() && SR_UTILS_NS::Input::Instance().IsMouseMoved() && SR_UTILS_NS::Input::Instance().IsCursorLocked()) {
                auto&& resolution = m_window->GetSize();
                resolution /= 2;
                SR_PLATFORM_NS::SetMousePos(m_window->GetPosition() + resolution.Cast<int32_t>());
                SR_UTILS_NS::Input::Instance().ResetMouse();
            }
        }

        if (m_editor && m_window->IsWindowFocus()) {
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

    void Engine::FlushScene() {
        SR_TRACY_ZONE;

        if (m_sceneQueue.Empty()) {
            return;
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
    }

    void Engine::SetGameMode(bool enabled) {
        m_isGameMode = enabled;

        if (m_isGameMode) {
            m_editor->HideAll();
        }
        else {
            m_editor->ShowAll();
        }

        if (m_engineScene) {
            m_engineScene->SetGameMode(m_isGameMode);
        }

        m_editor->Enable(!m_isGameMode);
    }

    bool Engine::IsNeedReloadResources() {
        return m_autoReloadResources && !IsGameMode();
    }

    Engine::ScenePtr Engine::GetScene() const {
        return m_engineScene ? m_engineScene->pScene : ScenePtr();
    }

    SR_WORLD_NS::SceneBuilder* Engine::GetSceneBuilder() const {
        return m_engineScene ? m_engineScene->pSceneBuilder : nullptr;
    }

    Engine::RenderScenePtr Engine::GetRenderScene() const {
        return m_engineScene ? m_engineScene->pRenderScene : RenderScenePtr();
    }
}