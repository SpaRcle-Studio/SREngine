//
// Created by Monika on 16.11.2021.
//

#ifndef GAMEENGINE_VISUALCHUNK_H
#define GAMEENGINE_VISUALCHUNK_H

#include <World/Chunk.h>
#include <Math/Vector3.h>

namespace Framework::Graphics::Types {
    class DebugWireframeMesh;
}

namespace SR_WORLD_NS {
    class Region;
}

namespace Framework::Core::World {
    class VisualChunk : public SR_WORLD_NS::Chunk {
    public:
        explicit VisualChunk(SRChunkAllocArgs);
        ~VisualChunk() override;

    private:
        std::array<Graphics::Types::DebugWireframeMesh*, 2> m_meshes = { nullptr, nullptr };

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
        bool Load(SR_HTYPES_NS::Marshal&& marshal) override;

        void Update(float_t dt) override;

    };
}

#endif //GAMEENGINE_VISUALCHUNK_H
