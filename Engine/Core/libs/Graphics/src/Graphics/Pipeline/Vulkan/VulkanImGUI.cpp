//
// Created by Nikita on 01.07.2021.
//

#include <Utils/GUI.h>
#include <Utils/Common/Features.h>

#include <EvoVulkan/Types/DescriptorPool.h>

#include <Graphics/Pipeline/Vulkan/VulkanImGUI.h>
#include <Graphics/Pipeline/Vulkan/VulkanTracy.h>

#include <Graphics/GUI/Widget.h>
#include <Graphics/Pipeline/Environment.h>
#include <Graphics/Pipeline/Vulkan.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace SR_GRAPH_NS::WinAPI2 {
    static int GetBorderHeight(HWND hWnd) {
        RECT rcClient, rcWind;
        GetClientRect(hWnd, &rcClient);
        GetWindowRect(hWnd, &rcWind);
        return ((rcWind.right - rcWind.left) - rcClient.right) / 2;
    }

    static LRESULT ImGui_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui::GetCurrentContext() == NULL)
            return 0;

        ImGuiIO& io = ImGui::GetIO();

        switch (msg) {
            case WM_CHAR:
                wchar_t wch;
                MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (char *) &wParam, 1, &wch, 1);
                io.AddInputCharacter(wch);
                return 1;
            default:
                break;
        }

        return 0;
    }
}

int CreatePlatformSurface(ImGuiViewport* pv, ImU64 vk_inst, const void* vk_allocators, ImU64* out_vk_surface) {
#ifdef SR_WIN32
    VkWin32SurfaceCreateInfoKHR sci;
    PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;

    vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(reinterpret_cast<VkInstance>(vk_inst), "vkCreateWin32SurfaceKHR");
    if (!vkCreateWin32SurfaceKHR) {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    memset(&sci, 0, sizeof(sci));
    sci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    sci.hinstance = GetModuleHandle(NULL);
    sci.hwnd = static_cast<HWND>(pv->PlatformHandleRaw);

    VkResult err = vkCreateWin32SurfaceKHR(reinterpret_cast<VkInstance>(vk_inst), &sci, static_cast<const VkAllocationCallbacks *>(vk_allocators), (VkSurfaceKHR*)out_vk_surface);
    return (int)err;
#else
    SRHaltOnce("Unsupported platform!");
    return -1;
#endif
}

LRESULT CustomWindowProcPlatform(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)  {
    if (!SR_GRAPH_NS::WinAPI2::ImGui_WndProcHandler(hwnd, msg, wParam, lParam)) {
        if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam)) {
            return true;
        }
    }

    switch (msg) {
        case WM_CREATE: {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        case WM_DESTROY:
        case WM_CLOSE: {
            auto&& viewport = ImGui::FindViewportByPlatformHandle(hwnd);
            if (auto&& widget = SR_GRAPH_NS::GUI::ViewportsTableManager::Instance().GetWidgetByViewport(viewport)) {
                //widget->Close();
            }

            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

static void (*ImGui_Platform_CreateWindow)(ImGuiViewport* vp) = nullptr;

void Replacement_Platform_CreateWindow(ImGuiViewport* vp)
{
    if (ImGui_Platform_CreateWindow != nullptr) {
        ImGui_Platform_CreateWindow(vp);
    }

    if (vp->PlatformHandle != nullptr) {
        /// platform dependent manipulation of viewport window, f.e. in Win32:
        SetWindowLongPtr((HWND)vp->PlatformHandle, GWLP_WNDPROC, (LONG_PTR)CustomWindowProcPlatform);
    }
}

namespace SR_GRAPH_NS::VulkanTypes {
    VkImGUI::VkImGUI(const PipelinePtr& pPipeline)
        : Super()
        , m_pipeline(pPipeline)
    { }

    VkImGUI::~VkImGUI() {
        SR_INFO("VkImGUI::~VkImGUI() : destroying vulkan imgui...");

        SR_SAFE_DELETE_PTR(m_pool);

        for (auto&& cmdPool : m_cmdPools) {
            if (cmdPool != VK_NULL_HANDLE) {
                vkDestroyCommandPool(*m_device, cmdPool, nullptr);
            }
        }

        m_cmdPools.clear();

        if (m_semaphore != VK_NULL_HANDLE) {
            vkDestroySemaphore(*m_device, m_semaphore, nullptr);
            m_semaphore = VK_NULL_HANDLE;
        }

        DeInitializeRenderer();

        m_swapchain = nullptr;
        m_device = nullptr;
    }

    void VkImGUI::DeInitializeRenderer() {
        SR_INFO("VkImGUI::DeInitializeRenderer() : de-initialization vulkan ImGui renderer...");

        DestroyBuffers();

        if (m_renderPass.IsReady()) {
            DestroyRenderPass(m_device, &m_renderPass);
        }
        else {
            SR_ERROR("VkImGUI::~VkImGUI() : render pass isn't ready!");
            return;
        }

        auto&& pVulkanBackend = ImGui::GetCurrentContext() ? (ImGui_ImplVulkan_Data*)ImGui::GetIO().BackendRendererUserData : NULL;

        if (pVulkanBackend) {
            ImGui_ImplVulkan_Shutdown();
        }
    }

    bool VkImGUI::Init() {
        SR_INFO("VkImGUI::Init() : initializing vulkan imgui...");

        auto&& pKernel = dynamic_cast<Vulkan*>(m_pipeline)->GetKernel();

        m_tracyEnabled = SR_UTILS_NS::Features::Instance().Enabled("Tracy", false);

        m_device      = pKernel->GetDevice();
        m_swapchain   = pKernel->GetSwapchain();
        m_multisample = pKernel->GetMultisampleTarget();

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

        //! create vulkan command buffers
        m_cmdBuffs.resize(m_swapchain->GetCountImages());

        auto&& semaphoreCI = EvoVulkan::Tools::Initializers::SemaphoreCreateInfo();
        if (vkCreateSemaphore(*m_device, &semaphoreCI, nullptr, &m_semaphore) != VK_SUCCESS) {
            VK_ERROR("VkImGUI::Init() : failed to create vulkan semaphore!");
            return false;
        }

        for (auto&& m_cmdBuff : m_cmdBuffs) {
            if (auto&& pool = m_device->CreateCommandPool(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT); pool != VK_NULL_HANDLE) {
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

        if (!InitializeRenderer()) {
            SR_ERROR("VkImGUI::Init() : failed to initialize renderer!");
            return false;
        }

        if (!ReSize(m_swapchain->GetSurfaceWidth(), m_swapchain->GetSurfaceHeight())) {
            SR_ERROR("VkImGUI::Init() : failed to resize frame buffers!");
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

    bool VkImGUI::InitializeRenderer() {
        SR_INFO("VkImGUI::InitializeRenderer() : initialization vulkan ImGui renderer...");

        const VkSampleCountFlagBits countMSAASamples = EvoVulkan::Tools::Convert::IntToSampleCount(
            1// m_pipeline->GetSamplesCount()
        );

        m_renderPass = EvoVulkan::Types::CreateRenderPass(
            m_device, m_swapchain,
            {
                EvoVulkan::Tools::CreateColorAttachmentDescription(
                    m_swapchain->GetColorFormat(),
                    countMSAASamples,
                    VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                    VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
                )
            },
            countMSAASamples,
            false /** depth buffer */
        );

        if (!m_renderPass.IsReady()) {
            SR_ERROR("VkImGUI::Init() : failed to create render pass!");
            return false;
        }

        auto&& pKernel = dynamic_cast<Vulkan*>(m_pipeline)->GetKernel();

        ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();

        ImGuiViewport* mainViewport = platform_io.Viewports.front();
        mainViewport->PlatformHandle = pKernel->GetSurface()->GetHandle();

        platform_io.Platform_CreateVkSurface = CreatePlatformSurface;
        ImGui_Platform_CreateWindow = platform_io.Platform_CreateWindow;
        platform_io.Platform_CreateWindow = Replacement_Platform_CreateWindow;

        /// Setup Platform/Renderer bindings
        uint32_t images = m_swapchain->GetCountImages();

        ImGui_ImplVulkan_InitInfo init_info = {
            .Instance       = pKernel->GetInstance(),
            .PhysicalDevice = *pKernel->GetDevice(),
            .Device         = *pKernel->GetDevice(),
            .QueueFamily    = pKernel->GetDevice()->GetQueues()->GetGraphicsIndex(),
            .Queue          = pKernel->GetDevice()->GetQueues()->GetGraphicsQueue(),
            .PipelineCache  = pKernel->GetPipelineCache(),
            .DescriptorPool = *m_pool,
            .Subpass        = 0,
            .MinImageCount  = images,
            .ImageCount     = images,
            .MSAASamples    = countMSAASamples,
            .Allocator      = nullptr,
            //TODO: .CheckVkResultFn = ...
        };

        if (!ImGui_ImplVulkan_Init(&init_info, m_renderPass)) {
            SR_ERROR("Vulkan::InitGUI() : failed to init vulkan imgui implementation!");
            return false;
        }
        else {
            auto&& single = EvoVulkan::Types::CmdBuffer::BeginSingleTime(m_device, pKernel->GetCmdPool());
            ImGui_ImplVulkan_CreateFontsTexture(*single);
            single->End();
            delete single;
        }

        return true;
    }

    bool VkImGUI::ReCreate() {
        DestroyBuffers();

        if (!m_device || !m_swapchain) {
            SR_ERROR("VkImGUI::ReCreate() : device or swapchain is nullptr!");
            return false;
        }

        m_frameBuffs.resize(m_swapchain->GetCountImages());

        auto&& fbInfo = EvoVulkan::Tools::Initializers::FrameBufferCI(m_renderPass, m_surfaceSize.x, m_surfaceSize.y);
        auto&& attaches = std::vector<VkImageView>(1);
        fbInfo.attachmentCount = attaches.size();

        for (uint32_t i = 0; i < m_frameBuffs.size(); i++) {
            attaches[0] = m_swapchain->GetBuffers()[i].m_view;

            fbInfo.pAttachments = attaches.data();
            if (vkCreateFramebuffer(*m_device, &fbInfo, nullptr, &m_frameBuffs[i]) != VK_SUCCESS) {
                SR_ERROR("VkImGUI::ReCreate() : failed to create frame buffer!");
                return false;
            }
        }

        //!------------------

        m_clearValues = { { .color = { {0.0, 0.0, 0.0, 1.0} } } };

        m_renderPassBI = {
                .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                .pNext = nullptr,
                .renderPass = m_renderPass,
                .framebuffer = VK_NULL_HANDLE,
                .renderArea = { VkOffset2D(), { static_cast<uint32_t>(m_surfaceSize.x), static_cast<uint32_t>(m_surfaceSize.y) } },
                .clearValueCount = static_cast<uint32_t>(m_clearValues.size()),
                .pClearValues = m_clearValues.data(),
        };

        m_surfaceDirty = false;

        return true;
    }

    bool VkImGUI::ReSize(uint32_t width, uint32_t height) {
        SR_GRAPH_LOG("VkImGUI::ReSize() : resize imgui vulkan frame buffers...\n\tWidth: " + std::to_string(width) + "\n\tHeight: " + std::to_string(height));

        m_surfaceSize = SR_MATH_NS::IVector2(width, height);

        return ReCreate();
    }

    VkCommandBuffer VkImGUI::Render(uint32_t frame) {
        auto&& buffer = m_cmdBuffs[frame];

        vkResetCommandPool(*m_device, m_cmdPools[frame], 0);

        if (m_tracyEnabled) {
            vkBeginCommandBuffer(buffer, &m_cmdBuffBI);
            {
                SR_TRACY_VK_FRAME_ZONE_N(buffer, "VkImGUI");

                m_renderPassBI.framebuffer = m_frameBuffs[frame];
                vkCmdBeginRenderPass(m_cmdBuffs[frame], &m_renderPassBI, VK_SUBPASS_CONTENTS_INLINE);

                if (auto&& drawData = ImGui::GetDrawData()) {
                    ImGui_ImplVulkan_RenderDrawData(drawData, m_cmdBuffs[frame]);
                }
                else {
                    VK_WARN("VkImGUI::Render() : imgui draw data is nullptr!");
                }

                vkCmdEndRenderPass(m_cmdBuffs[frame]);
            }

            SR_TRACY_VK_COLLECT(buffer);
        }
        else {
            vkBeginCommandBuffer(buffer, &m_cmdBuffBI);
            {
                m_renderPassBI.framebuffer = m_frameBuffs[frame];
                vkCmdBeginRenderPass(m_cmdBuffs[frame], &m_renderPassBI, VK_SUBPASS_CONTENTS_INLINE);

                if (auto&& drawData = ImGui::GetDrawData()) {
                    ImGui_ImplVulkan_RenderDrawData(drawData, m_cmdBuffs[frame]);
                }
                else {
                    VK_WARN("VkImGUI::Render() : imgui draw data is nullptr!");
                }

                vkCmdEndRenderPass(m_cmdBuffs[frame]);
            }
        }

        vkEndCommandBuffer(m_cmdBuffs[frame]);

        return buffer;
    }

    void VkImGUI::SetSurfaceDirty() {
        m_surfaceDirty = true;
    }

    bool VkImGUI::IsUndockingActive() const {
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            return GImGui->Viewports.size() > 1;
        }

        return false;
    }

    void VkImGUI::DestroyBuffers() {
        for (auto&& buffer : m_frameBuffs) {
            vkDestroyFramebuffer(*m_device, buffer, nullptr);
        }

        m_frameBuffs.clear();
    }

    VkSubmitInfo VkImGUI::GetSubmitInfo(uint32_t countSemaphores, const VkSemaphore* waitSemaphores) const {
        auto&& pKernel = dynamic_cast<Vulkan*>(m_pipeline)->GetKernel();

        VkSubmitInfo submitInfo = EvoVulkan::Tools::Initializers::SubmitInfo();

        submitInfo.pWaitDstStageMask = pKernel->GetSubmitPipelineStages();

        submitInfo.commandBufferCount = m_cmdBuffs.size();
        submitInfo.pCommandBuffers = m_cmdBuffs.data();

        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = GetSemaphoreRef();

        submitInfo.waitSemaphoreCount = countSemaphores;
        submitInfo.pWaitSemaphores = waitSemaphores;

        return submitInfo;
    }
}
