//
// Created by Monika on 29.11.2021.
//

#ifndef GAMEENGINE_VISUALREGION_H
#define GAMEENGINE_VISUALREGION_H

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
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderScene>;
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

#endif //GAMEENGINE_VISUALREGION_H
