//
// Created by Nikita on 29.12.2020.
// Looked by Drakeme on 26.06.2022.
// Changed by Monika on 20.11.2022
// Approved by innerviewer on 03.09.2023
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
#include <Utils/SRLM/LogicalMachine.h>

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
#include <Graphics/Memory/CameraManager.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Types/RenderTexture.h>
#include <Graphics/Font/Font.h>

#include <Physics/Rigidbody.h>
#include <Physics/PhysicsScene.h>
#include <Physics/PhysicsLib.h>

#include <Audio/SoundManager.h>

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Impl/EvoScriptManager.h>

int main(int argc, char **argv) {
    setlocale(LC_ALL, "rus");
    setlocale(LC_NUMERIC, "C");
    srand(time(NULL));

    auto&& exe = SR_PLATFORM_NS::GetApplicationPath().GetFolder();
    SR_UTILS_NS::Debug::Instance().Init(exe, true, SR_UTILS_NS::Debug::Theme::Dark);
    SR_UTILS_NS::Debug::Instance().SetLevel(SR_UTILS_NS::Debug::Level::Low);

    SR_PLATFORM_NS::InitSegmentationHandler();

    SR_HTYPES_NS::Thread::Factory::Instance().SetMainThread();
    SR_HTYPES_NS::Time::Instance().Update();

    auto&& resourcesManager = SR_UTILS_NS::ResourceManager::Instance();

    if (auto&& folder = SR_UTILS_NS::GetCmdOption(argv, argv + argc, "-resources"); folder.empty()) {
        resourcesManager.Init(SR_UTILS_NS::Path(exe.ToString() + "/../../Resources"));
    }
    else {
        resourcesManager.Init(folder);
    }

    SR_UTILS_NS::Features::Instance().SetPath(resourcesManager.GetResPath().Concat("Engine/Configs/Features.xml"));
    SR_UTILS_NS::Features::Instance().Reload();

    resourcesManager.Run();

    SR_WORLD_NS::SceneAllocator::Instance().Init([]() -> SR_WORLD_NS::Scene* {
        return new SR_CORE_NS::World();
    });

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

    SR_SRLM_NS::DataTypeManager::DestroySingleton();

    SR_CORE_NS::EditorSettings::DestroySettings();
    SR_UTILS_NS::TagManager::DestroySettings();

    SR_AUDIO_NS::SoundManager::DestroySingleton();
    SR_PHYSICS_NS::PhysicsLibrary::DestroySingleton();
    SR_GRAPH_NS::Memory::CameraManager::DestroySingleton();
    SR_SCRIPTING_NS::GlobalEvoCompiler::DestroySingleton();
    SR_SCRIPTING_NS::EvoScriptManager::DestroySingleton();
    SR_UTILS_NS::EntityManager::DestroySingleton();
    SR_CORE_NS::Engine::DestroySingleton();
    SR_GRAPH_NS::GUI::NodeManager::DestroySingleton();
    SR_UTILS_NS::TaskManager::DestroySingleton();
    SR_GRAPH_NS::Memory::MeshManager::DestroySingleton();

    SR_UTILS_NS::Debug::Instance().System("All systems were successfully closed!");

    SR_UTILS_NS::ResourceManager::DestroySingleton();

    SR_HTYPES_NS::Thread::Factory::Instance().PrintThreads();

    SR_UTILS_NS::Debug::DestroySingleton();

    return 0;
}