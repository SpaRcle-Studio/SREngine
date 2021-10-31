//
// Created by Monika on 30.10.2021.
//

#ifndef GAMEENGINE_VERTEXMESH_H
#define GAMEENGINE_VERTEXMESH_H

#include <any>
#include <Types/Mesh.h>

namespace Framework::Graphics::Types {
    class VertexMesh : public Mesh {
    protected:
        ~VertexMesh() override = default;
        VertexMesh(Shader* shader, Material* material, std::string name = "Unnamed")
            : Mesh(shader, material, std::move(name)) { };
    protected:
        int32_t  m_VBO = SR_ID_INVALID;
        uint32_t m_countVertices = 0;
    public:
        template<bool fast> [[nodiscard]] int32_t GetVBO();
    protected:
        virtual void SetVertexArray(const std::any& vertices) = 0;

        Mesh* Copy(Mesh* mesh) const override {
            return Mesh::Copy(mesh);
        }

        bool Calculate() override {
            return Mesh::Calculate();
        }
    };

    /*
    int32_t Mesh::GetVBO(bool fast)  {
        if (fast)
            return m_VBO;

        if (m_isDestroy) // TODO: what?
            return m_VBO;

        if (!m_isCalculated)
            if (!Calculate())
                return -1;

        return m_VBO;
    }*/

    template<bool fast> int32_t VertexMesh::GetVBO() {
        if constexpr (fast) {
            return m_VBO;
        } else {
            if (!m_isCalculated && !Calculate())
                return SR_ID_INVALID;

            return m_VBO;
        }
    }
}

#endif //GAMEENGINE_VERTEXMESH_H
