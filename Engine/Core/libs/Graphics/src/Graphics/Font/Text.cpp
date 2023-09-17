//
// Created by Monika on 14.02.2022.
//

#include <Utils/ECS/Transform.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Locale/Encoding.h>

#include <Graphics/Font/Text.h>
#include <Graphics/Font/Font.h>
#include <Graphics/Font/TextBuilder.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/RenderScene.h>

namespace SR_GTYPES_NS {
    SR_REGISTER_COMPONENT(Text);

    Text::Text()
        : Mesh(MeshType::Static)
    { }

    Text::~Text() {
        SetFont(nullptr);
    }

    void Text::Draw() {
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

            EVK_PUSH_LOG_LEVEL(EvoVulkan::Tools::LogLevel::ErrorsOnly);

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

            EVK_POP_LOG_LEVEL();
        }

        switch (m_uboManager.BindUBO(m_virtualUBO)) {
            case Memory::UBOManager::BindResult::Duplicated:
                pShader->InitUBOBlock();
                pShader->Flush();
                UseSamplers();
                SR_FALLTHROUGH;
            case Memory::UBOManager::BindResult::Success:
                m_pipeline->Draw(6);
                break;
            case Memory::UBOManager::BindResult::Failed:
            default:
                break;
        }
    }

    bool Text::Calculate() {
        if (IsCalculated()) {
            return true;
        }

        if (m_hasErrors || !IsCalculatable()) {
            return false;
        }

        if (!BuildAtlas()) {
            SR_ERROR("Text::Calculate() : failed to build atlas!");
            return false;
        }

        return Mesh::Calculate();
    }

    void Text::FreeVideoMemory() {
        if (m_id != SR_ID_INVALID) {
            SRVerifyFalse(!m_pipeline->FreeTexture(&m_id));
        }

        Mesh::FreeVideoMemory();
    }

    bool Text::BuildAtlas() {
        if (!m_font) {
            SR_ERROR("Text::BuildAtlas() : missing font!");
            return false;
        }

        if (m_id != SR_ID_INVALID) {
            SRVerifyFalse(!m_pipeline->FreeTexture(&m_id));
        }

        TextBuilder textBuilder(m_font);
        textBuilder.SetKerning(m_kerning);
        textBuilder.SetDebug(m_debug);
        textBuilder.SetCharSize(m_fontSize);

        if (!textBuilder.Build(m_text)) {
            return false;
        }

        m_width = textBuilder.GetWidth();
        m_height = textBuilder.GetHeight();

        SR_GRAPH_NS::SRTextureCreateInfo textureCreateInfo;

        textureCreateInfo.pData = textBuilder.GetData();
        textureCreateInfo.format = textBuilder.GetColorFormat();
        textureCreateInfo.width = m_width;
        textureCreateInfo.height = m_height;
        textureCreateInfo.compression = TextureCompression::None;
        textureCreateInfo.filter = TextureFilter::NEAREST;
        textureCreateInfo.mipLevels = 1;
        textureCreateInfo.cpuUsage = false;
        textureCreateInfo.alpha = true;

        EVK_PUSH_LOG_LEVEL(EvoVulkan::Tools::LogLevel::ErrorsOnly);

        m_id = m_pipeline->AllocateTexture(textureCreateInfo);

        EVK_POP_LOG_LEVEL();

        if (m_id == SR_ID_INVALID) {
            SR_ERROR("Text::BuildAtlas() : failed to build the font atlas!");
            return false;
        }

        return true;
    }

    SR_UTILS_NS::Component* Text::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        auto&& pMesh = new Text();

        SR_MAYBE_UNUSED const auto&& type = static_cast<MeshType>(marshal.Read<int32_t>());

        pMesh->m_fontSize = marshal.Read<SR_MATH_NS::UVector2>();
        pMesh->m_localization = marshal.Read<bool>();
        pMesh->m_preprocessor = marshal.Read<bool>();
        pMesh->m_kerning = marshal.Read<bool>();
        pMesh->m_debug = marshal.Read<bool>();

        const auto&& material = marshal.Read<std::string>();
        if (material != "None") {
            if (auto&& pMaterial = SR_GTYPES_NS::Material::Load(SR_UTILS_NS::Path(material, true))) {
                pMesh->SetMaterial(pMaterial);
            }
            else {
                SR_ERROR("Text::LoadComponent() : failed to load material! Name: " + material);
            }
        }

        const auto&& font = marshal.Read<std::string>();
        if (font != "None") {
            if (auto&& pFont = SR_GTYPES_NS::Font::Load(SR_UTILS_NS::Path(font, true))) {
                pMesh->SetFont(pFont);
            }
            else {
                SR_ERROR("Text::LoadComponent() : failed to load font! Name: " + font);
            }
        }

        pMesh->m_text = marshal.Read<SR_HTYPES_NS::UnicodeString>();

        return dynamic_cast<Component*>(pMesh);
    }

    void Text::UseMaterial() {
        Mesh::UseMaterial();
        UseModelMatrix();
    }

    void Text::UseModelMatrix() {
        GetRenderContext()->GetCurrentShader()->SetMat4(SHADER_MODEL_MATRIX, m_modelMatrix);
        GetRenderContext()->GetCurrentShader()->SetFloat(SHADER_TEXT_RECT_X, 0.f);
        GetRenderContext()->GetCurrentShader()->SetFloat(SHADER_TEXT_RECT_Y, 0.f);
        GetRenderContext()->GetCurrentShader()->SetFloat(SHADER_TEXT_RECT_WIDTH, m_width / 100.f);
        GetRenderContext()->GetCurrentShader()->SetFloat(SHADER_TEXT_RECT_HEIGHT, m_height / 100.f);

        Mesh::UseModelMatrix();
    }

    void Types::Text::OnMatrixDirty() {
        if (auto&& pTransform = GetTransform()) {
            m_modelMatrix = pTransform->GetMatrix();
        }
        else {
            m_modelMatrix = SR_MATH_NS::Matrix4x4::Identity();
        }

        Component::OnMatrixDirty();
    }

    Mesh::RenderScenePtr Text::GetRenderScene() {
        if (!m_renderScene.Valid()) {
            auto&& pScene = TryGetScene();
            if (!pScene) {
                return m_renderScene;
            }

            m_renderScene = pScene->Do<RenderScenePtr>([](SR_WORLD_NS::Scene* ptr) {
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
        GetRenderScene().Do([this](SR_GRAPH_NS::RenderScene *ptr) {
            ptr->Register(this);
        });

        Component::OnAttached();
    }

    void Text::OnDestroy() {
        RenderScene::Ptr renderScene = GetRenderScene();

        Component::OnDestroy();

        /// если ресурс уничтожится сразу, то обрабатывать это нужно в контексте SharedPtr
        if (!IsGraphicsResourceRegistered()) {
            GetThis().DynamicCast<Text>().AutoFree([](auto&& pData) {
                pData->MarkMeshDestroyed();
            });
        }
        else {
            MarkMeshDestroyed();
        }

        if (renderScene) {
            renderScene->SetDirty();
        }
    }

    SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Text::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = Component::Save(pMarshal, flags);

        pMarshal->Write<int32_t>(static_cast<int32_t>(GetMeshType()));
        pMarshal->Write<SR_MATH_NS::UVector2>(m_fontSize);
        pMarshal->Write<bool>(m_localization);
        pMarshal->Write<bool>(m_preprocessor);
        pMarshal->Write<bool>(m_kerning);
        pMarshal->Write<bool>(m_debug);
        pMarshal->Write<std::string>(m_material ? m_material->GetResourceId() : "None");
        pMarshal->Write<std::string>(m_font ? m_font->GetResourceId() : "None");
        pMarshal->Write<SR_HTYPES_NS::UnicodeString>(m_text);

        return pMarshal;
    }

    void Text::UseSamplers() {
        GetRenderContext()->GetCurrentShader()->SetSampler2D(SHADER_TEXT_ATLAS_TEXTURE, m_id);
        Mesh::UseSamplers();
    }

    void Text::SetFont(Font *pFont) {
        if (pFont == m_font) {
            return;
        }

        if (m_font) {
            m_font->RemoveUsePoint();
        }

        if ((m_font = pFont)) {
            m_font->AddUsePoint();
        }

        m_isCalculated = false;

        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
    }

    void Text::SetFontSize(const SR_MATH_NS::UVector2& size)
    {
        m_fontSize = size;
        m_isCalculated = false;
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
    }

    void Text::SetText(const std::string &text) {
        m_text = SR_UTILS_NS::Locale::UtfToUtf<char32_t, char>(text);
        m_isCalculated = false;
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
    }

    void Text::SetText(const std::u16string &text) {
        m_text = SR_UTILS_NS::Locale::UtfToUtf<char32_t, char16_t>(text);
        m_isCalculated = false;
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
    }

    void Text::SetText(const std::u32string &text) {
        m_text = text;
        m_isCalculated = false;
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
    }

    bool Text::IsCalculatable() const {
        return Mesh::IsCalculatable() && !m_text.empty() && m_font;
    }

    void Text::OnLoaded() {
        Component::OnLoaded();
    }

    SR_UTILS_NS::Component* Text::CopyComponent() const {
        if (auto&& pComponent = dynamic_cast<Text*>(Component::CopyComponent())) {
            pComponent->SetText(m_text);
            pComponent->SetDebug(m_debug);
            pComponent->SetFont(m_font);
            pComponent->SetFontSize(m_fontSize);
            pComponent->SetKerning(m_kerning);
            return pComponent;
        }

        return nullptr;
    }

    void Text::SetKerning(bool enabled) {
        m_kerning = enabled;
        m_isCalculated = false;
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
    }

    void Text::SetDebug(bool enabled) {
        m_debug = enabled;
        m_isCalculated = false;
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
    }
}