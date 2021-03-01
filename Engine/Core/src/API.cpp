//
// Created by Monika on 14.02.2021.
//

#include <API.h>
#include <Engine.h>
#include <Types/Time.h>
#include <EntityComponentSystem/Transform.h>
#include <GUI/Canvas.h>
#include <Math/Vector3.h>

using namespace Framework::Helper::Math;

void Framework::API::Register(Framework::Scripting::Compiler *compiler) {
    // Engine
    compiler->RegisterScriptClass("Base", [](lua_State* L) {
        luabridge::getGlobalNamespace(L)
            .beginClass<Engine>("Engine")
                    .addStaticFunction("Get", static_cast<Engine*(*)()>([]() {
                        return Engine::Get();
                    }))
                    .addStaticFunction("Reload", static_cast<void(*)()>([]() {
                        return Engine::Reload();
                    }))
            .endClass();
    });

    // Debug
    compiler->RegisterScriptClass("Base", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Debug>("Debug")
                    .addStaticFunction("Log", static_cast<void(*)(std::string)>([](std::string s) {
                        Debug::ScriptLog(std::move(s));
                    }))
                    .addStaticFunction("Error", static_cast<void(*)(std::string)>([](std::string s) {
                        Debug::ScriptError(std::move(s));
                    }))
                    .addStaticFunction("MakeCrash", static_cast<void(*)()>([]() {
                        Debug::MakeCrash();
                    }))
                .endClass();
    });

    // String
    compiler->RegisterScriptClass("Base", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<std::string>("String")
                .addStaticFunction("FromFloat", static_cast<std::string(*)(float)>([](float f) -> std::string {
                    return std::to_string(f);
                }))
                .addStaticFunction("FromBool", static_cast<std::string(*)(bool)>([](bool b) -> std::string {
                    return b ? "true" : "false";
                }))
                .endClass();
    });

    // Time
    compiler->RegisterScriptClass("Base", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Helper::Types::Time>("Time")
                .addStaticFunction("DeltaTime", static_cast<double (*)()>([]() -> double {
                    return Engine::Get()->GetTime()->DeltaTime();
                }))
                .endClass();
    });

    // KeyCode and Input
    compiler->RegisterScriptClass("Base", [](lua_State* L) {
        static int MouseMiddle      = (int)KeyCode::MouseMiddle;
        static int MouseLeft        = (int)KeyCode::MouseLeft;
        static int MouseRight       = (int)KeyCode::MouseRight;
        static int A                = (int)KeyCode::A;
        static int D                = (int)KeyCode::D;
        static int S                = (int)KeyCode::S;
        static int Q                = (int)KeyCode::Q;
        static int R                = (int)KeyCode::R;
        static int W                = (int)KeyCode::W;
        static int T                = (int)KeyCode::T;
        static int P                = (int)KeyCode::P;
        static int B                = (int)KeyCode::B;
        static int E                = (int)KeyCode::E;
        static int F                = (int)KeyCode::F;
        static int C                = (int)KeyCode::C;
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
                .addProperty("Q",               &Q,                   false)
                .addProperty("W",               &W,                   false)
                .addProperty("R",               &R,                   false)
                .addProperty("T",               &T,                   false)
                .addProperty("P",               &P,                   false)
                .addProperty("B",               &B,                   false)
                .addProperty("E",               &E,                   false)
                .addProperty("F",               &F,                   false)
                .addProperty("C",               &C,                   false)
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

    // EventManager
    compiler->RegisterScriptClass("Base", [](lua_State* L) {
        static int exit = (int)EventManager::Event::Exit;

        luabridge::getGlobalNamespace(L)
                .beginNamespace("Event")
                .addProperty("Exit", &exit, false)
                .endNamespace()

                .beginClass<Helper::EventManager>("EventManager")
                .addStaticFunction("Push", static_cast<void(*)(int)>([](int event) {
                    EventManager::Push((EventManager::Event)event);
                }))
                .endClass();
    });

    // Vector3
    compiler->RegisterScriptClass("Math", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Vector3>("Vector3")
                    .addStaticFunction("New", static_cast<Vector3(*)(float,float,float)>([](float x,float y,float z) -> Vector3 {
                        return Vector3(x,y,z);
                    }))

                    .addProperty("x", &Vector3::x)
                    .addProperty("y", &Vector3::y)
                    .addProperty("z", &Vector3::z)

                    .addFunction("Empty", (Vector3 (Math::Vector3::*)(void))&Helper::Math::Vector3::Empty)
                    .addStaticFunction("Sum", static_cast<Vector3(*)(Vector3, Vector3)>([](Vector3 v1, Vector3 v2) -> Vector3 {
                         return v1 + v2;
                     }))
                    .addStaticFunction("Sub", static_cast<Vector3(*)(Vector3, Vector3)>([](Vector3 v1, Vector3 v2) -> Vector3 {
                        return v1 - v2;
                    }))
                    .addStaticFunction("FMul", static_cast<Vector3(*)(Vector3, float)>([](Vector3 v1, float f) -> Vector3 {
                        return v1 * f;
                    }))
                    .addStaticFunction("FDiv", static_cast<Vector3(*)(Vector3, float)>([](Vector3 v1, float f) -> Vector3 {
                        return v1 / f;
                    }))
                .endClass();
    });

    // Vector2
    compiler->RegisterScriptClass("Math", [](lua_State* L){
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
    compiler->RegisterScriptClass("Math", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Helper::Transform>("Transform")
                .addFunction("Forward", (Vector3 (Framework::Helper::Transform::*)(void))&Helper::Transform::Forward)
                .addFunction("Up", (Vector3 (Framework::Helper::Transform::*)(void))&Helper::Transform::Up)
                .addFunction("Right", (Vector3 (Framework::Helper::Transform::*)(void))&Helper::Transform::Right)

                .addFunction("Translate", (void (Helper::Transform::*)(Vector3))&Helper::Transform::Translate)
                .addFunction("Rotate",    (void (Helper::Transform::*)(Vector3))&Helper::Transform::Rotate)

                .addFunction("SetScale",    (void (Helper::Transform::*)(Vector3, bool))&Helper::Transform::SetScale)
                .endClass();
    });

    // Component
    compiler->RegisterScriptClass("Engine", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Helper::Component>("Component")
                        .addFunction("GetParent", (GameObject* (Helper::Component::*)(void))&Helper::Component::GetParent)
                .endClass();
    });

    // GameObject
    compiler->RegisterScriptClass("Engine", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Helper::GameObject>("GameObject")
                .addFunction("AddComponent", (bool (Framework::Helper::GameObject::*)(Helper::Component*))&Helper::GameObject::AddComponent)
                .addFunction("GetTransform", (Helper::Transform* (Framework::Helper::GameObject::*)(void))&Helper::GameObject::GetTransform)
                .addFunction("AddChild", (bool (Framework::Helper::GameObject::*)(Helper::GameObject*))&Helper::GameObject::AddChild)
                .addFunction("SetSelect", (void (Framework::Helper::GameObject::*)(bool))&Helper::GameObject::SetSelect)
                .endClass();
    });

    // Scene
    compiler->RegisterScriptClass("Engine", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Helper::Scene>("Scene")
                .addStaticFunction("Get", static_cast<Scene*(*)()>([]() -> Scene* {
                    return Engine::Get()->GetScene();
                }))
                .addFunction("Instance", (GameObject* (Framework::Helper::Scene::*)(std::string))&Helper::Scene::Instance)
                .addFunction("GetSelected", (GameObject* (Framework::Helper::Scene::*)(void))&Helper::Scene::GetSelected)
                .addFunction("DestroyGM", (bool (Framework::Helper::Scene::*)(GameObject*))&Helper::Scene::DestroyGameObject)
                .addFunction("Destroy", (bool (Framework::Helper::Scene::*)(void))&Helper::Scene::Destroy)
                .addFunction("Free", (bool (Framework::Helper::Scene::*)(void))&Helper::Scene::Free)
                .addFunction("Print", (void (Framework::Helper::Scene::*)(void))&Helper::Scene::Print)
                .addFunction("UnselectAll", (void (Framework::Helper::Scene::*)(void))&Helper::Scene::UnselectAll)
                .endClass();
        Scripting::Script::RegisterCasting<Scene*>("Scene", L);
    });

    // Material
    compiler->RegisterScriptClass("Graphics", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::Material>("Material")
                .addFunction("SetDiffuse", (void (Framework::Graphics::Material::*)(Graphics::Texture*))&Graphics::Material::SetDiffuse)
                .addFunction("SetBloom", (void (Framework::Graphics::Material::*)(bool value))&Graphics::Material::SetBloom)
                .addFunction("SetColor", (void (Framework::Graphics::Material::*)(Vector3))&Graphics::Material::SetColor)
                .addStaticFunction("RandomColor3", static_cast<Vector3(*)()>([]() -> Vector3 {
                    return Graphics::Material::GetRandomColor();
                }))
                .endClass();
    });

    // Mesh
    compiler->RegisterScriptClass("Graphics", [](lua_State* L){
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
                .addFunction("Copy", (Framework::Graphics::Mesh* (Framework::Graphics::Mesh::*)(void))&Graphics::Mesh::Copy)
                .addFunction("Base", (Helper::Component* (Framework::Graphics::Mesh::*)(void))&Graphics::Mesh::BaseComponent)
                .addFunction("GetMaterial", (Graphics::Material* (Framework::Graphics::Mesh::*)(void))&Graphics::Mesh::GetMaterial)
                .endClass();
    });

    // PostProcessing
    compiler->RegisterScriptClass("Graphics", [](lua_State* L) {
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::PostProcessing>("PostProcessing")
                .addFunction("SetBloomIntensity", (void (Framework::Graphics::PostProcessing::*)(float))&Graphics::PostProcessing::SetBloomIntensity)
                .addFunction("SetBloomAmount", (void (Framework::Graphics::PostProcessing::*)(int))&Graphics::PostProcessing::SetBloomAmount)
                .addFunction("SetBloom", (void (Framework::Graphics::PostProcessing::*)(bool))&Graphics::PostProcessing::SetBloom)
                .addFunction("GetBloomEnabled", (bool (Framework::Graphics::PostProcessing::*)(void))&Graphics::PostProcessing::GetBloomEnabled)
                .addFunction("SetGamma", (void (Framework::Graphics::PostProcessing::*)(float))&Graphics::PostProcessing::SetGamma)
                .addFunction("SetExposure", (void (Framework::Graphics::PostProcessing::*)(float))&Graphics::PostProcessing::SetExposure)
                .addFunction("GetFinalTextureID", (unsigned int (Framework::Graphics::PostProcessing::*)(void))&Graphics::PostProcessing::GetFinally)
                .addFunction("GetColoredImage", (unsigned int (Framework::Graphics::PostProcessing::*)(void))&Graphics::PostProcessing::GetColoredImage)
                .addFunction("GetBloomMask", (unsigned int (Framework::Graphics::PostProcessing::*)(void))&Graphics::PostProcessing::GetBloomMask)
                .addFunction("GetCustomColorBuffer", (unsigned int (Framework::Graphics::PostProcessing::*)(unsigned char))&Graphics::PostProcessing::GetCustomColorBuffer)
                .addFunction("GetBlurBloomMask", (unsigned int (Framework::Graphics::PostProcessing::*)(void))&Graphics::PostProcessing::GetBlurBloomMask)
                .addFunction("GetSkyboxColor", (unsigned int (Framework::Graphics::PostProcessing::*)(void))&Graphics::PostProcessing::GetSkyboxColor)
                .addFunction("GetStencilBuffer", (unsigned int (Framework::Graphics::PostProcessing::*)(void))&Graphics::PostProcessing::GetStencilBuffer)
                .addFunction("GetDepthBuffer", (unsigned int (Framework::Graphics::PostProcessing::*)(void))&Graphics::PostProcessing::GetDepthBuffer)
                .endClass();
    });

    // Camera
    compiler->RegisterScriptClass("Graphics", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::Camera>("Camera")
                .addStaticFunction("New", static_cast<Graphics::Camera*(*)(unsigned int)>([](unsigned int countHDRBuffers) -> Graphics::Camera* {
                    return new Graphics::Camera(countHDRBuffers);
                }))
                .addFunction("GetPostProcessing", (Graphics::PostProcessing* (Framework::Graphics::Camera::*)(void))&Graphics::Camera::GetPostProcessing)
                        //.addFunction("Free", (bool (Framework::Graphics::Camera::*)(void))&Graphics::Camera::Free)
                .addFunction("Base", (Helper::Component* (Framework::Graphics::Camera::*)(void))&Graphics::Camera::BaseComponent)
                .addFunction("SetFrameSize", (void (Framework::Graphics::Camera::*)(unsigned int w, unsigned int h))&Graphics::Camera::UpdateProjection)
                .addFunction("SetDirectOutput", (void (Framework::Graphics::Camera::*)(bool value))&Graphics::Camera::SetDirectOutput)
                .addFunction("IsDirectOutput", (bool (Framework::Graphics::Camera::*)(void))&Graphics::Camera::IsDirectOutput)
                .addFunction("GetSize", (glm::vec2 (Framework::Graphics::Camera::*)(void))&Graphics::Camera::GetSize)
                .addFunction("WaitCalculate", (void (Framework::Graphics::Camera::*)(void))&Graphics::Camera::WaitCalculate)
                .addFunction("WaitBuffersCalculate", (void (Framework::Graphics::Camera::*)(void))&Graphics::Camera::WaitBuffersCalculate)
                .endClass();
        Scripting::Script::RegisterCasting<Graphics::Camera*>("Camera", L);
    });

    // Texture & TextureFilter & TextureType
    compiler->RegisterScriptClass("Graphics", [](lua_State* L) {
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
    compiler->RegisterScriptClass("Graphics", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::Skybox>("Skybox")
                .addStaticFunction("Load", static_cast<Graphics::Skybox*(*)(std::string, std::string)>([](std::string name, std::string shaderName) -> Graphics::Skybox* {
                    return Skybox::Load(std::move(name), std::move(shaderName));
                }))
                .addFunction("Free", (bool (Framework::Graphics::Skybox::*)(void))&Graphics::Skybox::Free)
                .addFunction("AwaitDestroy", (bool (Framework::Graphics::Skybox::*)(void))&Graphics::Skybox::AwaitDestroy)
                .endClass();
    });

    // Render
    compiler->RegisterScriptClass("Graphics", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::Render>("Render")
                .addStaticFunction("Get", static_cast<Graphics::Render*(*)()>([]() -> Graphics::Render* {
                    return Engine::Get()->GetWindow()->GetRender();
                }))
                .addFunction("SetGridEnabled", (void (Framework::Graphics::Render::*)(bool))&Graphics::Render::SetGridEnabled)
                .addFunction("RegisterMesh", (void (Framework::Graphics::Render::*)(Graphics::Mesh*))&Graphics::Render::RegisterMesh)
                .addFunction("RegisterTexture", (void (Framework::Graphics::Render::*)(Graphics::Texture*))&Graphics::Render::RegisterTexture)
                .addFunction("SetSkybox", (void (Framework::Graphics::Render::*)(Graphics::Skybox*))&Graphics::Render::SetSkybox)
                .endClass();
    });

    // Window
    compiler->RegisterScriptClass("Graphics", [](lua_State* L){
        luabridge::getGlobalNamespace(L)
                .beginClass<Graphics::Window>("Window")
                .addStaticFunction("Get", static_cast<Graphics::Window*(*)()>([]() -> Graphics::Window* {
                    return Engine::Get()->GetWindow();
                }))
                .addFunction("AddCamera", (void (Framework::Graphics::Window::*)(Graphics::Camera*))&Graphics::Window::AddCamera)
                .addFunction("DestroyCamera", (void (Framework::Graphics::Window::*)(Graphics::Camera*))&Graphics::Window::DestroyCamera)
                .addFunction("SetCanvas", (bool (Framework::Graphics::Window::*)(Graphics::GUI::ICanvas*))&Graphics::Window::SetCanvas)
                .addFunction("GetWindowSize", (glm::vec2 (Framework::Graphics::Window::*)(void))&Graphics::Window::GetWindowSize)
                .addFunction("IsFullScreen", (bool (Framework::Graphics::Window::*)(void))&Graphics::Window::IsFullScreen)
                .addFunction("SetGUIEnabled", (void (Framework::Graphics::Window::*)(bool))&Graphics::Window::SetGUIEnabled)
                .addFunction("SetFullScreen", (void (Framework::Graphics::Window::*)(bool))&Graphics::Window::SetFullScreen)
                .addFunction("Resize", (void (Framework::Graphics::Window::*)(unsigned int, unsigned int))&Graphics::Window::Resize)
                .addFunction("CentralizeWindow", (void (Framework::Graphics::Window::*)())&Graphics::Window::CentralizeWindow)
                .addFunction("RequireAimedMesh", (bool (Framework::Graphics::Window::*)(Graphics::Camera*,ImGuiWindow*))&Graphics::Window::RequireAimedMesh)
                .addFunction("PopAimedMesh", (Mesh* (Framework::Graphics::Window::*)(void))&Graphics::Window::PopAimedMesh)
                .endClass();
    });

    // ICanvas
    compiler->RegisterScriptClass("GUI", [](lua_State* L){
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
    compiler->RegisterScriptClass("GUI", [](lua_State* L){
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

    // ImGuiWindow
    compiler->RegisterScriptClass("GUI", [](lua_State* L) {
        luabridge::getGlobalNamespace(L)
            .beginClass<ImGuiWindow>("ImGuiWindow")

            .endClass();
    });

    // GUIWindow
    compiler->RegisterScriptClass("GUI", [](lua_State* L){
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
                .addStaticFunction("SetGuizmoTool", static_cast<bool(*)(unsigned char)>([](unsigned char id) -> bool {
                            return Graphics::GUI::GUIWindow::SetGuizmoTool(id);
                        }))
                .addStaticFunction("DrawGuizmo", static_cast<void(*)(Graphics::Camera*, Helper::GameObject*, glm::vec2)>(
                        [](Graphics::Camera* camera,Helper::GameObject*gm, glm::vec2 cameraSize) {
                    Graphics::GUI::GUIWindow::DrawGuizmo(camera, gm, cameraSize);
                }))
                .addStaticFunction("DrawInspector", static_cast<void(*)(Helper::GameObject*)>([](Helper::GameObject*gm) {
                    if (!gm)
                        return;

                    ret:
                    if (gm->GetScene()->GetCountUsesPoints() > 0)
                        goto ret;

                    gm->GetScene()->AddUsePoint();

                    Graphics::GUI::GUIWindow::DrawInspector(gm);

                    gm->GetScene()->RemoveUsePoint();
                }))
                .addStaticFunction("DrawHierarchy", static_cast<void(*)(Helper::Scene*)>([](Helper::Scene*scene) {
                    ret:
                    if (scene->GetCountUsesPoints() > 0)
                        goto ret;

                    scene->AddUsePoint();

                    Graphics::GUI::GUIWindow::DrawHierarchy(scene);

                    scene->RemoveUsePoint();
                }))
                        //--------------------------------------------------------------------------------------------------
                .addStaticFunction("BeginMainMenuBar", static_cast<bool(*)()>([]() -> bool {
                    return Graphics::GUI::GUIWindow::BeginMainMenuBar();
                }))
                .addStaticFunction("EndMainMenuBar", static_cast<void(*)()>([]() {
                    Graphics::GUI::GUIWindow::EndMainMenuBar();
                }))
                .addStaticFunction("BeginMenu", static_cast<bool(*)(const std::string&)>([](const std::string& name) -> bool {
                    return Graphics::GUI::GUIWindow::BeginMenu(name.c_str());
                }))
                .addStaticFunction("EndMenu", static_cast<void(*)()>([]() {
                    Graphics::GUI::GUIWindow::EndMenu();
                }))
                .addStaticFunction("MenuItem", static_cast<bool(*)(const std::string&)>([](const std::string& name) -> bool {
                    return Graphics::GUI::GUIWindow::MenuItem(name.c_str());
                }))
                .addStaticFunction("DebugWindow", static_cast<void(*)(void)>([](void) {
                    Graphics::GUI::GUIWindow::DebugWindow();
                }))
                .addStaticFunction("Get", static_cast<ImGuiWindow*(*)()>([]() -> ImGuiWindow* {
                    return ImGui::GetCurrentWindow();
                }))
                .endClass();
    });
}

