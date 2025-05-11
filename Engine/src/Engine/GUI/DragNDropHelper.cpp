//
// Created by Monika on 15.04.2023.
//

#include <Engine/GUI/DragNDropHelper.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Component.h>

namespace SR_CORE_GUI_NS {
    bool DragDropTargetEntityRef(EditorGUI* pContext, SR_UTILS_NS::EntityRef& entityRef, const char* id, float_t width) {
        std::string preview;

        if (auto&& pGameObject = entityRef.GetGameObject()) {
            preview = "[GMJ] " + pGameObject->GetName().ToStringRef();
        }
        else if (auto&& pComponent = entityRef.GetComponent()) {
            preview = "[CMP] " + pComponent->GetMeta()->GetFactoryName().ToStringRef();
        }
        else {
            preview = "[None]";
        }

        bool changed = false;

        SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Border, SR_MATH_NS::FColor(247, 84, 225, 255) / 255.f);

        if (SR_GRAPH_GUI_NS::Immediate::BeginChild(SR_FORMAT_C("{}-{}", id, (void*)&entityRef), SR_MATH_NS::FVector2(width, 50), true)) {
            SR_GRAPH_GUI_NS::Immediate::PopStyleColor();

            SR_GRAPH_GUI_NS::Immediate::Text("%s:", id);

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            if (SR_GRAPH_GUI_NS::Immediate::BeginChild(SR_FORMAT_C("{}-{}-1", id, (void*)&entityRef), SR_MATH_NS::FVector2(200, 20), true)) {
                SR_GRAPH_GUI_NS::Immediate::Text("%s", preview.c_str());

                if (SR_GRAPH_GUI_NS::Immediate::BeginDragDropTarget()) {
                    if (auto&& payload = SR_GRAPH_GUI_NS::Immediate::AcceptDragDropPayload("Hierarchy##Payload")) {
                        if (auto&& pData = SR_GRAPH_GUI_NS::Immediate::GetDataFromDragDropPayload(payload)) {
                            std::list<SR_UTILS_NS::SceneObject::Ptr> gameObjects = *(std::list<SR_UTILS_NS::SceneObject::Ptr>*)(pData);
                            if (!gameObjects.empty()) {
                                entityRef.SetPathTo(gameObjects.front().DynamicCast<SR_UTILS_NS::Entity>());
                                changed = true;
                            }
                        }
                    }

                    if (auto&& payload = SR_GRAPH_GUI_NS::Immediate::AcceptDragDropPayload("InspectorComponent##Payload")) {
                        if (auto&& pData = SR_GRAPH_GUI_NS::Immediate::GetDataFromDragDropPayload(payload)) {
                            std::list<SR_UTILS_NS::Component::Ptr> components = *(std::list<SR_UTILS_NS::Component::Ptr> *)(pData);
                            if (!components.empty()) {
                                entityRef.SetPathTo(components.front()->DynamicCast<SR_UTILS_NS::Entity>());
                                changed = true;
                            }
                        }
                    }

                    SR_GRAPH_GUI_NS::Immediate::EndDragDropTarget();
                }

                SR_GRAPH_GUI_NS::Immediate::EndChild();
            }

            if (SR_GRAPH_GUI_NS::Immediate::Button("Reset")) {
                entityRef.SetPathTo(nullptr);
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            if (SR_GRAPH_GUI_NS::Immediate::Button("Show")) {
                auto&& pHierarchy = pContext->GetWidget<Hierarchy>();

                if (auto&& pSceneObject = entityRef.GetSceneObject(); pSceneObject && pHierarchy) {
                    pHierarchy->SelectGameObject(pSceneObject);
                }
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            if (SR_GRAPH_GUI_NS::Immediate::Button("Update")) {
                entityRef.UpdateTarget();
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            bool relative = entityRef.IsRelative();
            if (SR_GRAPH_GUI_NS::Immediate::Checkbox(SR_FORMAT_C("Relative##{}-{}", id, (void*)&entityRef), &relative)) {
                entityRef.SetRelative(relative);
                entityRef.UpdateTarget();
                changed = true;
            }

            SR_GRAPH_GUI_NS::Immediate::EndChild();
        }
        else {
            SR_GRAPH_GUI_NS::Immediate::PopStyleColor();
        }

        return changed;
    }
}