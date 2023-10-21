cmake_minimum_required(VERSION 3.16)
project(Graphics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

if (NOT ANDROID_NDK)
    set(BUILD_SHARED_LIBS ON)
endif()

set(FT_CONFIG_OPTION_USE_ZLIdB OFF)
set(FT_DISABLE_HARFBUZZ ON)

message("$ENV{VULKAN_SDK}")

find_package(Vulkan REQUIRED)

add_subdirectory(libs/EvoVulkan/Core)

if (ANDROID_NDK)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-function -Wunused-function -Wno-comment -Wunused-variable")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unused-function -Wunused-function -Wno-comment -Wunused-variable")
endif()

include(freetype.cmake)

add_subdirectory(libs/cmp_core)

set(SR_GRAPHICS_SOURCES cxx/Graphics.cxx cxx/ImGUI.cxx cxx/SRSL.cxx cxx/Pass.cxx cxx/GUI.cxx cxx/Animations.cxx)

if (SR_GRAPHICS_STATIC_LIBRARY)
    add_library(Graphics STATIC ${SR_GRAPHICS_SOURCES})

    if (CYGWIN)
        target_link_libraries(Graphics "$ENV{VULKAN_SDK}/Lib/vulkan-1.lib")
    else()

    endif()
else()
    if (MINGW)
        target_link_libraries(Graphics ${Vulkan_LIBRARY} Dwmapi.lib)
    else()
        if (ANDROID_NDK)

        else()
            target_link_libraries(Graphics ${Vulkan_LIBRARY})
        endif()
    endif()

    add_library(Graphics SHARED ${SR_GRAPHICS_SOURCES})
    add_library(Graphics::lib ALIAS Graphics)
endif()

target_link_libraries(Graphics CMP_Core freetype)

if (EVO_VULKAN_STATIC_LIBRARY)
    target_link_libraries(Graphics EvoVulkan)
else()
    target_link_libraries(Graphics EvoVulkan::lib)
endif()

target_include_directories(Graphics PUBLIC inc)
target_include_directories(Graphics PUBLIC libs/EvoVulkan/Core/inc)
target_include_directories(Graphics PUBLIC libs/cmp_core/source)
target_include_directories(Graphics PUBLIC libs/inc)
target_include_directories(Graphics PUBLIC libs/imgui)
#target_include_directories(Graphics PUBLIC libs/imgui-node-editor)
target_include_directories(Graphics PUBLIC libs/ImGuizmo)
#target_include_directories(Graphics PUBLIC libs/glew/inc)
target_include_directories(Graphics PUBLIC libs)
target_include_directories(Graphics PUBLIC  ${Vulkan_INCLUDE_DIRS})
target_include_directories(Graphics PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include)
target_include_directories(Graphics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Utils/libs)
target_include_directories(Graphics PUBLIC  ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include/icu)
target_include_directories(Graphics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Utils/libs/assimp/include)
target_include_directories(Graphics PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/libs/assimp/include)
target_include_directories(Graphics PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include/tracy/tracy)
