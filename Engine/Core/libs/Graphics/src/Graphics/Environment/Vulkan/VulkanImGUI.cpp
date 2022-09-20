//
// Created by Nikita on 01.07.2021.
//

#include <Utils/GUI.h>

#include <EvoVulkan/Types/DescriptorPool.h>

#include <Graphics/Environment/Vulkan/VulkanImGUI.h>

int CreatePlatformSurface(ImGuiViewport* pv, ImU64 vk_inst, const void* vk_allocators, ImU64* out_vk_surface) {
    VkWin32SurfaceCreateInfoKHR sci;
    PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;

    vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(reinterpret_cast<VkInstance>(vk_inst), "vkCreateWin32SurfaceKHR");
    if (!vkCreateWin32SurfaceKHR) {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    memset(&sci, 0, sizeof(sci));
    sci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    sci.hinstance = GetModuleHandle(NULL);
    sci.hwnd = static_cast<HWND>(pv->PlatformHandle);

    VkResult err = vkCreateWin32SurfaceKHR(reinterpret_cast<VkInstance>(vk_inst), &sci, static_cast<const VkAllocationCallbacks *>(vk_allocators), (VkSurfaceKHR*)out_vk_surface);
    return (int)err;
}

bool Framework::Graphics::VulkanTypes::VkImGUI::Init(EvoVulkan::Core::VulkanKernel* kernel) {
    SR_INFO("VkImGUI::Init() : initializing vulkan imgui...");

    m_device      = kernel->GetDevice();
    m_swapchain   = kernel->GetSwapchain();
    m_multisample = kernel->GetMultisampleTarget();

    if (!m_device || !m_swapchain || !m_multisample) {
        SR_ERROR("VkImGUI::Init() : device, multisample or swapchain is nullptr!");
        return false;
    }

    if (!m_pool) {
        m_pool = EvoVulkan::Types::DescriptorPool::Create(*m_device, 1000 * m_poolSizes.size(), m_poolSizes);
    }

    if (!m_pool) {
        SR_ERROR("VkImGUI::Init() : failed to create descriptor pool!");
        return false;
    }

    m_renderPass = EvoVulkan::Types::CreateRenderPass(
            m_device,
            m_swapchain,
            {
                EvoVulkan::Tools::CreateColorAttachmentDescription(
                        m_swapchain->GetColorFormat(),
                        m_device->GetMSAASamples(),
                        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
                    )
            },
            m_device->MultisampleEnabled(), false
    );

    if (!m_renderPass.Ready()) {
        SR_ERROR("VkImGUI::Init() : failed to create render pass!");
        return false;
    }

    //ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();

    //ImGuiViewport* mainViewport = platform_io.MainViewport;
    //mainViewport->PlatformHandle = kernel->GetSurface()->GetHandle();

    //platform_io.Platform_CreateVkSurface = CreatePlatformSurface;

    // Setup Platform/Renderer bindings
    uint32_t images = m_swapchain->GetCountImages();

    ImGui_ImplVulkan_InitInfo init_info = {
            .Instance       = kernel->GetInstance(),
            .PhysicalDevice = *kernel->GetDevice(),
            .Device         = *kernel->GetDevice(),
            .QueueFamily    = kernel->GetDevice()->GetQueues()->GetGraphicsIndex(),
            .Queue          = kernel->GetDevice()->GetGraphicsQueue(),
            .PipelineCache  = kernel->GetPipelineCache(),
            .DescriptorPool = *m_pool,
            .Subpass        = 0,
            .MinImageCount  = images,
            .ImageCount     = images,
            .MSAASamples    = kernel->GetDevice()->GetMSAASamples(),
            .Allocator      = nullptr,
            //TODO: .CheckVkResultFn = ...
    };

    if (!ImGui_ImplVulkan_Init(&init_info, m_renderPass)) {
        SR_ERROR("Vulkan::InitGUI() : failed to init vulkan imgui implementation!");
        return false;
    }
    else {
        auto&& single = EvoVulkan::Types::CmdBuffer::BeginSingleTime(m_device, kernel->GetCmdPool());
        ImGui_ImplVulkan_CreateFontsTexture(*single);
        single->End();
        single->Destroy();
        single->Free();
    }

    //! create vulkan command buffers
    this->m_cmdBuffs.resize(m_swapchain->GetCountImages());
    for (auto& m_cmdBuff : m_cmdBuffs) {
        if (auto pool = m_device->CreateCommandPool(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT); pool != VK_NULL_HANDLE) {
            m_cmdPools.emplace_back(pool);

            auto&& info = EvoVulkan::Tools::Initializers::CommandBufferAllocateInfo(pool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, 1);
            if (vkAllocateCommandBuffers(*m_device, &info, &m_cmdBuff) != VK_SUCCESS) {
                SR_ERROR("VkImGUI::Init() : failed to create command buffer!");
                return false;
            }
        }
        else {
            SR_ERROR("VkImGUI::Init() : failed to create command pool!");
            return false;
        }
    }

    if (!ReSize(m_swapchain->GetSurfaceWidth(), m_swapchain->GetSurfaceHeight())) {
        SR_ERROR("Vulkan::InitGUI() : failed to resize frame buffers!");
        return false;
    }

    m_cmdBuffBI = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .pNext = nullptr,
            .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
            .pInheritanceInfo = nullptr
    };

    return true;
}

bool Framework::Graphics::VulkanTypes::VkImGUI::Destroy() {
    SR_INFO("VkImGUI::Destroy() : destroying vulkan imgui...");

    if (m_pool) {
        delete m_pool;
        m_pool = nullptr;
    }
    else {
        SR_ERROR("VkImGUI::Destroy() : descriptor pool is nullptr!");
        return false;
    }

    if (m_renderPass.Ready()) {
        DestroyRenderPass(m_device, &m_renderPass);
    }
    else {
        SR_ERROR("VkImGUI::Destroy() : render pass isn't ready!");
        return false;
    }

    for (auto& cmdPool : m_cmdPools)
        if (cmdPool != VK_NULL_HANDLE)
            vkDestroyCommandPool(*m_device, cmdPool, nullptr);

    for (auto& buffer : m_frameBuffs)
        vkDestroyFramebuffer(*m_device, buffer, nullptr);
    m_frameBuffs.clear();

    this->m_swapchain = nullptr;
    this->m_device    = nullptr;

    ImGui_ImplVulkan_Shutdown();

    return true;
}

void Framework::Graphics::VulkanTypes::VkImGUI::Free() {
    delete this;
}

bool Framework::Graphics::VulkanTypes::VkImGUI::ReSize(uint32_t width, uint32_t height) {
    SR_GRAPH_LOG("VkImGUI::ReSize() : resize imgui vulkan frame buffers...\n\tWidth: " + std::to_string(width) + "\n\tHeight: " + std::to_string(height));

    if (!m_device || !m_swapchain) {
        SR_ERROR("VkImGUI::ReSize() : device or swapchain is nullptr!");
        return false;
    }

    for (auto& buffer : m_frameBuffs) {
        vkDestroyFramebuffer(*m_device, buffer, nullptr);
    }

    m_frameBuffs.clear();
    m_frameBuffs.resize(m_swapchain->GetCountImages());

    auto fbInfo = EvoVulkan::Tools::Initializers::FrameBufferCI(m_renderPass, width, height);
    auto attaches = std::vector<VkImageView>(m_device->MultisampleEnabled() ? 2 : 1);
    fbInfo.attachmentCount = attaches.size();

    for (uint32_t i = 0; i < m_frameBuffs.size(); i++) {
        if (m_device->MultisampleEnabled()) {
            attaches[0] = m_multisample->GetResolve(0);
            attaches[1] = m_swapchain->GetBuffers()[i].m_view;
        }
        else
            attaches[0] = m_swapchain->GetBuffers()[i].m_view;

        fbInfo.pAttachments = attaches.data();
        if (vkCreateFramebuffer(*m_device, &fbInfo, nullptr, &m_frameBuffs[i]) != VK_SUCCESS) {
            SR_ERROR("VkImGUI::ReSize() : failed to create frame buffer!");
            return false;
        }
    }

    //!------------------

    if (m_device->MultisampleEnabled())
        this->m_clearValues = { { .color = { 0.0, 0.0, 0.0, 1.0 } }, { .color = { 0.0, 0.0, 0.0, 1.0 } } };
    else
        this->m_clearValues = { { .color = { 0.0, 0.0, 0.0, 1.0 } } };

    m_renderPassBI = {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .pNext = nullptr,
            .renderPass = m_renderPass,
            .framebuffer = VK_NULL_HANDLE,
            .renderArea = { VkOffset2D(), { width, height } },
            .clearValueCount = static_cast<uint32_t>(m_clearValues.size()),
            .pClearValues = m_clearValues.data(),
    };

    m_surfaceDirty = false;

    return true;
}

VkCommandBuffer Framework::Graphics::VulkanTypes::VkImGUI::Render(uint32_t frame) {
    auto buffer = m_cmdBuffs[frame];

    vkResetCommandPool(*m_device, m_cmdPools[frame], 0);
    vkBeginCommandBuffer(m_cmdBuffs[frame], &m_cmdBuffBI);

    m_renderPassBI.framebuffer = m_frameBuffs[frame];
    vkCmdBeginRenderPass(m_cmdBuffs[frame], &m_renderPassBI, VK_SUBPASS_CONTENTS_INLINE);

    if (auto drawData = ImGui::GetDrawData())
        ImGui_ImplVulkan_RenderDrawData(drawData, m_cmdBuffs[frame]);
    else
        VK_WARN("VkImGUI::Render() : imgui draw data is nullptr!");

    vkCmdEndRenderPass(m_cmdBuffs[frame]);
    vkEndCommandBuffer(m_cmdBuffs[frame]);

    return buffer;
}
