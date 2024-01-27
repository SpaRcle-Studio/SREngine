//
// Created by Monika on 30.07.2022.
//

#include <Graphics/Types/Geometry/Sprite.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Types/Uniforms.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Utils/MeshUtils.h>

namespace SR_GTYPES_NS {
    Sprite::Sprite()
        : Super(MeshType::Sprite)
    { }

    std::string Sprite::GetMeshIdentifier() const {
        static const std::string id = "SpriteFromMemory";
        return id;
    }

    bool Sprite::InitializeEntity() noexcept {
        m_properties.AddStandardProperty("Sliced", &m_sliced);

        m_properties.AddStandardProperty("Texture border", &m_textureBorder)
            .SetDrag(0.01f)
            .SetResetValue(0.15f)
            .SetActiveCondition([this]() { return m_sliced; })
            .SetWidth(90.f);

        m_properties.AddStandardProperty("Window border", &m_windowBorder)
            .SetDrag(0.01f)
            .SetResetValue(0.15f)
            .SetActiveCondition([this]() { return m_sliced; })
            .SetWidth(90.f);

        return Super::InitializeEntity();
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
            default: {
                m_hasErrors = true;
                return;
            }
        }
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

            if (m_sliced) {
                pShader->SetVec2(SHADER_SLICED_TEXTURE_BORDER, m_textureBorder);
                pShader->SetVec2(SHADER_SLICED_WINDOW_BORDER, m_windowBorder);
            }
        }
        else {
            SRHaltOnce("Shader is nullptr!");
        }
        Super::UseModelMatrix();
    }

    void Sprite::OnPriorityChanged() {
        ReRegisterMesh();
        Component::OnPriorityChanged();
    }
}