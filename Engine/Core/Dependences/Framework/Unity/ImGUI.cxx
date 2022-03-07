//
// Created by Monika on 11.12.2021.
//

#include <GUI.h>

#include "../Depends/imgui/imgui.cpp"
#include "../Depends/imgui/imgui_tables.cpp"
#include "../Depends/imgui/imgui_draw.cpp"
#include "../Depends/imgui/imgui_widgets.cpp"

#include "../Depends/imgui/misc/cpp/imgui_stdlib.cpp"

#ifdef SR_WIN32
    #include "../Depends/imgui/backends/imgui_impl_win32.cpp"
#endif

#ifdef SR_USE_GLFW3
    #include "../Depends/imgui/backends/imgui_impl_glfw.cpp"
#endif

#ifdef SR_USE_OPENGL
    #include "../Depends/imgui/backends/imgui_impl_opengl3.cpp"
    //#include "../Depends/imgui/backends/imgui_impl_glut.cpp"
#endif

#ifdef SR_USE_OPENGL
    #include "../Depends/imgui/backends/imgui_impl_vulkan.cpp"
#endif

#ifdef SR_USE_IMGUIZMO
    #include "../Depends/ImGuizmo/ImGuizmo.cpp"
#endif

#ifdef SR_USE_IMGUI_NODE_EDITOR
    #include "../Depends/imgui-node-editor/imgui_node_editor_api.cpp"
    #include "../Depends/imgui-node-editor/imgui_node_editor.cpp"
    #include "../Depends/imgui-node-editor/imgui_canvas.cpp"
    #include "../Depends/imgui-node-editor/crude_json.cpp"
#endif