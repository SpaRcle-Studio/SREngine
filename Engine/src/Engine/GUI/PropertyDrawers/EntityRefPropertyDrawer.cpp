//
// Created by Monika on 19.07.2025.
//

#include <Engine/GUI/PropertyDrawers/EntityRefPropertyDrawer.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/Engine.h>

#include <Scripting/Base/Behaviour.h>

#include <Utils/ECS/EntityRef.h>
#include <Utils/ECS/SceneObject.h>
#include <Utils/ECS/Component.h>

#include <Codegen/EntityRefPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback EntityRefPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pUID);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetPropertyName().c_str());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        if (!context.pValue || !context.GetPropertyDisplayName().empty()) {
            const SR_MATH_NS::FVector2 buttonSize = SR_MATH_NS::FVector2(context.fieldTitleWidth, context.fieldHeight);

            if (SR_GRAPH_GUI_NS::Immediate::Button(context.GetPropertyDisplayName().c_str(), buttonSize)) {
                if (context.pProperty) {
                    if (context.onBeforeChangeCallback) {
                        context.onBeforeChangeCallback(false);
                    }
                    feedback.isChanged = true;
                    value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                    value = value.Copy();
                }
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();
        }

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(context.fieldWidth);

        if (auto&& pEntityRef = dynamic_cast<SR_UTILS_NS::EntityRefBase*>(value.GetSRClass())) {
            SR_UTILS_NS::StringAtom entityType = pEntityRef->GetTypeName();
            if (pEntityRef->GetEntity()) {
                SR_UTILS_NS::SceneObject::Ptr pSceneObject;
                if (pEntityRef->GetEntity()->GetMeta()->IsSameOrInherited(SR_UTILS_NS::SceneObject::GetMetaStatic()->GetFactoryName())) {
                    pSceneObject = pEntityRef->GetEntity().DynamicCast<SR_UTILS_NS::SceneObject>();
                }
                std::string formatted = pSceneObject ? pSceneObject->GetName().ToStringRef() : " {} ({})"_format(pEntityRef->GetEntity()->GetEntityId(), entityType.ToCStr());
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text, SR_MATH_NS::FColor(1.f, 1.f, 1.f, 1.f));
                SR_GRAPH_GUI_NS::Immediate::PushID((void*)pEntityRef);
                if (SR_GRAPH_GUI_NS::Immediate::Button(formatted.c_str(), SR_MATH_NS::FVector2(context.fieldWidth, 0))) {
                    if (pSceneObject) {
                        if (auto&& pHierarchy = context.pEditor->GetWidget<SR_CORE_GUI_NS::Hierarchy>()) {
                            pHierarchy->SelectGameObject(pSceneObject);
                        }
                    }
                }
                SR_GRAPH_GUI_NS::Immediate::PopID();
                SR_GRAPH_GUI_NS::Immediate::PopStyleColor();
            }
            else if (pEntityRef->GetEntityId() != SR_ID_INVALID) {
                std::string formatted = " {} ({})"_format(pEntityRef->GetEntityId(), entityType.ToCStr());
                SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
                SR_GRAPH_GUI_NS::Immediate::ButtonColoredText(formatted.c_str(), SR_MATH_NS::FColor(0.f, 1.f, 0.f, 1.f), SR_MATH_NS::FVector2(context.fieldWidth, 0));
                SR_GRAPH_GUI_NS::Immediate::EndDisabled();
            }
            else {
                std::string formatted = " Is not set ({})"_format(entityType.ToCStr());
                SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
                SR_GRAPH_GUI_NS::Immediate::ButtonColoredText(formatted.c_str(), SR_MATH_NS::FColor(1.f, 1.f, 0.f, 1.f) , SR_MATH_NS::FVector2(context.fieldWidth, 0));
                SR_GRAPH_GUI_NS::Immediate::EndDisabled();
            }

            if (SR_GRAPH_GUI_NS::Immediate::BeginDragDropTarget()) {
                if (auto&& payload = SR_GRAPH_GUI_NS::Immediate::AcceptDragDropPayload("Hierarchy##Payload")) {
                    if (auto&& pData = SR_GRAPH_GUI_NS::Immediate::GetDataFromDragDropPayload(payload)) {
                        SR_GRAPH_GUI_NS::PayloadArrayData payloadData = *(SR_GRAPH_GUI_NS::PayloadArrayData*)(pData);
                        std::vector<SR_UTILS_NS::SceneObject::Ptr> sceneObjects;

                        for (size_t i = 0; i < payloadData.size; ++i) {
                            uint64_t entityId = static_cast<uint64_t*>(payloadData.data)[i];
                            if (auto&& pSO = context.pEditor->GetEngine()->GetScene()->GetEntityController()->FindById(entityId).StaticCast<SR_UTILS_NS::SceneObject>()) {
                                sceneObjects.emplace_back(pSO);
                            }
                        }

                        if (!sceneObjects.empty() && sceneObjects.front() && sceneObjects.front()->GetMeta()->IsSameOrInherited(entityType)) {
                            if (context.onBeforeChangeCallback) {
                                context.onBeforeChangeCallback(false);
                            }
                            feedback.isChanged = true;
                            pEntityRef->SetEntityId(sceneObjects.front()->GetEntityId());
                        }
                    }
                }

                if (auto&& payload = SR_GRAPH_GUI_NS::Immediate::AcceptDragDropPayload("InspectorComponent##Payload")) {
                    if (auto&& pData = SR_GRAPH_GUI_NS::Immediate::GetDataFromDragDropPayload(payload)) {
                        SR_GRAPH_GUI_NS::PayloadArrayData payloadData = *(SR_GRAPH_GUI_NS::PayloadArrayData*)(pData);
                        std::list<SR_UTILS_NS::Component::Ptr> components;
                        for (size_t i = 0; i < payloadData.size; ++i) {
                            uint64_t entityId = static_cast<uint64_t*>(payloadData.data)[i];
                            if (auto&& pEntity = context.pEditor->GetEngine()->GetScene()->GetEntityController()->FindById(entityId)) {
                                components.emplace_back(pEntity.StaticCast<SR_UTILS_NS::Component>());
                            }
                        }
                        if (!components.empty() && components.front()) {
                            static const auto&& behaviourMeta = SR_SCRIPTING_NS::Behaviour::GetMetaStatic();

                            if (components.front()->GetMeta()->IsSameOrInherited(entityType)) {
                                if (context.onBeforeChangeCallback) {
                                    context.onBeforeChangeCallback(false);
                                }
                                feedback.isChanged = true;
                                pEntityRef->SetEntityId(components.front()->GetEntityId());
                            }
                            else if (components.front()->GetMeta()->IsSameOrInherited(behaviourMeta->GetFactoryName())) {
                                if (auto&& pBehaviour = components.front().StaticCast<SR_SCRIPTING_NS::Behaviour>()) {
                                    if (auto&& pInnerBehaviour = pBehaviour->GetBehaviour(); pInnerBehaviour && pInnerBehaviour->GetMeta()->IsSameOrInherited(entityType)) {
                                        if (context.onBeforeChangeCallback) {
                                            context.onBeforeChangeCallback(false);
                                        }
                                        feedback.isChanged = true;
                                        pEntityRef->SetEntityId(components.front()->GetEntityId());
                                    }
                                }
                            }
                        }
                    }
                }

                SR_GRAPH_GUI_NS::Immediate::EndDragDropTarget();
            }
        }
        else {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map entity ref value!");
        }

        SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

        SetValue(context, feedback, value);

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        return feedback;
    }
}
