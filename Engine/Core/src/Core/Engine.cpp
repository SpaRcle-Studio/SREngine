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

#include <Physics/PhysicsScene.h>

#include <Types/Skybox.h>

namespace Framework {
    bool Engine::Create(SR_GRAPH_NS::Window* window) {
        m_window = window;

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

        if (!m_window->Create()) {
            SR_ERROR("Engine::Create() : failed to create window!");
            return false;
        }

        m_input->Register(&Graphics::GUI::GlobalWidgetManager::Instance());
        m_input->Register(m_editor);
        m_editor->Enable(Helper::Features::Instance().Enabled("EditorOnStartup", false));

        Graphics::Environment::RegisterScrollEvent([](double x, double y) {
            SR_UTILS_NS::Input::Instance().SetMouseScroll(x, y);
        });

        if (!m_scene.Valid()) {
            auto&& scenePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Scenes/New scene");
            SetScene(SR_WORLD_NS::Scene::New(scenePath));
        }

        m_updateFrequency = (1.f / (60.f * m_speed)) * CLOCKS_PER_SEC;
        m_accumulator = m_updateFrequency;
        m_timeStart = Clock::now();

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

        Helper::EventManager::Instance().Subscribe([this](const SR_UTILS_NS::EventManager::Event& event){
            switch (event) {
                case SR_UTILS_NS::EventManager::Event::Exit:
                    m_exitEvent = true;
                    break;
                case SR_UTILS_NS::EventManager::Event::FatalError:
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

        while (m_isRun) {
            SR_HTYPES_NS::Thread::Sleep(10);

            if (m_exitEvent) {
                SR_SYSTEM_LOG("Engine::Await() : the closing event have been received!");
                break;
            }
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

        SR_INFO("Engine::Close() : destroying the editor...");
        SR_SAFE_DELETE_PTR(m_editor);

        if (m_cmdManager && m_cmdManager->IsRun()) {
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

        if (m_window && m_window->IsRun()) {
            m_window->Close();
            delete m_window;
            m_window = nullptr;
        }

        return true;
    }

    void Engine::DrawCallback() {
        if (!m_isRun || m_window == nullptr || m_window->IsWindowCollapsed()) {
            m_accumulator = 0.f;
            return;
        }

        SR_HTYPES_NS::Time::Instance().Update();

        if (m_scene.LockIfValid()) {
            const auto now = SR_HTYPES_NS::Time::Instance().Now();
            const auto deltaTime = now - m_timeStart;
            const auto dt = static_cast<float_t>(deltaTime.count()) / CLOCKS_PER_SEC / CLOCKS_PER_SEC;
            m_timeStart = now;

            Prepare();

            Update(dt);

            /// fixed update
            if (m_accumulator >= m_updateFrequency) {
                while (m_accumulator >= m_updateFrequency) {
                    FixedUpdate();
                    m_accumulator -= m_updateFrequency;
                }
            }

            m_accumulator += dt;

            m_scene.Unlock();
        }

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

            oldScene.AutoFree([](SR_WORLD_NS::Scene* pScene) {
                pScene->Destroy();
                delete pScene;
            });

            m_physicsScene.AutoFree([](SR_PHYSICS_NS::PhysicsScene* pPhysicsScene) {
                delete pPhysicsScene;
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

                m_renderScene->SetTechnique("Editor/Configs/OverlayRenderTechnique.xml");

                m_renderScene->Register(m_editor);
                m_renderScene->Register(&Graphics::GUI::GlobalWidgetManager::Instance());

                m_renderScene->SetOverlayEnabled(m_editor->Enabled());

                pContext.Unlock();
                m_renderScene.Unlock();
                oldRenderScene.RemoveAllLocks();
            }

            m_physicsScene = new SR_PHYSICS_NS::PhysicsScene(m_scene);
        }

        if (m_editor) {
            m_editor->GetWindow<Hierarchy>()->SetScene(m_scene);
            m_editor->GetWindow<SceneViewer>()->SetScene(m_scene);
            m_editor->GetWindow<Inspector>()->SetScene(m_scene);
            m_editor->GetWindow<WorldEdit>()->SetScene(m_scene);
        }

        if (locked) {
            oldScene.Unlock();
        }

        return true;
    }

    void Engine::Reload() {
        SR_PLATFORM_NS::SelfOpen();
        m_exitEvent = true;
    }

    void Engine::WorldThread() {
        auto timer = Helper::Types::Timer(0.1);

        while (m_isRun) {
            SR_HTYPES_NS::Thread::Sleep(250);

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
                    if (gameObject->TryRecursiveLockIfValid()) {
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

    void Engine::FixedUpdate() {
        SR_UTILS_NS::Input::Instance().Check();

        m_input->Check();

        bool lShiftPressed = SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::LShift);

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

        if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F3) && lShiftPressed) {
            Reload();
            return;
        }

        for (auto&& pComponent : m_updateableComponents) {
            pComponent->FixedUpdate();
        }

        if (m_editor) {
            m_editor->Update();
        }
    }

    void Engine::Update(float_t dt) {
        if (m_physicsScene.RecursiveLockIfValid()) {
            m_physicsScene->Update(dt);
            m_physicsScene.Unlock();
        }

        for (auto&& pComponent : m_updateableComponents) {
            pComponent->Update(dt);
        }
    }

    void Engine::Prepare() {
        const bool isPaused = !m_isActive || m_isPaused;
        auto&& root = m_scene->GetRootGameObjects();

        uint64_t rootHash = 0;

        for (auto&& gameObject : root) {
            rootHash = SR_UTILS_NS::HashCombine(gameObject.GetRawPtr(), rootHash);
            gameObject->Awake(isPaused);
        }

        for (auto&& gameObject : root) {
            gameObject->CheckActivity();
        }

        for (auto&& gameObject : root) {
            gameObject->Start();
        }

        /// WARNING: если произойдет коллизия хешей при уничтожении коренного объекта, то будет краш!
        if (rootHash == m_rootHash) {
            for (auto&& gameObject : root) {
                if ((m_needRebuildComponents |= gameObject->IsDirty())) {
                    break;
                }
            }
        }
        else {
            m_needRebuildComponents = true;
            m_rootHash = rootHash;
        }

        if (m_needRebuildComponents) {
            size_t capacity = m_updateableComponents.capacity();
            m_updateableComponents.clear();
            m_updateableComponents.reserve(capacity);

            SR_HTYPES_NS::Function<void(const SR_UTILS_NS::GameObject::Ptr& ptr)> function;

            function = [&](const SR_UTILS_NS::GameObject::Ptr& ptr) {
                for (auto&& pComponent : ptr->GetComponents()) {
                    if (isPaused && !pComponent->ExecuteInEditMode()) {
                        continue;
                    }

                    if (pComponent->IsCanUpdate()) {
                        m_updateableComponents.emplace_back(pComponent);
                    }

                    for (auto&& children : ptr->GetChildrenRef()) {
                        function(children);
                    }
                }
            };

            for (auto&& gameObject : root) {
                function(gameObject);
                gameObject->SetDirty(false);
            }

            m_needRebuildComponents = false;
        }
    }

    void Engine::SetActive(bool isActive) {
        m_isActive = isActive;
        m_needRebuildComponents = true;
    }

    void Engine::SetSpeed(float_t speed) {
        m_speed = speed;
    }

    void Engine::SetPaused(bool isPaused) {
        m_isPaused = isPaused;
        m_needRebuildComponents = true;
    }
}