//
// Created by Nikita on 29.12.2020.
//

#ifdef _DEBUG

#else
    #define SR_RELEASE
#endif

#include <easy/profiler.h>

#include <Engine.h>

#include <Debug.h>
#include <FileSystem/FileSystem.h>
#include <ResourceManager/ResourceManager.h>
#include <Environment/OpenGL.h>
#include <Environment/Vulkan.h>
#include <EntityComponentSystem/Transform.h>

#include <Types/Rigidbody.h>
#include <Core/PhysEngine.h>

using namespace Framework;
using namespace Framework::Scripting;
using namespace Framework::Helper;
using namespace Framework::Helper::Math;
using namespace Framework::Helper::Types;
using namespace Framework::Graphics;
using namespace Framework::Graphics::Types;
using namespace Framework::Physics;
using namespace Framework::Physics::Types;

int main() {
    std::string exe = FileSystem::GetPathToExe();

    Debug::Init(exe, true, Debug::Theme::Dark);
    Debug::SetLevel(Debug::Level::Full);
    ResourceManager::Init(exe + "/../../Resources");

    ShellExecute(nullptr, "open", (ResourceManager::GetResourcesFolder() + "\\Utilities\\EngineCrashHandler.exe").c_str(),
            ("--log log.txt --target "+FileSystem::GetExecutableFileName() + " --out " + exe + "\\").c_str(),
            nullptr, SW_SHOWDEFAULT
    );

    // Register all resource types
    {
        ResourceManager::RegisterType("Mesh");
        ResourceManager::RegisterType("Texture");
    }

    // Register all components
    {
        Component::RegisterComponent("Mesh", []() -> Component* { return new Mesh(); });
        Component::RegisterComponent("Rigidbody", []() -> Rigidbody* { return new Rigidbody(); });
        Component::RegisterComponent("Camera", []() -> Camera* { return new Camera(); });
    }

    //Environment::Set(new OpenGL());
    Environment::Set(new Vulkan());

    auto *render = new Render();

    WindowFormat format = WindowFormat::_1600_900;
    //WindowFormat format = WindowFormat::_1366_768;
    auto *window = new Window(
            "SpaRcle Engine",
            format,
            render,
            false,
            false,
            0
    );

    Scene* scene = Scene::New("New scene");

    auto* physics = new PhysEngine();

    Engine *engine = Engine::Get();

    if(engine->Create(window, scene, physics)){
      if (engine->Init(nullptr)){
          if (engine->Run()){

          }
          else
              Debug::Error("Failed running game engine!");
      } else
          Debug::Error("Failed initializing game engine!");
    } else
        Debug::Error("Failed creating game engine!");

    if (engine->IsRun()) {
        Debug::System("All systems successfully run!");

        engine->Await(); // await close engine
    }

    engine->Close();

    Debug::System("All systems successfully closed!");

    ResourceManager::Stop();

    if (Helper::Debug::Profile())
        profiler::dumpBlocksToFile("profile.prof");

    return Debug::Stop();
}