//
// Created by Monika on 30.07.2022.
//

#include <Utils/Types/RawMesh.h>
#include <Utils/Types/DataStorage.h>

#include <Graphics/UI/Sprite2D.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Pipeline/Environment.h>
#include <Graphics/Types/Uniforms.h>
#include <Graphics/Types/Shader.h>

namespace SR_GRAPH_UI_NS {
    SR_REGISTER_COMPONENT(Sprite2D);

    Sprite2D::Sprite2D()
        : Super(MeshType::Sprite2D)
    {  }

    std::string Sprite2D::GetMeshIdentifier() const {
        static const std::string id = "Sprite2DFromMemory";
        return id;
    }

    SR_UTILS_NS::Component* Sprite2D::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        SR_MAYBE_UNUSED const auto&& type = static_cast<MeshType>(marshal.Read<int32_t>());

        const auto&& material = marshal.Read<std::string>();

        auto&& pSprite = new Sprite2D();

        if (material != "None") {
            if (auto&& pMaterial = SR_GTYPES_NS::Material::Load(material)) {
                pSprite->SetMaterial(pMaterial);
            }
            else {
                SR_ERROR("Sprite2D::LoadComponent() : failed to load material! Name: " + material);
            }
        }

        return pSprite;
    }

    bool Sprite2D::Calculate() {
        if (IsCalculated()) {
            return true;
        }

        FreeVideoMemory();

        if (!IsCanCalculate()) {
            return false;
        }

        if (!CalculateVBO<Vertices::VertexType::UIVertex, Vertices::UIVertex>([this]() { return SR_SPRITE_VERTICES; })) {
            return false;
        }

        return IndexedMesh::Calculate();
    }

    void Sprite2D::Draw() {
        if (!IsActive()) {
            return;
        }

        if ((!IsCalculated() && !Calculate()) || m_hasErrors) {
            return;
        }

        auto&& pShader = GetPipeline()->GetCurrentShader();
        auto&& uboManager = Memory::UBOManager::Instance();

        if (m_dirtyMaterial)
        {
            m_dirtyMaterial = false;

            m_virtualUBO = uboManager.ReAllocateUBO(m_virtualUBO, pShader->GetUBOBlockSize(), pShader->GetSamplersCount());

            if (m_virtualUBO != SR_ID_INVALID) {
                uboManager.BindUBO(m_virtualUBO);
            }
            else {
                m_pipeline->ResetDescriptorSet();
                m_hasErrors = true;
                return;
            }

            pShader->InitUBOBlock();
            pShader->Flush();

            m_material->UseSamplers();
            pShader->FlushSamplers();
        }

        switch (uboManager.BindUBO(m_virtualUBO)) {
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

    SR_HTYPES_NS::Marshal::Ptr Sprite2D::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = Super::Save(pMarshal, flags);

        pMarshal->Write(m_material ? m_material->GetResourceId() : "None");

        return pMarshal;
    }

    std::vector<uint32_t> Sprite2D::GetIndices() const {
        return SR_SPRITE_INDICES;
    }

    void Sprite2D::UseMaterial() {
        Super::UseMaterial();
        UseModelMatrix();
    }

    void Sprite2D::UseModelMatrix() {
        GetRenderContext()->GetCurrentShader()->SetMat4(SHADER_MODEL_MATRIX, m_modelMatrix);
        Super::UseModelMatrix();
    }

    SR_UTILS_NS::Component* Sprite2D::CopyComponent() const {
        return MeshComponent::CopyComponent();
    }
}