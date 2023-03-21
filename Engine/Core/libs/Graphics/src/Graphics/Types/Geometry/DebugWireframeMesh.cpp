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

            if (m_virtualUBO != SR_ID_INVALID) {
                m_uboManager.BindUBO(m_virtualUBO);
            }
            else {
                m_pipeline->ResetDescriptorSet();
                m_hasErrors = true;
                return;
            }

            pShader->InitUBOBlock();
            pShader->Flush();

            m_material->UseSamplers();
        }

        switch (m_uboManager.BindUBO(m_virtualUBO)) {
            case Memory::UBOManager::BindResult::Duplicated:
                pShader->InitUBOBlock();
                pShader->Flush();
                m_material->UseSamplers();
                SR_FALLTHROUGH;
            case Memory::UBOManager::BindResult::Success:
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

        if (!IsCanCalculate()) {
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

    void DebugWireframeMesh::FreeVideoMemory() {
        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("DebugWireframeMesh::FreeVideoMemory() : free \"" + GetGeometryName() + "\" mesh video memory...");
        }

        if (!FreeVBO<Vertices::VertexType::SimpleVertex>()) {
            SR_ERROR("DebugWireframeMesh::FreeVideoMemory() : failed to free VBO!");
        }

        IndexedMesh::FreeVideoMemory();
    }

    std::vector<uint32_t> DebugWireframeMesh::GetIndices() const {
        return GetRawMesh()->GetIndices(GetMeshId());
    }

    void DebugWireframeMesh::SetMatrix(const SR_MATH_NS::Matrix4x4& matrix4X4) {
        m_modelMatrix = matrix4X4;
    }

    void DebugWireframeMesh::UseMaterial() {
        Mesh::UseMaterial();
        GetShader()->SetMat4(SHADER_MODEL_MATRIX, m_modelMatrix);
        GetShader()->SetVec4(SR_COMPILE_TIME_CRC32_STR("color"), m_color.Cast<float_t>().ToGLM());
    }

    const SR_MATH_NS::Matrix4x4 &DebugWireframeMesh::GetModelMatrix() const {
        return m_modelMatrix;
    }

    void DebugWireframeMesh::SetColor(const SR_MATH_NS::FVector4& color) {
        m_color = color;
    }

    std::string DebugWireframeMesh::GetMeshIdentifier() const {
        if (auto&& pRawMesh = GetRawMesh()) {
            return pRawMesh->GetResourceId() + "|" + std::to_string(GetMeshId());
        }

        return Super::GetMeshIdentifier();
    }
}