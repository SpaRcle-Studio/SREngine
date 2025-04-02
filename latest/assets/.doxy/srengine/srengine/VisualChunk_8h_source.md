

# File VisualChunk.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**World**](dir_61ddcda44ab5988dd2bd052e2f237885.md) **>** [**VisualChunk.h**](VisualChunk_8h.md)

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


