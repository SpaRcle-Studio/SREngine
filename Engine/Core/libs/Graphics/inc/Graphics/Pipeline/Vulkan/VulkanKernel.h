//
// Created by Monika on 16.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_VULKAN_KERNEL_H
#define SR_ENGINE_GRAPHICS_VULKAN_KERNEL_H

#include <Utils/Types/SharedPtr.h>
#include <EvoVulkan/VulkanKernel.h>

namespace SR_GRAPH_NS {
    class Pipeline;

    class VulkanKernel : public EvoVulkan::Core::VulkanKernel {
        using Super = EvoVulkan::Core::VulkanKernel;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
    public:
        explicit VulkanKernel(PipelinePtr pPipeline);
        ~VulkanKernel() override = default;

    public:
        bool OnResize() override;

        void PollWindowEvents() override;

        SR_NODISCARD bool IsWindowValid() const override;
        SR_NODISCARD bool IsRayTracingRequired() const noexcept override;

        bool BuildCmdBuffers() override {
            return true;
        }

        bool OnComplete() override {
            return true;
        }

        void SetGUIEnabled(bool enabled) override;

        bool Destroy() override {
            return EvoVulkan::Core::VulkanKernel::Destroy();
        }

    private:
        EvoVulkan::Core::RenderResult Render() override;
        EvoVulkan::Core::FrameResult PrepareFrame() override;
        EvoVulkan::Core::FrameResult SubmitFrame() override;
        EvoVulkan::Core::FrameResult QueuePresent() override;
        EvoVulkan::Core::FrameResult WaitIdle() override;

    private:
        PipelinePtr m_pipeline;

    };
}

#endif //SR_ENGINE_GRAPHICS_VULKAN_KERNEL_H
