//
// Created by Monika on 14.02.2022.
//

#include <Graphics/Font/Text.h>
#include <Utils/ECS/Transform.h>

namespace SR_GTYPES_NS {
    Text::Text()
        : Super(MeshType::Static)
    {
        Component::InitComponent<Text>();
        SetMaterial(Material::Load("Engine/Materials/text.mat"));
    }

    void Text::Draw() {
        auto&& pShader = m_context->GetCurrentShader();

        if (!pShader || !IsActive() || IsDestroyed()) {
            return;
        }

        if ((!m_isCalculated && !Calculate()) || m_hasErrors) {
            return;
        }

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

            UseSamplers();
        }

        switch (m_uboManager.BindUBO(m_virtualUBO)) {
            case Memory::UBOManager::BindResult::Duplicated:
                pShader->InitUBOBlock();
                pShader->Flush();
                UseSamplers();
                SR_FALLTHROUGH;
            case Memory::UBOManager::BindResult::Success:
                m_pipeline->DrawIndices(6);
                break;
            case Memory::UBOManager::BindResult::Failed:
            default:
                break;
        }
    }

    SR_UTILS_NS::IResource* Text::Copy(SR_UTILS_NS::IResource* destination) const{
        return Mesh::Copy(destination);
    }

    bool Text::Calculate() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_isCalculated) {
            return true;
        }

        if (m_hasErrors || !IsCanCalculate()) {
            return false;
        }

        if (!BuildAtlas()) {
            SR_ERROR("Text::Calculate() : failed to build atlas!");
            return false;
        }

        return Mesh::Calculate();
    }

    void Text::FreeVideoMemory() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_id != SR_ID_INVALID) {
            SRVerifyFalse(!m_pipeline->FreeTexture(&m_id));
        }

        Mesh::FreeVideoMemory();
    }

    bool Text::BuildAtlas() {
        if (m_id != SR_ID_INVALID) {
            SRVerifyFalse(!m_pipeline->FreeTexture(&m_id));
        }

        SR_GRAPH_NS::Font font;
        font.Load();
        std::u32string str = U"Heприветlloあにま👼は申し訳ありません➦приветxccvxc�� ��⊆�� \x02\x01\b \xff\xff\xff ";
        font.Init(str, 32, 1, 4, 4, 0, 255, 0);

        m_width = font.GetWidth();
        m_height = font.GetHeight();

        m_id = m_pipeline->CalculateTexture(font.GetData(),
                ColorFormat::RGBA8_UNORM, m_width, m_height, TextureFilter::NEAREST,
                TextureCompression::None, 1,
                true, false
        );

        if (m_id == SR_ID_INVALID) {
            SR_ERROR("Text::BuildAtlas() : failed to build the font atlas!");
            return false;
        }

        return true;
    }

    SR_UTILS_NS::Component* Text::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        const auto &&type = static_cast<MeshType>(marshal.Read<int32_t>());

        const auto &&material = marshal.Read<std::string>();
        auto &&pMesh = new Text();

        if (pMesh && material != "None") {
            if (auto&& pMaterial = Types::Material::Load(SR_UTILS_NS::Path(material, true))) {
                pMesh->SetMaterial(pMaterial);
            }
            else {
                SR_ERROR("Text::LoadComponent() : failed to load material! Name: " + material);
            }
        }

        return dynamic_cast<Component*>(pMesh);
    }

    void Text::UseMaterial() {
        Mesh::UseMaterial();
        UseModelMatrix();
    }

    void Text::UseModelMatrix() {
        m_context->GetCurrentShader()->SetMat4(SHADER_MODEL_MATRIX, m_modelMatrix);
        Mesh::UseModelMatrix();
    }

    SR_UTILS_NS::Path Text::GetResourcePath() const {
        static SR_UTILS_NS::Path path;
        return path;
    }

    void Types::Text::OnMatrixDirty() {
        if (auto&& pTransform = GetTransform()) {
            m_modelMatrix = pTransform->GetMatrix();
        }
        else {
            SRHalt("Component have not transform, but OnMatrixDirty was called!");
        }

        Component::OnMatrixDirty();
    }

    Mesh::RenderScenePtr Text::GetRenderScene() {
        if (!m_renderScene.Valid()) {
            m_renderScene = TryGetScene().Do<RenderScenePtr>([](SR_WORLD_NS::Scene* ptr) {
                return ptr->GetDataStorage().GetValue<RenderScenePtr>();
            }, RenderScenePtr());
        }

        return m_renderScene;
    }

    void Text::OnEnable() {
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
        Component::OnEnable();
    }

    void Text::OnDisable() {
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
        Component::OnDisable();
    }

    void Text::OnAttached() {
        AddUsePoint();

        GetRenderScene().Do([this](SR_GRAPH_NS::RenderScene *ptr) {
            ptr->Register(this);
        });

        Component::OnAttached();
    }

    void Text::OnDestroy() {
        Component::OnDestroy();

        auto&& renderScene = GetRenderScene();

        /// после вызова данная сущность может быть уничтожена
        RemoveUsePoint();

        renderScene->SetDirty();
    }

    SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Text::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = Component::Save(pMarshal, flags);

        pMarshal->Write(static_cast<int32_t>(m_type));
        pMarshal->Write(m_material ? m_material->GetResourceId() : "None");

        return pMarshal;
    }

    void Text::UseSamplers() {
        m_context->GetCurrentShader()->SetSampler2D(SHADER_TEXT_ATLAS_TEXTURE, m_id);
        Mesh::UseSamplers();
    }
}