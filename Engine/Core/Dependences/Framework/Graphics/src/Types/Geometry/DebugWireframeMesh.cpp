//
// Created by Monika on 29.10.2021.
//

#include <Types/Geometry/DebugWireframeMesh.h>
#include <Utils/Types/RawMesh.h>

namespace SR_GTYPES_NS {
    SR_UTILS_NS::IResource* DebugWireframeMesh::Copy(IResource* destination) const {
        SR_SCOPED_LOCK

        auto* wireFramed = dynamic_cast<DebugWireframeMesh *>(destination ? destination : new DebugWireframeMesh(m_geometryName));
        wireFramed = dynamic_cast<DebugWireframeMesh *>(Framework::Graphics::Types::IndexedMesh::Copy(wireFramed));

        if (wireFramed->IsCalculated()) {
            auto &&manager = Memory::MeshManager::Instance();
            wireFramed->m_VBO = manager.CopyIfExists<Vertices::Type::SimpleVertex, Memory::MeshMemoryType::VBO>(GetResourceId());
        }

        return wireFramed;
    }

    void DebugWireframeMesh::DrawVulkan() {
        if (!IsActive() || IsDestroyed())
            return;

        if ((!m_isCalculated && !Calculate()) || m_hasErrors)
            return;

        auto &&shader = m_material->GetShader();
        auto&& uboManager = Memory::UBOManager::Instance();

        if (m_dirtyMaterial)
        {
            m_dirtyMaterial = false;

            m_virtualUBO = uboManager.ReAllocateUBO(m_virtualUBO, shader->GetUBOBlockSize(), shader->GetSamplersCount());

            if (m_virtualUBO != SR_ID_INVALID) {
                uboManager.BindUBO(m_virtualUBO);
            }
            else {
                m_env->ResetDescriptorSet();
                m_hasErrors = true;
                return;
            }

            shader->InitUBOBlock();
            shader->Flush();

            m_material->UseSamplers();
        }

        uboManager.BindUBO(m_virtualUBO);

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

        if (!IsCanCalculate()) {
            return false;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("DebugWireframeMesh::Calculate() : calculating \"" + m_geometryName + "\"...");
        }

        auto vertices = Vertices::CastVertices<Vertices::SimpleVertex>(m_rawMesh->GetVertices(m_meshId));

        if (!CalculateVBO<Vertices::Type::SimpleVertex>(vertices))
            return false;

        return IndexedMesh::Calculate();
    }

    bool DebugWireframeMesh::FreeVideoMemory() {
        SR_SCOPED_LOCK

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("DebugWireframeMesh::FreeVideoMemory() : free \"" + m_geometryName + "\" mesh video memory...");
        }

        if (!FreeVBO<Vertices::Type::SimpleVertex>())
            return false;

        return IndexedMesh::FreeVideoMemory();
    }
}