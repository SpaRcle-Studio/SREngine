//
// Created by Monika on 27.12.2021.
//

#ifndef SRENGINE_FILEBROWSER_H
#define SRENGINE_FILEBROWSER_H

#include <FileSystem/Path.h>
#include <string>

namespace Framework::Core::GUI {
    class FileBrowser {
        using Hash = std::size_t;
    public:
        FileBrowser();
        FileBrowser(const FileBrowser &copyFrom) = delete;
        FileBrowser &operator=(const FileBrowser &copyFrom) = delete;

    public:
        void SetFolder(const Helper::Path& path);
        void Draw();

    private:
        void Draw(const Helper::Path& root);

    private:
        Helper::Path m_root;
        Helper::Path m_selectedDir;

    };
}

#endif //SRENGINE_FILEBROWSER_H
