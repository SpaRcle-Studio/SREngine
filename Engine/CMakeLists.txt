cmake_minimum_required(VERSION 3.16)
project(SpaRcleEngine)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/TargetArchitecture.cmake)
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
option(SR_ENGINE_EXTENDED_NAME "" ON)

if (SR_ENGINE_FLATPAK_BUILD)
    add_compile_definitions(SR_ENGINE_FLATPAK_BUILD)
endif()

# TODO!
#add_compile_definitions(_CONTAINER_DEBUG_LEVEL=0)
#add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)

add_definitions(
    -DSR_ICU
    -DSR_USE_IMGUI
    -DSR_USE_IMGUIZMO
    #-DSR_USE_IMGUI_NODE_EDITOR
    -DSR_USE_VULKAN
    -DSR_DLL_EXPORTS
    -DSR_SUPPORT_PARALLEL
    -DSR_CXX_20
)

set(SR_UTILS_ASSIMP ON CACHE INTERNAL "" FORCE)
set(SR_UTILS_DLL_EXPORTS ON CACHE INTERNAL "" FORCE)

if (SR_TRACY_ENABLE)
    add_definitions(
        -DSR_TRACY_ENABLE
        -DTRACY_ON_DEMAND
        -DTRACY_ENABLE
    )
endif()

add_subdirectory(Core)

if (CMAKE_GENERATOR MATCHES "Visual Studio")
    add_executable(SREngine main.cpp)
else()
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")

    add_executable(SREngine
        main.cpp
        ${APP_ICON_RESOURCE_WINDOWS}
    )
endif()

add_custom_command(TARGET SREngine
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -DTARGET_NAME=Engine
    -DTARGET_PATH=${CMAKE_BINARY_DIR}
    -P ${CMAKE_SOURCE_DIR}/Engine/cmake/PostBuild.cmake
    COMMENT "Running SpaRcle engine post-build script..."
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(SREngine Core)

# TODO: implement an easy way to set if a build is 'stable' or 'latest'
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(executableType "stable")
else()
    set(executableType "latest")
endif()

if (SR_ENGINE_FLATPAK_BUILD)
    install(SREngine DESTINATION /app/bin)
    install(SREngine PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
endif()

if (SR_ENGINE_EXTENDED_NAME)
    if (UNIX AND NOT APPLE)
        set_target_properties(SREngine PROPERTIES OUTPUT_NAME "SREngine_v${SR_ENGINE_VERSION}-${executableType}_linux.${CURRENT_TARGET_ARCHITECTURE}")
    elseif (WIN32)
        set_target_properties(SREngine PROPERTIES OUTPUT_NAME "SREngine_v${SR_ENGINE_VERSION}-${executableType}_windows.${CURRENT_TARGET_ARCHITECTURE}")
    endif()
else()
    set_target_properties(SREngine PROPERTIES OUTPUT_NAME "srengine")
endif()
