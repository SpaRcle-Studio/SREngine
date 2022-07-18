//
// Created by Nikita on 29.12.2020.
//	looked by Drakeme on 26.06.2022.

#include <Utils/macros.h>

/// TODO: move to platform class!
#ifdef SR_WIN32
    #include <Windows.h>
    #include <shellapi.h>
#endif

#include <Utils/Debug.h>
#include <Audio/Sound.h>

#include <Core/Engine.h>
#include <Core/World/World.h>
#include <Core/World/VisualChunk.h>
#include <Core/World/VisualRegion.h>

#include <Utils/ResourceManager/ResourceManager.h>
#include <Environment/OpenGL.h>
#include <Environment/Vulkan.h>

#include <Utils/ECS/ComponentManager.h>
#include <Utils/Input/InputSystem.h>
#include <Utils/Common/CmdOptions.h>
#include <Utils/Common/Features.h>
#include <Utils/Types/Marshal.h>
#include <Audio/RawSound.h>
#include <Audio/SoundManager.h>

#include <Types/Rigidbody.h>
#include <Utils/Types/RawMesh.h>
#include <Types/Texture.h>
#include <Loaders/SRSL.h>
#include <Types/Material.h>
#include <Types/Skybox.h>
#include <Types/Mesh.h>
#include <Types/Shader.h>
#include <Types/Geometry/Mesh3D.h>
#include <Animations/Bone.h>
#include <Memory/MeshAllocator.h>
#include <GUI/NodeManager.h>
#include <FbxLoader/Debug.h>
#include <Types/Camera.h>
#include <Render/RenderManager.h>
#include <Memory/CameraManager.h>
#include <Scripting/Base/Behaviour.h>
#include <Utils/Settings.h>
#include <Utils/Platform/Platform.h>
#include <Types/Framebuffer.h>
#include <Types/RenderTexture.h>

using namespace Framework;

using namespace Framework::Core;
using namespace Framework::Core::World;

using namespace Framework::Helper;
using namespace Framework::Helper::Math;
using namespace Framework::Helper::Types;
using namespace Framework::Helper::World;

using namespace Framework::Graphics;
using namespace Framework::Graphics::Types;
using namespace Framework::Graphics::Animations;

using namespace Framework::Physics;
using namespace Framework::Physics::Types;

using namespace Framework::Scripting;

using namespace Framework::Audio;
/*
        +---------------+       +----+          +----+       +---------------+            +----------------+
        |               |       \     \        /     /       |               |           /                 |
        |               |        \     \      /     /        |               |          /                  |
        |      +--------+         \     \    /     /         |      +--------+         /         +---------+
        |      |                   \     \  /     /          |      |                 /        /
        |      +--------+           \     \/     /           |      +--------+       |        /
        |               |            \          /            |               |       |       |
        |               |            /          \            |               |       |       |
        |      +--------+           /     /\     \           |      +--------+       |        \
        |      |                   /     /  \     \          |      |                 \        \
        |      +--------+         /     /    \     \         |      +--------+         \        +---------+
        |               |        /     /      \     \        |               |          \                 |
        |               |       /     /        \     \       |               |           \                |
        +---------------+       +----+          +-----+      +---------------+            +---------------+
 */

int main(int argc, char **argv) {
    if constexpr (sizeof(size_t) != 8) {
        std::cerr << "The engine supports only 64-bit systems!\n";
        return -1;
    }

    setlocale(LC_ALL, "rus");
    setlocale(LC_NUMERIC, "C");
    srand(time(NULL));

    auto&& exe = SR_PLATFORM_NS::GetApplicationPath().GetFolder();
    Debug::Instance().Init(exe, true, Debug::Theme::Dark);
    Debug::Instance().SetLevel(Debug::Level::Low);

    Thread::Factory::Instance().SetMainThread();

    auto&& resourcesManager = ResourceManager::Instance();

    if (auto&& folder = GetCmdOption(argv, argv + argc, "-resources"); folder.empty()) {
        resourcesManager.Init(Path(exe.ToString() + "/../../Resources"));
    }
    else
        resourcesManager.Init(folder);

    Features::Instance().Reload(resourcesManager.GetResPath().Concat("/Configs/Features.xml"));

    if (!FbxLoader::Debug::IsInit()) {
        FbxLoader::Debug::Init(
                [](const std::string &msg) { SR_ERROR(msg); },
                [](const std::string &msg) { SR_WARN(msg); }
        );
    }

    if (Features::Instance().Enabled("CrashHandler")) {
#ifdef SR_WIN32
        ShellExecute(nullptr, "open", (ResourceManager::Instance().GetResPath().Concat(
                "/Utilities/EngineCrashHandler.exe").CStr()),
                     ("--log log.txt --target " + SR_PLATFORM_NS::GetApplicationName().ToString() + " --out " + exe.ToString() + "\\").c_str(),
                     nullptr, SW_SHOWDEFAULT
        );
#endif
    }

    // Register all resource types
    {
        resourcesManager.RegisterType<RawMesh>();
        resourcesManager.RegisterType<Mesh>();
        resourcesManager.RegisterType<Texture>();
        resourcesManager.RegisterType<Material>();
        resourcesManager.RegisterType<Shader>();
        resourcesManager.RegisterType<Skybox>();
        resourcesManager.RegisterType<Behaviour>();
        resourcesManager.RegisterType<Settings>();
        resourcesManager.RegisterType<Sound>();
        resourcesManager.RegisterType<RawSound>();
        resourcesManager.RegisterType<Framebuffer>();
    }

    // Register all components
    {
        //Component::RegisterComponent("SkinnedMesh", []() -> Component* { return new SkinnedMesh();  });
        ComponentManager::Instance().RegisterComponent<Mesh3D>([]() -> Mesh3D* { return Memory::MeshAllocator::Allocate<Mesh3D>(); });
        ComponentManager::Instance().RegisterComponent<Rigidbody>([]() -> Rigidbody* { return new Rigidbody(); });
        ComponentManager::Instance().RegisterComponent<Camera>([]() -> Camera* { return Camera::Allocate(); });
        ComponentManager::Instance().RegisterComponent<Bone>([]() -> Bone* { return new Bone(); });
        ComponentManager::Instance().RegisterComponent<Behaviour>([]() -> Behaviour* { return Behaviour::CreateEmpty(); });

        if (Helper::Features::Instance().Enabled("DebugChunks", false))
            Chunk::SetAllocator([](SRChunkAllocArgs) -> Chunk * { return new VisualChunk(SRChunkAllocVArgs); });

        if (Helper::Features::Instance().Enabled("DebugRegions", false))
            Region::SetAllocator([](SRRegionAllocArgs) -> Region* { return new VisualRegion(SRRegionAllocVArgs); });

        SceneAllocator::Instance().Init([]() -> Scene* { return new Core::World::World(); });
    }

    //TEST AUDIO LOAD

    /*
    if (auto&& pSound = SR_AUDIO_NS::Sound::Load("Space_Angels_Musicfonts.wav")) {
        pSound->PlayAsync();
        //pSound->Destroy();
    }

    //SR_AUDIO_NS::Sound::Load("ahh.wav");
    //SR_AUDIO_NS::Sound::Load("drop.wav");
    //SR_AUDIO_NS::Sound::Load("Space_Engineers_Main_Theme_KhydroDjent.wav");
    //SR_AUDIO_NS::Sound::Load("TRAUMATIC.mp3");
     */

    const auto&& envDoc = Xml::Document::Load(ResourceManager::Instance().GetConfigPath().Concat("Environment.xml"));
    const auto&& envName = envDoc.TryRoot().TryGetNode("Environment").TryGetAttribute("Name").ToString("");

    if (envName == "OpenGL") {
        Environment::Set(new OpenGL());
    }
    else if (envName == "Vulkan") {
        Environment::Set(new Vulkan());
    }
    else if (envName.empty()) {
        SR_ERROR("System error: file \"Resources/Configs/Environment.xml\" does not exist!");
        ResourceManager::DestroySingleton();
        Debug::DestroySingleton();
        return -1500;
    }
    else {
        SR_ERROR("System error: unknown environment! \"" + envName + "\" is not supported!");
        ResourceManager::DestroySingleton();
        Debug::DestroySingleton();
        return -2000;
    }

    Render* render = RenderManager::Instance().Allocate("Main");
    if (!render) {
        SR_ERROR("FATAL: render does not support this pipeline!");
        ResourceManager::DestroySingleton();
        Debug::DestroySingleton();
        return -1000;
    }

    auto window = new Window(
            "SpaRcle Engine",
            "Engine/icon.ico",
            IVector2(1366, 768), //IVector2(1600, 900),
            render,
            false, // vsync
            false, // fullscreen
            true,  // resizable
            true,  // header enabled
            2
    );

    auto physics = new PhysEngine();

    auto&& engine = Engine::Instance();

    if(engine.Create(window, physics)) {
        if (engine.Init()) {
            if (engine.Run()) {

            }
            else
                SR_ERROR("Failed to run game engine!");
        }
        else
            SR_ERROR("Failed to initialize game engine!");
    }
    else
        SR_ERROR("Failed to create game engine!");

    if (engine.IsRun()) {
        Debug::Instance().System("All systems are successfully running!");

        engine.Await(); // await close engine
    }

    engine.Close();

    SR_GRAPH_NS::Memory::CameraManager::DestroySingleton();
    SR_SCRIPTING_NS::GlobalEvoCompiler::DestroySingleton();
    SR_UTILS_NS::EntityManager::DestroySingleton();
    SR_AUDIO_NS::SoundManager::DestroySingleton();
    Framework::Engine::DestroySingleton();
    Framework::Graphics::GUI::NodeManager::DestroySingleton();

    Debug::Instance().System("All systems were successfully closed!");

    ResourceManager::DestroySingleton();

    SR_SYSTEM_LOG("Thread count: " + ToString(Thread::Factory::Instance().GetThreadsCount()));

    Debug::DestroySingleton();

    return 0;
}