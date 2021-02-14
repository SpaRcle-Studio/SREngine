//
// Created by Monika on 14.02.2021.
//

#include <GUI/GUIWindow.h>
#include <EntityComponentSystem/Transform.h>
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

void Framework::Graphics::GUI::GUIWindow::DrawInspector(Framework::Helper::GameObject *gameObject) noexcept {
    //DrawTextOnCenter(gameObject->GetName());
    //ImGui::Text(("Tag:  " + gameObject->GetTag()).c_str());

    ImGui::Text("%s", ("Name: " + gameObject->GetName()).c_str());
    ImGui::Separator();
    DrawTextOnCenter("Transform");

    glm::vec3 position = gameObject->GetTransform()->GetPosition();
    glm::vec3 rotation = gameObject->GetTransform()->GetRotation();
    glm::vec3 scale = gameObject->GetTransform()->GetScale();

    if (ImGui::InputFloat3("Tr", &position[0]))
        gameObject->GetTransform()->SetPosition(position);
    if (ImGui::InputFloat3("Rt", &rotation[0]))
        gameObject->GetTransform()->SetRotation(rotation);
    if (ImGui::InputFloat3("Sc", &scale[0]))
        gameObject->GetTransform()->SetScale(scale);

    ImGui::TreePop();
}
