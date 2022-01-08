//
// Created by Monika on 29.10.2021.
//

#include <Types/Geometry/DebugWireframeMesh.h>

Framework::Helper::IResource* Framework::Graphics::Types::DebugWireframeMesh::Copy(IResource* destination) const {
    const std::lock_guard<std::recursive_mutex> locker(m_mutex);

    auto* wireFramed = dynamic_cast<DebugWireframeMesh *>(destination ? destination : new DebugWireframeMesh(this->m_geometryName));
    wireFramed = dynamic_cast<DebugWireframeMesh *>(Framework::Graphics::Types::IndexedMesh::Copy(wireFramed));

    if (wireFramed->IsCalculated())
        wireFramed->m_VBO = Memory::MeshManager::Instance().CopyIfExists<Vertices::Type::SkyboxVertex, Memory::MeshManager::VBO>(GetResourceId());
    else
        wireFramed->m_vertices = m_vertices;

    return wireFramed;
}

void  Framework::Graphics::Types::DebugWireframeMesh::DrawVulkan() {
    if (!IsReady() || IsDestroy())
        return;

    if (!m_isCalculated)
        if (m_hasErrors || !this->Calculate())
            return;

    if (m_descriptorSet < 0) {
        if (m_descriptorSet = m_env->AllocDescriptorSet({ DescriptorType::Uniform }); m_descriptorSet < 0) {
            Helper::Debug::Error("DebugWireframeMesh::DrawVulkan() : failed to calculate descriptor set!");
            m_hasErrors = true; return;
        }

        if (m_UBO = m_env->AllocateUBO(sizeof(WireframeUBO)); m_UBO < 0) {
            Helper::Debug::Error("DebugWireframeMesh::DrawVulkan() : failed to allocate uniform buffer object!");
            m_hasErrors = true; return;
        }

        this->m_env->UpdateDescriptorSets(m_descriptorSet, {
                { DescriptorType::Uniform, { 0, m_UBO                                 } },
                { DescriptorType::Uniform, { 1, Shader::GetCurrentShader()->GetUBO(0) } },
        });

        UpdateUBO();
    }

    this->m_env->BindDescriptorSet(m_descriptorSet);

    this->m_env->DrawIndices(this->m_countIndices);
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

    if (!m_vertices.empty())
        m_barycenter = Vertices::Barycenter(m_vertices);
    SRAssert(m_barycenter != Math::FVector3(Math::UnitMAX));

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

void Framework::Graphics::Types::DebugWireframeMesh::UpdateUBO() {
    if (m_UBO >= 0) {
        WireframeUBO ubo = { m_modelMat, m_material->GetColor() };
        m_env->UpdateUBO(m_UBO, &ubo, sizeof(WireframeUBO));
    }
}
