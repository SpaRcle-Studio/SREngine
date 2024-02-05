//
// Created by Monika on 18.11.2023.
//

#include <Graphics/Pass/FlatColorBufferPass.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Pipeline/Pipeline.h>

namespace SR_GRAPH_NS {
    //SR_REGISTER_RENDER_PASS(FlatColorBufferPass)

    void FlatColorBufferPass::UseConstants(SR_GTYPES_NS::Shader* pShader) {
        Super::UseConstants(pShader);

        pShader->SetConstInt(SHADER_COLOR_BUFFER_MODE, 1);
    }

    SR_GTYPES_NS::Framebuffer* FlatColorBufferPass::GetColorFrameBuffer() const noexcept {
        return GetFramebuffer();
    }

    void FlatColorBufferPass::OnResize(const SR_MATH_NS::UVector2& size) {
        FlatClusterPass::OnResize(size);
    }

    void FlatColorBufferPass::Update() {
        if (!GetFramebuffer() || GetFramebuffer()->IsDirty() || !m_isFrameBufferRendered) {
            return;
        }

        ResetColorIndex();

        GetPassPipeline()->SetCurrentFrameBuffer(GetFramebuffer());

        auto&& pIdentifier = m_uboManager.GetIdentifier();
        m_uboManager.SetIdentifier(this);

        FlatClusterPass::Update();

        m_uboManager.SetIdentifier(pIdentifier);

        GetPassPipeline()->SetCurrentFrameBuffer(nullptr);
    }

    bool FlatColorBufferPass::Render() {
        m_isFrameBufferRendered = false;

        if (!GetFramebuffer()) {
            return false;
        }

        auto&& pIdentifier = m_uboManager.GetIdentifier();
        m_uboManager.SetIdentifier(this);

        if (GetFramebuffer()->Bind())
        {
            if (GetFramebuffer()->BeginCmdBuffer(GetClearColors(), GetClearDepth()))
            {
                GetFramebuffer()->BeginRender();
                GetFramebuffer()->SetViewportScissor();

                FlatClusterPass::Render();

                GetFramebuffer()->EndRender();
                GetFramebuffer()->EndCmdBuffer();

                m_isFrameBufferRendered = true;
            }
        }

        m_uboManager.SetIdentifier(pIdentifier);

        return false;
    }

    bool FlatColorBufferPass::Init() {
        return FlatClusterPass::Init();
    }

    bool FlatColorBufferPass::Load(const SR_XML_NS::Node& passNode) {
        LoadFramebufferSettings(passNode);
        return IMeshClusterPass::Load(passNode);
    }

    std::vector<SR_GTYPES_NS::Framebuffer *> FlatColorBufferPass::GetFrameBuffers() const {
        if (!GetFramebuffer()) {
            return std::vector<SR_GTYPES_NS::Framebuffer*>(); /// NOLINT
        }
        return { GetFramebuffer() };
    }

    void FlatColorBufferPass::UseUniforms(SR_GTYPES_NS::Shader* pShader, MeshPtr pMesh) {
        IncrementColorIndex();
        SetMeshIndex(pMesh, GetColorIndex());

        pShader->SetVec3(SHADER_COLOR_BUFFER_VALUE, GetMeshColor());

        Super::UseUniforms(pShader, pMesh);
    }
}
