cmake_minimum_required(VERSION 3.16)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT MSVC AND NOT ANDROID_NDK)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++20")
endif()

project(ImmediateGUI)

SR_COMMON_GENERATE_BUILD_SOURCES(${PROJECT_SOURCE_DIR})
SR_COMMON_GET_SOURCES(ImmediateGUI)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(SR_IMMEDIATE_GUI_DLL_EXPORTS "" ON)

if (SR_IMMEDIATE_GUI_STATIC_LIBRARY)
    add_library(ImmediateGUI STATIC ${ImmediateGUI_SOURCES})
else()
    add_library(ImmediateGUI SHARED ${ImmediateGUI_SOURCES})
    add_library(ImmediateGUI::lib ALIAS ImmediateGUI)

    if (UNIX)
        target_compile_options(ImmediateGUI PRIVATE -fPIC)

        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            target_link_libraries(ImmediateGUI atomic)
        endif()
    endif()

    target_link_libraries(ImmediateGUI Utils)

    SR_COPY_SHARED_MODULE_TO_EXECUTABLE_FOLDER(ImmediateGUI)
    SR_COPY_STATIC_LIBRARY_TO_LIBRARY_FOLDER(ImmediateGUI)
endif()

define_property(GLOBAL PROPERTY SR_IMMEDIATE_GUI_INCLUDE_DIRECTORIES
    BRIEF_DOCS "Contains linkable libraries"
    FULL_DOCS "Contains paths to libraries for linking"
)
set_property(GLOBAL PROPERTY SR_IMMEDIATE_GUI_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/inc")

target_include_directories(ImmediateGUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(ImmediateGUI PRIVATE libs)
target_include_directories(ImmediateGUI PRIVATE libs/imgui)
target_include_directories(ImmediateGUI PRIVATE libs/ImNodeFlow/include)

target_compile_definitions(ImmediateGUI PRIVATE SR_IMGUI_INCLUDE_CHECK)

if (SR_IMMEDIATE_GUI_DLL_EXPORTS)
    message("ImmediateGUI will be built as a shared library")
    target_compile_definitions(ImmediateGUI PUBLIC SR_IMMEDIATE_GUI_DLL_EXPORTS)
endif()

get_property(SR_UTILS_INCLUDE_DIRECTORIES_CONTENT GLOBAL PROPERTY SR_UTILS_INCLUDE_DIRECTORIES)
target_include_directories(ImmediateGUI PUBLIC ${SR_UTILS_INCLUDE_DIRECTORIES_CONTENT})

if (SR_USE_PCH)
    target_compile_definitions(ImmediateGUI PUBLIC SR_USE_PCH)
    target_precompile_headers(ImmediateGUI PUBLIC ${SR_COMMON_PCH_HEADER_PATH})
endif()

if (SR_RENDER_USE_VULKAN)
    message("$ENV{VULKAN_SDK}")
    find_package(Vulkan REQUIRED)
    target_include_directories(ImmediateGUI PRIVATE ${Vulkan_INCLUDE_DIRS})
    if (NOT SR_IMMEDIATE_GUI_STATIC_LIBRARY)
        target_link_libraries(ImmediateGUI ${Vulkan_LIBRARIES})
    endif()
endif()

set_target_properties(ImmediateGUI PROPERTIES
    BUILD_RPATH "\$ORIGIN"
    INSTALL_RPATH "\$ORIGIN"
)
