//
// Created by Monika on 30.10.2021.
//

#include <Types/Geometry/IndexedMesh.h>
#include <Utils/Types/RawMesh.h>

namespace SR_GTYPES_NS {
    SR_UTILS_NS::IResource *IndexedMesh::Copy(SR_UTILS_NS::IResource *destination) const {
        if (!destination) {
            SR_ERROR("IndexedMesh::Copy() : destination in nullptr!");
            return nullptr;
        }

        auto indexed = dynamic_cast<IndexedMesh *>(destination);
        if (!indexed) {
            SR_ERROR("IndexedMesh::Copy() : bad cast!");
            return nullptr;
        }

        if (IsCalculated()) {
            auto &&manager = Memory::MeshManager::Instance();
            indexed->m_IBO = manager.CopyIfExists<Vertices::VertexType::Unknown, Memory::MeshMemoryType::IBO>(GetResourceId());
        }

        indexed->m_countIndices = m_countIndices;

        return Mesh::Copy(indexed);
    }

    bool IndexedMesh::Calculate() {
        if (m_IBO = Memory::MeshManager::Instance().CopyIfExists<Vertices::VertexType::Unknown, Memory::MeshMemoryType::IBO>(GetResourceId()); m_IBO == SR_ID_INVALID) {
            auto&& indices = GetIndices();

            SRAssert(indices.size() == m_countIndices);

            if (m_countIndices == 0 || indices.empty()) {
                SR_ERROR("IndexedMesh::Calculate() : invalid indices! \n\tResource id: " + std::string(GetResourceId()) + "\n\tGeometry name: " + GetGeometryName());
                return false;
            }

            if (m_IBO = m_pipeline->CalculateIBO((void *) indices.data(), sizeof(uint32_t), m_countIndices, m_VBO); m_IBO == SR_ID_INVALID) {
                SR_ERROR("IndexedMesh::Calculate() : failed calculate IBO \"" + m_geometryName + "\" mesh!");
                m_hasErrors = true;
                return false;
            }
            else
                Memory::MeshManager::Instance().Register<Vertices::VertexType::Unknown, Memory::MeshMemoryType::IBO>(GetResourceId(), m_IBO);
        }

        return Mesh::Calculate();
    }

    bool IndexedMesh::FreeIBO() {
        if (m_IBO == SR_ID_INVALID) {
            return true;
        }

        using namespace Memory;

        auto &&manager = Memory::MeshManager::Instance();

        if (manager.Free<Vertices::VertexType::Unknown, MeshMemoryType::IBO>(GetResourceId()) == MeshManager::FreeResult::Freed) {
            if (!Environment::Get()->FreeIBO(&m_IBO)) {
                SR_ERROR("IndexedMesh:FreeVideoMemory() : failed free IBO! Something went wrong...");
                return false;
            }
        }

        return true;
    }

    void IndexedMesh::FreeVideoMemory() {
        FreeIBO();
        Mesh::FreeVideoMemory();
    }

    int32_t IndexedMesh::GetVBO() {
        if (!m_isCalculated && !Calculate())
            return SR_ID_INVALID;

        return m_VBO;
    }

    int32_t IndexedMesh::GetIBO() {
        if (!m_isCalculated && !Calculate())
            return SR_ID_INVALID;

        return m_IBO;
    }
}