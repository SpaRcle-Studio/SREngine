//
// Created by Monika on 14.02.2022.
//

#include <Core/GUI/Inspector.h>

#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/ECS/TransformZero.h>
#include <Utils/ECS/LayerManager.h>
#include <Utils/Types/SafePtrLockGuard.h>
#include <Utils/World/ScenePrefabLogic.h>

#include <Scripting/Base/Behaviour.h>

#include <Physics/3D/Rigidbody3D.h>
#include <Physics/2D/Rigidbody2D.h>

#include <Graphics/Types/Geometry/Sprite.h>
#include <Audio/Types/AudioSource.h>
#include <Graphics/UI/Canvas.h>
#include <Graphics/UI/Gizmo.h>
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
        SR_LOCK_GUARD;

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

            if (m_gameObject->IsPrefab()) {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(0, 1, 1, 1), "(The changes will not be saved)");
            }

            if (m_gameObject->IsDirty()) {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "(Is dirty)");
            }

            if (m_gameObject->IsDontSave()) {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "(Dont Save)");
            }

            /// --------------------------------------------------------------------------------------------------------

            std::string gm_name = m_gameObject->GetName();
            if (ImGui::InputText("Name", &gm_name, ImGuiInputTextFlags_NoUndoRedo | ImGuiInputTextFlags_EnterReturnsTrue)) {
                auto&& cmd = new SR_CORE_NS::Commands::GameObjectRename(pEngine, m_gameObject, gm_name);
                pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
            }

            /// --------------------------------------------------------------------------------------------------------

            InspectTag(m_gameObject->GetTag(), [this](auto&& tag){
                m_gameObject->SetTag(tag);
            });

            InspectLayer(m_gameObject->GetLocalLayer(), [this](auto&& tag) {
                m_gameObject->SetLayer(tag);
            });

            /// --------------------------------------------------------------------------------------------------------

            ImGui::Text("Entity id: %llu", m_gameObject->GetEntityId());

            ImGui::Separator();

            auto&& pTransform = m_gameObject->GetTransform();
            auto&& pOldTransform = pTransform->Copy();

            bool changed = false;

            switch (pTransform->GetMeasurement()) {
                case SR_UTILS_NS::Measurement::Space2D:
                    changed |= DrawTransform2D(dynamic_cast<SR_UTILS_NS::Transform2D*>(pTransform));
                    break;
                case SR_UTILS_NS::Measurement::Space3D:
                    changed |= DrawTransform3D(dynamic_cast<SR_UTILS_NS::Transform3D*>(pTransform));
                    break;
                case SR_UTILS_NS::Measurement::SpaceZero:
                case SR_UTILS_NS::Measurement::Space4D:
                default:
                    break;
            }

            changed |= DrawSwitchTransform();

            if (!m_isUsed && changed) {
                SR_SAFE_DELETE_PTR(m_oldTransformMarshal)
                m_oldTransformMarshal = pOldTransform->Save(SR_UTILS_NS::SavableContext(nullptr, SR_UTILS_NS::SavableFlagBits::SAVABLE_FLAG_NONE));
                m_isUsed = true;
            }

            if (m_isUsed && SR_UTILS_NS::Input::Instance().GetMouseUp(SR_UTILS_NS::MouseCode::MouseLeft)) {
                auto&& cmd = new SR_CORE_NS::Commands::GameObjectTransform(pEngine, m_gameObject, m_oldTransformMarshal->CopyPtr());
                pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);

                SR_SAFE_DELETE_PTR(m_oldTransformMarshal)
                m_isUsed = false;
            }

            SR_SAFE_DELETE_PTR(pOldTransform)

            DrawComponents(dynamic_cast<SR_UTILS_NS::IComponentable*>(m_gameObject.Get()));

            m_gameObject.Unlock();
        }
    }

    void Inspector::InspectScene() {
        std::string gm_name = m_scene->GetName();
        ImGui::InputText("Name", &gm_name, ImGuiInputTextFlags_ReadOnly);

        auto&& pLogic = m_scene->GetLogicBase().DynamicCast<SR_WORLD_NS::ScenePrefabLogic>();

        if (pLogic) {
            InspectTag(pLogic->GetTag(), [pLogic](auto &&tag) {
                pLogic->SetTag(tag);
            });

            InspectLayer(pLogic->GetLayer(), [pLogic](auto &&tag) {
                pLogic->SetLayer(tag);
            });
        }

        ImGui::Separator();

        DrawComponents(dynamic_cast<SR_UTILS_NS::IComponentable*>(m_scene.Get()));
    }

    void Inspector::Update(float_t dt) {
        SR_LOCK_GUARD;

        if (auto&& selected = m_hierarchy->GetSelected(); selected.size() == 1) {
            if (*selected.begin() != m_gameObject) {
                ResetWeakStorage();
            }
            m_gameObject = *selected.begin();
            SRAssert(m_gameObject);
        }
        else {
            m_gameObject = SR_UTILS_NS::GameObject::Ptr();
        }
    }

    void Inspector::SetScene(const SR_WORLD_NS::Scene::Ptr& scene) {
        SR_LOCK_GUARD;

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
            for (auto&& name : SR_UTILS_NS::ComponentManager::Instance().GetComponentsNames()) {
                if (ImGui::Selectable(name.c_str(), false)) {
                    auto&& pNewComponent = SR_UTILS_NS::ComponentManager::Instance().CreateComponentOfName(name);
                    pIComponentable->AddComponent(pNewComponent);
                }
            }
            ImGui::EndCombo();
        }
        ImGui::PopItemWidth();

        uint32_t index = 0;

        pIComponentable->ForEachComponent([&](SR_UTILS_NS::Component* pComponent) -> bool {
            DrawComponent(pComponent, index);
            return true;
        });
    }

    bool Inspector::DrawTransform2D(SR_UTILS_NS::Transform2D *pTransform) const {
        TextCenter("Transform 2D");

        bool changed = false;

        auto&& translation = pTransform->GetTranslation();
        if (SR_GRAPH_GUI_NS::DrawVec3Control("Translation", translation, 0.f, 0.01f)) {
            pTransform->SetTranslation(translation);
            changed = true;
        }

        auto&& rotation = pTransform->GetRotation();
        if (SR_GRAPH_GUI_NS::DrawVec3Control("Rotation", rotation)) {
            pTransform->SetRotation(rotation);
            changed = true;
        }

        auto&& scale = pTransform->GetScale();
        if (SR_GRAPH_GUI_NS::DrawVec3Control("Scale", scale, 1.f, 0.01f) && !scale.HasZero()) {
            pTransform->SetScale(scale);
            changed = true;
        }

        auto&& skew = pTransform->GetSkew();
        if (SR_GRAPH_GUI_NS::DrawVec3Control("Skew", skew, 1.f, 0.01f) && !skew.HasZero()) {
            pTransform->SetSkew(skew);
            changed = true;
        }

        SR_GRAPH_GUI_NS::EnumCombo<SR_UTILS_NS::Anchor>("Anchor", pTransform->GetAnchor(), [&changed, pTransform](auto&& value) {
            pTransform->SetAnchor(value);
            changed = true;
        });

        SR_GRAPH_GUI_NS::EnumCombo<SR_UTILS_NS::FixedSize>("Fixed size", pTransform->GetFixedSize(), [&changed, pTransform](auto&& value) {
            pTransform->SetFixedSize(value);
            changed = true;
        });

        SR_GRAPH_GUI_NS::EnumCombo<SR_UTILS_NS::Stretch>("Stretch", pTransform->GetStretch(), [&changed, pTransform](auto&& value) {
            pTransform->SetStretch(value);
            changed = true;
        });

        SR_GRAPH_GUI_NS::EnumCombo<SR_UTILS_NS::PositionMode>("Position mode", pTransform->GetPositionMode(), [&changed, pTransform](auto&& value) {
            pTransform->SetPositionMode(value);
            changed = true;
        });

        ImGui::Separator();

        SR_GRAPH_GUI_NS::DrawTextOnCenter("Sorting");

        int32_t priority = pTransform->GetLocalPriority();
        if (ImGui::InputInt("Priority", &priority)) {
            pTransform->SetLocalPriority(priority);
            changed = true;
        }

        bool isRelativePriority = pTransform->IsRelativePriority();
        if (ImGui::Checkbox("Relative", &isRelativePriority)) {
            pTransform->SetRelativePriority(isRelativePriority);
            changed = true;
        }

        ImGui::Separator();

        return changed;
    }

    bool Inspector::DrawTransform3D(SR_UTILS_NS::Transform3D *transform) {
        TextCenter("Transform 3D");

        bool changed = false;

        auto&& translation = transform->GetTranslation();
        if (SR_GRAPH_GUI_NS::DrawVec3Control("Translation", translation, 0.f, 0.01f)) {
            transform->SetTranslation(translation);
            changed = true;
        }

        auto&& rotation = transform->GetRotation();  
        if (SR_GRAPH_GUI_NS::DrawVec3Control("Rotation", rotation)) {
            transform->SetRotation(rotation);
            changed = true;
        }

        auto&& scale = transform->GetScale();
        if (SR_GRAPH_GUI_NS::DrawVec3Control("Scale", scale, 1.f, 0.01f) && !scale.HasZero()) {
            transform->SetScale(scale);
            changed = true;
        }

        auto&& skew = transform->GetSkew();
        if (SR_GRAPH_GUI_NS::DrawVec3Control("Skew", skew, 1.f, 0.01f) && !skew.HasZero()) {
            transform->SetSkew(skew);
            changed = true;
        }

        return changed;
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

    bool Inspector::DrawSwitchTransform() {
        auto&& pTransform = m_gameObject->GetTransform();

        const char* space_types[] = { "Zero (Holder)", "1D", "2D", "3D", "4D" };
        auto item_current = static_cast<int32_t>(pTransform->GetMeasurement());
        if (ImGui::Combo("Transform type", &item_current, space_types, IM_ARRAYSIZE(space_types))) {
            switch (static_cast<SR_UTILS_NS::Measurement>(item_current)) {
                case SR_UTILS_NS::Measurement::SpaceZero:
                    m_gameObject->SetTransform(new SR_UTILS_NS::TransformZero());
                    return true;
                case SR_UTILS_NS::Measurement::Space2D:
                    m_gameObject->SetTransform(new SR_UTILS_NS::Transform2D());
                    return true;
                case SR_UTILS_NS::Measurement::Space3D:
                    m_gameObject->SetTransform(new SR_UTILS_NS::Transform3D());
                    return true;
                case SR_UTILS_NS::Measurement::Space4D:
                default:
                    break;
            }
        }

        return false;
    }

    void Inspector::DrawComponentProperties(SR_UTILS_NS::Component* pComponent) {
        auto&& properties = pComponent->GetComponentProperties();
        SR_CORE_GUI_NS::DrawPropertyContext context;
        context.pEditor = dynamic_cast<EditorGUI*>(GetManager());
        SR_CORE_GUI_NS::DrawPropertyContainer(context, &properties);
    }

    void Inspector::DrawComponent(SR_UTILS_NS::Component* pComponent, uint32_t &index) {
        auto&& pContext = dynamic_cast<EditorGUI*>(GetManager());

        if (!pComponent || !pContext) {
            return;
        }

        SRAssert1Once(pComponent->Valid());

        ++index;

        if (ImGui::BeginChild("InspectorComponent")) {
            bool enabled = pComponent->IsEnabled();
            if (ImGui::Checkbox(SR_FORMAT("##{}{}ckb", pComponent->GetComponentName().c_str(), (void*)pComponent).c_str(), &enabled)) {
                pComponent->SetEnabled(enabled);
            }

            ImGui::SameLine();

            const bool isOpened = ImGui::CollapsingHeader(SR_FORMAT("[{}] {}", index, pComponent->GetComponentName().c_str()).c_str());

            if (!ImGui::GetDragDropPayload() && ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
                m_pointersHolder = { pComponent->DynamicCast<SR_UTILS_NS::Component>() };
                ImGui::SetDragDropPayload("InspectorComponent##Payload", &m_pointersHolder, sizeof(std::vector<SR_UTILS_NS::Component::Ptr>), ImGuiCond_Once);
                ImGui::Text("%s ->", pComponent->GetComponentName().c_str());
                ImGui::EndDragDropSource();
            }

            ImGui::SameLine(); ImGui::Text(" ");

            if (pComponent->ExecuteInEditMode()) {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(0, 1, 0, 1), "[Editor mode]");
            }

            if (pComponent->IsDontSave()) {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "[Dont save]");
            }

            if (!pComponent->IsAttached()) {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "[Loaded]");
            }

            if (isOpened) {
                SR_CORE_GUI_NS::DrawPropertyContext context;
                context.pEditor = pContext;

                if (SR_CORE_GUI_NS::DrawPropertyContainer(context, &pComponent->GetEntityMessages())) {
                    ImGui::Separator();
                }

                if (!ComponentDrawer::DrawComponentOld(pComponent, pContext, index)) {
                    DrawComponentProperties(pComponent);
                }
            }

            if (ImGui::BeginPopupContextWindow("InspectorMenu")) {
                if (ImGui::BeginMenu("Remove component")) {
                    if (ImGui::MenuItem(pComponent->GetComponentName().c_str())) {
                        pComponent->GetParent()->RemoveComponent(pComponent);
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndPopup();
            }
            ImGui::EndChild();
        }
    }

    void Inspector::InspectTag(SR_UTILS_NS::StringAtom tag, SR_HTYPES_NS::Function<void(SR_UTILS_NS::StringAtom)> callback) {
        /// вызываем в потокобезопасном контексте, так как теги могут быть изменены извне
        SR_UTILS_NS::TagManager::Instance().Do([&](auto&& pSettings) {
            auto&& pTagManager = dynamic_cast<SR_UTILS_NS::TagManager*>(pSettings);
            auto&& tags = pTagManager->GetTags();
            auto&& tagIndex = static_cast<int>(pTagManager->GetTagIndex(tag));
            auto&& pTags = const_cast<std::vector<SR_UTILS_NS::StringAtom>*>(&tags);

            if (ImGui::Combo("Tag", &tagIndex, [](void* vec, int idx, const char** out_text){
                auto&& vector = reinterpret_cast<std::vector<SR_UTILS_NS::StringAtom>*>(vec);
                if (idx < 0 || idx >= vector->size())
                    return false;

                *out_text = vector->at(idx).c_str();

                return true;
            }, reinterpret_cast<void*>(pTags), tags.size())) {
                /// TODO: переделать на комманды
                callback(pTagManager->GetTagByIndex(tagIndex));
            }
        });
    }

    void Inspector::InspectLayer(SR_UTILS_NS::StringAtom layer, SR_HTYPES_NS::Function<void(SR_UTILS_NS::StringAtom)> callback) {
        SR_UTILS_NS::LayerManager::Instance().Do([&](auto&& pSettings) {
            auto&& pLayerManager = dynamic_cast<SR_UTILS_NS::LayerManager*>(pSettings);
            auto&& layers = pLayerManager->GetLayers();
            auto&& layerIndex = static_cast<int>(pLayerManager->GetLayerIndex(layer));
            auto&& pLayers = const_cast<std::vector<SR_UTILS_NS::StringAtom>*>(&layers);

            if (ImGui::Combo("Layer", &layerIndex, [](void* vec, int idx, const char** out_text){
                auto&& vector = reinterpret_cast<std::vector<SR_UTILS_NS::StringAtom>*>(vec);
                if (idx < 0 || idx >= vector->size())
                    return false;

                *out_text = vector->at(idx).c_str();

                return true;
            }, reinterpret_cast<void*>(pLayers), layers.size())) {
                /// TODO: переделать на комманды
                callback(layers[layerIndex]);
            }
        });
    }
}