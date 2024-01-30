//
// Created by Monika on 21.01.2023.
//

#include <Graphics/Pass/IFramebufferPass.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Types/Framebuffer.h>

namespace SR_GRAPH_NS {
    IFramebufferPass::IFramebufferPass()
        : m_frameBufferUboManager(SR_GRAPH_NS::Memory::UBOManager::Instance())
    { }

    IFramebufferPass::~IFramebufferPass() {
        if (m_framebuffer) {
            m_framebuffer->RemoveUsePoint();
            m_framebuffer = nullptr;
        }
    }

    void IFramebufferPass::LoadFramebufferSettings(const SR_XML_NS::Node& passNode) {
        auto&& settingsNode = passNode.TryGetNode("FramebufferSettings");
        if (!settingsNode) {
            return;
        }

        m_isDirectional = settingsNode.TryGetAttribute("Directional").ToBool(false);

        m_dynamicResizing = settingsNode.TryGetAttribute("DynamicResizing").ToBool(true);
        m_depthEnabled = settingsNode.TryGetAttribute("DepthEnabled").ToBool(true);
        m_samples = settingsNode.TryGetAttribute("SmoothSamples").ToUInt(0);
        m_layersCount = SR_MAX(1, settingsNode.TryGetAttribute("Layers").ToUInt(1));

        m_depthAspect = ImageAspect::DepthStencil;

        for (auto&& subNode : settingsNode.GetNodes()) {
            /// color layers
            if (subNode.NameView() == "Layer") {
                m_colorFormats.emplace_back(SR_UTILS_NS::EnumReflector::FromString<ImageFormat>(subNode.TryGetAttribute("Format").ToString(
                        "RGBA8_UNORM"
                )));

                SR_MATH_NS::FColor clearColor;

                clearColor.r = subNode.TryGetAttribute("R").ToFloat(0.f);
                clearColor.g = subNode.TryGetAttribute("G").ToFloat(0.f);
                clearColor.b = subNode.TryGetAttribute("B").ToFloat(0.f);
                clearColor.a = subNode.TryGetAttribute("A").ToFloat(1.f);

                m_clearColors.emplace_back(clearColor);
            }
                /// depth layer
            else if (subNode.NameView() == "Depth") {
                m_depth = subNode.TryGetAttribute("ClearValue").ToFloat(1.f);

                m_depthFormat = SR_UTILS_NS::EnumReflector::FromString<ImageFormat>(subNode.TryGetAttribute("DepthFormat").ToString(
                    "Auto"
                ));

                m_depthAspect = SR_UTILS_NS::EnumReflector::FromString<ImageAspect>(subNode.TryGetAttribute("Aspect").ToString(
                    "DepthStencil"
                ));
            }
            else if (subNode.NameView() == "Size") {
                m_size.x = subNode.TryGetAttribute("X").ToInt(0);
                m_size.y = subNode.TryGetAttribute("Y").ToInt(0);
            }
            else if (subNode.NameView() == "PreScale") {
                m_preScale.x = subNode.TryGetAttribute("X").ToFloat(1.f);
                m_preScale.y = subNode.TryGetAttribute("Y").ToFloat(1.f);
            }
        }
    }

    bool IFramebufferPass::InitializeFramebuffer(RenderContext* pContext) {
        /// fix zero size
        if (m_size.x == 0) {
            m_size.x = static_cast<int32_t>(pContext->GetWindowSize().x);
        }

        if (m_size.y == 0) {
            m_size.y = static_cast<int32_t>(pContext->GetWindowSize().y);
        }

        /// pre scale size
        SR_MATH_NS::IVector2 size = {
                static_cast<int32_t>(static_cast<SR_MATH_NS::Unit>(m_size.x) * m_preScale.x),
                static_cast<int32_t>(static_cast<SR_MATH_NS::Unit>(m_size.y) * m_preScale.y),
        };

        SRAssert(!m_framebuffer);

        /// initialize framebuffer
        if ((m_framebuffer = SR_GTYPES_NS::Framebuffer::Create(m_colorFormats, m_depthFormat, size))) {
            m_framebuffer->SetLayersCount(m_layersCount);
            m_framebuffer->SetSampleCount(m_samples);
            m_framebuffer->SetDepthEnabled(m_depthEnabled);
            m_framebuffer->SetDepthAspect(m_depthAspect);
            m_framebuffer->AddUsePoint();
        }
        else {
            SR_ERROR("FramebufferPass::Init() : failed to create framebuffer!");
            return false;
        }

        if (m_framebuffer) {
            pContext->Register(m_framebuffer);
        }

        return true;
    }

    bool IFramebufferPass::RenderFrameBuffer(const PipelinePtr& pPipeline) {
        if (!m_framebuffer && !IsDirectional()) {
            return false;
        }

        m_framebuffer->Update();

        /// установим кадровый буфер, чтобы BeginCmdBuffer понимал какие значение для очистки ставить
        pPipeline->SetCurrentFrameBuffer(m_framebuffer);

        if (m_layersCount > 1) {
            return RenderFrameBuffer(pPipeline, m_layersCount);
        }

        auto&& pIdentifier = m_frameBufferUboManager.GetIdentifier();
        m_frameBufferUboManager.SetIdentifier(this);

        if (IsDirectional()) {
            RenderFrameBufferInner();
        }
        else if (m_framebuffer->Bind()) {
            m_framebuffer->BeginCmdBuffer(m_clearColors, m_depth);
            {
                m_framebuffer->BeginRender();
                m_framebuffer->SetViewportScissor();

                RenderFrameBufferInner();

                m_framebuffer->EndRender();
            }
            m_framebuffer->EndCmdBuffer();
        }

        pPipeline->SetCurrentFrameBuffer(nullptr);

        m_frameBufferUboManager.SetIdentifier(pIdentifier);

        return IsDirectional();
    }

    bool IFramebufferPass::RenderFrameBuffer(const PipelinePtr& pPipeline, uint8_t layers) {
        auto&& pIdentifier = m_frameBufferUboManager.GetIdentifier();
        m_frameBufferUboManager.SetIdentifier(this);

        m_framebuffer->BeginCmdBuffer(m_clearColors, m_depth);
        m_framebuffer->SetViewportScissor();

        for (uint32_t i = 0; i < layers; ++i) {
            m_currentFrameBufferLayer = i;
            pPipeline->SetFrameBufferLayer(i);

            if (m_framebuffer->Bind()) {
                m_framebuffer->BeginRender();
                RenderFrameBufferInner();
                m_framebuffer->EndRender();
            }
        }

        m_frameBufferUboManager.SetIdentifier(pIdentifier);

        m_framebuffer->EndCmdBuffer();

        pPipeline->SetCurrentFrameBuffer(nullptr);

        return IsDirectional();
    }

    void IFramebufferPass::ResizeFrameBuffer(const SR_MATH_NS::UVector2 &size) {
        if (m_dynamicResizing && m_framebuffer) {
            m_framebuffer->SetSize(SR_MATH_NS::IVector2(
                    static_cast<int32_t>(static_cast<SR_MATH_NS::Unit>(size.x) * m_preScale.x),
                    static_cast<int32_t>(static_cast<SR_MATH_NS::Unit>(size.y) * m_preScale.y)
            ));
        }
    }

    void IFramebufferPass::UpdateFrameBuffer(const PipelinePtr& pPipeline) {
        if (!IsDirectional() && (!m_framebuffer || m_framebuffer->IsDirty())) {
            return;
        }

        pPipeline->SetCurrentFrameBuffer(m_framebuffer);

        auto&& pIdentifier = m_frameBufferUboManager.GetIdentifier();
        m_frameBufferUboManager.SetIdentifier(this);

        for (uint32_t i = 0; i < m_layersCount; ++i) {
            m_currentFrameBufferLayer = i;
            pPipeline->SetFrameBufferLayer(i);
            UpdateFrameBufferInner();
        }

        m_frameBufferUboManager.SetIdentifier(pIdentifier);

        pPipeline->SetCurrentFrameBuffer(nullptr);
    }
}
