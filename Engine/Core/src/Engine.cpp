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

Framework::Engine::Engine() {
    this->m_compiler = new Scripting::Compiler();
}

Framework::Engine::~Engine() {

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
    Scripting::Script* engine = m_compiler->Load("engine", true);

    while (m_window->IsWindowOpen()) {
        m_compiler->PoolEvents();

        Helper::InputSystem::Check();

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

    return false;
}

bool Framework::Engine::RegisterLibraries() {
    Helper::Debug::Log("Engine::RegisterLibraries() : register all lua libraries...");

    // Debug
    this->m_compiler->RegisterScriptClass("Base", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Debug>("Debug")
                    .addStaticFunction("Log", static_cast<void(*)(std::string)>([](std::string s) {
                        Debug::ScriptLog(std::move(s));
                    }))
                    .addStaticFunction("Error", static_cast<void(*)(std::string)>([](std::string s) {
                        Debug::ScriptError(std::move(s));
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
                    .addStaticFunction("DeltaTime", static_cast<double (*)()>([]() -> double {
                        return Helper::Types::Time::DeltaTime();
                    }))
                .endClass();
    });

    // KeyCode and Input
    this->m_compiler->RegisterScriptClass("Base", [](lua_State* L) {
        static int MouseMiddle      = (int)KeyCode::MouseMiddle;
        static int MouseLeft        = (int)KeyCode::MouseLeft;
        static int MouseRight       = (int)KeyCode::MouseRight;
        static int A                = (int)KeyCode::A;
        static int D                = (int)KeyCode::D;
        static int S                = (int)KeyCode::S;
        static int W                = (int)KeyCode::W;
        static int P                = (int)KeyCode::P;
        static int Space            = (int)KeyCode::Space;
        static int LShift           = (int)KeyCode::LShift;

        luabridge::getGlobalNamespace(L)
                .beginNamespace("KeyCode")
                    .addProperty("MouseMiddle",     &MouseMiddle,         false)
                    .addProperty("MouseLeft",       &MouseLeft,           false)
                    .addProperty("MouseRight",      &MouseRight,          false)
                    .addProperty("A",               &A,                   false)
                    .addProperty("D",               &D,                   false)
                    .addProperty("S",               &S,                   false)
                    .addProperty("W",               &W,                   false)
                    .addProperty("P",               &P,                   false)
                    .addProperty("Space",           &Space,               false)
                    .addProperty("LShift",          &LShift,              false)
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
                    .addStaticFunction("GetMouseDrag", static_cast<glm::vec2(*)()>([]() -> glm::vec2 {
                        return Helper::InputSystem::MouseDrag();
                    }))
                    .addStaticFunction("GetMouseWheel", static_cast<int(*)()>([]() -> int {
                        return Helper::InputSystem::GetMouseWheel();
                    }))
                .endClass();
    });

    // Vector3
    this->m_compiler->RegisterScriptClass("Math", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<glm::vec3>("Vector3")
                    .addStaticFunction("New", static_cast<glm::vec3(*)(float,float,float)>([](float x,float y,float z) -> glm::vec3 {
                        return glm::vec3(x,y,z);
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

    // Vector2
    this->m_compiler->RegisterScriptClass("Math", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<glm::vec2>("Vector2")
                    .addStaticFunction("New", static_cast<glm::vec2(*)(float, float)>([](float x, float y) -> glm::vec2 {
                        return glm::vec2(x, y);
                    }))
                    .addProperty("x", &glm::vec2::x)
                    .addProperty("y", &glm::vec2::y)

                    .addStaticFunction("Empty", static_cast<bool(*)(glm::vec2)>([](glm::vec2 v) -> bool {
                        return (!v.x && !v.y);
                    }))
                    .addStaticFunction("Sum", static_cast<glm::vec2(*)(glm::vec2, glm::vec2)>([](glm::vec2 v1, glm::vec2 v2) -> glm::vec2 {
                        return v1 + v2;
                    }))
                    .addStaticFunction("Sub", static_cast<glm::vec2(*)(glm::vec2, glm::vec2)>([](glm::vec2 v1, glm::vec2 v2) -> glm::vec2 {
                        return v1 - v2;
                    }))
                    .addStaticFunction("FMul", static_cast<glm::vec2(*)(glm::vec2, float)>([](glm::vec2 v1, float f) -> glm::vec2 {
                        return v1 * f;
                    }))
                    .addStaticFunction("FDiv", static_cast<glm::vec2(*)(glm::vec2, float)>([](glm::vec2 v1, float f) -> glm::vec2 {
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
                    .addFunction("Rotate",    (void (Helper::Transform::*)(glm::vec3))&Helper::Transform::Rotate)
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
                    .addFunction("DestroyGM", (bool (Framework::Helper::Scene::*)(GameObject*))&Helper::Scene::DestroyGameObject)
                    .addFunction("Destroy", (bool (Framework::Helper::Scene::*)(void))&Helper::Scene::Destroy)
                .endClass();
    });

    // Material
    this->m_compiler->RegisterScriptClass("Graphics", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::Material>("Material")
                    .addFunction("SetDiffuse", (void (Framework::Graphics::Material::*)(Graphics::Texture*))&Graphics::Material::SetDiffuse)
                    .addFunction("SetBloom", (void (Framework::Graphics::Material::*)(bool value))&Graphics::Material::SetBloom)
                    .addFunction("SetColor", (void (Framework::Graphics::Material::*)(glm::vec3))&Graphics::Material::SetColor)
                .endClass();
    });

    // Mesh
    this->m_compiler->RegisterScriptClass("Graphics", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::Mesh>("Mesh")
                    .addStaticFunction("Load", static_cast<Graphics::Mesh*(*)(std::string name, unsigned int id)>([](std::string name, unsigned int id) -> Graphics::Mesh* {
                        auto meshes = Mesh::Load(name);
                        if (id >= meshes.size()) {
                            Debug::ScriptError("Script(InternalError) : An error occurred while loading the \""+name+"\" model: \n\tIndex went out of model size. "+
                                               std::to_string(id) + " >= "+std::to_string(meshes.size()));
                            return nullptr;
                        }
                        return meshes[id];
                    }))
                    .addFunction("Base", (Helper::Component* (Framework::Graphics::Mesh::*)(void))&Graphics::Mesh::BaseComponent)
                    .addFunction("GetMaterial", (Graphics::Material* (Framework::Graphics::Mesh::*)(void))&Graphics::Mesh::GetMaterial)
                .endClass();
    });

    // PostProcessing
    this->m_compiler->RegisterScriptClass("Graphics", [](lua_State* L) {
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::PostProcessing>("PostProcessing")
                    .addFunction("SetBloomIntensity", (void (Framework::Graphics::PostProcessing::*)(float))&Graphics::PostProcessing::SetBloomIntensity)
                    .addFunction("SetBloomAmount", (void (Framework::Graphics::PostProcessing::*)(int))&Graphics::PostProcessing::SetBloomAmount)
                    .addFunction("SetBloom", (void (Framework::Graphics::PostProcessing::*)(bool))&Graphics::PostProcessing::SetBloom)
                    .addFunction("SetGamma", (void (Framework::Graphics::PostProcessing::*)(float))&Graphics::PostProcessing::SetGamma)
                    .addFunction("SetExposure", (void (Framework::Graphics::PostProcessing::*)(float))&Graphics::PostProcessing::SetExposure)
                    .addFunction("GetFinallyTexID", (unsigned int (Framework::Graphics::PostProcessing::*)(void))&Graphics::PostProcessing::GetFinally)
                    .addFunction("GetColoredImage", (unsigned int (Framework::Graphics::PostProcessing::*)(void))&Graphics::PostProcessing::GetColoredImage)
                    .addFunction("GetBloomMask", (unsigned int (Framework::Graphics::PostProcessing::*)(void))&Graphics::PostProcessing::GetBloomMask)
                .endClass();
    });

    // Camera
    this->m_compiler->RegisterScriptClass("Graphics", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::Camera>("Camera")
                    .addStaticFunction("New", static_cast<Graphics::Camera*(*)()>([]() -> Graphics::Camera* {
                        return new Graphics::Camera();
                    }))
                    .addFunction("GetPostProcessing", (Graphics::PostProcessing* (Framework::Graphics::Camera::*)(void))&Graphics::Camera::GetPostProcessing)
                    //.addFunction("Free", (bool (Framework::Graphics::Camera::*)(void))&Graphics::Camera::Free)
                    .addFunction("Base", (Helper::Component* (Framework::Graphics::Camera::*)(void))&Graphics::Camera::BaseComponent)
                    .addFunction("SetFrameSize", (void (Framework::Graphics::Camera::*)(unsigned int w, unsigned int h))&Graphics::Camera::UpdateProjection)
                    .addFunction("SetDirectOutput", (void (Framework::Graphics::Camera::*)(bool value))&Graphics::Camera::SetDirectOutput)
                    .addFunction("IsDirectOutput", (bool (Framework::Graphics::Camera::*)(void))&Graphics::Camera::IsDirectOutput)
                    .addFunction("GetSize", (glm::vec2 (Framework::Graphics::Camera::*)(void))&Graphics::Camera::GetSize)
                .endClass();
        Scripting::Script::RegisterCasting<Graphics::Camera*>("Camera", L);
    });

    // Texture & TextureFilter & TextureType
    this->m_compiler->RegisterScriptClass("Graphics", [](lua_State* L) {
        static int texTypeDiff      = (int)Graphics::TextureType::Diffuse;
        static int texTypeNorm      = (int)Graphics::TextureType::Normal;
        static int texTypeSpec      = (int)Graphics::TextureType::Specular;
        static int texTypeGlos      = (int)Graphics::TextureType::Glossiness;
        static int texTypeRoug      = (int)Graphics::TextureType::Roughness;

        static int texFilterNear    = (int)Graphics::TextureFilter::NEAREST;
        static int texFilterLine    = (int)Graphics::TextureFilter::LINEAR;

        luabridge::getGlobalNamespace(L)
                .beginNamespace("TextureType")
                    .addProperty("Diffuse",     &texTypeDiff)
                    .addProperty("Normal",      &texTypeNorm)
                    .addProperty("Specular",    &texTypeSpec)
                    .addProperty("Glossiness",  &texTypeGlos)
                    .addProperty("Roughness",   &texTypeRoug)
                .endNamespace()

                .beginNamespace("TextureFilter")
                    .addProperty("NEAREST",     &texFilterNear)
                    .addProperty("LINEAR",      &texFilterLine)
                .endNamespace()

                .beginClass<Graphics::Texture>("Texture")
                    .addStaticFunction("Load", static_cast<Graphics::Texture*(*)(std::string, bool, int, int)>([](std::string name, bool autoRemove, int type, int filter) -> Graphics::Texture* {
                        return Texture::Load(std::move(name), autoRemove, (Graphics::TextureType)type, (Graphics::TextureFilter)filter);
                    }))
                .endClass();
    });

    // Skybox
    this->m_compiler->RegisterScriptClass("Graphics", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::Skybox>("Skybox")
                    .addStaticFunction("Load", static_cast<Graphics::Skybox*(*)(std::string)>([](std::string name) -> Graphics::Skybox* {
                        return Skybox::Load(std::move(name));
                    }))
                    .addFunction("Free", (bool (Framework::Graphics::Skybox::*)(void))&Graphics::Skybox::Free)
                    .addFunction("AwaitDestroy", (bool (Framework::Graphics::Skybox::*)(void))&Graphics::Skybox::AwaitDestroy)
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
                    .addFunction("RegisterTexture", (void (Framework::Graphics::Render::*)(Graphics::Texture*))&Graphics::Render::RegisterTexture)
                    .addFunction("SetSkybox", (void (Framework::Graphics::Render::*)(Graphics::Skybox*))&Graphics::Render::SetSkybox)
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
                    .addFunction("DestroyCamera", (void (Framework::Graphics::Window::*)(Graphics::Camera*))&Graphics::Window::DestroyCamera)
                    .addFunction("SetCanvas", (bool (Framework::Graphics::Window::*)(Graphics::GUI::ICanvas*))&Graphics::Window::SetCanvas)
                .endClass();
    });

    // ICanvas
    this->m_compiler->RegisterScriptClass("GUI", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
            .beginClass<Graphics::GUI::ICanvas>("Canvas")
                    //.addStaticFunction("Load", static_cast<Graphics::GUI::ICanvas*(*)(const std::string&, bool)>([](const std::string& luaScriptName, bool fromEditor) -> Graphics::GUI::ICanvas* {
                    //    Scripting::Script* script = Engine::Get()->GetCompiler()->DelayedLoad(luaScriptName, fromEditor);
                    //    return (Graphics::GUI::ICanvas*)(new Framework::Canvas(script));
                    //}))
                    .addStaticFunction("Load", static_cast<Graphics::GUI::ICanvas*(*)(Scripting::Script*)>([](Scripting::Script*script) -> Graphics::GUI::ICanvas* {
                        return (Graphics::GUI::ICanvas*)(new Framework::Canvas(script));
                    }))
            .endClass();
    });

    // DockSpace
    this->m_compiler->RegisterScriptClass("GUI", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::GUI::DockSpace>("DockSpace")
                        .addStaticFunction("Begin", static_cast<void(*)()>([]() {
                            Graphics::GUI::DockSpace::Begin();
                        }))
                .endClass();
    });

    /*// ImVec4
    this->m_compiler->RegisterScriptClass("GUI", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<ImVec4>("ImVec4")
                    .addStaticFunction("New", static_cast<ImVec4(*)(float,float,float,float)>([](float x,float y,float z,float w) -> ImVec4 {
                        return ImVec4(x,y,z,w);
                    }))
                .endClass();
    });

    // ImGuiStyle
    this->m_compiler->RegisterScriptClass("GUI", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<ImGuiStyle>("ImGuiStyle")
                    .addStaticFunction("Get", static_cast<ImGuiStyle&(*)()>([]() -> ImGuiStyle& { return ImGui::GetStyle(); }))
                    .addStaticFunction("GetColors", static_cast<ImVec4*(*)()>([]() -> ImVec4* {
                        return ImGui::GetStyle().Colors;
                    }))
                .endClass();
    });*/

    // GUIWindow
    this->m_compiler->RegisterScriptClass("GUI", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::GUI::GUIWindow>("GUIWindow")
                    .addStaticFunction("Begin", static_cast<void(*)(const std::string&)>([](const std::string& winName) {
                        Graphics::GUI::GUIWindow::Begin(winName);
                    }))
                    .addStaticFunction("End", static_cast<void(*)()>([]() {
                        Graphics::GUI::GUIWindow::End();
                    }))
                    .addStaticFunction("BeginChild", static_cast<void(*)(const std::string&)>([](const std::string& winName) {
                        Graphics::GUI::GUIWindow::BeginChild(winName);
                    }))
                    .addStaticFunction("EndChild", static_cast<void(*)()>([]() {
                        Graphics::GUI::GUIWindow::EndChild();
                    }))
                    .addStaticFunction("GetSize", static_cast<glm::vec2(*)()>([]() -> glm::vec2 {
                        return Graphics::GUI::GUIWindow::GetWindowSize();
                    }))
                    .addStaticFunction("DrawTexture", static_cast<void(*)(glm::vec2, glm::vec2, unsigned int, bool)>(
                            [](glm::vec2 winSize, glm::vec2 imgSize, unsigned int texID, bool center) {
                        Graphics::GUI::GUIWindow::DrawTexture(winSize, imgSize, texID, center);
                    }))
                .endClass();
    });

    return true;
}
