//
// Created by Monika on 26.03.2022.
//

#ifndef SRENGINE_ENGINESTATISTICS_H
#define SRENGINE_ENGINESTATISTICS_H

#include <Graphics/GUI/Widget.h>

namespace Framework::Core::GUI {
    class EngineStatistics : public Graphics::GUI::Widget {
    public:
        EngineStatistics();
        ~EngineStatistics() override = default;

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

#endif //SRENGINE_ENGINESTATISTICS_H
