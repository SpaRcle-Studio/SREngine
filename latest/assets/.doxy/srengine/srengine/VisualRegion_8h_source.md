

# File VisualRegion.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**World**](dir_61ddcda44ab5988dd2bd052e2f237885.md) **>** [**VisualRegion.h**](VisualRegion_8h.md)

[Go to the documentation of this file](VisualRegion_8h.md)


```C++
//
// Created by Monika on 29.11.2021.
//

#ifndef SR_ENGINE_VISUALREGION_H
#define SR_ENGINE_VISUALREGION_H

#include <Utils/World/Region.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector2.h>

namespace SR_GRAPH_NS {
    class RenderScene;
}

namespace SR_GTYPES_NS {
    class DebugWireframeMesh;
}

namespace SR_WORLD_NS {
    class Region;
}

namespace SR_CORE_NS {
    class VisualRegion : public SR_WORLD_NS::Region {
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::RenderScene>;
    public:
        explicit VisualRegion(SRRegionAllocArgs) : SR_UTILS_NS::World::Region(SRRegionAllocVArgs) { }
        ~VisualRegion() override = default;

    private:
        Graphics::Types::DebugWireframeMesh* m_mesh = nullptr;

    private:
        void SetVisible(bool value);
        void UpdateFacesPos();

        void ApplyOffset() override;
        void OnEnter() override;
        void OnExit() override;
        bool Unload(bool force) override;
        bool Load() override;

    };
}

#endif //SR_ENGINE_VISUALREGION_H
```


