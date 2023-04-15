//
// Created by Monika on 15.04.2023.
//

#ifndef SRENGINE_DRAGNDROPHELPER_H
#define SRENGINE_DRAGNDROPHELPER_H

#include <Utils/ECS/EntityRef.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Component.h>
#include <Utils/GUI.h>

namespace SR_CORE_GUI_NS {
    SR_MAYBE_UNUSED static bool BeginDragDropTargetWindow(const char* payloadType);
    SR_MAYBE_UNUSED static bool BeginDragDropTargetField(const char* payloadType, ImVec2 size);

    /// ================================================================================================================

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

    bool DragDropTargetEntityRef(SR_UTILS_NS::EntityRef& entityRef, const char* payloadType, const char* id, int32_t index, float_t width = 300.f) {
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

        if (ImGui::BeginChild(SR_FORMAT_C("%s-%s-%i", id, payloadType, index), ImVec2(width, 50), true)) {
            ImGui::Text("%s:", id);

            ImGui::SameLine();

            if (ImGui::BeginChild(SR_FORMAT_C("%s-%s-%i-1", id, payloadType, index), ImVec2(200, 20), true)) {
                ImGui::Text("%s", preview.c_str());

                if (BeginDragDropTargetWindow(payloadType)) {
                    if (auto&& payload = ImGui::AcceptDragDropPayload(payloadType); payload != nullptr && payload->Data) {
                        std::list<SR_UTILS_NS::GameObject::Ptr> gameObjects = *(std::list<SR_UTILS_NS::GameObject::Ptr>*) (payload->Data);
                        if (!gameObjects.empty()) {
                            entityRef.SetPathTo(gameObjects.front().DynamicCast<SR_UTILS_NS::Entity>());
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

            }

            ImGui::SameLine();

            bool relative = entityRef.IsRelative();
            if (ImGui::Checkbox(SR_FORMAT_C("Relative##%s-%s-%i", id, payloadType, index), &relative)) {
                entityRef.SetRelative(relative);
                changed = true;
            }

            ImGui::EndChild();
        }

        return changed;
    }
}

#endif //SRENGINE_DRAGNDROPHELPER_H
