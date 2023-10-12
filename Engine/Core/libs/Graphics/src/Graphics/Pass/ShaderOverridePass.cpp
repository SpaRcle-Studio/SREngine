//
// Created by Monika on 21.01.2023.
//

#include <Graphics/Pass/ShaderOverridePass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(ShaderOverridePass)

    ShaderOverridePass::~ShaderOverridePass() {
        for (auto&& [type, pShader] : m_shaders) {
            if (!pShader) {
                continue;
            }

            pShader->RemoveUsePoint();
            pShader = nullptr;
        }

        m_shaders.clear();

        if (m_framebuffer) {
            m_framebuffer->RemoveUsePoint();
            m_framebuffer = nullptr;
        }
    }

    bool ShaderOverridePass::Load(const SR_XML_NS::Node& passNode) {
        LoadFramebufferSettings(passNode.TryGetNode("FramebufferSettings"));

        m_isDirectional = passNode.GetAttribute("Directional").ToBool(false);

        for (auto&& subNode : passNode.GetNodes()) {
            if (subNode.NameView() == "PreScale") {
                m_preScale.x = subNode.TryGetAttribute("X").ToFloat(1.f);
                m_preScale.y = subNode.TryGetAttribute("Y").ToFloat(1.f);
            }
        }

        if (auto&& shadersNode = passNode.TryGetNode("Shaders")) {
            for (auto&& overrideNode : shadersNode.TryGetNodes("Override")) {
                if (auto&& pShader = SR_GTYPES_NS::Shader::Load(overrideNode.GetAttribute("Path").ToString())) {
                    m_shaders.emplace_back(std::make_pair(
                            SR_UTILS_NS::EnumReflector::FromString<SR_SRSL_NS::ShaderType>(overrideNode.GetAttribute("Type").ToString()),
                            pShader
                    ));
                }
            }
        }

        for (auto&& [type, pShader] : m_shaders) {
            if (!pShader) {
                continue;
            }

            pShader->AddUsePoint();
        }

        return BasePass::Load(passNode);
    }

    void ShaderOverridePass::OnResize(const SR_MATH_NS::UVector2 &size) {
        IFramebufferPass::ResizeFrameBuffer(size);
        BasePass::OnResize(size);
    }

    bool ShaderOverridePass::Init() {
        return BasePass::Init() && (IsDirectional() || InitializeFramebuffer(GetContext()));
    }

    bool ShaderOverridePass::Render() {
        if (!m_framebuffer && !IsDirectional()) {
            return false;
        }

        auto&& pIdentifier = m_uboManager.GetIdentifier();
        m_uboManager.SetIdentifier(this);

        if (IsDirectional()) {
            Super::Render();
        }
        else if (m_framebuffer->Bind()) {
            m_framebuffer->BeginCmdBuffer(m_clearColors, 1.f);
            {
                m_framebuffer->BeginRender();
                m_framebuffer->SetViewportScissor();

                Super::Render();

                m_framebuffer->EndRender();
            }
            m_framebuffer->EndCmdBuffer();
        }

        m_uboManager.SetIdentifier(pIdentifier);

        return IsDirectional();
    }

    void ShaderOverridePass::Update() {
        if (!IsDirectional() && (!m_framebuffer || m_framebuffer->IsDirty())) {
            return;
        }

        m_pipeline->SetCurrentFrameBuffer(m_framebuffer);

        auto&& pRenderScene = GetRenderScene();

        auto&& pIdentifier = m_uboManager.GetIdentifier();
        m_uboManager.SetIdentifier(this);

        Super::Update();

        m_uboManager.SetIdentifier(pIdentifier);

        m_pipeline->SetCurrentFrameBuffer(nullptr);
    }

    ShaderOverridePass::ShaderPtr ShaderOverridePass::GetShader(SR_SRSL_NS::ShaderType type) const {
        for (auto&& [shaderType, pShader] : m_shaders) {
            if (shaderType == type) {
                return pShader;
            }
        }

        return nullptr;
    }

    void ShaderOverridePass::UseSharedUniforms(ShaderOverridePass::ShaderPtr pShader) {
        if (m_camera) {
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());
            pShader->SetVec3(SHADER_VIEW_DIRECTION, m_camera->GetViewDirection());
        }
        Super::UseSharedUniforms(pShader);
    }

    std::vector<SR_GTYPES_NS::Framebuffer*> ShaderOverridePass::GetFrameBuffers() const {
        if (!m_framebuffer) {
            return std::vector<SR_GTYPES_NS::Framebuffer*>();
        }
        return { m_framebuffer };
    }
}
