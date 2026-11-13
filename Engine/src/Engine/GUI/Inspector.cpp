//
// Created by Monika on 14.02.2022.
//

#include <Engine/GUI/EditorGUI.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/Inspector.h>
#include <Engine/EngineCommands.h>

#include <Scripting/Base/Behaviour.h>

#include <Physics/3D/Rigidbody3D.h>

#include <Graphics/UI/Canvas.h>
#include <Graphics/UI/Gizmo.h>
#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Graphics/Animations/Animator.h>

#include <Utils/ECS/LayerManager.h>
#include <Utils/ECS/Component.h>
#include <Utils/World/ScenePrefabLogic.h>
#include <Utils/Common/StoreUtils.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Events/Broadcaster.h>
#include <Utils/Reflection/Value.h>
#include <Utils/Serialization/SerializationFlags.h>

#include <Enum/TreeNodeFlags.hpp>
#include <Enum/ChildWindowFlags.hpp>

#include <Codegen/Inspector.generated.hpp>

namespace SR_CORE_GUI_NS {
    Inspector::Inspector()
        : SR_GRAPH_GUI_NS::Widget("Inspector")
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

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameRounding, 0.0f);

        if (SR_IMMEDIATE_GUI_NS::BeginTabBar("Inspector#TabBar")) {
            static SR_UTILS_NS::StringAtom noObjectSelectedId = "No object selected";
            SR_UTILS_NS::StringAtom gameObjectPage = noObjectSelectedId;

            if (m_sceneObject) {
                gameObjectPage = m_sceneObject->GetMeta()->GetFactoryName();
            }

            if (SR_IMMEDIATE_GUI_NS::BeginTabItem(gameObjectPage.data())) {
                InspectGameObject();
                SR_IMMEDIATE_GUI_NS::EndTabItem();
            }

            if (SR_IMMEDIATE_GUI_NS::BeginTabItem("Scene")) {
                InspectScene();
                SR_IMMEDIATE_GUI_NS::EndTabItem();
            }

            SR_IMMEDIATE_GUI_NS::EndTabBar();
        }

        if (SR_IMMEDIATE_GUI_NS::GetScrollMaxY() > 0) {
            m_scrollBarWidth = SR_IMMEDIATE_GUI_NS::GetScrollbarSize();
        }
        else {
            m_scrollBarWidth = 0;
        }

        SR_IMMEDIATE_GUI_NS::PopStyleVar();
    }

    SR_INLINE_STATIC const SR_UTILS_NS::StringAtom editorDebugModeId = "EditorDebugMode";

    void Inspector::InspectGameObject() {
        if (!m_sceneObject) {
            return;
        }

        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

        if (bool enabled = m_sceneObject->IsEnabled(); SR_IMMEDIATE_GUI_NS::Checkbox("##Enabled", &enabled)) {
            auto&& cmd = new SR_CORE_NS::Commands::EntityEnable(pEngine, m_sceneObject.Get(), enabled);
            pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        SR_IMMEDIATE_GUI_NS::PushItemWidth(SR_IMMEDIATE_GUI_NS::GetContentRegionAvail().x + 2.f);
        SR_THREAD_LOCAL static std::string buffer;
        buffer = m_sceneObject->GetName().ToStringView();
        SR_IMMEDIATE_GUI_NS::InputText("##Name", &buffer);
        if (SR_IMMEDIATE_GUI_NS::IsItemDeactivatedAfterEdit()) {
            pEngine->GetCmdManager()->Execute<SR_CORE_NS::Commands::SceneObjectRename>(SR_UTILS_NS::SyncType::Async, pEngine, m_sceneObject, buffer);
        }
        SR_IMMEDIATE_GUI_NS::PopItemWidth();

        if (SR_UTILS_NS::StoreUtils::User::GetBool("ShowEntityId", false)) {
            SR_IMMEDIATE_GUI_NS::Text("Entity id: %llu", m_sceneObject->GetEntityId());
        }

        if (m_sceneObject->IsDirty() && SR_UTILS_NS::StoreUtils::User::GetBool(editorDebugModeId, false)) {
            SR_IMMEDIATE_GUI_NS::WarningBox("Object is dirty");
        }

        if (m_sceneObject->HasSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave)) {
            SR_IMMEDIATE_GUI_NS::WarningBox("Saving is disabled for this object");
        }

        /// --------------------------------------------------------------------------------------------------------

        const float_t lineHeight = SR_IMMEDIATE_GUI_NS::GetFontSize() + SR_IMMEDIATE_GUI_NS::GetFramePadding().y * 2.0f;
        const float_t layerAndTagWidth = SR_IMMEDIATE_GUI_NS::GetContentRegionAvail().x - lineHeight;

        SR_IMMEDIATE_GUI_NS::PushItemWidth(layerAndTagWidth / 2.f - SR_IMMEDIATE_GUI_NS::CalcTextSize("Tag").x);
        InspectTag(m_sceneObject->GetLocalTag(), [&](auto&& tag) {
            pEngine->GetCmdManager()->Execute<SR_CORE_NS::Commands::SceneObjectTag>(SR_UTILS_NS::SyncType::Async, pEngine, m_sceneObject, tag);
        });
        SR_IMMEDIATE_GUI_NS::PopItemWidth();

        SR_IMMEDIATE_GUI_NS::SameLine();

        SR_IMMEDIATE_GUI_NS::PushItemWidth(layerAndTagWidth / 2.f - SR_IMMEDIATE_GUI_NS::CalcTextSize("Layer").x);
        InspectLayer(m_sceneObject->GetLocalLayer(), [&](auto&& layer) {
            pEngine->GetCmdManager()->Execute<SR_CORE_NS::Commands::SceneObjectLayer>(SR_UTILS_NS::SyncType::Async, pEngine, m_sceneObject, layer);
        });
        SR_IMMEDIATE_GUI_NS::PopItemWidth();

        /// --------------------------------------------------------------------------------------------------------

        SR_IMMEDIATE_GUI_NS::Separator();

        DrawSceneObject(m_sceneObject);

        DrawComponents(m_sceneObject.Get());
    }

    void Inspector::InspectScene() {
        std::string name = m_scene->GetName();
        SR_IMMEDIATE_GUI_NS::InputText("Name", &name, SR_IMMEDIATE_GUI_NS::InputTextFlags::ReadOnly);

        SR_IMMEDIATE_GUI_NS::Separator();

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
        SR_IMMEDIATE_GUI_NS::BeginDisabled();
        SR_IMMEDIATE_GUI_NS::CollapsingHeader("##header", SR_IMMEDIATE_GUI_NS::TreeNodeFlags::Leaf | SR_IMMEDIATE_GUI_NS::TreeNodeFlags::NoTreePushOnOpen);
        SR_IMMEDIATE_GUI_NS::EndDisabled();

        static const char* text = "Components";
        const SR_MATH_NS::FVector2 headerSize = SR_IMMEDIATE_GUI_NS::GetItemRectSize();
        const SR_MATH_NS::FVector2 headerPos = SR_IMMEDIATE_GUI_NS::GetItemRectMin();
        const SR_MATH_NS::FVector2 textSize = SR_IMMEDIATE_GUI_NS::CalcTextSize(text);
        const SR_MATH_NS::FVector2 textPos = SR_MATH_NS::FVector2(
            headerPos.x + (headerSize.x - textSize.x) * 0.5f,
            headerPos.y + (headerSize.y - textSize.y) * 0.5f
        );
        SR_IMMEDIATE_GUI_NS::AddText(SR_IMMEDIATE_GUI_NS::GetWindowDrawList(), textPos, SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::Text), text);

        uint32_t index = 0;

        pIComponentable->ForEachComponent([&](SR_UTILS_NS::Component& component) -> bool {
            DrawComponent(&component, index);
            return true;
        });

        const SR_MATH_NS::FVector2 dummySize = SR_IMMEDIATE_GUI_NS::GetContentRegionAvail();
        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(dummySize.x, dummySize.y > 0 ? dummySize.y : 200));

        if (SR_IMMEDIATE_GUI_NS::IsItemClicked(SR_IMMEDIATE_GUI_NS::MouseButton::Right)) {
            m_componentSearchBuffer.clear();
            m_componentSearchOpened = false;
            SR_IMMEDIATE_GUI_NS::OpenPopup("InspectorAddComponentPopup");
        }

        if (SR_IMMEDIATE_GUI_NS::BeginPopup("InspectorAddComponentPopup")) {
            m_onBeforeChangeCallback = [&](bool drag) {
                if (!m_pComponentsSerializer) {
                    m_pComponentsSerializer = SR_CORE_NS::Commands::CreateSerializer();
                    SR_UTILS_NS::Serialization::Save(*m_pComponentsSerializer, pIComponentable->GetComponents(), SR_UTILS_NS::COMMAND_DATA_ID);
                }
            };

            const float_t lineHeight = SR_IMMEDIATE_GUI_NS::GetFontSize() + SR_IMMEDIATE_GUI_NS::GetFramePadding().y * 2.0f;

            SR_IMMEDIATE_GUI_NS::PushItemWidth(lineHeight * 5.f);

            static const auto&& serializeId = SR_UTILS_NS::SerializationId::Create("SREngineComponentClipboard");

            if (auto&& clipboard = SR_PLATFORM_NS::GetClipboardText(); clipboard.starts_with(serializeId.GetName())) {
                if (SR_IMMEDIATE_GUI_NS::Button("Paste", SR_MATH_NS::FVector2(lineHeight * 5.f, 0))) {
                    clipboard.erase(0, strlen(serializeId.GetName()));
                    SR_UTILS_NS::SRADeserializer deserializer;
                    SR_UTILS_NS::String decodedData;
                    SR_UTILS_NS::StringUtils::Instance().Base64Decode(clipboard, decodedData);
                    if (deserializer.LoadFromString(decodedData)) {
                        SR_UTILS_NS::Component::Ptr pPastedComponent;
                        SR_UTILS_NS::Serialization::Load(deserializer, pPastedComponent, serializeId);
                        if (pPastedComponent) {
                            m_onBeforeChangeCallback(false);
                            pIComponentable->AddComponent(pPastedComponent);
                        }
                    }
                    SR_IMMEDIATE_GUI_NS::CloseCurrentPopup();
                }
            }

            if (!m_componentSearchOpened) {
                SR_IMMEDIATE_GUI_NS::SetKeyboardFocusHere();
                m_componentSearchOpened = true;
            }

            SR_IMMEDIATE_GUI_NS::InputText("##search", &m_componentSearchBuffer);
            SR_IMMEDIATE_GUI_NS::PopItemWidth();

            SR_IMMEDIATE_GUI_NS::Separator();
            DrawComponentCategory(pIComponentable, m_componentsCategories, "Misc");
            SR_IMMEDIATE_GUI_NS::EndPopup();

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

        m_tmpBuffer.clear();
        SR_UTILS_NS::FormatTo(m_tmpBuffer, "{}", pComponent->GetEntityId());
        SR_IMMEDIATE_GUI_NS::PushID(m_tmpBuffer.c_str());

        SRAssert1Once(pComponent->Valid());

        ++index;

        m_tmpBuffer.clear();
        SR_UTILS_NS::FormatTo(m_tmpBuffer, "[{}] {}", index, pComponent->GetMeta()->GetDisplayName());

        bool enabled = pComponent->IsEnabled();
        if (SR_IMMEDIATE_GUI_NS::Checkbox("##componentEnabled", &enabled)) {
            auto&& cmd = new SR_CORE_NS::Commands::EntityEnable(pEngine, pComponent, enabled);
            pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        const bool isComponentActive = pComponent->IsActive();

        if (!isComponentActive) {
            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, SR_MATH_NS::FColor(0.5f, 0.5f, 0.5f));
        }

        const bool isOpened = SR_IMMEDIATE_GUI_NS::CollapsingHeader(pComponent->GetMeta()->GetDisplayName().c_str());

        if (!isComponentActive) {
            SR_IMMEDIATE_GUI_NS::PopStyleColor();
        }

        if (SR_IMMEDIATE_GUI_NS::IsItemClicked(SR_IMMEDIATE_GUI_NS::MouseButton::Right)) {
            SR_IMMEDIATE_GUI_NS::OpenPopup(m_tmpBuffer.c_str());
        }

        if (!SR_IMMEDIATE_GUI_NS::GetDragDropPayload() && SR_IMMEDIATE_GUI_NS::BeginDragDropSource(SR_IMMEDIATE_GUI_NS::DragDropFlags::SourceAllowNullID)) {
            m_pointersHolder = { pComponent->GetEntityId() };
            SR_GRAPH_GUI_NS::PayloadArrayData payloadData = { m_pointersHolder.data(), m_pointersHolder.size() };
            SR_IMMEDIATE_GUI_NS::SetDragDropPayload("InspectorComponent##Payload", &payloadData, sizeof(SR_GRAPH_GUI_NS::PayloadArrayData), SR_IMMEDIATE_GUI_NS::Condition::Once);
            SR_IMMEDIATE_GUI_NS::Text("%s ->", pComponent->GetMeta()->GetDisplayName().c_str());
            SR_IMMEDIATE_GUI_NS::EndDragDropSource();
        }

        SR_IMMEDIATE_GUI_NS::SameLine(); SR_IMMEDIATE_GUI_NS::Text(" ");

        if (pComponent->ExecuteInEditMode()) {
            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(0, 1, 0, 1), "[Editor mode]");
        }

        if (pComponent->HasSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave)) {
            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1, 1, 0, 1), "[Dont save]");
        }

        if (!pComponent->IsAttached()) {
            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1, 1, 0, 1), "[Loaded]");
        }

        if (SR_UTILS_NS::StoreUtils::User::GetBool("ShowEntityId", false)) {
            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_IMMEDIATE_GUI_NS::Text("[Entity id: %llu]", pComponent->GetEntityId());
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

            SR_UTILS_NS::SceneObject::Ptr pStrongPrefabOwner;
            if (auto&& pComponentSceneObject = dynamic_cast<SR_UTILS_NS::SceneObject*>(pComponent->GetParent()); pComponentSceneObject && pComponentSceneObject->IsPrefab()) {
                pStrongPrefabOwner = SR_HTYPES_NS::SharedPtr(pComponentSceneObject->GetPrefabOwner());
            }

            m_onBeforeChangeCallback = [this, pStrongComponent = SR_HTYPES_NS::SharedPtr(pComponent), pStrongPrefabOwner](bool drag) {
                if (!m_pComponentSerializer) {
                    m_isDragMode = drag;
                    m_editableComponent = pStrongComponent;
                    m_pComponentSerializer = SR_CORE_NS::Commands::CreateSerializer();
                    SR_UTILS_NS::Serialization::Save(*m_pComponentSerializer, *pStrongComponent, SR_UTILS_NS::COMMAND_DATA_ID);
                    if (pStrongPrefabOwner) {
                        m_editablePrefabOwner = pStrongPrefabOwner;
                        m_pPrefabSOSerializer = SR_CORE_NS::Commands::CreateSerializer();
                        m_pPrefabSOSerializer->AddDontSaveTag("Inspector");
                        SR_UTILS_NS::Serialization::Save(*m_pPrefabSOSerializer, *pStrongPrefabOwner, SR_UTILS_NS::COMMAND_DATA_ID);
                    }
                }
            };

            auto&& context = CreateDrawerContext(&value);
            context.pUID = context.pOwner = pComponent;
            context.pComponent = pComponent;

            if (auto&& pPrefabSceneObject = dynamic_cast<SR_UTILS_NS::SceneObject*>(pComponent->GetParent()); pPrefabSceneObject && pPrefabSceneObject->IsPrefab()) {
                context.onPropertyChangedCallback = [pPrefabSceneObject, pComponent](SR_UTILS_NS::SRClass* pOwner, const SR_UTILS_NS::Reflection::Property& property, const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& propertyPath) {
                    pPrefabSceneObject->SetPrefabPropertyOverride(pComponent, pOwner, property, propertyPath);
                };
                context.onObjectChangedCallback = [pPrefabSceneObject, pComponent](SR_UTILS_NS::SRClass* pObject, const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& propertyPath) {
                    pPrefabSceneObject->SetPrefabObjectOverride(pComponent, pObject, propertyPath);
                };
                context.isPropertyOverriddenCallback = [pPrefabSceneObject, pComponent](SR_UTILS_NS::SRClass*, const SR_UTILS_NS::Reflection::Property&, const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& propertyPath) {
                    return pPrefabSceneObject->HasPrefabPropertyOverride(pComponent, propertyPath);
                };
                context.revertPropertyCallback = [pPrefabSceneObject, pComponent](SR_UTILS_NS::SRClass*, const SR_UTILS_NS::Reflection::Property&, const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& propertyPath) {
                    pPrefabSceneObject->RevertPrefabPropertyOverride(pComponent, propertyPath);
                };
            }

            auto&& componentContext = m_componentContexts.at(pComponent->GetEntityId());
            componentContext.lastUsage = SR_HTYPES_NS::Time::Instance().Now();
            componentContext.pObjectDrawer->Draw(context);

            if (m_pComponentSerializer && (!m_isDragMode || !SR_UTILS_NS::Input::Instance().GetMouse(SR_UTILS_NS::MouseCode::MouseLeft))) {
                if (m_editableComponent) {
                    auto&& cmd = new SR_CORE_NS::Commands::ComponentChange(
                        pEngine, m_editableComponent, std::move(m_pComponentSerializer),
                        m_editablePrefabOwner, std::move(m_pPrefabSOSerializer)
                    );
                    pEngine->GetCmdManager()->Store(cmd);
                }
                m_editablePrefabOwner = nullptr;
            }
        }

        if (SR_IMMEDIATE_GUI_NS::BeginPopup(m_tmpBuffer.c_str())) {
            auto&& pParent = pComponent->GetParent();
            const int32_t componentIndex = pParent->GetComponentIndex(pComponent);
            const auto componentsCount = static_cast<int32_t>(pParent->GetComponentsCount());

            m_onBeforeChangeCallback = [&](bool drag) {
                if (!m_pComponentsSerializer) {
                    m_pComponentsSerializer = SR_CORE_NS::Commands::CreateSerializer();
                    SR_UTILS_NS::Serialization::Save(*m_pComponentsSerializer, pParent->GetComponents(), SR_UTILS_NS::COMMAND_DATA_ID);
                }
            };

            static const auto&& serializeId = SR_UTILS_NS::SerializationId::Create("SREngineComponentClipboard");

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Remove")) {
                m_onBeforeChangeCallback(false);
                pParent->RemoveComponent(pComponent);
            }
            if (componentIndex != 0 && SR_IMMEDIATE_GUI_NS::MenuItem("Move up")) {
                m_onBeforeChangeCallback(false);
                pParent->MoveComponent(pComponent, -1);
            }
            if ((componentIndex + 1) != componentsCount && SR_IMMEDIATE_GUI_NS::MenuItem("Move down")) {
                m_onBeforeChangeCallback(false);
                pParent->MoveComponent(pComponent, 1);
            }
            if (componentIndex != 0 && SR_IMMEDIATE_GUI_NS::MenuItem("Move to start")) {
                m_onBeforeChangeCallback(false);
                pParent->MoveComponent(pComponent, -componentIndex);
            }
            if ((componentIndex + 1) != componentsCount && SR_IMMEDIATE_GUI_NS::MenuItem("Move to end")) {
                m_onBeforeChangeCallback(false);
                pParent->MoveComponent(pComponent, componentsCount - (componentIndex + 1));
            }

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Copy")) {
                SR_UTILS_NS::SRASerializer serializer;
                SR_UTILS_NS::Serialization::Save(serializer, SR_HTYPES_NS::SharedPtr(pComponent), serializeId);
                SR_UTILS_NS::String encoded;
                SR_UTILS_NS::StringUtils::Instance().Base64Encode(serializer.ToString(), encoded);
                SR_PLATFORM_NS::TextToClipboard(serializeId.GetName() + encoded);
            }

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Cut")) {
                SR_UTILS_NS::SRASerializer serializer;
                SR_UTILS_NS::Serialization::Save(serializer, SR_HTYPES_NS::SharedPtr(pComponent), serializeId);
                SR_UTILS_NS::String encoded;
                SR_UTILS_NS::StringUtils::Instance().Base64Encode(serializer.ToString(), encoded);
                SR_PLATFORM_NS::TextToClipboard(serializeId.GetName() + encoded);

                m_onBeforeChangeCallback(false);
                pParent->RemoveComponent(pComponent);
            }

            if (auto&& clipboard = SR_PLATFORM_NS::GetClipboardText(); clipboard.starts_with(serializeId.GetName())) {
                if (SR_IMMEDIATE_GUI_NS::MenuItem("Paste (replace)")) {
                    clipboard.erase(0, strlen(serializeId.GetName()));
                    SR_UTILS_NS::SRADeserializer deserializer;
                    SR_UTILS_NS::String decodedData;
                    SR_UTILS_NS::StringUtils::Instance().Base64Decode(clipboard, decodedData);
                    if (deserializer.LoadFromString(decodedData)) {
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

            if (SR_IMMEDIATE_GUI_NS::MenuItem("Duplicate")) {
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

            SR_IMMEDIATE_GUI_NS::EndPopup();
        }

        SR_IMMEDIATE_GUI_NS::PopID();
    }

    void Inspector::DrawSceneObject(SR_UTILS_NS::SceneObject::Ptr& pSceneObject) {
        m_onBeforeChangeCallback = [&](bool drag) {
            if (!m_pSOSerializer) {
                m_isDragMode = drag;
                m_pSOSerializer = SR_CORE_NS::Commands::CreateSerializer();
                m_pSOSerializer->AddDontSaveTag("Inspector");
                SR_UTILS_NS::Serialization::Save(*m_pSOSerializer, *pSceneObject, SR_UTILS_NS::COMMAND_DATA_ID);
            }
        };

        SR_UTILS_NS::SceneObject::Ptr pStrongSceneObject = pSceneObject;
        auto&& value = SR_UTILS_NS::Reflection::Value::CreateRef(pStrongSceneObject);
        auto&& context = CreateDrawerContext(&value);

        if (pSceneObject->IsPrefab()) {
            context.onPropertyChangedCallback = [&pSceneObject](SR_UTILS_NS::SRClass* pOwner, const SR_UTILS_NS::Reflection::Property& property, const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& propertyPath) {
                pSceneObject->SetPrefabPropertyOverride(pSceneObject.Get(), pOwner, property, propertyPath);
            };
            context.onObjectChangedCallback = [&pSceneObject](SR_UTILS_NS::SRClass* pObject, const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& propertyPath) {
                pSceneObject->SetPrefabObjectOverride(pSceneObject.Get(), pObject, propertyPath);
            };
            context.isPropertyOverriddenCallback = [&pSceneObject](SR_UTILS_NS::SRClass*, const SR_UTILS_NS::Reflection::Property&, const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& propertyPath) {
                return pSceneObject->HasPrefabPropertyOverride(pSceneObject.Get(), propertyPath);
            };
            context.revertPropertyCallback = [&pSceneObject](SR_UTILS_NS::SRClass*, const SR_UTILS_NS::Reflection::Property&, const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& propertyPath) {
                pSceneObject->RevertPrefabPropertyOverride(pSceneObject.Get(), propertyPath);
            };
        }

        context.fieldWidth += context.fieldTitleWidth;
        context.fieldTitleWidth = 0.f;
        context.noHeader = true;
        context.openedByDefault = true;
        context.isDebugMode = SR_UTILS_NS::StoreUtils::User::GetBool(editorDebugModeId, false);
        context.editorPropertyParams.SetNotNull();
        m_pPointerDrawer->Draw(context);

        if (m_pSOSerializer && (!m_isDragMode || !SR_IMMEDIATE_GUI_NS::IsMouseDown(SR_IMMEDIATE_GUI_NS::MouseButton::Left))) {
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

            auto&& pNewSerializer = SR_CORE_NS::Commands::CreateSerializer();
            pNewSerializer->AddDontSaveTag("Inspector");
            SR_UTILS_NS::Serialization::Save(*pNewSerializer, *pSceneObject, SR_UTILS_NS::COMMAND_DATA_ID);

            auto&& cmd = new SR_CORE_NS::Commands::SceneObjectChangeProperties(pEngine, pSceneObject, std::move(m_pSOSerializer), std::move(pNewSerializer));
            pEngine->GetCmdManager()->Store(cmd);
        }
    }

    void Inspector::DrawComponentCategory(SR_UTILS_NS::IComponentable* pComponentable, ComponentCategory& category, SR_UTILS_NS::StringAtom categoryName) {
        static auto&& addComponentFn = [](Inspector* pInspector, SR_UTILS_NS::IComponentable* pComponentable, SR_UTILS_NS::StringAtom name, SR_UTILS_NS::StringAtom displayName)-> SR_UTILS_NS::Component::Ptr {
            SR_UTILS_NS::Component::Ptr pComponent;
            if (SR_IMMEDIATE_GUI_NS::Selectable(displayName.c_str(), false)) {
                pComponent = SR_UTILS_NS::Factory::Instance().Create<SR_UTILS_NS::Component>(name);
                if (pComponent) {
                    pInspector->m_onBeforeChangeCallback(false);
                    pComponentable->AddComponent(pComponent);
                }
                else {
                    SRHalt("Inspector::DrawComponentCategory() : failed to create component! Name: {}", name);
                }
            }
            if (SR_IMMEDIATE_GUI_NS::IsItemFocused()) {
                if (SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::Enter)) {
                    pComponent = SR_UTILS_NS::Factory::Instance().Create<SR_UTILS_NS::Component>(name);
                    if (pComponent) {
                        pInspector->m_onBeforeChangeCallback(false);
                        pComponentable->AddComponent(pComponent);
                    }
                    else {
                        SRHalt("Inspector::DrawComponentCategory() : failed to create component! Name: {}", name);
                    }
                    SR_IMMEDIATE_GUI_NS::CloseCurrentPopup();
                }
            }
            SR_IMMEDIATE_GUI_NS::Separator();
            return pComponent;
        };

        SR_HTYPES_NS::Function<bool(const ComponentCategory&, std::string_view)> checkMatch;

        checkMatch = [&checkMatch](const ComponentCategory& checkCategory, std::string_view search) -> bool {
            const bool hasComponents = std::ranges::any_of(checkCategory.components, [&](auto&& info) {
                return SR_UTILS_NS::StringUtils::CheckSearchMatch(search, info.name) || SR_UTILS_NS::StringUtils::CheckSearchMatch(search, info.displayName);
            });
            return hasComponents || checkCategory.categories.any_of([&](auto&& pair) {
                return checkMatch(pair.second, search);
            });
        };

        if (m_componentSearchBuffer.empty() || checkMatch(category, m_componentSearchBuffer)) {
            if (category.components.empty() || SR_IMMEDIATE_GUI_NS::BeginMenu(categoryName.c_str())) {
                for (auto&& [name, subCategory] : category.categories) {
                    DrawComponentCategory(pComponentable, subCategory, name);
                }

                for (auto&& info : category.components) {
                    if (!m_componentSearchBuffer.empty()) {
                        if (!SR_UTILS_NS::StringUtils::CheckSearchMatch(m_componentSearchBuffer, info.name) && !SR_UTILS_NS::StringUtils::CheckSearchMatch(m_componentSearchBuffer, info.displayName)) {
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
                    SR_IMMEDIATE_GUI_NS::EndMenu();
                }
            }
        }

        SR_IMMEDIATE_GUI_NS::Separator();
    }

    PropertyDrawerContext Inspector::CreateDrawerContext(SR_UTILS_NS::Reflection::Value* pValue) {
        PropertyDrawerContext context(pValue);
        context.pEditor = dynamic_cast<EditorGUI*>(GetManager());

        const float_t lineHeight = SR_IMMEDIATE_GUI_NS::GetFontSize() + SR_IMMEDIATE_GUI_NS::GetFramePadding().y * 2.0f;
        float_t windowWidth = SR_IMMEDIATE_GUI_NS::GetWindowSize().x - m_scrollBarWidth;
        context.lineHeight = lineHeight;
        context.axisButtonWidth = context.lineHeight;
        context.spaceWidth = windowWidth;
        context.fieldHeight = lineHeight;
        context.fieldTitleWidth = windowWidth * 0.3f;
        context.fieldWidth = windowWidth * 0.7f;
        context.noHeader = true;

        static const SR_UTILS_NS::StringAtom editorDebugModeId = "EditorDebugMode";
        context.isDebugMode = SR_UTILS_NS::StoreUtils::User::GetBool(editorDebugModeId, false);

        context.editorPropertyParams.SetDragSpeed(0.1f);
        context.onBeforeChangeCallback = m_onBeforeChangeCallback;

        return context;
    }

    void Inspector::InspectTag(const SR_UTILS_NS::StringAtom currentTag, const SR_HTYPES_NS::Function<void(SR_UTILS_NS::StringAtom)>& callback) {
        SR_TRACY_ZONE;
        SR_MAYBE_UNUSED auto&& lock = SR_UTILS_NS::TagManager::Instance().ScopeLockSingleton();

        auto&& tags = SR_UTILS_NS::TagManager::Instance().GetTags();
        auto&& tagIndex = static_cast<int>(SR_UTILS_NS::TagManager::Instance().GetTagIndex(currentTag));

        m_comboBoxBuffer.clear();
        for (auto&& tag : tags) {
            m_comboBoxBuffer += tag.ToStringView();
            m_comboBoxBuffer += '\0';
        }

        if (SR_IMMEDIATE_GUI_NS::Combo("Tag", &tagIndex, m_comboBoxBuffer.c_str())) {
            callback(tags[tagIndex]);
        }
    }

    void Inspector::InspectLayer(const SR_UTILS_NS::StringAtom currentLayer, const SR_HTYPES_NS::Function<void(SR_UTILS_NS::StringAtom)>& callback) {
        SR_TRACY_ZONE;
        SR_MAYBE_UNUSED auto&& lock = SR_UTILS_NS::LayerManager::Instance().ScopeLockSingleton();

        auto&& layers = SR_UTILS_NS::LayerManager::Instance().GetLayers();
        auto&& layerIndex = static_cast<int>(SR_UTILS_NS::LayerManager::Instance().GetLayerIndex(currentLayer));

        m_comboBoxBuffer.clear();
        for (auto&& layer : layers) {
            m_comboBoxBuffer += layer.ToStringView();
            m_comboBoxBuffer += '\0';
        }

        if (SR_IMMEDIATE_GUI_NS::Combo("Layer", &layerIndex, m_comboBoxBuffer.c_str())) {
            callback(layers[layerIndex]);
        }
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

    void Inspector::Init() {
        m_hierarchy = GetManager()->GetWidget<Hierarchy>().Get();
        Widget::Init();
    }
}
