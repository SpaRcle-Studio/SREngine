//
// Created by Monika on 29.11.2021.
//

#ifndef GAMEENGINE_VISUALREGION_H
#define GAMEENGINE_VISUALREGION_H

#include <Utils/World/Region.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector2.h>

namespace Framework::Graphics::Types {
    class DebugWireframeMesh;
}

namespace Framework::Helper::World {
    class Region;
}

namespace Framework::Core::World {
    class VisualRegion : public Helper::World::Region {
    public:
        explicit VisualRegion(SRRegionAllocArgs) : Helper::World::Region(SRRegionAllocVArgs) { }
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
