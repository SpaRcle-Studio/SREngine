//
// Created by Monika on 27.12.2021.
//

#include <Core/GUI/FileBrowser.h>

#include <Utils/FileSystem/Path.h>
#include <Utils/Common/VectorUtils.h>
#include <Utils/Debug.h>
#include <Utils/ResourceManager/ResourceManager.h>

#include <Graphics/GUI/Icons.h>
#include <Graphics/Animations/AnimationClip.h>

namespace SR_CORE_NS::GUI {
    FileBrowser::FileBrowser()
        : Widget("Assets")
    { }

    void FileBrowser::SetFolder(const SR_UTILS_NS::Path &path) {
        m_selectedDir = m_defaultRoot = path;
        m_dirtySelectedDir = true;
        m_dirtyFoldersTree = true;

        if (!m_selectedDir.IsDir()) {
            SR_ERROR("FileBrowser::SetFolder() : path is not folder! \n\tPath: " + m_selectedDir.ToString());
        }
    }

    void FileBrowser::CurrentDirectoryContextMenu(){
        if(ImGui::BeginPopupContextWindow()){
            if (ImGui::Selectable("Paste")) {
                SR_UTILS_NS::Platform::PasteFilesFromClipboard(m_selectedDir);
                m_dirtySelectedDir = true;
            }
            if (ImGui::Selectable("Open in native Explorer")) {
                SR_UTILS_NS::Platform::OpenWithAssociatedApp(m_selectedDir);
            }
            if (ImGui::Selectable("Refresh")) {
                m_dirtySelectedDir = true;
            }
            ImGui::EndPopup();
        }
    }

    void FileBrowser::CacheElements(const SR_UTILS_NS::Path& root) {
        m_elements.clear();
        for (const auto &path : root.GetAll()) {
            if (path.GetBaseName().empty()) {
                continue;
            }
            else {
                FBElement current;

                if (path.IsDir()) {
                    current.filename = path.GetBaseName();
                    current.isDir = true;
                } else {
                    current.filename = path.GetBaseNameAndExt();
                    current.isDir = false;
                }

                current.cutName = SR_UTILS_NS::StringUtils::CutName(current.filename, 7);

                auto&& extension = path.GetExtensionView();

                if (extension.empty()) { //TODO Сделать красивым
                    path.IsEmpty() ? current.iconType = Core::EditorIcon::EmptyFolder
                                   : current.iconType = Core::EditorIcon::Folder;
                } else if (extension == "zip") {
                    current.iconType = Core::EditorIcon::ZIP;
                } else if ((extension == "jpg") || (extension == "jpeg")) {
                    current.iconType = Core::EditorIcon::JPG;
                } else if (extension == "txt") {
                    current.iconType = Core::EditorIcon::TXT;
                } else if (extension == "xml") {
                    current.iconType = Core::EditorIcon::XML;
                } else if (extension == "png") {
                    current.iconType = Core::EditorIcon::PNG;
                } else if (extension == "dll") {
                    current.iconType = Core::EditorIcon::DLL;
                } else {
                    current.iconType = Core::EditorIcon::File;
                }
                
                m_elements.emplace_back(current);
            }
        }
        m_dirtySelectedDir = false;
    }

    void FileBrowser::DrawFoldersTree(const FBFolder& parentFolder) {
        const ImGuiTreeNodeFlags WITH_CHILD = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        const ImGuiTreeNodeFlags SELECTED_WITH_CHILD = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Selected;
        const ImGuiTreeNodeFlags WITHOUT_CHILD = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;
        const ImGuiTreeNodeFlags SELECTED_WITHOUT_CHILD = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Selected;

        unsigned short index = 0;
        for (const auto &folder : parentFolder.innerFolders) {
            const bool selected = m_selectedDir.GetHash() == folder.path.GetHash();

            if (folder.innerFolders.empty()) {
                ImGui::TreeNodeEx((void *) (intptr_t) index, selected ? SELECTED_WITHOUT_CHILD : WITHOUT_CHILD, "%s",
                                  folder.filename.c_str());

                if (ImGui::IsItemClicked()) {
                    m_selectedDir = folder.path;
                    m_dirtySelectedDir = true;
                    m_dirtyFoldersTree = true;
                }
            } else {
                bool open = ImGui::TreeNodeEx((void *) (intptr_t) index, selected ? SELECTED_WITH_CHILD : WITH_CHILD,
                                              "%s",
                                              folder.filename.c_str());

                if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
                    m_selectedDir = folder.path;
                    m_dirtySelectedDir = true;
                    m_dirtyFoldersTree = true;
                }

                if (open) {
                    DrawFoldersTree(folder);
                    ImGui::TreePop();
                }
            }
            index++;
        }
    }

    void FileBrowser::LoadFoldersTree(FBFolder& parentFolder) {
        const auto &folders = parentFolder.path.GetFolders();
        for (const auto &path : folders) 
        {
            FBFolder currentfolder;
            currentfolder.path = path;
            currentfolder.filename = path.GetBaseName();
            if (!currentfolder.path.IsEmpty()) {
                LoadFoldersTree(currentfolder);
            }
            parentFolder.innerFolders.emplace_back(currentfolder);
        }
    }

    void FileBrowser::FileContextMenu(const std::string &filename){
        if (!ImGui::BeginPopupContextItem()) {
            return;
        }

        if (ImGui::Selectable("Open")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);

            if (m_callbackFunction) {
                m_callbackFunction(path);
                m_callbackFunction = CallbackFn();
            }
            else {
                SR_UTILS_NS::Platform::OpenWithAssociatedApp(path);
            }
        }
        if (ImGui::Selectable("Extract animations")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            auto&& animations = SR_ANIMATIONS_NS::AnimationClip::Load(path);
            for (auto&& pAnimation : animations) {
               // pAnimation->Save()
            }
        }
        if (ImGui::Selectable("Copy")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            std::list<SR_UTILS_NS::Path> paths({path}); ///TODO: убрать, когда будет сделано выделение нескольких файлов и их передача в метод
            SR_UTILS_NS::Platform::CopyFilesToClipboard(paths);
        }
        if (ImGui::Selectable("Cut")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            ///SR_UTILS_NS::Platform::CopyFilesToClipboard(paths);
            ///for (auto &&path:paths) {
            /// SR_UTILS_NS::Platform::Delete(path);
            ///}
            m_dirtySelectedDir = true;
        }
        if (ImGui::Selectable("Paste")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            SR_UTILS_NS::Platform::PasteFilesFromClipboard(path);
            m_dirtySelectedDir = true;
        }
        if (ImGui::Selectable("Delete")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            ///метод Delete является слишком опасным, поскольку проводит удаление рекурсивно и безвозвратно
            ///TODO:раскомментировать SR_UTILS_NS::Platform::Delete, если обезопасили от безвозвратного удаления файлов
            ///SR_UTILS_NS::Platform::Delete(path);
            m_dirtySelectedDir = true;
        }

        ImGui::EndPopup();
    }

    void FileBrowser::CurrentDirectoryPanel(const float_t height) { //height используется и как ширина Refresh Button
        if (ImGui::BeginChild("current directory panel", ImVec2(0.f, height))) 
        {
            ImGui::Separator();
            /// Back Button
            if (ImGui::Button("Back")) {
                m_selectedDir = m_selectedDir.GetPrevious();
                m_dirtySelectedDir = true;
            }
            /// Current Directory Text
            ImGui::SameLine();
            ImGui::Text("%s", m_selectedDir.CStr());
            /// Refresh Button
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - height);

            if (SR_GRAPH_GUI_NS::ImageButton(dynamic_cast<EditorGUI *>(GetManager())->GetIconDescriptor(Core::EditorIcon::Reset), height-10.f)){
                m_dirtySelectedDir = true;
                m_dirtyFoldersTree = true;
            }

            ImGui::EndChild();
        }
    }

    void FileBrowser::ItemViewPanel() {
        if (ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()))) 
        {
            ImGui::Separator();

            CurrentDirectoryContextMenu();

            auto wndSize = ImGui::GetWindowSize();

            uint32_t index = 1;

            for (const auto &element : m_elements) {
                ++index;

                ImGui::BeginGroup();

                const std::string headerid = "##FileBrowserElement%s" + element.filename;
                if (element.isDir) {
                    void* descriptor = dynamic_cast<EditorGUI *>(GetManager())->GetIconDescriptor(element.iconType);

                    if (SR_GRAPH_GUI_NS::ImageButtonDouble(headerid, descriptor, SR_MATH_NS::IVector2(50), 0)) {
                        m_selectedDir = m_selectedDir.Concat(element.filename);
                        m_dirtySelectedDir = true;
                    }

                    FileContextMenu(element.filename);
                }
                else
                {
                    void* descriptor = dynamic_cast<EditorGUI *>(GetManager())->GetIconDescriptor(element.iconType);

                    if (SR_GRAPH_GUI_NS::ImageButtonDouble(headerid, descriptor, SR_MATH_NS::IVector2(50), 0)) {
                        SR_UTILS_NS::Path path = m_selectedDir.Concat(element.filename);
                        //SR_UTILS_NS::Platform::OpenWithAssociatedApp(m_selectedDir.Concat(element.filename));

                        if (m_callbackFunction) {
                            m_callbackFunction(path);
                            m_callbackFunction = CallbackFn();
                        }
                        else {
                            SR_UTILS_NS::Platform::OpenWithAssociatedApp(path);
                        }
                    }

                    FileContextMenu(element.filename);
                }

                ImGui::Text("%s", element.cutName.c_str());

                ImGui::EndGroup();

                if ((ImGui::GetItemRectSize().x * index) + m_assetWidth < wndSize.x) {
                    ImGui::SameLine();
                }
                else
                    index = 1;

                //ImGui::PopStyleVar();
            }

            CheckHovered();
            CheckFocused();

            ImGui::EndChild();
        }
    }

    void FileBrowser::FileCatalogPanel(const float_t& leftWidth) {
        if (ImGui::BeginChild("left panel", ImVec2(leftWidth, 0), true)) 
        {
            ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize());

            DrawFoldersTree(m_foldersTree);

            m_assetWidth = ImGui::GetItemRectSize().x;

            ImGui::PopStyleVar();

            CheckHovered();
            CheckFocused();

            ImGui::EndChild();
        }
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

        m_assetWidth = 0.f;

        const float_t leftWidth = 250;

        if (m_dirtyFoldersTree) {
            m_foldersTree.innerFolders.clear();
            m_foldersTree.path = m_defaultRoot;
            LoadFoldersTree(m_foldersTree);
            m_dirtyFoldersTree = false;
        }

        FileCatalogPanel(leftWidth); //Отрисовка панели файлового древа

        float_t windowWidth = ImGui::GetWindowWidth();          //код для исключения ошибок ImGui
        if (leftWidth > windowWidth - 40)                       //проверяет ширину панели каталога файлов
            return;                                             //для прекращения отрисовки

        ImGui::SameLine();

        // right

        ImGui::BeginGroup();

        CurrentDirectoryPanel(22); //Отрисовка панели нынешней директории

        auto&& DirectoryPanelHeight = ImGui::GetWindowHeight(); //код для исключения ошибок ImGui
        if (DirectoryPanelHeight < 50) {                        //проверяет высоту панели нынешней директории
            ImGui::EndGroup();                                  //для прекращения отрисовки
            return;
        }

        if (m_dirtySelectedDir) {
            CacheElements(m_selectedDir);
            m_dirtySelectedDir = false;
        }
        ItemViewPanel(); //Отрисовка панели файлового древа

        ImGui::EndGroup();
    }
}