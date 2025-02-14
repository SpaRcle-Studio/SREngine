//
// Created by Monika on 13.02.2025.
//

#include <Core/GUI/PropertyDrawers/PathPropertyDrawer.h>

#include <Codegen/PathPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback PathPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetProperty().GetName().c_str());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        if (!context.pValue) {
            const ImVec2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (ImGui::Button(context.GetProperty().GetEditorParams().GetDisplayName().c_str(), buttonSize)) {
                feedback.isChanged = true;
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.DetachIfConst();
            }

            ImGui::SameLine();
        }

        ImGui::PushItemWidth(context.fieldWidth);

        if (auto&& pPath = value.TryCast<SR_UTILS_NS::Path>()) {
            std::string path = pPath->ToStringRef();
            if (ImGui::InputText("##Input", &path, ImGuiInputTextFlags_EnterReturnsTrue)) {
                feedback.isChanged = true;
                /// If you copy path in Windows in Explorer, then it will be in quotes, so we need to remove them
                path = SR_UTILS_NS::StringUtils::RemoveCharsFromString(path, "\"");
                *pPath = path;
            }
        }
        else {
            SR_GRAPH_GUI_NS::ColoredText("Failed to map path value!", ImColor(1.f, 0.f, 0.f, 1.f));
        }

        ImGui::PopItemWidth();

        if (!context.pValue && feedback.isChanged && !value.IsRef()) {
            context.GetProperty().Set(context.pOwner, value);
        }

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopID();

        return feedback;
    }
}
