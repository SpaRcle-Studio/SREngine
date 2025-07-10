cmake_minimum_required(VERSION 3.16...3.16.2)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT MSVC AND NOT ANDROID_NDK)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++20")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(SREngine VERSION 1.0.0 LANGUAGES CXX DESCRIPTION "SpaRcle Engine - cross-platform 2D/3D game engine in C++.")

set_property(GLOBAL PROPERTY SR_ENGINE_VERSION_PROPERTY ${PROJECT_VERSION})
set_property(GLOBAL PROPERTY SR_ENGINE_MAJOR_VERSION_PROPERTY ${PROJECT_VERSION_MAJOR})
set_property(GLOBAL PROPERTY SR_ENGINE_MINOR_VERSION_PROPERTY ${PROJECT_VERSION_MINOR})
set_property(GLOBAL PROPERTY SR_ENGINE_PATCH_VERSION_PROPERTY ${PROJECT_VERSION_PATCH})

set(SR_ENGINE_EXTENDED_NAME ON)

if (EMSCRIPTEN)
    set(SR_EMSCRIPTEN ON)
    add_definitions(-DSR_EMSCRIPTEN)
    message(STATUS "SpaRcle Engine: Emscripten build mode enabled")
else()
    set(SR_EMSCRIPTEN OFF)
endif()

message(STATUS "SpaRcle Engine: Host system: ${CMAKE_HOST_SYSTEM_NAME}")

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(SR_HOST_SYSTEM_WINDOWS ON)
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(SR_HOST_SYSTEM_LINUX ON)
    set(SR_HOST_SYSTEM_UNIX ON)
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    set(SR_HOST_SYSTEM_MAC ON)
    set(SR_HOST_SYSTEM_UNIX ON)
else()
    message(FATAL_ERROR "SpaRcle Engine: unsupported host system!")
endif()

if (NOT SR_EMSCRIPTEN AND NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "SpaRcle Engine supports only x64 systems!")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SR_BUILD_DEBUG_MODE ON)
    message(STATUS "SpaRcle Engine: Debug build mode enabled")
else()
    set(SR_BUILD_DEBUG_MODE OFF)
    message(STATUS "SpaRcle Engine: Release build mode enabled")
endif()

include(Engine/cmake/WindowsSDK.cmake)

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

if (ANDROID_NDK)
    set(SR_EXECUTABLE_NAME "sparcle")
else()
    set(SR_EXECUTABLE_DIR "${SR_CMAKE_ROOT_BUILD_DIRECTORY}/Bin")
    set(SR_EXECUTABLE_NAME "SREngine")
endif()

set(SR_OUTPUT_LIBRARY_DIR "${SR_CMAKE_ROOT_BUILD_DIRECTORY}/Lib")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines-ts")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")

add_definitions(
    -DSR_ICU
    -DSR_USE_IMGUI
    -DSR_USE_VULKAN
    -DSR_CXX_20
)

if (NOT SR_EMSCRIPTEN AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_definitions(-DSR_SUPPORT_PARALLEL)
endif()

if (ANDROID_NDK)
    add_compile_options(-Wno-c++20-attribute-extensions)
    add_definitions(-Wno-c++20-attribute-extensions)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++20-attribute-extensions")
else()
    if (UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -Wno-deprecated -fPIC")
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

include(Engine/cmake/ModularBuild.cmake)

set(SR_PHYSICS_USE_BULLET3 OFF)
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
