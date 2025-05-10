

# File EngineStatistics.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**EngineStatistics.h**](EngineStatistics_8h.md)

[Go to the documentation of this file](EngineStatistics_8h.md)


```C++
//
// Created by Monika on 26.03.2022.
//

#ifndef SR_ENGINE_ENGINESTATISTICS_H
#define SR_ENGINE_ENGINESTATISTICS_H

#include <Graphics/GUI/Widget.h>

namespace SR_GRAPH_NS {
    class IRenderTechnique;
    class MeshDrawerPass;
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

    };
}

#endif //SR_ENGINE_ENGINESTATISTICS_H
```


