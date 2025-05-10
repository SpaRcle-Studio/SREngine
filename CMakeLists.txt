cmake_minimum_required(VERSION 3.16...3.16.2)
project(SREngine VERSION 0.0.7 LANGUAGES CXX DESCRIPTION "SpaRcle Engine - cross-platform 2D/3D game engine in C++.")

set_property(GLOBAL PROPERTY SR_ENGINE_VERSION_PROPERTY ${PROJECT_VERSION})
set_property(GLOBAL PROPERTY SR_ENGINE_MAJOR_VERSION_PROPERTY ${PROJECT_VERSION_MAJOR})
set_property(GLOBAL PROPERTY SR_ENGINE_MINOR_VERSION_PROPERTY ${PROJECT_VERSION_MINOR})
set_property(GLOBAL PROPERTY SR_ENGINE_PATCH_VERSION_PROPERTY ${PROJECT_VERSION_PATCH})

set(SR_ENGINE_EXTENDED_NAME ON)

if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "SpaRcle Engine supports only x64 systems!")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SR_BUILD_DEBUG_MODE ON)
    message(STATUS "SpaRcle Engine: Debug build mode enabled")
else()
    set(SR_BUILD_DEBUG_MODE OFF)
    message(STATUS "SpaRcle Engine: Release build mode enabled")
endif()

function(find_windows_sdk SR_WINDOWS_SDK_DIR)
    cmake_host_system_information(RESULT sdk_path QUERY WINDOWS_REGISTRY "HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v10.0" VALUE "InstallationFolder")
    cmake_path(CONVERT ${sdk_path} TO_CMAKE_PATH_LIST sdk_path)
    if(EXISTS ${sdk_path})
        set(${SR_WINDOWS_SDK_DIR} ${sdk_path} PARENT_SCOPE)
        return()
    endif()
    message(WARNING "Windows SDK path wasn't found in the registry. Searching on drives.")
    foreach(drive ${CMAKE_SYSTEM_NAME}:/ C D E F G H I J K L M N O P Q R S T U V W X Y Z)
        set(sdk_path "${drive}:/Program Files (x86)/Windows Kits/10")
        if(EXISTS ${sdk_path})
            set(${SR_WINDOWS_SDK_DIR} ${sdk_path} PARENT_SCOPE)
            return()
        endif()
    endforeach()
    message(FATAL_ERROR "Windows SDK wasn't found on any drive!")
endfunction()

function(find_latest_windows_sdk_version SR_WINDOWS_SDK_VERSION)
    file(GLOB SDK_VERSIONS LIST_DIRECTORIES true "${SR_WINDOWS_SDK_DIR}/Include/*")

    list(SORT SDK_VERSIONS)
    list(GET SDK_VERSIONS -1 LATEST_SDK_DIR)

    if (LATEST_SDK_DIR)
        string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+" LATEST_SDK_VERSION ${LATEST_SDK_DIR})
        set(${SR_WINDOWS_SDK_VERSION} ${LATEST_SDK_VERSION} PARENT_SCOPE)
    else()
        message(FATAL_ERROR "No valid Windows SDK versions found!")
    endif()
endfunction()

if (MSVC)
    get_filename_component(SR_MSVC_COMPILER_PATH "${CMAKE_CXX_COMPILER}" ABSOLUTE)
    message(STATUS "SpaRcle Engine: MSVC compiler path: ${SR_MSVC_COMPILER_PATH}")
    add_definitions(-DSR_MSVC_COMPILER_PATH="${SR_MSVC_COMPILER_PATH}")

    find_windows_sdk(SR_WINDOWS_SDK_DIR)
    find_latest_windows_sdk_version(SR_WINDOWS_SDK_VERSION)

    message(STATUS "SpaRcle Engine: Windows SDK path is ${SR_WINDOWS_SDK_DIR}")
    message(STATUS "SpaRcle Engine: Windows SDK version is ${SR_WINDOWS_SDK_VERSION}")

    add_definitions(-DSR_WINDOWS_SDK_DIR="${SR_WINDOWS_SDK_DIR}")
    add_definitions(-DSR_WINDOWS_SDK_VERSION="${SR_WINDOWS_SDK_VERSION}")
endif()

if (WIN32)
    set(SR_ENGINE_PLATFORM "Windows")
elseif(ANDROID_NDK)
    set(SR_ENGINE_PLATFORM "Android")
elseif(UNIX)
    set(SR_ENGINE_PLATFORM "Linux")
else()
    message(FATAL_ERROR "SpaRcle Engine: unsupported platform")
endif()

message(STATUS "SpaRcle Engine: current platform is ${SR_ENGINE_PLATFORM}")
message(STATUS "SpaRcle Engine: cmake version is ${CMAKE_VERSION}")

set(SR_CMAKE_ROOT_BUILD_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "SpaRcle Engine: root build directory is ${SR_CMAKE_ROOT_BUILD_DIRECTORY}")

set(SR_CMAKE_ROOT_SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "SpaRcle Engine: root source directory is ${SR_CMAKE_ROOT_SOURCE_DIRECTORY}")

set(SR_CMAKE_VENV_DIRECTORY "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/.venv")
message(STATUS "SpaRcle Engine: venv directory is ${SR_CMAKE_VENV_DIRECTORY}")

set(SR_CMAKE_RESOURCES_DIRECTORY "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/Resources")
message(STATUS "SpaRcle Engine: resources directory is ${SR_CMAKE_RESOURCES_DIRECTORY}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines-ts")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")

add_definitions(
    -DSR_ICU
    -DSR_USE_IMGUI
    -DSR_USE_VULKAN
    -DSR_SUPPORT_PARALLEL
    -DSR_CXX_20
)

if (ANDROID_NDK)
    add_compile_options(-Wno-c++20-attribute-extensions)
    add_definitions(-Wno-c++20-attribute-extensions)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++20-attribute-extensions")
else()
    if (UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcompare-debug-second -w -Wno-deprecated -fPIC")
    endif()

    if (UNIX AND SR_BUILD_DEBUG_MODE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-pie -no-pie -g3")
    endif()
endif()

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX")
endif()

if (SR_DISABLE_EXCEPTIONS)
    # TODO: not working
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
        message(STATUS "Using GNU compiler: -fno-exceptions enabled")
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHs")
        message(STATUS "Using MSVC compiler: /EHs enabled")
    else()
        message(WARNING "Unknown compiler, exceptions handling settings may not be correct")
    endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSR_UTILS_ASSIMP")

if (ANDROID_NDK)
    set(SR_ENGINE_USE_MODULAR_BUILD OFF)
else()
    set(SR_ENGINE_USE_MODULAR_BUILD ON)
endif()

if (SR_ENGINE_USE_MODULAR_BUILD)
    set(SR_COMMON_STATIC_LIBRARY OFF)
    set(SR_SCRIPTING_STATIC_LIBRARY OFF)
    set(SR_AUDIO_STATIC_LIBRARY OFF)
    set(SR_PHYSICS_STATIC_LIBRARY OFF)
    set(SR_GRAPHICS_STATIC_LIBRARY OFF)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSR_COMMON_DLL_EXPORTS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSR_SCRIPTING_DLL_EXPORTS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSR_AUDIO_DLL_EXPORTS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSR_PHYSICS_DLL_EXPORTS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSR_GRAPHICS_DLL_EXPORTS")
    set(SR_COMMON_STATIC_LIBRARY ON)
    set(SR_SCRIPTING_STATIC_LIBRARY ON)
    set(SR_AUDIO_STATIC_LIBRARY ON)
    set(SR_PHYSICS_STATIC_LIBRARY ON)
    set(SR_GRAPHICS_STATIC_LIBRARY ON)
endif()

set(SR_PHYSICS_USE_BULLET3 OFF)
set(SR_PHYSICS_USE_PHYSX ON)
set(SR_PHYSICS_USE_BOX2D OFF)

set(EVO_VULKAN_STATIC_LIBRARY ON)

set(SR_TRACY_ENABLE ON)

set(SR_ICU ON)

set(CMAKE_BUILD_PARALLEL_LEVEL 0)

set(CMAKE_SHARED_LINKER_FLAGS_CHECKED "")
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "")
set(CMAKE_EXE_LINKER_FLAGS_PROFILE "")
set(CMAKE_EXE_LINKER_FLAGS_CHECKED "")

add_subdirectory(Engine)

if (EXISTS ${SR_CMAKE_RESOURCES_DIRECTORY}/CMakeLists.txt)
    message(STATUS "SpaRcle Engine: adding Resources subdirectory")
    add_subdirectory(${SR_CMAKE_RESOURCES_DIRECTORY})
else()
    message(STATUS "SpaRcle Engine: Resources subdirectory not found")
endif()