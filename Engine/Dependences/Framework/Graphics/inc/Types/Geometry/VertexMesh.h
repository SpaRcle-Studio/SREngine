//
// Created by Monika on 30.10.2021.
//

#ifndef GAMEENGINE_VERTEXMESH_H
#define GAMEENGINE_VERTEXMESH_H

#include <any>
#include <Types/Mesh.h>
#include <Memory/MeshManager.h>

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

        Mesh* Copy(Mesh* destination) const override {
            if (auto vertex = dynamic_cast<VertexMesh*>(destination)) {
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

    protected:
        template<Vertices::Type type> bool CalculateVBO(void* data);
        template<Vertices::Type type> bool FreeVBO();

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

    template<Vertices::Type type> bool VertexMesh::CalculateVBO(void* data) {
        using namespace Memory;

        if (m_VBO = MeshManager::Instance().CopyIfExists<type, MeshManager::VBO>(m_resource_id); m_VBO == SR_ID_INVALID) {
            if (m_VBO = this->m_env->CalculateVBO(data, type, m_countVertices); m_VBO == SR_ID_INVALID) {
                Debug::Error("Mesh3D::Calculate() : failed calculate VBO \"" + m_geometryName + "\" mesh!");
                this->m_hasErrors = true;
                return false;
            } else
                return Memory::MeshManager::Instance().Register<type, Memory::MeshManager::VBO>(m_resource_id, m_VBO);
        }

        return true;
    }

    template<Vertices::Type type> bool VertexMesh::FreeVBO() {
        using namespace Memory;

        if (MeshManager::Instance().Free<type, MeshManager::VBO>(m_resource_id) == MeshManager::FreeResult::Freed) {
            if (!m_env->FreeVBO(m_VBO)) {
                Debug::Error("Mesh:FreeVideoMemory() : failed free VBO! Something went wrong...");
                return false;
            }
        }

        return true;
    }
}

#endif //GAMEENGINE_VERTEXMESH_H
