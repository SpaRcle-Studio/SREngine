//
// Created by Monika on 14.02.2022.
//

#include <Core/GUI/Inspector.h>

#include <GUI/Utils.h>
#include <Utils/ECS/Transform3D.h>
#include <Scripting/Base/Behaviour.h>

namespace Framework::Core::GUI {
    Inspector::Inspector(Hierarchy* hierarchy)
        : Graphics::GUI::Widget("Inspector")
        , m_hierarchy(hierarchy)
    { }

    void Inspector::Draw() {
        SR_LOCK_GUARD

        if (m_gameObject.TryLockIfValid()) {
            if (bool v = m_gameObject->IsEnabled(); ImGui::Checkbox("Enabled", &v)) {
                m_gameObject->SetEnabled(v);
            }

            std::string gm_name = m_gameObject->GetName();
            if (ImGui::InputText("Name", &gm_name))
                m_gameObject->SetName(gm_name);

            ImGui::Text("Entity id: %llu", m_gameObject->GetEntityId());

            ImGui::Separator();

            DrawTransform(m_gameObject->GetTransform());
            DrawComponents();

            m_gameObject.Unlock();
        }
    }

    void Inspector::Update() {
        SR_LOCK_GUARD

        if (auto&& selected = m_hierarchy->GetSelected(); selected.size() == 1) {
            m_gameObject.Replace(*selected.begin());
        }
        else
            m_gameObject.Replace(SR_UTILS_NS::GameObject::Ptr());
    }

    void Inspector::DrawComponents() {
        if (ImGui::BeginPopupContextWindow("InspectorMenu")) {
            if (ImGui::BeginMenu("Add component")) {
                for (const auto& [name, id] : SR_UTILS_NS::ComponentManager::Instance().GetComponentsNames()) {
                    if (ImGui::MenuItem(name.c_str())) {
                        m_gameObject->AddComponent(SR_UTILS_NS::ComponentManager::Instance().CreateComponentOfName(name));
                        break;
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndPopup();
        }

        uint32_t index = 0;
        m_gameObject->ForEachComponent([&](SR_UTILS_NS::Component* component) -> bool {
            SR_UTILS_NS::Component* copyPtrComponent = component;

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

            copyPtrComponent = DrawComponent<SR_SCRIPTING_NS::Behaviour>(copyPtrComponent, "Behaviour", index);
            copyPtrComponent = DrawComponent<SR_GTYPES_NS::Camera>(copyPtrComponent, "Camera", index);
            copyPtrComponent = DrawComponent<Graphics::Types::Mesh3D>(copyPtrComponent, "Mesh3D", index);

            if (copyPtrComponent != component && copyPtrComponent) {
                SR_LOG("Inspector::DrawComponents() : component \"" + component->GetComponentName() + "\" has been replaced.");

                m_gameObject->RemoveComponent(component);
                m_gameObject->AddComponent(copyPtrComponent);

                return false;
            }

            return true;

        exit:
            ImGui::EndMenu();
            ImGui::EndPopup();

            return false;
        });
    }

    void Inspector::DrawTransform(Helper::Transform3D *transform) const {
        TextCenter("Transform");

        auto&& translation = transform->GetTranslation();
        if (Graphics::GUI::DrawVec3Control("Translation", translation, 0.f, 70.f, 0.01f))
            transform->SetTranslation(translation);

        auto&& rotation = transform->GetRotation();
        if (Graphics::GUI::DrawVec3Control("Rotation", rotation))
            transform->SetRotation(rotation);

        auto&& scale = transform->GetScale();
        if (Graphics::GUI::DrawVec3Control("Scale", scale, 1.f) && !scale.HasZero())
            transform->SetScale(scale);

        auto&& skew = transform->GetSkew();
        if (Graphics::GUI::DrawVec3Control("Skew", skew, 1.f) && !skew.HasZero())
            transform->SetSkew(skew);
    }
}