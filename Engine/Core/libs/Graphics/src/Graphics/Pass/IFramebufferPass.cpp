//
// Created by Monika on 21.01.2023.
//

#include <Graphics/Pass/IFramebufferPass.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Types/Framebuffer.h>

namespace SR_GRAPH_NS {
    IFramebufferPass::IFramebufferPass()
        : m_preScale(SR_MATH_NS::FVector2(1.f))
        , m_depth(1.f)
        , m_depthFormat(ImageFormat::Unknown)
    { }

    IFramebufferPass::~IFramebufferPass() {
        if (m_framebuffer) {
            m_framebuffer->RemoveUsePoint();
            m_framebuffer = nullptr;
        }
    }

    void IFramebufferPass::LoadFramebufferSettings(const SR_XML_NS::Node& settingsNode) {
        m_dynamicResizing = settingsNode.TryGetAttribute("DynamicResizing").ToBool(true);
        m_depthEnabled = settingsNode.TryGetAttribute("DepthEnabled").ToBool(true);
        m_samples = settingsNode.TryGetAttribute("SmoothSamples").ToUInt(0);
        m_layersCount = settingsNode.TryGetAttribute("Layers").ToUInt(1);

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
            m_size.x = pContext->GetWindowSize().x;
        }

        if (m_size.y == 0) {
            m_size.y = pContext->GetWindowSize().y;
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

    void IFramebufferPass::ResizeFrameBuffer(const SR_MATH_NS::UVector2 &size) {
        if (m_dynamicResizing && m_framebuffer) {
            m_framebuffer->SetSize(SR_MATH_NS::IVector2(
                    static_cast<SR_MATH_NS::Unit>(size.x) * m_preScale.x,
                    static_cast<SR_MATH_NS::Unit>(size.y) * m_preScale.y
            ));
        }
    }
}
