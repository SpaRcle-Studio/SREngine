//
// Created by Nikita on 29.12.2020.
//

#include <Core/Engine.h>
#include <Core/GUI/EditorGUI.h>

#include <GUI/WidgetManager.h>
#include <Environment/Environment.h>

#include <Utils/Events/EventManager.h>
#include <Utils/World/Scene.h>
#include <Utils/Common/Features.h>
#include <Utils/Types/SafePtrLockGuard.h>

#include <Render/Render.h>
#include <Render/RenderScene.h>
#include <Render/RenderContext.h>
#include <Memory/CameraManager.h>
#include <Window/Window.h>

#include <Types/Skybox.h>

namespace Framework {
    bool Engine::Create(SR_GRAPH_NS::Window* window) {
        m_window = window;

        m_time       = new SR_HTYPES_NS::Time();
        m_cmdManager = new SR_UTILS_NS::CmdManager();
        m_input      = new SR_UTILS_NS::InputDispatcher();
        m_pipeline   = SR_GRAPH_NS::Environment::Get();
        m_editor     = new Core::GUI::EditorGUI();

        if (m_isCreate) {
            SR_ERROR("Engine::Create() : game engine is already created!");
            return false;
        }

        SR_INFO("Engine::Create() : creating game engine...");

        m_window->SetDrawCallback([this]() {
            DrawCallback();
        });

        m_window->SetResizeCallback([this](const SR_MATH_NS::IVector2& size) {
            ResizeCallback(size);
        });

        if (!m_window->Create()) {
            SR_ERROR("Engine::Create() : failed to create window!");
            return false;
        }

        m_input->Register(&Graphics::GUI::GlobalWidgetManager::Instance());
        m_input->Register(m_editor);
        m_editor->Enable(Helper::Features::Instance().Enabled("EditorOnStartup", false));

        Graphics::Environment::RegisterScrollEvent([](double x, double y){
            SR_UTILS_NS::Input::Instance().SetMouseScroll(x, y);
        });

        if (!m_scene.Valid()) {
            auto&& scenePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Scenes/New scene");
            SetScene(SR_WORLD_NS::Scene::New(scenePath));
        }

        m_isCreate = true;

        return true;
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

        Helper::EventManager::Subscribe([this](SR_UTILS_NS::EventManager::Event event){
            switch (event) {
                case SR_UTILS_NS::EventManager::Event::Exit:
                    m_exitEvent = true;
                    break;
                case SR_UTILS_NS::EventManager::Event::Fatal:
                    SR_ERROR("Engine::(EventManager) : a fatal error event has been detected!");
                    m_exitEvent = true;
                    break;
            }
        });

        if (!m_window->Init()) {
            SR_ERROR("Engine::Init() : failed to initialize window!");
            return false;
        }

        RegisterLibraries();

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

        if (!m_window->Run()) {
            SR_ERROR("Engine::Run() : failed to run window!");
            return false;
        }

        if (!Core::Commands::RegisterEngineCommands()) {
            SR_ERROR("Engine::Run() : errors were detected during the registration of commands!");
            return false;
        }

        if (!m_cmdManager->Run()) {
            SR_ERROR("Engine::Run() : failed to run command manager!");
            return false;
        }

        m_isRun = true;

        if (SR_UTILS_NS::Features::Instance().Enabled("ChunkSystem", true)) {
            SR_INFO("Engine::Run() : running world thread...");

            m_worldThread = SR_HTYPES_NS::Thread::Factory::Instance().Create(&Engine::WorldThread, this);
        }

        return true;
    }

    void Engine::Await() {
        SR_INFO("Engine::Await() : waiting for the engine to close...");

        const float updateFrequency = (1.f / 60.f) * CLOCKS_PER_SEC;
        float accumulator = updateFrequency;
        using clock = std::chrono::high_resolution_clock;
        auto timeStart = clock::now();

        while (m_isRun) {
            SR_HTYPES_NS::Thread::Sleep(1);

            const auto now = clock::now();
            const auto deltaTime = now - timeStart;
            timeStart = now;

            const bool windowFocused = m_window != nullptr && m_window->IsWindowFocus();

            /// fixed update
            if (accumulator >= updateFrequency) {
                SR_UTILS_NS::EventManager::PoolEvents();

                while (accumulator >= updateFrequency) {
                    if (windowFocused) {
                        SR_UTILS_NS::Input::Instance().Check();

                        m_input->Check();

                        if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Ctrl)) {
                            if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::Z))
                                m_cmdManager->Cancel();

                            if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::Y))
                                if (!m_cmdManager->Redo())
                                    SR_WARN("Engine::Await() : failed to redo \"" + m_cmdManager->GetLastCmdName() + "\" command!");
                        }

                        if (m_editor && SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F1)) {
                            m_editor->SetDockingEnabled(!m_editor->IsDockingEnabled());
                        }

                        if (m_editor && SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F2)) {
                            m_editor->Enable(!m_editor->Enabled());
                            m_renderScene.Do([](SR_GRAPH_NS::RenderScene* ptr) {
                                ptr->SetOverlayEnabled(!ptr->IsOverlayEnabled());
                            });
                        }

                        if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F3)) {
                            Reload();
                        }

                        if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::BackSpace) && SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::LShift)) {
                            SR_SYSTEM_LOG("Engine::Await() : The closing key combination have been detected!");
                            m_exitEvent = true;
                            break;
                        }
                    }

                    if (m_editor) {
                        m_editor->Update();
                    }

                    accumulator -= updateFrequency;
                }
            }

            if (m_exitEvent) {
                SR_SYSTEM_LOG("Engine::Await() : the closing event have been received!");
                break;
            }

            accumulator += (float)deltaTime.count() / CLOCKS_PER_SEC / CLOCKS_PER_SEC;
        }

        if (m_editor && m_editor->Enabled()) {
            m_editor->Enable(false);
            SR_SYSTEM_LOG("Engine::Await() : disabling editor gui...");
        }
    }

    bool Engine::Close() {
        SR_INFO("Engine::Close() : closing game engine...");

        m_isRun = false;

        if (m_input) {
            m_input->UnregisterAll();
        }
        SR_SAFE_DELETE_PTR(m_input);

        if (m_scene.Valid()) {
            m_scene->Save();
            SetScene(ScenePtr());
        }

        SR_SAFE_DELETE_PTR(m_editor);

        if (m_cmdManager && m_cmdManager->IsRun())
            m_cmdManager->Close();
        SR_SAFE_DELETE_PTR(m_cmdManager);

        if (m_worldThread) {
            SR_INFO("Engine::Close() : destroying world thread...");
            m_worldThread->TryJoin();
            m_worldThread->Free();
            m_worldThread = nullptr;
        }

        if (m_window && m_window->IsRun()) {
            m_window->Close();
            delete m_window;
            m_window = nullptr;
        }

        if (m_time) {
            SR_INFO("Engine::Close() : destroying time...");
            delete m_time;
            m_time = nullptr;
        }

        return true;
    }

    void Engine::DrawCallback() {
        if (m_renderScene.LockIfValid()) {
            m_renderScene->Render();
            /// В процессе отрисовки сцена могла быть заменена
            m_renderScene.TryUnlock();
        }
    }

    bool Engine::RegisterLibraries() {
        SR_LOG("Engine::RegisterLibraries() : registering all libraries...");

        API::RegisterEvoScriptClasses();

        return true;
    }

    bool Engine::SetScene(const SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene> &scene)  {
        SR_LOCK_GUARD

        /// создаем бекап указателя на сцену,
        /// чтобы проконтролировать, что она корректно уничтожится и не произойдет блокировки
        bool locked = false;
        ScenePtr oldScene = m_scene;
        RenderScenePtr oldRenderScene = m_renderScene;

        if (oldScene.RecursiveLockIfValid())
        {
            m_renderScene.Do([this](SR_GRAPH_NS::RenderScene* ptr) {
                ptr->Remove(m_editor);
                ptr->Remove(&Graphics::GUI::GlobalWidgetManager::Instance());
            });

            oldScene.AutoFree([](SR_WORLD_NS::Scene* scene) {
                scene->Destroy();
                scene->Free();
            });
            locked = true;
        }

        if (scene == oldScene && scene.Valid()) {
            SR_WARN("Engine::SetScene() : scene ptr equals current scene ptr!");
            if (locked) {
                oldScene.Unlock();
            }
            return false;
        }

        if ((m_scene = scene).Valid()) {
            if (auto&& pContext = m_window->GetContext(); pContext.LockIfValid()) {
                m_renderScene.ReplaceAndCopyLock(pContext->CreateScene(m_scene));

                m_renderScene->SetTechnique("Editor/Configs/EditorRenderTechnique.xml");

                m_renderScene->Register(m_editor);
                m_renderScene->Register(&Graphics::GUI::GlobalWidgetManager::Instance());

                m_renderScene->SetOverlayEnabled(m_editor->Enabled());

                pContext.Unlock();
                m_renderScene.Unlock();
                oldRenderScene.RemoveAllLocks();
            }
        }

        if (m_editor) {
            m_editor->GetWindow<Hierarchy>()->SetScene(m_scene);
            m_editor->GetWindow<SceneViewer>()->SetScene(m_scene);
            m_editor->GetWindow<WorldEdit>()->SetScene(m_scene);
        }

        if (locked) {
            oldScene.Unlock();
        }

        return true;
    }

    void Engine::Reload() {
        SR_PLATFORM_NS::SelfOpen();
        SR_UTILS_NS::EventManager::Push(SR_UTILS_NS::EventManager::Event::Exit);
    }

    void Engine::WorldThread() {
        auto timer = Helper::Types::Timer(0.1);

        while (m_isRun) {
            SR_HTYPES_NS::Thread::Sleep(1);

            auto&& pCamera = m_renderScene.Do<CameraPtr>([](SR_GRAPH_NS::RenderScene* ptr) -> CameraPtr {
                if (auto&& pCamera = ptr->GetMainCamera()) {
                    return pCamera;
                }

                return ptr->GetFirstOffScreenCamera();
            }, nullptr);

            if (!pCamera) {
                continue;
            }

            if (timer.Update() && m_scene.LockIfValid()) {
                if (auto &&gameObject = pCamera->GetParent()) {
                    if (gameObject->TryLockIfValid()) {
                        m_scene->SetObserver(gameObject->GetThis());
                        gameObject->Unlock();
                    }
                }

                m_scene->Update(timer.GetDeltaTime());
                m_scene.Unlock();
            }
        }

        SR_SYSTEM_LOG("Engine::WorldThread() : world thread completed!");
    }

    void Engine::ResizeCallback(const SR_MATH_NS::IVector2& size) {
        if (!m_scene.LockIfValid()) {
            return;
        }

        for (auto&& root : m_scene->GetRootGameObjects()) {
            if (root.LockIfValid()) {
                root->OnWindowResized(size);
                root.Unlock();
            }
        }

        m_scene.Unlock();
    }
}