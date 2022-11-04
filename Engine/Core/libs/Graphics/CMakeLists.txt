cmake_minimum_required(VERSION 3.16)
project(Graphics)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(BUILD_SHARED_LIBS ON)
set(FT_CONFIG_OPTION_USE_ZLIB OFF)
set(FT_DISABLE_HARFBUZZ ON)

message("Vulkan sdk path: $ENV{VULKAN_SDK}")

if (CYGWIN)
    #include_directories("$ENV{VULKAN_SDK}/Include")
else()
    include_directories(${Vulkan_INCLUDE_DIRS})
    find_package(Vulkan REQUIRED)
endif()

add_subdirectory(libs/EvoVulkan)

add_subdirectory(libs/harfbuzz)
add_subdirectory(libs/freetype)

if (SR_GRAPHICS_STATIC_LIBRARY)
    add_library(Graphics STATIC Graphics.cxx ImGUI.cxx)

    if (CYGWIN)
        target_link_libraries(Graphics "$ENV{VULKAN_SDK}/Lib/vulkan-1.lib")
    else()

    endif()
else()
    if (MINGW)
        target_link_libraries(Graphics ${Vulkan_LIBRARY} Dwmapi.lib)
    else()
        target_link_libraries(Graphics ${Vulkan_LIBRARY})
    endif()

    add_library(Graphics SHARED Graphics.cxx inc/Graphics/Font/FreeType.h)
    add_library(Graphics::lib ALIAS Graphics)
endif()

target_link_libraries(Graphics CMP_Core freetype harfbuzz)

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
target_include_directories(Graphics PUBLIC libs/imgui-node-editor)
target_include_directories(Graphics PUBLIC libs/ImGuizmo)
#target_include_directories(Graphics PUBLIC libs/glew/inc)
target_include_directories(Graphics PUBLIC libs)
target_include_directories(Graphics PUBLIC  ${Vulkan_INCLUDE_DIRS})
target_include_directories(Graphics PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include)
target_include_directories(Graphics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Utils/libs)
target_include_directories(Graphics PUBLIC  ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include/icu)

