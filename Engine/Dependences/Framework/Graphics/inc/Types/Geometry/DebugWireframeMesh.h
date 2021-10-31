//
// Created by Monika on 05.10.2021.
//

#ifndef GAMEENGINE_DEBUGWIREFRAMEMESH_H
#define GAMEENGINE_DEBUGWIREFRAMEMESH_H

#include <Types/Geometry/Mesh3D.h>
#include <Types/Vertices.h>
#include <Types/Uniforms.h>

namespace Framework::Graphics::Types {
    /*
    class DebugWireframeMesh : public Mesh {
    public:
        DebugWireframeMesh(Shader* shader, Material* material, std::string name = "Unnamed") : Mesh(shader, material, std::move(name)) { }
        DebugWireframeMesh() : Mesh(nullptr, nullptr, "Unnamed")  { }
    private:
        std::vector<Vertices::SkyboxVertex> m_vertices = std::vector<Vertices::SkyboxVertex>();
    public:
        void ReCalcModel() override;
    public:
        SR_FORCE_INLINE void DrawVulkan() override {

        }
        SR_FORCE_INLINE void DrawOpenGL() override {

        }

        Mesh* Copy(Mesh* mesh) const override;

        void SetVertexArray(const std::vector<Vertices::SkyboxVertex>& vertices);

        void Free() override {
        #ifndef SR_RELEASE
            if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
                Debug::Log("Mesh3D::Free() : free mesh memory...");
        #endif
            delete this;
        }

        bool Calculate() override;

        bool FreeVideoMemory() override;
    };*/
}

#endif //GAMEENGINE_DEBUGWIREFRAMEMESH_H
