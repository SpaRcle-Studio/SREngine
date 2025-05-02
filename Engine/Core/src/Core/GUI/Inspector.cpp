//
// Created by Monika on 14.02.2022.
//

#include <Core/GUI/Inspector.h>
#include <Core/EngineCommands.h>

#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/ECS/TransformZero.h>
#include <Utils/ECS/LayerManager.h>
#include <Utils/Types/SafePtrLockGuard.h>
#include <Utils/World/ScenePrefabLogic.h>
#include <Utils/Common/StoreUtils.h>

#include <Scripting/Base/Behaviour.h>

#include <Physics/3D/Rigidbody3D.h>
#include <Physics/2D/Rigidbody2D.h>

#include <Graphics/Types/Geometry/Sprite.h>
#include <Audio/Types/AudioSource.h>
#include <Graphics/UI/Canvas.h>
#include <Graphics/UI/Gizmo.h>
#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Graphics/GUI/Utils.h>
#include <Graphics/Types/Geometry/SkinnedMesh.h>
#include <Graphics/Animations/Animator.h>
#include <Graphics/Animations/BoneComponent.h>

namespace SR_CORE_GUI_NS {
    Inspector::Inspector(Hierarchy* hierarchy)
        : SR_GRAPH_GUI_NS::Widget("Inspector")
        , m_hierarchy(hierarchy)
    {
        m_pPointerDrawer = SR_CORE_GUI_NS::PropertyDrawerBase::MakeShared<PointerPropertyDrawer>();
        InitCategories();
    }

    void Inspector::Draw() {
        if (!m_scene) {
            return;
        }

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);

        if (ImGui::BeginTabBar("Inspector#TabBar")) {
            std::string_view gameObjectPage = "GameObject";
            ImVec4 color = ImVec4(1, 1, 1, 1);

            if (m_sceneObject) {
                if (m_sceneObject->IsPrefab()) {
                    color = ImVec4(0, 1, 1, 1);
                    gameObjectPage = "GameObject (Changes won't be saved)";
                }

                if (m_sceneObject->IsDirty()) {
                    color = ImVec4(1, 1, 0, 1);
                    gameObjectPage = "GameObject (Is dirty)";
                }

                if (m_sceneObject->HasSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave)) {
                    color = ImVec4(1, 1, 0, 1);
                    gameObjectPage = "GameObject (Dont Save)";
                }
            }

            ImGui::PushStyleColor(ImGuiCol_Text, color);
            if (ImGui::BeginTabItem(gameObjectPage.data())) {
                ImGui::PopStyleColor();
                InspectGameObject();
                ImGui::EndTabItem();
            }
            else {
                ImGui::PopStyleColor();
            }

            if (ImGui::BeginTabItem("Scene")) {
                InspectScene();
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        if (ImGui::GetScrollMaxY() > 0) {
            m_scrollBarWidth = ImGui::GetStyle().ScrollbarSize;
        }
        else {
            m_scrollBarWidth = 0;
        }

        ImGui::PopStyleVar();
    }

    void Inspector::InspectGameObject() {
        if (!m_sceneObject) {
            return;
        }

        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

        if (bool enabled = m_sceneObject->IsEnabled(); ImGui::Checkbox("##Enabled", &enabled)) {
            auto&& cmd = new SR_CORE_NS::Commands::EntityEnable(pEngine, m_sceneObject.Get(), enabled);
            pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
        }

        ImGui::SameLine();

        ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x + 2.f);
        std::string name = m_sceneObject->GetName();
        ImGui::InputText("##Name", &name);
        if (ImGui::IsItemDeactivatedAfterEdit()) {
            pEngine->GetCmdManager()->Execute<SR_CORE_NS::Commands::SceneObjectRename>(SR_UTILS_NS::SyncType::Async, pEngine, m_sceneObject, name);
        }
        ImGui::PopItemWidth();

        if (SR_UTILS_NS::StoreUtils::User::GetBool("ShowEntityId", false)) {
            ImGui::Text("Entity id: %llu", m_sceneObject->GetEntityId());
        }

        /// --------------------------------------------------------------------------------------------------------

        const float_t lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        const float_t layerAndTagWidth = ImGui::GetContentRegionAvail().x - lineHeight;

        ImGui::PushItemWidth(layerAndTagWidth / 2.f - ImGui::CalcTextSize("Tag").x);
        InspectTag(m_sceneObject->GetTag(), [&](auto&& tag) {
            pEngine->GetCmdManager()->Execute<SR_CORE_NS::Commands::SceneObjectTag>(SR_UTILS_NS::SyncType::Async, pEngine, m_sceneObject, tag);
        });
        ImGui::PopItemWidth();

        ImGui::SameLine();

        ImGui::PushItemWidth(layerAndTagWidth / 2.f - ImGui::CalcTextSize("Layer").x);
        InspectLayer(m_sceneObject->GetLocalLayer(), [&](auto&& layer) {
            pEngine->GetCmdManager()->Execute<SR_CORE_NS::Commands::SceneObjectLayer>(SR_UTILS_NS::SyncType::Async, pEngine, m_sceneObject, layer);
        });
        ImGui::PopItemWidth();

        /// --------------------------------------------------------------------------------------------------------

        ImGui::Separator();

        if (auto&& pGameObject = m_sceneObject.DynamicCast<SR_UTILS_NS::GameObject>()) {
            SR_UTILS_NS::Transform::Ptr pTransform = pGameObject->GetTransform();

            m_onBeforeChangeCallback = [&](bool drag) {
                if (!m_pTransformSerializer) {
                    m_isDragMode = drag;
                    m_pTransformSerializer = SR_CORE_NS::Commands::CreateSerializer();
                    SR_UTILS_NS::Serialization::Save(*m_pTransformSerializer, pTransform, SR_UTILS_NS::ICommand::DATA_ID);
                }
            };

            auto&& value = SR_UTILS_NS::Reflection::Value::CreateRef(pTransform);
            auto&& context = CreateDrawerContext(&value);

            context.fieldWidth += context.fieldTitleWidth;
            context.fieldTitleWidth = 0.f;
            context.noHeader = false;
            context.openedByDefault = true;
            context.editorPropertyParams.SetNotNull();
            m_pPointerDrawer->Draw(context);

            if (m_isDragMode && pTransform) {
                pTransform->UpdateTree();
            }

            if (m_pTransformSerializer && (!m_isDragMode || !SR_UTILS_NS::Input::Instance().GetMouse(SR_UTILS_NS::MouseCode::MouseLeft))) {
                auto&& pNewSerializer = SR_CORE_NS::Commands::CreateSerializer();
                SR_UTILS_NS::Serialization::Save(*pNewSerializer, pTransform, SR_UTILS_NS::ICommand::DATA_ID);

                auto&& cmd = new SR_CORE_NS::Commands::GameObjectTransform(pEngine, pGameObject, std::move(m_pTransformSerializer), std::move(pNewSerializer));
                pEngine->GetCmdManager()->Store(cmd);

                if (pTransform != pGameObject->GetTransform()) {
                    pGameObject->SetTransform(pTransform);
                }
            }
        }

        DrawComponents(m_sceneObject.Get());
    }

    void Inspector::InspectScene() {
        std::string name = m_scene->GetName();
        ImGui::InputText("Name", &name, ImGuiInputTextFlags_ReadOnly);

        ImGui::Separator();

        DrawComponents(dynamic_cast<SR_UTILS_NS::IComponentable*>(m_scene.Get()));
    }

    void Inspector::Update(float_t dt) {
        SR_LOCK_GUARD;

        if (m_componentContexts.size() > m_maxComponentContexts) {
            SR_UTILS_NS::TimePointType oldestTime = SR_UTILS_NS::TimePointType::max();
            SR_UTILS_NS::EntityId oldestId = SR_ID_INVALID;
            for (auto&& [id, context] : m_componentContexts) {
                if (context.lastUsage < oldestTime) {
                    oldestTime = context.lastUsage;
                    oldestId = id;
                }
            }
            if (oldestId != SR_ID_INVALID) {
                m_componentContexts.erase(oldestId);
            }
            else {
                SRHalt("Inspector::Update() : failed to find oldest component context!");
            }
        }

        if (auto&& selected = m_hierarchy->GetSelected(); selected.size() == 1) {
            if (*selected.begin() != m_sceneObject) {
                ResetWeakStorage();
            }
            m_sceneObject = *selected.begin();
            SRAssert(m_sceneObject);
        }
        else {
            m_sceneObject = SR_UTILS_NS::SceneObject::Ptr();
        }
    }

    void Inspector::SetScene(const SR_WORLD_NS::Scene::Ptr& scene) {
        SR_LOCK_GUARD;

        m_scene = scene;
    }

    void Inspector::DrawComponents(SR_UTILS_NS::IComponentable* pIComponentable) {
        ImGui::BeginDisabled();
        ImGui::CollapsingHeader("##header",  ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
        ImGui::EndDisabled();

        static const char* text = "Components";
        const ImVec2 headerSize = ImGui::GetItemRectSize();
        const ImVec2 headerPos = ImGui::GetItemRectMin();
        const ImVec2 textSize = ImGui::CalcTextSize(text);
        const ImVec2 textPos = ImVec2(
            headerPos.x + (headerSize.x - textSize.x) * 0.5f,
            headerPos.y + (headerSize.y - textSize.y) * 0.5f
        );
        ImGui::GetWindowDrawList()->AddText(textPos, ImGui::GetColorU32(ImGuiCol_Text), text);

        uint32_t index = 0;

        pIComponentable->ForEachComponent([&](SR_UTILS_NS::Component::Ptr& pComponent) -> bool {
            DrawComponent(pComponent.Get(), index);
            return true;
        });

        const ImVec2 dummySize = ImGui::GetContentRegionAvail();
        ImGui::Dummy(ImVec2(dummySize.x, dummySize.y > 0 ? dummySize.y : 200));

        if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
            m_componentSearchBuffer.clear();
            m_componentSearchOpened = false;
            ImGui::OpenPopup("InspectorAddComponentPopup");
        }

        if (ImGui::BeginPopup("InspectorAddComponentPopup")) {
            m_onBeforeChangeCallback = [&](bool drag) {
                if (!m_pComponentsSerializer) {
                    m_pComponentsSerializer = SR_CORE_NS::Commands::CreateSerializer();
                    SR_UTILS_NS::Serialization::Save(*m_pComponentsSerializer, pIComponentable->GetComponents(), SR_UTILS_NS::ICommand::DATA_ID);
                }
            };

            const float_t lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

            ImGui::PushItemWidth(lineHeight * 5.f);

            static const auto&& serializeId = SR_UTILS_NS::SerializationId::Create("SREngineComponentClipboard");

            if (auto&& clipboard = SR_PLATFORM_NS::GetClipboardText(); clipboard.starts_with(serializeId.GetName())) {
                if (ImGui::Button("Paste", ImVec2(lineHeight * 5.f, 0))) {
                    clipboard.erase(0, strlen(serializeId.GetName()));
                    SR_UTILS_NS::SRADeserializer deserializer;
                    if (deserializer.LoadFromString(SR_UTILS_NS::StringUtils::Base64Decode(clipboard))) {
                        SR_UTILS_NS::Component::Ptr pPastedComponent;
                        SR_UTILS_NS::Serialization::Load(deserializer, pPastedComponent, serializeId);
                        if (pPastedComponent) {
                            m_onBeforeChangeCallback(false);
                            pIComponentable->AddComponent(pPastedComponent);
                        }
                    }
                    ImGui::CloseCurrentPopup();
                }
            }

            if (!m_componentSearchOpened) {
                ImGui::SetKeyboardFocusHere();
                m_componentSearchOpened = true;
            }

            if (ImGui::Button("Reload")) {
                InitCategories();
            }
            ImGui::InputText("##search", &m_componentSearchBuffer);
            ImGui::PopItemWidth();

            ImGui::Separator();
            DrawComponentCategory(pIComponentable, m_componentsCategories, "Misc");
            ImGui::EndPopup();

            if (m_pComponentsSerializer) {
                auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
                auto&& cmd = new SR_CORE_NS::Commands::ComponentsChange(pEngine, pIComponentable, std::move(m_pComponentsSerializer));
                pEngine->GetCmdManager()->Store(cmd);
            }
        }
    }

    void Inspector::DrawComponent(SR_UTILS_NS::Component* pComponent, uint32_t &index) {
        auto&& pContext = dynamic_cast<EditorGUI*>(GetManager());
        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

        if (!pComponent || !pContext || !pEngine) {
            return;
        }

        ImGui::PushID(std::to_string(pComponent->GetEntityId()).c_str());

        SRAssert1Once(pComponent->Valid());

        ++index;

        const std::string headerName = "[{}] {}"_format(index, pComponent->GetMeta()->GetFactoryName());

        bool enabled = pComponent->IsEnabled();
        if (ImGui::Checkbox("##componentEnabled", &enabled)) {
            auto&& cmd = new SR_CORE_NS::Commands::EntityEnable(pEngine, pComponent, enabled);
            pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
        }

        ImGui::SameLine();

        const bool isOpened = ImGui::CollapsingHeader(pComponent->GetMeta()->GetFactoryName().c_str());

        if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
            ImGui::OpenPopup(headerName.c_str());
        }

        if (!ImGui::GetDragDropPayload() && ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
            m_pointersHolder = { pComponent->DynamicCast<SR_UTILS_NS::Component>() };
            ImGui::SetDragDropPayload("InspectorComponent##Payload", &m_pointersHolder, sizeof(std::vector<SR_UTILS_NS::Component::Ptr>), ImGuiCond_Once);
            ImGui::Text("%s ->", pComponent->GetMeta()->GetFactoryName().c_str());
            ImGui::EndDragDropSource();
        }

        ImGui::SameLine(); ImGui::Text(" ");

        if (pComponent->ExecuteInEditMode()) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "[Editor mode]");
        }

        if (pComponent->HasSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave)) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "[Dont save]");
        }

        if (!pComponent->IsAttached()) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "[Loaded]");
        }

        if (SR_UTILS_NS::StoreUtils::User::GetBool("ShowEntityId", false)) {
            ImGui::SameLine();
            ImGui::Text("[Entity id: %llu]", pComponent->GetEntityId());
        }

        if (isOpened) {
            SR_CORE_GUI_NS::DrawPropertyContext context;
            context.pEditor = pContext;

            if (SR_CORE_GUI_NS::DrawPropertyContainer(context, &pComponent->GetEntityMessages())) {
                ImGui::Separator();
            }
        }

        if (isOpened) {
            if (m_componentContexts.count(pComponent->GetEntityId()) == 0) {
                ComponentContext& componentContext = m_componentContexts[pComponent->GetEntityId()];
                if (auto&& inspectorName = pComponent->GetMeta()->GetInspectorName(); !inspectorName.empty()) {
                    componentContext.pObjectDrawer = SR_UTILS_NS::Factory::Instance().Create<ObjectPropertyDrawer>(inspectorName);
                }
                if (!componentContext.pObjectDrawer) {
                    componentContext.pObjectDrawer = SRNew<ObjectPropertyDrawer>();
                }
            }

            auto&& value = SR_UTILS_NS::Reflection::Value::CreateRef(*pComponent);

            m_onBeforeChangeCallback = [&](bool drag) {
                if (!m_pComponentSerializer) {
                    m_isDragMode = drag;
                    m_editableComponent = pComponent;
                    m_pComponentSerializer = SR_CORE_NS::Commands::CreateSerializer();
                    SR_UTILS_NS::Serialization::Save(*m_pComponentSerializer, *pComponent, SR_UTILS_NS::ICommand::DATA_ID);
                }
            };

            auto&& context = CreateDrawerContext(&value);
            context.pOwner = pComponent;
            context.pComponent = pComponent;

            auto&& componentContext = m_componentContexts.at(pComponent->GetEntityId());
            componentContext.lastUsage = SR_HTYPES_NS::Time::Instance().Now();
            componentContext.pObjectDrawer->Draw(context);

            if (m_pComponentSerializer && (!m_isDragMode || !SR_UTILS_NS::Input::Instance().GetMouse(SR_UTILS_NS::MouseCode::MouseLeft))) {
                if (m_editableComponent) {
                    auto&& cmd = new SR_CORE_NS::Commands::ComponentChange(pEngine, m_editableComponent, std::move(m_pComponentSerializer));
                    pEngine->GetCmdManager()->Store(cmd);
                }
            }
        }

        if (ImGui::BeginPopup(headerName.c_str())) {
            auto&& pParent = pComponent->GetParent();
            const int32_t componentIndex = pParent->GetComponentIndex(pComponent);
            const auto componentsCount = static_cast<int32_t>(pParent->GetComponentsCount());

            m_onBeforeChangeCallback = [&](bool drag) {
                if (!m_pComponentsSerializer) {
                    m_pComponentsSerializer = SR_CORE_NS::Commands::CreateSerializer();
                    SR_UTILS_NS::Serialization::Save(*m_pComponentsSerializer, pParent->GetComponents(), SR_UTILS_NS::ICommand::DATA_ID);
                }
            };

            static const auto&& serializeId = SR_UTILS_NS::SerializationId::Create("SREngineComponentClipboard");

            if (ImGui::MenuItem("Remove")) {
                m_onBeforeChangeCallback(false);
                pParent->RemoveComponent(pComponent);
            }
            if (componentIndex != 0 && ImGui::MenuItem("Move up")) {
                m_onBeforeChangeCallback(false);
                pParent->MoveComponent(pComponent, -1);
            }
            if ((componentIndex + 1) != componentsCount && ImGui::MenuItem("Move down")) {
                m_onBeforeChangeCallback(false);
                pParent->MoveComponent(pComponent, 1);
            }

            if (ImGui::MenuItem("Copy")) {
                SR_UTILS_NS::SRASerializer serializer;
                SR_UTILS_NS::Serialization::Save(serializer, SR_HTYPES_NS::SharedPtr(pComponent), serializeId);
                std::string encoded = SR_UTILS_NS::StringUtils::Base64Encode(serializer.ToString());
                SR_PLATFORM_NS::TextToClipboard(serializeId.GetName() + encoded);
            }

            if (auto&& clipboard = SR_PLATFORM_NS::GetClipboardText(); clipboard.starts_with(serializeId.GetName())) {
                if (ImGui::MenuItem("Paste (replace)")) {
                    clipboard.erase(0, strlen(serializeId.GetName()));
                    SR_UTILS_NS::SRADeserializer deserializer;
                    if (deserializer.LoadFromString(SR_UTILS_NS::StringUtils::Base64Decode(clipboard))) {
                        SR_UTILS_NS::Component::Ptr pPastedComponent;
                        SR_UTILS_NS::Serialization::Load(deserializer, pPastedComponent, serializeId);
                        if (pPastedComponent) {
                            m_onBeforeChangeCallback(false);
                            pParent->RemoveComponent(pComponent);
                            pParent->AddComponent(pPastedComponent);

                            const int32_t distance = (componentIndex + 1) - componentsCount;
                            SRAssert2(distance <= 0, "Invalid distance: {}", distance);
                            pParent->MoveComponent(pPastedComponent, distance);
                        }
                    }
                }
            }

            if (ImGui::MenuItem("Duplicate")) {
                m_onBeforeChangeCallback(false);
                auto&& pCopiedComponent = pComponent->CloneComponent();
                pParent->AddComponent(pCopiedComponent);
                const int32_t distance = (componentIndex + 1) - componentsCount;
                SRAssert2(distance <= 0, "Invalid distance: {}", distance);
                pParent->MoveComponent(pCopiedComponent, distance);
            }

            if (pParent) {
                if (m_pComponentsSerializer) {
                    auto&& cmd = new SR_CORE_NS::Commands::ComponentsChange(pEngine, pParent, std::move(m_pComponentsSerializer));
                    pEngine->GetCmdManager()->Store(cmd);
                }
            }
            else {
                m_pComponentsSerializer = nullptr;
            }

            ImGui::EndPopup();
        }

        ImGui::PopID();
    }

    void Inspector::DrawComponentCategory(SR_UTILS_NS::IComponentable* pComponentable, ComponentCategory& category, SR_UTILS_NS::StringAtom categoryName) {
        static auto&& addComponentFn = [](Inspector* pInspector, SR_UTILS_NS::IComponentable* pComponentable, SR_UTILS_NS::StringAtom name) {
            if (ImGui::Selectable(name.c_str(), false)) {
                if (auto&& pComponent = SR_UTILS_NS::Factory::Instance().Create<SR_UTILS_NS::Component>(name)) {
                    pInspector->m_onBeforeChangeCallback(false);
                    pComponentable->AddComponent(pComponent);
                }
                else {
                    SRHalt("Inspector::DrawComponentCategory() : failed to create component! Name: {}", name);
                }
            }
            if (ImGui::IsItemFocused()) {
                if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::Enter)) {
                    if (auto&& pComponent = SR_UTILS_NS::Factory::Instance().Create<SR_UTILS_NS::Component>(name)) {
                        pInspector->m_onBeforeChangeCallback(false);
                        pComponentable->AddComponent(pComponent);
                    }
                    else {
                        SRHalt("Inspector::DrawComponentCategory() : failed to create component! Name: {}", name);
                    }
                    ImGui::CloseCurrentPopup();
                }
            }
            ImGui::Separator();
        };

        std::function<bool(const ComponentCategory&, std::string_view)> checkMatch;

        checkMatch = [&checkMatch](const ComponentCategory& checkCategory, std::string_view search) -> bool {
            const bool hasComponents = std::ranges::any_of(checkCategory.components, [&](auto&& name) {
                return PropertyDrawerBase::CheckSearchMatch(search, name);
            });
            return hasComponents || std::ranges::any_of(checkCategory.categories, [&](auto&& pair) {
                return checkMatch(pair.second, search);
            });
        };

        if (m_componentSearchBuffer.empty() || checkMatch(category, m_componentSearchBuffer)) {
            if (category.components.empty() || ImGui::BeginMenu(categoryName.c_str())) {
                for (auto&& [name, subCategory] : category.categories) {
                    DrawComponentCategory(pComponentable, subCategory, name);
                }

                for (auto&& name : category.components) {
                    if (!m_componentSearchBuffer.empty() && !PropertyDrawerBase::CheckSearchMatch(m_componentSearchBuffer, name)) {
                        continue;
                    }
                    addComponentFn(this, pComponentable, name);
                }

                if (!category.components.empty()) {
                    ImGui::EndMenu();
                }
            }
        }

        ImGui::Separator();
    }

    PropertyDrawerContext Inspector::CreateDrawerContext(SR_UTILS_NS::Reflection::Value* pValue) {
        PropertyDrawerContext context(pValue);
        context.pEditor = dynamic_cast<EditorGUI*>(GetManager());

        const float_t lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        float_t windowWidth = ImGui::GetWindowWidth() - m_scrollBarWidth;
        context.lineHeight = lineHeight;
        context.axisButtonWidth = context.lineHeight;
        context.spaceWidth = windowWidth;
        context.fieldHeight = lineHeight;
        context.fieldTitleWidth = windowWidth * 0.3f;
        context.fieldWidth = windowWidth * 0.7f;
        context.noHeader = true;
        context.editorPropertyParams.SetDragSpeed(0.1f);
        context.onBeforeChangeCallback = m_onBeforeChangeCallback;

        return context;
    }

    void Inspector::InspectTag(const SR_UTILS_NS::StringAtom tag, const SR_HTYPES_NS::Function<void(SR_UTILS_NS::StringAtom)>& callback) {
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

    void Inspector::InspectLayer(const SR_UTILS_NS::StringAtom layer, const SR_HTYPES_NS::Function<void(SR_UTILS_NS::StringAtom)>& callback) {
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

    void Inspector::InitCategories() {
        m_availableComponents = SR_UTILS_NS::Factory::Instance().GetInheritances(SR_UTILS_NS::Component::GetClassStaticName());

        std::erase_if(m_availableComponents, [](auto&& name) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(name);
            return pMeta->IsAbstract() || pMeta->IsHidden();
        });

        m_componentsCategories = ComponentCategory();

        for (auto&& name : m_availableComponents) {
            auto&& category = SR_UTILS_NS::Factory::Instance().GetType(name)->GetCategory();
            if (category.empty()) {
                m_componentsCategories.categories["Misc"].components.emplace_back(name);
            }
            else {
                ComponentCategory* pCategory = nullptr;
                for (auto&& cat : category) {
                    if (pCategory) {
                        pCategory = &pCategory->categories[cat];
                    }
                    else {
                        pCategory = &m_componentsCategories.categories[cat];
                    }
                }
                SRAssert(pCategory);
                pCategory->components.emplace_back(name);
            }
        }
    }
}
