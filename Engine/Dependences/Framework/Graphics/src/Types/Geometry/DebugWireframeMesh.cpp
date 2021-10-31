//
// Created by Monika on 29.10.2021.
//

#include <Types/Geometry/DebugWireframeMesh.h>
#include <Memory/MeshManager.h>

/*
Framework::Graphics::Types::Mesh* Framework::Graphics::Types::DebugWireframeMesh::Copy(Framework::Graphics::Types::Mesh *mesh) const {
    const std::lock_guard<std::recursive_mutex> locker(m_mutex);

    DebugWireframeMesh* wireFramed = dynamic_cast<DebugWireframeMesh *>(mesh ? mesh : new DebugWireframeMesh(this->m_shader, nullptr, this->m_geometry_name));
    wireFramed = dynamic_cast<DebugWireframeMesh *>(Mesh::Copy(wireFramed));

    if (wireFramed->IsCalculated()) {
        wireFramed->m_VBO = Memory::MeshManager::Instance().CopyIfExists<DebugWireframeMesh>(m_resource_id, Memory::MeshManager::VBO);
        wireFramed->m_vertices = m_vertices;
    }

    return wireFramed;
}

bool Framework::Graphics::Types::DebugWireframeMesh::Calculate() {
    return false;
}

void Framework::Graphics::Types::DebugWireframeMesh::ReCalcModel() {

}

bool Framework::Graphics::Types::DebugWireframeMesh::FreeVideoMemory() {
    return false;
}

void Framework::Graphics::Types::DebugWireframeMesh::SetVertexArray(const std::vector<Vertices::SkyboxVertex> &vertices) {
    this->m_isCalculated  = false;
    this->m_countVertices = vertices.size();
    this->m_vertices      = vertices;
}*/
