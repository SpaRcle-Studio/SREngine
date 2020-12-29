//
// Created by Nikita on 29.12.2020.
//

#include "../inc/Engine.h"
#include <Input/Input.h>
#include <Types/Time.h>
#include <Input/InputSystem.h>

Framework::Engine::Engine() {
    this->m_compiler = new Scripting::Compiler();
}

Framework::Engine::~Engine() {
    delete m_compiler;
}

bool Framework::Engine::Create(Graphics::Window* window, Helper::Scene* scene) {
    this->m_window = window;
    this->m_render = window->GetRender();

    if (m_isCreate){
        Helper::Debug::Error("Engine::Create() : game engine already create!");
        return false;
    }

    Helper::Debug::Info("Engine::Create() : creating game engine...");

    if (!this->m_window->Create()){
        Helper::Debug::Error("Engine::Create() : failed create window!");
        return false;
    }

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

    if (!this->m_window->Init()){
        Helper::Debug::Error("Engine::Init() : failed initialize window!");
        return false;
    } else {
        if (scene_camera) {
            m_window->AddCamera(scene_camera);

            GameObject *camera = m_scene->Instance("SceneCamera");
            camera->AddComponent(scene_camera);
        }
    }

    {
        this->m_compiler->RegisterScriptClass([](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Debug>("Debug")
                        .addStaticFunction("Log", static_cast<void(*)(std::string)>([](std::string s) {
                            Debug::ScriptLog(s);
                        }))
                        .addStaticFunction("Error", static_cast<void(*)(std::string)>([](std::string s) {
                            Debug::ScriptError(s);
                        }))
                    .endClass();
        });

        this->m_compiler->RegisterScriptClass([](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<std::string>("String")
                    .addStaticFunction("FromFloat", static_cast<std::string(*)(float)>([](float f) -> std::string {
                        return std::to_string(f);
                    }))
                    .endClass();
        });

        this->m_compiler->RegisterScriptClass([](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Helper::Types::Time>("Time")
                    .addStaticFunction("DeltaTime", static_cast<float(*)()>([]() -> float {
                        return Helper::Types::Time::DeltaTime();
                    }))
                    .endClass();
        });

        this->m_compiler->RegisterScriptClass([](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Helper::Component>("Component")
                    .endClass();
        });

        this->m_compiler->RegisterScriptClass([](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Graphics::Camera>("Camera")
                        .addStaticFunction("New", static_cast<Graphics::Camera*(*)()>([]() -> Graphics::Camera* {
                            return new Graphics::Camera();
                        }))
                        .addFunction("Free", (bool (Framework::Graphics::Camera::*)(void))&Graphics::Camera::Free)
                        .addFunction("Base", (Helper::Component* (Framework::Graphics::Camera::*)(void))&Graphics::Camera::BaseComponent)
                        .addFunction("SetFrameSize", (void (Framework::Graphics::Camera::*)(unsigned int w, unsigned int h))&Graphics::Camera::UpdateProjection)
                    .endClass();
        });

        this->m_compiler->RegisterScriptClass([](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Graphics::Window>("Window")
                        .addStaticFunction("Get", static_cast<Graphics::Window*(*)()>([]() -> Graphics::Window* {
                            return Engine::Get()->GetWindow();
                        }))
                        .addFunction("AddCamera", (void (Framework::Graphics::Window::*)(Graphics::Camera*))&Graphics::Window::AddCamera)
                        .addFunction("RemoveCamera", (void (Framework::Graphics::Window::*)(Graphics::Camera*))&Graphics::Window::RemoveCamera)
                    .endClass();
        });

        this->m_compiler->RegisterScriptClass([](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Helper::GameObject>("GameObject")
                            .addFunction("AddComponent", (bool (Framework::Helper::GameObject::*)(Helper::Component*))&Helper::GameObject::AddComponent)
                    .endClass();
        });

        this->m_compiler->RegisterScriptClass([](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Helper::Scene>("Scene")
                        .addStaticFunction("Get", static_cast<Scene*(*)()>([]() -> Scene* {
                            return Engine::Get()->GetScene();
                        }))
                        .addFunction("Instance", (GameObject* (Framework::Helper::Scene::*)(std::string))&Helper::Scene::Instance)
                        .addFunction("Destroy", (bool (Framework::Helper::Scene::*)(GameObject*))&Helper::Scene::Destroy)
                    .endClass();
        });
    }

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
    Graphics::Types::Skybox* skybox = Graphics::Types::Skybox::Load("Sea.jpg");
    m_render->SetSkybox(skybox);

    //Mesh *mesh = Mesh::Load("cube.obj")[0];
    //mesh->OnMove({0,0,5});
    //m_render->RegisterMesh(mesh);

    m_compiler->Load("engine", true);

    while (true) {
        Helper::InputSystem::Check();

        if (InputSystem::IsDown(KeyCode::Esc)) {
            Debug::System("Engine::Await() : ESC has been pressed.");
            break;
        }

        if (InputSystem::IsDown(KeyCode::K))
            Debug::Log("Down");

        if (InputSystem::IsUp(KeyCode::K))
            Debug::Log("Up");

        if (Helper::Types::Time::Begin()){
            m_compiler->FixedUpdateAll();

            Helper::Types::Time::End();
        }

        m_compiler->UpdateAll();
    }
}

bool Framework::Engine::Close() {
    if (m_window->IsRun()) {
        this->m_window->Close();
        this->m_window->Free();
    }

    return false;
}
