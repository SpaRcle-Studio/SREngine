//
// Created by Nikita on 02.06.2021.
//

#include <Utils/Types/RawMesh.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/ECS/ComponentManager.h>

#include <Graphics/Types/Geometry/Mesh3D.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Types/Uniforms.h>
#include <Graphics/Types/Shader.h>

namespace SR_GTYPES_NS {
    SR_REGISTER_COMPONENT(Mesh3D);

    Mesh3D::Mesh3D()
        : Super(MeshType::Static)
    { }

    bool Mesh3D::Calculate()  {
        SR_TRACY_ZONE;

        if (IsCalculated()) {
            return true;
        }

        FreeVideoMemory();

        if (!IsCalculatable()) {
            return false;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Full) {
            SR_LOG("Mesh3D::Calculate() : calculating \"" + GetGeometryName() + "\"...");
        }

        if (!CalculateVBO<Vertices::VertexType::StaticMeshVertex, Vertices::StaticMeshVertex>([this]() {
            return Vertices::CastVertices<Vertices::StaticMeshVertex>(GetVertices());
        })) {
            return false;
        }

        return IndexedMesh::Calculate();
    }

    void Mesh3D::Draw() {
        SR_TRACY_ZONE;

        auto&& pShader = GetRenderContext()->GetCurrentShader();

        if (!pShader || !IsActive()) {
            return;
        }

        if ((!IsCalculated() && !Calculate()) || m_hasErrors) {
            return;
        }

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

    SR_HTYPES_NS::Marshal::Ptr SR_GTYPES_NS::Mesh3D::Save(SR_UTILS_NS::SavableSaveData data) const {
        auto&& pMarshal = MeshComponent::Save(data);

        /// TODO: use unicode
        pMarshal->Write<std::string>(GetMeshStringPath());
        pMarshal->Write<int32_t>(static_cast<int32_t>(GetMeshId()));

        pMarshal->Write<std::string>(m_material ? m_material->GetResourceId() : "None");

        return pMarshal;
    }

    SR_UTILS_NS::Component* SR_GTYPES_NS::Mesh3D::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        const auto&& type = static_cast<MeshType>(marshal.Read<int32_t>());

        const auto&& path = marshal.Read<std::string>();
        const auto&& id = marshal.Read<uint32_t>();

        const auto&& material = marshal.Read<std::string>();

        if (id < 0) {
            return nullptr;
        }

        auto&& pMesh = Mesh::Load(SR_UTILS_NS::Path(path, true), type, id);

        if (pMesh && material != "None") {
            if (auto&& pMaterial = SR_GTYPES_NS::Material::Load(SR_UTILS_NS::Path(material, true))) {
                pMesh->SetMaterial(pMaterial);
            }
            else {
                SR_ERROR("Mesh3D::LoadComponent() : failed to load material! Name: " + material);
            }
        }

        return dynamic_cast<Component*>(pMesh);
    }

    std::vector<uint32_t> Mesh3D::GetIndices() const {
        return GetRawMesh()->GetIndices(GetMeshId());
    }

    bool Mesh3D::IsCalculatable() const {
        return IsValidMeshId() && Mesh::IsCalculatable();
    }

    void Mesh3D::UseMaterial() {
        Super::UseMaterial();
        UseModelMatrix();
    }

    void Mesh3D::UseModelMatrix() {
        GetRenderContext()->GetCurrentShader()->SetMat4(SHADER_MODEL_MATRIX, m_modelMatrix);
    }

    void Mesh3D::OnRawMeshChanged() {
        IRawMeshHolder::OnRawMeshChanged();

        if (GetRawMesh() && IsValidMeshId()) {
            SetGeometryName(GetRawMesh()->GetGeometryName(GetMeshId()));
        }

        MarkPipelineUnBuild();

        m_dirtyMaterial = true;
        m_isCalculated = false;
    }

    std::string Mesh3D::GetMeshIdentifier() const {
        if (auto&& pRawMesh = GetRawMesh()) {
            return SR_UTILS_NS::Format("%s|%i|%i", pRawMesh->GetResourceId().c_str(), GetMeshId(), pRawMesh->GetReloadCount());
        }

        return Super::GetMeshIdentifier();
    }

    SR_UTILS_NS::Component* Mesh3D::CopyComponent() const {
        if (auto&& pMesh = dynamic_cast<Mesh3D*>(MeshComponent::CopyComponent())) {
            pMesh->SetRawMesh(GetRawMesh());
            pMesh->SetMeshId(GetMeshId());
            return pMesh;
        }

        return nullptr;
    }

    void Mesh3D::OnResourceReloaded(SR_UTILS_NS::IResource* pResource) {
        if (GetRawMesh() == pResource) {
            OnRawMeshChanged();
            return;
        }
        Mesh::OnResourceReloaded(pResource);
    }
}