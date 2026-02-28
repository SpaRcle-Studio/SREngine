cmake_minimum_required(VERSION 3.16)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT MSVC AND NOT ANDROID_NDK)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++20")
endif()

project(SpaRcleEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/TargetArchitecture.cmake)
include(cmake/InstallPython.cmake)
include(cmake/Codegen.cmake)

SRCodegen()

target_architecture(CURRENT_TARGET_ARCHITECTURE)
message(STATUS "SpaRcle Engine: current build target architecture: ${CURRENT_TARGET_ARCHITECTURE}")
message(STATUS "SpaRcle Engine: current build type: ${CMAKE_BUILD_TYPE}")

get_property(SR_ENGINE_VERSION GLOBAL PROPERTY SR_ENGINE_VERSION_PROPERTY)
get_property(SR_ENGINE_MAJOR_VERSION GLOBAL PROPERTY SR_ENGINE_MAJOR_VERSION_PROPERTY)
get_property(SR_ENGINE_MINOR_VERSION GLOBAL PROPERTY SR_ENGINE_MINOR_VERSION_PROPERTY)
get_property(SR_ENGINE_PATCH_VERSION GLOBAL PROPERTY SR_ENGINE_PATCH_VERSION_PROPERTY)

message(STATUS "SpaRcle Engine: current version is ${SR_ENGINE_VERSION}")
message(STATUS "SpaRcle Engine: C compiler is '${CMAKE_C_COMPILER}'")
message(STATUS "SpaRcle Engine: C++ compiler is '${CMAKE_CXX_COMPILER}'")

option(SR_ENGINE_FLATPAK_BUILD "" OFF)

if (SR_ENGINE_FLATPAK_BUILD)
    add_compile_definitions(SR_ENGINE_FLATPAK_BUILD)
endif()

if (NOT SR_ENGINE_FLATPAK_BUILD AND NOT ANDROID_NDK)
    set(SR_ENGINE_EXTENDED_NAME ON)
endif()

include(cmake/EngineCore.cmake)
include(cmake/Executable.cmake)
