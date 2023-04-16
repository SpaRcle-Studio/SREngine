//
// Created by Monika on 15.04.2023.
//

#include <Core/GUI/DragNDropHelper.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Component.h>
#include <Utils/GUI.h>

namespace SR_CORE_GUI_NS {
    bool BeginDragDropTargetWindow(const char* payloadType) {
        ImRect inner_rect = ImGui::GetCurrentWindow()->InnerRect;

        if (ImGui::BeginDragDropTargetCustom(inner_rect, ImGui::GetID("##WindowBgArea"))) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(payloadType, ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect))
            {
                if (payload->IsPreview()) {
                    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
                    draw_list->AddRectFilled(inner_rect.Min, inner_rect.Max, ImGui::GetColorU32(ImGuiCol_DragDropTarget, 0.05f));
                    draw_list->AddRect(inner_rect.Min, inner_rect.Max, ImGui::GetColorU32(ImGuiCol_DragDropTarget), 0.0f, 0, 2.0f);
                }

                if (payload->IsDelivery()) {
                    return true;
                }

                ImGui::EndDragDropTarget();
            }
        }

        return false;
    }

    bool DragDropTargetEntityRef(EditorGUI* pContext, SR_UTILS_NS::EntityRef& entityRef, const char* id, int32_t index, float_t width) {
        std::string preview;

        if (auto&& pGameObject = entityRef.GetGameObject()) {
            preview = "[GMJ] " + pGameObject->GetName();
        }
        else if (auto&& pComponent = entityRef.GetComponent()) {
            preview = "[CMP] " + pComponent->GetComponentName();
        }
        else {
            preview = "[None]";
        }

        bool changed = false;

        if (ImGui::BeginChild(SR_FORMAT_C("%s-%i", id, index), ImVec2(width, 50), true)) {
            ImGui::Text("%s:", id);

            ImGui::SameLine();

            if (ImGui::BeginChild(SR_FORMAT_C("%s-%i-1", id, index), ImVec2(200, 20), true)) {
                ImGui::Text("%s", preview.c_str());

                if (ImGui::BeginDragDropTarget()) {
                    if (auto&& payload = ImGui::AcceptDragDropPayload("Hierarchy##Payload"); payload != nullptr && payload->Data) {
                        std::list<SR_UTILS_NS::GameObject::Ptr> gameObjects = *(std::list<SR_UTILS_NS::GameObject::Ptr>*)(payload->Data);
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

                if (auto&& pGameObject = entityRef.GetGameObject(); pGameObject && pHierarchy) {
                    pHierarchy->SelectGameObject(pGameObject);
                }
            }

            ImGui::SameLine();

            bool relative = entityRef.IsRelative();
            if (ImGui::Checkbox(SR_FORMAT_C("Relative##%s-%i", id, index), &relative)) {
                entityRef.SetRelative(relative);
                changed = true;
            }

            ImGui::EndChild();
        }

        return changed;
    }
}