//
// Created by Monika on 27.12.2021.
//

#include <Core/GUI/FileBrowser.h>

#include <Utils/FileSystem/Path.h>
#include <Utils/Common/VectorUtils.h>
#include <Utils/Debug.h>
#include <Utils/Resources/ResourceManager.h>

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
        if(SR_GRAPH_GUI_NS::Immediate::BeginPopupContextWindow()){
            if (SR_GRAPH_GUI_NS::Immediate::Selectable("Paste")) {
                SR_UTILS_NS::Platform::PasteFilesFromClipboard(m_selectedDir);
                m_dirtySelectedDir = true;
            }
            if (SR_GRAPH_GUI_NS::Immediate::Selectable("Open in native Explorer")) {
                SR_UTILS_NS::Platform::OpenWithAssociatedApp(m_selectedDir);
            }
            if (SR_GRAPH_GUI_NS::Immediate::Selectable("Refresh")) {
                m_dirtySelectedDir = true;
            }
            SR_GRAPH_GUI_NS::Immediate::EndPopup();
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
        const auto WITH_CHILD = SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::OpenOnArrow | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::OpenOnDoubleClick;
        const auto SELECTED_WITH_CHILD = SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::OpenOnArrow | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::OpenOnDoubleClick | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::Selected;
        const auto WITHOUT_CHILD = SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::NoTreePushOnOpen | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::Leaf;
        const auto SELECTED_WITHOUT_CHILD = SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::NoTreePushOnOpen | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::Leaf | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::Selected;

        unsigned short index = 0;
        for (const auto &folder : parentFolder.innerFolders) {
            const bool selected = m_selectedDir.GetHash() == folder.path.GetHash();

            if (folder.innerFolders.empty()) {
                SR_GRAPH_GUI_NS::Immediate::TreeNodeEx((void *) (intptr_t) index, selected ? SELECTED_WITHOUT_CHILD : WITHOUT_CHILD, "%s",
                                  folder.filename.c_str());

                if (SR_GRAPH_GUI_NS::Immediate::IsItemClicked()) {
                    m_selectedDir = folder.path;
                    m_dirtySelectedDir = true;
                    m_dirtyFoldersTree = true;
                }
            } else {
                bool open = SR_GRAPH_GUI_NS::Immediate::TreeNodeEx((void *) (intptr_t) index, selected ? SELECTED_WITH_CHILD : WITH_CHILD,
                                              "%s",
                                              folder.filename.c_str());

                if (SR_GRAPH_GUI_NS::Immediate::IsItemClicked() && !SR_GRAPH_GUI_NS::Immediate::IsItemToggledOpen()) {
                    m_selectedDir = folder.path;
                    m_dirtySelectedDir = true;
                    m_dirtyFoldersTree = true;
                }

                if (open) {
                    DrawFoldersTree(folder);
                    SR_GRAPH_GUI_NS::Immediate::TreePop();
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
        if (!SR_GRAPH_GUI_NS::Immediate::BeginPopupContextItem()) {
            return;
        }

        if (SR_GRAPH_GUI_NS::Immediate::Selectable("Open")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);

            if (m_callbackFunction) {
                m_callbackFunction(path);
                m_callbackFunction = CallbackFn();
            }
            else {
                SR_UTILS_NS::Platform::OpenWithAssociatedApp(path);
            }
        }
        if (SR_GRAPH_GUI_NS::Immediate::Selectable("Extract animations")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            //auto&& animations = SR_ANIMATIONS_NS::AnimationClip::Load(path);
            //for (auto&& pAnimation : animations) {
            //   // pAnimation->Save()
            //}
        }
        if (SR_GRAPH_GUI_NS::Immediate::Selectable("Copy")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            std::list<SR_UTILS_NS::Path> paths({path}); ///TODO: убрать, когда будет сделано выделение нескольких файлов и их передача в метод
            SR_UTILS_NS::Platform::CopyFilesToClipboard(paths);
        }
        if (SR_GRAPH_GUI_NS::Immediate::Selectable("Cut")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            ///SR_UTILS_NS::Platform::CopyFilesToClipboard(paths);
            ///for (auto &&path:paths) {
            /// SR_UTILS_NS::Platform::Delete(path);
            ///}
            m_dirtySelectedDir = true;
        }
        if (SR_GRAPH_GUI_NS::Immediate::Selectable("Paste")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            SR_UTILS_NS::Platform::PasteFilesFromClipboard(path);
            m_dirtySelectedDir = true;
        }
        if (SR_GRAPH_GUI_NS::Immediate::Selectable("Delete")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            ///метод Delete является слишком опасным, поскольку проводит удаление рекурсивно и безвозвратно
            ///TODO:раскомментировать SR_UTILS_NS::Platform::Delete, если обезопасили от безвозвратного удаления файлов
            ///SR_UTILS_NS::Platform::Delete(path);
            m_dirtySelectedDir = true;
        }

        SR_GRAPH_GUI_NS::Immediate::EndPopup();
    }

    void FileBrowser::CurrentDirectoryPanel(const float_t height) { //height используется и как ширина Refresh Button
        if (SR_GRAPH_GUI_NS::Immediate::BeginChild("current directory panel", SR_MATH_NS::FVector2(0.f, height)))
        {
            SR_GRAPH_GUI_NS::Immediate::Separator();
            /// Back Button
            if (SR_GRAPH_GUI_NS::Immediate::Button("Back")) {
                m_selectedDir = m_selectedDir.GetPrevious();
                m_dirtySelectedDir = true;
            }
            /// Current Directory Text
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_GRAPH_GUI_NS::Immediate::Text("%s", m_selectedDir.CStr());
            /// Refresh Button
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_GRAPH_GUI_NS::Immediate::SetCursorPosX(SR_GRAPH_GUI_NS::Immediate::GetCursorPos().x + SR_GRAPH_GUI_NS::Immediate::GetContentRegionAvail().x - height);

            if (SR_GRAPH_GUI_NS::Immediate::ImageButton(dynamic_cast<EditorGUI *>(GetManager())->GetIconDescriptor(Core::EditorIcon::Reset), height-10.f)){
                m_dirtySelectedDir = true;
                m_dirtyFoldersTree = true;
            }

            SR_GRAPH_GUI_NS::Immediate::EndChild();
        }
    }

    void FileBrowser::ItemViewPanel() {
        if (SR_GRAPH_GUI_NS::Immediate::BeginChild("item view", SR_MATH_NS::FVector2(0, -SR_GRAPH_GUI_NS::Immediate::GetFrameHeightWithSpacing())))
        {
            SR_GRAPH_GUI_NS::Immediate::Separator();

            CurrentDirectoryContextMenu();

            auto wndSize = SR_GRAPH_GUI_NS::Immediate::GetWindowSize();

            uint32_t index = 1;

            for (const auto &element : m_elements) {
                ++index;

                SR_GRAPH_GUI_NS::Immediate::BeginGroup();

                const std::string headerid = "##FileBrowserElement%s" + element.filename;
                if (element.isDir) {
                    void* descriptor = dynamic_cast<EditorGUI *>(GetManager())->GetIconDescriptor(element.iconType);

                    if (SR_GRAPH_GUI_NS::Immediate::ImageButtonDouble(headerid, descriptor, SR_MATH_NS::FVector2(50), 0)) {
                        m_selectedDir = m_selectedDir.Concat(element.filename);
                        m_dirtySelectedDir = true;
                    }

                    FileContextMenu(element.filename);
                }
                else
                {
                    void* descriptor = dynamic_cast<EditorGUI *>(GetManager())->GetIconDescriptor(element.iconType);

                    if (SR_GRAPH_GUI_NS::Immediate::ImageButtonDouble(headerid, descriptor, SR_MATH_NS::FVector2(50), 0)) {
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

                SR_GRAPH_GUI_NS::Immediate::Text("%s", element.cutName.c_str());

                SR_GRAPH_GUI_NS::Immediate::EndGroup();

                if ((SR_GRAPH_GUI_NS::Immediate::GetItemRectSize().x * index) + m_assetWidth < wndSize.x) {
                    SR_GRAPH_GUI_NS::Immediate::SameLine();
                }
                else
                    index = 1;

                //ImGui::PopStyleVar();
            }

            CheckHovered();
            CheckFocused();

            SR_GRAPH_GUI_NS::Immediate::EndChild();
        }
    }

    void FileBrowser::FileCatalogPanel(const float_t& leftWidth) {
        if (SR_GRAPH_GUI_NS::Immediate::BeginChild("left panel", SR_MATH_NS::FVector2(leftWidth, 0), true))
        {
            SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::IndentSpacing, SR_GRAPH_GUI_NS::Immediate::GetFontSize());

            DrawFoldersTree(m_foldersTree);

            m_assetWidth = SR_GRAPH_GUI_NS::Immediate::GetItemRectSize().x;

            SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

            CheckHovered();
            CheckFocused();

            SR_GRAPH_GUI_NS::Immediate::EndChild();
        }
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

        float_t windowWidth = SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x;          //код для исключения ошибок ImGui
        if (leftWidth > windowWidth - 40)                       //проверяет ширину панели каталога файлов
            return;                                             //для прекращения отрисовки

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        // right

        SR_GRAPH_GUI_NS::Immediate::BeginGroup();

        CurrentDirectoryPanel(22); //Отрисовка панели нынешней директории

        auto&& DirectoryPanelHeight = SR_GRAPH_GUI_NS::Immediate::GetWindowSize().y; //код для исключения ошибок ImGui
        if (DirectoryPanelHeight < 50) {                        //проверяет высоту панели нынешней директории
            SR_GRAPH_GUI_NS::Immediate::EndGroup();                                  //для прекращения отрисовки
            return;
        }

        if (m_dirtySelectedDir) {
            CacheElements(m_selectedDir);
            m_dirtySelectedDir = false;
        }
        ItemViewPanel(); //Отрисовка панели файлового древа

        SR_GRAPH_GUI_NS::Immediate::EndGroup();
    }
}