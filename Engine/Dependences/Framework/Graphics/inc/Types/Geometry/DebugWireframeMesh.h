//
// Created by Monika on 05.10.2021.
//

#ifndef GAMEENGINE_DEBUGWIREFRAMEMESH_H
#define GAMEENGINE_DEBUGWIREFRAMEMESH_H

#include <Types/Geometry/IndexedMesh.h>
#include <Types/Vertices.h>
#include <Types/Uniforms.h>

namespace Framework::Graphics::Types {
    class DebugWireframeMesh : public IndexedMesh {
    public:
        explicit DebugWireframeMesh(const std::string& name = "Unnamed") : IndexedMesh(name) { }
    protected:
        ~DebugWireframeMesh() override = default;
    private:
        std::vector<Vertices::SkyboxVertex> m_vertices = std::vector<Vertices::SkyboxVertex>();
    public:
        void DrawVulkan() override {

        }

        void DrawOpenGL() override {

        }

        Mesh* Copy(Mesh* mesh) const override;

        void SetVertexArray(const std::any& vertices) override;

        bool Calculate() override;

        bool FreeVideoMemory() override;
    };
}

#endif //GAMEENGINE_DEBUGWIREFRAMEMESH_H
