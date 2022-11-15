//
// Created by Monika on 10.10.2022.
//

#include <Graphics/Pass/ColorBufferPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(ColorBufferPass)

    ColorBufferPass::ColorBufferPass(RenderTechnique *pTechnique, BasePass* pParent)
        : BasePass(pTechnique, pParent)
    { }

    ColorBufferPass::~ColorBufferPass() {
        for (auto&& pShader : m_shaders) {
            if (!pShader) {
                continue;
            }

            pShader->RemoveUsePoint();
            pShader = nullptr;
        }

        if (m_framebuffer) {
            m_framebuffer->RemoveUsePoint();
            m_framebuffer = nullptr;
        }
    }

    bool ColorBufferPass::Load(const SR_XML_NS::Node &passNode) {
        LoadSettings(passNode.TryGetNode("Settings"));
        return BasePass::Load(passNode);
    }

    void ColorBufferPass::LoadSettings(const SR_XML_NS::Node &settingsNode) {
        m_directional = settingsNode.GetAttribute("Directional").ToBool(false);
        m_depthEnabled = settingsNode.TryGetAttribute("DepthEnabled").ToBool(true);
        m_samples = settingsNode.TryGetAttribute("SmoothSamples").ToUInt(0);

        for (auto&& subNode : settingsNode.GetNodes()) {
            if (subNode.NameView() == "PreScale") {
                m_preScale.x = subNode.TryGetAttribute("X").ToFloat(1.f);
                m_preScale.y = subNode.TryGetAttribute("Y").ToFloat(1.f);
            }
        }
    }

    bool ColorBufferPass::PreRender() {
        return BasePass::PreRender();
    }

    bool ColorBufferPass::Render() {
        if (!m_framebuffer) {
            return false;
        }

        auto&& pRenderScene = GetRenderScene();

        auto&& pIdentifier = m_uboManager.GetIdentifier();
        m_uboManager.SetIdentifier(this);

        if (m_directional) {
            SR_MAYBE_UNUSED bool hasDrawData = DrawCluster(&pRenderScene->GetOpaque());
            hasDrawData |= DrawCluster(&pRenderScene->GetTransparent());
        }
        else if (m_framebuffer->Bind() && m_framebuffer->BeginRender(SR_MATH_NS::FColor(0.0), 1.f)) {
            DrawCluster(&pRenderScene->GetOpaque());
            DrawCluster(&pRenderScene->GetTransparent());
            m_framebuffer->EndRender();
        }

        //auto&& colorId = m_framebuffer->GetColorTexture(0);

        m_uboManager.SetIdentifier(pIdentifier);

        return m_directional;
    }

    void ColorBufferPass::Update() {
        if (!m_camera) {
            return;
        }

        m_colorId = 0;

        auto&& pRenderScene = GetRenderScene();

        auto&& pIdentifier = m_uboManager.GetIdentifier();
        m_uboManager.SetIdentifier(this);

        UpdateCluster(&pRenderScene->GetOpaque());
        UpdateCluster(&pRenderScene->GetTransparent());

        m_uboManager.SetIdentifier(pIdentifier);

        BasePass::Update();
    }

    ColorBufferPass::ShaderPtr ColorBufferPass::GetShader(SRSL::ShaderType type) const {
        switch (type) {
            case SRSL::ShaderType::Canvas:
                return m_shaders[0];
            case SRSL::ShaderType::Spatial:
            case SRSL::ShaderType::SpatialCustom:
                return m_shaders[1];
            case SRSL::ShaderType::Skybox:
            case SRSL::ShaderType::Simple:
                return m_shaders[2];
            case SRSL::ShaderType::Particles:
            case SRSL::ShaderType::Custom:
            case SRSL::ShaderType::Animation:
            case SRSL::ShaderType::PostProcessing:
            case SRSL::ShaderType::Line:
            case SRSL::ShaderType::Compute:
            case SRSL::ShaderType::Unknown:
            default:
                return nullptr;
        }
    }

    void ColorBufferPass::OnResize(const SR_MATH_NS::IVector2 &size) {
        if (m_framebuffer) {
            m_framebuffer->SetSize(SR_MATH_NS::IVector2(
                    static_cast<SR_MATH_NS::Unit>(size.x) * m_preScale.x,
                    static_cast<SR_MATH_NS::Unit>(size.y) * m_preScale.y
            ));
        }

        BasePass::OnResize(size);
    }

    bool ColorBufferPass::Init() {
        if (!m_directional && GetParentPass()) {
            SR_ERROR("ColorBufferPass::Init() : if the rendering pass of the color buffer is not directional, then it cannot be nested!");
            return BasePass::Init() && false;
        }

        bool result = BasePass::Init();

        m_shaders[0] = SR_GTYPES_NS::Shader::Load("Engine/Shaders/ColorBuffer/canvas.srsl");
        m_shaders[1] = SR_GTYPES_NS::Shader::Load("Engine/Shaders/ColorBuffer/spatial.srsl");
        m_shaders[2] = SR_GTYPES_NS::Shader::Load("Engine/Shaders/ColorBuffer/simple.srsl");

        for (auto&& pShader : m_shaders) {
            if (!pShader) {
                continue;
            }

            pShader->AddUsePoint();
        }

        auto&& window_size = m_context->GetWindowSize();

        SR_MATH_NS::IVector2 size = {
                static_cast<int32_t>(static_cast<SR_MATH_NS::Unit>(window_size.x) * m_preScale.x),
                static_cast<int32_t>(static_cast<SR_MATH_NS::Unit>(window_size.y) * m_preScale.y),
        };

        if (!(m_framebuffer = SR_GTYPES_NS::Framebuffer::Create({ ColorFormat::RG8_UNORM }, DepthFormat::Auto, size))) {
            SR_ERROR("ColorBufferPass::Init() : failed to create framebuffer!");
        }
        else {
            m_framebuffer->SetSampleCount(m_samples);
            m_framebuffer->SetDepthEnabled(m_depthEnabled);
            m_framebuffer->AddUsePoint();
        }

        if (m_framebuffer) {
            m_context->Register(m_framebuffer);
        }

        return result;
    }

    bool ColorBufferPass::DrawCluster(MeshCluster* pCluster) {
        if (!pCluster || pCluster->Empty()) {
            return false;
        }

        for (auto&&[_, subCluster] : *pCluster) {
            auto&& pShader = GetShader(subCluster.GetShaderType());
            if (!pShader || (pShader && !pShader->Use())) {
                continue;
            }

            for (auto&& [key, meshGroup] : subCluster) {
                (*meshGroup.begin())->BindMesh();

                for (auto&& pMesh : meshGroup) {
                    pMesh->Draw();
                }
            }

            pShader->UnUse();
        }

        return true;
    }

    void ColorBufferPass::UpdateCluster(MeshCluster *pCluster) {
        for (auto const& [_, subCluster] : *pCluster) {
            auto&& pShader = GetShader(subCluster.GetShaderType());
            if (!pShader || !pShader->Ready()) {
                continue;
            }

            m_context->SetCurrentShader(pShader);

            /**
             * TODO: нужно сделать что-то вроде SetSharedMat4, который будет биндить не в BLOCK а в SHARED_BLOCK
             */
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());

            for (auto const& [key, meshGroup] : subCluster) {
                for (const auto &pMesh : meshGroup) {
                    if (!pMesh->IsMeshActive()) {
                        continue;
                    }

                    auto&& virtualUbo = pMesh->GetVirtualUBO();
                    if (virtualUbo == SR_ID_INVALID) {
                        continue;
                    }

                    pMesh->UseModelMatrix();

                    ++m_colorId;
                    SetMeshIndex(pMesh, m_colorId);

                    auto&& color = SR_MATH_NS::HEXToBGR(m_colorId).Cast<SR_MATH_NS::Unit>();

                    pShader->SetVec3(SR_COMPILE_TIME_CRC32_STR("color"), color.ToGLM() / 255.f);

                    if (m_uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
                        SR_ERROR("ColorBufferPass::Update() : memory has been duplicated!");
                    }

                    pShader->Flush();
                }
            }
        }

        m_context->SetCurrentShader(nullptr);
    }

    SR_MATH_NS::FColor ColorBufferPass::GetColor(float_t x, float_t y) const {
        if (x < 0 || x > 1 || y < 0 || y > 1) {
            return SR_MATH_NS::FColor(0.f);
        }

        if (!m_framebuffer || m_directional) {
            return SR_MATH_NS::FColor(0.f);
        }

        auto&& textureId = m_framebuffer->GetColorTexture(0);

        const uint32_t xPos = m_framebuffer->GetWidth() * x;
        const uint32_t yPos = m_framebuffer->GetHeight() * y;

        return m_context->GetPipeline()->GetPixelColor(textureId, xPos, yPos);
    }

    SR_GTYPES_NS::Mesh *ColorBufferPass::GetMesh(float_t x, float_t y) const {
        auto&& color = GetColor(x, y);

        auto&& colorIndex = SR_MATH_NS::BGRToHEX(SR_MATH_NS::IVector3(
                static_cast<int32_t>(color.x),
                static_cast<int32_t>(color.y),
                static_cast<int32_t>(color.z)
        ));

        if (colorIndex > m_table.size() || colorIndex == 0) {
            return nullptr;
        }

        return m_table[colorIndex - 1];
    }

    void ColorBufferPass::SetMeshIndex(ColorBufferPass::MeshPtr pMesh, uint32_t colorId) {
        /// 0 - черный цвет, отсутствие мешей
        if (colorId == 0) {
            SRHalt("ColorBufferPass::SetMeshIndex() : invalid index!");
            return;
        }

        if (m_colorId - 1 >= m_table.size()) {
            if (m_table.empty()) {
                m_table.resize(32);
            }
            else {
                m_table.resize(m_table.size() * 2);
            }
        }

        m_table[m_colorId - 1] = pMesh;
    }

    uint32_t ColorBufferPass::GetIndex(float_t x, float_t y) const {
        auto&& color = GetColor(x, y);

        auto&& colorIndex = SR_MATH_NS::BGRToHEX(SR_MATH_NS::IVector3(
                static_cast<int32_t>(color.x),
                static_cast<int32_t>(color.y),
                static_cast<int32_t>(color.z)
        ));

        return colorIndex;
    }
}
