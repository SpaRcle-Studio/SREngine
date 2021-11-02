//
// Created by Monika on 29.10.2021.
//

#include <Types/Geometry/DebugWireframeMesh.h>

Framework::Graphics::Types::Mesh* Framework::Graphics::Types::DebugWireframeMesh::Copy(Framework::Graphics::Types::Mesh *mesh) const {
    const std::lock_guard<std::recursive_mutex> locker(m_mutex);

    auto* wireFramed = dynamic_cast<DebugWireframeMesh *>(mesh ? mesh : new DebugWireframeMesh(this->m_geometryName));
    wireFramed = dynamic_cast<DebugWireframeMesh *>(Framework::Graphics::Types::IndexedMesh::Copy(wireFramed));

    if (wireFramed->IsCalculated())
        wireFramed->m_VBO = Memory::MeshManager::Instance().CopyIfExists<Vertices::Type::SkyboxVertex, Memory::MeshManager::VBO>(m_resource_id);
    else
        wireFramed->m_vertices = m_vertices;

    return wireFramed;
}

bool Framework::Graphics::Types::DebugWireframeMesh::Calculate() {
    const std::lock_guard<std::recursive_mutex> locker(m_mutex);

    bool iboOK = ((m_IBO != SR_ID_INVALID && m_useIndices) || !m_useIndices);
    if (m_VBO != SR_ID_INVALID && iboOK && !m_hasErrors) {
        this->m_isCalculated = true;
        return true;
    }

    if (!IsCanCalculate())
        return false;

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("DebugWireframeMesh::Calculate() : calculating \"" + m_geometryName + "\"...");

    m_barycenter = Vertices::Barycenter(m_vertices);

    if (!CalculateVBO<Vertices::Type::SkyboxVertex>(m_vertices.data()))
        return false;

    return IndexedMesh::Calculate();
}

bool Framework::Graphics::Types::DebugWireframeMesh::FreeVideoMemory() {
    if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
        Helper::Debug::Log("DebugWireframeMesh::FreeVideoMemory() : free \"" + m_geometryName + "\" mesh video memory...");

    if (!FreeVBO<Vertices::Type::SkyboxVertex>())
        return false;

    return IndexedMesh::FreeVideoMemory();
}

void Framework::Graphics::Types::DebugWireframeMesh::SetVertexArray(const std::any &vertices) {
    try {
        auto wireframeVertices = std::any_cast<Vertices::SkyboxVertices>(vertices);
        this->m_countVertices  = wireframeVertices.size();
        this->m_vertices       = wireframeVertices;
        this->m_isCalculated   = false;
    }
    catch (const std::bad_any_cast& e) {
        Helper::Debug::Error("DebugWireframeMesh::SetVertexArray() : "
                             "failed to cast any to vertices! \n\tMessage: " + std::string(e.what()));
    }
}
