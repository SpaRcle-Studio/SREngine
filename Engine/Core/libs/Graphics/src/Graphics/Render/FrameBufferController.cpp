//
// Created by Monika on 04.02.2024.
//

#include <Graphics/Render/FrameBufferController.h>
#include <Graphics/Types/Framebuffer.h>

namespace SR_GRAPH_NS {
    FrameBufferController::FrameBufferController()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Manually)
    { }

    FrameBufferController::~FrameBufferController() {
        if (m_framebuffer) {
            m_framebuffer->RemoveUsePoint();
            m_framebuffer = nullptr;
        }
    }

    void FrameBufferController::OnResize(const SR_MATH_NS::UVector2& size) {
        if (m_dynamicResizing && m_framebuffer) {
            m_framebuffer->SetSize(SR_MATH_NS::IVector2(
                    static_cast<int32_t>(static_cast<SR_MATH_NS::Unit>(size.x) * m_preScale.x),
                    static_cast<int32_t>(static_cast<SR_MATH_NS::Unit>(size.y) * m_preScale.y)
            ));
        }
    }

    bool FrameBufferController::InitializeFramebuffer(RenderContext* pContext) {
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
            m_framebuffer->SetFeatures(m_features);
            m_framebuffer->AddUsePoint();
        }
        else {
            SR_ERROR("FrameBufferController::Init() : failed to create framebuffer!");
            return false;
        }

        if (m_framebuffer) {
            pContext->Register(m_framebuffer);
        }

        return true;
    }


    bool FrameBufferController::LoadFramebufferSettings(const SR_XML_NS::Node& settingsNode) {
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
            }
            /// depth layer
            else if (subNode.NameView() == "Depth") {
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
            else if (subNode.NameView() == "Features") {
                m_features.depthShaderRead = subNode.TryGetAttribute("DepthShaderRead").ToBool(m_features.depthShaderRead);
                m_features.colorShaderRead = subNode.TryGetAttribute("ColorShaderRead").ToBool(m_features.colorShaderRead);
                m_features.depthLoad = subNode.TryGetAttribute("DepthLoad").ToBool(m_features.depthLoad);
                m_features.colorLoad = subNode.TryGetAttribute("ColorLoad").ToBool(m_features.colorLoad);
                m_features.transferSrcDepth = subNode.TryGetAttribute("TransferSrcDepth").ToBool(m_features.transferSrcDepth);
                m_features.transferSrcColor = subNode.TryGetAttribute("TransferSrcColor").ToBool(m_features.transferSrcColor);
                m_features.transferDstDepth = subNode.TryGetAttribute("TransferDstDepth").ToBool(m_features.transferDstDepth);
                m_features.transferDstColor = subNode.TryGetAttribute("TransferDstColor").ToBool(m_features.transferDstColor);
            }
        }

        return true;
    }
}