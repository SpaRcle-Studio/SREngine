//
// Created by Nikita on 15.03.2021.
//

#ifndef SR_ENGINE_UTILS_GUI_H
#define SR_ENGINE_UTILS_GUI_H

#include <Utils/Debug.h>
#include <Utils/Math/Vector2.h>

#ifdef SR_USE_IMGUI
    #define IMGUI_UNLIMITED_FRAME_RATE
    #define IMGUI_DEFINE_MATH_OPERATORS
    #define IMGUI_USE_WCHAR32

    #ifndef IM_ASSERT
        #define IM_ASSERT(_EXP) SRAssert1Once(_EXP)
    #endif

    #ifndef IM_ASSERT_USER_ERROR
        #define IM_ASSERT_USER_ERROR(_EXP, _MSG) SRAssert2Once(_EXP, _MSG)
    #endif

    #include <imgui.h>
    #include <misc/cpp/imgui_stdlib.h>
    #include <imgui_internal.h>

    #ifdef SR_WIN32
        #include <backends/imgui_impl_win32.h>
    #endif

    #ifdef SR_USE_VULKAN
        #include <backends/imgui_impl_vulkan.h>

        #ifdef min
            #undef min
        #endif

        #ifdef max
            #undef max
        #endif
    #endif

    #ifdef SR_USE_OPENGL
        #define GL_GLEXT_PROTOTYPES
        //#include <GL/glew.h>
        //#include <GL/wglew.h>
        #include <backends/imgui_impl_opengl3.h>
        #include <backends/imgui_impl_opengl3_loader.h>

        //#include <GL/gl3w.h>
    #endif

    #ifdef SR_USE_GLFW3
        #include <backends/imgui_impl_glfw.h>
    #endif

    #include <ImGuizmo.h>
#endif

#ifdef SR_USE_IMGUI_NODE_EDITOR
    #include <imgui-node-editor/imgui_node_editor.h>
#endif

namespace SR_GRAPH_NS {
    enum class PipelineType : uint8_t;
}

namespace SR_GRAPH_GUI_NS {
#ifdef SR_USE_IMGUI
    SR_DLL_EXPORT extern bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size = -1.0f);
    SR_DLL_EXPORT extern bool IsVec4Null(const ImVec4& v1);
    SR_DLL_EXPORT extern bool IsVec2Null(const ImVec2& v1);
    SR_DLL_EXPORT extern bool ImageButton(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding);
    SR_DLL_EXPORT extern bool ImageButtonDouble(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding);
    SR_DLL_EXPORT extern bool ImageButton(void* pDescriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding);
    SR_DLL_EXPORT extern bool ImageButton(void* pDescriptor, const SR_MATH_NS::IVector2& size);
    SR_DLL_EXPORT extern bool BeginDragDropTargetWindow(const std::string& payloadType);
    SR_DLL_EXPORT extern bool ImageButtonInternal(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::IVector2 &size, int32_t framePadding, ImGuiButtonFlags flags);
    SR_DLL_EXPORT extern bool ImageButton(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding, ImGuiButtonFlags flags);
    SR_DLL_EXPORT extern bool CollapsingHeader(const std::string& label, ImGuiTreeNodeFlags flags);
    SR_DLL_EXPORT extern void DrawMultiLineTextOnCenter(const std::string& text);
    SR_DLL_EXPORT extern void DrawMultiLineTextOnCenter(const std::string& text, ImVec4 color);
    SR_DLL_EXPORT extern void DrawTextOnCenter(const std::string& text, ImVec4 color = ImVec4(1.f, 1.f, 1.f, 1.f), bool sameLine = true);
    SR_DLL_EXPORT extern int ImTextCharToUtf8(char* buf, int32_t bufSize, uint32_t c);
    SR_DLL_EXPORT extern ImVec2 DrawTexture(void* pDescriptor, const SR_MATH_NS::IVector2& size, SR_GRAPH_NS::PipelineType pipelineType, bool imposition);
    SR_DLL_EXPORT extern ImVec2 DrawImage(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col, bool imposition);
#endif
}

#endif //SR_ENGINE_UTILS_GUI_H
