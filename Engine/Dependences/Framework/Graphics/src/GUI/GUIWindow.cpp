//
// Created by Monika on 14.02.2021.
//

#include <GUI/GUIWindow.h>
#include <EntityComponentSystem/Scene.h>

void Framework::Graphics::GUI::GUIWindow::DrawChild(Framework::Helper::GameObject *root) noexcept {
    unsigned long i = 0;

    for (Helper::GameObject*  child : root->GetChildrenRef()) {
        if (child->HasChildren()) {
            bool open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                          g_node_flags_with_child |
                                          (child->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                          "%s", child->GetName().c_str()
            );

            CheckSelected(child);

            if (open)
                DrawChild(child);
        } else {
            ImGui::TreeNodeEx((void *) (intptr_t) i,
                              g_node_flags_without_child | (child->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                              "%s", child->GetName().c_str()
            );

            CheckSelected(child);
        }

        i++;
    }

    ImGui::TreePop();
}

void Framework::Graphics::GUI::GUIWindow::DrawHierarchy(Framework::Helper::Scene *scene) noexcept {
    auto root = scene->GetRootGameObjects();

    unsigned long i = 0;

    GUIWindow::m_shiftPressed = Helper::InputSystem::IsPressed(Helper::KeyCode::LShift);

    if (ImGui::TreeNodeEx(scene->GetName().c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3);

        for (Helper::GameObject* obj : root){
            if (obj->HasChildren()) {
                bool open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                              g_node_flags_with_child     | (obj->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                              "%s", obj->GetName().c_str());

                CheckSelected(obj);

                if (open)
                    DrawChild(obj);
            } else {
                ImGui::TreeNodeEx((void *) (intptr_t) i,
                                  g_node_flags_without_child | (obj->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                  "%s", obj->GetName().c_str());

                CheckSelected(obj);
            }

            i++;
        }

        ImGui::TreePop();
        ImGui::PopStyleVar();
    }
}

void Framework::Graphics::GUI::GUIWindow::CheckSelected(Framework::Helper::GameObject *gm) noexcept {
    if (ImGui::IsItemClicked()) {
        if (!m_shiftPressed)
            gm->GetScene()->UnselectAll();

        gm->SetSelect(true);
    }
}
