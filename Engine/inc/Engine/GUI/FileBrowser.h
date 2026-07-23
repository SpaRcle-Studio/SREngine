//
// Created by Monika on 27.12.2021.
//

#ifndef SR_ENGINE_FILEBROWSER_H
#define SR_ENGINE_FILEBROWSER_H

#include <Engine/stdInclude.h>

#include <Graphics/GUI/Widget.h>

#include <Utils/FileSystem/Path.h>

namespace SR_CORE_NS::GUI {
    struct FBElement {
        SR_GTYPES_NS::Texture::Ptr pTexture;
        std::string filename;
        std::string cutName;
        EditorIcon iconType;
        bool isDir;
    };

    struct FBFolder {
        SR_UTILS_NS::Path path;
        std::string filename;
        std::list<FBFolder> innerFolders;
        bool childrenLoaded = false; ///< true = direct children already loaded (lazy tree)
        bool hasSubfolders = true; ///< false = no subfolders (show as leaf, no expand arrow)
    };

    class FileBrowser : public SR_GRAPH_GUI_NS::Widget {
        SR_CLASS()
        using Hash = std::size_t;
        using Super = SR_GRAPH_GUI_NS::Widget;
        using CallbackFn = SR_HTYPES_NS::Function<void(const SR_UTILS_NS::Path& path)>;
    public:
        FileBrowser();
        ~FileBrowser() override;

    public:
        void SetFolder(const SR_UTILS_NS::Path& path);
        void SetCallback(CallbackFn callbackFn) { m_callbackFunction = std::move(callbackFn); }

    private:
        void Draw() override;

    private:
        void OnOpen() override;
        void OnClose() override;
        void FileContextMenu(const std::string& element);
        void CurrentDirectoryContextMenu();
        void CurrentDirectoryPanel();
        void ItemViewPanel();
        void FileCatalogPanel(const float_t& leftWidth);
        void CacheElements(const SR_UTILS_NS::Path& root); // Загружает элементы CurrentDirectoryPanel в кэш
        void OpenFileWithApp(const SR_UTILS_NS::Path& path);

    private:
        void DrawFoldersTree(FBFolder& parentFolder); // Отрисовка созданного дерева (может подгружать детей по требованию)
        void LoadFolderChildren(FBFolder& parentFolder); // Загрузка только прямых дочерних папок (один уровень)
        void FreeTextures();

    private:
        float_t m_itemsScale = 1.0f;

        SR_UTILS_NS::Vector<SR_UTILS_NS::Path> m_currentDirElements;
        SR_UTILS_NS::Vector<SR_UTILS_NS::Path> m_tmp;
        SR_UTILS_NS::Path m_defaultRoot;
        SR_UTILS_NS::Path m_selectedDir;

        CallbackFn m_callbackFunction;

        float_t m_assetWidth = 0.0f;

        FBFolder m_foldersTree;

        std::atomic<bool> m_dirtySelectedDir;
        std::atomic<bool> m_dirtyFoldersTree;

        std::list<FBElement> m_elements;

        std::vector<SR_UTILS_NS::StringAtom> m_availableAssets;
        std::vector<char> m_comboBoxBuffer;
        int32_t m_newAssetIndex = -1;
        SR_UTILS_NS::Path m_newAssetPath;
        std::string m_newAssetName;

    };
}

#endif //SR_ENGINE_FILEBROWSER_H
