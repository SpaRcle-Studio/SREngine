

# File FileBrowser.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**FileBrowser.h**](FileBrowser_8h.md)

[Go to the documentation of this file](FileBrowser_8h.md)


```C++
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
        using CallbackFn = std::function<void(const SR_UTILS_NS::Path& path)>;
    public:
        FileBrowser();
        ~FileBrowser() override = default;

    public:
        void SetFolder(const SR_UTILS_NS::Path& path);
        void SetCallback(CallbackFn callbackFn) { m_callbackFunction = std::move(callbackFn); }

    private:
        void Draw() override;

    private:
        void FileContextMenu(const std::string &element);
        void CurrentDirectoryContextMenu();
        void CurrentDirectoryPanel(const float_t height);
        void ItemViewPanel();
        void FileCatalogPanel(const float_t& leftWidth);
        void CacheElements(const SR_UTILS_NS::Path& root); // Загружает элементы CurrentDirectoryPanel в кэш

    private:
        void DrawFoldersTree(const FBFolder& parentFolder); // Отрисовка созданного дерева
        void LoadFoldersTree(FBFolder& parentFolder); // Создание дерева файлов и его кеширования

    private:
        SR_UTILS_NS::Path m_defaultRoot;
        SR_UTILS_NS::Path m_selectedDir;

        CallbackFn m_callbackFunction;

        float_t m_assetWidth;

        FBFolder m_foldersTree;

        std::atomic<bool> m_dirtySelectedDir;
        std::atomic<bool> m_dirtyFoldersTree;

        std::list<FBElement> m_elements;
    };
}

#endif //SR_ENGINE_FILEBROWSER_H
```


