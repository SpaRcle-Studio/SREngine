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

namespace Framework::Graphics::Types {
    class DebugWireframeMesh final : public IndexedMesh {
        friend class Memory::MeshAllocator;
    private:
        explicit DebugWireframeMesh(const std::string& name = "Unnamed")
            : IndexedMesh(MeshType::Wireframe, name)
        { }

    protected:
        ~DebugWireframeMesh() override = default;

    public:
        typedef Vertices::SkyboxVertex VertexType;

    private:
        std::vector<VertexType> m_vertices = std::vector<VertexType>();

    protected:
        void UpdateUBO() override;

    public:
        void DrawVulkan() override;

        void DrawOpenGL() override {

        }

        IResource* Copy(IResource* destination) const override;

        void SetVertexArray(const std::any& vertices) override;

        bool Calculate() override;

        bool FreeVideoMemory() override;
    };
}

#endif //GAMEENGINE_DEBUGWIREFRAMEMESH_H
