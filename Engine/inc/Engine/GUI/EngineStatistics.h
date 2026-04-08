//
// Created by Monika on 26.03.2022.
//

#ifndef SR_ENGINE_ENGINESTATISTICS_H
#define SR_ENGINE_ENGINESTATISTICS_H

#include <Graphics/GUI/Widget.h>

namespace SR_GRAPH_NS {
    class IRenderTechnique;
    class MeshDrawerPass;
    class RenderQueue;
}

namespace EvoVulkan {
    struct SubmitInfo;
}

namespace SR_CORE_NS::GUI {
    class EngineStatistics : public SR_GRAPH_GUI_NS::Widget {
    public:
        EngineStatistics();
        ~EngineStatistics() override = default;

    protected:
        void Draw() override;

    private:
        void CommonPage();
        void ResourcesPage();
        void ThreadsPage();
        void WidgetsPage();
        void VideoMemoryPage();
        void SubmitQueuePage();
        void RenderStrategyPage();
        void StringAtoms();

        void DrawSubmitInfo(const EvoVulkan::SubmitInfo& submitInfo);
        void DrawRenderTechnique(SR_GRAPH_NS::IRenderTechnique* pRenderTechnique);
        void DrawMeshDrawerPass(SR_GRAPH_NS::MeshDrawerPass* pMeshDrawerPass);
        void DrawRenderQueue(const SR_GRAPH_NS::RenderQueue* pRenderQueue);

    private:
        std::string m_stringCache;
        bool m_showShaderMacros = false;
        bool m_showShaderPrograms = false;
        bool m_showUnusedShaders = false;

    };
}

#endif //SR_ENGINE_ENGINESTATISTICS_H
