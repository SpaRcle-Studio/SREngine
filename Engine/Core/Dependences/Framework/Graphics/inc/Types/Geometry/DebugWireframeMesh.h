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
        friend class Memory::MeshAllocator;
    public:
        typedef Vertices::SimpleVertex VertexType;

    private:
        explicit DebugWireframeMesh(const std::string& name = "Unnamed")
            : IndexedMesh(MeshType::Wireframe, name)
        {
            /// override component
            Component::InitComponent<DebugWireframeMesh>();
        }

    protected:
        ~DebugWireframeMesh() override = default;

    public:
        void DrawVulkan() override;
        void DrawOpenGL() override { }

        IResource* Copy(IResource* destination) const override;

        bool Calculate() override;

        bool FreeVideoMemory() override;

    };
}

#endif //GAMEENGINE_DEBUGWIREFRAMEMESH_H
