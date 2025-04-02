

# File VulkanKernel.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pipeline**](dir_5b8a811d805f0a9bb3b25de386a42645.md) **>** [**Vulkan**](dir_8e9bc433d1305450ae178a7c83320a15.md) **>** [**VulkanKernel.h**](VulkanKernel_8h.md)

[Go to the documentation of this file](VulkanKernel_8h.md)


```C++
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
```


