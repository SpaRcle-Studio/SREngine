//
// Created by Monika on 11.12.2021.
//

#include <ImmediateGUI/Impl/ImGUI.h>

#include <Utils/Profile/TracyContext.h>

#define IMGUI_TRACY_ZONE SR_TRACY_ZONE
#define IMGUI_TRACY_ZONE_N(name) SR_TRACY_ZONE_N(name)
#define IMGUI_TRACY_ZONE_VALUE(value) SR_TRACY_ZONE_VALUE(value)

#include <imgui/imgui.cpp>
#include <imgui/imgui_tables.cpp>
#include <imgui/imgui_draw.cpp>
#include <imgui/imgui_widgets.cpp>
#include <imgui/imgui_demo.cpp>

#ifdef IMGUI_HAS_STACK_LAYOUT
    #include <imgui/imgui_stacklayout.cpp>
#endif

#include <imgui/misc/cpp/imgui_stdlib.cpp>

#ifdef SR_WIN32
    #include <imgui/backends/imgui_impl_win32.cpp>
#endif

#ifdef SR_ANDROID
    #include <imgui/backends/imgui_impl_android.cpp>
#endif

#if defined(SR_LINUX) && defined(SR_RENDER_GLFW)
    #include <imgui/backends/imgui_impl_glfw.cpp>
#endif

#ifdef SR_USE_GLFW3
    #include <imgui/backends/imgui_impl_glfw.cpp>
#endif

#ifdef SR_USE_OPENGL
    #include <imgui/backends/imgui_impl_opengl3.cpp>
    /// #include "../Depends/imgui/backends/imgui_impl_glut.cpp"
#endif

#ifdef SR_USE_VULKAN
    #include <imgui/backends/imgui_impl_vulkan.cpp>
#endif

#ifdef SR_USE_IMGUI_NODE_EDITOR
    #define __IMGUI_EXTRA_MATH_INL__
    #include <imgui-node-editor/imgui_node_editor.cpp>
    #include <imgui-node-editor/imgui_node_editor_api.cpp>
    #include <imgui-node-editor/imgui_canvas.cpp>
    #include <imgui-node-editor/crude_json.cpp>

    #include <ImmediateGUI/Impl/NodeEditorDeprecatedMath.h>
#endif

namespace SR_IMMEDIATE_GUI_NS {
    ImColor FCToImC(const SR_MATH_NS::FColor& color) {
        return ImColor(color.r, color.g, color.b, color.a);
    }

    ImVec2 F2ToImV2(const SR_MATH_NS::FVector2& vec) {
        return ImVec2(vec.x, vec.y);
    }

    ImVec4 F4ToImV4(const SR_MATH_NS::FVector4& vec) {
        return ImVec4(vec.x, vec.y, vec.z, vec.w);
    }

    ImVec4 FCToImV4(const SR_MATH_NS::FColor& vec) {
        return ImVec4(vec.r, vec.g, vec.b, vec.a);
    }

    SR_MATH_NS::FVector2 ImV2ToF2(const ImVec2& vec) {
        return SR_MATH_NS::FVector2(vec.x, vec.y);
    }

    SR_MATH_NS::FVector4 ImV4ToF4(const ImVec4& vec) {
        return SR_MATH_NS::FVector4(vec.x, vec.y, vec.z, vec.w);
    }

    SR_MATH_NS::FRect IRToFR(const ImRect& rect) {
        return SR_MATH_NS::FRect(
            rect.Min.x,
            rect.Min.y,
            rect.Max.x,
            rect.Max.y
        );
    }
}