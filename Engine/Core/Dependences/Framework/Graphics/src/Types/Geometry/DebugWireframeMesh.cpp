//
// Created by Monika on 29.10.2021.
//

#include <Types/Geometry/DebugWireframeMesh.h>
#include <Types/RawMesh.h>

Framework::Helper::IResource* Framework::Graphics::Types::DebugWireframeMesh::Copy(IResource* destination) const {
    const std::lock_guard<std::recursive_mutex> locker(m_mutex);

    auto* wireFramed = dynamic_cast<DebugWireframeMesh *>(destination ? destination : new DebugWireframeMesh(this->m_geometryName));
    wireFramed = dynamic_cast<DebugWireframeMesh *>(Framework::Graphics::Types::IndexedMesh::Copy(wireFramed));

    if (wireFramed->IsCalculated()) {
        auto &&manager = Memory::MeshManager::Instance();
        wireFramed->m_VBO = manager.CopyIfExists<Vertices::Type::SkyboxVertex, Memory::MeshManager::VBO>(GetResourceId());
    }

    return wireFramed;
}

void  Framework::Graphics::Types::DebugWireframeMesh::DrawVulkan() {
    if (!IsReady() || IsDestroyed())
        return;

    if (!m_isCalculated)
        if (m_hasErrors || !Calculate())
            return;

    if (m_descriptorSet < 0) {
        if (m_descriptorSet = m_env->AllocDescriptorSet({ DescriptorType::Uniform }); m_descriptorSet < 0) {
            SR_ERROR("DebugWireframeMesh::DrawVulkan() : failed to calculate descriptor set!");
            m_hasErrors = true;
            return;
        }

        if (m_UBO = m_env->AllocateUBO(sizeof(WireframeUBO)); m_UBO < 0) {
            SR_ERROR("DebugWireframeMesh::DrawVulkan() : failed to allocate uniform buffer object!");
            m_hasErrors = true;
            return;
        }

        const auto&& shader = m_material->GetShader();

        m_env->UpdateDescriptorSets(m_descriptorSet, {
                { DescriptorType::Uniform, { 0, m_UBO             } },
                { DescriptorType::Uniform, { 1, shader->GetUBO(0) } },
        });

        UpdateUBO();
    }

    m_env->BindDescriptorSet(m_descriptorSet);
    m_env->DrawIndices(m_countIndices);
}

bool Framework::Graphics::Types::DebugWireframeMesh::Calculate() {
    const std::lock_guard<std::recursive_mutex> locker(m_mutex);

    if (m_isCalculated)
        return true;

    const bool iboOK = m_IBO != SR_ID_INVALID;
    if (m_VBO != SR_ID_INVALID && iboOK && !m_hasErrors) {
        m_isCalculated = true;
        return true;
    }

    if (!IsCanCalculate())
        return false;

    if (Debug::GetLevel() >= Debug::Level::High)
        SR_LOG("DebugWireframeMesh::Calculate() : calculating \"" + m_geometryName + "\"...");

    ///TODO: if (!m_vertices.empty())
    ///    m_barycenter = Vertices::Barycenter(m_vertices);
    ///SRAssert(m_barycenter != Math::FVector3(Math::UnitMAX));

    auto vertices = Vertices::CastVertices<Vertices::SkyboxVertex>(m_rawMesh->GetVertices(m_meshId));

    if (!CalculateVBO<Vertices::Type::SkyboxVertex>(vertices.data()))
        return false;

    return IndexedMesh::Calculate();
}

bool Framework::Graphics::Types::DebugWireframeMesh::FreeVideoMemory() {
    if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
        SR_LOG("DebugWireframeMesh::FreeVideoMemory() : free \"" + m_geometryName + "\" mesh video memory...");

    if (!FreeVBO<Vertices::Type::SkyboxVertex>())
        return false;

    return IndexedMesh::FreeVideoMemory();
}

void Framework::Graphics::Types::DebugWireframeMesh::UpdateUBO() {
    if (m_UBO >= 0) {
        WireframeUBO ubo = { m_modelMat, m_material->GetColor(MAT_PROPERTY_DIFFUSE_COLOR).ToGLM() };
        m_env->UpdateUBO(m_UBO, &ubo, sizeof(WireframeUBO));
    }
}
