//
// Created by Nikita on 29.12.2020.
//

#include <Engine.h>
#include <Types/Time.h>
#include <Types/Timer.h>
#include <Input/InputSystem.h>
#include <EntityComponentSystem/Transform.h>
#include <Environment/Environment.h>
#include <GUI/EditorGUI.h>
#include <Events/EventManager.h>
#include <Utils/Features.h>

#include <Render/Render.h>
#include <Window/Window.h>

#include <World/Scene.h>

#include <utility>
#include <chrono>

Framework::Engine::Engine() = default;
Framework::Engine::~Engine() = default;

bool Framework::Engine::Create(SR_GRAPH_NS::Window* window, Physics::PhysEngine* physics) {
    this->m_window = window;
    this->m_render = window->GetRender();

    this->m_physics = physics;

    this->m_time       = new Helper::Types::Time();
    this->m_compiler   = new Scripting::EvoCompiler();
    this->m_cmdManager = new Helper::CmdManager();

    if (m_isCreate){
        Helper::Debug::Error("Engine::Create() : game engine already create!");
        return false;
    }

    Helper::Debug::Info("Engine::Create() : creating game engine...");

    if (!this->m_window->Create()){
        Helper::Debug::Error("Engine::Create() : failed create window!");
        return false;
    }

    m_window->SetCanvas(m_editor = new Core::GUI::EditorGUI(m_compiler));

    if (!m_physics->Create()) {
        Helper::Debug::Error("Engine::Create() : failed create physics engine!");
        return false;
    }

    Graphics::Environment::RegisterScrollEvent([](double x, double y){
        Input::SetMouseScroll(x, y);
    });

    this->m_isCreate = true;

    return true;
}

bool Framework::Engine::Init(Engine::MainScriptType mainScriptType) {
    if (!m_isCreate) {
        Debug::Error("Engine::Init() : engine is not create!");
        return false;
    }

    if (m_isInit) {
        Debug::Error("Engine::Init() : engine is already initialize!");
        return false;
    }

    Helper::Debug::Info("Engine::Init() : initializing game engine...");

    Helper::EventManager::Subscribe([this](EventManager::Event event){
        switch (event) {
            case EventManager::Event::Exit:
                this->m_exitEvent = true;
                break;
            case EventManager::Event::Fatal:
                Debug::Error("Engine::(EventManager) : a fatal error event has been detected!");
                this->m_exitEvent = true;
                break;
        }
    });

    m_scriptType = mainScriptType;

    if (!m_compiler || !m_compiler->Init()) {
        Helper::Debug::Error("Engine::Init() : failed to initialize compiler!");
        return false;
    }

    if (!this->m_window->Init()) {
        Helper::Debug::Error("Engine::Init() : failed to initialize window!");
        return false;
    }

    this->RegisterLibraries();

    this->m_isInit = true;

    return true;
}

bool Framework::Engine::Run() {
    if (!m_isInit) {
        Debug::Error("Engine::Run() : engine is not initialize!");
        return false;
    }

    if (m_isRun) {
        Debug::Error("Engine::Run() : engine already ran!");
        return false;
    }

    Helper::Debug::Info("Engine::Run() : running game engine...");

    if (!this->m_window->Run()){
        Helper::Debug::Error("Engine::Run() : failed to ran window!");
        return false;
    }

    if (!this->LoadMainScript()) {
        Helper::Debug::Error("Engine::Run() : failed to load main script!");
        return false;
    }

    if (!Core::Commands::RegisterEngineCommands()) {
        Helper::Debug::Error("Engine::Run() : errors were detected during the registration of commands!");
        return false;
    }

    if (!m_cmdManager->Run()) {
        Helper::Debug::Error("Engine::Run() : failed to ran command manager!");
        return false;
    }

    Helper::Debug::Info("Engine::Run() : running world thread...");

    if (Helper::Features::Instance().Enabled("ChunkSystem")) {
        m_worldThread = new Helper::Types::Thread([this]() {
            auto timer = Helper::Types::Timer(1.0);

            while (m_isRun) {
                if (timer.Update() && m_scene.LockIfValid()) {
                    m_scene->Update(timer.GetDeltaTime());
                    m_scene.Unlock();
                }
            }
        });
    }

    this->m_isRun = true;

    return true;
}

void Framework::Engine::Await() {
    Debug::Info("Engine::Await() : wait close engine...");

    const float updateFrequency = (1.f / 60.f) * CLOCKS_PER_SEC;
    float accumulator = updateFrequency;
    using clock = std::chrono::high_resolution_clock;
    auto timeStart = clock::now();

    while (m_isRun) {
        auto deltaTime = clock::now() - timeStart;
        timeStart = clock::now();

        EventManager::PoolEvents();
        m_compiler->PollEvents();

        /// fixed update
        if (accumulator >= updateFrequency) {
            while (accumulator >= updateFrequency) {
                Helper::Input::Check();

                if (Input::GetKey(KeyCode::BackSpace) && Input::GetKeyDown(KeyCode::LShift)) {
                    Debug::System("Engine::Await() : The closing key combination have been detected!");
                    m_exitEvent = true;
                    break;
                }

                m_compiler->FixedUpdateAll();
                accumulator -= updateFrequency;
            }
        }

        if (m_exitEvent) {
            Debug::System("Engine::Await() : The closing event have been received!");
            break;
        }

        m_compiler->UpdateAll();

        accumulator += (float)deltaTime.count() / CLOCKS_PER_SEC / CLOCKS_PER_SEC;
    }

    if (m_window->IsGUIEnabled()) {
        m_window->SetGUIEnabled(false);
        Helper::Debug::System("Engine::Await() : disable editor gui...");
    }

    Helper::Debug::System("Engine::Await() : Stopping main engine script...");

    m_mainScript->Close();
    m_mainScript->DelayedDestroyAndFree();
}

bool Framework::Engine::Close() {
    Helper::Debug::Info("Engine::Close() : close game engine...");

    m_isRun = false;

    if (m_cmdManager) {
        m_cmdManager->Close();
        delete m_cmdManager;
        m_cmdManager = nullptr;
    }

    if (m_window && m_window->IsRun()) {
        m_window->Close();
        m_window->Free();
        m_window = nullptr;
    }

    if (m_editor) {
        m_editor->Destroy();
        m_editor->Free();
        m_editor = nullptr;
    }

    if (m_compiler) {
        this->m_compiler->PollEvents();
        Helper::Debug::Info("Engine::Close() : destroy compiler...");
        m_compiler->Destroy();
        m_compiler->Free();
        m_compiler = nullptr;
    }

    if (m_time) {
        Helper::Debug::Info("Engine::Close() : destroy time...");
        delete m_time;
        m_time = nullptr;
    }

    if (m_worldThread) {
        Helper::Debug::Info("Engine::Close() : destroy world thread...");
        m_worldThread->TryJoin();
        delete m_worldThread;
    }

    return true;
}

bool Framework::Engine::RegisterLibraries() {
    Helper::Debug::Log("Engine::RegisterLibraries() : register all libraries...");

    API::RegisterEvoScriptClasses(dynamic_cast<Scripting::EvoCompiler*>(m_compiler));

    return true;
}

bool Framework::Engine::LoadMainScript() {
    Debug::Info("Engine::LoadMainScript() : loading the main engine script...");

    std::string scriptName;
    switch (m_scriptType) {
        case MainScriptType::Engine:    scriptName = "Engine/Engine"; break;
        case MainScriptType::Benchmark: scriptName = "Engine/Benchmark"; break;
        case MainScriptType::Game:
        case MainScriptType::None:
        default:
            Helper::Debug::Error("Engine::LoadMainScript() : unknown script type!");
            return false;
    }

    m_mainScript = Scripting::Script::Allocate(
            "SpaRcle Engine", scriptName, m_compiler,
            Scripting::ScriptType::EvoScript);

    if (!m_mainScript->Compile()) {
        Helper::Debug::Error("Engine::LoadMainScript() : failed to load main engine script!");
        return false;
    } else
        return true;
}

bool Framework::Engine::CloseScene() {
    return m_scene.AutoFree([](World::Scene* scene) {
        scene->Destroy();
        scene->Free();
    });
}

bool Framework::Engine::SetScene(const Helper::Types::SafePtr<World::Scene> &scene)  {
    // TODO: add thread security!
    if (m_scene.Valid() && scene == m_scene) {
        Helper::Debug::Warn("Engine::SetScene() : scene ptr equals current scene ptr!");
        return false;
    } else {
        this->m_scene = scene;
        return true;
    }
}

void Framework::Engine::Reload() {
    Helper::FileSystem::Reload();
    EventManager::Push(EventManager::Event::Exit);
}
