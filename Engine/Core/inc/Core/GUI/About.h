//
// Created by Igor on 12/03/2023.
//

#ifndef SRENGINE_ABOUT_H
#define SRENGINE_ABOUT_H

#include <Graphics/GUI/Widget.h>

namespace Framework::Core::GUI {
    class About : public Graphics::GUI::Widget {
    public:
        About();
        ~About() override = default;

    protected:
        void Draw() override;

    private:
        void ResourcesPage();
        void ThreadsPage();

    private:
        const ImGuiTreeNodeFlags m_nodeFlagsWithChild = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        const ImGuiTreeNodeFlags m_nodeFlagsWithoutChild = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;

    };
}

#endif //SRENGINE_ABOUT_H
