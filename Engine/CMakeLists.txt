cmake_minimum_required(VERSION 3.16)
project(SpaRcleEngine)

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

