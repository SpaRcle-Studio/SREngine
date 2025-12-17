//
// Created by Monika on 14.02.2022.
//

#include <Engine/GUI/EditorGUI.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/Inspector.h>
#include <Engine/EngineCommands.h>

#include <Scripting/Base/Behaviour.h>

#include <Physics/3D/Rigidbody3D.h>
#include <Physics/2D/Rigidbody2D.h>

#include <Audio/Types/AudioSource.h>

#include <Graphics/Types/Geometry/Sprite.h>
#include <Graphics/UI/Canvas.h>
#include <Graphics/UI/Gizmo.h>
#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Graphics/GUI/Utils.h>
#include <Graphics/Types/Geometry/SkinnedMesh.h>
#include <Graphics/Animations/Animator.h>
#include <Graphics/Animations/BoneComponent.h>

#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/ECS/TransformZero.h>
#include <Utils/ECS/LayerManager.h>
#include <Utils/Types/SafePtrLockGuard.h>
#include <Utils/World/ScenePrefabLogic.h>
#include <Utils/Common/StoreUtils.h>
#include <Utils/Events/Broadcaster.h>
#include <Utils/Reflection/Value.h>
#include <Utils/Serialization/SerializationFlags.h>

#include <Enum/TreeNodeFlags.hpp>

namespace SR_CORE_GUI_NS {
    Inspector::Inspector(Hierarchy* hierarchy)
        : SR_GRAPH_GUI_NS::Widget("Inspector")
        , m_hierarchy(hierarchy)
    {
        m_pPointerDrawer = SR_CORE_GUI_NS::PropertyDrawerBase::MakeShared<PointerPropertyDrawer>();
        InitCategories();
        m_moduleReloadSubscription = SR_UTILS_NS::Broadcaster::Instance().Subscribe(SR_UTILS_NS::Events::EVENT_ON_SCRIPT_MODULE_RELOADED_ID, [this](auto&& msg) {
            InitCategories();
        });
    }

    void Inspector::Draw() {
        if (!m_scene) {
            return;
        }

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::FrameRounding, 0.0f);

        if (SR_GRAPH_GUI_NS::Immediate::BeginTabBar("Inspector#TabBar")) {
            std::string gameObjectPage = "No object selected";

            if (m_sceneObject) {
                gameObjectPage = m_sceneObject->GetMeta()->GetFactoryName();
            }

            SR_MATH_NS::FColor color = SR_MATH_NS::FColor(1, 1, 1, 1);

            if (m_sceneObject) {
                if (m_sceneObject->IsPrefab()) {
                    color = SR_MATH_NS::FColor(0, 1, 1, 1);
                    gameObjectPage += " (Changes won't be saved)";
                }

                if (m_sceneObject->IsDirty()) {
                    color = SR_MATH_NS::FColor(1, 1, 0, 1);
                    gameObjectPage += " (Is dirty)";
                }

                if (m_sceneObject->HasSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave)) {
                    color = SR_MATH_NS::FColor(1, 1, 0, 1);
                    gameObjectPage += " (Dont Save)";
                }
            }

            SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text, color);
            if (SR_GRAPH_GUI_NS::Immediate::BeginTabItem(gameObjectPage.data())) {
                SR_GRAPH_GUI_NS::Immediate::PopStyleColor();
                InspectGameObject();
                SR_GRAPH_GUI_NS::Immediate::EndTabItem();
            }
            else {
                SR_GRAPH_GUI_NS::Immediate::PopStyleColor();
            }

            if (SR_GRAPH_GUI_NS::Immediate::BeginTabItem("Scene")) {
                InspectScene();
                SR_GRAPH_GUI_NS::Immediate::EndTabItem();
            }

            SR_GRAPH_GUI_NS::Immediate::EndTabBar();
        }

        if (SR_GRAPH_GUI_NS::Immediate::GetScrollMaxY() > 0) {
            m_scrollBarWidth = SR_GRAPH_GUI_NS::Immediate::GetScrollbarSize();
        }
        else {
            m_scrollBarWidth = 0;
        }

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();
    }

    void Inspector::InspectGameObject() {
        if (!m_sceneObject) {
            return;
        }

        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

        if (bool enabled = m_sceneObject->IsEnabled(); SR_GRAPH_GUI_NS::Immediate::Checkbox("##Enabled", &enabled)) {
            auto&& cmd = new SR_CORE_NS::Commands::EntityEnable(pEngine, m_sceneObject.Get(), enabled);
            pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(SR_GRAPH_GUI_NS::Immediate::GetContentRegionAvail().x + 2.f);
        std::string name = m_sceneObject->GetName();
        SR_GRAPH_GUI_NS::Immediate::InputText("##Name", &name);
        if (SR_GRAPH_GUI_NS::Immediate::IsItemDeactivatedAfterEdit()) {
            pEngine->GetCmdManager()->Execute<SR_CORE_NS::Commands::SceneObjectRename>(SR_UTILS_NS::SyncType::Async, pEngine, m_sceneObject, name);
        }
        SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

        if (SR_UTILS_NS::StoreUtils::User::GetBool("ShowEntityId", false)) {
            SR_GRAPH_GUI_NS::Immediate::Text("Entity id: %llu", m_sceneObject->GetEntityId());
        }

        /// --------------------------------------------------------------------------------------------------------

        const float_t lineHeight = SR_GRAPH_GUI_NS::Immediate::GetFontSize() + SR_GRAPH_GUI_NS::Immediate::GetFramePadding().y * 2.0f;
        const float_t layerAndTagWidth = SR_GRAPH_GUI_NS::Immediate::GetContentRegionAvail().x - lineHeight;

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(layerAndTagWidth / 2.f - SR_GRAPH_GUI_NS::Immediate::CalcTextSize("Tag").x);
        InspectTag(m_sceneObject->GetLocalTag(), [&](auto&& tag) {
            pEngine->GetCmdManager()->Execute<SR_CORE_NS::Commands::SceneObjectTag>(SR_UTILS_NS::SyncType::Async, pEngine, m_sceneObject, tag);
        });
        SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(layerAndTagWidth / 2.f - SR_GRAPH_GUI_NS::Immediate::CalcTextSize("Layer").x);
        InspectLayer(m_sceneObject->GetLocalLayer(), [&](auto&& layer) {
            pEngine->GetCmdManager()->Execute<SR_CORE_NS::Commands::SceneObjectLayer>(SR_UTILS_NS::SyncType::Async, pEngine, m_sceneObject, layer);
        });
        SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

        /// --------------------------------------------------------------------------------------------------------

        SR_GRAPH_GUI_NS::Immediate::Separator();

        //if (auto&& pGameObject = m_sceneObject.DynamicCast<SR_UTILS_NS::GameObject>()) {
        //    DrawGameObject(pGameObject);
        //}

        DrawSceneObject(m_sceneObject);

        DrawComponents(m_sceneObject.Get());
    }

    void Inspector::InspectScene() {
        std::string name = m_scene->GetName();
        SR_GRAPH_GUI_NS::Immediate::InputText("Name", &name, SR_GRAPH_GUI_NS::Immediate::InputTextFlags::ReadOnly);

        SR_GRAPH_GUI_NS::Immediate::Separator();

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

        if (m_hierarchy) {
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
        else {
            m_sceneObject = SR_UTILS_NS::SceneObject::Ptr();
        }
    }

    void Inspector::SetScene(const SR_WORLD_NS::Scene::Ptr& scene) {
        SR_LOCK_GUARD;

        m_scene = scene;
    }

    void Inspector::DrawComponents(SR_UTILS_NS::IComponentable* pIComponentable) {
        SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
        SR_GRAPH_GUI_NS::Immediate::CollapsingHeader("##header", SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::Leaf | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::NoTreePushOnOpen);
        SR_GRAPH_GUI_NS::Immediate::EndDisabled();

        static const char* text = "Components";
        const SR_MATH_NS::FVector2 headerSize = SR_GRAPH_GUI_NS::Immediate::GetItemRectSize();
        const SR_MATH_NS::FVector2 headerPos = SR_GRAPH_GUI_NS::Immediate::GetItemRectMin();
        const SR_MATH_NS::FVector2 textSize = SR_GRAPH_GUI_NS::Immediate::CalcTextSize(text);
        const SR_MATH_NS::FVector2 textPos = SR_MATH_NS::FVector2(
            headerPos.x + (headerSize.x - textSize.x) * 0.5f,
            headerPos.y + (headerSize.y - textSize.y) * 0.5f
        );
        SR_GRAPH_GUI_NS::Immediate::AddText(SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList(), textPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), text);

        uint32_t index = 0;

        pIComponentable->ForEachComponent([&](SR_UTILS_NS::Component::Ptr& pComponent) -> bool {
            DrawComponent(pComponent.Get(), index);
            return true;
        });

        const SR_MATH_NS::FVector2 dummySize = SR_GRAPH_GUI_NS::Immediate::GetContentRegionAvail();
        SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(dummySize.x, dummySize.y > 0 ? dummySize.y : 200));

        if (SR_GRAPH_GUI_NS::Immediate::IsItemClicked(SR_GRAPH_GUI_NS::Immediate::MouseButton::Right)) {
            m_componentSearchBuffer.clear();
            m_componentSearchOpened = false;
            SR_GRAPH_GUI_NS::Immediate::OpenPopup("InspectorAddComponentPopup");
        }

        if (SR_GRAPH_GUI_NS::Immediate::BeginPopup("InspectorAddComponentPopup")) {
            m_onBeforeChangeCallback = [&](bool drag) {
                if (!m_pComponentsSerializer) {
                    m_pComponentsSerializer = SR_CORE_NS::Commands::CreateSerializer();
                    SR_UTILS_NS::Serialization::Save(*m_pComponentsSerializer, pIComponentable->GetComponents(), SR_UTILS_NS::ICommand::DATA_ID);
                }
            };

            const float_t lineHeight = SR_GRAPH_GUI_NS::Immediate::GetFontSize() + SR_GRAPH_GUI_NS::Immediate::GetFramePadding().y * 2.0f;

            SR_GRAPH_GUI_NS::Immediate::PushItemWidth(lineHeight * 5.f);

            static const auto&& serializeId = SR_UTILS_NS::SerializationId::Create("SREngineComponentClipboard");

            if (auto&& clipboard = SR_PLATFORM_NS::GetClipboardText(); clipboard.starts_with(serializeId.GetName())) {
                if (SR_GRAPH_GUI_NS::Immediate::Button("Paste", SR_MATH_NS::FVector2(lineHeight * 5.f, 0))) {
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
                    SR_GRAPH_GUI_NS::Immediate::CloseCurrentPopup();
                }
            }

            if (!m_componentSearchOpened) {
                SR_GRAPH_GUI_NS::Immediate::SetKeyboardFocusHere();
                m_componentSearchOpened = true;
            }

            SR_GRAPH_GUI_NS::Immediate::InputText("##search", &m_componentSearchBuffer);
            SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

            SR_GRAPH_GUI_NS::Immediate::Separator();
            DrawComponentCategory(pIComponentable, m_componentsCategories, "Misc");
            SR_GRAPH_GUI_NS::Immediate::EndPopup();

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

        SR_GRAPH_GUI_NS::Immediate::PushID(std::to_string(pComponent->GetEntityId()).c_str());

        SRAssert1Once(pComponent->Valid());

        ++index;

        const std::string headerName = "[{}] {}"_format(index, pComponent->GetMeta()->GetDisplayName());

        bool enabled = pComponent->IsEnabled();
        if (SR_GRAPH_GUI_NS::Immediate::Checkbox("##componentEnabled", &enabled)) {
            auto&& cmd = new SR_CORE_NS::Commands::EntityEnable(pEngine, pComponent, enabled);
            pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        const bool isComponentActive = pComponent->IsActive();

        if (!isComponentActive) {
            SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text, SR_MATH_NS::FColor(0.5f, 0.5f, 0.5f));
        }

        const bool isOpened = SR_GRAPH_GUI_NS::Immediate::CollapsingHeader(pComponent->GetMeta()->GetDisplayName().c_str());

        if (!isComponentActive) {
            SR_GRAPH_GUI_NS::Immediate::PopStyleColor();
        }

        if (SR_GRAPH_GUI_NS::Immediate::IsItemClicked(SR_GRAPH_GUI_NS::Immediate::MouseButton::Right)) {
            SR_GRAPH_GUI_NS::Immediate::OpenPopup(headerName.c_str());
        }

        if (!SR_GRAPH_GUI_NS::Immediate::GetDragDropPayload() && SR_GRAPH_GUI_NS::Immediate::BeginDragDropSource(SR_GRAPH_GUI_NS::Immediate::DragDropFlags::SourceAllowNullID)) {
            m_pointersHolder = { pComponent->DynamicCast<SR_UTILS_NS::Component>() };
            SR_GRAPH_GUI_NS::Immediate::SetDragDropPayload("InspectorComponent##Payload", &m_pointersHolder, sizeof(std::vector<SR_UTILS_NS::Component::Ptr>), SR_GRAPH_GUI_NS::Immediate::Condition::Once);
            SR_GRAPH_GUI_NS::Immediate::Text("%s ->", pComponent->GetMeta()->GetDisplayName().c_str());
            SR_GRAPH_GUI_NS::Immediate::EndDragDropSource();
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine(); SR_GRAPH_GUI_NS::Immediate::Text(" ");

        if (pComponent->ExecuteInEditMode()) {
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0, 1, 0, 1), "[Editor mode]");
        }

        if (pComponent->HasSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave)) {
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1, 1, 0, 1), "[Dont save]");
        }

        if (!pComponent->IsAttached()) {
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1, 1, 0, 1), "[Loaded]");
        }

        if (SR_UTILS_NS::StoreUtils::User::GetBool("ShowEntityId", false)) {
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_GRAPH_GUI_NS::Immediate::Text("[Entity id: %llu]", pComponent->GetEntityId());
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

            m_onBeforeChangeCallback = [this, pStrongComponent = SR_HTYPES_NS::SharedPtr(pComponent)](bool drag) {
                if (!m_pComponentSerializer) {
                    m_isDragMode = drag;
                    m_editableComponent = pStrongComponent;
                    m_pComponentSerializer = SR_CORE_NS::Commands::CreateSerializer();
                    SR_UTILS_NS::Serialization::Save(*m_pComponentSerializer, *pStrongComponent, SR_UTILS_NS::ICommand::DATA_ID);
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

        if (SR_GRAPH_GUI_NS::Immediate::BeginPopup(headerName.c_str())) {
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

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Remove")) {
                m_onBeforeChangeCallback(false);
                pParent->RemoveComponent(pComponent);
            }
            if (componentIndex != 0 && SR_GRAPH_GUI_NS::Immediate::MenuItem("Move up")) {
                m_onBeforeChangeCallback(false);
                pParent->MoveComponent(pComponent, -1);
            }
            if ((componentIndex + 1) != componentsCount && SR_GRAPH_GUI_NS::Immediate::MenuItem("Move down")) {
                m_onBeforeChangeCallback(false);
                pParent->MoveComponent(pComponent, 1);
            }

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Copy")) {
                SR_UTILS_NS::SRASerializer serializer;
                SR_UTILS_NS::Serialization::Save(serializer, SR_HTYPES_NS::SharedPtr(pComponent), serializeId);
                std::string encoded = SR_UTILS_NS::StringUtils::Base64Encode(serializer.ToString());
                SR_PLATFORM_NS::TextToClipboard(serializeId.GetName() + encoded);
            }

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Cut")) {
                SR_UTILS_NS::SRASerializer serializer;
                SR_UTILS_NS::Serialization::Save(serializer, SR_HTYPES_NS::SharedPtr(pComponent), serializeId);
                std::string encoded = SR_UTILS_NS::StringUtils::Base64Encode(serializer.ToString());
                SR_PLATFORM_NS::TextToClipboard(serializeId.GetName() + encoded);

                m_onBeforeChangeCallback(false);
                pParent->RemoveComponent(pComponent);
            }

            if (auto&& clipboard = SR_PLATFORM_NS::GetClipboardText(); clipboard.starts_with(serializeId.GetName())) {
                if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Paste (replace)")) {
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

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Duplicate")) {
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

            SR_GRAPH_GUI_NS::Immediate::EndPopup();
        }

        SR_GRAPH_GUI_NS::Immediate::PopID();
    }

    void Inspector::DrawSceneObject(const SR_UTILS_NS::SceneObject::Ptr& pSceneObject) {
        m_onBeforeChangeCallback = [&](bool drag) {
            if (!m_pSOSerializer) {
                m_isDragMode = drag;
                m_pSOSerializer = SR_CORE_NS::Commands::CreateSerializer();
                m_pSOSerializer->AddDontSaveTag("Inspector");
                SR_UTILS_NS::Serialization::Save(*m_pSOSerializer, *pSceneObject, SR_UTILS_NS::ICommand::DATA_ID);
            }
        };

        auto&& value = SR_UTILS_NS::Reflection::Value::CreateRef(pSceneObject);
        auto&& context = CreateDrawerContext(&value);

        context.fieldWidth += context.fieldTitleWidth;
        context.fieldTitleWidth = 0.f;
        context.noHeader = true;
        context.openedByDefault = true;
        context.editorPropertyParams.SetNotNull();
        m_pPointerDrawer->Draw(context);

        if (m_pSOSerializer && (!m_isDragMode || !SR_GRAPH_GUI_NS::Immediate::IsMouseDown(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left))) {
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

            auto&& pNewSerializer = SR_CORE_NS::Commands::CreateSerializer();
            pNewSerializer->AddDontSaveTag("Inspector");
            SR_UTILS_NS::Serialization::Save(*pNewSerializer, *pSceneObject, SR_UTILS_NS::ICommand::DATA_ID);

            auto&& cmd = new SR_CORE_NS::Commands::SceneObjectChangeProperties(pEngine, pSceneObject, std::move(m_pSOSerializer), std::move(pNewSerializer));
            pEngine->GetCmdManager()->Store(cmd);
        }
    }

    void Inspector::DrawGameObject(const SR_UTILS_NS::GameObject::Ptr& pGameObject) {
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

        if (m_pTransformSerializer && (!m_isDragMode || !SR_GRAPH_GUI_NS::Immediate::IsMouseDown(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left))) {
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

            auto&& pNewSerializer = SR_CORE_NS::Commands::CreateSerializer();
            SR_UTILS_NS::Serialization::Save(*pNewSerializer, pTransform, SR_UTILS_NS::ICommand::DATA_ID);

            auto&& cmd = new SR_CORE_NS::Commands::GameObjectTransform(pEngine, pGameObject, std::move(m_pTransformSerializer), std::move(pNewSerializer));
            pEngine->GetCmdManager()->Store(cmd);

            if (pTransform != pGameObject->GetTransform()) {
                pGameObject->SetTransform(pTransform);
            }
        }
    }

    void Inspector::DrawComponentCategory(SR_UTILS_NS::IComponentable* pComponentable, ComponentCategory& category, SR_UTILS_NS::StringAtom categoryName) {
        static auto&& addComponentFn = [](Inspector* pInspector, SR_UTILS_NS::IComponentable* pComponentable, SR_UTILS_NS::StringAtom name, SR_UTILS_NS::StringAtom displayName)-> SR_UTILS_NS::Component::Ptr {
            SR_UTILS_NS::Component::Ptr pComponent;
            if (SR_GRAPH_GUI_NS::Immediate::Selectable(displayName.c_str(), false)) {
                pComponent = SR_UTILS_NS::Factory::Instance().Create<SR_UTILS_NS::Component>(name);
                if (pComponent) {
                    pInspector->m_onBeforeChangeCallback(false);
                    pComponentable->AddComponent(pComponent);
                }
                else {
                    SRHalt("Inspector::DrawComponentCategory() : failed to create component! Name: {}", name);
                }
            }
            if (SR_GRAPH_GUI_NS::Immediate::IsItemFocused()) {
                if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::Enter)) {
                    pComponent = SR_UTILS_NS::Factory::Instance().Create<SR_UTILS_NS::Component>(name);
                    if (pComponent) {
                        pInspector->m_onBeforeChangeCallback(false);
                        pComponentable->AddComponent(pComponent);
                    }
                    else {
                        SRHalt("Inspector::DrawComponentCategory() : failed to create component! Name: {}", name);
                    }
                    SR_GRAPH_GUI_NS::Immediate::CloseCurrentPopup();
                }
            }
            SR_GRAPH_GUI_NS::Immediate::Separator();
            return pComponent;
        };

        std::function<bool(const ComponentCategory&, std::string_view)> checkMatch;

        checkMatch = [&checkMatch](const ComponentCategory& checkCategory, std::string_view search) -> bool {
            const bool hasComponents = std::ranges::any_of(checkCategory.components, [&](auto&& info) {
                return PropertyDrawerBase::CheckSearchMatch(search, info.name) || PropertyDrawerBase::CheckSearchMatch(search, info.displayName);
            });
            return hasComponents || std::ranges::any_of(checkCategory.categories, [&](auto&& pair) {
                return checkMatch(pair.second, search);
            });
        };

        if (m_componentSearchBuffer.empty() || checkMatch(category, m_componentSearchBuffer)) {
            if (category.components.empty() || SR_GRAPH_GUI_NS::Immediate::BeginMenu(categoryName.c_str())) {
                for (auto&& [name, subCategory] : category.categories) {
                    DrawComponentCategory(pComponentable, subCategory, name);
                }

                for (auto&& info : category.components) {
                    if (!m_componentSearchBuffer.empty()) {
                        if (!PropertyDrawerBase::CheckSearchMatch(m_componentSearchBuffer, info.name) && !PropertyDrawerBase::CheckSearchMatch(m_componentSearchBuffer, info.displayName)) {
                            continue;
                        }
                    }

                    if (info.isBehaviour) {
                        if (auto&& pBehaviour = addComponentFn(this, pComponentable, SR_SCRIPTING_NS::Behaviour::GetClassStaticName(), info.name)) {
                            pBehaviour.StaticCast<SR_SCRIPTING_NS::Behaviour>()->SetBehaviourName(info.name);
                        }
                    }
                    else {
                        addComponentFn(this, pComponentable, info.name, info.displayName);
                    }
                }

                if (!category.components.empty()) {
                    SR_GRAPH_GUI_NS::Immediate::EndMenu();
                }
            }
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();
    }

    PropertyDrawerContext Inspector::CreateDrawerContext(SR_UTILS_NS::Reflection::Value* pValue) {
        PropertyDrawerContext context(pValue);
        context.pEditor = dynamic_cast<EditorGUI*>(GetManager());

        const float_t lineHeight = SR_GRAPH_GUI_NS::Immediate::GetFontSize() + SR_GRAPH_GUI_NS::Immediate::GetFramePadding().y * 2.0f;
        float_t windowWidth = SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x - m_scrollBarWidth;
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

            if (SR_GRAPH_GUI_NS::Immediate::Combo("Tag", &tagIndex, [](void* vec, int idx, const char** out_text){
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

            if (SR_GRAPH_GUI_NS::Immediate::Combo("Layer", &layerIndex, [](void* vec, int idx, const char** out_text){
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
        m_availableCppBehaviours = SR_UTILS_NS::Factory::Instance().GetInheritances(SR_SCRIPTING_NS::CppBehaviour::GetClassStaticName());

        std::erase_if(m_availableComponents, [](auto&& name) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(name);
            return pMeta->IsAbstract() || pMeta->IsHidden();
        });

        std::erase_if(m_availableCppBehaviours, [](auto&& name) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(name);
            return pMeta->IsAbstract() || pMeta->IsHidden();
        });

        m_componentsCategories = ComponentCategory();

        auto&& processComponent = [this](const SR_UTILS_NS::StringAtom& name, bool isBehaviour) {
            ComponentCategory::ComponentInfo componentInfo;
            componentInfo.name = name;
            componentInfo.displayName = SR_UTILS_NS::Factory::Instance().GetType(name)->GetDisplayName();
            componentInfo.isBehaviour = isBehaviour;

            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(name);
            if (pMeta->GetCategory().empty()) {
                m_componentsCategories.categories["Misc"].components.emplace_back(componentInfo);
            }
            else {
                ComponentCategory* pCategory = nullptr;
                for (auto&& cat : pMeta->GetCategory()) {
                    if (pCategory) {
                        pCategory = &pCategory->categories[cat];
                    }
                    else {
                        pCategory = &m_componentsCategories.categories[cat];
                    }
                }

                if (SRVerify(pCategory)) {
                    pCategory->components.emplace_back(componentInfo);
                }
            }
        };

        for (auto&& name : m_availableComponents) {
            processComponent(name, false);
        }

        for (auto&& name : m_availableCppBehaviours) {
            processComponent(name, true);
        }
    }
}
