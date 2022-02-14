//
// Created by Monika on 11.02.2022.
//

#include <GUI/Editor/Hierarchy.h>
#include <Input/InputSystem.h>

namespace SR_GRAPH_NS::GUI {
    Hierarchy::Hierarchy()
        : Widget("Hierarchy")
    { }

    void Hierarchy::Draw() {
        m_shiftPressed = Helper::Input::GetKey(Helper::KeyCode::LShift);

        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_scene.LockIfValid()) {
            uint64_t i = 0;

            if (ImGui::TreeNodeEx(m_scene->GetName().c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3);

                m_scene->ForEachRootObjects([&i, this](const Helper::Types::SafePtr<Helper::GameObject>& gm) {
                    if (gm->HasChildren()) {
                        const bool open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                                      m_nodeFlagsWithChild | (gm->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                                      "%s", gm->GetName().c_str());
                        CheckSelected(gm);

                        if (open)
                            DrawChild(gm);
                    }
                    else {
                        ImGui::TreeNodeEx((void *) (intptr_t) i,
                                          m_nodeFlagsWithoutChild | (gm->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                          "%s", gm->GetName().c_str());

                        CheckSelected(gm);
                    }
                    i++;
                });
                ImGui::TreePop();
                ImGui::PopStyleVar();
            }

            m_scene.Unlock();
        }
    }

    void Hierarchy::SetScene(const SR_WORLD_NS::Scene::Ptr& scene) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_scene = scene;
    }

    void Hierarchy::CheckSelected(const Helper::Types::SafePtr<Helper::GameObject> &gm) const {
        if (ImGui::IsItemClicked()) {
            if (!m_shiftPressed && gm->GetScene().Valid())
                gm->GetScene()->DeSelectAll();

            gm->SetSelect(true);
        }
    }

    void Hierarchy::DrawChild(const Helper::Types::SafePtr<Helper::GameObject> &root) const {
        uint64_t i = 0;

        root->ForEachChild([&i, this](const Helper::Types::SafePtr<Helper::GameObject>& child){
            if (child->HasChildren()) {
                const bool open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                              m_nodeFlagsWithChild |
                                              (child->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                              "%s", child->GetName().c_str()
                );

                CheckSelected(child);

                if (open)
                    DrawChild(child);

            } else {
                ImGui::TreeNodeEx((void *) (intptr_t) i,
                                  m_nodeFlagsWithoutChild | (child->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                  "%s", child->GetName().c_str()
                );

                CheckSelected(child);
            }

            ++i;
        });

        ImGui::TreePop();
    }
}