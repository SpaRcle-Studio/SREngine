//
// Created by Monika on 27.12.2021.
//

#ifndef SR_ENGINE_FILEBROWSER_H
#define SR_ENGINE_FILEBROWSER_H

#include <Utils/FileSystem/Path.h>

#include <Graphics/GUI/Widget.h>

namespace SR_CORE_NS::GUI {
    struct FBElement {
        std::string filename;
        std::string cutName;
        EditorIcon iconType;
        bool isDir;
    };

    struct FBFolder {
        SR_UTILS_NS::Path path;
        std::string filename;
        std::list<FBFolder> innerFolders;
    };

    class FileBrowser : public SR_GRAPH_GUI_NS::Widget {
        using Hash = std::size_t;
        using Super = SR_GRAPH_GUI_NS::Widget;
        using CallbackFn = std::function<void(const SR_UTILS_NS::Path& path)>;
    public:
        FileBrowser();
        ~FileBrowser() override;

    public:
        void SetFolder(const SR_UTILS_NS::Path& path);
        void SetCallback(CallbackFn callbackFn) { m_callbackFunction = std::move(callbackFn); }

    private:
        void Draw() override;

    private:
        void OnClose() override;
        void FileContextMenu(const std::string &element);
        void CurrentDirectoryContextMenu();
        void CurrentDirectoryPanel();
        void ItemViewPanel();
        void FileCatalogPanel(const float_t& leftWidth);
        void CacheElements(const SR_UTILS_NS::Path& root); // Загружает элементы CurrentDirectoryPanel в кэш
        void OpenFileWithApp(const SR_UTILS_NS::Path& path);

    private:
        void DrawFoldersTree(const FBFolder& parentFolder); // Отрисовка созданного дерева
        void LoadFoldersTree(FBFolder& parentFolder); // Создание дерева файлов и его кеширования
        void FreeTextures();

    private:
        float_t m_itemsScale = 1.0f;

        SR_UTILS_NS::Path m_defaultRoot;
        SR_UTILS_NS::Path m_selectedDir;

        CallbackFn m_callbackFunction;

        float_t m_assetWidth = 0.0f;

        FBFolder m_foldersTree;

        std::map<std::string, SR_GTYPES_NS::Texture::Ptr> m_currentDirTextures;

        std::atomic<bool> m_dirtySelectedDir;
        std::atomic<bool> m_dirtyFoldersTree;

        std::list<FBElement> m_elements;
    };
}

#endif //SR_ENGINE_FILEBROWSER_H
