#include <Utils/stdInclude.h>

#ifdef SR_WIN32
    #include "../Utils/src/Utils/Platform/PlatformWindows.cpp"
#endif

#ifdef SR_ANDROID
    #include "../Utils/src/Utils/Platform/PlatformAndroid.cpp"
    #include "../Utils/src/Utils/Platform/AndroidNativeAppGlue.c"
#endif

#include "../Utils/src/Utils/ECS/Component.cpp"
#include "../Utils/src/Utils/ECS/IComponentable.cpp"
#include "../Utils/src/Utils/ECS/ComponentManager.cpp"
#include "../Utils/src/Utils/ECS/GameObject.cpp"
#include "../Utils/src/Utils/ECS/ISavable.cpp"
#include "../Utils/src/Utils/ECS/Transform.cpp"
#include "../Utils/src/Utils/ECS/EntityManager.cpp"
#include "../Utils/src/Utils/ECS/Transform3D.cpp"
#include "../Utils/src/Utils/ECS/Transform2D.cpp"
#include "../Utils/src/Utils/ECS/EntityRef.cpp"
#include "../Utils/src/Utils/ECS/Prefab.cpp"

#include "../Utils/src/Utils/Events/EventManager.cpp"
#include "../Utils/src/Utils/Events/Event.cpp"
#include "../Utils/src/Utils/Events/EventDispatcher.cpp"

#include "../Utils/src/Utils/FileSystem/FileSystem.cpp"
#include "../Utils/src/Utils/FileSystem/Path.cpp"
#include "../Utils/src/Utils/FileSystem/FileDialog.cpp"

#include "../Utils/src/Utils/Input/InputSystem.cpp"
#include "../Utils/src/Utils/Input/InputDispatcher.cpp"
#include "../Utils/src/Utils/Input/InputDevice.cpp"
#include "../Utils/src/Utils/Input/InputHandler.cpp"

#include "../Utils/src/Utils/Math/Matrix3x3.cpp"
#include "../Utils/src/Utils/Math/Quaternion.cpp"
#include "../Utils/src/Utils/Math/Vector3.cpp"
#include "../Utils/src/Utils/Math/Vector6.cpp"
#include "../Utils/src/Utils/Math/Noise.cpp"
#include "../Utils/src/Utils/Math/Rect.cpp"

#include "../Utils/src/Utils/TaskManager/TaskManager.cpp"

#include "../Utils/src/Utils/Settings.cpp"
#include "../Utils/src/Utils/DebugDraw.cpp"
#include "../Utils/src/Utils/Debug.cpp"
#include "../Utils/src/Utils/Xml.cpp"

#include "../Utils/src/Utils/ResourceManager/IResource.cpp"
#include "../Utils/src/Utils/ResourceManager/ResourceInfo.cpp"
#include "../Utils/src/Utils/ResourceManager/ResourcesHolder.cpp"
#include "../Utils/src/Utils/ResourceManager/ResourceManager.cpp"

#include "../Utils/src/Utils/CommandManager/ICommand.cpp"
#include "../Utils/src/Utils/CommandManager/CmdManager.cpp"
#include "../Utils/src/Utils/CommandManager/ReversibleCommand.cpp"

#include "../Utils/src/Utils/Types/String.cpp"
#include "../Utils/src/Utils/Types/Time.cpp"
#include "../Utils/src/Utils/Types/Time.cpp"
#include "../Utils/src/Utils/Types/Marshal.cpp"
#include "../Utils/src/Utils/Types/EDMarshal.cpp"
#include "../Utils/src/Utils/Types/Thread.cpp"
#include "../Utils/src/Utils/Types/SafeQueue.cpp"
#include "../Utils/src/Utils/Types/RawMesh.cpp"
#include "../Utils/src/Utils/Types/UnicodeString.cpp"

#include "../Utils/src/Utils/Common/Stacktrace.cpp"
#include "../Utils/src/Utils/Common/StringUtils.cpp"
#include "../Utils/src/Utils/Common/Features.cpp"
#include "../Utils/src/Utils/Common/Singleton.cpp"
#include "../Utils/src/Utils/Common/SingletonHolder.cpp"
#include "../Utils/src/Utils/Common/Enumerations.cpp"
#include "../Utils/src/Utils/Common/EnumReflector.cpp"
#include "../Utils/src/Utils/Common/Hashes.cpp"

#include "../Utils/src/Utils/World/Chunk.cpp"
#include "../Utils/src/Utils/World/Observer.cpp"
#include "../Utils/src/Utils/World/Region.cpp"
#include "../Utils/src/Utils/World/Scene.cpp"
#include "../Utils/src/Utils/World/SceneBuilder.cpp"
#include "../Utils/src/Utils/World/SceneAllocator.cpp"
#include "../Utils/src/Utils/World/SceneLogic.cpp"
#include "../Utils/src/Utils/World/SceneCubeChunkLogic.cpp"
#include "../Utils/src/Utils/World/SceneDefaultLogic.cpp"
