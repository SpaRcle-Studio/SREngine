#include <Utils/stdInclude.h>

#include "../../Utils/src/Utils/SRLM/LogicalMachine.cpp"
#include "../../Utils/src/Utils/SRLM/DataType.cpp"
#include "../../Utils/src/Utils/SRLM/DataTypeManager.cpp"
#include "../../Utils/src/Utils/SRLM/DataOperators.cpp"
#include "../../Utils/src/Utils/SRLM/LogicalNode.cpp"
#include "../../Utils/src/Utils/SRLM/LogicalNodes.cpp"
#include "../../Utils/src/Utils/SRLM/LogicalNodeManager.cpp"
#include "../../Utils/src/Utils/SRLM/ConvertorNode.cpp"

#include "../../Utils/src/Utils/Events/EventManager.cpp"
#include "../../Utils/src/Utils/Events/Event.cpp"
#include "../../Utils/src/Utils/Events/EventDispatcher.cpp"

#include "../../Utils/src/Utils/FileSystem/FileSystem.cpp"
#include "../../Utils/src/Utils/FileSystem/Path.cpp"
#include "../../Utils/src/Utils/FileSystem/FileDialog.cpp"
#include "../../Utils/src/Utils/FileSystem/AssimpCache.cpp"

#include "../../Utils/src/Utils/Input/InputSystem.cpp"
#include "../../Utils/src/Utils/Input/InputDispatcher.cpp"
#include "../../Utils/src/Utils/Input/InputDevice.cpp"
#include "../../Utils/src/Utils/Input/InputHandler.cpp"

#include "../../Utils/src/Utils/Math/Matrix3x3.cpp"
#include "../../Utils/src/Utils/Math/Matrix4x4.cpp"
#include "../../Utils/src/Utils/Math/Quaternion.cpp"
#include "../../Utils/src/Utils/Math/Vector3.cpp"
#include "../../Utils/src/Utils/Math/Vector6.cpp"
#include "../../Utils/src/Utils/Math/Noise.cpp"
#include "../../Utils/src/Utils/Math/Rect.cpp"

#include "../../Utils/src/Utils/TaskManager/TaskManager.cpp"

#include "../../Utils/src/Utils/Settings.cpp"
#include "../../Utils/src/Utils/DebugDraw.cpp"
#include "../../Utils/src/Utils/Debug.cpp"
#include "../../Utils/src/Utils/Xml.cpp"

#include "../../Utils/src/Utils/ResourceManager/FileWatcher.cpp"
#include "../../Utils/src/Utils/ResourceManager/IResource.cpp"
#include "../../Utils/src/Utils/ResourceManager/ResourceInfo.cpp"
#include "../../Utils/src/Utils/ResourceManager/ResourcesHolder.cpp"
#include "../../Utils/src/Utils/ResourceManager/ResourceManager.cpp"
#include "../../Utils/src/Utils/ResourceManager/ResourceContainer.cpp"
#include "../../Utils/src/Utils/ResourceManager/IResourceReloader.cpp"

#include "../../Utils/src/Utils/CommandManager/ICommand.cpp"
#include "../../Utils/src/Utils/CommandManager/CmdManager.cpp"
#include "../../Utils/src/Utils/CommandManager/ReversibleCommand.cpp"

#include "../../Utils/src/Utils/Types/String.cpp"
#include "../../Utils/src/Utils/Types/Time.cpp"
#include "../../Utils/src/Utils/Types/Time.cpp"
#include "../../Utils/src/Utils/Types/Marshal.cpp"
#include "../../Utils/src/Utils/Types/EDMarshal.cpp"
#include "../../Utils/src/Utils/Types/Thread.cpp"
#include "../../Utils/src/Utils/Types/SafeQueue.cpp"
#include "../../Utils/src/Utils/Types/RawMesh.cpp"
#include "../../Utils/src/Utils/Types/UnicodeString.cpp"
#include "../../Utils/src/Utils/Types/Stream.cpp"
#include "../../Utils/src/Utils/Types/Regex.cpp"
#include "../../Utils/src/Utils/Types/IRawMeshHolder.cpp"
#include "../../Utils/src/Utils/Types/Mutex.cpp"
#include "../../Utils/src/Utils/Types/LockGuard.cpp"

#include "../../Utils/src/Utils/Common/Stacktrace.cpp"
#include "../../Utils/src/Utils/Common/StringUtils.cpp"
#include "../../Utils/src/Utils/Common/Features.cpp"
#include "../../Utils/src/Utils/Common/Singleton.cpp"
#include "../../Utils/src/Utils/Common/SingletonHolder.cpp"
#include "../../Utils/src/Utils/Common/Enumerations.cpp"
#include "../../Utils/src/Utils/Common/EnumReflector.cpp"
#include "../../Utils/src/Utils/Common/Hashes.cpp"
#include "../../Utils/src/Utils/Common/HashManager.cpp"
#include "../../Utils/src/Utils/Common/Vertices.cpp"

#include "../../Utils/src/Utils/Game/LookAtComponent.cpp"

#ifdef SR_TRACY_ENABLE
    #include "../../Utils/src/Utils/Profile/TracyContext.cpp"
#endif

#include "../../Utils/libs/xxHash/xxhash.c"