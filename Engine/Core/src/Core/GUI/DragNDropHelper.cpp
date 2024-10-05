//
// Created by Monika on 15.04.2023.
//

#include <Core/GUI/DragNDropHelper.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Component.h>

namespace SR_CORE_GUI_NS {
    bool DragDropTargetEntityRef(EditorGUI* pContext, SR_UTILS_NS::EntityRef& entityRef, const char* id, float_t width) {
        std::string preview;

        if (auto&& pGameObject = entityRef.GetGameObject()) {
            preview = "[GMJ] " + pGameObject->GetName();
        }
        else if (auto&& pComponent = entityRef.GetComponent()) {
            preview = "[CMP] " + pComponent->GetComponentName().ToStringRef();
        }
        else {
            preview = "[None]";
        }

        bool changed = false;

        ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4)ImColor(247, 84, 225));

        if (ImGui::BeginChild(SR_FORMAT_C("{}-{}", id, (void*)&entityRef), ImVec2(width, 50), true)) {
            ImGui::PopStyleColor();

            ImGui::Text("%s:", id);

            ImGui::SameLine();

            if (ImGui::BeginChild(SR_FORMAT_C("{}-{}-1", id, (void*)&entityRef), ImVec2(200, 20), true)) {
                ImGui::Text("%s", preview.c_str());

                if (ImGui::BeginDragDropTarget()) {
                    if (auto&& payload = ImGui::AcceptDragDropPayload("Hierarchy##Payload"); payload != nullptr && payload->Data) {
                        std::list<SR_UTILS_NS::SceneObject::Ptr> gameObjects = *(std::list<SR_UTILS_NS::SceneObject::Ptr>*)(payload->Data);
                        if (!gameObjects.empty()) {
                            entityRef.SetPathTo(gameObjects.front().DynamicCast<SR_UTILS_NS::Entity>());
                            changed = true;
                        }
                    }

                    if (auto&& payload = ImGui::AcceptDragDropPayload("InspectorComponent##Payload"); payload != nullptr && payload->Data) {
                        std::list<SR_UTILS_NS::Component::Ptr> components = *(std::list<SR_UTILS_NS::Component::Ptr>*)(payload->Data);
                        if (!components.empty()) {
                            entityRef.SetPathTo(components.front()->DynamicCast<SR_UTILS_NS::Entity>());
                            changed = true;
                        }
                    }

                    ImGui::EndDragDropTarget();
                }

                ImGui::EndChild();
            }

            if (ImGui::Button("Reset")) {
                entityRef.SetPathTo(nullptr);
            }

            ImGui::SameLine();

            if (ImGui::Button("Show")) {
                auto&& pHierarchy = pContext->GetWidget<Hierarchy>();

                if (auto&& pSceneObject = entityRef.GetSceneObject(); pSceneObject && pHierarchy) {
                    pHierarchy->SelectGameObject(pSceneObject);
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("Update")) {
                entityRef.UpdateTarget();
            }

            ImGui::SameLine();

            bool relative = entityRef.IsRelative();
            if (ImGui::Checkbox(SR_FORMAT_C("Relative##{}-{}", id, (void*)&entityRef), &relative)) {
                entityRef.SetRelative(relative);
                entityRef.UpdateTarget();
                changed = true;
            }

            ImGui::EndChild();
        }
        else {
            ImGui::PopStyleColor();
        }

        return changed;
    }
}