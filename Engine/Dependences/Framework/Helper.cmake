
set(HELPER_SRC
        #Debuger/Logger source code
        ${FRAMEWORK_ROOT_DIR}/Helper/src/Debug.cpp
        #Resource Manager source code
        ${FRAMEWORK_ROOT_DIR}/Helper/src/FileSystem/OldFileSystem.cpp
        ${FRAMEWORK_ROOT_DIR}/Helper/src/ResourceManager/ResourceManager.cpp
        ${FRAMEWORK_ROOT_DIR}/Helper/src/ResourceManager/IResource.cpp
        #Mathematical classes source code
        ${FRAMEWORK_ROOT_DIR}/Helper/src/Math/Vector2.cpp
        ${FRAMEWORK_ROOT_DIR}/Helper/src/Math/Vector3.cpp
        ${FRAMEWORK_ROOT_DIR}/Helper/src/Math/Quaternion.cpp
        ${FRAMEWORK_ROOT_DIR}/Helper/src/Math/Matrix3x3.cpp
        ${FRAMEWORK_ROOT_DIR}/Helper/src/Types/String.cpp
        #Input classes source code
        ${FRAMEWORK_ROOT_DIR}/Helper/src/Input/Input.cpp

        ${FRAMEWORK_ROOT_DIR}/Helper/src/Utils/StringUtils.cpp

        ${FRAMEWORK_ROOT_DIR}/Helper/src/EntityComponentSystem/GameObject.cpp
        ${FRAMEWORK_ROOT_DIR}/Helper/src/EntityComponentSystem/Component.cpp
        ${FRAMEWORK_ROOT_DIR}/Helper/src/EntityComponentSystem/Transform.cpp
        ${FRAMEWORK_ROOT_DIR}/Helper/src/EntityComponentSystem/Scene.cpp
        )

if(WIN32)
    set(HELPER_SRC ${HELPER_SRC}
        ${FRAMEWORK_ROOT_DIR}/Helper/src/FileSystem/Windows/FileSystem.cpp)

elseif(UNIX)
    set(HELPER_SRC ${HELPER_SRC}
        ${FRAMEWORK_ROOT_DIR}/Helper/src/FileSystem/Linux/FileSystem.cpp)

endif()


set(HELPER_INC_PUBLIC
        ${FRAMEWORK_ROOT_DIR}/Helper/inc
        )

set(HELPER_INC_PRIVATE)

set(HELPER_INC_INSTANCE)
