

# File VisualChunk.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**World**](dir_748c98af40e9646c77253b96f05954cd.md) **>** [**VisualChunk.h**](VisualChunk_8h.md)

[Go to the documentation of this file](VisualChunk_8h.md)


```C++
//
// Created by Monika on 16.11.2021.
//

#ifndef SR_ENGINE_VISUALCHUNK_H
#define SR_ENGINE_VISUALCHUNK_H

#include <Utils/World/Chunk.h>
#include <Utils/Math/Vector3.h>

namespace SR_GTYPES_NS {
    class DebugWireframeMesh;
}

namespace SR_GRAPH_NS {
    class RenderScene;
}

namespace SR_WORLD_NS {
    class Region;
}

namespace SR_CORE_NS {
    class VisualChunk : public SR_WORLD_NS::Chunk {
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::RenderScene>;
    public:
        explicit VisualChunk(SRChunkAllocArgs);
        ~VisualChunk() override;

    private:
        SR_GTYPES_NS::DebugWireframeMesh* m_loadMesh = nullptr;
        SR_GTYPES_NS::DebugWireframeMesh* m_stayMesh = nullptr;

    private:
        void SetFacesVisible(bool value);
        void SetLoadVisible(bool value);
        void UpdateFacesPos();
        void UpdateLoadPos();

        bool ApplyOffset() override;
        void Reload() override;
        void OnExit() override;
        void OnEnter() override;
        bool Unload() override;

        void Update(float_t dt) override;

    };
}

#endif //SR_ENGINE_VISUALCHUNK_H
```


