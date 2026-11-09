//
// Created by Monika on 13.02.2025.
//

#include <Engine/GUI/PropertyDrawers/PathPropertyDrawer.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Utils/FileSystem/FileDialog.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Common/StringUtils.h>

#include <Codegen/PathPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback PathPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        const SR_UTILS_NS::Reflection::Value value = context.GetValue();

        /// Геттер может вернуть ссылку на чужие данные (например, на путь разделяемого RawMesh),
        /// поэтому само значение только читаем. Новый путь накапливаем отдельно и применяем в конце,
        /// так что копия Path создаётся только на кадре с реальным изменением.
        std::optional<SR_UTILS_NS::Path> newPath;

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetPropertyName().c_str());

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        SR_MATH_NS::FVector2 buttonSize;

        if (!context.pValue || !context.GetPropertyDisplayName().empty()) {
            const bool isPickingEnabled = context.GetEditorParams().GetCustomArg("pick") == "enabled";

            if (!context.noHeader) {
                buttonSize = isPickingEnabled ?
                             SR_MATH_NS::FVector2(context.fieldTitleWidth * 0.75f, context.fieldHeight) :
                             SR_MATH_NS::FVector2(context.fieldTitleWidth, context.fieldHeight);

                if (SR_IMMEDIATE_GUI_NS::Button(context.GetPropertyDisplayName().c_str(), buttonSize)) {
                    if (context.pProperty) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }
                        feedback.isChanged = true;
                        const SR_UTILS_NS::Reflection::Value& resetValue = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                        auto&& pResetPath = resetValue.IsValid() ? resetValue.Cast<SR_UTILS_NS::Path>() : nullptr;
                        newPath = pResetPath ? *pResetPath : SR_UTILS_NS::Path();
                    }
                }
                DrawTitleContextMenu(context, feedback);
            }

            if (isPickingEnabled) {
                SR_IMMEDIATE_GUI_NS::SameLine();

                if (SR_IMMEDIATE_GUI_NS::Button("...", SR_MATH_NS::FVector2(context.fieldTitleWidth * 0.25f, context.fieldHeight))) {
                    auto&& filterName = context.GetEditorParams().GetCustomArg("filter name");
                    auto&& filterValue = context.GetEditorParams().GetCustomArg("filter value");

                    const bool relativeRes = context.GetEditorParams().GetCustomArg("relative") == "resources";

                    if (!filterName.empty() && !filterValue.empty()) {
                        auto&& resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                        auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesPath, { { filterName, filterValue } });

                        if (!path.empty()) {
                            if (context.onBeforeChangeCallback) {
                                context.onBeforeChangeCallback(false);
                            }
                            feedback.isChanged = true;

                            if (relativeRes) {
                                path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPathRef());
                            }

                            newPath = std::move(path);
                        }
                    }
                }
            }

            SR_IMMEDIATE_GUI_NS::SameLine();
        }

        SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth);

        if (auto&& pPath = value.Cast<SR_UTILS_NS::Path>()) {
            static std::string gPathTmp;
            gPathTmp = newPath.has_value() ? newPath->ToStringRef() : pPath->ToStringRef();
            if (SR_IMMEDIATE_GUI_NS::InputText("##Input", &gPathTmp, SR_IMMEDIATE_GUI_NS::InputTextFlags::EnterReturnsTrue)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                feedback.isChanged = true;
                /// If you copy path in Windows in Explorer, then it will be in quotes, so we need to remove them
                gPathTmp = SR_UTILS_NS::StringUtils::RemoveCharsFromString(gPathTmp, "\"");
                newPath = gPathTmp;
            }
        }
        else {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map path value!");
        }

        SR_IMMEDIATE_GUI_NS::PopItemWidth();

        if (newPath.has_value()) {
            if (context.pValue) {
                /// вложенное значение - пишем на месте, сеттера у него нет
                if (auto&& pPath = context.pValue->Cast<SR_UTILS_NS::Path>()) {
                    *pPath = newPath.value();
                }
            }
            else {
                context.GetProperty().Set(context.pOwner, SR_UTILS_NS::Reflection::Value::CreateCRef(newPath.value()));
            }
        }

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        return feedback;
    }
}
