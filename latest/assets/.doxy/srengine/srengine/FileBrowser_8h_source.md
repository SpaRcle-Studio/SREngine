

# File FileBrowser.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**FileBrowser.h**](FileBrowser_8h.md)

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


