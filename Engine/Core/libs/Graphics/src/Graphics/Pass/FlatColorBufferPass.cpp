//
// Created by Monika on 18.11.2023.
//

#include <Graphics/Pass/FlatColorBufferPass.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Pipeline/Pipeline.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(FlatColorBufferPass)

    void FlatColorBufferPass::UseConstants(SR_GTYPES_NS::Shader* pShader) {
        Super::UseConstants(pShader);

        pShader->SetConstInt(SHADER_COLOR_BUFFER_MODE, 1);
    }

    SR_GTYPES_NS::Framebuffer* FlatColorBufferPass::GetColorFrameBuffer() const noexcept {
        return GetFramebuffer();
    }

    void FlatColorBufferPass::OnResize(const SR_MATH_NS::UVector2& size) {
        IFramebufferPass::ResizeFrameBuffer(size);
        FlatClusterPass::OnResize(size);
    }

    void FlatColorBufferPass::Update() {
        if (!m_framebuffer || m_framebuffer->IsDirty() || !m_isFrameBufferRendered) {
            return;
        }

        ResetColorIndex();

        GetPassPipeline()->SetCurrentFrameBuffer(m_framebuffer);

        auto&& pIdentifier = m_uboManager.GetIdentifier();
        m_uboManager.SetIdentifier(this);

        FlatClusterPass::Update();

        m_uboManager.SetIdentifier(pIdentifier);

        GetPassPipeline()->SetCurrentFrameBuffer(nullptr);
    }

    bool FlatColorBufferPass::Render() {
        m_isFrameBufferRendered = false;

        if (!m_framebuffer) {
            return false;
        }

        auto&& pIdentifier = m_uboManager.GetIdentifier();
        m_uboManager.SetIdentifier(this);

        if (m_framebuffer->Bind())
        {
            if (m_framebuffer->BeginCmdBuffer(m_clearColors, m_depth))
            {
                m_framebuffer->BeginRender();
                m_framebuffer->SetViewportScissor();

                FlatClusterPass::Render();

                m_framebuffer->EndRender();
                m_framebuffer->EndCmdBuffer();

                m_isFrameBufferRendered = true;
            }
        }

        m_uboManager.SetIdentifier(pIdentifier);

        return false;
    }

    bool FlatColorBufferPass::Init() {
        return FlatClusterPass::Init() && InitializeFramebuffer(GetContext());
    }

    bool FlatColorBufferPass::Load(const SR_XML_NS::Node& passNode) {
        LoadFramebufferSettings(passNode.TryGetNode("FramebufferSettings"));
        return IMeshClusterPass::Load(passNode);
    }

    std::vector<SR_GTYPES_NS::Framebuffer *> FlatColorBufferPass::GetFrameBuffers() const {
        if (!m_framebuffer) {
            return std::vector<SR_GTYPES_NS::Framebuffer*>(); /// NOLINT
        }
        return { m_framebuffer };
    }

    void FlatColorBufferPass::UseUniforms(SR_GTYPES_NS::Shader* pShader, MeshPtr pMesh) {
        IncrementColorIndex();
        SetMeshIndex(pMesh, GetColorIndex());

        pShader->SetVec3(SHADER_COLOR_BUFFER_VALUE, GetMeshColor());

        Super::UseUniforms(pShader, pMesh);
    }
}
