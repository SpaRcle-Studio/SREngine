//
// Created by Monika on 27.12.2021.
//

#ifndef SRENGINE_FILEBROWSER_H
#define SRENGINE_FILEBROWSER_H

#include <FileSystem/Path.h>
#include <GUI/Widget.h>
#include <string>
#include <macros.h>

namespace SR_GRAPH_NS::GUI {
    class FileBrowser : public Widget {
        using Hash = std::size_t;
    public:
        FileBrowser();
        ~FileBrowser() override = default;

    public:
        void SetFolder(const Helper::Path& path);

    private:
        void Draw() override;
        void Draw(const Helper::Path& root);

    private:
        Helper::Path m_root;
        Helper::Path m_selectedDir;

    };
}

#endif //SRENGINE_FILEBROWSER_H
