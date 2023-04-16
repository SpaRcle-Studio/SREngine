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

namespace SR_CORE_NS::GUI {
    Hierarchy::Hierarchy()
        : Widget("Hierarchy")
    {
        m_sceneRunnerWidget = new SceneRunner();
    }

    Hierarchy::~Hierarchy() {
        SR_SAFE_DELETE_PTR(m_sceneRunnerWidget);
    }

    void Hierarchy::Draw() {
        SR_LOCK_GUARD

        m_shiftPressed = SR_UTILS_NS::Input::Instance().GetKey(Helper::KeyCode::LShift);

        if (m_scene.TryRecursiveLockIfValid()) {
            m_tree = m_scene->GetRootGameObjects();
            m_scene.Unlock();
        }
        else {
            m_tree.clear();
        }

        m_sceneRunnerWidget->SetManager(GetManager());
        m_sceneRunnerWidget->DrawAsSubWindow();

        for (auto&& gameObject : m_tree) {
            if (!gameObject.RecursiveLockIfValid()) {
                continue;
            }

            DrawChild(gameObject);
            gameObject.Unlock();
        }

        if (GUISystem::Instance().BeginDragDropTargetWindow("Hierarchy##Payload")) {
            if (auto payload = ImGui::AcceptDragDropPayload("Hierarchy##Payload"); payload != NULL && payload->Data) {
                /*for (auto&& ptr : *(std::list<Helper::GameObject::Ptr>*)(payload->Data)) {
                    if (ptr.RecursiveLockIfValid()) {
                        ptr->MoveToTree(SR_UTILS_NS::GameObject::Ptr());
                        ptr->Unlock();
                    }
                }*/
                if (m_scene.RecursiveLockIfValid()) {
                    std::vector<SR_UTILS_NS::ReversibleCommand*> commands;
                    commands.emplace_back(new Framework::Core::Commands::ChangeHierarchySelected(this, m_selected, {}));
                    for (auto&& ptr : *(std::list<Helper::GameObject::Ptr>*)(payload->Data)) {
                        if (ptr.RecursiveLockIfValid()) {
                            commands.emplace_back(new Framework::Core::Commands::GameObjectMove(ptr, SR_UTILS_NS::GameObject::Ptr()));
                            ptr.Unlock();
                        }
                    }
                    auto&& cmd = new SR_UTILS_NS::GroupCommand(std::move(commands));
                    Engine::Instance().GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
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

    void Hierarchy::Update() {
        SR_LOCK_GUARD

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
        SR_LOCK_GUARD

        m_scene = scene;

        if (auto&& widget = dynamic_cast<SceneRunner*>(m_sceneRunnerWidget)) {
            widget->SetScene(m_scene);
        }
    }

    void Hierarchy::ContextMenu(const Helper::GameObject::Ptr &gm, uint64_t id) {
        ImGui::PushID((void*)(intptr_t)id);
        if (ImGui::BeginPopupContextItem("HierarchyContextMenu")) {
            if (m_selected.count(gm) == 0) {
                SelectGameObject(gm);
            }

            if (ImGui::Selectable("Copy")) {
                Copy();
            }

            ImGui::Separator();

            if (ImGui::Selectable("Paste")) {
                Paste();
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

            ImGui::Separator();

            if (ImGui::Selectable("Add children")) { ///TODO: ВСМЫСЛЕ children???? Можно добавлять несколько детей одной командой????

            }

            ImGui::EndPopup();
        }
        ImGui::PopID();
    }

    void Hierarchy::CheckSelected(const SR_UTILS_NS::GameObject::Ptr& gm) {
        if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            SelectGameObject(gm);
        }
    }

    void Hierarchy::DrawChild(const SR_UTILS_NS::GameObject::Ptr &root) {
        const auto& name = root->GetName();
        const bool hasChild = root->HasChildren();

        const ImGuiTreeNodeFlags flags = (hasChild ? m_nodeFlagsWithChild : m_nodeFlagsWithoutChild) |
                ((m_selected.count(root) == 1) ? ImGuiTreeNodeFlags_Selected : 0);

        const uint64_t id = root->GetEntityId();
        const bool open = ImGui::TreeNodeEx((void*)(intptr_t)id, flags, "%s", name.c_str());

        for (auto&& gameObject : m_selected) {
            if (gameObject) {
                ExpandPath(gameObject->GetParent());
            }
        }

        ContextMenu(root, id);

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

            ImGui::SetDragDropPayload("Hierarchy##Payload", &m_pointersHolder, sizeof(std::list<Helper::GameObject::Ptr>), ImGuiCond_Once);
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

            if (auto payload = ImGui::AcceptDragDropPayload("Hierarchy##Payload"); payload != NULL && payload->Data) {
                /*for (auto&& ptr : *(std::list<Helper::GameObject::Ptr>*)(payload->Data)) {
                    if (ptr.RecursiveLockIfValid()) {
                        ptr->MoveToTree(root);
                        ptr->Unlock();
                    }
                }*/
                if (m_scene.RecursiveLockIfValid()) {
                    std::vector<SR_UTILS_NS::ReversibleCommand*> commands;
                    commands.emplace_back(new Framework::Core::Commands::ChangeHierarchySelected(this, m_selected, {}));
                    for (auto&& ptr : *(std::list<Helper::GameObject::Ptr>*)(payload->Data)) {
                        if (ptr.RecursiveLockIfValid()) {
                            commands.emplace_back(new Framework::Core::Commands::GameObjectMove(ptr, root));
                            ptr.Unlock();
                        }
                    }
                    auto&& cmd = new SR_UTILS_NS::GroupCommand(std::move(commands));
                    Engine::Instance().GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
                    m_scene.Unlock();
                }
            }

            ImGui::EndDragDropTarget();
        }

        if (open && hasChild) {
            if (root) {
                root->ForEachChild([&](const SR_UTILS_NS::GameObject::Ptr &child) {
                    DrawChild(child);
                });
            }
            ImGui::TreePop();
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
                    Paste();
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
        SR_LOCK_GUARD

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

        pMarshal->Write(static_cast<uint64_t>(m_selected.size()));

        for (auto&& ptr : m_selected) {
            if (ptr.RecursiveLockIfValid()) {
                pMarshal = ptr->Save(pMarshal, SR_UTILS_NS::SAVABLE_FLAG_ECS_NO_ID);
                ptr.Unlock();
            }
        }

        if (pMarshal && pMarshal->Valid()) {
            SR_UTILS_NS::Platform::TextToClipboard(pMarshal->ToBase64());
        }

        SR_SAFE_DELETE_PTR(pMarshal);
    }

    void Hierarchy::Paste() {

        auto&& base64 = Helper::Platform::GetClipboardText();

        if (auto marshal = SR_HTYPES_NS::Marshal::LoadFromBase64(base64); marshal.Valid()) {
            std::set<Helper::GameObject::Ptr> selected;

            if (m_scene.RecursiveLockIfValid()) {
                auto&& count = marshal.Read<uint64_t>();

                if (count > 1000) {
                    SR_WARN("Hierarchy::Paste() : attempt to insert a large number of objects! Count: " + SR_UTILS_NS::ToString(count));
                }

                for (uint64_t i = 0; i < count; ++i) {
                    if (auto &&ptr = m_scene->Instance(marshal)) {
                        selected.insert(ptr);
                    }
                    else
                        break;
                }
                m_scene.Unlock();
            }

            SetSelectedImpl(selected);
        }
    }

    void Hierarchy::Delete() {
        SR_LOCK_GUARD

        if (!m_selected.empty() && m_scene.RecursiveLockIfValid()) {
            std::vector<SR_UTILS_NS::ReversibleCommand*> commands;
            commands.emplace_back(new Framework::Core::Commands::ChangeHierarchySelected(this, m_selected, {}));
            for (auto&& selected : m_selected) {
                if (selected.RecursiveLockIfValid()) {
                    commands.emplace_back(new Framework::Core::Commands::GameObjectDelete(selected));
                    selected.Unlock();
                }
            }
            auto&& cmd = new SR_UTILS_NS::GroupCommand(std::move(commands));
            Engine::Instance().GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
            m_selected.clear();
            m_scene.Unlock();
        }
    }

    std::set<Helper::GameObject::Ptr> Hierarchy::GetSelected() const {
        SR_LOCK_GUARD
        return m_selected;
    }

    void Hierarchy::ClearSelected() {
        SR_LOCK_GUARD
        if (!m_selected.empty()) { ///команда не должна срабатывать, если ни один объект не выделен, иначе такая команда бесполезна
            auto&& cmd = new Framework::Core::Commands::ChangeHierarchySelected(this, m_selected, {});
            Engine::Instance().GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Sync);
        }
    }

    void Hierarchy::SelectGameObject(const SR_UTILS_NS::GameObject::Ptr& ptr) {
        SR_LOCK_GUARD

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

        std::set<SR_UTILS_NS::GameObject::Ptr> newSelected;
        if (m_shiftPressed) {
            newSelected = m_selected;
        }
        newSelected.insert(ptr);

        auto&& cmd = new Framework::Core::Commands::ChangeHierarchySelected(this, m_selected, newSelected);
        Engine::Instance().GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Sync);
    }

    void Hierarchy::SetSelectedImpl(const std::set<SR_UTILS_NS::GameObject::Ptr>& changeSelected){
        SR_LOCK_GUARD
        m_selected = changeSelected;
#ifdef SR_DEBUG
        for (auto&& ptr : m_selected) {
            SRAssert(ptr);
        }
#endif
        m_needExpand = true;
    }

    void Hierarchy::ExpandPath(const SR_UTILS_NS::GameObject::Ptr& gm) { /** NOLINT */
        if (!gm) {
            return;
        }
        const uint64_t id = gm->GetEntityId();
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        ImGui::TreeNodeSetOpen(window->GetID((void*)(intptr_t)id), true);
        ExpandPath(gm->GetParent());
    }
}