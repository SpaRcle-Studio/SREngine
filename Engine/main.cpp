//
// Created by Nikita on 29.12.2020.
//

#include <easy/profiler.h>

#include <Engine.h>

#include <Debug.h>
#include <FileSystem/FileSystem.h>
#include <ResourceManager/ResourceManager.h>
#include <Environment/OpenGL.h>
#include <EntityComponentSystem/Transform.h>

using namespace Framework;
using namespace Framework::Scripting;
using namespace Framework::Helper;
using namespace Framework::Helper::Math;
using namespace Framework::Helper::Types;
using namespace Framework::Graphics;
using namespace Framework::Graphics::Types;

int main() {
    ShellExecute(nullptr, "open", "EngineCrashHandler.exe", ("--log log.txt --target "+FileSystem::GetExecutableFileName()).c_str(), nullptr, SW_SHOWDEFAULT);

    if (Helper::Debug::Profile()) EASY_PROFILER_ENABLE;

    Debug::Init(FileSystem::GetPathToExe(), true, Debug::Theme::Dark);
    Debug::SetLevel(Debug::Level::Low);
    ResourceManager::Init(FileSystem::GetPathToExe() + "/../../Resources");

    // Register all resource types
    {
        ResourceManager::RegisterType("Mesh");
        ResourceManager::RegisterType("Texture");
    }

    Environment::Set(new OpenGL());

    auto *render = new Render();

    WindowFormat format = WindowFormat::_1366_768;
    auto *window = new Window(
            "SpaRcle Engine",
            format,
            render,
            false,
            false,
            4
    );

    Scene* scene = Scene::New("New scene");

    Engine *engine = Engine::Get();

    if(engine->Create(window, scene)){
      if (engine->Init(nullptr)){
          if (engine->Run()){

          }
          else
              Debug::Error("Failed running game engine!");
      } else
          Debug::Error("Failed initializing game engine!");
    } else
        Debug::Error("Failed creating game engine!");

    Debug::System("All systems successfully run!");

    if (engine->IsRun())
        engine->Await(); // await close engine

    engine->Close();

    Debug::System("All systems successfully closed!");

    ResourceManager::Stop();

    if (Helper::Debug::Profile())
        profiler::dumpBlocksToFile("profile.prof");

    return Debug::Stop();
}