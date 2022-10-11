//
// Created by Monika on 10.10.2022.
//

#include <Graphics/Pass/ColorBufferPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(ColorBufferPass)

    ColorBufferPass::ColorBufferPass(RenderTechnique *pTechnique)
        : BasePass(pTechnique)
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
            bool hasDrawData = DrawCluster(&pRenderScene->GetOpaque());
            hasDrawData |= DrawCluster(&pRenderScene->GetTransparent());
        }
        else if (m_framebuffer->Bind() && m_framebuffer->BeginRender(SR_MATH_NS::FColor(0.0), 1.f)) {
            DrawCluster(&pRenderScene->GetOpaque());
            DrawCluster(&pRenderScene->GetTransparent());
            m_framebuffer->EndRender();
        }

        m_uboManager.SetIdentifier(pIdentifier);

        return m_directional;
    }

    void ColorBufferPass::Update() {
        if (!m_camera) {
            return;
        }

        m_color = SR_MATH_NS::IVector3(0);

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

        /// TODO: переделать на RGB8_UNORM
        if (!(m_framebuffer = SR_GTYPES_NS::Framebuffer::Create({ ColorFormat::RGBA8_UNORM }, DepthFormat::Auto, size))) {
            SR_ERROR("ColorBufferPass::Init() : failed to create framebuffer!");
        }
        else {
            m_framebuffer->AddUsePoint();
        }

        if (m_framebuffer) {
            m_context->Register(m_framebuffer);
        }

        return result;
    }

    bool ColorBufferPass::DrawCluster(MeshCluster* pCluster) {
        auto &&pipeline = GetPipeline();

        if (!pCluster || pCluster->Empty()) {
            return false;
        }

        for (auto&&[_, subCluster] : *pCluster) {
            auto&& pShader = GetShader(subCluster.GetShaderType());
            if (!pShader || pShader && !pShader->Use()) {
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
        auto&& pipeline = GetPipeline();

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
                for (const auto &mesh : meshGroup) {
                    if (!mesh->IsMeshActive()) {
                        continue;
                    }

                    auto&& virtualUbo = mesh->GetVirtualUBO();
                    if (virtualUbo == SR_ID_INVALID) {
                        continue;
                    }

                    mesh->UseModelMatrix();

                    NextColor();

                    pShader->SetVec3(SR_COMPILE_TIME_CRC32_STR("color"), m_color.ToGLM() / 255.f);

                    if (m_uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
                        SR_ERROR("ColorBufferPass::Update() : memory has been duplicated!");
                    }

                    pShader->Flush();
                }
            }
        }

        m_context->SetCurrentShader(nullptr);
    }

    void ColorBufferPass::NextColor() {
        const int modifier = 50;

        m_color.x += modifier;

        if (m_color.x >= 255) {
            m_color.x = 0;
            m_color.y += modifier;
        }

        if (m_color.y >= 255) {
            m_color.y = 0;
            m_color.z += modifier;
        }
    }
}
