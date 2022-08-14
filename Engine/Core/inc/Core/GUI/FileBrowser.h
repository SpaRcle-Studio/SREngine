//
// Created by Monika on 27.12.2021.
//

#ifndef SRENGINE_FILEBROWSER_H
#define SRENGINE_FILEBROWSER_H

#include <Utils/FileSystem/Path.h>
#include <GUI/Widget.h>

namespace SR_CORE_NS::GUI {
    class FileBrowser : public SR_GRAPH_NS::GUI::Widget {
        using Hash = std::size_t;
    public:
        FileBrowser();
        ~FileBrowser() override = default;

    public:
        void SetFolder(const SR_UTILS_NS::Path& path);

    private:
        void FileContextMenu(const std::string &element);
        void CurrentDirectoryContextMenu();
        void CurrentDirectoryPanel();
        void ItemViewPanel();
        void FileCatalogPanel(const float_t& leftWidth);
        void Draw() override;
        void Draw(const SR_UTILS_NS::Path& root);
        void LoadElements(const SR_UTILS_NS::Path& root); //Загружает элементы CurrentDirectoryPanel в кэш
         //Загружает дерево файлов в кэш


    private:
        SR_UTILS_NS::Path m_defaultRoot;
        SR_UTILS_NS::Path m_selectedDir;
        float_t m_assetWidth;
        struct Element {
            std::string filename;
            EditorIcon icontype; //TODO Editor Icon
            bool isDir;
        };
        std::list<Element> m_elements;
        std::atomic<bool> m_dirtySelectedDir;
        std::atomic<bool> m_dirtyFoldersTree;
        struct Folder {
            SR_UTILS_NS::Path path;
            std::string filename;
            std::list<Folder> innerfolders;
        };
        void DrawFoldersTree(const Folder& parentFolder); //отрисовка созданного дерева
        void LoadFoldersTree(Folder& parentFolder); //создание дерева файлов и его кеширования
        Folder m_foldersTree;
    };
}

#endif //SRENGINE_FILEBROWSER_H
