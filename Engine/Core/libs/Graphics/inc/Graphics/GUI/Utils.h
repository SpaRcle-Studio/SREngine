//
// Created by Monika on 16.02.2022.
//

#ifndef SR_ENGINE_GUI_UTILS_H
#define SR_ENGINE_GUI_UTILS_H

#include <Utils/Debug.h>
#include <Utils/Math/Mathematics.h>
#include <Utils/Math/Rect.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/SRLM/DataType.h>
#include <Utils/TypeTraits/Properties.h>

namespace SR_GRAPH_GUI_NS {
    class ImGuiDisabledLockGuard : public SR_UTILS_NS::NonCopyable {
    public:
        explicit ImGuiDisabledLockGuard(bool disabled)
            : SR_UTILS_NS::NonCopyable()
        {
            ImGui::BeginDisabled(disabled);
        }

        ~ImGuiDisabledLockGuard() override {
            ImGui::EndDisabled();
        }
    };

    SR_MAYBE_UNUSED static ImVec4 MakeDisableColor(ImVec4 color) {
        color.w /= 2;
        return color;
    }

    SR_MAYBE_UNUSED void static EnumCombo(const std::string& label, SR_UTILS_NS::EnumReflector* pReflector, const SR_HTYPES_NS::Function<void(SR_UTILS_NS::EnumReflector* pReflector)>& callback) {
        if (ImGui::BeginCombo(label.c_str(), (pReflector ? pReflector->GetNameInternal().ToStringRef() : std::string()).c_str())) {
            auto&& selectables = SR_UTILS_NS::EnumReflectorManager::Instance().GetReflectors();
            for (auto&& selectable : selectables) {
                if (ImGui::Selectable(selectable.second->GetNameInternal().ToCStr())) {
                    ImGui::SetItemDefaultFocus();
                    callback(selectable.second);
                }
            }

            ImGui::EndCombo();
        }
    }

    SR_MAYBE_UNUSED void static EnumCombo(
            const std::string& label,
            SR_UTILS_NS::EnumReflector* pReflector,
            const std::optional<SR_UTILS_NS::StringAtom>& value,
            const SR_HTYPES_NS::Function<void(SR_UTILS_NS::StringAtom)>& callback,
            const SR_HTYPES_NS::Function<bool(const SR_UTILS_NS::StringAtom&)>& filter
    ) {
        auto&& strValue = value ? value.value() : SR_UTILS_NS::StringAtom();

        if (ImGui::BeginCombo(SR_FORMAT_C("{}##{}", label.c_str(), (void*)&value), strValue.c_str())) {
            auto&& selectables = pReflector->GetNamesInternal();
            for (auto&& selectable : selectables) {
                if (filter && !filter(selectable)) {
                    continue;
                }

                if (ImGui::Selectable(selectable.ToCStr())) {
                    ImGui::SetItemDefaultFocus();
                    callback(selectable);
                }
            }

            ImGui::EndCombo();
        }
    }

    SR_MAYBE_UNUSED void static EnumCombo(
        const std::string& label,
        SR_UTILS_NS::EnumReflector* pReflector,
        const std::optional<SR_UTILS_NS::StringAtom>& value,
        const SR_HTYPES_NS::Function<void(SR_UTILS_NS::StringAtom)>& callback
    ) {
        EnumCombo(label, pReflector, value, callback, SR_HTYPES_NS::Function<bool(const SR_UTILS_NS::StringAtom&)>());
    }

    template<typename T> void static EnumCombo(const std::string& label, T value, const SR_HTYPES_NS::Function<void(T)>& callback) {
        if (ImGui::BeginCombo(label.c_str(), SR_UTILS_NS::EnumReflector::ToStringAtom(value).c_str())) {
            auto&& selectables = SR_UTILS_NS::EnumReflector::GetNames<T>();
            for (auto&& selectable : selectables) {
                if (ImGui::Selectable(selectable.c_str())) {
                    ImGui::SetItemDefaultFocus();
                    callback(SR_UTILS_NS::EnumReflector::FromString<T>(selectable));
                }
            }

            ImGui::EndCombo();
        }
    }

    SR_MAYBE_UNUSED static bool Vec4Null(const ImVec4 &v1) { return (v1.x == 0) && (v1.y == 0) && (v1.z == 0) && (v1.w == 0); }

    SR_MAYBE_UNUSED static bool DragUnit(const std::string& name, SR_MATH_NS::Unit& value, float_t drag = 0.1f) {
        float_t temp = value;

        if (ImGui::DragFloat(SR_FORMAT_C("##{}{}", name.c_str(), (void*)&value), &temp, drag, 0.0f, 0.0f, "%.5f")) {
            value = temp;
            return true;
        }

        return false;
    }

    SR_MAYBE_UNUSED static bool DragInt32(const std::string& name, int32_t& value, int32_t drag = 1) {
        int32_t temp = value;

        if (ImGui::DragInt(SR_FORMAT_C("##{}{}", name.c_str(), (void*)&value), &temp, drag, 0, 0, "%.2i")) {
            value = temp;
            return true;
        }

        return false;
    }

    SR_MAYBE_UNUSED static bool DragUInt32(const std::string& name, uint32_t& value, uint32_t drag = 1) {
        int32_t temp = value;

        if (ImGui::DragInt(SR_FORMAT_C("##{}{}", name.c_str(), (void*)&value), &temp, drag, 0, 0, "%.2i")) {
            value = SR_MAX(0, temp);
            return true;
        }

        return false;
    }

    SR_MAYBE_UNUSED static bool InputInt(const std::string& name, int32_t& value, int32_t step = 1) {
        int32_t temp = value;
        bool changed = false;

        auto&& textWidth = SR_CLAMP(ImGui::CalcTextSize(std::to_string(value).c_str()).x, 300, 150);

        ImGui::PushItemWidth(textWidth);

        if (ImGui::InputInt(SR_FORMAT_C("{}##{}", name.c_str(), (void*)&value), &temp, step)) {
            value = temp;
            changed = true;
        }

        ImGui::PopItemWidth();

        return changed;
    }

    SR_MAYBE_UNUSED static bool UInputInt32(const std::string& name, uint32_t& value, uint32_t step = 1) {
        int32_t temp = static_cast<int32_t>(value); /// NOLINT
        bool changed = false;

        auto&& textWidth = SR_CLAMP(ImGui::CalcTextSize(std::to_string(value).c_str()).x, 300, 150);

        ImGui::PushItemWidth(textWidth);

        if (ImGui::InputInt(SR_FORMAT_C("{}##{}", name.c_str(), (void*)&value), &temp, static_cast<int32_t>(step))) {
            if (temp < 0) {
                temp = 0;
            }
            changed = value != temp;
            value = temp;
        }

        ImGui::PopItemWidth();

        return changed;
    }

    template<typename T> static void DrawValue(const std::string& label, const T& value, uint32_t index = 0) {
        std::string string;

        if constexpr (std::is_same_v<T, std::string>) {
            string = value;
        }
        else if constexpr (std::is_same_v<T, SR_UTILS_NS::StringAtom>) {
            string = value;
        }
        else if constexpr (std::is_same_v<T, std::string_view>) {
            string = std::string(value);
        }
        else if constexpr (std::is_same_v<T, SR_UTILS_NS::Path>) {
            string = value.ToStringAtom();
        }
        else if constexpr (SR_MATH_NS::IsNumber<T>()) {
            string = std::to_string(value);
        }
        else if constexpr (std::is_same_v<T, const char*>) {
            string = std::string(value);
        }
        else {
            SRHalt("Unknown type!");
        }

        auto&& textWidth = SR_CLAMP(ImGui::CalcTextSize(string.c_str()).x, 300, 150);

        ImGui::PushItemFlag(ImGuiItemFlags_::ImGuiItemFlags_Disabled, true);
        ImGui::PushItemWidth(textWidth);

        ImGui::InputText(
                SR_FORMAT_C("{}##{}", label.c_str(), index),
                &string,
                ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly
        );

        ImGui::PopItemWidth();
        ImGui::PopItemFlag();
    }

    template<typename T> static bool DrawValueControl(
            const char* label,
            T& value,
            T reset,
            ImVec2 btnSize,
            ImVec4 btn,
            ImVec4 hovered,
            ImVec4 activeCol,
            ImFont* font = nullptr,
            T drag = static_cast<T>(0.1f))
    {
        bool result = false;

        ImGui::PushStyleColor(ImGuiCol_Button, btn);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hovered);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeCol);

        if (font)
            ImGui::PushFont(font);

        if (ImGui::Button(SR_FORMAT_C("{}##{}", label, (void*)&value), btnSize)) {
            value = reset;
            result = true;
        }

        if (font)
            ImGui::PopFont();

        ImGui::PopStyleColor(3);

        ImGui::SameLine();

        if constexpr (std::is_same_v<T, SR_MATH_NS::Unit>) {
            result |= DragUnit(label, value, drag);
        }
        else if constexpr (std::is_same_v<T, bool>) {
            bool temp = value;

            if (ImGui::Checkbox(SR_FORMAT_C("##{}{}", label, (void*)&value), &temp)) {
                value = temp;
                result |= true;
            }
        }
        else if constexpr (std::is_same_v<T, uint32_t>) {
            result |= DragUInt32(label, value, drag);
        }
        else {
            result |= DragInt32(label, value, drag);
        }

        return result;
    }

    SR_MAYBE_UNUSED static bool DrawSlider(const std::string& label,
                           SR_MATH_NS::Unit& value,
                           float_t min = 0.0f,
                           float_t max = 0.0f,
                           uint32_t index = 0
    ) {
        auto tmp = static_cast<float_t>(value);

        if (ImGui::SliderScalar(SR_FORMAT_C("{}##{}", label.c_str(), (void*)&value), ImGuiDataType_Float, &tmp, &min, &max, nullptr, ImGuiSliderFlags_Logarithmic)) {
            value = static_cast<SR_MATH_NS::Unit>(tmp);
            return true;
        }

        return false;
    }

    template<typename T> static bool DrawValueSlider (
            const std::string& label,
            T& value,
            T reset,
            T min,
            T max,
            ImVec2 btnSize,
            ImVec4 btn,
            ImVec4 hovered,
            ImVec4 activeCol,
            ImFont* font = nullptr,
            bool active = true)
    {
        bool result = false;

        ImGui::PushStyleColor(ImGuiCol_Button, active ? btn : MakeDisableColor(btn));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, active ? hovered : MakeDisableColor(hovered));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, active ? activeCol : MakeDisableColor(activeCol));

        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, !active);

        if (font) {
            ImGui::PushFont(font);
        }

        if (ImGui::Button(SR_FORMAT_C("{}##{}", label.c_str(), (void*)&value), btnSize) && active) {
            value = reset;
            result = true;
        }

        if (font) {
            ImGui::PopFont();
        }

        ImGui::PopStyleColor(3);

        ImGui::SameLine();

        if (DrawSlider("##" + label, value, static_cast<float_t>(min), static_cast<float_t>(max))) {
            result |= true;
        }

        ImGui::PopItemFlag();

        return result;
    }

    SR_MAYBE_UNUSED bool DrawDataType(SR_SRLM_NS::DataType* pData, bool* pIsEnum, void* pProvider, float_t width = 0, uint32_t deep = 0);

    SR_MAYBE_UNUSED static bool DrawColorControl(
            const std::string& label,
            SR_MATH_NS::FVector4& values,
            float_t resetValue = 0.0f,
            float_t columnWidth = 40.0f)
    {
        bool result = false;

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

        result |= DrawValueControl<SR_MATH_NS::Unit>("R", values.r, resetValue, buttonSize,
                                  ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f },
                                  ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f  },
                                  ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f },
                                  nullptr, 0.01f);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        result |= DrawValueControl<SR_MATH_NS::Unit>("G", values.g, resetValue, buttonSize,
                                  ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
                                  ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f },
                                  ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
                                  nullptr, 0.01f);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        result |= DrawValueControl<SR_MATH_NS::Unit>("B", values.b, resetValue, buttonSize,
                                  ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f },
                                  ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f },
                                  ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f },
                                  nullptr, 0.01f);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        result |= DrawValueControl<SR_MATH_NS::Unit>("A", values.a, resetValue, buttonSize,
                                  ImVec4{ 0.7f, 0.7f, 0.7f, 1.0f },
                                  ImVec4{ 0.8f, 0.8f, 0.8f, 1.0f },
                                  ImVec4{ 0.7f, 0.7f, 0.7f, 1.0f },
                                  nullptr, 0.01f);

        ImGui::PopItemWidth();
        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();

        values = values.Clamp(10, 0);

        return result;
    }

    SR_MAYBE_UNUSED static bool DrawEditableSlider(const std::string& label,
           SR_MATH_NS::Unit& value,
           float_t min = 0.0f,
           float_t max = 0.0f,
           float_t power = 0.1,
           SR_HTYPES_NS::DataStorage* storage = nullptr)
    {
        bool slider = true;

        if (storage) {
            auto&& id = SR_FORMAT("##edt_slider_{}{}", label.c_str(), (void*)&value);
            slider = storage->GetValueDef<bool>(id, true);
            if (ImGui::Checkbox(id.c_str(), &slider)) {
                storage->SetValue<bool>(id, slider);
            }

            ImGui::SameLine();
        }

        const float_t lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { 45.f, lineHeight };

        if (slider) {
            return DrawValueSlider<SR_MATH_NS::Unit>(
                    label, value, 0.f,
                    static_cast<SR_MATH_NS::Unit>(min),
                    static_cast<SR_MATH_NS::Unit>(max),
                    buttonSize,
                    ImVec4{0.2f, 0.7f, 0.2f, 1.0f},
                    ImVec4{0.3f, 0.8f, 0.3f, 1.0f},
                    ImVec4{0.2f, 0.7f, 0.2f, 1.0f}, nullptr, true
            );
        }

        return DrawValueControl<SR_MATH_NS::Unit>(
                 label.c_str(), value, 0.f, buttonSize,
                 ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
                 ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f },
                 ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f }, nullptr, power
         );
    }

    SR_MAYBE_UNUSED static bool DrawFRect(
           const std::array<std::string, 4>& names,
           SR_MATH_NS::FRect& value,
           float_t min = 0.0f,
           float_t max = 0.0f,
           float_t power = 0.1,
           SR_HTYPES_NS::DataStorage* storage = nullptr
    ) {
        bool dirty = false;

        auto left = static_cast<SR_MATH_NS::Unit>(value.Left());
        if (Graphics::GUI::DrawEditableSlider(names[0], left, min, max, power, storage)) {
            value.SetLeft(left);
            dirty = true;
        }

        auto bottom = static_cast<SR_MATH_NS::Unit>(value.Bottom());
        if (Graphics::GUI::DrawEditableSlider(names[1], bottom, min, max, power, storage)) {
            value.SetBottom(bottom);
            dirty = true;
        }

        auto right = static_cast<SR_MATH_NS::Unit>(value.Right());
        if (Graphics::GUI::DrawEditableSlider(names[2], right, min, max, power, storage)) {
            value.SetRight(right);
            dirty = true;
        }

        auto top = static_cast<SR_MATH_NS::Unit>(value.Top());
        if (Graphics::GUI::DrawEditableSlider(names[3], top, min, max, power, storage)) {
            value.SetTop(top);
            dirty = true;
        }

        return dirty;
    }

    SR_MAYBE_UNUSED static bool DrawVec3Control(
            const std::string& label,
            SR_MATH_NS::FVector3& values,
            float_t resetValue = 0.0f,
            float_t columnWidth = 70.0f,
            float_t drag = 0.1,
            uint32_t index = 0,
            bool active = true)
    {
        bool result = false;

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

        result |= DrawValueControl<SR_MATH_NS::Unit>("X", values.x, resetValue, buttonSize,
                ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f },
                ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f  },
                ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }, nullptr, drag);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        result |= DrawValueControl<SR_MATH_NS::Unit>("Y", values.y, resetValue, buttonSize,
               ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
               ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f },
               ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f }, nullptr, drag);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        result |= DrawValueControl<SR_MATH_NS::Unit>("Z", values.z, resetValue, buttonSize,
               ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f },
               ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f },
               ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f }, nullptr, drag);

        ImGui::PopItemWidth();
        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();

        return result;
    }

    SR_MAYBE_UNUSED static bool DrawVec2Control(
            const std::string& label,
            SR_MATH_NS::FVector2& values,
            float_t resetValue = 0.0f,
            float_t columnWidth = 70.0f,
            float_t drag = 0.1)
    {
        bool result = false;

        ImGui::PushID(SR_FORMAT_C("{}{}", label.c_str(), (void*)&values));

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text("%s", label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        /// ---------------------------------------------------------------------------

        result |= DrawValueControl<SR_MATH_NS::Unit>("X", values.x, resetValue, buttonSize,
                ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f },
                ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f  },
                ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }, nullptr, drag);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        result |= DrawValueControl<SR_MATH_NS::Unit>("Y", values.y, resetValue, buttonSize,
               ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
               ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f },
               ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f }, nullptr, drag);

        ImGui::PopItemWidth();
        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();

        return result;
    }

    SR_MAYBE_UNUSED static bool DrawBVec3Control(
            const std::string& label,
            SR_MATH_NS::BVector3& values,
            bool resetValue,
            float_t columnWidth = 70.0f)
    {
        bool result = false;

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

        result |= DrawValueControl<bool>("X", values.x, resetValue, buttonSize,
                                                     ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f },
                                                     ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f  },
                                                     ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }, nullptr, false);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        result |= DrawValueControl<bool>("Y", values.y, resetValue, buttonSize,
                                                     ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
                                                     ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f },
                                                     ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f }, nullptr, false);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        result |= DrawValueControl<bool>("Z", values.z, resetValue, buttonSize,
                                                     ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f },
                                                     ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f },
                                                     ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f }, nullptr, false);

        ImGui::PopItemWidth();
        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();

        return result;
    }

    SR_MAYBE_UNUSED static bool DrawUVec2Control(
        const std::string& label,
        SR_MATH_NS::UVector2& values,
        uint32_t resetValue = 0,
        float_t columnWidth = 70.0f,
        uint32_t drag = 1,
        uint32_t index = 0,
        bool active = true)
    {
        bool result = false;

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

        result |= DrawValueControl<uint32_t>("X", values.x, resetValue, buttonSize,
            ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f },
            ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f },
            ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }, nullptr, drag);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        result |= DrawValueControl<uint32_t>("Y", values.y, resetValue, buttonSize,
            ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
            ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f },
            ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f }, nullptr, drag);

        ImGui::PopItemWidth();
        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();

        return result;
    }

    SR_MAYBE_UNUSED static bool DrawIVec3Control(
            const std::string& label,
            SR_MATH_NS::IVector3& values,
            int32_t resetValue = 0,
            float_t columnWidth = 70.0f,
            int32_t drag = 1,
            uint32_t index = 0,
            bool active = true)
    {
        bool result = false;

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

        result |= DrawValueControl<int32_t>("X", values.x, resetValue, buttonSize,
                ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f },
                ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f  },
                ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }, nullptr, drag);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        result |= DrawValueControl<int32_t>("Y", values.y, resetValue, buttonSize,
               ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
               ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f },
               ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f }, nullptr, drag);

        ImGui::PopItemWidth();
        ImGui::SameLine();

        result |= DrawValueControl<int32_t>("Z", values.z, resetValue, buttonSize,
               ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f },
               ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f },
               ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f }, nullptr, drag);

        ImGui::PopItemWidth();
        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();

        return result;
    }

    SR_MAYBE_UNUSED static bool CheckBox(bool& value) {
        const bool result = ImGui::Checkbox(SR_FORMAT_C("##{}", (void*)&value), &value);
        return result;
    }

    SR_MAYBE_UNUSED static bool CheckBox(const std::string& name, bool& value) {
        const bool result = ImGui::Checkbox(SR_FORMAT_C("{}##{}", name, (void*)&value), &value);
        return result;
    }

    SR_MAYBE_UNUSED static void Text(const char* text) {
        ImGui::Text(text);
    }

    SR_MAYBE_UNUSED static bool Button(const std::string& label, ImVec4 color = ImVec4(0, 0, 0, 0), ImVec4 hovered = ImVec4(0, 0, 0, 0), uint32_t index = 0) {
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

        const auto result = ImGui::Button(SR_FORMAT_C("{}##{}", label.c_str(), index));

        if (hasBtnColor)
            ImGui::PopStyleColor(2);

        if (hasHoveredColor || hasBtnColor)
            ImGui::PopStyleColor(1);

        return result;
    }

    SR_MAYBE_UNUSED static bool Button(const std::string& label, uint32_t index = 0) {
        return Button(label, ImVec4(0, 0, 0, 0), ImVec4(0, 0, 0, 0), index);
    }

    bool RadioButton(const char* label, bool active, float_t radius = 1.f);

    bool CheckboxNoNavFocus(const char* label, bool* v);
    bool ButtonBehaviorNoNavFocus(const ImRect& bb, ImGuiID id, bool* out_hovered, bool* out_held, ImGuiButtonFlags flags = 0);

    SR_MAYBE_UNUSED static float CalcMaxPopupHeightFromItemCount(int items_count)
    {
        ImGuiContext& g = *GImGui;
        if (items_count <= 0)
            return FLT_MAX;
        return (g.FontSize + g.Style.ItemSpacing.y) * items_count - g.Style.ItemSpacing.y + (g.Style.WindowPadding.y * 2);
    }

    SR_MAYBE_UNUSED static bool BeginNodeCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0)
    {
        using namespace ImGui;

        // Always consume the SetNextWindowSizeConstraint() call in our early return paths
        ImGuiContext& g = *GImGui;
        bool has_window_size_constraint = (g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint) != 0;
        g.NextWindowData.Flags &= ~ImGuiNextWindowDataFlags_HasSizeConstraint;

        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        IM_ASSERT((flags & (ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_NoPreview)) != (ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_NoPreview)); // Can't use both flags together

        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);

        const float arrow_size = (flags & ImGuiComboFlags_NoArrowButton) ? 0.0f : GetFrameHeight();
        const ImVec2 label_size = CalcTextSize(label, NULL, true);
        const float expected_w = CalcItemWidth();
        const float w = (flags & ImGuiComboFlags_NoPreview) ? arrow_size : expected_w;
        const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y * 2.0f));
        const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));
        ItemSize(total_bb, style.FramePadding.y);
        if (!ItemAdd(total_bb, id, &frame_bb))
            return false;

        bool hovered, held;
        bool pressed = ButtonBehavior(frame_bb, id, &hovered, &held);
        bool popup_open = IsPopupOpen(id, ImGuiPopupFlags_None);

        const ImU32 frame_col = GetColorU32(hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
        const float value_x2 = ImMax(frame_bb.Min.x, frame_bb.Max.x - arrow_size);
        RenderNavHighlight(frame_bb, id);
        if (!(flags & ImGuiComboFlags_NoPreview))
            window->DrawList->AddRectFilled(frame_bb.Min, ImVec2(value_x2, frame_bb.Max.y), frame_col, style.FrameRounding, (flags & ImGuiComboFlags_NoArrowButton) ? ImDrawCornerFlags_All : ImDrawCornerFlags_Left);
        if (!(flags & ImGuiComboFlags_NoArrowButton))
        {
            ImU32 bg_col = GetColorU32((popup_open || hovered) ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
            ImU32 text_col = GetColorU32(ImGuiCol_Text);
            window->DrawList->AddRectFilled(ImVec2(value_x2, frame_bb.Min.y), frame_bb.Max, bg_col, style.FrameRounding, (w <= arrow_size) ? ImDrawCornerFlags_All : ImDrawCornerFlags_Right);
            if (value_x2 + arrow_size - style.FramePadding.x <= frame_bb.Max.x)
                RenderArrow(window->DrawList, ImVec2(value_x2 + style.FramePadding.y, frame_bb.Min.y + style.FramePadding.y), text_col, ImGuiDir_Down, 1.0f);
        }
        RenderFrameBorder(frame_bb.Min, frame_bb.Max, style.FrameRounding);
        if (preview_value != NULL && !(flags & ImGuiComboFlags_NoPreview))
            RenderTextClipped(frame_bb.Min + style.FramePadding, ImVec2(value_x2, frame_bb.Max.y), preview_value, NULL, NULL, ImVec2(0.0f, 0.0f));
        if (label_size.x > 0)
            RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

        if ((pressed || g.NavActivateId == id) && !popup_open)
        {
            if (window->DC.NavLayerCurrent == 0)
                window->NavLastIds[0] = id;
            OpenPopupEx(id, ImGuiPopupFlags_None);
            popup_open = true;
        }

        if (!popup_open)
            return false;

        if (has_window_size_constraint)
        {
            g.NextWindowData.Flags |= ImGuiNextWindowDataFlags_HasSizeConstraint;
            g.NextWindowData.SizeConstraintRect.Min.x = ImMax(g.NextWindowData.SizeConstraintRect.Min.x, w);
        }
        else
        {
            if ((flags & ImGuiComboFlags_HeightMask_) == 0)
                flags |= ImGuiComboFlags_HeightRegular;
            IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiComboFlags_HeightMask_));    // Only one
            int popup_max_height_in_items = -1;
            if (flags & ImGuiComboFlags_HeightRegular)     popup_max_height_in_items = 8;
            else if (flags & ImGuiComboFlags_HeightSmall)  popup_max_height_in_items = 4;
            else if (flags & ImGuiComboFlags_HeightLarge)  popup_max_height_in_items = 20;
            SetNextWindowSizeConstraints(ImVec2(w, 0.0f), ImVec2(FLT_MAX, CalcMaxPopupHeightFromItemCount(popup_max_height_in_items)));
        }

        char name[16];
        ImFormatString(name, IM_ARRAYSIZE(name), "##Combo_%02d", g.BeginPopupStack.Size); // Recycle windows based on depth

        // Position the window given a custom constraint (peak into expected window size so we can position it)
        // This might be easier to express with an hypothetical SetNextWindowPosConstraints() function.
        //if (ImGuiWindow* popup_window = FindWindowByName(name)) {
        //    if (popup_window->WasActive)
        //    {
        //        ImVec2 cursorScreenPos = ax::NodeEditor::CanvasToScreen(ImGui::GetCursorScreenPos());
        //        ax::NodeEditor::Suspend();
        //        ImGui::SetCursorScreenPos(cursorScreenPos);
        //        // Always override 'AutoPosLastDirection' to not leave a chance for a past value to affect us.
        //        ImVec2 size_expected = ImGui::CalcWindowNextAutoFitSize(popup_window);
        //        if (flags & ImGuiComboFlags_PopupAlignLeft)
        //            popup_window->AutoPosLastDirection = ImGuiDir_Left; // "Below, Toward Left"
        //        else
        //            popup_window->AutoPosLastDirection = ImGuiDir_Down; // "Below, Toward Right (default)"
        //        ImRect r_outer = ImGui::GetPopupAllowedExtentRect(popup_window);
        //        ImVec2 pos = FindBestWindowPosForPopupEx(frame_bb.GetBL(), size_expected, &popup_window->AutoPosLastDirection, r_outer, frame_bb, ImGuiPopupPositionPolicy_ComboBox);
        //        SetNextWindowPos(pos);
        //        ax::NodeEditor::Resume();
        //    }
        //}

        // We don't use BeginPopupEx() solely because we have a custom name string, which we could make an argument to BeginPopupEx()
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_Popup | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove;

        ax::NodeEditor::Suspend();

        // Horizontally align ourselves with the framed text
        PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(style.FramePadding.x, style.WindowPadding.y));
        bool ret = Begin(name, NULL, window_flags);
        PopStyleVar();
        if (!ret)
        {
            EndPopup();
            IM_ASSERT(0);   // This should never happen as we tested for IsPopupOpen() above
            return false;
        }
        return true;
    }

    SR_MAYBE_UNUSED static void EndNodeCombo()
    {
        ImGui::EndPopup();

        ax::NodeEditor::Resume();
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

#endif //SR_ENGINE_GUI_UTILS_H
