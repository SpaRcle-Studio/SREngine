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

        IncrementColorIndex();

        pShader->SetConstInt(SHADER_COLOR_BUFFER_MODE, 1);
        pShader->SetConstVec3(SHADER_COLOR_BUFFER_VALUE, GetMeshColor());
    }

    SR_GTYPES_NS::Framebuffer* FlatColorBufferPass::GetColorFrameBuffer() const noexcept {
        return GetFramebuffer();
    }

    void FlatColorBufferPass::Update() {
        if (!m_framebuffer || m_framebuffer->IsDirty()) {
            return;
        }

        m_pipeline->SetCurrentFrameBuffer(m_framebuffer);

        auto&& pIdentifier = m_uboManager.GetIdentifier();
        m_uboManager.SetIdentifier(this);

        FlatClusterPass::Update();

        m_uboManager.SetIdentifier(pIdentifier);

        m_pipeline->SetCurrentFrameBuffer(nullptr);
    }

    bool FlatColorBufferPass::Render() {
        ResetColorIndex();

        if (!m_framebuffer) {
            return false;
        }

        auto&& pIdentifier = m_uboManager.GetIdentifier();
        m_uboManager.SetIdentifier(this);

        if (m_framebuffer->Bind()) {
            m_framebuffer->BeginCmdBuffer(m_clearColors, 1.f);
            {
                m_framebuffer->BeginRender();
                m_framebuffer->SetViewportScissor();

                FlatClusterPass::Render();

                m_framebuffer->EndRender();
            }
            m_framebuffer->EndCmdBuffer();
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
}
