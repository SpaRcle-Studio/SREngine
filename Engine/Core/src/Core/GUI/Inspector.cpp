//
// Created by Monika on 14.02.2022.
//

#include <Core/GUI/Inspector.h>

#include <GUI/Utils.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/Types/SafePtrLockGuard.h>
#include <Scripting/Base/Behaviour.h>
#include <Physics/3D/Rigidbody3D.h>
#include <UI/Sprite2D.h>
#include <UI/Anchor.h>
#include <UI/Canvas.h>
#include <Utils/ECS/TransformZero.h>
#include <Types/Geometry/ProceduralMesh.h>

namespace Framework::Core::GUI {
    Inspector::Inspector(Hierarchy* hierarchy)
        : Graphics::GUI::Widget("Inspector")
        , m_hierarchy(hierarchy)
    { }

    void Inspector::Draw() {
        SR_LOCK_GUARD

        if (m_gameObject.TryRecursiveLockIfValid()) {
            if (bool v = m_gameObject->IsEnabled(); ImGui::Checkbox("Enabled", &v)) {
                m_gameObject->SetEnabled(v);
            }

            std::string gm_name = m_gameObject->GetName();
            if (ImGui::InputText("Name", &gm_name))
                m_gameObject->SetName(gm_name);

            ImGui::Text("Entity id: %llu", m_gameObject->GetEntityId());

            ImGui::Separator();

            auto&& pTransform = m_gameObject->GetTransform();

            switch (pTransform->GetMeasurement()) {
                case SR_UTILS_NS::Measurement::Space2D:
                    DrawTransform2D(dynamic_cast<SR_UTILS_NS::Transform2D *>(pTransform));
                    break;
                case SR_UTILS_NS::Measurement::Space3D:
                    DrawTransform3D(dynamic_cast<SR_UTILS_NS::Transform3D *>(pTransform));
                    break;
                case SR_UTILS_NS::Measurement::SpaceZero:
                case SR_UTILS_NS::Measurement::Space4D:
                default:
                    break;
            }

            DrawSwitchTransform();

            DrawComponents();

            m_gameObject.Unlock();
        }
    }

    void Inspector::Update() {
        SR_LOCK_GUARD

        if (auto&& selected = m_hierarchy->GetSelected(); selected.size() == 1) {
            m_gameObject.Replace(*selected.begin());
        }
        else {
            m_gameObject.Replace(SR_UTILS_NS::GameObject::Ptr());
        }
    }

    void Inspector::SetScene(const SR_WORLD_NS::Scene::Ptr& scene) {
        SR_LOCK_GUARD

        m_scene = scene;
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
            copyPtrComponent = DrawComponent<SR_GTYPES_NS::Mesh3D>(copyPtrComponent, "Mesh3D", index);
            copyPtrComponent = DrawComponent<SR_GTYPES_NS::ProceduralMesh>(copyPtrComponent, "ProceduralMesh", index);
            copyPtrComponent = DrawComponent<SR_GRAPH_NS::UI::Sprite2D>(copyPtrComponent, "Sprite2D", index);
            copyPtrComponent = DrawComponent<SR_GRAPH_NS::UI::Anchor>(copyPtrComponent, "Anchor", index);
            copyPtrComponent = DrawComponent<SR_GRAPH_NS::UI::Canvas>(copyPtrComponent, "Canvas", index);
            copyPtrComponent = DrawComponent<SR_PHYSICS_NS::Types::Rigidbody3D>(copyPtrComponent, "Rigidbody3D", index);

            if (copyPtrComponent != component && copyPtrComponent) {
                SR_LOG("Inspector::DrawComponents() : component \"" + component->GetComponentName() + "\" has been replaced.");

                m_gameObject->ReplaceComponent(component, copyPtrComponent);

                return false;
            }

            return true;

        exit:
            ImGui::EndMenu();
            ImGui::EndPopup();

            return false;
        });
    }

    void Inspector::DrawTransform2D(SR_UTILS_NS::Transform2D *transform) const {
        TextCenter("Transform 2D");

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

    void Inspector::DrawTransform3D(SR_UTILS_NS::Transform3D *transform) const {
        TextCenter("Transform 3D");

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

    void Inspector::DrawSwitchTransform() {
        auto&& pTransform = m_gameObject->GetTransform();

        const char* space_types[] = { "Zero", "1D", "2D", "3D", "4D" };
        auto item_current = static_cast<int32_t>(pTransform->GetMeasurement());
        if (ImGui::Combo("Measurement", &item_current, space_types, IM_ARRAYSIZE(space_types))) {
            switch (static_cast<SR_UTILS_NS::Measurement>(item_current)) {
                case SR_UTILS_NS::Measurement::SpaceZero:
                    m_gameObject->SetTransform(new SR_UTILS_NS::TransformZero());
                    break;
                case SR_UTILS_NS::Measurement::Space2D:
                    m_gameObject->SetTransform(new SR_UTILS_NS::Transform2D());
                    break;
                case SR_UTILS_NS::Measurement::Space3D:
                    m_gameObject->SetTransform(new SR_UTILS_NS::Transform3D());
                    break;
                case SR_UTILS_NS::Measurement::Space4D:
                default:
                    break;
            }
        }
    }
}