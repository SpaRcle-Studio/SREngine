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

#include <Render/Render.h>
#include <Render/CameraManager.h>
#include <Window/Window.h>

#include <Types/Skybox.h>

bool Framework::Engine::Create(SR_GRAPH_NS::Window* window, Physics::PhysEngine* physics) {
    m_window = window;
    m_render = window->GetRender();

    m_physics = physics;

    m_time       = new Helper::Types::Time();
    m_cmdManager = new Helper::CmdManager();
    m_input      = new Helper::InputDispatcher();

    if (m_isCreate) {
        SR_ERROR("Engine::Create() : game engine is already created!");
        return false;
    }

    SR_INFO("Engine::Create() : creating game engine...");

    if (!m_window->Create()) {
        SR_ERROR("Engine::Create() : failed to create window!");
        return false;
    }

    window->RegisterWidgetManager(&Graphics::GUI::GlobalWidgetManager::Instance());
    window->RegisterWidgetManager(m_editor = new Core::GUI::EditorGUI());

    m_input->Register(&Graphics::GUI::GlobalWidgetManager::Instance());
    m_input->Register(m_editor);

    m_editor->Enable(Helper::Features::Instance().Enabled("EditorOnStartup", false));

    if (!m_physics->Create()) {
        SR_ERROR("Engine::Create() : failed to create physics engine!");
        return false;
    }

    Graphics::Environment::RegisterScrollEvent([](double x, double y){
        SR_UTILS_NS::Input::Instance().SetMouseScroll(x, y);
    });

    if (!m_scene.Valid()) {
        auto&& scenePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Scenes/New scene");
        SetScene(SR_WORLD_NS::Scene::New(scenePath));
    }

    /// TODO: move to camera
    if (SR_UTILS_NS::Features::Instance().Enabled("LoadSkybox")) {
        if (!m_window->GetRender()->GetSkybox()) {
            m_window->GetRender()->SetSkybox(SR_GTYPES_NS::Skybox::Load("Sea.jpg"));
        }
    }

    m_isCreate = true;

    return true;
}

bool Framework::Engine::Init() {
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

bool Framework::Engine::Run() {
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

    if (Helper::Features::Instance().Enabled("ChunkSystem")) {
        SR_INFO("Engine::Run() : running world thread...");

        m_worldThread = SR_HTYPES_NS::Thread::Factory::Instance().Create([this]() {
            auto timer = Helper::Types::Timer(0.1);

            while (m_isRun) {
                SR_HTYPES_NS::Thread::Sleep(1);

                if (timer.Update() && m_scene.LockIfValid()) {
                    m_scene->Update(timer.GetDeltaTime());
                    m_scene.Unlock();
                }
            }
        });
    }

    return true;
}

void Framework::Engine::Await() {
    SR_INFO("Engine::Await() : waiting for the engine to close...");

    const float updateFrequency = (1.f / 60.f) * CLOCKS_PER_SEC;
    float accumulator = updateFrequency;
    using clock = std::chrono::high_resolution_clock;
    auto timeStart = clock::now();
    const bool needUpdateScripts = SR_UTILS_NS::Features::Instance().Enabled("UpdateScripts", true);

    while (m_isRun) {
        SR_HTYPES_NS::Thread::Sleep(1);

        SR_GRAPH_NS::CameraManager::Instance().Update();

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

                    if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F1)) {
                        m_editor->SetDockingEnabled(!m_editor->IsDockingEnabled());
                    }

                    if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F2)) {
                        m_editor->Enable(!m_editor->Enabled());
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

                m_editor->Update();

                accumulator -= updateFrequency;
            }
        }

        if (m_exitEvent) {
            SR_SYSTEM_LOG("Engine::Await() : the closing event have been received!");
            break;
        }

        accumulator += (float)deltaTime.count() / CLOCKS_PER_SEC / CLOCKS_PER_SEC;
    }

    if (m_editor->Enabled()) {
        m_editor->Enable(false);
        SR_SYSTEM_LOG("Engine::Await() : disabling editor gui...");
    }
}

bool Framework::Engine::Close() {
    SR_INFO("Engine::Close() : closing game engine...");

    m_isRun = false;

    if (m_editor && m_window) {
        m_window->RemoveWidgetManager(m_editor);
        m_editor->Destroy();
        m_editor->Free();
        m_editor = nullptr;
    }

    if (m_scene.Valid()) {
        m_scene->Save();
        SetScene(ScenePtr());
    }

    if (m_input) {
        m_input->UnregisterAll();
    }
    SR_SAFE_DELETE_PTR(m_input);

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
        m_window->RemoveWidgetManager(&Graphics::GUI::GlobalWidgetManager::Instance());
        m_window->Close();
        m_window->Free();
        m_window = nullptr;
    }

    if (m_time) {
        SR_INFO("Engine::Close() : destroying time...");
        delete m_time;
        m_time = nullptr;
    }

    return true;
}

bool Framework::Engine::RegisterLibraries() {
    SR_LOG("Engine::RegisterLibraries() : registering all libraries...");

    API::RegisterEvoScriptClasses();

    return true;
}

bool Framework::Engine::SetScene(const Helper::Types::SafePtr<SR_WORLD_NS::Scene> &scene)  {
    SR_LOCK_GUARD

    /// создаем бекап указателя на сцену,
    /// чтобы проконтролировать, что она корректно уничтожится и не произойдет блокировки
    bool locked = false;
    ScenePtr oldScene = m_scene;

    if (oldScene.RecursiveLockIfValid())
    {
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

    m_scene = scene;

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

void Framework::Engine::Reload() {
    SR_PLATFORM_NS::SelfOpen();
    SR_UTILS_NS::EventManager::Push(SR_UTILS_NS::EventManager::Event::Exit);
}
