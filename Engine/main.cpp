//
// Created by Nikita on 29.12.2020.
// Looked by Drakeme on 26.06.2022.
// Changed by Monika on 20.11.2022
//

#include <Utils/macros.h>

/// TODO: move to platform class!
#ifdef SR_WIN32
    #include <Windows.h>
    #include <shellapi.h>
#endif

#include <Utils/Debug.h>
#include <Utils/World/SceneAllocator.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Input/InputSystem.h>
#include <Utils/Common/CmdOptions.h>
#include <Utils/Common/Features.h>
#include <Utils/Types/Marshal.h>
#include <Utils/TaskManager/TaskManager.h>
#include <Utils/Settings.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Locale/Encoding.h>

#include <Core/Engine.h>
#include <Core/World/World.h>
#include <Core/World/VisualChunk.h>
#include <Core/World/VisualRegion.h>
#include <Core/Settings/EditorSettings.h>

#include <Graphics/Pipeline/OpenGL.h>
#include <Graphics/Pipeline/Vulkan.h>
#include <Graphics/UI/Canvas.h>
#include <Graphics/UI/Anchor.h>
#include <Graphics/UI/Sprite2D.h>
#include <Graphics/SRSL/Shader.h>

#include <Graphics/Font/Text.h>
#include <Graphics/Types/Texture.h>
#include <Graphics/Loaders/SRSL.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Types/Skybox.h>
#include <Graphics/Types/Mesh.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Geometry/Mesh3D.h>
#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Graphics/Types/Geometry/DebugWireframeMesh.h>
#include <Graphics/Animations/Bone.h>
#include <Graphics/Memory/MeshAllocator.h>
#include <Graphics/GUI/NodeManager.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/Render/RenderManager.h>
#include <Graphics/Memory/CameraManager.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Types/RenderTexture.h>
#include <Graphics/Font/Font.h>

#include <Physics/Rigidbody.h>
#include <Physics/PhysicsScene.h>
#include <Physics/PhysicsLib.h>

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Impl/EvoScriptManager.h>

using namespace Framework;

using namespace Framework::Core;

using namespace Framework::Helper;
using namespace Framework::Helper::Math;
using namespace Framework::Helper::Types;
using namespace Framework::Helper::World;

using namespace Framework::Graphics;
using namespace Framework::Graphics::UI;
using namespace Framework::Graphics::Types;
using namespace Framework::Graphics::Animations;

using namespace Framework::Physics;
using namespace Framework::Physics::Types;

using namespace Framework::Scripting;

int main(int argc, char **argv) {
    setlocale(LC_ALL, "rus");
    setlocale(LC_NUMERIC, "C");
    srand(time(NULL));

    auto&& exe = SR_PLATFORM_NS::GetApplicationPath().GetFolder();
    Debug::Instance().Init(exe, true, Debug::Theme::Dark);
    Debug::Instance().SetLevel(Debug::Level::Low);

    SR_PLATFORM_NS::InitSegmentationHandler();

    Thread::Factory::Instance().SetMainThread();
    SR_HTYPES_NS::Time::Instance().Update();

    auto&& resourcesManager = ResourceManager::Instance();

    if (auto&& folder = GetCmdOption(argv, argv + argc, "-resources"); folder.empty()) {
        resourcesManager.Init(Path(exe.ToString() + "/../../Resources"));
    }
    else {
        resourcesManager.Init(folder);
    }

    Features::Instance().SetPath(resourcesManager.GetResPath().Concat("Engine/Configs/Features.xml"));
    Features::Instance().Reload();

    resourcesManager.Run();

    if (Features::Instance().Enabled("CrashHandler")) {
    #ifdef SR_WIN32
        ShellExecute(nullptr, "open", (ResourceManager::Instance().GetResPath().Concat(
                "Engine/Utilities/EngineCrashHandler.exe").CStr()),
                     ("--log log.txt --target " + SR_PLATFORM_NS::GetApplicationName().ToString() + " --out " + exe.ToString() + "\\").c_str(),
                     nullptr, SW_SHOWDEFAULT
        );
    #endif
    }

    {
        SceneAllocator::Instance().Init([]() -> Scene* { return new Core::World(); });
    }

    auto&& engine = SR_CORE_NS::Engine::Instance();

    if(engine.Create()) {
        if (engine.Init()) {
            if (!engine.Run()) {
                SR_ERROR("Failed to run game engine!");
            }
        }
        else {
            SR_ERROR("Failed to initialize game engine!");
        }
    }
    else {
        SR_ERROR("Failed to create game engine!");
    }

    if (engine.IsRun()) {
        SR_SYSTEM_LOG("All systems are successfully running!");

        engine.Await(); /// await close engine
    }

    engine.Close();

    SR_CORE_NS::EditorSettings::DestroySettings();
    SR_UTILS_NS::TagManager::DestroySettings();

    SR_PHYSICS_NS::PhysicsLibrary::DestroySingleton();
    SR_GRAPH_NS::Memory::CameraManager::DestroySingleton();
    SR_SCRIPTING_NS::GlobalEvoCompiler::DestroySingleton();
    SR_SCRIPTING_NS::EvoScriptManager::DestroySingleton();
    SR_UTILS_NS::EntityManager::DestroySingleton();
    SR_CORE_NS::Engine::DestroySingleton();
    SR_GRAPH_NS::GUI::NodeManager::DestroySingleton();
    SR_UTILS_NS::TaskManager::DestroySingleton();
    Memory::MeshManager::DestroySingleton();

    Debug::Instance().System("All systems were successfully closed!");

    ResourceManager::DestroySingleton();

    SR_SYSTEM_LOG("Thread count: " + ToString(Thread::Factory::Instance().GetThreadsCount()));

    Debug::DestroySingleton();

    return 0;
}