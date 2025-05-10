//
// Created by Monika on 13.02.2025.
//

#include <Core/GUI/PropertyDrawers/PathPropertyDrawer.h>

#include <Codegen/PathPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback PathPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pOwner);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetPropertyName().c_str());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        if (!context.pValue || !context.GetPropertyDisplayName().empty()) {
            const bool isPickingEnabled = context.GetEditorParams().GetCustomArg("pick") == "enabled";

            const SR_MATH_NS::FVector2 buttonSize = isPickingEnabled ?
                SR_MATH_NS::FVector2(context.fieldTitleWidth * 0.75f, context.fieldHeight) :
                SR_MATH_NS::FVector2(context.fieldTitleWidth, context.fieldHeight);

            if (SR_GRAPH_GUI_NS::Immediate::Button(context.GetPropertyDisplayName().c_str(), buttonSize)) {
                if (context.pProperty) {
                    if (context.onBeforeChangeCallback) {
                        context.onBeforeChangeCallback(false);
                    }
                    feedback.isChanged = true;
                    value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                    value = value.DetachIfConst();
                }
            }

            if (isPickingEnabled) {
                SR_GRAPH_GUI_NS::Immediate::SameLine();

                if (SR_GRAPH_GUI_NS::Immediate::Button("Pick", SR_MATH_NS::FVector2(context.fieldTitleWidth * 0.25f, context.fieldHeight))) {
                    auto&& filterName = context.GetEditorParams().GetCustomArg("filter name");
                    auto&& filterValue = context.GetEditorParams().GetCustomArg("filter value");
                    if (!filterName.empty() && !filterValue.empty()) {
                        auto&& resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                        auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesPath, { { filterName, filterValue } });

                        if (auto&& pPath = value.TryCast<SR_UTILS_NS::Path>(); pPath && !path.empty()) {
                            if (context.onBeforeChangeCallback) {
                                context.onBeforeChangeCallback(false);
                            }
                            feedback.isChanged = true;
                            *pPath = path;
                        }
                    }
                }
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();
        }

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(context.fieldWidth);

        if (auto&& pPath = value.TryCast<SR_UTILS_NS::Path>()) {
            std::string path = pPath->ToStringRef();
            if (SR_GRAPH_GUI_NS::Immediate::InputText("##Input", &path, SR_GRAPH_GUI_NS::Immediate::InputTextFlags::EnterReturnsTrue)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                feedback.isChanged = true;
                /// If you copy path in Windows in Explorer, then it will be in quotes, so we need to remove them
                path = SR_UTILS_NS::StringUtils::RemoveCharsFromString(path, "\"");
                *pPath = path;
            }
        }
        else {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map path value!");
        }

        SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

        SetValue(context, feedback, value);

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        return feedback;
    }
}
