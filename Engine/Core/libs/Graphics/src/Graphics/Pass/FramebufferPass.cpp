//
// Created by Monika on 22.07.2022.
//

#include <Graphics/Pass/FramebufferPass.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Pipeline/Pipeline.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(FramebufferPass)

    bool FramebufferPass::Load(const SR_XML_NS::Node &passNode) {
        LoadFramebufferSettings(passNode.TryGetNode("FramebufferSettings"));

        bool result = GroupPass::Load(passNode.TryGetNode("Passes"));

        SetName(passNode.TryGetAttribute("Name").ToString(passNode.Name()));

        return result;
    }

    bool FramebufferPass::PreRender() {
        GroupPass::PreRender();
        return false;
    }

    bool FramebufferPass::Render() {
        if (!m_framebuffer) {
            m_isFrameBufferRendered = false;
            return false;
        }

        if (!m_framebuffer->Bind()) {
            m_isFrameBufferRendered = false;
            return false;
        }

        if (!m_framebuffer->BeginCmdBuffer(m_clearColors, m_depth)) {
            m_isFrameBufferRendered = false;
            return false;
        }

        if (m_framebuffer->BeginRender()) {
            m_framebuffer->SetViewportScissor();
            GroupPass::Render();
            m_framebuffer->EndRender();
            m_framebuffer->EndCmdBuffer();
        }

        GetPassPipeline()->SetCurrentFrameBuffer(nullptr);

        m_isFrameBufferRendered = true;

        /// Независимо от того, отрисовали мы что-то в кадровый буффер или нет,
        /// все равно возвращаем false (hasDrawData), так как технически, кадровый буффер
        /// не несет данных для рендера.
        return false;
    }

    bool FramebufferPass::PostRender() {
        GroupPass::PostRender();
        return false;
    }

    void FramebufferPass::OnResize(const SR_MATH_NS::UVector2 &size) {
        IFramebufferPass::ResizeFrameBuffer(size);
        GroupPass::OnResize(size);
    }

    bool FramebufferPass::Init() {
        return GroupPass::Init() && InitializeFramebuffer(GetContext());
    }

    void FramebufferPass::Update() {
        if (!m_framebuffer || m_framebuffer->IsDirty()) {
            return;
        }

        if (!m_isFrameBufferRendered) {
            return;
        }

        GetPassPipeline()->SetCurrentFrameBuffer(m_framebuffer);

        GroupPass::Update();

        GetPassPipeline()->SetCurrentFrameBuffer(nullptr);
    }

    std::vector<SR_GTYPES_NS::Framebuffer*> FramebufferPass::GetFrameBuffers() const {
        if (!m_framebuffer) {
            return std::vector<SR_GTYPES_NS::Framebuffer*>(); /// NOLINT
        }
        return { m_framebuffer };
    }
}