//
// Created by Monika on 11.02.2022.
//

#include <Core/GUI/Hierarchy.h>

#include <Utils/Input/InputSystem.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Types/SafePtrLockGuard.h>
#include <Utils/TaskManager/TaskManager.h>
#include <GUI/Icons.h>
#include <Core/GUI/SceneRunner.h>

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

        m_sceneRunnerWidget->DrawSubWindow();

        for (auto&& gameObject : m_tree) {
            if (!gameObject.LockIfValid())
                continue;

            DrawChild(gameObject);
            gameObject.Unlock();
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
                m_selected.clear();
                m_selected.insert(gm);
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

    void Hierarchy::CheckSelected(const Helper::Types::SafePtr<Helper::GameObject> &gm) {
        if (ImGui::IsItemClicked() && m_selected.count(gm) == 0) {
            if (!m_shiftPressed && gm->GetScene().Valid())
                m_selected.clear();

            m_selected.insert(gm);
        }
    }

    void Hierarchy::DrawChild(const Helper::GameObject::Ptr &root) {
        const auto& name = root->GetName();
        const bool hasChild = root->HasChildren();

        const ImGuiTreeNodeFlags flags = (hasChild ? m_nodeFlagsWithChild : m_nodeFlagsWithoutChild) |
                ((m_selected.count(root) == 1) ? ImGuiTreeNodeFlags_Selected : 0);

        const uint64_t id = root->GetEntityId();
        const bool open = ImGui::TreeNodeEx((void*)(intptr_t)id, flags, "%s", name.c_str());

        ContextMenu(root, id);
        CheckSelected(root);

        if (!ImGui::GetDragDropPayload() && ImGui::BeginDragDropSource()) {
            m_pointersHolder.clear();

            for (const SR_UTILS_NS::GameObject::Ptr& ptr : m_selected) {
                if (ptr.RecursiveLockIfValid()) {
                    m_pointersHolder.emplace_back(ptr);
                    ptr.Unlock();
                }
            }

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
                SR_LOCK_GUARD

                if (m_scene.LockIfValid()) {
                    for (auto&& selected : m_selected) {
                        if (selected.LockIfValid()) {
                            auto cmd = new Framework::Core::Commands::GameObjectDelete(selected);
                            Engine::Instance().GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
                            selected.Unlock();
                        }
                    }
                    m_selected.clear();
                    m_scene.Unlock();
                }
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
        SR_HTYPES_NS::Marshal marshal;

        marshal.Write(static_cast<uint64_t>(m_selected.size()));

        for (auto&& ptr : m_selected) {
            if (ptr.LockIfValid()) {
                marshal.Append(ptr->Save(SR_UTILS_NS::SAVABLE_FLAG_ECS_NO_ID));
                ptr.Unlock();
            }
        }

        if (marshal.Valid()) {
            Helper::Platform::TextToClipboard(marshal.ToBase64());
        }
    }

    void Hierarchy::Paste() {
        /// TODO: перевести на команды
        SR_UTILS_NS::TaskManager::Instance().Execute([this](std::atomic<SR_UTILS_NS::Task::State>* state) {
            SR_HTYPES_NS::SafePtrLockGuard m_lock(GetRenderScene());

            state->store(SR_UTILS_NS::Task::State::Completed);
            auto&& base64 = Helper::Platform::GetClipboardText();

            if (auto marshal = SR_HTYPES_NS::Marshal::LoadFromBase64(base64); marshal.Valid()) {
                std::set<Helper::GameObject::Ptr> selected;

                if (m_scene.LockIfValid()) {
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

                {
                    SR_LOCK_GUARD
                    m_selected = selected;
                }
            }
        });
    }

    std::set<Helper::GameObject::Ptr> Hierarchy::GetSelected() const {
        SR_LOCK_GUARD
        return m_selected;
    }
}