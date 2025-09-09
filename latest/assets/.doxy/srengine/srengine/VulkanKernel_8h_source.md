

# File VulkanKernel.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pipeline**](dir_b95270d167403b29f5d572cffd5b214a.md) **>** [**Vulkan**](dir_f68684f6785c69ede334c05a5da1778e.md) **>** [**VulkanKernel.h**](VulkanKernel_8h.md)

[Go to the documentation of this file](VulkanKernel_8h.md)


```C++
//
// Created by Monika on 16.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_VULKAN_KERNEL_H
#define SR_ENGINE_GRAPHICS_VULKAN_KERNEL_H

#include <Graphics/macros.h>

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
        SR_NODISCARD bool SurfaceIsAvailable() const;

    private:
        void WaitFences() override;
        void WaitAllFences() override;
        void WaitDeviceIdle() override;

        EvoVulkan::Core::RenderResult Render() override;
        EvoVulkan::Core::FrameResult PrepareFrame() override;
        EvoVulkan::Core::FrameResult SubmitFrame() override;
        EvoVulkan::Core::FrameResult QueuePresent() override;
        EvoVulkan::Core::FrameResult WaitIdle() override;

    private:
        bool m_isSwapchainSuboptimal = false;
        PipelinePtr m_pipeline;

    };
}

#endif //SR_ENGINE_GRAPHICS_VULKAN_KERNEL_H
```


