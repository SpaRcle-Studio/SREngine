//
// Created by Monika on 15.07.2023.
//

#include <Utils/GUI.h>

#include <Graphics/GUI/Utils.h>

namespace SR_GRAPH_GUI_NS {
    bool RadioButton(const char* label, bool active, float_t radius)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        const float square_sz = ImGui::GetFrameHeight() * radius;
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
        const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), (label_size.y + style.FramePadding.y * 2.0f) / 1.75f));
        ImGui::ItemSize(total_bb, style.FramePadding.y / 1.75f);
        if (!ImGui::ItemAdd(total_bb, id))
            return false;

        ImVec2 center = check_bb.GetCenter();
        center.x = IM_ROUND(center.x);
        center.y = IM_ROUND(center.y);
        const float radiusInternal = (square_sz - 1.0f) * 0.5f;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
        if (pressed)
            ImGui::MarkItemEdited(id);

        ImGui::RenderNavHighlight(total_bb, id);
        window->DrawList->AddCircleFilled(center, radiusInternal, ImGui::GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16);
        if (active)
        {
            const float pad = ImMax(1.0f, IM_FLOOR(square_sz / 6.0f));
            window->DrawList->AddCircleFilled(center, radiusInternal - pad, ImGui::GetColorU32(ImGuiCol_CheckMark), 16);
        }

        if (style.FrameBorderSize > 0.0f)
        {
            window->DrawList->AddCircle(center + ImVec2(1, 1), radiusInternal, ImGui::GetColorU32(ImGuiCol_BorderShadow), 16, style.FrameBorderSize);
            window->DrawList->AddCircle(center, radiusInternal, ImGui::GetColorU32(ImGuiCol_Border), 16, style.FrameBorderSize);
        }

        ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y);
         if (g.LogEnabled)
             ImGui::LogRenderedText(&label_pos, active ? "(x)" : "( )");
         if (label_size.x > 0.0f)
             ImGui::RenderText(label_pos, label);

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
        return pressed;
    }
}