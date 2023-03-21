//
// Created by Monika on 30.10.2021.
//

#ifndef SRENGINE_GRAPHICS_INDEXEDMESH_H
#define SRENGINE_GRAPHICS_INDEXEDMESH_H

#include <Graphics/Memory/MeshManager.h>
#include <Graphics/Types/Mesh.h>
#include <Graphics/Pipeline/Environment.h>

namespace SR_GTYPES_NS {
    class IndexedMesh : public Mesh {
    protected:
        ~IndexedMesh() override;

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

        bool Calculate() override;

        bool CalculateIBO();

        void FreeVideoMemory() override;

        template<Vertices::VertexType type, typename Vertex> bool CalculateVBO(const std::vector<Vertex>& vertices);
        template<Vertices::VertexType type, typename Vertex> bool CalculateVBO(const SR_HTYPES_NS::Function<std::vector<Vertex>()>& getter);
        template<Vertices::VertexType type> bool FreeVBO();
        bool FreeIBO();

    protected:
        int32_t m_IBO = SR_ID_INVALID;
        int32_t m_VBO = SR_ID_INVALID;
        uint32_t m_countIndices = 0;
        uint32_t m_countVertices = 0;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    template<Vertices::VertexType type, typename Vertex> bool IndexedMesh::CalculateVBO(const SR_HTYPES_NS::Function<std::vector<Vertex>()>& getter) {
        SRAssert(m_pipeline);
        SRAssert(m_VBO == SR_ID_INVALID);

        using namespace Memory;

        if (!IsUniqueMesh()) {
            m_VBO = MeshManager::Instance().CopyIfExists<type, MeshMemoryType::VBO>(GetMeshIdentifier());
        }

        if (m_VBO == SR_ID_INVALID) {
            auto&& vertices = getter();
            return CalculateVBO<type>(vertices);
        }

        if (!IsUniqueMesh()) {
            m_countVertices = MeshManager::Instance().Size<type, MeshMemoryType::VBO>(
                GetMeshIdentifier()
            );
        }

        return true;
    }

    template<Vertices::VertexType type, typename Vertex> bool IndexedMesh::CalculateVBO(const std::vector<Vertex>& vertices) {
        SRAssert(m_pipeline);
        SRAssert(m_VBO == SR_ID_INVALID);

        using namespace Memory;

        if (!IsUniqueMesh()) {
            m_VBO = MeshManager::Instance().CopyIfExists<type, MeshMemoryType::VBO>(GetMeshIdentifier());
        }

        if (m_VBO == SR_ID_INVALID) {
            if ((m_countVertices = vertices.size()) == 0) {
                SR_ERROR("IndexedMesh::CalculateVBO() : invalid vertices! \n\tIdentifier: " + GetMeshIdentifier());
                return false;
            }

            if (m_VBO = m_pipeline->CalculateVBO((void*)vertices.data(), type, m_countVertices); m_VBO == SR_ID_INVALID) {
                SR_ERROR("IndexedMesh::CalculateVBO() : failed calculate VBO \"" + GetGeometryName() + "\" mesh!");
                m_hasErrors = true;
                return false;
            }
            else if (IsUniqueMesh()) {
                return true;
            }

            return MeshManager::Instance().Register<type, MeshMemoryType::VBO>(
                GetMeshIdentifier(),
                m_countVertices,
                m_VBO
            );
        }

        if (!IsUniqueMesh()) {
            m_countVertices = MeshManager::Instance().Size<type, MeshMemoryType::VBO>(
                GetMeshIdentifier()
            );
        }

        return true;
    }

    template<Vertices::VertexType type> bool IndexedMesh::FreeVBO() {
        if (m_VBO == SR_ID_INVALID) {
            return true;
        }

        using namespace Memory;

        const bool isAllowFree = IsUniqueMesh() || MeshManager::Instance().Free<type, MeshMemoryType::VBO>(GetMeshIdentifier()) == MeshManager::FreeResult::Freed;

        if (isAllowFree && !m_pipeline->FreeVBO(&m_VBO)) {
            SR_ERROR("IndexedMesh::FreeVideoMemory() : failed free VBO! Something went wrong...");
            return false;
        }

        m_VBO = SR_ID_INVALID;

        return true;
    }
}

#endif //SRENGINE_GRAPHICS_INDEXEDMESH_H
