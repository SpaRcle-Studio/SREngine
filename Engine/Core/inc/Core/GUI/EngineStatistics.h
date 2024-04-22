//
// Created by Monika on 26.03.2022.
//

#ifndef SR_ENGINE_ENGINESTATISTICS_H
#define SR_ENGINE_ENGINESTATISTICS_H

#include <Graphics/GUI/Widget.h>

#include <EvoVulkan/Tools/SubmitInfo.h>

namespace SR_CORE_NS::GUI {
    class EngineStatistics : public SR_GRAPH_GUI_NS::Widget {
    public:
        EngineStatistics();
        ~EngineStatistics() override = default;

    protected:
        void Draw() override;

    private:
        void ResourcesPage();
        void ThreadsPage();
        void WidgetsPage();
        void VideoMemoryPage();
        void SubmitQueuePage();
        void RenderStrategyPage();

        void DrawSubmitInfo(const EvoVulkan::SubmitInfo& submitInfo);

    private:
        const ImGuiTreeNodeFlags m_nodeFlagsWithChild = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        const ImGuiTreeNodeFlags m_nodeFlagsWithoutChild = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;

    };
}

#endif //SR_ENGINE_ENGINESTATISTICS_H
