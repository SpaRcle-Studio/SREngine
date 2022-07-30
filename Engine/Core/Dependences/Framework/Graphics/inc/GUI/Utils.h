//
// Created by Monika on 16.02.2022.
//

#ifndef SRENGINE_GUIUTILS_H
#define SRENGINE_GUIUTILS_H

#include <Utils/Debug.h>
#include <Utils/Math/Mathematics.h>

namespace SR_GRAPH_NS::GUI {
    static ImVec4 MakeDisableColor(ImVec4 color) {
        color.w /= 2;
        return color;
    }

    static bool Vec4Null(const ImVec4 &v1) { return (v1.x == 0) && (v1.y == 0) && (v1.z == 0) && (v1.w == 0); }

    static bool DragUnit(const std::string& name, SR_MATH_NS::Unit& value, float_t drag = 0.1f, bool active = true, uint32_t index = 0) {
        float_t temp = value;

        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, !active);

        if (ImGui::DragFloat(SR_FORMAT_C("##%s%i", name.c_str(), index), &temp, drag, 0.0f, 0.0f, "%.2f")) {
            value = temp;
            ImGui::PopItemFlag();
            return true;
        }

        ImGui::PopItemFlag();

        return false;
    }

    static bool InputInt(const std::string& name, int32_t& value, int32_t step = 1, bool active = true, uint32_t index = 0) {
        int32_t temp = value;
        bool changed = false;

        auto&& textWidth = SR_CLAMP(ImGui::CalcTextSize(std::to_string(value).c_str()).x, 300, 150);

        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, !active);
        ImGui::PushItemWidth(textWidth);

        if (ImGui::InputInt(SR_FORMAT_C("%s##%i", name.c_str(), index), &temp, step)) {
            value = temp;
            changed = true;
        }

        ImGui::PopItemWidth();
        ImGui::PopItemFlag();

        return changed;
    }

    template<typename T> static void DrawValue(const std::string& label, const T& value, uint32_t index = 0) {
        std::string string;

        if constexpr (std::is_same_v<T, std::string>) {
            string = value;
        }
        else if constexpr (std::is_same_v<T, SR_UTILS_NS::Path>) {
            string = value.ToString();
        }
        else if constexpr (SR_MATH_NS::IsNumber<T>()) {
            string = std::to_string(value);
        }
        else if constexpr (std::is_same_v<T, const char*>) {
            string = std::string(value);
        }
        else {
            SR_STATIC_ASSERT("Unknown type!");
        }

        auto&& textWidth = SR_CLAMP(ImGui::CalcTextSize(string.c_str()).x, 300, 150);

        ImGui::PushItemFlag(ImGuiItemFlags_::ImGuiItemFlags_Disabled, true);
        ImGui::PushItemWidth(textWidth);

        ImGui::InputText(
                SR_FORMAT_C("%s##%i", label.c_str(), index),
                &string,
                ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly
        );

        ImGui::PopItemWidth();
        ImGui::PopItemFlag();
    }

    static bool DrawUnitControl(
            const char* label,
            SR_MATH_NS::Unit& value,
            SR_MATH_NS::Unit reset,
            ImVec2 btnSize,
            ImVec4 btn,
            ImVec4 hovered,
            ImVec4 activeCol,
            ImFont* font = nullptr,
            bool active = true,
            float_t drag = 0.1f,
            uint32_t index = 0)
    {
        bool result = false;

        ImGui::PushStyleColor(ImGuiCol_Button, active ? btn : MakeDisableColor(btn));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, active ? hovered : MakeDisableColor(hovered));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, active ? activeCol : MakeDisableColor(activeCol));

        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, !active);

        if (font)
            ImGui::PushFont(font);

        if (ImGui::Button(SR_FORMAT_C("%s##%i", label, index), btnSize) && active) {
            value = reset;
            result = true;
        }

        if (font)
            ImGui::PopFont();

        ImGui::PopItemFlag();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();

        result |= DragUnit(label, value, drag, active, index);

        ImGui::PopItemWidth();

        return result;
    }

    static bool DrawColorControl(
            const std::string& label,
            SR_MATH_NS::FVector4& values,
            float_t resetValue = 0.0f,
            bool active = true,
            float_t columnWidth = 40.0f,
            uint32_t index = 0)
    {
        bool result = false;

        ImGuiIO& io = ImGui::GetIO();

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text("%s", label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 4.0f, lineHeight };

        /// ---------------------------------------------------------------------------

        result |= DrawUnitControl("R", values.r, resetValue, buttonSize,
                                  ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f },
                                  ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f  },
                                  ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f },
                                  nullptr, active, 0.01f, index);

        ImGui::SameLine();

        result |= DrawUnitControl("G", values.g, resetValue, buttonSize,
                                  ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
                                  ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f },
                                  ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
                                  nullptr, active, 0.01f, index);

        ImGui::SameLine();

        result |= DrawUnitControl("B", values.b, resetValue, buttonSize,
                                  ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f },
                                  ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f },
                                  ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f },
                                  nullptr, active, 0.01f, index);

        ImGui::SameLine();

        result |= DrawUnitControl("A", values.a, resetValue, buttonSize,
                                  ImVec4{ 0.7f, 0.7f, 0.7f, 1.0f },
                                  ImVec4{ 0.8f, 0.8f, 0.8f, 1.0f },
                                  ImVec4{ 0.7f, 0.7f, 0.7f, 1.0f },
                                  nullptr, active, 0.01f, index);

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();

        values = values.Clamp(10, 0);

        return result;
    }

    static bool DrawVec3Control(
            const std::string& label,
            SR_MATH_NS::FVector3& values,
            float_t resetValue = 0.0f,
            float_t columnWidth = 70.0f,
            float_t drag = 0.1,
            uint32_t index = 0)
    {
        bool result = false;

        ImGuiIO& io = ImGui::GetIO();

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text("%s", label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        /// ---------------------------------------------------------------------------

        result |= DrawUnitControl("X", values.x, resetValue, buttonSize,
                ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f },
                ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f  },
                ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }, nullptr, true, drag, index);

        ImGui::SameLine();

        result |= DrawUnitControl("Y", values.y, resetValue, buttonSize,
               ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
               ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f },
               ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f }, nullptr, true, drag, index);

        ImGui::SameLine();

        result |= DrawUnitControl("Z", values.z, resetValue, buttonSize,
               ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f },
               ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f },
               ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f }, nullptr, true, drag, index);

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();

        return result;
    }

    static bool CheckBox(const std::string& name, bool& value, bool active = true) {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, !active);

        const bool result = ImGui::Checkbox(name.c_str(), &value);

        ImGui::PopItemFlag();

        return result;
    }

    static bool Button(const std::string& label, ImVec4 color = ImVec4(0, 0, 0, 0), ImVec4 hovered = ImVec4(0, 0, 0, 0), uint32_t index = 0) {
        const auto hasBtnColor = !Vec4Null(color);
        const auto hasHoveredColor = !Vec4Null(hovered);

        if (!hasHoveredColor)
            hovered = color + ImVec4(0.1, 0.1, 0.1, 0);

        if (hasBtnColor) {
            ImGui::PushStyleColor(ImGuiCol_Button, color);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);
        }

        if (hasHoveredColor || hasBtnColor)
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hovered);

        const auto result = ImGui::Button(SR_FORMAT_C("%s##%i", label.c_str(), index));

        if (hasBtnColor)
            ImGui::PopStyleColor(2);

        if (hasHoveredColor || hasBtnColor)
            ImGui::PopStyleColor(1);

        return result;
    }
}

/*
glm::vec2 Framework::Graphics::Window::GetGlobalWindowMousePos(Framework::Graphics::Camera *camera, ImGuiWindow *aimedWindowTarget) {
    glm::vec2 win_pos = { aimedWindowTarget->Pos.x, aimedWindowTarget->Pos.y };
    glm::vec2 win_size = { aimedWindowTarget->Size.x, aimedWindowTarget->Size.y };
    glm::vec2 window_size = this->GetWindowSize().ToGLM();
    glm::vec2 img_size = camera->GetSize().ToGLM();

    glm::vec2 pos = m_env->GetMousePos();

    const float dx = win_size.x / img_size.x;
    const float dy = win_size.y / img_size.y;

    if (dy > dx)
        img_size *= dx;
    else
        img_size *= dy;

    // Вычисляем положение мыши в окне относительно изображения н окне интерфейса

    pos -= win_pos;
    pos *= (window_size / win_size);

    pos -= ((win_size - img_size) / 2.f) * window_size / win_size;
    pos *= win_size / img_size;

    pos.y = window_size.y - pos.y;

    return pos;
}
 */

#endif //SRENGINE_GUIUTILS_H
