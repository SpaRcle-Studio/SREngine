//
// Created by Nikita on 29.12.2020.
//

#include "../inc/Engine.h"
#include <Input/Input.h>
#include <Types/Time.h>
#include <Input/InputSystem.h>
#include <EntityComponentSystem/Transform.h>
#include <Environment/Environment.h>
#include <GUI/ICanvas.h>

#include <utility>
#include <GUI/Canvas.h>
#include <Events/EventManager.h>
#include <API.h>

Framework::Engine::Engine() {
    this->m_compiler = new Scripting::Compiler();
}

Framework::Engine::~Engine() = default;

bool Framework::Engine::Create(Graphics::Window* window, Helper::Scene* scene, Physics::PhysEngine* physics) {
    this->m_window = window;
    this->m_render = window->GetRender();

    this->m_physics = physics;

    this->m_time = new Helper::Types::Time();

    if (m_isCreate){
        Helper::Debug::Error("Engine::Create() : game engine already create!");
        return false;
    }

    Helper::Debug::Info("Engine::Create() : creating game engine...");

    if (!this->m_window->Create()){
        Helper::Debug::Error("Engine::Create() : failed create window!");
        return false;
    }

    if (!m_physics->Create()) {
        Helper::Debug::Error("Engine::Create() : failed create physics engine!");
        return false;
    }

    Graphics::Environment::RegisterScrollEvent([](double x, double y){
        InputSystem::SetMouseScroll(x, y);
    });

    this->m_scene = scene;

    this->m_isCreate = true;

    return true;
}

bool Framework::Engine::Init(Graphics::Camera* scene_camera) {
    if (!m_isCreate) {
        Debug::Error("Engine::Init() : engine is not create!");
        return false;
    }

    if (m_isInit) {
        Debug::Error("Engine::Init() : engine already initialize!");
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

    if (!this->m_window->Init()) {
        Helper::Debug::Error("Engine::Init() : failed initialize window!");
        return false;
    } else {
        if (scene_camera) {
            m_window->AddCamera(scene_camera);

            GameObject *camera = m_scene->Instance("SceneCamera");
            camera->AddComponent(scene_camera);
        }
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
        Helper::Debug::Error("Engine::Run() : failed ran window!");
        return false;
    }

    this->m_isRun = true;

    return true;
}

void Framework::Engine::Await() {
    Debug::Info("Engine::Await() : load engine script...");

    Scripting::Script* engine = nullptr;

    if (Graphics::Environment::Get()->GetPipeLine() == Graphics::Environment::PipeLine::OpenGL)
        engine = m_compiler->Load("engine", true);
    else
        engine = m_compiler->Load("simpleEngine", true);

    Debug::Info("Engine::Await() : wait close engine...");

    while (m_window->IsWindowOpen()) {
        EventManager::PoolEvents();
        if (m_exitEvent) {
            Debug::System("The closing event was received!");
            break;
        }

        m_compiler->PoolEvents();

        Helper::InputSystem::Check();

        if (m_time->Begin()){
            m_compiler->FixedUpdateAll();

            m_time->End();
        }

        m_compiler->UpdateAll();
    }

    engine->Close();
    engine->Destroy();

    m_compiler->PoolEvents();
}

bool Framework::Engine::Close() {
    Helper::Debug::Info("Engine::Close() : close game engine...");

    this->m_compiler->CloseAll();
    this->m_compiler->DestroyAll();

    this->m_compiler->PoolEvents();

    if (m_window->IsRun()) {
        this->m_window->Close();
        this->m_window->Free();
    }

    this->m_compiler->PoolEvents();
    this->m_compiler->Free();
    //Helper::Debug::Info("Engine::Close() : free compiler pointer...");
    //delete m_compiler;

    if (m_time)
        delete m_time;

    return false;
}

bool Framework::Engine::RegisterLibraries() {
    Helper::Debug::Log("Engine::RegisterLibraries() : register all lua libraries...");

    API::Register(m_compiler);

    return true;
}
