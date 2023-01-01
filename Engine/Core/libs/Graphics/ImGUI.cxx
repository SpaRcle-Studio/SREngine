//
// Created by Monika on 11.12.2021.
//

#include <Utils/GUI.h>

#include <imgui/imgui.cpp>
#include <imgui/imgui_tables.cpp>
#include <imgui/imgui_draw.cpp>
#include <imgui/imgui_widgets.cpp>

#include <imgui/misc/cpp/imgui_stdlib.cpp>

#ifdef SR_WIN32
    #include <imgui/backends/imgui_impl_win32.cpp>
#endif

/// #ifdef SR_USE_GLFW3
///     #include <imgui/backends/imgui_impl_glfw.cpp>
/// #endif

#ifdef SR_USE_OPENGL
    #include <imgui/backends/imgui_impl_opengl3.cpp>
    /// #include "../Depends/imgui/backends/imgui_impl_glut.cpp"
#endif

#ifdef SR_USE_VULKAN
    #include <imgui/backends/imgui_impl_vulkan.cpp>
#endif

#ifdef SR_USE_IMGUIZMO
    #ifdef SR_ANDROID
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wunused-variable"
        #pragma clang diagnostic ignored "-Wunused-function"
        #pragma clang diagnostic ignored "-Wno-unused-function"
        #pragma clang diagnostic ignored "-Wcomment"
        #pragma clang diagnostic ignored "-Wno-comment"
    #endif

    #include <ImGuizmo/ImGuizmo.cpp>

    #ifdef SR_ANDROID
        #pragma clang diagnostic pop
    #endif
#endif

#ifdef SR_USE_IMGUI_NODE_EDITOR
    #ifdef SR_ANDROID
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wunused-but-set-variable"
        #pragma clang diagnostic ignored "-Wunused-function"
    #endif

    #include <imgui-node-editor/imgui_node_editor_api.cpp>
    #include <imgui-node-editor/imgui_node_editor.cpp>
    #include <imgui-node-editor/imgui_canvas.cpp>
    #include <imgui-node-editor/crude_json.cpp>

    #ifdef SR_ANDROID
        #pragma clang diagnostic pop
    #endif
#endif