//
// Created by Monika on 15.09.2023.
//

#include <Graphics/Pipeline/Vulkan/VulkanPipeline.h>

#include <EvoVulkan/VulkanKernel.h>

#ifdef SR_USE_IMGUI
    #include <Graphics/Overlay/VulkanImGuiOverlay.h>
#endif

namespace SR_GRAPH_NS {
    std::string VulkanPipeline::GetVendor() const {
         return m_kernel ? m_kernel->GetDevice()->GetName() : "Invalid";
    }

    VulkanPipeline::~VulkanPipeline() {
        SR_SAFE_DELETE_PTR(m_kernel);
    }

    bool VulkanPipeline::InitOverlay() {
    #ifdef SR_USE_IMGUI
        auto&& pImGuiOverlay = m_overlays[OverlayType::ImGui];
        pImGuiOverlay = new VulkanImGuiOverlay(GetThis());
        if (!pImGuiOverlay->Init()) {
            SR_ERROR("VulkanPipeline::InitOverlay() : failed to initialize ImGui overlay!");
            return false;
        }
    #endif

        return Pipeline::InitOverlay();
    }

    bool VulkanPipeline::Destroy() {
        if (m_kernel) {
            m_kernel->Destroy();
        }

        return Super::Destroy();
    }

    bool VulkanPipeline::PreInit(const PipelinePreInitInfo& info) {
        auto&& GetUsedMemoryFn = [pPipeline = GetThis()]() -> uint32_t {
            return pPipeline ? pPipeline->GetUsedMemory() / 1024 / 1024 : 0;
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().LogCallback = [GetUsedMemoryFn](const std::string& msg) {
            SR_VULKAN_LOG(SR_FORMAT("{%i} %s", GetUsedMemoryFn(), msg.c_str()));
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().WarnCallback = [GetUsedMemoryFn](const std::string& msg) {
            SR_WARN(SR_FORMAT("{%i} %s", GetUsedMemoryFn(), msg.c_str()));
        };
        EvoVulkan::Tools::VkFunctionsHolder::Instance().ErrorCallback = [GetUsedMemoryFn](const std::string& msg) {
            SR_VULKAN_ERROR(SR_FORMAT("{%i} %s", GetUsedMemoryFn(), msg.c_str()));
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().GraphCallback = [GetUsedMemoryFn](const std::string& msg) {
            SR_VULKAN_MSG(SR_FORMAT("{%i} %s", GetUsedMemoryFn(), msg.c_str()));
        };

        EvoVulkan::Tools::VkFunctionsHolder::Instance().AssertCallback = [GetUsedMemoryFn](const std::string &msg) {
            SRHalt(SR_FORMAT("{%i} %s", GetUsedMemoryFn(), msg.c_str()));
            return false;
        };

        return Pipeline::PreInit(info);
    }

    uint64_t VulkanPipeline::GetUsedMemory() const {
        return m_kernel->GetAllocator() ? m_kernel->GetAllocator()->GetGPUMemoryUsage() : 0;
    }
}