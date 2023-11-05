//
// Created by Monika on 14.02.2022.
//

#include <Core/GUI/Inspector.h>

#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/ECS/TransformZero.h>
#include <Utils/Types/SafePtrLockGuard.h>

#include <Scripting/Base/Behaviour.h>

#include <Physics/3D/Rigidbody3D.h>
#include <Physics/2D/Rigidbody2D.h>

#include <Graphics/Types/Geometry/Sprite.h>
#include <Audio/Types/AudioSource.h>
#include <Graphics/UI/Canvas.h>
#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Graphics/GUI/Utils.h>
#include <Graphics/Font/ITextComponent.h>
#include <Graphics/Types/Geometry/SkinnedMesh.h>
#include <Graphics/Animations/Animator.h>
#include <Graphics/Animations/BoneComponent.h>

namespace SR_CORE_GUI_NS {
    Inspector::Inspector(Hierarchy* hierarchy)
        : SR_GRAPH_GUI_NS::Widget("Inspector")
        , m_hierarchy(hierarchy)
    { }

    void Inspector::Draw() {
        SR_LOCK_GUARD

        if (!m_scene.RecursiveLockIfValid()) {
            return;
        }

        if (ImGui::BeginTabBar("Inspector#TabBar")) {
            if (ImGui::BeginTabItem("GameObject")) {
                InspectGameObject();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Scene")) {
                InspectScene();
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        m_scene.Unlock();
    }

    void Inspector::InspectGameObject() {
        if (m_gameObject.TryRecursiveLockIfValid()) {
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

            if (bool v = m_gameObject->IsEnabled(); ImGui::Checkbox("Enabled", &v)) {
                auto&& cmd = new SR_CORE_NS::Commands::GameObjectEnable(pEngine, m_gameObject, v);
                pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
            }

            /// --------------------------------------------------------------------------------------------------------

            std::string gm_name = m_gameObject->GetName();
            if (ImGui::InputText("Name", &gm_name, ImGuiInputTextFlags_NoUndoRedo | ImGuiInputTextFlags_EnterReturnsTrue)) {
                auto&& cmd = new SR_CORE_NS::Commands::GameObjectRename(pEngine, m_gameObject, gm_name);
                pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
            }

            /// --------------------------------------------------------------------------------------------------------

            /// вызываем в потокобезопасном контексте, так как теги могут быть изменены извне
            SR_UTILS_NS::TagManager::Instance().Do([&](auto&& pSettings) {
                auto&& pTagManager = dynamic_cast<SR_UTILS_NS::TagManager*>(pSettings);
                auto&& tags = pTagManager->GetTags();
                auto&& tagIndex = static_cast<int>(pTagManager->GetTagIndex(m_gameObject->GetTag()));
                auto&& pTags = const_cast<std::vector<std::string>*>(&tags);

                if (ImGui::Combo("Tag", &tagIndex, [](void* vec, int idx, const char** out_text){
                    auto&& vector = reinterpret_cast<std::vector<std::string>*>(vec);
                    if (idx < 0 || idx >= vector->size())
                        return false;

                    *out_text = vector->at(idx).c_str();

                    return true;
                }, reinterpret_cast<void*>(pTags), tags.size())) {
                    /// TODO: переделать на комманды
                    m_gameObject->SetTag(pTagManager->GetTagByIndex(tagIndex));
                }
            });

            /// --------------------------------------------------------------------------------------------------------

            ImGui::Text("Entity id: %llu", m_gameObject->GetEntityId());

            ImGui::Separator();

            auto pTransform = m_gameObject->GetTransform();

            switch (pTransform->GetMeasurement()) {
                case SR_UTILS_NS::Measurement::Space2D:
                    DrawTransform2D(dynamic_cast<SR_UTILS_NS::Transform2D*>(pTransform));
                    break;
                case SR_UTILS_NS::Measurement::Space3D:
                    DrawTransform3D(dynamic_cast<SR_UTILS_NS::Transform3D*>(pTransform));
                    break;
                case SR_UTILS_NS::Measurement::SpaceZero:
                case SR_UTILS_NS::Measurement::Space4D:
                default:
                    break;
            }

            DrawSwitchTransform();

            DrawComponents(dynamic_cast<SR_UTILS_NS::IComponentable*>(m_gameObject.Get()));

            m_gameObject.Unlock();
        }
    }

    void Inspector::InspectScene() {
        std::string gm_name = m_scene->GetName();
        ImGui::InputText("Name", &gm_name, ImGuiInputTextFlags_ReadOnly);

        ImGui::Separator();

        DrawComponents(dynamic_cast<SR_UTILS_NS::IComponentable*>(m_scene.Get()));
    }

    void Inspector::Update(float_t dt) {
        SR_LOCK_GUARD

        if (auto&& selected = m_hierarchy->GetSelected(); selected.size() == 1) {
            if (*selected.begin() != m_gameObject) {
                ResetWeakStorage();
            }
            m_gameObject.Replace(*selected.begin());
            SRAssert(m_gameObject);
        }
        else {
            m_gameObject.Replace(SR_UTILS_NS::GameObject::Ptr());
        }
    }

    void Inspector::SetScene(const SR_WORLD_NS::Scene::Ptr& scene) {
        SR_LOCK_GUARD

        m_scene = scene;
    }

    void Inspector::DrawComponents(SR_UTILS_NS::IComponentable* pIComponentable) {
        ImGui::Separator();

        SR_GRAPH_GUI_NS::DrawTextOnCenter("Components");

        ImGuiStyle& style = ImGui::GetStyle();

        float_t button_sz = ImGui::GetFrameHeight();
        float_t spacing = style.ItemInnerSpacing.x;
        float_t width = (ImGui::GetWindowWidth() - 70.f) - spacing * 2.0f - button_sz * 2.0f;

        ImGui::PushItemWidth(width);
        if (ImGui::BeginCombo("Add component", nullptr, ImGuiComboFlags_NoArrowButton)) {
            for (const auto&[name, id] : SR_UTILS_NS::ComponentManager::Instance().GetComponentsNames()) {
                if (ImGui::Selectable(name.c_str(), false)) {
                    auto &&pNewComponent = SR_UTILS_NS::ComponentManager::Instance().CreateComponentOfName(name);
                    pIComponentable->AddComponent(pNewComponent);
                }
            }
            ImGui::EndCombo();
        }
        ImGui::PopItemWidth();

        uint32_t index = 0;
        pIComponentable->ForEachComponent([&](SR_UTILS_NS::Component* component) -> bool {
            SR_UTILS_NS::Component* copyPtrComponent = component;

            SRAssert1Once(copyPtrComponent->GetParent());

            copyPtrComponent = DrawComponent<SR_SCRIPTING_NS::Behaviour>(copyPtrComponent, "Behaviour", index);
            copyPtrComponent = DrawComponent<SR_GTYPES_NS::Camera>(copyPtrComponent, "Camera", index);
            copyPtrComponent = DrawComponent<SR_GTYPES_NS::Mesh3D>(copyPtrComponent, "Mesh3D", index);
            copyPtrComponent = DrawComponent<SR_GTYPES_NS::SkinnedMesh>(copyPtrComponent, "SkinnedMesh", index);
            copyPtrComponent = DrawComponent<SR_GTYPES_NS::ProceduralMesh>(copyPtrComponent, "ProceduralMesh", index);
            copyPtrComponent = DrawComponent<SR_GTYPES_NS::Sprite>(copyPtrComponent, "Sprite", index);
            copyPtrComponent = DrawComponent<SR_GRAPH_NS::UI::Anchor>(copyPtrComponent, "Anchor", index);
            copyPtrComponent = DrawComponent<SR_GRAPH_NS::UI::Canvas>(copyPtrComponent, "Canvas", index);
            copyPtrComponent = DrawComponent<SR_PTYPES_NS::Rigidbody3D>(copyPtrComponent, "Rigidbody3D", index);
            copyPtrComponent = DrawComponent<SR_GTYPES_NS::Text2D>(copyPtrComponent, "Text2D", index);
            copyPtrComponent = DrawComponent<SR_GTYPES_NS::Text3D>(copyPtrComponent, "Text3D", index);
            copyPtrComponent = DrawComponent<SR_ANIMATIONS_NS::Animator>(copyPtrComponent, "Animator", index);
            copyPtrComponent = DrawComponent<SR_ANIMATIONS_NS::Skeleton>(copyPtrComponent, "Skeleton", index);
            copyPtrComponent = DrawComponent<SR_ANIMATIONS_NS::BoneComponent>(copyPtrComponent, "Bone", index);
            copyPtrComponent = DrawComponent<SR_UTILS_NS::LookAtComponent>(copyPtrComponent, "LookAtComponent", index);
            copyPtrComponent = DrawComponent<SR_AUDIO_NS::AudioSource>(copyPtrComponent, "AudioSource", index);
            copyPtrComponent = DrawComponent<SR_AUDIO_NS::AudioListener>(copyPtrComponent, "AudioListener", index);

            if (copyPtrComponent != component && copyPtrComponent) {
                SR_LOG("Inspector::DrawComponents() : component \"" + component->GetComponentName() + "\" has been replaced.");

                pIComponentable->RemoveComponent(component);
                pIComponentable->AddComponent(copyPtrComponent);

                return false;
            }

            return true;
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

        if (ImGui::BeginCombo("Anchor", SR_UTILS_NS::EnumReflector::ToString(pTransform->GetAnchor()).c_str())) {
            auto&& selectables = SR_UTILS_NS::EnumReflector::GetNames<SR_UTILS_NS::Anchor>();
            for (auto&& selectable : selectables) {
                if (ImGui::Selectable(selectable.c_str())) {
                    ImGui::SetItemDefaultFocus();
                    pTransform->SetAnchor(SR_UTILS_NS::EnumReflector::FromString<SR_UTILS_NS::Anchor>(selectable));
                }
            }

            ImGui::EndCombo();
        }

        auto&& stretchTypes = SR_UTILS_NS::EnumReflector::GetNames<SR_UTILS_NS::Stretch>();

        auto stretch = static_cast<int32_t>(SR_UTILS_NS::EnumReflector::GetIndex<SR_UTILS_NS::Stretch>(pTransform->GetStretch()));

        if (ImGui::Combo("Stretch", &stretch, [](void* vec, int idx, const char** out_text){
            auto&& vector = reinterpret_cast<std::vector<std::string>*>(vec);
            if (idx < 0 || idx >= vector ->size())
                  return false;

            *out_text = vector->at(idx).c_str();

            return true;
        }, const_cast<void*>(reinterpret_cast<const void*>(&stretchTypes)), stretchTypes.size())) {
            pTransform->SetStretch(SR_UTILS_NS::EnumReflector::At<SR_UTILS_NS::Stretch>(stretch));
        }

        SR_GRAPH_GUI_NS::EnumCombo<SR_UTILS_NS::PositionMode>("Position mode", pTransform->GetPositionMode(), [pTransform](auto&& value) {
            pTransform->SetPositionMode(value);
        });

        ImGui::Separator();

        SR_GRAPH_GUI_NS::DrawTextOnCenter("Sorting");

        int32_t priority = pTransform->GetLocalPriority();
        if (ImGui::InputInt("Priority", &priority)) {
            pTransform->SetLocalPriority(priority);
        }

        bool isRelativePriority = pTransform->IsRelativePriority();
        if (ImGui::Checkbox("Relative", &isRelativePriority)) {
            pTransform->SetRelativePriority(isRelativePriority);
        }

        ImGui::Separator();
    }

    void Inspector::DrawTransform3D(SR_UTILS_NS::Transform3D *transform) {
        TextCenter("Transform 3D");

        auto&& oldTransform = transform->Copy();
        bool changed = false;
        auto&& translation = transform->GetTranslation();
        if (Graphics::GUI::DrawVec3Control("Translation", translation, 0.f, 70.f, 0.01f)) {
            transform->SetTranslation(translation);
            changed = true;
        }
        auto&& rotation = transform->GetRotation();  
        if (Graphics::GUI::DrawVec3Control("Rotation", rotation)) {
            transform->SetRotation(rotation);
            changed = true;
        }
        auto&& scale = transform->GetScale();
        if (Graphics::GUI::DrawVec3Control("Scale", scale, 1.f) && !scale.HasZero()) {
            transform->SetScale(scale);
            changed = true;
        }
        auto&& skew = transform->GetSkew();
        if (Graphics::GUI::DrawVec3Control("Skew", skew, 1.f) && !skew.HasZero()) {
            transform->SetSkew(skew);
            changed = true;
        }

        if (!m_isUsed && changed) {
            SR_SAFE_DELETE_PTR(m_oldTransformMarshal)
            m_oldTransformMarshal = oldTransform->Save(SR_UTILS_NS::SavableSaveData(nullptr, SR_UTILS_NS::SavableFlagBits::SAVABLE_FLAG_NONE));
            m_isUsed = true;
        }
        if (m_isUsed && SR_UTILS_NS::Input::Instance().GetMouseUp(SR_UTILS_NS::MouseCode::MouseLeft)) {
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
            auto&& cmd = new SR_CORE_NS::Commands::GameObjectTransform(pEngine, transform->GetGameObject(), m_oldTransformMarshal->CopyPtr());
            pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);

            SR_SAFE_DELETE_PTR(m_oldTransformMarshal)
            m_isUsed = false;
        }

        SR_SAFE_DELETE_PTR(oldTransform)
    }

    void SR_CORE_NS::GUI::Inspector::BackupTransform(const SR_UTILS_NS::GameObject::Ptr& ptr, const std::function<void()>& operation) const
    {
        ///SR_HTYPES_NS::Marshal::Ptr pMarshal = ptr->GetTransform()->Save(nullptr, SR_UTILS_NS::SavableFlagBits::SAVABLE_FLAG_NONE);
        ///
        ///operation();
        ///
        ///auto&& cmd = new Framework::Core::Commands::GameObjectTransform(ptr, pMarshal);
        ///Engine::Instance().GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
    }

    void Inspector::DrawSwitchTransform() {
        auto&& pTransform = m_gameObject->GetTransform();

        const char* space_types[] = { "Zero (Holder)", "1D", "2D", "3D", "4D" };
        auto item_current = static_cast<int32_t>(pTransform->GetMeasurement());
        if (ImGui::Combo("Transform type", &item_current, space_types, IM_ARRAYSIZE(space_types))) {
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