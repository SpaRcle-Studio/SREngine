//
// Created by Monika on 21.01.2023.
//

#include <Graphics/Pass/IFramebufferPass.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/FrameBufferController.h>
#include <Graphics/Types/Framebuffer.h>

namespace SR_GRAPH_NS {
    IFramebufferPass::IFramebufferPass()
        : m_frameBufferUboManager(SR_GRAPH_NS::Memory::UBOManager::Instance())
    { }

    void IFramebufferPass::LoadFramebufferSettings(const SR_XML_NS::Node& passNode) {
        auto&& settingsNode = passNode.TryGetNode("FramebufferSettings");
        if (!settingsNode) {
            return;
        }

        m_isDirectional = settingsNode.TryGetAttribute("Directional").ToBool(false);

        if (!m_isDirectional) {
            m_frameBufferName = settingsNode.GetAttribute("Name").ToString();
            m_frameBufferController = GetFrameBufferRenderTechnique()->GetFrameBufferController(m_frameBufferName);
            if (!m_frameBufferController) {
                SR_ERROR("IFramebufferPass::LoadFramebufferSettings() : failed to find frame buffer controller!\n\tName: " + m_frameBufferName.ToStringRef());
            }
        }

        for (auto&& subNode : settingsNode.GetNodes()) {
            /// color layers
            if (subNode.NameView() == "Layer") {
                SR_MATH_NS::FColor clearColor;

                clearColor.r = subNode.TryGetAttribute("R").ToFloat(0.f);
                clearColor.g = subNode.TryGetAttribute("G").ToFloat(0.f);
                clearColor.b = subNode.TryGetAttribute("B").ToFloat(0.f);
                clearColor.a = subNode.TryGetAttribute("A").ToFloat(1.f);

                m_clearColors.emplace_back(clearColor);
            }
                /// depth layer
            else if (subNode.NameView() == "Depth") {
                if (subNode.HasAttribute("ClearValue")) {
                    m_depth = subNode.GetAttribute("ClearValue").ToFloat(1.f);
                }
                else {
                    m_depth = std::nullopt;
                }
            }
        }
    }

    bool IFramebufferPass::RenderFrameBuffer(const PipelinePtr& pPipeline) {
        auto&& pFrameBuffer = GetFramebuffer();

        if (!pFrameBuffer && !IsDirectional()) {
            return false;
        }

        pFrameBuffer->Update();

        /// установим кадровый буфер, чтобы BeginCmdBuffer понимал какие значение для очистки ставить
        pPipeline->SetCurrentFrameBuffer(pFrameBuffer);

        if (GetLayersCount() > 1) {
            return RenderFrameBuffer(pPipeline, GetLayersCount());
        }

        auto&& pIdentifier = m_frameBufferUboManager.GetIdentifier();
        m_frameBufferUboManager.SetIdentifier(this);

        if (IsDirectional()) {
            RenderFrameBufferInner();
        }
        else if (pFrameBuffer->Bind()) {
            pFrameBuffer->BeginCmdBuffer(m_clearColors, m_depth);
            {
                pFrameBuffer->BeginRender();
                pFrameBuffer->SetViewportScissor();

                RenderFrameBufferInner();

                pFrameBuffer->EndRender();
            }
            pFrameBuffer->EndCmdBuffer();
        }

        pPipeline->SetCurrentFrameBuffer(nullptr);

        m_frameBufferUboManager.SetIdentifier(pIdentifier);

        return IsDirectional();
    }

    bool IFramebufferPass::RenderFrameBuffer(const PipelinePtr& pPipeline, uint8_t layers) {
        auto&& pFrameBuffer = GetFramebuffer();
        auto&& pIdentifier = m_frameBufferUboManager.GetIdentifier();

        m_frameBufferUboManager.SetIdentifier(this);

        pFrameBuffer->BeginCmdBuffer(m_clearColors, m_depth);
        pFrameBuffer->SetViewportScissor();

        for (uint32_t i = 0; i < layers; ++i) {
            m_currentFrameBufferLayer = i;
            pPipeline->SetFrameBufferLayer(i);

            if (pFrameBuffer->Bind()) {
                pFrameBuffer->BeginRender();
                RenderFrameBufferInner();
                pFrameBuffer->EndRender();
            }
        }

        m_frameBufferUboManager.SetIdentifier(pIdentifier);

        pFrameBuffer->EndCmdBuffer();

        pPipeline->SetCurrentFrameBuffer(nullptr);

        return IsDirectional();
    }

    void IFramebufferPass::UpdateFrameBuffer(const PipelinePtr& pPipeline) {
        auto&& pFrameBuffer = GetFramebuffer();
        if (!IsDirectional() && (!pFrameBuffer || pFrameBuffer->IsDirty())) {
            return;
        }

        pPipeline->SetCurrentFrameBuffer(pFrameBuffer);

        auto&& pIdentifier = m_frameBufferUboManager.GetIdentifier();
        m_frameBufferUboManager.SetIdentifier(this);

        for (uint32_t i = 0; i < GetLayersCount(); ++i) {
            m_currentFrameBufferLayer = i;
            pPipeline->SetFrameBufferLayer(i);
            UpdateFrameBufferInner();
        }

        m_frameBufferUboManager.SetIdentifier(pIdentifier);

        pPipeline->SetCurrentFrameBuffer(nullptr);
    }

    IFramebufferPass::FramebufferPtr IFramebufferPass::GetFramebuffer() const noexcept {
        return m_frameBufferController ? m_frameBufferController->GetFramebuffer() : nullptr;
    }

    uint8_t IFramebufferPass::GetLayersCount() const noexcept {
        return m_frameBufferController ? m_frameBufferController->GetLayersCount() : 1;
    }
}
