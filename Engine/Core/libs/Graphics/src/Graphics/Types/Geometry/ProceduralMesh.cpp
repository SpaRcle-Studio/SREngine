//
// Created by Monika on 05.04.2022.
//

#include <Graphics/Types/Geometry/ProceduralMesh.h>

namespace SR_GTYPES_NS {
    ProceduralMesh::ProceduralMesh()
        : Super(MeshType::Procedural)
    {
        /// override component
        Component::InitComponent<ProceduralMesh>();
        SetId(SR_FORMAT("Procedural:%p", (void*)this));
    }

    SR_UTILS_NS::IResource* ProceduralMesh::CopyResource(IResource* destination) const {
        /// TODO: fixme
        SRHalt("The procedural meshes isn't are copyable!");
        return nullptr;
    }

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

    void ProceduralMesh::FreeVideoMemory() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (!FreeVBO<Vertices::VertexType::StaticMeshVertex>()) {
            SR_ERROR("ProceduralMesh::FreeVideoMemory() : failed to free VBO!");
        }

        IndexedMesh::FreeVideoMemory();
    }

    SR_HTYPES_NS::Marshal::Ptr SR_GTYPES_NS::ProceduralMesh::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = Component::Save(pMarshal, flags);

        pMarshal->Write(static_cast<int32_t>(m_type));

        pMarshal->Write(m_material ? m_material->GetResourceId() : "None");

        return pMarshal;
    }

    bool ProceduralMesh::Calculate()  {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_isCalculated) {
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
        if (!IsActive() || IsDestroyed())
            return;

        if ((!m_isCalculated && !Calculate()) || m_hasErrors)
            return;

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

        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
    }

    void ProceduralMesh::UseMaterial() {
        Mesh::UseMaterial();
        GetShader()->SetMat4(SHADER_MODEL_MATRIX, m_modelMatrix);
    }
}
