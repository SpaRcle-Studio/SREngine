cmake_minimum_required(VERSION 3.16)
project(imgui-cmake)

add_subdirectory(./../glfw glfw_build)
add_subdirectory(./../glew/build/cmake glew_build)

set(srcFiles
        imgui.cpp
        imgui_widgets.cpp
        imgui_draw.cpp
        imgui_demo.cpp
        #imgui_tables.cpp
        backends/imgui_impl_glfw.cpp
        backends/imgui_impl_opengl3.cpp
        backends/imgui_impl_win32.cpp
        misc/cpp/imgui_stdlib.cpp

        Guizmo/ImGuizmo.cpp
        )

set(publicHeaderFiles
        imgui.h
        imgui_internal.h
        imconfig.h
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h
        backends/imgui_impl_glfw.h
        backends/imgui_impl_opengl3.h
        backends/imgui_impl_win32.h
        misc/cpp/imgui_stdlib.h

        Guizmo/ImGuizmo.h
        #imgui_draw.cpp
        #imgui_widgets.cpp
        )

set(includeDir ${CMAKE_CURRENT_BINARY_DIR}/include)
file(COPY ${publicHeaderFiles} DESTINATION ${includeDir})

find_package(OpenGL REQUIRED)

add_library(imgui STATIC
        ${srcFiles})

target_link_libraries(imgui opengl32 glew glfw)

target_include_directories(imgui
        PUBLIC
        ${includeDir}
        ${FRAMEWORK_ROOT_DIR}/Depends/glew/include
        )

