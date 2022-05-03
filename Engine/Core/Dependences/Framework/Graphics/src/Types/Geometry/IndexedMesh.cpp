//
// Created by Monika on 30.10.2021.
//

#include <Types/Geometry/IndexedMesh.h>
#include <Types/RawMesh.h>

namespace Framework::Graphics::Types {
    IResource *IndexedMesh::Copy(IResource *destination) const {
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
            indexed->m_IBO = manager.CopyIfExists<Vertices::Type::Unknown, Memory::MeshManager::IBO>(GetResourceId());
        }

        indexed->m_countIndices = m_countIndices;

        return Mesh::Copy(indexed);
    }

    bool IndexedMesh::Calculate() {
        auto&& indices = m_rawMesh->GetIndices(m_meshId);

        if (m_IBO = Memory::MeshManager::Instance().CopyIfExists<Vertices::Type::Unknown, Memory::MeshManager::IBO>(GetResourceId()); m_IBO == SR_ID_INVALID) {
            SRAssert(indices.size() == m_countIndices);

            if (m_countIndices == 0 || indices.empty()) {
                SR_ERROR("IndexedMesh::Calculate() : invalid indices! \n\tResource id: " + GetResourceId() + "\n\tGeometry name: " + GetGeometryName());
                return false;
            }

            if (m_IBO = m_env->CalculateIBO((void *) indices.data(), sizeof(uint32_t), m_countIndices, m_VBO); m_IBO == SR_ID_INVALID) {
                SR_ERROR("IndexedMesh::Calculate() : failed calculate IBO \"" + m_geometryName + "\" mesh!");
                m_hasErrors = true;
                return false;
            }
            else
                Memory::MeshManager::Instance().Register<Vertices::Type::Unknown, Memory::MeshManager::IBO>(GetResourceId(), m_IBO);
        }

        return Mesh::Calculate();
    }

    bool IndexedMesh::FreeVideoMemory() {
        using namespace Memory;

        auto &&manager = Memory::MeshManager::Instance();

        if (manager.Free<Vertices::Type::Unknown, MeshManager::IBO>(GetResourceId()) == MeshManager::FreeResult::Freed) {
            if (!Environment::Get()->FreeIBO(&m_IBO))
                SR_ERROR("IndexedMesh:FreeVideoMemory() : failed free IBO! Something went wrong...");
        }

        return Mesh::FreeVideoMemory();
    }

    void IndexedMesh::SetRawMesh(Helper::Types::RawMesh *raw)  {
        m_countIndices = raw->GetIndicesCount(m_meshId);
        m_countVertices = raw->GetVerticesCount(m_meshId);
        Mesh::SetRawMesh(raw);
    }
}