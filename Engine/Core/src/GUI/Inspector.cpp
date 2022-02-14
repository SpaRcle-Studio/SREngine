//
// Created by Monika on 14.02.2022.
//

#include "GUI/Inspector.h"

namespace Framework::Core::GUI {
    Inspector::Inspector()
        : Graphics::GUI::Widget("Inspector")
    { }

    void Inspector::Draw() {
        if (m_gameObject.LockIfValid()) {
            if (bool v = m_gameObject->IsActive(); ImGui::Checkbox("Enabled", &v))
                m_gameObject->SetActive(v);

            std::string gm_name = m_gameObject->GetName();
            if (ImGui::InputText("Name", &gm_name))
                m_gameObject->SetNameFromInspector(gm_name);

            ImGui::Text("Entity id: %llu", m_gameObject->GetEntityId());

            ImGui::Separator();
            TextCenter("Transform");

            auto position = m_gameObject->GetTransform()->GetPosition().ToGLM();
            auto rotation = m_gameObject->GetTransform()->GetRotation().ToGLM();
            auto scale    = m_gameObject->GetTransform()->GetScale().ToGLM();
            auto skew     = m_gameObject->GetTransform()->GetSkew().ToGLM();

            ImGui::Text("[Global]");

            if (ImGui::InputFloat3("G Tr", &position[0], "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
                m_gameObject->GetTransform()->SetGlobalPosition(position);

            if (ImGui::InputFloat3("G Rt", &rotation[0], "%.3f", ImGuiInputTextFlags_ReadOnly))
                m_gameObject->GetTransform()->SetRotation(rotation);

            if (ImGui::InputFloat3("G Sc", &scale[0], "%.3f", ImGuiInputTextFlags_ReadOnly))
                m_gameObject->GetTransform()->SetScale(scale);

            ImGui::Text("[Local]");

            position = m_gameObject->GetTransform()->GetPosition(true).ToGLM();
            rotation = m_gameObject->GetTransform()->GetRotation(true).ToGLM();
            scale    = m_gameObject->GetTransform()->GetScale(true).ToGLM();

            if (ImGui::InputFloat3("L Tr", &position[0], "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
                m_gameObject->GetTransform()->SetLocalPosition(position);

            if (ImGui::InputFloat3("L Rt", &rotation[0], "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
                m_gameObject->GetTransform()->SetLocalRotation(rotation);

            if (ImGui::InputFloat3("L Sc", &scale[0], "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
                m_gameObject->GetTransform()->SetLocalScale(position);

            if (ImGui::InputFloat3("L Sw", &skew[0], "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
                m_gameObject->GetTransform()->SetSkew(skew);

            DrawComponents();

            m_gameObject.Unlock();
        }
    }

    void Inspector::Update() {
        if (m_scene.LockIfValid()) {
            const auto selected = m_scene->GetSelected();
            m_gameObject.Replace(selected);
            m_scene.Unlock();
        }
    }

    void Inspector::SetScene(const World::Scene::Ptr& scene) {
        m_scene.Replace(scene);
    }

    void Inspector::DrawComponents() {
        if (ImGui::BeginPopupContextWindow("InspectorMenu")) {
            if (ImGui::BeginMenu("Add component")) {
                for (const auto& [name, id] : ComponentManager::Instance().GetComponentsNames()) {
                    if (ImGui::MenuItem(name.c_str())) {
                        m_gameObject->AddComponent(ComponentManager::Instance().CreateComponentOfName(name));
                        break;
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndPopup();
        }

        m_gameObject->ForEachComponent([this](Component* component) -> bool {
            if (ImGui::BeginPopupContextWindow("InspectorMenu")) {
                if (ImGui::BeginMenu("Remove component")) {
                    if (ImGui::MenuItem(component->GetComponentName().c_str())) {
                        m_gameObject->RemoveComponent(component);
                        goto exit;
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndPopup();
            }

            if (ImGui::CollapsingHeader(component->GetComponentName().c_str()))
                component->DrawOnInspector();

            return true;

            exit:
            ImGui::EndMenu();
            ImGui::EndPopup();
            return false;
        });
    }
}