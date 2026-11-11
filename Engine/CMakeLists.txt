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

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_options(
        "$<$<CONFIG:Release>:-ffunction-sections>"
        "$<$<CONFIG:Release>:-fdata-sections>"
    )
    add_link_options("$<$<CONFIG:Release>:LINKER:--strip-all>")
    add_link_options("$<$<CONFIG:Release>:LINKER:--gc-sections>")
endif()

include(cmake/EngineCore.cmake)
include(cmake/Executable.cmake)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND SR_ENGINE_EXPLICIT_DLL_EXPORTS)
    foreach(SR_VISIBILITY_MODULE IN ITEMS Utils ImmediateGUI Audio Physics Graphics Scripting Engine)
        set_target_properties(${SR_VISIBILITY_MODULE} PROPERTIES
            C_VISIBILITY_PRESET hidden
            CXX_VISIBILITY_PRESET hidden
        )
    endforeach()
endif()

if (SR_ENGINE_USE_MODULAR_BUILD)
    # Link replacements into every shared engine module on each platform.
    foreach(SR_MEMORY_MODULE IN ITEMS ImmediateGUI Audio Physics Graphics Scripting Engine)
        if (TARGET ${SR_MEMORY_MODULE})
            get_target_property(SR_MEMORY_MODULE_TYPE ${SR_MEMORY_MODULE} TYPE)
            if (SR_MEMORY_MODULE_TYPE STREQUAL "SHARED_LIBRARY")
                target_sources(${SR_MEMORY_MODULE} PRIVATE
                    "${CMAKE_CURRENT_SOURCE_DIR}/libs/Utils/src/Utils/Memory/GlobalMemoryOperators.cpp"
                )
            endif()
        endif()
    endforeach()
endif()

option(SR_ENGINE_GENERATE_MAP "Generate MSVC linker MAP files for shared engine modules" OFF)

if (MSVC AND SR_ENGINE_GENERATE_MAP)
    foreach(SR_MAP_MODULE IN ITEMS Utils ImmediateGUI Audio Physics Graphics Scripting Engine)
        get_target_property(SR_MAP_MODULE_TYPE ${SR_MAP_MODULE} TYPE)
        if (SR_MAP_MODULE_TYPE STREQUAL "SHARED_LIBRARY")
            target_link_options(${SR_MAP_MODULE} PRIVATE
                "/MAP:$<TARGET_FILE_DIR:${SR_MAP_MODULE}>/$<TARGET_FILE_BASE_NAME:${SR_MAP_MODULE}>.map"
            )
        endif()
    endforeach()
endif()
