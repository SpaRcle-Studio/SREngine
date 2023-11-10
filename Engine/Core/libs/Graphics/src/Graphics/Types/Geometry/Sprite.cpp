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
    { }

    std::string Sprite::GetMeshIdentifier() const {
        static const std::string id = "SpriteFromMemory";
        return id;
    }

    SR_UTILS_NS::Component* Sprite::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) { //Нафига dataStorage, если он не используется, чёртов полиморфизм
        SR_MAYBE_UNUSED const auto&& type = static_cast<MeshType>(marshal.Read<int32_t>());

        const auto&& material = marshal.Read<std::string>();

        auto&& pSprite = SR_UTILS_NS::ComponentManager::Instance().CreateComponent<Sprite>();

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

    SR_UTILS_NS::Component* Sprite::CopyComponent() const {
        return MeshComponent::CopyComponent();
    }

    void Sprite::OnPriorityDirty() {
        if (auto&& pRenderScene = GetRenderScene()) {
            pRenderScene->GetFlatCluster().MarkDirty();
        }
        Component::OnPriorityDirty();
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

        m_properties.AddEnumProperty("Mesh type", &m_meshType).SetReadOnly();

        auto&& materialContainer = m_properties.AddContainer("Material");

        materialContainer.AddCustomProperty<SR_UTILS_NS::PathProperty>("Path")
            .AddFileFilter("Material", "mat")
            .SetGetter([this]()-> SR_UTILS_NS::Path {
                 return m_material ? m_material->GetResourcePath() : SR_UTILS_NS::Path();
            })
            .SetSetter([this](const SR_UTILS_NS::Path& path) {
                SetMaterial(path);
            });

        materialContainer.AddCustomProperty<SR_UTILS_NS::ExternalProperty>("Material")
            .SetPropertyGetter([this]() -> SR_UTILS_NS::Property* { return m_material ? &m_material->GetProperties() : nullptr; })
            .SetActiveCondition([this]() -> bool { return m_material; })
            .SetReadOnly();

        return Component::InitializeEntity();
    }
}