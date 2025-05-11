

# File EngineStatistics.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**EngineStatistics.h**](EngineStatistics_8h.md)

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


