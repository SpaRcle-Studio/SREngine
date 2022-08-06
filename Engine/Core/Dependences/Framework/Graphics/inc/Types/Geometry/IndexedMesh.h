//
// Created by Monika on 30.10.2021.
//

#ifndef GAMEENGINE_INDEXEDMESH_H
#define GAMEENGINE_INDEXEDMESH_H

#include <Memory/MeshManager.h>
#include <Types/Mesh.h>

namespace SR_GRAPH_NS::Types {
    class IndexedMesh : public Mesh {
    protected:
        ~IndexedMesh() override = default;

        explicit IndexedMesh(MeshType type)
            : Mesh(type)
        { }

    public:
        template<bool fast> SR_NODISCARD int32_t GetIBO();
        template<bool fast> SR_NODISCARD int32_t GetVBO();

        SR_NODISCARD uint32_t GetIndicesCount() const { return m_countIndices; }
        SR_NODISCARD uint32_t GetVerticesCount() const { return m_countVertices; }

        IResource* Copy(IResource* destination) const override;

        bool Calculate() override;

        void FreeVideoMemory() override;

        template<Vertices::Type type, typename Vertex> bool CalculateVBO(const std::vector<Vertex>& vertices);
        template<Vertices::Type type> bool FreeVBO();

    protected:
        int32_t m_IBO = SR_ID_INVALID;
        int32_t m_VBO = SR_ID_INVALID;
        uint32_t m_countIndices = 0;
        uint32_t m_countVertices = 0;

    };

    template<bool fast> int32_t IndexedMesh::GetIBO() {
        static_assert(fast, "unsupported!");

        if constexpr (fast) {
            return m_VBO;
        }
    }

    template<bool fast> int32_t IndexedMesh::GetVBO() {
        if constexpr (fast) {
            return m_VBO;
        }
        else {
            if (!m_isCalculated && !Calculate())
                return SR_ID_INVALID;

            return m_VBO;
        }
    }

    template<Vertices::Type type, typename Vertex> bool IndexedMesh::CalculateVBO(const std::vector<Vertex>& vertices) {
        if (!vertices.empty()) {
            m_barycenter = Vertices::Barycenter(vertices);
        }
        SRAssert(m_barycenter != SR_MATH_NS::FVector3(SR_MATH_NS::UnitMAX));

        if (m_VBO = Memory::MeshManager::Instance().CopyIfExists<type, Memory::MeshMemoryType::VBO>(GetResourceId()); m_VBO == SR_ID_INVALID) {
            if (m_countVertices == 0 || !vertices.data()) {
                SR_ERROR("VertexMesh::Calculate() : invalid vertices! \n\tResource id: " + GetResourceId() + "\n\tGeometry name: " + GetGeometryName());
                return false;
            }

            if (m_VBO = m_pipeline->CalculateVBO((void*)vertices.data(), type, m_countVertices); m_VBO == SR_ID_INVALID) {
                SR_ERROR("VertexMesh::Calculate() : failed calculate VBO \"" + m_geometryName + "\" mesh!");
                m_hasErrors = true;
                return false;
            }
            else {
                return Memory::MeshManager::Instance().Register<type, Memory::MeshMemoryType::VBO>(GetResourceId(), m_VBO);
            }
        }

        return true;
    }

    template<Vertices::Type type> bool IndexedMesh::FreeVBO() {
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
