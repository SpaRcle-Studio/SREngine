//
// Created by Monika on 11.02.2022.
//

#include <Engine/EngineCommands.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/SceneRunner.h>
#include <Engine/GUI/EditorGUI.h>

#include <Graphics/GUI/Icons.h>
#include <Graphics/GUI/Utils.h>

#include <Utils/Input/InputSystem.h>
#include <Utils/Platform/Platform.h>
#include <Utils/TaskManager/TaskManager.h>
#include <Utils/ECS/TransformRect.h>
#include <Utils/Common/StoreUtils.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/World/ScenePrefabLogic.h>
#include <Utils/CommandManager/ReversibleCommand.h>
#include <Utils/FileSystem/FileDialog.h>
#include <Utils/Serialization/SerializationFlags.h>

#include <Enum/TreeNodeFlags.hpp>

#include <Codegen/Hierarchy.generated.hpp>

namespace SR_CORE_GUI_NS {
    const SR_MATH_NS::FColor SR_PREFAB_COLOR_FIRST = SR_MATH_NS::FColor(39.f / 255.f, 225 / 255.f, 193.f / 255.f, 1.f);
    const SR_MATH_NS::FColor SR_PREFAB_COLOR_SECOND = SR_MATH_NS::FColor(1.f, 140.f / 255.f, 0.f, 1.f);

    Hierarchy::Hierarchy()
        : Widget("Hierarchy")
    {
        m_sceneRunnerWidget = new SceneRunner();
        SetFlags(SR_GRAPH_GUI_NS::WindowFlags::HorizontalScrollbar);
    }

    Hierarchy::~Hierarchy() {
        SR_SAFE_DELETE_PTR(m_sceneRunnerWidget);
    }

    void Hierarchy::Draw() {
        SR_TRACY_ZONE;

        if (!m_engine) {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Missing engine!");
            return;
        }

        m_shiftPressed = SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::LShift) ||
                         SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::RShift);
        m_ctrlPressed = SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::LCtrl) ||
                        SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::RCtrl);
        m_previousVisibleItems.swap(m_visibleItems);
        m_visibleItems.clear();

        bool isPrefabLogic = false;

        if (m_scene) {
            m_tree = m_scene->GetRootSceneObjects();
            isPrefabLogic = m_scene->GetLogicBase().DynamicCast<SR_WORLD_NS::ScenePrefabLogic>() != nullptr;
        }
        else {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Missing scene!");
            m_tree.clear();
        }

        m_sceneRunnerWidget->DrawAsSubWindow();

        ContextMenu();

        for (auto&& pGameObject : m_tree) {
            if (pGameObject) {
                DrawChild(pGameObject, -1);
            }
        }
        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0.0f, 10.0f)); ///Требуется, чтобы в конце древа всегда было пустое пространство для вызова контекстного меню

        if (!isPrefabLogic && SR_IMMEDIATE_GUI_NS::BeginDragDropTargetWindow("Hierarchy##Payload")) {
            if (auto&& pPayload = SR_IMMEDIATE_GUI_NS::AcceptDragDropPayload("Hierarchy##Payload")) {
                if (m_scene) {
                    if (auto&& pData = SR_IMMEDIATE_GUI_NS::GetDataFromDragDropPayload(pPayload)) {
                        auto&& pCmd = new SR_CORE_NS::Commands::GameObjectsMove(m_engine, m_pointersHolder, SR_ID_INVALID, SR_ID_INVALID);
                        m_engine->GetCmdManager()->Execute(pCmd, SR_UTILS_NS::SyncType::Async);
                    }
                }
            }
            SR_IMMEDIATE_GUI_NS::EndDragDropTarget();
        }

        /// TODO: Это по-хорошему нужно перевести в какой-нибудь MouseUp
        if (!SR_IMMEDIATE_GUI_NS::IsAnyItemHovered() && SR_IMMEDIATE_GUI_NS::IsWindowHovered() && SR_IMMEDIATE_GUI_NS::IsMouseDoubleClicked(SR_IMMEDIATE_GUI_NS::MouseButton::Left)) {
            ClearSelected();
        }

    }

    void Hierarchy::Update(float_t dt) {
        m_engine = const_cast<Engine*>(dynamic_cast<EditorGUI*>(GetManager())->GetEngine().Get());
        m_showHidden = SR_UTILS_NS::StoreUtils::User::GetBool("ShowHiddenEntities", false);

        for (auto pIt = m_selected.begin(); pIt != m_selected.end(); ) {
            if (*pIt) {
                ++pIt;
            }
            else {
                pIt = m_selected.erase(pIt);
            }
        }
    }

    void Hierarchy::SetScene(const SR_WORLD_NS::Scene::Ptr& scene) {
        m_scene = scene;

        if (auto&& widget = dynamic_cast<SceneRunner*>(m_sceneRunnerWidget)) {
            widget->SetScene(m_scene);
        }
    }

    void Hierarchy::ContextMenu() {
        SR_TRACY_ZONE;

        auto&& pScene = m_engine->GetScene();
        auto&& pSceneLogic = pScene ? pScene->GetLogicBase().DynamicCast<SR_WORLD_NS::ScenePrefabLogic>() : nullptr;

        if (!pSceneLogic && SR_IMMEDIATE_GUI_NS::BeginPopupContextWindow("HierarchyContextMenu")) {
            static_cast<EditorGUI*>(GetManager())->DrawEditorInstanceMenu();

            Paste(nullptr, true);

            SR_IMMEDIATE_GUI_NS::EndPopup();
        }
    }

    void Hierarchy::DrawChild(const SR_UTILS_NS::SceneObject::Ptr& pRoot, uint32_t prefabIndex) {
        SR_TRACY_ZONE;

        const uint64_t id = pRoot->GetEntityId();
        SR_IMMEDIATE_GUI_NS::PushID((intptr_t)id);

        if (!m_showHidden && pRoot->HasEditorFlags(SR_UTILS_NS::EditorFlags::Hidden)) {
            SR_IMMEDIATE_GUI_NS::PopID();
            return;
        }

        m_visibleItems.emplace_back(pRoot);

        const auto& name = pRoot->GetName();
        bool hasChild = false;

        for (auto&& pChild : pRoot->GetChildrenRef()) {
            if (!pChild) {
                continue;
            }
            if (m_showHidden || !pChild->HasEditorFlags(SR_UTILS_NS::EditorFlags::Hidden)) {
                hasChild = true;
                break;
            }
        }

        const SR_IMMEDIATE_GUI_NS::TreeNodeFlags flags = (hasChild ? SR_IMMEDIATE_GUI_NS::GetNodeFlagsWithChild() : SR_IMMEDIATE_GUI_NS::GetNodeFlagsWithoutChild()) |
                                         ((m_selected.count(pRoot) == 1) ? SR_IMMEDIATE_GUI_NS::TreeNodeFlags::Selected : SR_IMMEDIATE_GUI_NS::TreeNodeFlags::None);

        if (pRoot->IsPrefabOwner()) {
            ++prefabIndex;
        }

        if (pRoot->HasSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave)) {
            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, SR_MATH_NS::FColor(220.f / 255.f, 199.f / 255.f, 0.f / 255.f, 1.f));
        }
        else if (pRoot->GetPrefab()) {
            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, prefabIndex % 2 == 0 ? SR_PREFAB_COLOR_FIRST : SR_PREFAB_COLOR_SECOND);
        }

        if (SR_IMMEDIATE_GUI_NS::RadioButton("##", pRoot->IsEnabled(), 0.75f)) {
            SR_UTILS_NS::Vector<SR_UTILS_NS::ReversibleCommand*> commands;
            if (m_selected.count(pRoot) == 1 && m_selected.size() > 1) {
                for (auto&& pSelected : m_selected) {
                    if (pSelected) {
                        commands.emplace_back(new SR_CORE_NS::Commands::EntityEnable(m_engine, pSelected.StaticCast<SR_UTILS_NS::Entity>(), !pRoot->IsEnabled()));
                    }
                }
            }
            else {
                commands.emplace_back(new SR_CORE_NS::Commands::EntityEnable(m_engine, pRoot.StaticCast<SR_UTILS_NS::Entity>(), !pRoot->IsEnabled()));
            }
            m_engine->GetCmdManager()->Execute(new SR_UTILS_NS::GroupCommand(std::move(commands)), SR_UTILS_NS::SyncType::Async);
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        const bool open = SR_IMMEDIATE_GUI_NS::TreeNodeEx((void*)(intptr_t)id, flags, "%s", name.c_str());
        const auto itemMin = SR_IMMEDIATE_GUI_NS::GetItemRectMin();
        const auto itemMax = SR_IMMEDIATE_GUI_NS::GetItemRectMax();

        if (pRoot->GetPrefab() || pRoot->HasSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave)) {
            SR_IMMEDIATE_GUI_NS::PopStyleColor();
        }

        for (auto&& gameObject : m_selected) {
            if (gameObject) {
                ExpandPath(gameObject->GetParent());
            }
        }

        ChildContextMenu(pRoot, id);
        CheckSelected(pRoot);

        if (!SR_IMMEDIATE_GUI_NS::GetDragDropPayload() && SR_IMMEDIATE_GUI_NS::BeginDragDropSource()) {
            SR_TRACY_ZONE_N("BeginDragDropSource Hierarchy");

            m_pointersHolder.clear();

            bool useSelected = false;

            for (auto&& ptr : m_selected) {
                useSelected |= ptr == pRoot;
            }

            if (useSelected) {
                for (auto&& pTreeRoot : m_tree) {
                    AppendSelectedIds(pTreeRoot, false);
                }
            }
            else {
                m_pointersHolder.emplace_back(pRoot->GetEntityId());
            }

            SR_GRAPH_GUI_NS::PayloadArrayData payloadData = { m_pointersHolder.data(), m_pointersHolder.size() };
            SR_IMMEDIATE_GUI_NS::SetDragDropPayload("Hierarchy##Payload", &payloadData, sizeof(SR_GRAPH_GUI_NS::PayloadArrayData), SR_IMMEDIATE_GUI_NS::Condition::Once);
            SR_IMMEDIATE_GUI_NS::Text("%s ->", name.c_str());
            SR_IMMEDIATE_GUI_NS::EndDragDropSource();
        }

        if (SR_IMMEDIATE_GUI_NS::BeginDragDropTarget()) {
            SR_IMMEDIATE_GUI_NS::Separator();

            if (auto&& pPayload = SR_IMMEDIATE_GUI_NS::GetDragDropPayload()) {
                if (strcmp(SR_IMMEDIATE_GUI_NS::GetPayloadType(pPayload), "InspectorComponent##Payload") == 0) {
                    if (m_selected.count(pRoot) == 0) {
                        SelectGameObject(pRoot);
                    }
                }
                else if (strcmp(SR_IMMEDIATE_GUI_NS::GetPayloadType(pPayload), "Hierarchy##Payload") == 0) {
                    const float_t relativeY = (SR_IMMEDIATE_GUI_NS::GetMousePos().y - itemMin.y) / (itemMax.y - itemMin.y);
                    if (relativeY < 0.25f || relativeY > 0.75f) {
                        const float_t lineY = relativeY < 0.25f ? itemMin.y : itemMax.y;
                        SR_IMMEDIATE_GUI_NS::DrawListAddLine(
                            SR_IMMEDIATE_GUI_NS::GetWindowDrawList(),
                            SR_MATH_NS::FVector2(itemMin.x, lineY),
                            SR_MATH_NS::FVector2(itemMax.x, lineY),
                            SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::DragDropTarget),
                            2.0f
                        );
                    }
                }
            }

            if (auto payload = SR_IMMEDIATE_GUI_NS::AcceptDragDropPayload("Hierarchy##Payload")) {
                if (auto&& pData = SR_IMMEDIATE_GUI_NS::GetDataFromDragDropPayload(payload)) {
                    if (m_scene) {
                        const float_t relativeY = (SR_IMMEDIATE_GUI_NS::GetMousePos().y - itemMin.y) / (itemMax.y - itemMin.y);
                        SR_UTILS_NS::EntityId parentId = pRoot->GetEntityId();
                        int32_t index = SR_ID_INVALID;
                        if (relativeY < 0.25f || relativeY > 0.75f) {
                            parentId = pRoot->GetParent() ? pRoot->GetParent()->GetEntityId() : SR_ID_INVALID;
                            if (pRoot->GetParent()) {
                                index = pRoot->GetParent()->GetChildIndex(*pRoot);
                            }
                            else {
                                auto&& root = m_scene->GetRootSceneObjects();
                                auto&& pIt = std::find(root.begin(), root.end(), pRoot);
                                index = pIt == root.end() ? SR_ID_INVALID : static_cast<int32_t>(pIt - root.begin());
                            }
                            if (relativeY > 0.75f && index != SR_ID_INVALID) {
                                ++index;
                            }
                        }

                        auto&& cmd = new SR_CORE_NS::Commands::GameObjectsMove(m_engine, m_pointersHolder, parentId, index);
                        m_engine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
                    }
                }
            }

            SR_IMMEDIATE_GUI_NS::EndDragDropTarget();
        }

        if (open && hasChild) {
            if (pRoot) {
                pRoot->ForEachChild([&](const SR_UTILS_NS::SceneObject::Ptr &child) {
                    DrawChild(child, prefabIndex);
                });
            }
            SR_IMMEDIATE_GUI_NS::TreePop();
        }

        SR_IMMEDIATE_GUI_NS::PopID();
    }

    void Hierarchy::AppendSelectedIds(const SR_UTILS_NS::SceneObject::Ptr& pRoot, bool hasSelectedParent) {
        if (!pRoot) {
            return;
        }
        const bool isSelected = m_selected.count(pRoot) == 1;
        if (isSelected && !hasSelectedParent) {
            m_pointersHolder.emplace_back(pRoot->GetEntityId());
        }
        for (auto&& pChild : pRoot->GetChildrenRef()) {
            AppendSelectedIds(pChild, hasSelectedParent || isSelected);
        }
    }

    bool Hierarchy::IsTopLevelSelected(const SR_UTILS_NS::SceneObject::Ptr& pSceneObject) const {
        for (SR_UTILS_NS::SceneObject::Ptr pParent = pSceneObject ? pSceneObject->GetParent() : nullptr; pParent; pParent = pParent->GetParent()) {
            if (m_selected.count(pParent) == 1) {
                return false;
            }
        }
        return pSceneObject;
    }

    void Hierarchy::ChildContextMenu(const SR_UTILS_NS::SceneObject::Ptr& pSceneObject, uint64_t id) {
        SR_TRACY_ZONE;

        SR_IMMEDIATE_GUI_NS::PushID((void*)(intptr_t)id);
        if (SR_IMMEDIATE_GUI_NS::BeginPopupContextItem("HierarchyChildContextMenu")) {
            if (m_selected.count(pSceneObject) == 0) {
                SelectGameObject(pSceneObject);
            }

            if (SR_IMMEDIATE_GUI_NS::Selectable("Copy")) {
                Copy();
            }

            Paste((m_selected.size() == 1) ? m_selected.begin()->Get() : nullptr, true);

            if (!pSceneObject->HasEditorFlags(SR_UTILS_NS::EditorFlags::DontDelete)) {
                SR_IMMEDIATE_GUI_NS::Separator();

                if (SR_IMMEDIATE_GUI_NS::Selectable("Cut")) {
                    Copy();
                    Delete();
                }

                SR_IMMEDIATE_GUI_NS::Separator();

                if (SR_IMMEDIATE_GUI_NS::Selectable("Delete")) {
                    Delete();
                }
            }

            if (pSceneObject) {
                if (pSceneObject->GetPrefab()) {
                    SR_IMMEDIATE_GUI_NS::Separator();

                    if (SR_IMMEDIATE_GUI_NS::Selectable("Break link")) {
                        pSceneObject->UnlinkPrefab();
                    }

                    SR_IMMEDIATE_GUI_NS::Separator();

                    if (SR_IMMEDIATE_GUI_NS::Selectable("Edit")) {
                        auto&& prefabPath = pSceneObject->GetPrefab()->GetResourcePath();
                        if (auto&& pScene = SR_WORLD_NS::Scene::LoadScene(CoreResLoader::GetResPath().Concat(prefabPath))) {
                            m_engine->SetActive(false);
                            m_engine->AddSceneToQueue(pScene);
                            m_engine->GetEditor()->CacheScenePath(pScene->GetPath());
                        }
                    }
                }
                else if (SR_IMMEDIATE_GUI_NS::Selectable("Make prefab")) {
                    auto&& resPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();

                    if (auto&& path = SR_UTILS_NS::FileDialog::Instance().SaveDialog(resPath.ToString(), { { "Scene", "prefab" } }); !path.IsEmpty()) {
                        path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetCachePath());
                        path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

                        SR_UTILS_NS::SRASerializer serializer;
                        SR_WORLD_NS::ScenePrefabLogic::SaveSOAsPrefab(serializer, pSceneObject);

                        if (auto&& pPrefabScene = SR_WORLD_NS::Scene::NewScene(CoreResLoader::GetResPath().Concat(path), SR_WORLD_NS::SceneLogicType::Prefab)) {
                            auto&& pDeserializer = serializer.CreateDeserializer();
                            pDeserializer->Detach();
                            pPrefabScene->GetLogicBase().DynamicCast<SR_WORLD_NS::ScenePrefabLogic>()->SetCustomSOData(std::move(pDeserializer));
                            pPrefabScene->SaveScene();

                            pSceneObject->DestroyChildren();

                            if (auto&& pPrefab = CoreResLoader::Load<SR_UTILS_NS::Prefab>(path)) {
                                pSceneObject->SetPrefab(pPrefab, true);
                            }
                            else {
                                SR_ERROR("Hierarchy::ChildContextMenu() : failed to load prefab from path: {}", path);
                            }

                            m_engine->AddSceneToQueue(pPrefabScene);
                        }
                    }
                }

                if (pSceneObject->GetSceneObjectType() == SR_UTILS_NS::SceneObjectType::GameObject) {
                    SR_IMMEDIATE_GUI_NS::Separator();

                    if (SR_IMMEDIATE_GUI_NS::BeginMenu("Add child")) {
                        static_cast<EditorGUI *>(GetManager())->DrawEditorInstanceMenu();
                        SR_IMMEDIATE_GUI_NS::EndMenu();
                    }
                }
            }

            SR_IMMEDIATE_GUI_NS::EndPopup();
        }
        SR_IMMEDIATE_GUI_NS::PopID();
    }

    void Hierarchy::CheckSelected(const SR_UTILS_NS::SceneObject::Ptr& gm) {
        SR_TRACY_ZONE;
        if (!SR_IMMEDIATE_GUI_NS::GetDragDropPayload() &&
            SR_IMMEDIATE_GUI_NS::IsItemHovered() &&
            SR_IMMEDIATE_GUI_NS::IsMouseReleased(SR_IMMEDIATE_GUI_NS::MouseButton::Left))
        {
            SelectGameObject(gm);
        }
    }

    void Hierarchy::OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) {
        switch (data->GetKeyCode()) {
            case SR_UTILS_NS::KeyCode::C: {
                if (IsKeyPressed(SR_UTILS_NS::KeyCode::LCtrl))
                    Copy();
                break;
            }
            case SR_UTILS_NS::KeyCode::V: {
                if (IsKeyPressed(SR_UTILS_NS::KeyCode::LCtrl))
                    Paste((m_selected.size() == 1) ? m_selected.begin()->Get() : nullptr, false);
                break;
            }
            case SR_UTILS_NS::KeyCode::Delete: {
                Delete();
                break;
            }
            default:
                break;
        }

        InputHandler::OnKeyDown(data);
    }

    void Hierarchy::OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) {
        switch (data->GetKeyCode()) {
            case SR_UTILS_NS::KeyCode::LShift: {
                if (m_pointersHolder.size() > 1) {
                    m_pointersHolder.clear();
                }
                break;
            }
            default:
                break;
        }

        InputHandler::OnKeyUp(data);
    }

    void Hierarchy::Copy() const {
        static const auto&& serializeId = SR_UTILS_NS::SerializationId::Create("SREngineSceneObjectsClipboard");

        SR_UTILS_NS::Vector<SR_UTILS_NS::SceneObject::Ptr> toCopy;
        for (auto&& pSO : m_selected) {
            if (IsTopLevelSelected(pSO)) {
                toCopy.emplace_back(pSO);
            }
        }

        if (toCopy.empty()) {
            return;
        }

        SR_UTILS_NS::SRASerializer serializer;
        SR_UTILS_NS::Serialization::Save(serializer, toCopy, serializeId);
        SR_UTILS_NS::String encodedData;
        SR_UTILS_NS::StringUtils::Instance().Base64Encode(serializer.ToString(), encodedData);
        SR_UTILS_NS::String clipboardData = serializeId.GetName() + encodedData;
        SR_PLATFORM_NS::TextToClipboard(clipboardData);
    }

    void Hierarchy::Paste(const SR_UTILS_NS::SceneObject::Ptr& pParent, bool fromGUI) {
        static const auto&& serializeId = SR_UTILS_NS::SerializationId::Create("SREngineSceneObjectsClipboard");

        auto&& clipboard = SR_PLATFORM_NS::GetClipboardText();
        if (!clipboard.starts_with(serializeId.GetName())) {
            return;
        }

        if (fromGUI) {
            if (!SR_IMMEDIATE_GUI_NS::Selectable("Paste")) {
                return;
            }
        }

        clipboard.erase(0, strlen(serializeId.GetName()));
        SR_UTILS_NS::SRADeserializer deserializer;
        SR_UTILS_NS::String decodedData;
        SR_UTILS_NS::StringUtils::Instance().Base64Decode(clipboard, decodedData);
        if (!deserializer.LoadFromString(decodedData)) {
            return;
        }

        SR_UTILS_NS::Vector<SR_UTILS_NS::SceneObject::Ptr> toPaste;
        SR_UTILS_NS::Serialization::Load(deserializer, toPaste, serializeId);
        if (toPaste.empty()) {
            return;
        }

        SR_UTILS_NS::Vector<SR_UTILS_NS::ReversibleCommand*> commands;

        for (auto&& pSO : toPaste) {
            if (!pSO) {
                continue;
            }

            if (pParent) {
                pParent->AddChild(pSO);
            }
            else {
                m_scene->RegisterSceneObject(pSO);
            }

            commands.emplace_back(new SR_CORE_NS::Commands::SceneObjectInstance(m_engine, pSO));
        }

        if (!commands.empty()) {
            m_engine->GetCmdManager()->Store(new SR_UTILS_NS::GroupCommand(std::move(commands)));
        }
    }

    void Hierarchy::Delete() {
        bool hasDeletable = false;
        for (auto&& pSelected : m_selected) {
            if (pSelected && !pSelected->HasEditorFlags(SR_UTILS_NS::EditorFlags::DontDelete)) {
                hasDeletable = true;
                break;
            }
        }

        if (!hasDeletable) {
            return;
        }

        if (!m_selected.empty() && m_scene) {
            SR_UTILS_NS::Vector<SR_UTILS_NS::ReversibleCommand*> commands;
            commands.emplace_back(new SR_CORE_NS::Commands::ChangeHierarchySelected(m_engine, this, m_selected, {}));
            for (auto&& pSelected : m_selected) {
                if (!IsTopLevelSelected(pSelected)) {
                    continue;
                }
                if (pSelected->HasEditorFlags(SR_UTILS_NS::EditorFlags::DontDelete)) {
                    continue;
                }
                commands.emplace_back(new SR_CORE_NS::Commands::SceneObjectDelete(m_engine, pSelected));
            }
            auto&& cmd = new SR_UTILS_NS::GroupCommand(std::move(commands));
            m_engine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);

            m_selected.clear();
        }
    }

    const SR_UTILS_NS::Set<SR_UTILS_NS::SceneObject::Ptr>& Hierarchy::GetSelected() const {
        return m_selected;
    }

    void Hierarchy::ClearSelected() {
        /// команда не должна срабатывать, если ни один объект не выделен, иначе такая команда бесполезна
        if (!m_selected.empty()) {
            auto&& cmd = new SR_CORE_NS::Commands::ChangeHierarchySelected(m_engine, this, m_selected, { });
            m_engine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Sync);
        }
    }

    void Hierarchy::SelectGameObject(const SR_UTILS_NS::SceneObject::Ptr& ptr) {
        SR_TRACY_ZONE;

        if (!ptr) {
            ClearSelected();
            return;
        }

        ///команда не должна срабатывать, если объект уже выделен и ни одного помимо него (либо если на нём прожат шифт), иначе такая команда бесполезна
        SR_UTILS_NS::Set<SR_UTILS_NS::SceneObject::Ptr> newSelected;
        if (m_shiftPressed && m_selectionAnchor) {
            newSelected = m_selected;
            int32_t anchorIndex = SR_ID_INVALID;
            int32_t targetIndex = SR_ID_INVALID;
            auto&& visibleItems = m_previousVisibleItems.empty() ? m_visibleItems : m_previousVisibleItems;
            for (int32_t i = 0; i < static_cast<int32_t>(visibleItems.size()); ++i) {
                if (visibleItems[i] == m_selectionAnchor) anchorIndex = i;
                if (visibleItems[i] == ptr) targetIndex = i;
            }
            if (anchorIndex != SR_ID_INVALID && targetIndex != SR_ID_INVALID) {
                if (anchorIndex > targetIndex) {
                    std::swap(anchorIndex, targetIndex);
                }
                for (int32_t i = anchorIndex; i <= targetIndex; ++i) {
                    newSelected.insert(visibleItems[i]);
                }
            }
        }
        else if (m_ctrlPressed) {
            newSelected = m_selected;
            if (newSelected.count(ptr) == 1) {
                newSelected.erase(ptr);
            }
            else {
                newSelected.insert(ptr);
            }
            m_selectionAnchor = ptr;
        }
        else {
            newSelected.insert(ptr);
            m_selectionAnchor = ptr;
        }

        if (newSelected == m_selected) {
            return;
        }

        auto&& cmd = new SR_CORE_NS::Commands::ChangeHierarchySelected(m_engine, this, m_selected, newSelected);
        m_engine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Sync);
    }

    void Hierarchy::SetSelectedImpl(const SR_UTILS_NS::Set<SR_UTILS_NS::SceneObject::Ptr>& changeSelected){
        SR_TRACY_ZONE;
        m_selected = changeSelected;
#ifdef SR_DEBUG
        for (auto&& pGameObject : m_selected) {
            SRAssert(pGameObject);
        }
#endif
    }

    void Hierarchy::ExpandPath(const SR_UTILS_NS::SceneObject::Ptr& gm) { /** NOLINT */
        SR_TRACY_ZONE;
        if (!gm) {
            return;
        }
        const uint64_t id = gm->GetEntityId();
        SR_IMMEDIATE_GUI_NS::WindowTreeNodeSetOpen(true, id);
        ExpandPath(gm->GetParent());
    }

    SR_GRAPH_NS::GUI::Widget* Hierarchy::GetSceneRunnerWidget() const noexcept {
        return m_sceneRunnerWidget;
    }

    void Hierarchy::SetManager(SR_GRAPH_NS::GUI::WidgetManager* pManager) {
        Super::SetManager(pManager);
        if (m_sceneRunnerWidget) {
            m_sceneRunnerWidget->SetManager(GetManager());
        }
    }
}
