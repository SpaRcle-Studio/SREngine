//
// Created by Monika on 30.07.2022.
//

#include <Graphics/Types/Geometry/Sprite.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Types/Uniforms.h>
#include <Graphics/Types/Shader.h>

namespace SR_GTYPES_NS {
    SR_REGISTER_COMPONENT(Sprite)

    Sprite::Sprite()
        : Super(MeshType::Sprite)
    {  }

    std::string Sprite::GetMeshIdentifier() const {
        static const std::string id = "SpriteFromMemory";
        return id;
    }

    SR_UTILS_NS::Component* Sprite::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) { //Нафига dataStorage, если он не используется, чёртов полиморфизм
        SR_MAYBE_UNUSED const auto&& type = static_cast<MeshType>(marshal.Read<int32_t>());

        const auto&& material = marshal.Read<std::string>();

        auto&& pSprite = new Sprite();

        if (material != "None") {
            if (auto&& pMaterial = SR_GTYPES_NS::Material::Load(material)) {
                pSprite->SetMaterial(pMaterial);
            }
            else {
                SR_ERROR("Sprite::LoadComponent() : failed to load material! Name: " + material)
            }
        }

        return pSprite;
    }

    bool Sprite::Calculate() {
        if (IsCalculated()) {
            return true;
        }

        FreeVideoMemory();

        if (!IsCalculatable()) {
            return false;
        }

        if (!CalculateVBO<Vertices::VertexType::UIVertex, Vertices::UIVertex>([]() { return SR_SPRITE_VERTICES; })) {
            return false;
        }

        return IndexedMesh::Calculate();
    }

    void Sprite::Draw() {
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

        const auto result = uboManager.BindUBO(m_virtualUBO);
        switch (result) {
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
            default: {
                m_hasErrors = true;
                return;
            }
        }
    }

    SR_HTYPES_NS::Marshal::Ptr Sprite::Save(SR_UTILS_NS::SavableSaveData data) const {
        auto&& pMarshal = Super::Save(data);

        pMarshal->Write(m_material ? m_material->GetResourceId() : "None");

        return pMarshal;
    }

    std::vector<uint32_t> Sprite::GetIndices() const {
        return SR_SPRITE_INDICES;
    }

    void Sprite::UseMaterial() {
        Super::UseMaterial();
        UseModelMatrix();
    }

    void Sprite::UseModelMatrix() {
        if (auto&& pShader = GetRenderContext()->GetCurrentShader()) {
            pShader->SetMat4(SHADER_MODEL_MATRIX, m_modelMatrix);
        }
        else {
            SRHaltOnce("Shader is nullptr!");
        }
        Super::UseModelMatrix();
    }

    SR_UTILS_NS::Component* Sprite::CopyComponent() const {
        return MeshComponent::CopyComponent();
    }
}