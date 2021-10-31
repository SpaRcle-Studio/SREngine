//
// Created by Monika on 30.10.2021.
//

#include <Types/Geometry/IndexedMesh.h>

namespace Framework::Graphics::Types {
    Mesh *IndexedMesh::Copy(Mesh *mesh) const {
        if (!mesh) {
            Helper::Debug::Error("IndexedMesh::Copy() : mesh in nullptr!");
            return nullptr;
        }

        auto indexed = dynamic_cast<IndexedMesh *>(mesh);
        if (!indexed) {
            Helper::Debug::Error("IndexedMesh::Copy() : bad cast!");
            return nullptr;
        }

        if (IsCalculated()) {
            auto &&manager = Memory::MeshManager::Instance();
            indexed->m_IBO = manager.CopyIfExists<uint32_t, Memory::MeshManager::IBO>(m_resource_id);
        } else
            indexed->m_indices = m_indices;

        indexed->m_countIndices = m_countIndices;
        indexed->m_useIndices = m_useIndices;

        return VertexMesh::Copy(indexed);
    }

    bool IndexedMesh::Calculate() {
        if (!m_useIndices)
            return true;

        if (m_IBO = Memory::MeshManager::Instance().CopyIfExists<uint32_t, Memory::MeshManager::IBO>(m_resource_id);
                m_IBO == SR_ID_INVALID) {
            if (m_IBO = this->m_env->CalculateIBO(m_indices.data(), sizeof(uint32_t), m_countIndices, m_VBO); m_IBO ==
                                                                                                              SR_ID_INVALID) {
                Debug::Error("IndexedMesh::Calculate() : failed calculate IBO \"" + m_geometry_name + "\" mesh!");
                this->m_hasErrors = true;
                return false;
            } else
                Memory::MeshManager::Instance().Register<uint32_t, Memory::MeshManager::IBO>(m_resource_id, m_IBO);
        }

        return VertexMesh::Calculate();
    }

    bool IndexedMesh::FreeVideoMemory() {
        using namespace Memory;
        auto &&manager = Memory::MeshManager::Instance();
        if (m_useIndices && manager.Free<uint32_t, MeshManager::IBO>(m_resource_id) == MeshManager::FreeResult::Freed) {
            if (!Environment::Get()->FreeIBO(m_IBO))
                Debug::Error("IndexedMesh:FreeVideoMemory() : failed free IBO! Something went wrong...");
        }
        return VertexMesh::FreeVideoMemory();
    }
}