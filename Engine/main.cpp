//
// Created by Nikita on 29.12.2020.
//

#ifdef WIN32
    #define VK_USE_PLATFORM_WIN32_KHR
#endif

#ifdef _DEBUG

#else
    #define SR_RELEASE
#endif

#include <Engine.h>

#include <Debug.h>
#include <ResourceManager/ResourceManager.h>
#include <Environment/OpenGL.h>
#include <Environment/Vulkan.h>
#include <EntityComponentSystem/Transform.h>

#include <Types/Rigidbody.h>
#include <Types/Geometry/Mesh3D.h>

using namespace Framework;
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

#ifdef WIN32
    ShellExecute(nullptr, "open", (ResourceManager::GetResourcesFolder() + "\\Utilities\\EngineCrashHandler.exe").c_str(),
            ("--log log.txt --target "+FileSystem::GetExecutableFileName() + " --out " + exe + "\\").c_str(),
            nullptr, SW_SHOWDEFAULT
    );
#endif

    // Register all resource types
    {
        ResourceManager::RegisterType("Mesh");
        ResourceManager::RegisterType("Texture");
    }

    // Register all components
    {
        //Component::RegisterComponent("SkinnedMesh",      []() -> Component* { return new SkinnedMesh();  });
        Component::RegisterComponent("Mesh3D",             []() -> Component* { return new Mesh3D();       });
        Component::RegisterComponent("Rigidbody",          []() -> Rigidbody* { return new Rigidbody();    });
        Component::RegisterComponent("Camera",             []() -> Camera*    { return Camera::Allocate(); });
    }

    if (auto env = Helper::FileSystem::ReadAllText(ResourceManager::GetResourcesFolder() + "/Configs/Environment.config"); env == "OpenGL")
        Environment::Set(new OpenGL());
    else if (env == "Vulkan")
        Environment::Set(new Vulkan());
    else if (env.empty()) {
        Helper::Debug::Error("System error: file \"Resources/Configs/Environment.config\" does not exist!\n\t"
                             "Please, create it and write the name of the environment there!");
        ResourceManager::Stop();
        Debug::Stop();
        return -1500;
    } else {
        Helper::Debug::Error("System error: unknown environment! \"" + env + "\" does not support!");
        ResourceManager::Stop();
        Debug::Stop();
        return -2000;
    }

    Render* render = Render::Allocate();
    if (!render) {
        Helper::Debug::Error("FATAL: render is not support this pipeline!");
        ResourceManager::Stop();
        Debug::Stop();
        return -1000;
    }

    auto window = new Window(
            "SpaRcle Engine",
            "icon.ico",
            WindowFormat::_480_480,
            render,
            false,
            false,
            true,
            2
    );

    auto physics = new PhysEngine();

    auto engine = Engine::Get();

    if(engine->Create(window, physics)) {
      if (engine->Init()){
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

    return Debug::Stop();
}