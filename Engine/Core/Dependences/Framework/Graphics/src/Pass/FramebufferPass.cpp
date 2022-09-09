//
// Created by Monika on 22.07.2022.
//

#include <Pass/FramebufferPass.h>
#include <Types/Framebuffer.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(FramebufferPass)

    FramebufferPass::FramebufferPass(RenderTechnique *pTechnique)
        : GroupPass(pTechnique)
        , m_preScale(SR_MATH_NS::FVector2(1.f))
        , m_depth(1.f)
        , m_depthFormat(DepthFormat::Unknown)
    { }

    FramebufferPass::~FramebufferPass() {
        if (m_framebuffer) {
            m_framebuffer->RemoveUsePoint();
            m_framebuffer = nullptr;
        }
    }

    bool FramebufferPass::Load(const SR_XML_NS::Node &passNode) {
        LoadSettings(passNode.TryGetNode("Settings"));

        bool result = GroupPass::Load(passNode.TryGetNode("Passes"));

        m_name = passNode.TryGetAttribute("Name").ToString(passNode.Name());

        return result;
    }

    bool FramebufferPass::PreRender() {
        GroupPass::PreRender();
        return false;
    }

    bool FramebufferPass::Render() {
        if (!m_framebuffer) {
            return false;
        }

        if (m_framebuffer->Bind() && m_framebuffer->BeginRender(m_clearColors, m_depth)) {
            GroupPass::Render();
            m_framebuffer->EndRender();
        }

        /// Независимо от того, отрисовали мы что-то в кадровый буффер или нет,
        /// все равно возвращаем false (hasDrawData), так как технически, кадровый буффер
        /// не несет данных для рендера.
        return false;
    }

    bool FramebufferPass::PostRender() {
        GroupPass::PostRender();
        return false;
    }

    void FramebufferPass::OnResize(const SR_MATH_NS::IVector2 &size) {
        if (m_dynamicResizing && m_framebuffer) {
            m_framebuffer->SetSize(SR_MATH_NS::IVector2(
                    static_cast<SR_MATH_NS::Unit>(size.x) * m_preScale.x,
                    static_cast<SR_MATH_NS::Unit>(size.y) * m_preScale.y
            ));
        }

        GroupPass::OnResize(size);
    }

    bool FramebufferPass::Init() {
        bool result = GroupPass::Init();

        /// fix zero size
        if (m_size.x == 0) {
            m_size.x = m_context->GetWindowSize().x;
        }

        if (m_size.y == 0) {
            m_size.y = m_context->GetWindowSize().y;
        }

        /// pre scale size
        SR_MATH_NS::IVector2 size = {
                static_cast<int32_t>(static_cast<SR_MATH_NS::Unit>(m_size.x) * m_preScale.x),
                static_cast<int32_t>(static_cast<SR_MATH_NS::Unit>(m_size.y) * m_preScale.y),
        };

        /// initialize framebuffer
        if (!(m_framebuffer = SR_GTYPES_NS::Framebuffer::Create(m_colorFormats, m_depthFormat, size))) {
            SR_ERROR("FramebufferPass::Init() : failed to create framebuffer!");
        }
        else {
            m_framebuffer->AddUsePoint();
        }

        if (m_framebuffer) {
            m_context->Register(m_framebuffer);
        }

        return result;
    }

    void FramebufferPass::Update() {
        if (!m_framebuffer) {
            return;
        }

        GroupPass::Update();
    }

    FramebufferPass::FramebufferPtr FramebufferPass::GetFramebuffer() const {
        return m_framebuffer;
    }

    void FramebufferPass::LoadSettings(const Helper::Xml::Node &settingsNode) {
        m_dynamicResizing = settingsNode.TryGetAttribute("DynamicResizing").ToBool(true);

        for (auto&& subNode : settingsNode.GetNodes()) {
            /// color layers
            if (subNode.NameView() == "Layer") {
                m_colorFormats.emplace_back(SR_UTILS_NS::EnumReflector::FromString<ColorFormat>(subNode.TryGetAttribute("Format").ToString(
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

                m_depthFormat = SR_UTILS_NS::EnumReflector::FromString<DepthFormat>(subNode.TryGetAttribute("DepthFormat").ToString(
                        "Auto"
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
}