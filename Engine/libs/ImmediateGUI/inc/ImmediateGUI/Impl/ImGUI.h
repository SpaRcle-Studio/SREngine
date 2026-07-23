//
// Created by Nikita on 15.03.2021.
//

#ifndef SR_ENGINE_UTILS_GUI_H
#define SR_ENGINE_UTILS_GUI_H

#include <ImmediateGUI/stdInclude.h>

#ifndef SR_IMGUI_INCLUDE_CHECK
    #error "ImGui included in another code module! Please include ImGui only in Grpahics module!"
#endif

#include <Utils/Debug.h>
#include <Utils/Math/Vector2.h>

namespace SR_GRAPH_GUI_NS {
    extern std::atomic<bool> gIgnoreImGuiAsserts;
    extern void SetIgnoreImGuiAsserts(bool ignore);
}

#ifdef SR_USE_IMGUI
    #define IMGUI_UNLIMITED_FRAME_RATE
    #define IMGUI_DEFINE_MATH_OPERATORS
    #define IMGUI_USE_WCHAR32

    #ifndef IM_ASSERT
        #define IM_ASSERT(_EXP) SRAssert1Once(SR_GRAPH_GUI_NS::gIgnoreImGuiAsserts || (_EXP))
    #endif

    #ifndef IM_ASSERT_USER_ERROR_RET
        #define IM_ASSERT_USER_ERROR_RET(_EXP, _MSG) if (!SRVerify2(SR_GRAPH_GUI_NS::gIgnoreImGuiAsserts || (_EXP), _MSG)) { return; }
    #endif

    #ifndef IM_ASSERT_USER_ERROR_RETV
        #define IM_ASSERT_USER_ERROR_RETV(_EXP, _RET, _MSG) if (!SRVerify2(SR_GRAPH_GUI_NS::gIgnoreImGuiAsserts || (_EXP), _MSG)) { return _RET; }
    #endif

    #ifndef IM_ASSERT_USER_ERROR
        #define IM_ASSERT_USER_ERROR(_EXP, _MSG) SRAssert2Once(_EXP, _MSG)
    #endif

    #include <imgui/imgui.h>
    #include <imgui/misc/cpp/imgui_stdlib.h>
    #include <imgui/imgui_internal.h>
    #include <implot/implot.h>
    #include <implot/implot_internal.h>

    #ifdef SR_WIN32
        #include <imgui/backends/imgui_impl_win32.h>
    #endif

    #ifdef SR_LINUX
        #include <imgui/backends/imgui_impl_glfw.h>
    #endif

    #ifdef SR_USE_VULKAN
        #include <imgui/backends/imgui_impl_vulkan.h>

        #ifdef min
            #undef min
        #endif

        #ifdef max
            #undef max
        #endif
    #endif

    #ifdef SR_EMSCRIPTEN
        #include <imgui/backends/imgui_impl_wgpu.h>
    #endif

    #ifdef SR_USE_OPENGL
        #define GL_GLEXT_PROTOTYPES
        //#include <GL/glew.h>
        //#include <GL/wglew.h>
        #include <imgui/backends/imgui_impl_opengl3.h>
        #include <imgui/backends/imgui_impl_opengl3_loader.h>

        //#include <GL/gl3w.h>
    #endif

    #ifdef SR_USE_GLFW3
        #include <imgui/backends/imgui_impl_glfw.h>
    #endif
#endif

#if defined(SR_USE_IMGUI_NODE_FLOW) && defined(SR_USE_IMGUI)
    #include <ImNodeFlow.h>
#endif

#if defined(SR_USE_IMGUI_NODE_EDITOR) && defined(SR_USE_IMGUI)
    #include <imgui-node-editor/imgui_node_editor.h>
#endif

namespace SR_GRAPH_GUI_NS::Immediate {
    ImColor FCToImC(const SR_MATH_NS::FColor& color);
    ImVec2 F2ToImV2(const SR_MATH_NS::FVector2& vec);
    ImVec4 F4ToImV4(const SR_MATH_NS::FVector4& vec);
    ImVec4 FCToImV4(const SR_MATH_NS::FColor& vec);
    SR_MATH_NS::FVector2 ImV2ToF2(const ImVec2& vec);
    SR_MATH_NS::FVector4 ImV4ToF4(const ImVec4& vec);
    SR_MATH_NS::FRect IRToFR(const ImRect& rect);
}

#endif //SR_ENGINE_UTILS_GUI_H
