//
// Created by Monika on 16.09.2023.
//

#include <Graphics/Pipeline/Vulkan/VulkanKernel.h>

namespace SR_GRAPH_NS {
    VulkanKernel::VulkanKernel(VulkanKernel::PipelinePtr pPipeline)
        : Super()
        , m_pipeline(std::move(pPipeline))
    { }

    bool VulkanKernel::OnResize()  {
        vkQueueWaitIdle(m_device->GetQueues()->GetGraphicsQueue());
        vkDeviceWaitIdle(*m_device);

        if (m_pipeline) {
            m_pipeline->SetDirty(true);
            if (m_GUIEnabled) {
                m_pipeline->ReCreateOverlay();
            }
        }

        return true;
    }

    bool VulkanKernel::IsWindowValid() const {
        if (!m_pipeline) {
            return false;
        }

        return m_pipeline->GetWindow().Do<bool>([](Window* pWindow) -> bool {
            return pWindow->IsValid();
        }, false);
    }

    void VulkanKernel::SetGUIEnabled(bool enabled) {
        if (m_pipeline) {
            m_pipeline->SetOverlaySurfaceDirty();
        }
        Super::SetGUIEnabled(enabled);
    }

    EvoVulkan::Core::RenderResult VulkanKernel::Render()  {
        SR_TRACY_ZONE;

        if (!m_swapchain->SurfaceIsAvailable()) {
            return EvoVulkan::Core::RenderResult::Success;
        }

        auto&& prepareResult = PrepareFrame();
        switch (prepareResult) {
            case EvoVulkan::Core::FrameResult::OutOfDate:
            case EvoVulkan::Core::FrameResult::Suboptimal:
            case EvoVulkan::Core::FrameResult::Dirty: {
                VK_LOG("SRVulkan::Render() : out of date...");
                m_hasErrors |= !ReCreate(prepareResult);

                if (m_hasErrors) {
                    return EvoVulkan::Core::RenderResult::Fatal;
                }

                VK_LOG("SRVulkan::Render() : window are successfully resized!");

                return EvoVulkan::Core::RenderResult::Success;
            }
            case EvoVulkan::Core::FrameResult::Success:
                break;
            default:
                SRHalt("SRVulkan::Render() : unexcepted behaviour!");
                return EvoVulkan::Core::RenderResult::Error;
        }

        for (auto&& submitInfo : m_submitQueue) {
            SR_TRACY_ZONE_S("QueueSubmit");

            auto&& vkSubmitInfo = submitInfo.ToVk();

            if (auto result = vkQueueSubmit(m_device->GetQueues()->GetGraphicsQueue(), 1, &vkSubmitInfo, VK_NULL_HANDLE); result != VK_SUCCESS) {
                VK_ERROR("renderFunction() : failed to queue submit (frame buffer)! Reason: " + EvoVulkan::Tools::Convert::result_to_description(result));

                if (result == VK_ERROR_DEVICE_LOST) {
                    return EvoVulkan::Core::RenderResult::DeviceLost;
                }

                return EvoVulkan::Core::RenderResult::Error;
            }
        }

        auto&& pImGuiOverlay = m_pipeline->GetOverlay(OverlayType::ImGui).DynamicCast<VulkanImGuiOverlay>();

        m_submitInfo.commandBuffers.clear();

        m_submitInfo.commandBuffers.emplace_back(m_drawCmdBuffs[m_currentBuffer]);

        if (m_GUIEnabled && pImGuiOverlay && !pImGuiOverlay->IsSurfaceDirty()) {
            m_submitInfo.commandBuffers.emplace_back(pImGuiOverlay->Render(m_currentBuffer));

            /// AddSubmitQueue(vkImgui->GetSubmitInfo(
            ///      GetSubmitInfo().signalSemaphoreCount,
            ///      GetSubmitInfo().pSignalSemaphores
            /// ));
        }

        {
            SR_TRACY_ZONE_S("GraphicsQueueSubmit");

            auto&& vkSubmitInfo = m_submitInfo.ToVk();

            /// Submit to queue
            if (auto result = vkQueueSubmit(m_device->GetQueues()->GetGraphicsQueue(), 1, &vkSubmitInfo, VK_NULL_HANDLE); result != VK_SUCCESS) {
                VK_ERROR("renderFunction() : failed to queue submit! Reason: " + EvoVulkan::Tools::Convert::result_to_description(result));

                if (result == VK_ERROR_DEVICE_LOST) {
                    SR_PLATFORM_NS::Terminate();
                }

                return EvoVulkan::Core::RenderResult::Error;
            }
        }

        switch (SubmitFrame()) {
            case EvoVulkan::Core::FrameResult::Success:
                return EvoVulkan::Core::RenderResult::Success;

            case EvoVulkan::Core::FrameResult::Error:
                return EvoVulkan::Core::RenderResult::Error;

            case EvoVulkan::Core::FrameResult::OutOfDate: {
                m_hasErrors |= !ReCreate(EvoVulkan::Core::FrameResult::OutOfDate);

                if (m_hasErrors) {
                    return EvoVulkan::Core::RenderResult::Fatal;
                }
                else {
                    return EvoVulkan::Core::RenderResult::Success;
                }
            }
            case EvoVulkan::Core::FrameResult::DeviceLost:
                SR_PLATFORM_NS::Terminate();

            default: {
                SRAssertOnce(false);
                return EvoVulkan::Core::RenderResult::Fatal;
            }
        }
    }

    bool VulkanKernel::IsRayTracingRequired() const noexcept {
    #ifdef SR_ANDROID
        return false;
    #else
        return SR_UTILS_NS::Features::Instance().Enabled("RayTracing", false);
    #endif
    }

    EvoVulkan::Core::FrameResult VulkanKernel::PrepareFrame() {
        SR_TRACY_ZONE;
        return Super::PrepareFrame();
    }

    EvoVulkan::Core::FrameResult VulkanKernel::SubmitFrame() {
        SR_TRACY_ZONE;
        return Super::SubmitFrame();
    }

    EvoVulkan::Core::FrameResult VulkanKernel::QueuePresent() {
        SR_TRACY_ZONE;
        return Super::QueuePresent();
    }

    EvoVulkan::Core::FrameResult VulkanKernel::WaitIdle() {
        SR_TRACY_ZONE;
        return Super::WaitIdle();
    }

    void VulkanKernel::PollWindowEvents() {
        if (!m_pipeline) {
            return;
        }

        m_pipeline->GetWindow().Do([](Window* pWindow) {
            pWindow->PollEvents();
        });
    }
}