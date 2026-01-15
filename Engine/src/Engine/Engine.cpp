//
// Created by Nikita on 29.12.2020.
//

#include <Engine/Engine.h>
#include <Engine/Application.h>
#include <Engine/EngineResources.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/World/EngineScene.h>

#include <Graphics/GUI/WidgetManager.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Window/Window.h>

#include <Physics/LibraryImpl.h>

#include <Scripting/Cpp/ScriptSystem.h>

#include <Utils/CommandManager/CmdManager.h>
#include <Utils/Input/InputDispatcher.h>
#include <Utils/Input/InputSystem.h>
#include <Utils/World/Scene.h>
#include <Utils/World/SceneUpdater.h>
#include <Utils/Common/Features.h>
#include <Utils/Common/StringAtomLiterals.h>
#include <Utils/TaskManager/ThreadWorker.h>
#include <Utils/Localization/LocalizationManager.h>

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
        SR_INFO("Engine::Create() : registering all resources...");

        if (!Resources::RegisterResources(GetThis())) {
            SR_ERROR("Engine::Create() : failed to register engine resources!");
            return false;
        }

        SR_INFO("Engine::Create() : creating main window...");

        if (SR_UTILS_NS::Features::Instance().Enabled("MainWindow", true)) {
            AddWindow(CreateMainWindow());
        }

        m_localizationManager = new SR_UTILS_NS::Localization::LocalizationManager();

        m_renderContext = new SR_GRAPH_NS::RenderContext();

        if (!m_renderContext->PreInit()) {
            SR_ERROR("Engine::Create() : failed to pre-initialize render context!");
            return false;
        }

        m_cmdManager = new SR_UTILS_NS::CmdManager();
        m_input = new SR_UTILS_NS::InputDispatcher();

        if (SR_UTILS_NS::Features::Instance().Enabled("Editor")) {
            m_editor = new SR_CORE_GUI_NS::EditorGUI(GetThis());
            m_editor->SetRenderContext(m_renderContext.Get());
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

        m_threadsWorker = SR_UTILS_NS::ThreadsWorker::Load("Engine/Configs/Threads.sras");
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
        SR_LOG("Engine::CreateMainWindow() : trying to find screen resolution...");

        auto&& resolutions = SR_PLATFORM_NS::GetScreenResolutions();

        if (resolutions.empty()) {
            SR_ERROR("Engine::CreateMainWindow() : supported resolutions are not found!");
            return nullptr;
        }
        else {
            std::string logResolutions;
            uint32_t index = 0;
            for (auto&& resolution : resolutions) {
                logResolutions += "\n\t{}: {}x{}"_format(++index, resolution.x, resolution.y);
            }
            SR_LOG("Engine::CreateMainWindow() : found {} resolutions:{}", resolutions.size(), logResolutions);
        }

        SR_MATH_NS::UVector2 resolution = resolutions[SR_MAX(static_cast<uint32_t>(resolutions.size() / 2), 0)];

        SR_LOG("Engine::CreateMainWindow() : selected resolution {}x{}", resolution.x, resolution.y);

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

        /// pWindow->SetFocusCallback([](bool focus) {
        ///     if (!focus) {
        ///         auto&& input = SR_UTILS_NS::Input::Instance();
        ///         input.ForceUnlockCursor();
        ///     }
        /// });

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

        if (!SR_SCRIPTING_NS::ScriptSystem::Instance().IsInitialized()) {
            if (!SR_SCRIPTING_NS::ScriptSystem::Instance().Init()) {
                SR_ERROR("Engine::Init() : failed to initialize script system!");
            }
        }

        m_isInit = true;

        return true;
    }

    bool Engine::Run() {
        if (!m_isInit) {
            SR_ERROR("Engine::Run() : engine is not initialized!");
            return false;
        }

        if (m_isRun) {
            SR_ERROR("Engine::Run() : engine is already running!");
            return false;
        }

        SR_INFO("Engine::Run() : running game engine...");

        m_isRun = true;

        if (m_threadsWorker) {
            m_threadsWorker->Start();
        }

        return true;
    }

    void Engine::DestroyEditor() {
        SR_SYSTEM_LOG("Engine::DestroyEditor() : destroying editor...");

        if (m_editor && m_editor->Enabled()) {
            SR_SYSTEM_LOG("Engine::DestroyEditor() : saving editor gui...");
            m_editor->Save();
        }

        SR_INFO("Engine::DestroyEditor() : destroying the editor...");

        if (m_editor && m_editor->Enabled()) {
            SR_SYSTEM_LOG("Engine::DestroyEditor() : disabling editor gui...");
            m_editor->Enable(false);
            m_input->Unregister(m_editor);
        }
        SR_SAFE_DELETE_PTR(m_editor);
    }

    bool Engine::Close() {
        SR_TRACY_ZONE;

        SR_INFO("Engine::Close() : closing game engine...");

        SR_SCRIPTING_NS::ScriptSystem::Instance().WaitForIdle();

        SRAssert2(!m_editor, "Engine::Close() : editor is not destroyed! Call DestroyEditor() before closing the engine!");

        m_isRun = false;

        if (m_threadsWorker) {
            if (m_threadsWorker->IsActive()) {
                m_threadsWorker->Stop();
            }
            m_threadsWorker.Reset();
        }

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

        //SR_SCRIPTING_NS::EvoScriptManager::Instance().Update(true);

        return true;
    }

    void Engine::AddSceneToQueue(const SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>& pScene)  {
        SR_TRACY_ZONE;
        m_sceneQueue.Push(pScene);
    }

    void Engine::Reload() {
        SR_TRACY_ZONE;
        m_application->Reload();
    }

    void Engine::FixedUpdate() {
        SR_TRACY_ZONE;

        const auto&& pFocusedWindow = GetFocusedWindow();

        if (m_editor && pFocusedWindow) {
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
                m_engineScene->pScene->SaveScene();
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

        if (m_engineScene && m_engineScene->pScene) {
            m_engineScene->pScene->GetEntityController()->SetActiveController();
        }

        return true;
    }

    void Engine::LoadStartupScene() {
        SR_TRACY_ZONE;

        SR_LOG("Engine::LoadStartupScene() : loading startup scene...");

        if (!m_engineScene && (m_editor && !m_editor->LoadSceneFromCachedPath())) {
            auto&& scenePath = SR_UTILS_NS::Path(SR_WORLD_NS::Scene::NewScenePath).ConcatExt("scene");

            if (SR_WORLD_NS::Scene::IsExists(scenePath)) {
                auto&& pScene = SR_WORLD_NS::Scene::LoadScene(scenePath);
                if (!pScene) {
                    SR_ERROR("Engine::Create() : failed to load scene! Delete broken new scene\n\tPath: " + scenePath.ToString());
                    SR_PLATFORM_NS::Delete(SR_WORLD_NS::Scene::GetAbsPath(scenePath));
                }
                else {
                    AddSceneToQueue(pScene);
                }
            }

            if (m_sceneQueue.Empty()) {
                AddSceneToQueue(SR_WORLD_NS::Scene::NewScene(scenePath, SR_WORLD_NS::SceneLogicType::Asset));
            }
        }
    }

    void Engine::SetGameMode(bool enabled) {
        SR_TRACY_ZONE;

        m_isGameMode = enabled;

        if (m_editor) {
            if (m_isGameMode) {
                m_editor->HideAll();
                //m_cursorLockOpt.emplace();
            }
            else {
                m_editor->ShowAll();
                //m_cursorLockOpt = std::nullopt;
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

    const Engine::ScenePtr& Engine::GetScene() const {
        static ScenePtr nullScene;
        return m_engineScene ? m_engineScene->pScene : nullScene;
    }

    SR_WORLD_NS::SceneUpdater* Engine::GetSceneBuilder() const {
        return m_engineScene ? m_engineScene->pSceneUpdater : nullptr;
    }

    const Engine::RenderScenePtr& Engine::GetRenderScene() const {
        if (m_engineScene) {
            return m_engineScene->pRenderScene;
        }
        static RenderScenePtr nullRenderScene;
        return nullRenderScene;
    }

    const Engine::PhysicsScenePtr& Engine::GetPhysicsScene() const {
        if (m_engineScene) {
            return m_engineScene->pPhysicsScene;
        }
        static PhysicsScenePtr nullPhysicsScene;
        return nullPhysicsScene;
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
        return GetFocusedWindow();
    }

    SR_UTILS_NS::Debug& Engine::GetDebugger() const {
        return SR_UTILS_NS::Debug::Instance();
    }

    Engine::WindowPtr Engine::GetFocusedWindow() const {
        for (auto&& pWindow : m_windows) {
            if (pWindow->IsWindowFocus()) {
                return pWindow;
            }
        }
        static WindowPtr nullWindow;
        return nullWindow;
    }

    const SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::ThreadsWorker>& Engine::GetThreadsWorker() const {
        return m_threadsWorker;
    }

    void Engine::ProcessInput() {
        SR_TRACY_ZONE;

        const auto&& pFocusedWindow = GetFocusedWindow();

        if (pFocusedWindow) {
            SR_UTILS_NS::Input::Instance().SetFocusedWindowRect(pFocusedWindow->GetWindowRect());
        }
        else {
            SR_UTILS_NS::Input::Instance().SetFocusedWindowRect(std::nullopt);
        }

        SR_UTILS_NS::Input::Instance().SetPlayMode(!IsPaused() && IsGameMode());
        SR_UTILS_NS::Input::Instance().Update();

        if (pFocusedWindow) {
            if (m_input) {
                m_input->Check();
            }

            bool lShiftPressed = SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::LShift);

            if (m_cmdManager && !IsGameMode() && SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Ctrl)) {
                if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::Z)) {
                    m_cmdManager->Cancel();
                }

                if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::Y)) {
                    if (!m_cmdManager->Redo()) {
                        SR_WARN("Engine::FixedUpdate() : failed to redo \"" + m_cmdManager->GetLastCmdName() + "\" command!");
                    }
                }
            }

            /// if (!IsGameMode() && m_editor && SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F1)) {
            ///     m_editor->SetDockingEnabled(!m_editor->IsDockingEnabled());
            /// }

            if (m_editor && IsActive() && SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F2)) {
                SetGameMode(!IsGameMode());
            }

            if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F3) && lShiftPressed) {
                Reload();
            }
        }
    }
}
