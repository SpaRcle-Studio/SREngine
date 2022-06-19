//
// Created by Monika on 27.12.2021.
//

#include "Core/GUI/FileBrowser.h"

#include <Utils/FileSystem/Path.h>
#include <Utils/Common/VectorUtils.h>
#include <Utils/Debug.h>
#include <Utils/ResourceManager/ResourceManager.h>

#include <GUI/Icons.h>

namespace SR_GRAPH_NS::GUI {
    FileBrowser::FileBrowser()
        : Widget("Assets")
    { }

    void FileBrowser::SetFolder(const SR_UTILS_NS::Path &path) {
        SRAssert((m_root = path).IsDir());
        m_selectedDir = m_root;
    }

    void FileBrowser::Draw(const SR_UTILS_NS::Path &root) {
        const ImGuiTreeNodeFlags WITH_CHILD = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        const ImGuiTreeNodeFlags SELECTED_WITH_CHILD = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Selected;
        const ImGuiTreeNodeFlags WITHOUT_CHILD = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;
        const ImGuiTreeNodeFlags SELECTED_WITHOUT_CHILD = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Selected;

        const auto& folders = root.GetFolders();

        SR_UTILS_NS::ForEach<const Helper::Path&>([=, this](auto path, auto index) -> bool {
            const bool selected = m_selectedDir.GetHash() == path.GetHash();

            if (path.GetFolders().empty()) {
                ImGui::TreeNodeEx((void *)(intptr_t)index, selected ? SELECTED_WITHOUT_CHILD : WITHOUT_CHILD, "%s", path.GetBaseName().c_str());

                if (ImGui::IsItemClicked())
                    m_selectedDir = path;
            }
            else {
                bool open = ImGui::TreeNodeEx((void *)(intptr_t)index, selected ? SELECTED_WITH_CHILD : WITH_CHILD, "%s", path.GetBaseName().c_str());

                if (ImGui::IsItemClicked())
                    m_selectedDir = path;

                if (open) {
                    Draw(path);
                    ImGui::TreePop();
                }
            }

            return true;
        }, folders);
    }

    bool ThumbNail(ImTextureID user_texture_id, std::string label, bool double_click, const ImVec2& size, const ImVec2& uv0 = ImVec2(0.0f, 0.0f), const ImVec2& uv1 = ImVec2(1.0f, 1.0f), int frame_padding = 1, const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(0, 0, 0, 0))
    {
        ImGuiButtonFlags button_flags = 0;
        if(double_click)
            button_flags |= ImGuiButtonFlags_PressedOnClickRelease | ImGuiButtonFlags_PressedOnDoubleClick;

        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;

        // Default to using texture ID as ID. User can still push string/integer prefixes.
        // We could hash the size/uv to create a unique ID but that would prevent the user from animating UV.
        //PushID((void*)(intptr_t)user_texture_id);
        const ImGuiID id = window->GetID(label.c_str());
        const ImVec2 label_size = ImGui::CalcTextSize(label.c_str(), NULL, true);

        //PopID();

        // add 3 font size to y for button rectangle height;
        ImVec2 button_size = size;
        button_size.y += label_size.y * 2;

        const ImVec2 padding = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;
        const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + button_size + padding * 2);
        const ImRect image_bb(window->DC.CursorPos + padding, window->DC.CursorPos + padding + size);
        ImGui::ItemSize(bb);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, button_flags);

        // Render
        const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
        ImGui::RenderNavHighlight(bb, id);
        ImGui::RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
        if (bg_col.w > 0.0f)
            window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, ImGui::GetColorU32(bg_col));
        window->DrawList->AddImage(user_texture_id, image_bb.Min, image_bb.Max, uv0, uv1, ImGui::GetColorU32(tint_col));

        // offset the thumbnail max y + padding.y
        ImRect offset = bb;
        offset.Min.y = image_bb.Max.y + padding.y;
        // render the text
        ImGui::RenderTextClipped(offset.Min + style.FramePadding, offset.Max - style.FramePadding, label.c_str(), NULL, &label_size, style.ButtonTextAlign, &offset);

        //std::stringstream input_text_label;
        //input_text_label.str(std::string());
        //input_text_label << "##" << label;

        //ImGuiInputTextFlags text_flag = ImGuiInputTextFlags_None;
        //ImGui::InputText(input_text_label.str().c_str(), label->data(), 64, text_flag, NULL, NULL);


        return pressed;
    }

    void FileBrowser::Draw() {
        // left

        float_t assetWidth = 0.f;

        const auto&& leftWidth = 250;

        if (ImGui::BeginChild("left pane", ImVec2(leftWidth, 0), true)) {

            ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize());

            Draw(m_root);

            assetWidth = ImGui::GetItemRectSize().x;

            ImGui::PopStyleVar();

            CheckHovered();
            CheckFocused();

            ImGui::EndChild();
        }

        auto&& windowWidth = ImGui::GetWindowWidth();
        if (leftWidth > windowWidth - 20)
            return;

        ImGui::SameLine();

        /////////////////////// right

        auto width = ImGui::GetWindowWidth();

        ImGui::BeginGroup();
        if (ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()))) {
            ImGui::Separator();

            if (ImGui::Button("Back")) {
                m_selectedDir = m_selectedDir.GetPrevious();
            }
            ImGui::SameLine();
            ImGui::Text("%s", m_selectedDir.CStr());

            ImGui::Separator();

            auto wndSize = ImGui::GetWindowSize();

            uint32_t index = 1;
            for (const auto &path : m_selectedDir.GetAll()) {
                if (path.GetBaseName().empty())
                    continue;

                ++index;

                ImGui::PushFont(Graphics::Environment::Get()->GetIconFont());
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

                ImGui::BeginGroup();

                if (path.IsDir()) {
                    if (ImGui::ButtonEx(SR_ICON_FOLDER, ImVec2(50, 50), ImGuiButtonFlags_PressedOnDoubleClick)) {
                        m_selectedDir = path;
                    }
                }
                else {
                    ImGui::Button(SR_ICON_FILE, ImVec2(50, 50));
                }

                ImGui::PopFont();

                ImGui::Text("%s", path.GetBaseName().c_str());

                ImGui::EndGroup();

                if ((ImGui::GetItemRectSize().x * index) + assetWidth < wndSize.x)
                    ImGui::SameLine();
                else
                    index = 1;

                ImGui::PopStyleVar();
            }

            CheckHovered();
            CheckFocused();

            ImGui::EndChild();
        }

        /*ImGui::BeginChild("buttons");
        if (ImGui::Button("Revert")) {}
        ImGui::SameLine();
        if (ImGui::Button("Save")) {}
        ImGui::EndChild();*/

        ImGui::EndGroup();
    }
}