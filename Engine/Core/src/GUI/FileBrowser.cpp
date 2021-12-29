//
// Created by Monika on 27.12.2021.
//

#include <GUI/FileBrowser.h>
#include <GUI/GUISystem.h>
#include <FileSystem/Path.h>
#include <Utils/VectorUtils.h>

#include <Debug.h>
#include <vector>
#include <GUI/Icons.h>
#include <ResourceManager/ResourceManager.h>

void Framework::Core::GUI::FileBrowser::SetFolder(const Helper::Path &path) {
    SRAssert((m_root = path).IsDir())
}

void Framework::Core::GUI::FileBrowser::Draw(const Framework::Helper::Path &root) {
    const ImGuiTreeNodeFlags WITH_CHILD = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    const ImGuiTreeNodeFlags SELECTED_WITH_CHILD = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Selected;
    const ImGuiTreeNodeFlags WITHOUT_CHILD = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;
    const ImGuiTreeNodeFlags SELECTED_WITHOUT_CHILD = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Selected;

    const auto& folders = root.GetFolders();

    Helper::Utils::ForEach<const Helper::Path&>([this](auto path, auto index) -> bool {
        const bool selected = m_selected == path.GetHash();

        if (path.GetFolders().empty()) {
            ImGui::TreeNodeEx((void *)(intptr_t)index, selected ? SELECTED_WITHOUT_CHILD : WITHOUT_CHILD, "%s", path.GetBaseName().c_str());

            if (ImGui::IsItemClicked())
                m_selected = path.GetHash();
        }
        else {
            bool open = ImGui::TreeNodeEx((void *)(intptr_t)index, selected ? SELECTED_WITH_CHILD : WITH_CHILD, "%s", path.GetBaseName().c_str());

            if (ImGui::IsItemClicked())
                m_selected = path.GetHash();

            if (open) {
                Draw(path);
                ImGui::TreePop();
            }
        }

        return true;
    }, folders);
}

void Framework::Core::GUI::FileBrowser::Draw() {
    // left

    ImGui::BeginChild("left pane", ImVec2(250, 0), true);

    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize());

    Draw(m_root);

    float assetWidth = ImGui::GetItemRectSize().x;

    ImGui::PopStyleVar();

    ImGui::EndChild();
    ImGui::SameLine();

    /////////////////////// right
    ImGui::BeginGroup();
    ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
    ImGui::Separator();

    auto wndSize = ImGui::GetWindowSize();

    uint32_t index = 1;
    for (const auto& file : SR_ICONS) {
        ++index;

        ImGui::PushFont(Graphics::Environment::Get()->GetIconFont());
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

        ImGui::Button(file, ImVec2(50, 50));

        if ((ImGui::GetItemRectSize().x * index) + assetWidth < wndSize.x)
            ImGui::SameLine();
        else
            index = 1;

        ImGui::PopStyleVar();
        ImGui::PopFont();
    }

    ImGui::EndChild();
    ImGui::BeginChild("buttons");
    if (ImGui::Button("Revert")) {}
    ImGui::SameLine();
    if (ImGui::Button("Save")) {}
    ImGui::EndChild();
    ImGui::EndGroup();
}

Framework::Core::GUI::FileBrowser::FileBrowser()
    : m_selected(SIZE_MAX)
{ }
