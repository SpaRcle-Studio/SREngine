//
// Created by Monika on 15.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_VULKAN_PIPELINE_H
#define SR_ENGINE_GRAPHICS_VULKAN_PIPELINE_H

#include <Graphics/Pipeline/Pipeline.h>

namespace EvoVulkan::Core {
    class VulkanKernel;
}

namespace SR_GRAPH_NS {
    class VulkanPipeline : public Pipeline {
        using Super = Pipeline;
    public:
        explicit VulkanPipeline(const RenderContextPtr& pContext)
            : Super(pContext)
        { }

        ~VulkanPipeline() override;

    public:
        bool InitOverlay() override;

        bool PreInit(const PipelinePreInitInfo& info) override;
        bool Destroy() override;

    public:
        SR_NODISCARD PipelineType GetType() const noexcept override { return PipelineType::Vulkan; }

        SR_NODISCARD std::string GetVendor() const override;
        SR_NODISCARD std::string GetRenderer() const override { return "Vulkan"; }
        SR_NODISCARD std::string GetVersion() const override { return "VK_API_VERSION_1_3"; }

        SR_NODISCARD EvoVulkan::Core::VulkanKernel* GetKernel() const noexcept { return m_kernel; }
        SR_NODISCARD uint64_t GetUsedMemory() const override;

    private:
        EvoVulkan::Core::VulkanKernel* m_kernel = nullptr;

    };
}

#endif //SR_ENGINE_GRAPHICS_VULKAN_PIPELINE_H
