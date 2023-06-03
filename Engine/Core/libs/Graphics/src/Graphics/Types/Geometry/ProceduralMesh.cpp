//
// Created by Monika on 05.04.2022.
//

#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Utils/ECS/ComponentManager.h>

namespace SR_GTYPES_NS {
    SR_REGISTER_COMPONENT(ProceduralMesh);

    ProceduralMesh::ProceduralMesh()
        : Super(MeshType::Procedural)
    { }

    SR_UTILS_NS::Component* ProceduralMesh::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        return nullptr;
    }

    void ProceduralMesh::SetVertices(const std::vector<Vertices::StaticMeshVertex>& vertices) {
        m_indices.clear();
        m_vertices.clear();

        m_countVertices = 0;
        m_countIndices = 0;

        SetDirtyMesh();

        std::unordered_map<Vertices::StaticMeshVertex, uint32_t> uniqueVertices;

        for (const auto& vertex : vertices) {
            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(m_vertices.size());
                m_vertices.push_back(vertex);
            }

            m_indices.push_back(uniqueVertices[vertex]);
        }

        m_countVertices = m_vertices.size();
        m_countIndices = m_indices.size();
    }

    SR_HTYPES_NS::Marshal::Ptr SR_GTYPES_NS::ProceduralMesh::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = MeshComponent::Save(pMarshal, flags);

        pMarshal->Write(m_material ? m_material->GetResourceId() : "None");

        return pMarshal;
    }

    bool ProceduralMesh::Calculate()  {
        if (IsCalculated()) {
            return true;
        }

        FreeVideoMemory();

        if (!IsCanCalculate()) {
            return false;
        }

        if (!CalculateVBO<Vertices::VertexType::StaticMeshVertex>(m_vertices)) {
            return false;
        }

        return IndexedMesh::Calculate();
    }

    std::vector<uint32_t> ProceduralMesh::GetIndices() const {
        return std::move(m_indices);
    }

    void ProceduralMesh::Draw() {
        if (!IsActive()) {
            return;
        }

        if ((!m_isCalculated && !Calculate()) || m_hasErrors) {
            return;
        }

        auto&& shader = m_material->GetShader();
        auto&& uboManager = Memory::UBOManager::Instance();

        if (m_dirtyMaterial)
        {
            m_dirtyMaterial = false;

            m_virtualUBO = uboManager.ReAllocateUBO(m_virtualUBO, shader->GetUBOBlockSize(), shader->GetSamplersCount());

            if (m_virtualUBO != SR_ID_INVALID) {
                uboManager.BindUBO(m_virtualUBO);
            }
            else {
                m_pipeline->ResetDescriptorSet();
                m_hasErrors = true;
                return;
            }

            shader->InitUBOBlock();
            shader->Flush();

            m_material->UseSamplers();
        }

        switch (uboManager.BindUBO(m_virtualUBO)) {
            case Memory::UBOManager::BindResult::Duplicated:
                shader->InitUBOBlock();
                shader->Flush();
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

    bool ProceduralMesh::IsCanCalculate() const {
        return m_countVertices > 0;
    }

    void ProceduralMesh::SetIndexedVertices(void *pData, uint64_t count) {
        m_vertices.resize((m_countVertices = count));
        memcpy(m_vertices.data(), pData, count * sizeof(Vertices::StaticMeshVertex));
        SetDirtyMesh();
    }

    void ProceduralMesh::SetIndices(void *pData, uint64_t count) {
        m_indices.resize((m_countIndices = count));
        memcpy(m_indices.data(), pData, count * sizeof(uint32_t));
        SetDirtyMesh();
    }

    void ProceduralMesh::SetDirtyMesh() {
        m_isCalculated = false;
        m_dirtyMaterial = true;

        if (auto&& renderScene = TryGetRenderScene()) {
            renderScene->SetDirty();
        }
    }

    void ProceduralMesh::UseMaterial() {
        Mesh::UseMaterial();
        UseModelMatrix();
    }

    void ProceduralMesh::UseModelMatrix() {
        Mesh::UseModelMatrix();
        GetRenderContext()->GetCurrentShader()->SetMat4(SHADER_MODEL_MATRIX, m_modelMatrix);
    }

    SR_UTILS_NS::Component* ProceduralMesh::CopyComponent() const {
        if (auto&& pComponent = dynamic_cast<ProceduralMesh*>(MeshComponent::CopyComponent())) {
            pComponent->SetIndexedVertices((void*)m_vertices.data(), m_vertices.size());
            pComponent->SetIndices((void*)m_indices.data(), m_indices.size());
            return pComponent;
        }

        return nullptr;
    }
}
