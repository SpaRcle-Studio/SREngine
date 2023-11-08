//
// Created by Monika on 29.10.2021.
//

#include <Graphics/Types/Geometry/DebugWireframeMesh.h>
#include <Utils/Types/RawMesh.h>

namespace SR_GTYPES_NS {
    DebugWireframeMesh::DebugWireframeMesh()
        : Super(MeshType::Wireframe)
    { }

    void DebugWireframeMesh::Draw() {
        if ((!IsCalculated() && !Calculate()) || m_hasErrors) {
            return;
        }

        auto&& pShader = m_material->GetShader();

        if (m_dirtyMaterial)
        {
            m_dirtyMaterial = false;

            m_virtualUBO = m_uboManager.ReAllocateUBO(m_virtualUBO, pShader->GetUBOBlockSize(), pShader->GetSamplersCount());

            if (m_virtualUBO == SR_ID_INVALID || m_uboManager.BindUBO(m_virtualUBO) == Memory::UBOManager::BindResult::Failed) {
                m_pipeline->ResetDescriptorSet();
                m_hasErrors = true;
                return;
            }

            pShader->InitUBOBlock();
            pShader->Flush();

            m_material->UseSamplers();
            pShader->FlushSamplers();
        }

        switch (m_uboManager.BindUBO(m_virtualUBO)) {
            case Memory::UBOManager::BindResult::Duplicated:
                pShader->InitUBOBlock();
                pShader->Flush();
                m_material->UseSamplers();
                pShader->FlushSamplers();
                SR_FALLTHROUGH;
            case Memory::UBOManager::BindResult::Success:
                pShader->FlushConstants();
                m_pipeline->DrawIndices(m_countIndices);
                break;
            case Memory::UBOManager::BindResult::Failed:
            default:
                break;
        }
    }

    bool DebugWireframeMesh::Calculate() {
        if (IsCalculated()) {
            return true;
        }

        FreeVideoMemory();

        if (!IsCalculatable()) {
            return false;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("DebugWireframeMesh::Calculate() : calculating \"" + GetGeometryName() + "\"...");
        }

        if (!CalculateVBO<Vertices::VertexType::SimpleVertex, Vertices::SimpleVertex>([this]() {
            return Vertices::CastVertices<Vertices::SimpleVertex>(GetVertices());
        })) {
            return false;
        }

        return IndexedMesh::Calculate();
    }

    std::vector<uint32_t> DebugWireframeMesh::GetIndices() const {
        return GetRawMesh()->GetIndices(GetMeshId());
    }

    void DebugWireframeMesh::SetMatrix(const SR_MATH_NS::Matrix4x4& matrix4X4) {
        m_modelMatrix = matrix4X4;
    }

    void DebugWireframeMesh::OnResourceReloaded(SR_UTILS_NS::IResource* pResource) {
        if (GetRawMesh() == pResource) {
            OnRawMeshChanged();
            return;
        }
        Mesh::OnResourceReloaded(pResource);
    }

    void DebugWireframeMesh::UseMaterial() {
        Mesh::UseMaterial();
        static const uint64_t colorHashName = SR_UTILS_NS::StringAtom("color").GetHash();
        GetShader()->SetMat4(SHADER_MODEL_MATRIX, m_modelMatrix);
        GetShader()->SetVec4(colorHashName, m_color.Cast<float_t>().ToGLM());
    }

    const SR_MATH_NS::Matrix4x4 &DebugWireframeMesh::GetModelMatrix() const {
        return m_modelMatrix;
    }

    void DebugWireframeMesh::SetColor(const SR_MATH_NS::FVector4& color) {
        m_color = color;
    }

    std::string DebugWireframeMesh::GetMeshIdentifier() const {
        if (auto&& pRawMesh = GetRawMesh()) {
            return SR_UTILS_NS::Format("%s|%i|%i", pRawMesh->GetResourceId().c_str(), GetMeshId(), pRawMesh->GetReloadCount());
        }

        return Super::GetMeshIdentifier();
    }
}