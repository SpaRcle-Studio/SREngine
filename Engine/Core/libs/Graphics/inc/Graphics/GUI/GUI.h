//
// Created by Nikita on 15.03.2021.
//

#ifndef SR_ENGINE_UTILS_GUI_H
#define SR_ENGINE_UTILS_GUI_H

#include <Utils/Debug.h>

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

namespace SR_UTILS_GUI_NS {
    SR_INLINE_STATIC bool Vec4Null(const ImVec4 &v1) { return (v1.x == 0) && (v1.y == 0) && (v1.z == 0) && (v1.w == 0); }

    /*bool GUISystem::ImageButton(std::string_view&& imageId, void *descriptor, const SR_MATH_NS::IVector2 &size, int32_t framePadding, ImGuiButtonFlags flags) {
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

        const bool result = ImageButtonInternal(imageId.data(), descriptor, size, framePadding, flags);

        ImGui::PopStyleColor();

        return result;
    }

    bool GUISystem::ImageButtonInternal(std::string_view&& imageId, void *descriptor, const SR_MATH_NS::IVector2 &size, int32_t framePadding, ImGuiButtonFlags flags) {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        if (window->SkipItems)
            return false;

        ImVec4 bg_col = ImVec4(0,0,0,0);
        ImVec4 tint_col = ImVec4(1,1,1,1);
        ImVec2 uv0, uv1;

        if (m_pipeLine == Graphics::PipelineType::OpenGL) {
            uv0 = ImVec2(0, 1);
            uv1 = ImVec2(1, 0);
        }
        else {
            uv0 = ImVec2(-1, 0);
            uv1 = ImVec2(0, 1);
        }

        /// Default is to use texture ID as ID. User can still push string/integer prefixes.
        ImGui::PushID((void*)(intptr_t)descriptor);
        const ImGuiID id = window->GetID(imageId.data());
        ImGui::PopID();

        const ImVec2 padding = (framePadding >= 0) ? ImVec2((float)framePadding, (float)framePadding) : g.Style.FramePadding;

        const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(size.x, size.y) + padding * 2);
        ImGui::ItemSize(bb);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

        // Render
        const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
        ImGui::RenderNavHighlight(bb, id);
        ImGui::RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, g.Style.FrameRounding));
        if (bg_col.w > 0.0f)
            window->DrawList->AddRectFilled(bb.Min + padding, bb.Max - padding, ImGui::GetColorU32(bg_col));
        window->DrawList->AddImage((ImTextureID)descriptor, bb.Min + padding, bb.Max - padding, uv0, uv1, ImGui::GetColorU32(tint_col));

        return pressed;
    }

    bool GUISystem::ImageButton(std::string_view&& imageId, void *descriptor, const SR_MATH_NS::IVector2 &size, int32_t framePadding) {
        return ImageButton(imageId.data(), descriptor, size, framePadding, ImGuiButtonFlags_None);
    }

    bool GUISystem::ImageButtonDouble(std::string_view&& imageId, void *descriptor, const SR_MATH_NS::IVector2 &size, int32_t framePadding) {
        return ImageButton(imageId.data(), descriptor, size, framePadding, ImGuiButtonFlags_PressedOnDoubleClick);
    }

    bool GUISystem::ImageButton(void *descriptor, const SR_MATH_NS::IVector2 &size, int32_t framePadding) {
        return ImageButton("##image", descriptor, size, framePadding);
    }

    bool GUISystem::ImageButton(void *descriptor, const SR_MATH_NS::IVector2 &size) {
        return ImageButton(descriptor, size, -1);
    }

    bool GUISystem::BeginDragDropTargetWindow(const char* payload_type)
    {
        using namespace ImGui;
        ImRect inner_rect = GetCurrentWindow()->InnerRect;
        if (BeginDragDropTargetCustom(inner_rect, GetID("##WindowBgArea")))
            if (const ImGuiPayload* payload = AcceptDragDropPayload(payload_type, ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect))
            {
                if (payload->IsPreview())
                {
                    ImDrawList* draw_list = GetForegroundDrawList();
                    draw_list->AddRectFilled(inner_rect.Min, inner_rect.Max, GetColorU32(ImGuiCol_DragDropTarget, 0.05f));
                    draw_list->AddRect(inner_rect.Min, inner_rect.Max, GetColorU32(ImGuiCol_DragDropTarget), 0.0f, 0, 2.0f);
                }
                if (payload->IsDelivery())
                    return true;
                EndDragDropTarget();
            }
        return false;
    }

    void GUISystem::DrawTexture(void *descriptor, const SR_MATH_NS::IVector2 &size) {
        if (m_pipeLine == Graphics::PipelineType::OpenGL) {
            DrawImage(descriptor, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0), {1, 1, 1, 1}, {0, 0, 0, 0}, true);
        }
        else {
            DrawImage(descriptor, ImVec2(size.x, size.y), ImVec2(-1, 0), ImVec2(0, 1), {1, 1, 1, 1}, {0, 0, 0, 0}, true);
        }
    }

    void GUISystem::DrawTexture(
            Framework::Helper::Math::IVector2 winSize,
            Framework::Helper::Math::IVector2 texSize, uint32_t id,
            bool centralize)
    {
        const float_t dx = static_cast<float_t>(winSize.x) / texSize.x;
        const float_t dy = static_cast<float_t>(winSize.y) / texSize.y;

        if (dy > dx)
            texSize *= dx;
        else
            texSize *= dy;

        // Because I use the texture from OpenGL, I need to invert the V from the UV.

        if (centralize) {
            ImVec2 initialCursorPos = ImGui::GetCursorPos();
            auto res = (winSize - texSize) * 0.5f;
            ImVec2 centralizedCursorPos = { (float)res.x, (float)res.y };
            centralizedCursorPos = ImClamp(centralizedCursorPos, initialCursorPos, centralizedCursorPos);
            ImGui::SetCursorPos(centralizedCursorPos);
        }

        if (m_pipeLine == Graphics::PipelineType::OpenGL)
            DrawImage(reinterpret_cast<void*>(static_cast<uint64_t>(id)), ImVec2(texSize.x, texSize.y), ImVec2(0, 1), ImVec2(1, 0), {1, 1, 1, 1 }, {0, 0, 0, 0 }, true);
        else {
            DrawImage(m_env->GetDescriptorSetFromTexture(id, true), ImVec2(texSize.x, texSize.y), ImVec2(-1, 0), ImVec2(0, 1), {1, 1, 1, 1}, {0, 0, 0, 0}, true);
        }
    }

    void GUISystem::DrawImage(
            ImTextureID user_texture_id,
            const ImVec2& size,
            const ImVec2& uv0,
            const ImVec2& uv1,
            const ImVec4& tint_col,
            const ImVec4& border_col,
            bool imposition)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return;

        ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
        if (border_col.w > 0.0f)
            bb.Max = bb.Max + ImVec2(2, 2);

        if (!imposition) {
            ImGui::ItemSize(bb);
            if (!ImGui::ItemAdd(bb, 0))
                return;
        }

        if (border_col.w > 0.0f) {
            window->DrawList->AddRect(bb.Min, bb.Max, ImGui::GetColorU32(border_col), 0.0f);
            window->DrawList->AddImage(user_texture_id, bb.Min + ImVec2(1, 1), bb.Max - ImVec2(1, 1), uv0, uv1, ImGui::GetColorU32(tint_col));
        }
        else
            window->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, uv0, uv1, ImGui::GetColorU32(tint_col));
    }

    bool GUISystem:: {

    }*/

    SR_DLL_EXPORT extern void CollapsingHeader(const std::string& label, ImGuiTreeNodeFlags flags);
    SR_DLL_EXPORT extern void DrawMultiLineTextOnCenter(const std::string& text);
    SR_DLL_EXPORT extern void DrawMultiLineTextOnCenter(const std::string& text, ImVec4 color);
    SR_DLL_EXPORT extern void DrawTextOnCenter(const std::string& text, ImVec4 color = ImVec4(1.f, 1.f, 1.f, 1.f), bool sameLine = true);
}

#endif //SR_ENGINE_UTILS_GUI_H
