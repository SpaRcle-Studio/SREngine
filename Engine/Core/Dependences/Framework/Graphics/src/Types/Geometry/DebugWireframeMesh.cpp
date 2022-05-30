//
// Created by Monika on 29.10.2021.
//

#include <Types/Geometry/DebugWireframeMesh.h>
#include <Types/RawMesh.h>

namespace SR_GTYPES_NS {
    SR_UTILS_NS::IResource* DebugWireframeMesh::Copy(IResource* destination) const {
        SR_SCOPED_LOCK

        auto* wireFramed = dynamic_cast<DebugWireframeMesh *>(destination ? destination : new DebugWireframeMesh(m_geometryName));
        wireFramed = dynamic_cast<DebugWireframeMesh *>(Framework::Graphics::Types::IndexedMesh::Copy(wireFramed));

        if (wireFramed->IsCalculated()) {
            auto &&manager = Memory::MeshManager::Instance();
            wireFramed->m_VBO = manager.CopyIfExists<Vertices::Type::SimpleVertex, Memory::MeshManager::VBO>(GetResourceId());
        }

        return wireFramed;
    }

    void DebugWireframeMesh::DrawVulkan() {
        if (!IsActive() || IsDestroyed())
            return;

        if ((!m_isCalculated && !Calculate()) || m_hasErrors)
            return;

        auto &&shader = m_material->GetShader();

        if (m_dirtyMaterial)
        {
            m_dirtyMaterial = false;

            if (m_descriptorSet >= 0 && !m_env->FreeDescriptorSet(&m_descriptorSet)) {
                SR_ERROR("DebugWireframeMesh::FreeVideoMemory() : failed to free descriptor set!");
            }

            if (m_UBO >= 0 && !m_env->FreeUBO(&m_UBO)) {
                SR_ERROR("DebugWireframeMesh::FreeVideoMemory() : failed to free uniform buffer object!");
            }

            if (shader->GetUBOBlockSize() > 0) {
                if (m_descriptorSet = m_env->AllocDescriptorSet({DescriptorType::Uniform}); m_descriptorSet < 0) {
                    SR_ERROR("DebugWireframeMesh::DrawVulkan() : failed to calculate descriptor set!");
                    m_hasErrors = true;
                    return;
                }

                if (m_UBO = m_env->AllocateUBO(shader->GetUBOBlockSize()); m_UBO < 0) {
                    SR_ERROR("DebugWireframeMesh::DrawVulkan() : failed to allocate uniform buffer object!");
                    m_hasErrors = true;
                    return;
                }

                m_env->BindUBO(m_UBO);
                m_env->BindDescriptorSet(m_descriptorSet);
            }
            else if (shader->GetSamplersCount() > 0) {
                if (m_descriptorSet = m_env->AllocDescriptorSet({DescriptorType::CombinedImage}); m_descriptorSet < 0) {
                    SR_ERROR("DebugWireframeMesh::DrawVulkan() : failed to calculate descriptor set!");
                    m_hasErrors = true;
                    return;
                }
                m_env->BindDescriptorSet(m_descriptorSet);
            }
            else
                m_env->ResetDescriptorSet();

            shader->InitUBOBlock();
            shader->Flush();

            m_material->UseSamplers();
        }

        if (m_descriptorSet != SR_ID_INVALID) {
            m_env->BindDescriptorSet(m_descriptorSet);
        }

        m_env->DrawIndices(m_countIndices);
    }

    bool DebugWireframeMesh::Calculate() {
        SR_SCOPED_LOCK

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

        auto vertices = Vertices::CastVertices<Vertices::SimpleVertex>(m_rawMesh->GetVertices(m_meshId));

        if (!CalculateVBO<Vertices::Type::SimpleVertex>(vertices.data()))
            return false;

        return IndexedMesh::Calculate();
    }

    bool DebugWireframeMesh::FreeVideoMemory() {
        SR_SCOPED_LOCK

        if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
            SR_LOG("DebugWireframeMesh::FreeVideoMemory() : free \"" + m_geometryName + "\" mesh video memory...");

        if (!FreeVBO<Vertices::Type::SimpleVertex>())
            return false;

        return IndexedMesh::FreeVideoMemory();
    }
}