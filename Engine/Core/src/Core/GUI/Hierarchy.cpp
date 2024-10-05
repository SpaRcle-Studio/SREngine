//
// Created by Monika on 11.02.2022.
//

#include <Core/GUI/Hierarchy.h>
#include <Core/GUI/SceneRunner.h>

#include <Utils/Input/InputSystem.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Types/SafePtrLockGuard.h>
#include <Utils/TaskManager/TaskManager.h>

#include <Graphics/GUI/Icons.h>

namespace SR_CORE_GUI_NS {
    Hierarchy::Hierarchy()
        : Widget("Hierarchy")
    {
        m_sceneRunnerWidget = new SceneRunner();

        SetFlags(ImGuiWindowFlags_HorizontalScrollbar);
    }

    Hierarchy::~Hierarchy() {
        SR_SAFE_DELETE_PTR(m_sceneRunnerWidget);
    }

    void Hierarchy::Draw() {
        SR_LOCK_GUARD;

        m_shiftPressed = SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::LShift);

        if (m_scene.TryRecursiveLockIfValid()) {
            m_tree = m_scene->GetRootSceneObjects();
            m_scene.Unlock();
        }
        else {
            m_tree.clear();
        }

        m_sceneRunnerWidget->SetManager(GetManager());
        m_sceneRunnerWidget->DrawAsSubWindow();

        ContextMenu();

        for (auto&& gameObject : m_tree) {
            if (!gameObject.Valid()) {
                continue;
            }

            DrawChild(gameObject, -1);
        }
        ImGui::Dummy(ImVec2(0.0f, 10.0f)); ///Требуется, чтобы в конце древа всегда было пустое пространство для вызова контекстного меню

        if (SR_GRAPH_GUI_NS::BeginDragDropTargetWindow("Hierarchy##Payload")) {
            if (auto&& pPayload = ImGui::AcceptDragDropPayload("Hierarchy##Payload"); pPayload != nullptr && pPayload->Data) {
                if (m_scene.RecursiveLockIfValid()) {
                    auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

                    std::vector<SR_UTILS_NS::ReversibleCommand*> commands;
                    commands.emplace_back(new SR_CORE_NS::Commands::ChangeHierarchySelected(pEngine, this, m_selected, { }));
                    for (auto&& ptr : *(std::list<SR_UTILS_NS::SceneObject::Ptr>*)(pPayload->Data)) {
                        if (ptr.RecursiveLockIfValid()) {
                            commands.emplace_back(new SR_CORE_NS::Commands::GameObjectMove(pEngine, ptr, SR_UTILS_NS::SceneObject::Ptr()));
                            ptr.Unlock();
                        }
                    }

                    auto&& cmd = new SR_UTILS_NS::GroupCommand(std::move(commands));
                    pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
                    m_scene.Unlock();
                }
            }
            ImGui::EndDragDropTarget();
        }

        /// TODO: Это по-хорошему нужно перевести в какой-нибудь MouseUp
        if (!ImGui::IsAnyItemHovered() && ImGui::IsWindowHovered() && ImGui::IsMouseDoubleClicked(0)) {
            ClearSelected();
        }

    }

    void Hierarchy::Update(float_t dt) {
        SR_LOCK_GUARD;

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
        SR_LOCK_GUARD;

        m_scene = scene;

        if (auto&& widget = dynamic_cast<SceneRunner*>(m_sceneRunnerWidget)) {
            widget->SetScene(m_scene);
        }
    }

    void Hierarchy::ContextMenu() {
        if (ImGui::BeginPopupContextWindow("HierarchyContextMenu")) {
            if (ImGui::Selectable("Add New GameObject")) {
                auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
                pEngine->GetScene()->InstanceGameObject("New GameObject"_atom);
            }

            ImGui::Separator();

            if (ImGui::Selectable("Paste")) {
                Paste();
            }

            ImGui::Separator();

            if (ImGui::Selectable("Hierarchy Settings (EMPTY)")) { // TODO: Когда-нибудь мы будем настраивать стили окон и подобное, наверное, надеюсь

            }

            ImGui::EndPopup();
        }
    }

    void Hierarchy::DrawChild(const SR_UTILS_NS::SceneObject::Ptr& root, uint32_t prefabIndex) {
        const auto& name = root->GetName();
        const bool hasChild = root->HasChildren();

        const ImGuiTreeNodeFlags flags = (hasChild ? m_nodeFlagsWithChild : m_nodeFlagsWithoutChild) |
                                         ((m_selected.count(root) == 1) ? ImGuiTreeNodeFlags_Selected : 0);

        if (root->IsPrefabOwner()) {
            ++prefabIndex;
        }

        if (root->IsDontSave()) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(220.f / 255.f, 199.f / 255.f, 0.f / 255.f, 1.f));
        }
        else if (root->GetPrefab()) {
            ImGui::PushStyleColor(ImGuiCol_Text, prefabIndex % 2 == 0 ? SR_PREFAB_COLOR_FIRST : SR_PREFAB_COLOR_SECOND);
        }

        const uint64_t id = root->GetEntityId();

        if (SR_GRAPH_GUI_NS::RadioButton(SR_FORMAT_C("##HierarchyEnableGM{}", id), root->IsEnabled(), 0.75f)) {
            root->SetEnabled(!root->IsEnabled());
        }

        ImGui::SameLine();

        const bool open = ImGui::TreeNodeEx((void*)(intptr_t)id, flags, "%s", name.c_str());

        if (root->GetPrefab() || root->IsDontSave()) {
            ImGui::PopStyleColor();
        }

        for (auto&& gameObject : m_selected) {
            if (gameObject) {
                ExpandPath(gameObject->GetParent());
            }
        }

        ChildContextMenu(root, id);
        CheckSelected(root);

        if (!ImGui::GetDragDropPayload() && ImGui::BeginDragDropSource()) {
            m_pointersHolder.clear();

            bool useSelected = false;

            for (auto&& ptr : m_selected) {
                useSelected |= ptr == root;
            }

            if (useSelected) {
                for (auto&& ptr : m_selected) {
                    if (ptr.RecursiveLockIfValid()) {
                        m_pointersHolder.emplace_back(ptr);
                        ptr.Unlock();
                    }
                }
            }
            else {
                m_pointersHolder.emplace_back(root);
            }

            ImGui::SetDragDropPayload("Hierarchy##Payload", &m_pointersHolder, sizeof(std::list<SR_UTILS_NS::SceneObject::Ptr>), ImGuiCond_Once);
            ImGui::Text("%s ->", name.c_str());
            ImGui::EndDragDropSource();
        }

        if (ImGui::BeginDragDropTarget()) {
            ImGui::Separator();

            if (auto&& pPayload = ImGui::GetDragDropPayload(); pPayload && strcmp(pPayload->DataType, "InspectorComponent##Payload") == 0) {
                if (m_selected.count(root) == 0) {
                    SelectGameObject(root);
                }
            }

            if (auto payload = ImGui::AcceptDragDropPayload("Hierarchy##Payload"); payload != nullptr && payload->Data) {
                /*for (auto&& ptr : *(std::list<Helper::GameObject::Ptr>*)(payload->Data)) {
                    if (ptr.RecursiveLockIfValid()) {
                        ptr->MoveToTree(root);
                        ptr->Unlock();
                    }
                }*/
                if (m_scene.RecursiveLockIfValid()) {
                    auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

                    std::vector<SR_UTILS_NS::ReversibleCommand*> commands;
                    commands.emplace_back(new SR_CORE_NS::Commands::ChangeHierarchySelected(pEngine, this, m_selected, {}));
                    for (auto&& ptr : *(std::list<SR_UTILS_NS::SceneObject::Ptr>*)(payload->Data)) {
                        if (ptr.RecursiveLockIfValid()) {
                            commands.emplace_back(new SR_CORE_NS::Commands::GameObjectMove(pEngine, ptr, root));
                            ptr.Unlock();
                        }
                    }
                    auto&& cmd = new SR_UTILS_NS::GroupCommand(std::move(commands));
                    pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
                    m_scene.Unlock();
                }
            }

            ImGui::EndDragDropTarget();
        }

        if (open && hasChild) {
            if (root) {
                root->ForEachChild([&](const SR_UTILS_NS::SceneObject::Ptr &child) {
                    DrawChild(child, prefabIndex);
                });
            }
            ImGui::TreePop();
        }
    }

    void Hierarchy::ChildContextMenu(const SR_UTILS_NS::SceneObject::Ptr& pSceneObject, uint64_t id) {
        ImGui::PushID((void*)(intptr_t)id);
        if (ImGui::BeginPopupContextItem("HierarchyChildContextMenu")) {
            if (m_selected.count(pSceneObject) == 0) {
                SelectGameObject(pSceneObject);
            }

            if (ImGui::Selectable("Copy")) {
                Copy();
            }

            ImGui::Separator();

            if (ImGui::Selectable("Paste")) {
                Paste((m_selected.size() == 1) ? m_selected.begin()->Get() : nullptr);
            }

            ImGui::Separator();

            if (ImGui::Selectable("Cut")) {
                Copy();
                Delete();
            }

            ImGui::Separator();

            if (ImGui::Selectable("Delete")) {
                Delete();
            }

            if (pSceneObject->GetPrefab()) {
                ImGui::Separator();

                if (ImGui::Selectable("Break link")) {
                    pSceneObject->UnlinkPrefab();
                }

                ImGui::Separator();

                if (ImGui::Selectable("Edit")) {
                    auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
                    auto&& prefabPath = pSceneObject->GetPrefab()->GetResourcePath();
                    if (auto&& pScene = SR_WORLD_NS::Scene::Load(prefabPath)) {
                        pEngine->SetActive(false);
                        pEngine->SetScene(pScene);
                        pEngine->GetEditor()->CacheScenePath(prefabPath);
                    }
                }
            }

            if (pSceneObject->GetSceneObjectType() == SR_UTILS_NS::SceneObjectType::GameObject) {
                ImGui::Separator();
                if (ImGui::Selectable("Add child game object")) {
                    pSceneObject->AddChild(pSceneObject->GetScene()->InstanceGameObject("New GameObject"_atom).StaticCast<SR_UTILS_NS::SceneObject>());
                }
            }

            ImGui::EndPopup();
        }
        ImGui::PopID();
    }

    void Hierarchy::CheckSelected(const SR_UTILS_NS::SceneObject::Ptr& gm) {
        if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            SelectGameObject(gm);
        }
    }

    void Hierarchy::OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) {
        switch (data->GetKeyCode()) {
            case SR_UTILS_NS::KeyCode::C: {
                if (IsKeyPressed(SR_UTILS_NS::KeyCode::Ctrl))
                    Copy();
                break;
            }
            case SR_UTILS_NS::KeyCode::V: {
                if (IsKeyPressed(SR_UTILS_NS::KeyCode::Ctrl))
                    Paste((m_selected.size() == 1) ? m_selected.begin()->Get() : nullptr);
                break;
            }
            case SR_UTILS_NS::KeyCode::Del: {
                Delete();
                break;
            }
            default:
                break;
        }

        InputHandler::OnKeyDown(data);
    }

    void Hierarchy::OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) {
        SR_LOCK_GUARD;

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
        auto&& pMarshal = new SR_HTYPES_NS::Marshal();

        pMarshal->Write<std::string>("SRCopyPaste#Hierarchy"); /// Требуется для проверки валидности содержимого буфера обмена в методе Paste()

        pMarshal->Write(static_cast<uint64_t>(m_selected.size()));

        for (auto&& ptr : m_selected) {
            if (ptr.RecursiveLockIfValid()) {
                pMarshal = ptr->Save(SR_UTILS_NS::SavableContext(pMarshal, SR_UTILS_NS::SAVABLE_FLAG_ECS_NO_ID));
                ptr.Unlock();
            }
        }

        if (pMarshal && pMarshal->Valid()) {
            SR_UTILS_NS::Platform::TextToClipboard(pMarshal->ToBase64());
        }

        SR_SAFE_DELETE_PTR(pMarshal)
    }

    void Hierarchy::Paste(const SR_UTILS_NS::SceneObject::Ptr& pParent) {
        auto&& base64 = SR_UTILS_NS::Platform::GetClipboardText();
        auto marshal = SR_HTYPES_NS::Marshal::LoadFromBase64(base64);
        if (!marshal.Valid()) {
            SR_WARN("Hierarchy::Paste() : content of clipboard couldn't be read");
            return;
        }

        if (marshal.TryRead<std::string>() != "SRCopyPaste#Hierarchy") {
            SR_LOG("Hierarchy::Paste() : attempted to paste invalid content from clipboard!"); ///TODO: Стоит ли оповещать об этом?
            return;
        }

        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
        auto&& cmd = new SR_CORE_NS::Commands::HierarchyPaste(pEngine, this, marshal.CopyPtr(), pParent);
        pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
    }

    void Hierarchy::Delete() {
        SR_LOCK_GUARD;

        if (!m_selected.empty() && m_scene.RecursiveLockIfValid()) {
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

            std::vector<SR_UTILS_NS::ReversibleCommand*> commands;
            commands.emplace_back(new SR_CORE_NS::Commands::ChangeHierarchySelected(pEngine, this, m_selected, {}));
            for (auto&& selected : m_selected) {
                if (selected.RecursiveLockIfValid()) {
                    commands.emplace_back(new SR_CORE_NS::Commands::GameObjectDelete(pEngine, selected));
                    selected.Unlock();
                }
            }
            auto&& cmd = new SR_UTILS_NS::GroupCommand(std::move(commands));
            pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
            m_selected.clear();
            m_scene.Unlock();
        }
    }

    const std::set<SR_UTILS_NS::SceneObject::Ptr>& Hierarchy::GetSelected() const {
        SR_LOCK_GUARD;
        return m_selected;
    }

    void Hierarchy::ClearSelected() {
        SR_LOCK_GUARD;
        /// команда не должна срабатывать, если ни один объект не выделен, иначе такая команда бесполезна
        if (!m_selected.empty()) {
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
            auto&& cmd = new SR_CORE_NS::Commands::ChangeHierarchySelected(pEngine, this, m_selected, { });
            pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Sync);
        }
    }

    void Hierarchy::SelectGameObject(const SR_UTILS_NS::SceneObject::Ptr& ptr) {
        SR_LOCK_GUARD;

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

        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();

        auto&& cmd = new SR_CORE_NS::Commands::ChangeHierarchySelected(pEngine, this, m_selected, newSelected);
        pEngine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Sync);
    }

    void Hierarchy::SetSelectedImpl(const std::set<SR_UTILS_NS::SceneObject::Ptr>& changeSelected){
        SR_LOCK_GUARD;
        m_selected = changeSelected;
#ifdef SR_DEBUG
        for (auto&& pGameObject : m_selected) {
            SRAssert(pGameObject);
        }
#endif
    }

    void Hierarchy::ExpandPath(const SR_UTILS_NS::SceneObject::Ptr& gm) { /** NOLINT */
        if (!gm) {
            return;
        }
        const uint64_t id = gm->GetEntityId();
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        ImGui::TreeNodeSetOpen(window->GetID((void*)(intptr_t)id), true);
        ExpandPath(gm->GetParent());
    }
}