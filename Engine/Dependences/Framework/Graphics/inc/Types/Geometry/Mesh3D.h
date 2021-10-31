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

namespace Framework::Graphics::Types {
    class Mesh3D : public IndexedMesh {
    public:
        explicit Mesh3D(const std::string& name = "UnnamedMesh3D")
            : IndexedMesh(name) { };
    protected:
        ~Mesh3D() override = default;
    private:
        Vertices::Mesh3DVertices m_vertices = Vertices::Mesh3DVertices();
    public:
        void DrawVulkan() override;
        void DrawOpenGL() override;

        Mesh* Copy(Mesh* mesh) const override;

        void SetVertexArray(const std::any& vertices) override;

        bool Calculate() override;

        bool FreeVideoMemory() override;
    };
}

#endif //GAMEENGINE_MESH3D_H
