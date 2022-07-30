//
// Created by Monika on 05.10.2021.
//

#ifndef GAMEENGINE_DEBUGWIREFRAMEMESH_H
#define GAMEENGINE_DEBUGWIREFRAMEMESH_H

#include <Types/Geometry/IndexedMesh.h>
#include <Types/Vertices.h>
#include <Types/Uniforms.h>

namespace Framework::Graphics::Memory {
    class MeshAllocator;
}

namespace SR_GTYPES_NS {
    class DebugWireframeMesh final : public IndexedMesh {
    public:
        typedef Vertices::SimpleVertex VertexType;

    public:
        DebugWireframeMesh();

    private:
        ~DebugWireframeMesh() override = default;

    public:
        void Draw() override;

        IResource* Copy(IResource* destination) const override;

        bool Calculate() override;

        void FreeVideoMemory() override;

    };
}

#endif //GAMEENGINE_DEBUGWIREFRAMEMESH_H
