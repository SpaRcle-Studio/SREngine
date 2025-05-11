

# File VisualRegion.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**World**](dir_748c98af40e9646c77253b96f05954cd.md) **>** [**VisualRegion.h**](VisualRegion_8h.md)

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


