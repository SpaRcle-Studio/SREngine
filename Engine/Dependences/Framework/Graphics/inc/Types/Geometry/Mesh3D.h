//
// Created by Nikita on 01.06.2021.
//

#ifndef GAMEENGINE_MESH3D_H
#define GAMEENGINE_MESH3D_H

#include <Types/Mesh.h>
#include <Types/Vertices.h>

#include <utility>

namespace Framework::Graphics::Types {
    class Mesh3D : public Mesh {
    public:
        Mesh3D(Shader* shader, Material* material, std::string name = "Unnamed") : Mesh(shader, material, std::move(name)) {

        }
        Mesh3D() : Mesh(nullptr, nullptr, "Unnamed")  {

        }
    private:
        std::vector<Vertices::Mesh3DVertex> m_vertices = std::vector<Vertices::Mesh3DVertex>();
    public:
        SR_FORCE_INLINE void DrawVulkan() noexcept override {
            if (m_isDestroy) return;

            if (!m_isCalculated)
                if (m_hasErrors || !this->Calculate())
                    return;
        }

        Mesh* Copy() override;

        SR_FORCE_INLINE void SetVertexArray(const std::vector<Vertices::Mesh3DVertex>& vertices) noexcept {
            this->m_isCalculated  = false;
            this->m_countVertices = vertices.size();
            this->m_vertices      = vertices;
        }

        bool Free() override {
            if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
                Debug::Log("Mesh3D::Free() : free mesh memory...");
            delete this;
            return true;
        }

        bool Calculate() override;

        bool FreeVideoMemory() override;
    };
}

#endif //GAMEENGINE_MESH3D_H
