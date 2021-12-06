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

namespace Framework::Helper::World {
    class Region;
}

namespace Framework::Core::World {
    class VisualChunk : public Helper::World::Chunk {
    public:
        explicit VisualChunk(SRChunkAllocArgs);
        ~VisualChunk() override = default;

    private:
        Graphics::Types::DebugWireframeMesh* m_mesh = nullptr;

    private:
        void SetVisible(bool value);

    public:
        void Update(float_t dt) override;
        void OnExit() override;
        void OnEnter() override;
        bool Unload() override;

    };
}

#endif //GAMEENGINE_VISUALCHUNK_H
