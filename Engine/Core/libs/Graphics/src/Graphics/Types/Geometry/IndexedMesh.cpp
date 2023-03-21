//
// Created by Monika on 30.10.2021.
//

#include <Utils/Types/RawMesh.h>
#include <Graphics/Types/Geometry/IndexedMesh.h>

namespace SR_GTYPES_NS {
    IndexedMesh::~IndexedMesh() {
        SRAssert(m_IBO == SR_ID_INVALID && m_VBO == SR_ID_INVALID);
    }

    bool IndexedMesh::Calculate() {
        if (!CalculateIBO()) {
            return false;
        }

        return Mesh::Calculate();
    }

    bool IndexedMesh::CalculateIBO() {
        SRAssert(m_pipeline);
        SRAssert(m_IBO == SR_ID_INVALID);

        using namespace Memory;

        if (!IsUniqueMesh()) {
            m_IBO = MeshManager::Instance().CopyIfExists<Vertices::VertexType::Unknown, MeshMemoryType::IBO>(GetMeshIdentifier());
        }

        if (m_IBO == SR_ID_INVALID) {
            auto&& indices = GetIndices();

            if ((m_countIndices = indices.size()) == 0) {
                SR_ERROR("IndexedMesh::CalculateIBO() : invalid indices! \n\tIdentifier: " + GetMeshIdentifier());
                return false;
            }

            if (m_IBO = m_pipeline->CalculateIBO((void *) indices.data(), sizeof(uint32_t), m_countIndices, m_VBO); m_IBO == SR_ID_INVALID) {
                SR_ERROR("IndexedMesh::CalculateIBO() : failed calculate IBO \"" + GetGeometryName() + "\" mesh!");
                m_hasErrors = true;
                return false;
            }
            else if (IsUniqueMesh()) {
                return Mesh::Calculate();
            }

            return MeshManager::Instance().Register<Vertices::VertexType::Unknown, MeshMemoryType::IBO>(
                GetMeshIdentifier(),
                m_countIndices,
                m_IBO
            );
        }

        if (!IsUniqueMesh()) {
            m_countIndices = MeshManager::Instance().Size<Vertices::VertexType::Unknown, MeshMemoryType::IBO>(
                GetMeshIdentifier()
            );
        }

        return true;
    }

    bool IndexedMesh::FreeIBO() {
        if (m_IBO == SR_ID_INVALID) {
            return true;
        }

        using namespace Memory;

        auto&& manager = Memory::MeshManager::Instance();

        const bool isAllowFree = IsUniqueMesh() || manager.Free<Vertices::VertexType::Unknown, MeshMemoryType::IBO>(GetMeshIdentifier()) == MeshManager::FreeResult::Freed;

        if (isAllowFree && !m_pipeline->FreeIBO(&m_IBO)) {
            SR_ERROR("IndexedMesh:FreeVideoMemory() : failed free IBO! Something went wrong...");
            return false;
        }

        m_IBO = SR_ID_INVALID;

        return true;
    }

    void IndexedMesh::FreeVideoMemory() {
        FreeIBO();
        Mesh::FreeVideoMemory();
    }

    int32_t IndexedMesh::GetVBO() {
        if (!IsCalculated() && !Calculate()) {
            return SR_ID_INVALID;
        }

        return m_VBO;
    }

    int32_t IndexedMesh::GetIBO() {
        if (!IsCalculated() && !Calculate()) {
            return SR_ID_INVALID;
        }

        return m_IBO;
    }
}