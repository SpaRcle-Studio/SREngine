//
// Created by Monika on 14.02.2022.
//

#include <Utils/ECS/Transform.h>
#include <Utils/ECS/ComponentManager.h>

#include <Graphics/Font/Text.h>
#include <Graphics/Font/Font.h>
#include <Graphics/Font/TextBuilder.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Pipeline/Environment.h>

#include <EvoVulkan/Tools/VulkanDebug.h>

namespace SR_GTYPES_NS {
    SR_REGISTER_COMPONENT(Text);

    Text::Text()
        : Mesh(MeshType::Static)
    {
        SetMaterial(Material::Load("Engine/Materials/text.mat"));
        SetFont(Font::Load("Engine/Fonts/TsunagiGothic.ttf"));
        //SetFont(Font::Load("Engine/Fonts/Metropolitan.ttf"));
        SetFont(Font::Load("Engine/Fonts/seguiemj.ttf"));
        m_text = U"Heприветlloあにま😀 😬 😁 😂 😃 😄 😅 😆 😇 😉 😊 🙂 🙃 ☺️ \n😋 😌 👦🏻 👧🏻 👨🏻 👩🏻 👴🏻 👵🏻 👶🏻 👱🏻 👮🏻 👲🏻 👳🏻 👷🏻 👸🏻 💂🏻 🎅🏻 👼🏻 💆🏻 💇🏻\n🤣 🤠 🤡 🤥 🤤 🤢";
        //m_text = U"Hello.,_ World!";
        //m_text = U"Metropolitan";
        //m_text = U"_!";
        //m_text = U",";
        //m_text = U"Hello!";
    }

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

        EVK_PUSH_LOG_LEVEL(EvoVulkan::Tools::LogLevel::ErrorsOnly);

        if (m_id != SR_ID_INVALID) {
            SRVerifyFalse(!m_pipeline->FreeTexture(&m_id));
        }

        TextBuilder textBuilder(m_font);
        textBuilder.SetKerning(m_kerning);
        textBuilder.SetDebug(m_debug);

        if (!textBuilder.Build(m_text)) {
            return false;
        }

        m_width = textBuilder.GetWidth();
        m_height = textBuilder.GetHeight();

        m_id = m_pipeline->CalculateTexture(textBuilder.GetData(),
            textBuilder.GetColorFormat(), m_width, m_height, TextureFilter::NEAREST,
            TextureCompression::None, 1,
            true, false
        );

        EVK_POP_LOG_LEVEL();

        if (m_id == SR_ID_INVALID) {
            SR_ERROR("Text::BuildAtlas() : failed to build the font atlas!");
            return false;
        }

        return true;
    }

    SR_UTILS_NS::Component* Text::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        SR_MAYBE_UNUSED const auto&& type = static_cast<MeshType>(marshal.Read<int32_t>());

        const auto&& material = marshal.Read<std::string>();
        auto&& pMesh = new Text();

        if (pMesh && material != "None") {
            if (auto&& pMaterial = SR_GTYPES_NS::Material::Load(SR_UTILS_NS::Path(material, true))) {
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
            GetThis().DynamicCast<Mesh>().AutoFree([](auto&& pData) {
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

        pMarshal->Write(static_cast<int32_t>(GetMeshType()));
        pMarshal->Write(m_material ? m_material->GetResourceId() : "None");

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
    }

    void Text::SetText(const std::string &text) {
        m_text = SR_UTILS_NS::Locale::UtfToUtf<char32_t, char>(text);
        m_isCalculated = false;
        m_dirtyMaterial = true;
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
    }

    void Text::SetText(const std::u16string &text) {
        m_text = SR_UTILS_NS::Locale::UtfToUtf<char32_t, char16_t>(text);
        m_isCalculated = false;
        m_dirtyMaterial = true;
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
    }

    void Text::SetText(const std::u32string &text) {
        m_text = text;
        m_isCalculated = false;
        m_dirtyMaterial = true;
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
    }

    bool Text::IsCanCalculate() const {
        return Mesh::IsCanCalculate() && !m_text.empty();
    }

    void Text::OnLoaded() {
        Component::OnLoaded();
    }

    SR_UTILS_NS::Component* Text::CopyComponent() const {
        return Component::CopyComponent();
    }

    void Text::SetKerning(bool enabled) {
        m_kerning = enabled;
        m_isCalculated = false;
        if (m_pipeline) {
            m_pipeline->SetBuildState(false);
        }
    }

    void Text::SetDebug(bool enabled) {
        m_debug = enabled;
        m_isCalculated = false;
        if (m_pipeline) {
            m_pipeline->SetBuildState(false);
        }
    }
}