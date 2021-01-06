//
// Created by Nikita on 29.12.2020.
//

#include "../inc/Engine.h"
#include <Input/Input.h>
#include <Types/Time.h>
#include <Input/InputSystem.h>
#include <EntityComponentSystem/Transform.h>

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
        // Debug
        this->m_compiler->RegisterScriptClass("Base", [](lua_State* L){
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

        // String
        this->m_compiler->RegisterScriptClass("Base", [](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<std::string>("String")
                    .addStaticFunction("FromFloat", static_cast<std::string(*)(float)>([](float f) -> std::string {
                        return std::to_string(f);
                    }))
                    .endClass();
        });

        // Time
        this->m_compiler->RegisterScriptClass("Base", [](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Helper::Types::Time>("Time")
                    .addStaticFunction("DeltaTime", static_cast<float(*)()>([]() -> float {
                        return Helper::Types::Time::DeltaTime();
                    }))
                    .endClass();
        });

        // Script
        this->m_compiler->RegisterScriptClass("Base", [](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<lua_State>("LuaState")
                            .addStaticProperty("L", L, false)
                    .endClass()

                    //.addVariable("L", L, false)
                    .beginClass<Scripting::Script>("Script")
                    .addStaticFunction("ImportLib", static_cast<bool(*)(const std::string&, lua_State*)>([](const std::string& name, lua_State* L) -> bool {
                        auto a = Engine::Get()->GetCompiler()->GetClasses(name);
                        if (a.empty())
                            return false;
                        else
                        {
                            Debug::Script("Script(InternalCall) : importing \""+name+"\" library...");
                            for (const auto& b : a)
                                b(L);
                        }
                    }))
                    .endClass();
        });

        // KeyCode and Input
        this->m_compiler->RegisterScriptClass("Base", [](lua_State* L){
            luabridge::getGlobalNamespace(L)
                .beginNamespace("KeyCode")
                    .addFunction("A",       static_cast<int(*)()>([]() -> int { return (int)KeyCode::A;          }))
                    .addFunction("D",       static_cast<int(*)()>([]() -> int { return (int)KeyCode::D;          }))
                    .addFunction("S",       static_cast<int(*)()>([]() -> int { return (int)KeyCode::S;          }))
                    .addFunction("W",       static_cast<int(*)()>([]() -> int { return (int)KeyCode::W;          }))
                    .addFunction("Space",   static_cast<int(*)()>([]() -> int { return (int)KeyCode::Space;      }))
                    .addFunction("LShift",  static_cast<int(*)()>([]() -> int { return (int)KeyCode::LShift;     }))
                .endNamespace();

            luabridge::getGlobalNamespace(L)
                    .beginClass<Helper::InputSystem>("Input")
                        .addStaticFunction("GetKey", static_cast<bool(*)(int)>([](int k) -> bool {
                            return Helper::InputSystem::IsPressed((KeyCode)k);
                        }))
                    .addStaticFunction("GetKeyDown", static_cast<bool(*)(int)>([](int k) -> bool {
                        return Helper::InputSystem::IsDown((KeyCode)k);
                    }))
                    .addStaticFunction("GetKeyUp", static_cast<bool(*)(int)>([](int k) -> bool {
                        return Helper::InputSystem::IsUp((KeyCode)k);
                    }))
                    //.addStaticFunction("MouseDrag", static_cast<glm::vec2(*)()>([]() -> glm::vec2 {
                        //return Helper::InputSystem::
                    //}))
                    .endClass();
        });

        // Vector3
        this->m_compiler->RegisterScriptClass("Math", [](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<glm::vec3>("Vector3")
                            .addStaticFunction("New", static_cast<glm::vec3(*)()>([]() -> glm::vec3 {
                                return glm::vec3();
                            }))
                            .addProperty("x", &glm::vec3::x)
                            .addProperty("y", &glm::vec3::y)
                            .addProperty("z", &glm::vec3::z)

                            .addStaticFunction("Empty", static_cast<bool(*)(glm::vec3)>([](glm::vec3 v) -> bool {
                                return (!v.x && !v.y && !v.z);
                            }))
                            .addStaticFunction("Sum", static_cast<glm::vec3(*)(glm::vec3, glm::vec3)>([](glm::vec3 v1, glm::vec3 v2) -> glm::vec3 {
                                return v1 + v2;
                            }))
                            .addStaticFunction("Sub", static_cast<glm::vec3(*)(glm::vec3, glm::vec3)>([](glm::vec3 v1, glm::vec3 v2) -> glm::vec3 {
                                return v1 - v2;
                            }))
                            .addStaticFunction("FMul", static_cast<glm::vec3(*)(glm::vec3, float)>([](glm::vec3 v1, float f) -> glm::vec3 {
                                return v1 * f;
                            }))
                            .addStaticFunction("FDiv", static_cast<glm::vec3(*)(glm::vec3, float)>([](glm::vec3 v1, float f) -> glm::vec3 {
                                return v1 / f;
                            }))
                    .endClass();
        });

        // Transform
        this->m_compiler->RegisterScriptClass("Math", [](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Helper::Transform>("Transform")
                    .addFunction("Forward", (glm::vec3 (Framework::Helper::Transform::*)(void))&Helper::Transform::Forward)
                    .addFunction("Up", (glm::vec3 (Framework::Helper::Transform::*)(void))&Helper::Transform::Up)
                    .addFunction("Right", (glm::vec3 (Framework::Helper::Transform::*)(void))&Helper::Transform::Right)

                    .addFunction("Translate", (void (Helper::Transform::*)(glm::vec3))&Helper::Transform::Translate)
                    .endClass();
        });

        // Component
        this->m_compiler->RegisterScriptClass("Engine", [](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Helper::Component>("Component")
                    .endClass();
        });

        // GameObject
        this->m_compiler->RegisterScriptClass("Engine", [](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Helper::GameObject>("GameObject")
                    .addFunction("AddComponent", (bool (Framework::Helper::GameObject::*)(Helper::Component*))&Helper::GameObject::AddComponent)
                    .addFunction("GetTransform", (Helper::Transform* (Framework::Helper::GameObject::*)(void))&Helper::GameObject::GetTransform)
                    .endClass();
        });

        // Scene
        this->m_compiler->RegisterScriptClass("Engine", [](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Helper::Scene>("Scene")
                    .addStaticFunction("Get", static_cast<Scene*(*)()>([]() -> Scene* {
                        return Engine::Get()->GetScene();
                    }))
                    .addFunction("Instance", (GameObject* (Framework::Helper::Scene::*)(std::string))&Helper::Scene::Instance)
                    .addFunction("Destroy", (bool (Framework::Helper::Scene::*)(GameObject*))&Helper::Scene::Destroy)
                    .endClass();
        });

        // Mesh
        this->m_compiler->RegisterScriptClass("Graphics", [](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Graphics::Mesh>("Mesh")
                    .addStaticFunction("Load", static_cast<Graphics::Mesh*(*)(std::string name, unsigned int id)>([](std::string name, unsigned int id) -> Graphics::Mesh* {
                        return Mesh::Load(std::move(name))[id];
                    }))
                    .addFunction("Base", (Helper::Component* (Framework::Graphics::Mesh::*)(void))&Graphics::Mesh::BaseComponent)
                    .endClass();
        });

        // Camera
        this->m_compiler->RegisterScriptClass("Graphics", [](lua_State* L){
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

        // Render
        this->m_compiler->RegisterScriptClass("Graphics", [](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Graphics::Render>("Render")
                    .addStaticFunction("Get", static_cast<Graphics::Render*(*)()>([]() -> Graphics::Render* {
                        return Engine::Get()->GetWindow()->GetRender();
                    }))
                    .addFunction("RegisterMesh", (void (Framework::Graphics::Render::*)(Graphics::Mesh*))&Graphics::Render::RegisterMesh)
                    .endClass();
        });

        // Window
        this->m_compiler->RegisterScriptClass("Graphics", [](lua_State* L){
            luabridge::getGlobalNamespace(L)
                    .beginClass<Graphics::Window>("Window")
                        .addStaticFunction("Get", static_cast<Graphics::Window*(*)()>([]() -> Graphics::Window* {
                            return Engine::Get()->GetWindow();
                        }))
                        .addFunction("AddCamera", (void (Framework::Graphics::Window::*)(Graphics::Camera*))&Graphics::Window::AddCamera)
                        .addFunction("RemoveCamera", (void (Framework::Graphics::Window::*)(Graphics::Camera*))&Graphics::Window::RemoveCamera)
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

        glm::vec2 drag = InputSystem::MouseDrag();
        if (drag != glm::vec2(0,0))
            std::cout << glm::to_string(drag) << std::endl;

        if (InputSystem::IsDown(KeyCode::Esc)) {
            Debug::System("Engine::Await() : ESC has been pressed.");
            break;
        }

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
