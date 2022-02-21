//
// Created by Monika on 16.02.2022.
//

#ifndef SRENGINE_GUIUTILS_H
#define SRENGINE_GUIUTILS_H

namespace Framework::Graphics::GUI {
    static bool Vec4Null(const ImVec4 &v1) { return (v1.x == 0) && (v1.y == 0) && (v1.z == 0) && (v1.w == 0); }

    static bool DragUnit(const std::string& name, Helper::Math::Unit& value) {
        float_t temp = value;
        if (ImGui::DragFloat(std::string("##" + name).c_str(), &temp, 0.1f, 0.0f, 0.0f, "%.2f")) {
            value = temp;
            return true;
        }

        return false;
    }

    static bool DrawVec3Control(const std::string& label, Helper::Math::FVector3& values, float_t resetValue = 0.0f, float_t columnWidth = 70.0f) {
        bool result = false;

        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text("%s", label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);

        if (ImGui::Button("X", buttonSize)) {
            values.x = resetValue;
            result = true;
        }

        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();

        result |= DragUnit("X", values.x);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushFont(boldFont);

        if (ImGui::Button("Y", buttonSize)) {
            values.y = resetValue;
            result = true;
        }

        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();

        result |= DragUnit("Y", values.y);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushFont(boldFont);

        if (ImGui::Button("Z", buttonSize)) {
            values.z = resetValue;
            result = true;
        }

        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();

        result |= DragUnit("Z", values.z);

        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();

        return result;
    }

    static bool Button(const std::string& name, ImVec4 color = ImVec4(0, 0, 0, 0)) {
        const auto hasColor = !Vec4Null(color);

        if (hasColor)
            ImGui::PushStyleColor(ImGuiCol_Button, color);

        const auto result = ImGui::Button(name.c_str());

        if (hasColor)
            ImGui::PopStyleColor();

        return result;
    }
}

#endif //SRENGINE_GUIUTILS_H
