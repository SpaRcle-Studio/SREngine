//
// Created by Nikita on 14.01.2021.
//

#ifndef GAMEENGINE_GUIWINDOW_H
#define GAMEENGINE_GUIWINDOW_H

#include <Input/InputSystem.h>
#include <Debug.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <glm/glm.hpp>
#include <EntityComponentSystem/Scene.h>

namespace Framework::Graphics::GUI {
    class GUIWindow {
    private:
        inline static const ImGuiTreeNodeFlags g_node_flags_with_child    = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        inline static const ImGuiTreeNodeFlags g_node_flags_without_child = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;
        inline static bool m_shiftPressed = false;
    public:
        GUIWindow() = delete;
        ~GUIWindow() = delete;
    private:
        inline static void CheckSelected(Helper::GameObject* gm) noexcept {
            if (ImGui::IsItemClicked()) {
                if (!m_shiftPressed)
                    gm->GetScene()->UnselectAll();

                gm->SetSelect(true);
            }
        }
        inline static void DrawChild(Helper::GameObject* root) noexcept {
            unsigned long i = 0;

            for (auto child : root->GetChildrenRef()) {
                if (child->HasChildren()){
                    bool open = ImGui::TreeNodeEx((void*)(intptr_t)i,
                            g_node_flags_with_child | (child->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                            "%s", child->GetName().c_str()
                    );

                    CheckSelected(child);

                    if (open)
                        DrawChild(child);
                } else {
                    ImGui::TreeNodeEx((void*)(intptr_t)i,
                            g_node_flags_without_child | (child->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                            "%s", child->GetName().c_str()
                    );

                    CheckSelected(child);
                }

                i++;
            }

            ImGui::TreePop();
        }
    public:
        inline static void DrawHierarchy(Helper::Scene* scene) noexcept {
            auto root = scene->GetRootGameObjects();

            unsigned long i = 0;

            GUIWindow::m_shiftPressed = Helper::InputSystem::IsPressed(Helper::KeyCode::LShift);

            if (ImGui::TreeNodeEx(scene->GetName().c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3);

                for (auto obj : root){
                    if (obj->HasChildren()) {
                        bool open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                          g_node_flags_with_child     | (obj->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                          "%s", obj->GetName().c_str());

                        CheckSelected(obj);

                        if (open)
                            DrawChild(obj);
                    } else {
                        ImGui::TreeNodeEx((void *) (intptr_t) i,
                                          g_node_flags_without_child | (obj->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                          "%s", obj->GetName().c_str());

                        CheckSelected(obj);
                    }

                    i++;
                }

                ImGui::TreePop();
                ImGui::PopStyleVar();
            }
            /*Helper::SceneTree tree = scene->GetTree();

            Helper::GameObject* obj = nullptr;

            if (ImGui::TreeNode(scene->GetName().c_str())) {
                ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3);

                for (unsigned long i = 0; i < tree->GetCountBranches(); i++) {
                    obj = tree->m_branches[i]->m_data;

                    if (obj->HasChildren()) {
                        ImGui::TreeNodeEx((void *) (intptr_t) i,
                                          g_node_flags_with_child     | (obj->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                          "%s", obj->GetName().c_str());
                    } else {
                        ImGui::TreeNodeEx((void *) (intptr_t) i,
                                           g_node_flags_without_child | (obj->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                          "%s", obj->GetName().c_str());
                    }
                }

                ImGui::TreePop();
                ImGui::PopStyleVar();
            }*/
        }

        inline static void Begin(const std::string& winName) noexcept {
            ImGui::Begin(winName.c_str());
        }
        inline static void BeginChild(const std::string& winName) noexcept {
            ImGui::BeginChild(winName.c_str());
        }

        inline static bool BeginMainMenuBar() noexcept { return ImGui::BeginMainMenuBar(); }
        inline static void EndMainMenuBar() noexcept { ImGui::EndMainMenuBar(); }

        inline static bool BeginMenu(const char* name) noexcept { return ImGui::BeginMenu(name); }
        inline static void EndMenu() noexcept { ImGui::EndMenu(); }

        inline static bool MenuItem(const char* name) noexcept { return ImGui::MenuItem(name); }

        inline static void End() noexcept {
            ImGui::End();
        }
        inline static void EndChild() noexcept {
            ImGui::EndChild();
        }
        inline static glm::vec2 GetWindowSize() {
            ImVec2 size = ImGui::GetWindowSize();
            return {size.x, size.y};
        }
        inline static void DrawImage(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col, bool imposition = false)
        {
            ImGuiWindow* window = ImGui::GetCurrentWindow();
            if (window->SkipItems)
                return;

            ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
            if (border_col.w > 0.0f)
                bb.Max += ImVec2(2, 2);

            if (!imposition) {
                ImGui::ItemSize(bb);
                if (!ImGui::ItemAdd(bb, 0))
                    return;
            }

            //user_texture_id = (void*)5;

            if (border_col.w > 0.0f)
            {
                window->DrawList->AddRect(bb.Min, bb.Max, ImGui::GetColorU32(border_col), 0.0f);
                window->DrawList->AddImage(user_texture_id, bb.Min + ImVec2(1, 1), bb.Max - ImVec2(1, 1), uv0, uv1, ImGui::GetColorU32(tint_col));
            }
            else
            {
                window->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, uv0, uv1, ImGui::GetColorU32(tint_col));
            }
        }
        inline static void DrawTexture(glm::vec2 win_size, glm::vec2 img_size, unsigned int tex, const bool centralize = true) {
            const float dx = win_size.x / img_size.x;
            const float dy = win_size.y / img_size.y;

            if (dx > dy)
                img_size *= dy;
            else
                if (dy > dx)
                    img_size *= dx;
                else
                    img_size *= dy;

            // Because I use the texture from OpenGL, I need to invert the V from the UV.

            if (centralize) {
                ImVec2 initialCursorPos = ImGui::GetCursorPos();
                glm::vec2 res = (win_size - img_size) * 0.5f;
                ImVec2 centralizedCursorPos = {res.x,res.y};
                centralizedCursorPos = ImClamp(centralizedCursorPos, initialCursorPos, centralizedCursorPos);
                ImGui::SetCursorPos(centralizedCursorPos);
            }

            //unsigned int* id = new unsigned int(tex);
            //(ImTextureID)static_cast<void*>(&tex)
            //DrawImage((ImTextureID)static_cast<void*>(&tex), ImVec2(img_size.x, img_size.y), ImVec2(0, 1), ImVec2(1, 0), { 1,1,1,1 }, { 0,0,0,0 }, true); // interesting bug
            DrawImage(reinterpret_cast<void*>(tex), ImVec2(img_size.x, img_size.y), ImVec2(0, 1), ImVec2(1, 0), { 1,1,1,1 }, { 0,0,0,0 }, true);
        }
    };
}

#endif //GAMEENGINE_GUIWINDOW_H
