cmake_minimum_required(VERSION 3.16)
project(SpaRcleEngine)

add_definitions(
    -DSR_ICU
    -DSR_USE_IMGUI
    -DSR_USE_IMGUIZMO
    -DSR_USE_IMGUI_NODE_EDITOR
    -DSR_USE_VULKAN
    -DSR_SUPPORT_PARALLEL
    -DSR_DLL_EXPORTS=1
    -DSR_CXX_20
)

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
        -P ${CMAKE_SOURCE_DIR}/Engine/post_build.cmake
        COMMENT "Running SpaRcle engine post-build script..."
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(SREngine Core)

