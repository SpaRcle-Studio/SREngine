//
// Created by Monika on 14.02.2022.
//

#include <Core/GUI/Inspector.h>

#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/ECS/TransformZero.h>
#include <Utils/Types/SafePtrLockGuard.h>

#include <Scripting/Base/Behaviour.h>
#include <Physics/Rigidbody.h>

#include <Graphics/UI/Sprite2D.h>
#include <Graphics/UI/Anchor.h>
#include <Graphics/UI/Canvas.h>
#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Graphics/GUI/Utils.h>
#include <Graphics/Font/Text.h>

namespace Framework::Core::GUI {
    Inspector::Inspector(Hierarchy* hierarchy)
        : Graphics::GUI::Widget("Inspector")
        , m_hierarchy(hierarchy)
    { }

    void Inspector::Draw() {
        SR_LOCK_GUARD

        if (!m_scene.RecursiveLockIfValid()) {
            return;
        }

        if (m_gameObject.TryRecursiveLockIfValid()) {
            if (bool v = m_gameObject->IsEnabled(); ImGui::Checkbox("Enabled", &v)) {
                auto&& cmd = new Framework::Core::Commands::GameObjectEnable(m_gameObject, v);
                Engine::Instance().GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);;
            }

            std::string gm_name = m_gameObject->GetName();
            if (ImGui::InputText("Name", &gm_name, ImGuiInputTextFlags_NoUndoRedo | ImGuiInputTextFlags_EnterReturnsTrue)) {
                auto&& cmd = new Framework::Core::Commands::GameObjectRename(m_gameObject, gm_name);
                Engine::Instance().GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
            }

            ImGui::Text("Entity id: %llu", m_gameObject->GetEntityId());

            ImGui::Separator();

            auto pTransform = m_gameObject->GetTransform();

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

        m_scene.Unlock();
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
            copyPtrComponent = DrawComponent<SR_PHYSICS_NS::Types::Rigidbody>(copyPtrComponent, "Rigidbody", index);
            copyPtrComponent = DrawComponent<SR_GTYPES_NS::Text>(copyPtrComponent, "Text", index);

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

    void Inspector::DrawTransform2D(SR_UTILS_NS::Transform2D *pTransform) const {
        TextCenter("Transform 2D");

        auto&& translation = pTransform->GetTranslation();
        if (Graphics::GUI::DrawVec3Control("Translation", translation, 0.f, 70.f, 0.01f))
            pTransform->SetTranslation(translation);

        auto&& rotation = pTransform->GetRotation();
        if (Graphics::GUI::DrawVec3Control("Rotation", rotation))
            pTransform->SetRotation(rotation);

        auto&& scale = pTransform->GetScale();
        if (Graphics::GUI::DrawVec3Control("Scale", scale, 1.f) && !scale.HasZero())
            pTransform->SetScale(scale);

        auto&& skew = pTransform->GetSkew();
        if (Graphics::GUI::DrawVec3Control("Skew", skew, 1.f) && !skew.HasZero())
            pTransform->SetSkew(skew);

        auto&& stretchTypes = SR_UTILS_NS::EnumReflector::GetNames<SR_UTILS_NS::Stretch>();
        auto stretch = static_cast<int>(SR_UTILS_NS::EnumReflector::GetIndex(pTransform->GetStretch()));

        if (ImGui::Combo("Stretch", &stretch, [](void* vec, int idx, const char** out_text){
            auto&& vector = reinterpret_cast<std::vector<std::string>*>(vec);
            if (idx < 0 || idx >= vector ->size())
                  return false;

            *out_text = vector->at(idx).c_str();

            return true;
        }, reinterpret_cast<void*>(&stretchTypes), stretchTypes.size())) {
            pTransform->SetStretch(SR_UTILS_NS::EnumReflector::At<SR_UTILS_NS::Stretch>(stretch));
        }
    }

    void Inspector::DrawTransform3D(SR_UTILS_NS::Transform3D *transform) const {
        TextCenter("Transform 3D");

        auto&& translation = transform->GetTranslation();
        if (Graphics::GUI::DrawVec3Control("Translation", translation, 0.f, 70.f, 0.01f)) {
            transform->SetTranslation(translation);
        }

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

    void SR_CORE_NS::GUI::Inspector::BackupTransform(const SR_UTILS_NS::GameObject::Ptr ptr, const std::function<void()>& operation) const
    {
        SR_HTYPES_NS::Marshal::Ptr pMarshal = ptr->GetTransform()->Save(nullptr, SR_UTILS_NS::SavableFlagBits::SAVABLE_FLAG_NONE);

        operation();

        auto&& cmd = new Framework::Core::Commands::GameObjectTransform(ptr, pMarshal);
        Engine::Instance().GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
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