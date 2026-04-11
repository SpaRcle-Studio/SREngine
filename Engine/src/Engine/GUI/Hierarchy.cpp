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
            return;
        }

        m_shiftPressed = SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::LShift);

        bool isPrefabLogic = false;

        if (m_scene) {
            m_tree = m_scene->GetRootSceneObjects();
            isPrefabLogic = m_scene->GetLogicBase().DynamicCast<SR_WORLD_NS::ScenePrefabLogic>() != nullptr;
        }
        else {
            m_tree.clear();
        }

        m_sceneRunnerWidget->DrawAsSubWindow();

        ContextMenu();

        for (auto&& pGameObject : m_tree) {
            if (pGameObject) {
                DrawChild(pGameObject, -1);
            }
        }
        SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(0.0f, 10.0f)); ///Требуется, чтобы в конце древа всегда было пустое пространство для вызова контекстного меню

        if (!isPrefabLogic && SR_GRAPH_GUI_NS::Immediate::BeginDragDropTargetWindow("Hierarchy##Payload")) {
            if (auto&& pPayload = SR_GRAPH_GUI_NS::Immediate::AcceptDragDropPayload("Hierarchy##Payload")) {
                if (m_scene) {
                    std::vector<SR_UTILS_NS::ReversibleCommand*> commands;
                    if (auto&& pData = SR_GRAPH_GUI_NS::Immediate::GetDataFromDragDropPayload(pPayload)) {
                        commands.emplace_back(new SR_CORE_NS::Commands::ChangeHierarchySelected(m_engine, this, m_selected, { }));

                        SR_GRAPH_GUI_NS::PayloadArrayData payloadData = *(SR_GRAPH_GUI_NS::PayloadArrayData*)(pData);
                        for (size_t i = 0; i < payloadData.size; ++i) {
                            uint64_t entityId = static_cast<uint64_t*>(payloadData.data)[i];
                            if (auto&& pSO = m_scene->GetEntityController()->FindById(entityId).StaticCast<SR_UTILS_NS::SceneObject>()) {
                                commands.emplace_back(new SR_CORE_NS::Commands::GameObjectMove(m_engine, pSO, SR_ID_INVALID));
                            }
                        }
                    }

                    auto&& pCmd = new SR_UTILS_NS::GroupCommand(std::move(commands));
                    m_engine->GetCmdManager()->Execute(pCmd, SR_UTILS_NS::SyncType::Async);
                }
            }
            SR_GRAPH_GUI_NS::Immediate::EndDragDropTarget();
        }

        /// TODO: Это по-хорошему нужно перевести в какой-нибудь MouseUp
        if (!SR_GRAPH_GUI_NS::Immediate::IsAnyItemHovered() && SR_GRAPH_GUI_NS::Immediate::IsWindowHovered() && SR_GRAPH_GUI_NS::Immediate::IsMouseDoubleClicked(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left)) {
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

        if (!pSceneLogic && SR_GRAPH_GUI_NS::Immediate::BeginPopupContextWindow("HierarchyContextMenu")) {
            static_cast<EditorGUI*>(GetManager())->DrawEditorInstanceMenu();

            Paste(nullptr, true);

            SR_GRAPH_GUI_NS::Immediate::EndPopup();
        }
    }

    void Hierarchy::DrawChild(const SR_UTILS_NS::SceneObject::Ptr& pRoot, uint32_t prefabIndex) {
        SR_TRACY_ZONE;

        const uint64_t id = pRoot->GetEntityId();
        SR_GRAPH_GUI_NS::Immediate::PushID((intptr_t)id);

        if (!m_showHidden && pRoot->HasEditorFlags(SR_UTILS_NS::EditorFlags::Hidden)) {
            SR_GRAPH_GUI_NS::Immediate::PopID();
            return;
        }

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

        const SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags flags = (hasChild ? SR_GRAPH_GUI_NS::Immediate::GetNodeFlagsWithChild() : SR_GRAPH_GUI_NS::Immediate::GetNodeFlagsWithoutChild()) |
                                         ((m_selected.count(pRoot) == 1) ? SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::Selected : SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::None);

        if (pRoot->IsPrefabOwner()) {
            ++prefabIndex;
        }

        if (pRoot->HasSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave)) {
            SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text, SR_MATH_NS::FColor(220.f / 255.f, 199.f / 255.f, 0.f / 255.f, 1.f));
        }
        else if (pRoot->GetPrefab()) {
            SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text, prefabIndex % 2 == 0 ? SR_PREFAB_COLOR_FIRST : SR_PREFAB_COLOR_SECOND);
        }

        if (SR_GRAPH_GUI_NS::RadioButton("##", pRoot->IsEnabled(), 0.75f)) {
            auto&& pCmd = new SR_CORE_NS::Commands::EntityEnable(m_engine, pRoot.StaticCast<SR_UTILS_NS::Entity>(), !pRoot->IsEnabled());
            m_engine->GetCmdManager()->Execute(pCmd, SR_UTILS_NS::SyncType::Async);
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        const bool open = SR_GRAPH_GUI_NS::Immediate::TreeNodeEx((void*)(intptr_t)id, flags, "%s", name.c_str());

        if (pRoot->GetPrefab() || pRoot->HasSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave)) {
            SR_GRAPH_GUI_NS::Immediate::PopStyleColor();
        }

        for (auto&& gameObject : m_selected) {
            if (gameObject) {
                ExpandPath(gameObject->GetParent());
            }
        }

        ChildContextMenu(pRoot, id);
        CheckSelected(pRoot);

        if (!SR_GRAPH_GUI_NS::Immediate::GetDragDropPayload() && SR_GRAPH_GUI_NS::Immediate::BeginDragDropSource()) {
            SR_TRACY_ZONE_N("BeginDragDropSource Hierarchy");

            m_pointersHolder.clear();

            bool useSelected = false;

            for (auto&& ptr : m_selected) {
                useSelected |= ptr == pRoot;
            }

            if (useSelected) {
                for (auto&& ptr : m_selected) {
                    if (ptr) {
                        m_pointersHolder.emplace_back(ptr->GetEntityId());
                    }
                }
            }
            else {
                m_pointersHolder.emplace_back(pRoot->GetEntityId());
            }

            SR_GRAPH_GUI_NS::PayloadArrayData payloadData = { m_pointersHolder.data(), m_pointersHolder.size() };
            SR_GRAPH_GUI_NS::Immediate::SetDragDropPayload("Hierarchy##Payload", &payloadData, sizeof(SR_GRAPH_GUI_NS::PayloadArrayData), SR_GRAPH_GUI_NS::Immediate::Condition::Once);
            SR_GRAPH_GUI_NS::Immediate::Text("%s ->", name.c_str());
            SR_GRAPH_GUI_NS::Immediate::EndDragDropSource();
        }

        if (SR_GRAPH_GUI_NS::Immediate::BeginDragDropTarget()) {
            SR_GRAPH_GUI_NS::Immediate::Separator();

            if (auto&& pPayload = SR_GRAPH_GUI_NS::Immediate::GetDragDropPayload()) {
                if (strcmp(SR_GRAPH_GUI_NS::Immediate::GetPayloadType(pPayload), "InspectorComponent##Payload") == 0) {
                    if (m_selected.count(pRoot) == 0) {
                        SelectGameObject(pRoot);
                    }
                }
            }

            if (auto payload = SR_GRAPH_GUI_NS::Immediate::AcceptDragDropPayload("Hierarchy##Payload")) {
                if (auto&& pData = SR_GRAPH_GUI_NS::Immediate::GetDataFromDragDropPayload(payload)) {
                    if (m_scene) {
                        std::vector<SR_UTILS_NS::ReversibleCommand*> commands;
                        commands.emplace_back(new SR_CORE_NS::Commands::ChangeHierarchySelected(m_engine, this, m_selected, {}));
                        SR_GRAPH_GUI_NS::PayloadArrayData payloadData = *(SR_GRAPH_GUI_NS::PayloadArrayData*)(pData);
                        for (size_t i = 0; i < payloadData.size; ++i) {
                            uint64_t entityId = static_cast<uint64_t*>(payloadData.data)[i];
                            if (auto&& pSO = m_scene->GetEntityController()->FindById(entityId).StaticCast<SR_UTILS_NS::SceneObject>()) {
                                commands.emplace_back(new SR_CORE_NS::Commands::GameObjectMove(m_engine, pSO, pRoot->GetEntityId()));
                            }
                        }
                        auto&& cmd = new SR_UTILS_NS::GroupCommand(std::move(commands));
                        m_engine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
                    }
                }
            }

            SR_GRAPH_GUI_NS::Immediate::EndDragDropTarget();
        }

        if (open && hasChild) {
            if (pRoot) {
                pRoot->ForEachChild([&](const SR_UTILS_NS::SceneObject::Ptr &child) {
                    DrawChild(child, prefabIndex);
                });
            }
            SR_GRAPH_GUI_NS::Immediate::TreePop();
        }

        SR_GRAPH_GUI_NS::Immediate::PopID();
    }

    void Hierarchy::ChildContextMenu(const SR_UTILS_NS::SceneObject::Ptr& pSceneObject, uint64_t id) {
        SR_TRACY_ZONE;

        SR_GRAPH_GUI_NS::Immediate::PushID((void*)(intptr_t)id);
        if (SR_GRAPH_GUI_NS::Immediate::BeginPopupContextItem("HierarchyChildContextMenu")) {
            if (m_selected.count(pSceneObject) == 0) {
                SelectGameObject(pSceneObject);
            }

            if (SR_GRAPH_GUI_NS::Immediate::Selectable("Copy")) {
                Copy();
            }

            Paste((m_selected.size() == 1) ? m_selected.begin()->Get() : nullptr, true);

            if (!pSceneObject->HasEditorFlags(SR_UTILS_NS::EditorFlags::DontDelete)) {
                SR_GRAPH_GUI_NS::Immediate::Separator();

                if (SR_GRAPH_GUI_NS::Immediate::Selectable("Cut")) {
                    Copy();
                    Delete();
                }

                SR_GRAPH_GUI_NS::Immediate::Separator();

                if (SR_GRAPH_GUI_NS::Immediate::Selectable("Delete")) {
                    Delete();
                }
            }

            if (pSceneObject) {
                if (pSceneObject->GetPrefab()) {
                    SR_GRAPH_GUI_NS::Immediate::Separator();

                    if (SR_GRAPH_GUI_NS::Immediate::Selectable("Break link")) {
                        pSceneObject->UnlinkPrefab();
                    }

                    SR_GRAPH_GUI_NS::Immediate::Separator();

                    if (SR_GRAPH_GUI_NS::Immediate::Selectable("Edit")) {
                        auto&& prefabPath = pSceneObject->GetPrefab()->GetResourcePath();
                        if (auto&& pScene = SR_WORLD_NS::Scene::LoadScene(prefabPath)) {
                            m_engine->SetActive(false);
                            m_engine->AddSceneToQueue(pScene);
                            m_engine->GetEditor()->CacheScenePath(prefabPath);
                        }
                    }
                }
                else if (SR_GRAPH_GUI_NS::Immediate::Selectable("Make prefab")) {
                    auto&& resPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();

                    if (auto&& path = SR_UTILS_NS::FileDialog::Instance().SaveDialog(resPath.ToString(), { { "Scene", "prefab" } }); !path.IsEmpty()) {
                        path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetCachePath());
                        path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

                        SR_UTILS_NS::SRASerializer serializer;
                        SR_WORLD_NS::ScenePrefabLogic::SaveSOAsPrefab(serializer, pSceneObject);

                        if (auto&& pPrefabScene = SR_WORLD_NS::Scene::NewScene(path, SR_WORLD_NS::SceneLogicType::Prefab)) {
                            pPrefabScene->GetLogicBase().DynamicCast<SR_WORLD_NS::ScenePrefabLogic>()->SetCustomSOData(serializer.CreateDeserializer());
                            pPrefabScene->SaveScene();

                            pSceneObject->DestroyChildren();

                            if (auto&& pPrefab = CoreResLoader::Load<SR_UTILS_NS::Prefab>(path)) {
                                pSceneObject->SetPrefab(pPrefab, true);
                            }
                            else {
                                SR_ERROR("Hierarchy::ChildContextMenu() : failed to load prefab from path: {}", path.ToString());
                            }

                            m_engine->AddSceneToQueue(pPrefabScene);
                        }
                    }
                }

                if (pSceneObject->GetSceneObjectType() == SR_UTILS_NS::SceneObjectType::GameObject) {
                    SR_GRAPH_GUI_NS::Immediate::Separator();

                    if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("Add child")) {
                        static_cast<EditorGUI *>(GetManager())->DrawEditorInstanceMenu();
                        SR_GRAPH_GUI_NS::Immediate::EndMenu();
                    }
                }
            }

            SR_GRAPH_GUI_NS::Immediate::EndPopup();
        }
        SR_GRAPH_GUI_NS::Immediate::PopID();
    }

    void Hierarchy::CheckSelected(const SR_UTILS_NS::SceneObject::Ptr& gm) {
        SR_TRACY_ZONE;
        if (SR_GRAPH_GUI_NS::Immediate::IsItemHovered() && SR_GRAPH_GUI_NS::Immediate::IsMouseReleased(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left)) {
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

        std::vector<SR_UTILS_NS::SceneObject::Ptr> toCopy;
        for (auto&& pSO : m_selected) {
            if (pSO) {
                toCopy.emplace_back(pSO);
            }
        }

        if (toCopy.empty()) {
            return;
        }

        SR_UTILS_NS::SRASerializer serializer;
        SR_UTILS_NS::Serialization::Save(serializer, toCopy, serializeId);
        const std::string clipboardData = serializeId.GetName() + SR_UTILS_NS::StringUtils::Base64Encode(serializer.ToString());
        SR_PLATFORM_NS::TextToClipboard(clipboardData);
    }

    void Hierarchy::Paste(const SR_UTILS_NS::SceneObject::Ptr& pParent, bool fromGUI) {
        static const auto&& serializeId = SR_UTILS_NS::SerializationId::Create("SREngineSceneObjectsClipboard");

        auto&& clipboard = SR_PLATFORM_NS::GetClipboardText();
        if (!clipboard.starts_with(serializeId.GetName())) {
            return;
        }

        if (fromGUI) {
            if (!SR_GRAPH_GUI_NS::Immediate::Selectable("Paste")) {
                return;
            }
        }

        clipboard.erase(0, strlen(serializeId.GetName()));
        SR_UTILS_NS::SRADeserializer deserializer;
        if (!deserializer.LoadFromString(SR_UTILS_NS::StringUtils::Base64Decode(clipboard))) {
            return;
        }

        std::vector<SR_UTILS_NS::SceneObject::Ptr> toPaste;
        SR_UTILS_NS::Serialization::Load(deserializer, toPaste, serializeId);
        if (toPaste.empty()) {
            return;
        }

        std::vector<SR_UTILS_NS::ReversibleCommand*> commands;

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
            std::vector<SR_UTILS_NS::ReversibleCommand*> commands;
            commands.emplace_back(new SR_CORE_NS::Commands::ChangeHierarchySelected(m_engine, this, m_selected, {}));
            for (auto&& pSelected : m_selected) {
                if (!pSelected) {
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

    const std::set<SR_UTILS_NS::SceneObject::Ptr>& Hierarchy::GetSelected() const {
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
        if ((m_selected.count(ptr) != 0)) {
            if ((m_shiftPressed)) {
                return;
            }
            if ((m_selected.size() == 1)) {
                return;
            }
        }

        std::set<SR_UTILS_NS::SceneObject::Ptr> newSelected;
        if (m_shiftPressed) {
            newSelected = m_selected;
        }
        newSelected.insert(ptr);

        auto&& cmd = new SR_CORE_NS::Commands::ChangeHierarchySelected(m_engine, this, m_selected, newSelected);
        m_engine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Sync);
    }

    void Hierarchy::SetSelectedImpl(const std::set<SR_UTILS_NS::SceneObject::Ptr>& changeSelected){
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
        SR_GRAPH_GUI_NS::Immediate::WindowTreeNodeSetOpen(true, id);
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
