//
// Created by Monika on 19.02.2026.
//

#include <Engine/GUI/PropertyDrawers/ResourceRefPropertyDrawer.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/Engine.h>

#include <Utils/Resources/ResourceRef.h>
#include <Utils/FileSystem/FileDialog.h>

#include <Codegen/ResourceRefPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback ResourceRefPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pUID);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetPropertyName().c_str());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        if (!context.pValue || !context.GetPropertyDisplayName().empty()) {
            const SR_MATH_NS::FVector2 buttonSize = SR_MATH_NS::FVector2(context.fieldTitleWidth * 0.75f, context.fieldHeight);

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

            SR_GRAPH_GUI_NS::Immediate::SameLine();
        }

        /// picking
        {
            if (SR_GRAPH_GUI_NS::Immediate::Button("...", SR_MATH_NS::FVector2(context.fieldTitleWidth * 0.25f, context.fieldHeight))) {
                auto&& filterName = context.GetEditorParams().GetCustomArg("filter name");
                auto&& filterValue = context.GetEditorParams().GetCustomArg("filter value");

                const bool relativeRes = context.GetEditorParams().GetCustomArg("relative") == "resources";

                if (!filterName.empty() && !filterValue.empty()) {
                    auto&& resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                    auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesPath, { { filterName, filterValue } });

                    if (auto&& pRef = dynamic_cast<SR_UTILS_NS::ResourceRefBase*>(value.GetSRClass())) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }
                        feedback.isChanged = true;

                        if (relativeRes) {
                            path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
                        }

                        pRef->SetResource(path.ToStringRef());
                    }
                }
            }
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(context.fieldWidth);

        if (auto&& pRef = dynamic_cast<SR_UTILS_NS::ResourceRefBase*>(value.GetSRClass())) {
            SR_UTILS_NS::StringAtom type = pRef->GetResourceType();

            if (pRef->GetId().empty()) {
                std::string formatted = " Is not set ({})"_format(type.ToCStr());
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 1.f, 0.f, 1.f), formatted.c_str());
            }
            else if (!pRef->GetResource()) {
                std::string formatted = " {} ({} is missing)"_format(pRef->GetId().ToCStr(), type.ToCStr());
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), formatted.c_str());
            }
            else {
                std::string formatted = " {} ({})"_format(pRef->GetId().ToCStr(), type.ToCStr());
                SR_GRAPH_GUI_NS::Immediate::Text(formatted.c_str());
            }
        }
        else {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map resource ref value!");
        }

        SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

        SetValue(context, feedback, value);

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        return feedback;
    }
}
