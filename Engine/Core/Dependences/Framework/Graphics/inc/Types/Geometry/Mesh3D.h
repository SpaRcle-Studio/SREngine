//
// Created by Nikita on 01.06.2021.
//

#ifndef GAMEENGINE_MESH3D_H
#define GAMEENGINE_MESH3D_H

#include <Types/Geometry/IndexedMesh.h>
#include <Types/Geometry/VertexMesh.h>
#include <Types/Vertices.h>

#include <utility>
#include <Types/Uniforms.h>

namespace Framework::Graphics::Memory {
    class MeshAllocator;
}

namespace Framework::Graphics::Types {
    class Mesh3D : public IndexedMesh {
        friend class Memory::MeshAllocator;
    private:
        explicit Mesh3D(const std::string& name = "UnnamedMesh3D")
            : IndexedMesh(name) { };
    protected:
        ~Mesh3D() override = default;

    public:
        typedef Vertices::Mesh3DVertex VertexType;

    private:
        std::vector<VertexType> m_vertices = std::vector<VertexType>();

    protected:
        void UpdateUBO() override;

    public:
        void DrawVulkan() override;
        void DrawOpenGL() override;

        IResource* Copy(IResource* destination) const override;

        void SetVertexArray(const std::any& vertices) override;

        bool Calculate() override;

        bool FreeVideoMemory() override;
    };
}

#endif //GAMEENGINE_MESH3D_H
