//
// Created by Monika on 30.10.2021.
//

#ifndef GAMEENGINE_INDEXEDMESH_H
#define GAMEENGINE_INDEXEDMESH_H

#include <Graphics/Memory/MeshManager.h>
#include <Graphics/Types/Mesh.h>

namespace SR_GRAPH_NS::Types {
    class IndexedMesh : public Mesh {
    protected:
        ~IndexedMesh() override = default;

        explicit IndexedMesh(MeshType type)
            : Mesh(type)
        { }

    public:
        SR_NODISCARD int32_t GetIBO() override;
        SR_NODISCARD int32_t GetVBO() override;

        SR_NODISCARD int32_t GetIBO() const override { return m_IBO; }
        SR_NODISCARD int32_t GetVBO() const override { return m_VBO; }

        SR_NODISCARD uint32_t GetIndicesCount() const { return m_countIndices; }
        SR_NODISCARD uint32_t GetVerticesCount() const { return m_countVertices; }

        IResource* Copy(IResource* destination) const override;

        bool Calculate() override;

        void FreeVideoMemory() override;

        template<Vertices::VertexType type, typename Vertex> bool CalculateVBO(const std::vector<Vertex>& vertices);
        template<Vertices::VertexType type> bool FreeVBO();
        bool FreeIBO();

    protected:
        int32_t m_IBO = SR_ID_INVALID;
        int32_t m_VBO = SR_ID_INVALID;
        uint32_t m_countIndices = 0;
        uint32_t m_countVertices = 0;

    };

    template<Vertices::VertexType type, typename Vertex> bool IndexedMesh::CalculateVBO(const std::vector<Vertex>& vertices) {
        if (m_VBO = Memory::MeshManager::Instance().CopyIfExists<type, Memory::MeshMemoryType::VBO>(GetResourceId()); m_VBO == SR_ID_INVALID) {
            if (m_countVertices == 0 || !vertices.data()) {
                SR_ERROR("VertexMesh::Calculate() : invalid vertices! \n\tResource id: " + std::string(GetResourceId()) + "\n\tGeometry name: " + GetGeometryName());
                return false;
            }

            if (m_VBO = m_pipeline->CalculateVBO((void*)vertices.data(), type, m_countVertices); m_VBO == SR_ID_INVALID) {
                SR_ERROR("VertexMesh::Calculate() : failed calculate VBO \"" + GetGeometryName() + "\" mesh!");
                m_hasErrors = true;
                return false;
            }
            else {
                return Memory::MeshManager::Instance().Register<type, Memory::MeshMemoryType::VBO>(GetResourceId(), m_VBO);
            }
        }

        return true;
    }

    template<Vertices::VertexType type> bool IndexedMesh::FreeVBO() {
        if (m_VBO == SR_ID_INVALID) {
            return true;
        }

        using namespace Memory;

        if (MeshManager::Instance().Free<type, MeshMemoryType::VBO>(GetResourceId()) == MeshManager::FreeResult::Freed) {
            if (!m_pipeline->FreeVBO(&m_VBO)) {
                SR_ERROR("VertexMesh:FreeVideoMemory() : failed free VBO! Something went wrong...");
                return false;
            }
        }

        return true;
    }
}

#endif //GAMEENGINE_INDEXEDMESH_H
