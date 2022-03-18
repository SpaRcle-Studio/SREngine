//
// Created by Monika on 30.10.2021.
//

#include <Types/Geometry/IndexedMesh.h>

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
        else {
            ///SR_WARN("IndexesMesh::Copy() : copying raw data. This can lead to a decrease in performance!");
            indexed->m_indices = m_indices;
        }

        indexed->m_countIndices = m_countIndices;
        indexed->m_useIndices = m_useIndices;

        return VertexMesh::Copy(indexed);
    }

    bool IndexedMesh::Calculate() {
        if (!m_useIndices)
            return true;

        if (m_IBO = Memory::MeshManager::Instance().CopyIfExists<Vertices::Type::Unknown, Memory::MeshManager::IBO>(GetResourceId()); m_IBO == SR_ID_INVALID) {
            if (m_countIndices == 0 || m_indices.empty()) {
                Debug::Error("IndexedMesh::Calculate() : invalid indices! \n\tResource id: " + GetResourceId() + "\n\tGeometry name: " + GetGeometryName());
                return false;
            }

            if (m_IBO = this->m_env->CalculateIBO(m_indices.data(), sizeof(uint32_t), m_countIndices, m_VBO); m_IBO == SR_ID_INVALID) {
                Debug::Error("IndexedMesh::Calculate() : failed calculate IBO \"" + m_geometryName + "\" mesh!");
                this->m_hasErrors = true;
                return false;
            } else
                Memory::MeshManager::Instance().Register<Vertices::Type::Unknown, Memory::MeshManager::IBO>(GetResourceId(), m_IBO);
        }

        return VertexMesh::Calculate();
    }

    bool IndexedMesh::FreeVideoMemory() {
        using namespace Memory;
        auto &&manager = Memory::MeshManager::Instance();
        if (m_useIndices && manager.Free<Vertices::Type::Unknown, MeshManager::IBO>(GetResourceId()) == MeshManager::FreeResult::Freed) {
            if (!Environment::Get()->FreeIBO(m_IBO))
                Debug::Error("IndexedMesh:FreeVideoMemory() : failed free IBO! Something went wrong...");
        }
        return VertexMesh::FreeVideoMemory();
    }
}