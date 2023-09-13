//
// Created by Monika on 12.09.2023.
//

#include <Utils/GUI.h>

namespace SR_UTILS_GUI_NS {
    void DrawTextOnCenter(const std::string& text, ImVec4 color, bool sameLine) {
        const auto fontSize = ImGui::GetFontSize() * static_cast<float_t>(text.size()) / 2.f;

        if (sameLine) {
            ImGui::SameLine(ImGui::GetWindowSize().x / 2 - fontSize + (fontSize / 2));
        }

        ImGui::TextColored(color, "%s", text.c_str());
    }

    void DrawMultiLineTextOnCenter(const std::string& text) {
        const float_t winWidth = ImGui::GetWindowSize().x;
        const float_t textWidth = ImGui::CalcTextSize(text.c_str()).x;

        /// calculate the indentation that centers the text on one line, relative
        /// to window left, regardless of the `ImGuiStyleVar_WindowPadding` value
        float_t textIndentation = (winWidth - textWidth) * 0.5f;

        /// if text is too long to be drawn on one line, `text_indentation` can
        /// become too small or even negative, so we check a minimum indentation
        float_t minIndentation = 20.0f;
        if (textIndentation <= minIndentation) {
            textIndentation = minIndentation;
        }

        ImGui::SameLine(textIndentation);
        ImGui::PushTextWrapPos(winWidth - textIndentation);
        ImGui::TextWrapped("%s", text.c_str());
        ImGui::PopTextWrapPos();
    }

    void DrawMultiLineTextOnCenter(const std::string &text, ImVec4 color) {
        const float_t winWidth = ImGui::GetWindowSize().x;
        const float_t textWidth = ImGui::CalcTextSize(text.c_str()).x;

        /// calculate the indentation that centers the text on one line, relative
        /// to window left, regardless of the `ImGuiStyleVar_WindowPadding` value
        float_t textIndentation = (winWidth - textWidth) * 0.5f;

        /// if text is too long to be drawn on one line, `text_indentation` can
        /// become too small or even negative, so we check a minimum indentation
        float_t minIndentation = 20.0f;
        if (textIndentation <= minIndentation) {
            textIndentation = minIndentation;
        }

        ImGui::SameLine(textIndentation);

        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::PushTextWrapPos(winWidth - textIndentation);

        ImGui::TextWrapped("%s", text.c_str());

        ImGui::PopTextWrapPos();
        ImGui::PopStyleColor();
    }

    void CollapsingHeader(const std::string& label, ImGuiTreeNodeFlags flags) {
        ImGuiWindow* pWindow = ImGui::GetCurrentWindow();
        if (pWindow->SkipItems) {
            return false;
        }

        ImGuiID id = pWindow->GetID(label);
        flags |= ImGuiTreeNodeFlags_CollapsingHeader;
        flags |= ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_ClipLabelForTrailingButton;

        return ImGui::TreeNodeBehavior(id, flags, label.c_str());
    }
}