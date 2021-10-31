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
        explicit VertexMesh(const std::string& name = "UnnamedVertexMesh")
            : Mesh(name) { };
    protected:
        int32_t  m_VBO = SR_ID_INVALID;
        uint32_t m_countVertices = 0;
    public:
        template<bool fast> [[nodiscard]] int32_t GetVBO();
    protected:
        virtual void SetVertexArray(const std::any& vertices) = 0;

        Mesh* Copy(Mesh* mesh) const override {
            if (auto vertex = dynamic_cast<VertexMesh*>(mesh)) {
                vertex->m_countVertices = m_countVertices;
                return Mesh::Copy(vertex);
            } else {
                Helper::Debug::Error("VertexMesh::Copy() : bad cast!");
                return nullptr;
            }
        }

        bool Calculate() override {
            return Mesh::Calculate();
        }
    };

    template<bool fast> int32_t VertexMesh::GetVBO() {
        if constexpr (fast) {
            return m_VBO;
        } else {
            //if (m_isDestroy) // TODO: what?
            //    return m_VBO;

            if (!m_isCalculated && !Calculate())
                return SR_ID_INVALID;

            return m_VBO;
        }
    }
}

#endif //GAMEENGINE_VERTEXMESH_H
