//
// Created by Monika on 11.02.2022.
//

#include <GUI/Hierarchy.h>
#include <Input/InputSystem.h>
#include <Platform/Platform.h>

namespace SR_CORE_NS::GUI {
    Hierarchy::Hierarchy()
        : Widget("Hierarchy")
    { }

    void Hierarchy::Draw() {
        std::lock_guard<std::mutex> lock(m_mutex);

        m_shiftPressed = Helper::Input::GetKey(Helper::KeyCode::LShift);

        if (m_scene.LockIfValid()) {
            m_scene->ForEachRootObjects([&](const Helper::GameObject::Ptr& gm) {
                DrawChild(gm);
            });

            m_scene.Unlock();
        }
    }

    void Hierarchy::SetScene(const SR_WORLD_NS::Scene::Ptr& scene) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_scene = scene;
    }

    void Hierarchy::ContextMenu(const Helper::GameObject::Ptr &gm, uint64_t id) const {
        ImGui::PushID((void*)(intptr_t)id);
        if (ImGui::BeginPopupContextItem("HierarchyContextMenu")) {
            if (m_scene->GetAllSelected().count(gm) == 0) {
                gm->GetScene()->DeSelectAll();
                gm->SetSelect(true);
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

            }

            ImGui::Separator();

            if (ImGui::Selectable("Delete")) {

            }

            ImGui::Separator();

            if (ImGui::Selectable("Add children")) {

            }

            ImGui::EndPopup();
        }
        ImGui::PopID();
    }

    void Hierarchy::CheckSelected(const Helper::Types::SafePtr<Helper::GameObject> &gm) const {
        if (ImGui::IsItemClicked() && !gm->IsSelected()) {
            if (!m_shiftPressed && gm->GetScene().Valid())
                gm->GetScene()->DeSelectAll();

            gm->SetSelect(true);
        }
    }

    void Hierarchy::DrawChild(const Helper::GameObject::Ptr &root) {
        const auto& name = root->GetName();
        const bool hasChild = root->HasChildren();

        const ImGuiTreeNodeFlags flags = (hasChild ? m_nodeFlagsWithChild : m_nodeFlagsWithoutChild) |
                (root->IsSelected() ? ImGuiTreeNodeFlags_Selected : 0);

        const uint64_t id = root->GetEntityId();
        const bool open = ImGui::TreeNodeEx((void*)(intptr_t)id, flags, "%s", name.c_str());

        ContextMenu(root, id);
        CheckSelected(root);

        if (!ImGui::GetDragDropPayload() && ImGui::BeginDragDropSource()) {
            m_pointersHolder.clear();

            for (const GameObject::Ptr& ptr : m_scene->GetAllSelected())
                m_pointersHolder.emplace_back(ptr);

            ImGui::SetDragDropPayload("Hierarchy##Payload", &m_pointersHolder, sizeof(std::list<Helper::GameObject::Ptr>), ImGuiCond_Once);
            ImGui::Text("%s ->", name.c_str());
            ImGui::EndDragDropSource();
        }

        if (ImGui::BeginDragDropTarget()) {
            ImGui::Separator();

            if (auto payload = ImGui::AcceptDragDropPayload("Hierarchy##Payload"); payload != NULL && payload->Data) {
                for (auto&& ptr : *(std::list<Helper::GameObject::Ptr>*)(payload->Data)) {
                    if (ptr.RecursiveLockIfValid()) {
                        ptr->MoveToTree(root);
                        ptr->Unlock();
                    }
                }
            }

            ImGui::EndDragDropTarget();
        }

        if (open && hasChild) {
            root->ForEachChild([&](const Helper::GameObject::Ptr &child) {
                DrawChild(child);
            });
            ImGui::TreePop();
        }
    }

    void Hierarchy::OnKeyDown(const KeyDownEvent &event) {
        switch (event.GetKeyCode()) {
            case KeyCode::C: {
                if (IsKeyPressed(KeyCode::Ctrl))
                    Copy();
                break;
            }
            case KeyCode::V: {
                if (IsKeyPressed(KeyCode::Ctrl))
                    Paste();
                break;
            }
            case KeyCode::Del:
                if (m_scene.LockIfValid()) {
                    for (auto&& selected : m_scene->GetAllSelected()) {
                        if (selected.LockIfValid()) {
                            auto cmd = new Framework::Core::Commands::GameObjectDelete(selected);
                            Engine::Instance().GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
                            selected.Unlock();
                        }
                    }
                    m_scene.Unlock();
                }
                break;
            default:
                break;
        }

        InputHandler::OnKeyDown(event);
    }

    void Hierarchy::OnKeyUp(const KeyUpEvent &event) {
        switch (event.GetKeyCode()) {
            case KeyCode::LShift: {
                if (m_pointersHolder.size() > 1) {
                    m_pointersHolder.clear();
                }
                break;
            }
            default:
                break;
        }

        InputHandler::OnKeyUp(event);
    }

    void Hierarchy::Copy() const {
        MarshalEncodeNode marshal;

        for (auto&& ptr : m_scene->GetAllSelected()) {
            marshal.Append(ptr->Save(SAVABLE_FLAG_ECS_NO_ID));
        }

        if (marshal.Valid())
            Helper::Platform::TextToClipboard(marshal.ToString());
    }

    void Hierarchy::Paste() const {
        if (auto marshal = Helper::MarshalDecodeNode::LoadFromMemory(Helper::Platform::GetClipboardText())) {
            m_scene->DeSelectAll();
            for (const auto& gameObject : marshal.GetNodes()) {
                if (auto&& ptr = m_scene->Instance(gameObject))
                    ptr->SetSelect(true);
            }
        }
    }
}