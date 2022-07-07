cmake_minimum_required(VERSION 3.16)
project(Framework)

set(CMAKE_CXX_STANDARD 20)

#SET(CMAKE_CXX_FLAGS_DEBUG  "-mbig-obj -O2")

if (MINGW)

else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()

# Переменная дириктории исходного кода данного фреймворка
set(FRAMEWORK_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(IMGUI_ROOT_DIR ${FRAMEWORK_ROOT_DIR}/Depends/imgui)
set(IMGUIZMO_ROOT_DIR ${FRAMEWORK_ROOT_DIR}/Depends/ImGuizmo)
set(IMGUI_NODE_EDITOR_ROOT_DIR ${FRAMEWORK_ROOT_DIR}/Depends/imgui-node-editor)

# Включаем вспомогательные файлы
include(Graphics.cmake)
include(Physics.cmake)
include(Scripting.cmake)

#add_subdirectory(Depends/imgui)

add_subdirectory(Depends/glfw)
add_subdirectory(Depends/glew/build/cmake)

#add_subdirectory(Depends/pugixml)
#add_subdirectory(Depends/inc/glm)

add_subdirectory(Depends/EvoVulkan/Core)
add_subdirectory(Depends/EvoScript/Core)
add_subdirectory(Depends/cmp_core)
add_subdirectory(Utils)
add_subdirectory(Audio)

#include(Depends/bullet3/UseBullet.cmake)

#add_subdirectory(Depends/bullet3)

#add_subdirectory(Depends/glfw)
#add_subdirectory(Depends/glew/build/cmake)

find_package(OpenGL REQUIRED)
#find_package(Vulkan REQUIRED FATAL_ERROR)

#find_package(PythonLibs REQUIRED)
#find_package(Lua51 REQUIRED)

#include_directories(${LUA_INCLUDE_DIR})

#include_directories(${PYTHON_INCLUDE_DIRS})

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Depends/vulkan/lib/vulkan-1.lib
#        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

# Добавляем библиотеку фреймворка
add_library(Framework STATIC ${GRAPHICS_SRC} ${PHYSICS_SRC} ${SCRIPTING_SRC})

target_link_libraries(Framework opengl32 glfw glew EvoScriptCore CMP_Core OpenAL)

#target_compile_features(Framework INTERFACE cxx_std_20)

if (EVO_VULKAN_STATIC_LIBRARY)
    target_link_libraries(Framework EvoVulkan)
else()
    target_link_libraries(Framework EvoVulkan::lib)
endif()

if (SR_UTILS_STATIC_LIBRARY)
    target_link_libraries(Framework Utils)
else()
    target_link_libraries(Framework Utils::lib)
endif()

if (SR_AUDIO_STATIC_LIBRARY)
    target_link_libraries(Framework Audio)
else()
    target_link_libraries(Framework Audio::lib)
endif()

if (CYGWIN)
    target_link_libraries(Framework "$ENV{VULKAN_SDK}/Lib/vulkan-1.lib")
else()
    if (MINGW)
        target_link_libraries(Framework ${Vulkan_LIBRARY} Dwmapi.lib)
    else()
        target_link_libraries(Framework ${Vulkan_LIBRARY})
    endif()
endif()

if(WIN32)
    if(MSVC)
        #add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
        #add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    else()
        #target_link_libraries(Framework -lpsapi opengl32 glfw glew EvoVulkanCore EvoScriptCore)
        target_link_libraries(Framework -lpsapi)
        target_compile_options(Framework PUBLIC "-Wa,-mbig-obj")
    endif()
endif()

# Устанавливаем директории
target_include_directories(Framework
        PUBLIC
            ${GRAPHICS_INC_PUBLIC} ${PHYSICS_INC_PUBLIC} ${SCRIPTING_INC_PUBLIC}
            ${IMGUI_ROOT_DIR} ${IMGUIZMO_ROOT_DIR} ${IMGUI_NODE_EDITOR_ROOT_DIR}
        PRIVATE
            ${GRAPHICS_INC_PRIVATE} ${PHYSICS_INC_PRIVATE} ${SCRIPTING_INC_PRIVATE}
        INSTANCE
            ${GRAPHICS_INC_INSTANCE} ${PHYSICS_INC_INSTANCE} ${SCRIPTING_INC_INSTANCE}
)