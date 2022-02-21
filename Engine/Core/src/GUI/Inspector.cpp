//
// Created by Monika on 14.02.2022.
//

#include "GUI/Inspector.h"
#include <GUI/Utils.h>
#include <EntityComponentSystem/Transform3D.h>

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
                m_gameObject->SetName(gm_name);

            ImGui::Text("Entity id: %llu", m_gameObject->GetEntityId());

            ImGui::Separator();
            TextCenter("Transform");

            auto&& transform = m_gameObject->GetTransform();

            auto&& translation = m_gameObject->GetTransform()->GetTranslation();
            if (Graphics::GUI::DrawVec3Control("Translation", translation))
                transform->SetTranslation(translation);

            auto&& rotation = m_gameObject->GetTransform()->GetRotation();
            if (Graphics::GUI::DrawVec3Control("Rotation", rotation))
                transform->SetRotation(rotation);

            auto&& scale = m_gameObject->GetTransform()->GetScale();
            if (Graphics::GUI::DrawVec3Control("Scale", scale, 1.f) && !scale.HasZero())
                transform->SetScale(scale);

            auto&& skew = m_gameObject->GetTransform()->GetSkew();
            if (Graphics::GUI::DrawVec3Control("Skew", skew, 1.f) && !skew.HasZero())
                transform->SetSkew(skew);

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