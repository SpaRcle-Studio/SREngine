//
// Created by Nikita on 14.01.2021.
//

#ifndef GAMEENGINE_GUIWINDOW_H
#define GAMEENGINE_GUIWINDOW_H

#define IMGUI_DEFINE_MATH_OPERATORS

#include <Input/InputSystem.h>
#include <Debug.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <glm/glm.hpp>
#include <ImGuizmo.h>

//#include <EntityComponentSystem/Scene.h>
//#include <EntityComponentSystem/GameObject.h>

namespace Framework::Helper{
    class Scene;
    class GameObject;
}

namespace Framework::Graphics {
        class Camera;
}

namespace Framework::Graphics::GUI {
    class GUIWindow {
    private:
        inline static const ImGuiTreeNodeFlags g_node_flags_with_child    = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        inline static const ImGuiTreeNodeFlags g_node_flags_without_child = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;
    public:
        GUIWindow()                 = delete;
        GUIWindow(const GUIWindow&) = delete;
        GUIWindow(GUIWindow&)       = delete;
        ~GUIWindow()                = delete;
    private:
        inline static ImGuizmo::OPERATION g_currentGuizmoOperation  = ImGuizmo::OPERATION::TRANSLATE;
        inline static ImGuizmo::MODE      g_currentGuizmoMode       = ImGuizmo::MODE::LOCAL;
        inline static bool                g_currentGuizmoPivot      = true;
        inline static bool                g_shiftPressed            = false;

        inline static void CheckSelected(Helper::GameObject* gm) noexcept;
        static void DrawChild(Helper::GameObject* root) noexcept;
        static inline ImVec2 SumVec2(const ImVec2& v1, const ImVec2& v2){
            return ImVec2(v1.x + v2.x, v1.y + v2.y);
        }
        static inline ImVec2 SubVec2(const ImVec2& v1, const ImVec2& v2){
            return ImVec2(v1.x - v2.x, v1.y - v2.y);
        }
    public:
        static void DrawHierarchy(Helper::Scene* scene) noexcept;
        static void DrawInspector(Helper::GameObject* gameObject) noexcept;
        static void DrawGuizmo(Graphics::Camera* camera, Helper::GameObject* gameObject, glm::vec2 cameraSize) noexcept;

        inline static bool Vec4Null(const ImVec4& v1) { return (v1.x == 0) && (v1.y == 0) && (v1.z == 0) && (v1.w == 0); }

        inline static bool SetGuizmoTool(unsigned char id) {
            ImGuizmo::OPERATION op;
            switch (id) {
                case 1: op = ImGuizmo::OPERATION::TRANSLATE; break;
                case 2: op = ImGuizmo::OPERATION::ROTATE;    break;
                case 3: op = ImGuizmo::OPERATION::SCALE;     break;
                default: return false;
            }
            if (op == g_currentGuizmoOperation)
                return false;

            g_currentGuizmoOperation = op;

            return true;
        }

        inline static bool ButtonWithId(
                const char* _id, const char* label, ImVec2 button_size = ImVec2(0, 0),
                ImGuiButtonFlags flags = ImGuiButtonFlags_None, bool imposition = false, ImVec2 offset = ImVec2(0,0), ImVec4 color = ImVec4(0,0,0,0)
        ) {
            const bool has_color = !Vec4Null(color);

            ImGuiWindow* window = ImGui::GetCurrentWindow();
            if (window->SkipItems)
                return false;

            ImGuiContext& g = *GImGui;
            const ImGuiStyle& style = g.Style;
            const ImGuiID id = window->GetID(_id);
            const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

            ImVec2 pos = window->DC.CursorPos + offset;
            if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
                pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
            ImVec2 size = ImGui::CalcItemSize(button_size, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

            const ImRect bb(pos, pos + size);

            if (has_color)
                ImGui::PushStyleColor(ImGuiCol_Button, color);

            if (!imposition)
            {
                ImGui::ItemSize(size, style.FramePadding.y);

                if (!ImGui::ItemAdd(bb, id))
                    return false;
            }

            if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
                flags |= ImGuiButtonFlags_Repeat;
            bool hovered, held;
            bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

            // Render
            const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
            ImGui::RenderNavHighlight(bb, id);
            ImGui::RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);
            ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);

            // Automatically close popups
            //if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
            //    CloseCurrentPopup();

            IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.LastItemStatusFlags);

            if (has_color)
                ImGui::PopStyleColor();

            return pressed;
        }

        inline static void Begin(const std::string& winName) noexcept {
            ImGui::Begin(winName.c_str());
        }
        inline static void BeginChild(const std::string& winName) noexcept {
            ImGui::BeginChild(winName.c_str());
        }

        inline static bool BeginMainMenuBar() noexcept { return ImGui::BeginMainMenuBar(); }
        inline static void EndMainMenuBar() noexcept { ImGui::EndMainMenuBar(); }

        inline static bool BeginMenu(const char* name) noexcept { return ImGui::BeginMenu(name); }
        inline static void EndMenu() noexcept { ImGui::EndMenu(); }

        inline static bool MenuItem(const char* name) noexcept { return ImGui::MenuItem(name); }

        inline static void End() noexcept {
            ImGui::End();
        }
        inline static void EndChild() noexcept {
            ImGui::EndChild();
        }
        inline static glm::vec2 GetWindowSize() {
            ImVec2 size = ImGui::GetWindowSize();
            return {size.x, size.y};
        }
        inline static void DrawTextOnCenter(const std::string& text, bool sameLine = true) {
            float font_size = ImGui::GetFontSize() * text.size() / 2;

            if (sameLine)
                ImGui::SameLine(
         ImGui::GetWindowSize().x / 2 -
                        font_size + (font_size / 2)
                );

            ImGui::Text("%s", text.c_str());
        }
        inline static void DrawImage(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col, bool imposition = false)
        {
            ImGuiWindow* window = ImGui::GetCurrentWindow();
            if (window->SkipItems)
                return;

            //ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
            ImRect bb(window->DC.CursorPos, SumVec2(window->DC.CursorPos, size));
            if (border_col.w > 0.0f)
                bb.Max = SumVec2(bb.Max, ImVec2(2, 2));
                //bb.Max += ImVec2(2, 2);

            if (!imposition) {
                ImGui::ItemSize(bb);
                if (!ImGui::ItemAdd(bb, 0))
                    return;
            }

            //user_texture_id = (void*)5;

            if (border_col.w > 0.0f)
            {
                window->DrawList->AddRect(bb.Min, bb.Max, ImGui::GetColorU32(border_col), 0.0f);
                //window->DrawList->AddImage(user_texture_id, bb.Min + ImVec2(1, 1), bb.Max - ImVec2(1, 1), uv0, uv1, ImGui::GetColorU32(tint_col));
                window->DrawList->AddImage(user_texture_id, SumVec2(bb.Min, ImVec2(1, 1)), SubVec2(bb.Max, ImVec2(1, 1)), uv0, uv1, ImGui::GetColorU32(tint_col));
            }
            else
            {
                window->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, uv0, uv1, ImGui::GetColorU32(tint_col));
            }
        }
        inline static void DrawTexture(glm::vec2 win_size, glm::vec2 img_size, unsigned int tex, const bool centralize = true) {
            const float dx = win_size.x / img_size.x;
            const float dy = win_size.y / img_size.y;

            if (dx > dy)
                img_size *= dy;
            else
                if (dy > dx)
                    img_size *= dx;
                else
                    img_size *= dy;

            // Because I use the texture from OpenGL, I need to invert the V from the UV.

            if (centralize) {
                ImVec2 initialCursorPos = ImGui::GetCursorPos();
                glm::vec2 res = (win_size - img_size) * 0.5f;
                ImVec2 centralizedCursorPos = {res.x,res.y};
                centralizedCursorPos = ImClamp(centralizedCursorPos, initialCursorPos, centralizedCursorPos);
                ImGui::SetCursorPos(centralizedCursorPos);
            }

            //unsigned int* id = new unsigned int(tex);
            //(ImTextureID)static_cast<void*>(&tex)
            //DrawImage((ImTextureID)static_cast<void*>(&tex), ImVec2(img_size.x, img_size.y), ImVec2(0, 1), ImVec2(1, 0), { 1,1,1,1 }, { 0,0,0,0 }, true); // interesting bug
            DrawImage(reinterpret_cast<void*>(tex), ImVec2(img_size.x, img_size.y), ImVec2(0, 1), ImVec2(1, 0), { 1,1,1,1 }, { 0,0,0,0 }, true);
        }
    };
}

#endif //GAMEENGINE_GUIWINDOW_H
