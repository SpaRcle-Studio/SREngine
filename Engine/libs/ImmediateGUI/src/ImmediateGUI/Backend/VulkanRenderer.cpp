//
// Created by Monika on 07.07.2026.
//

#include <ImmediateGUI/Backend/VulkanRenderer.h>
#include <ImmediateGUI/Impl/Internal.h>
#include <ImmediateGUI/Impl/WindowsImpl.h>

#include <Utils/Debug.h>

#if defined(SR_USE_VULKAN) && defined(SR_USE_IMGUI)

namespace SR_GRAPH_GUI_NS::Immediate {
    namespace {
        struct VulkanRenderer {
            VulkanRendererCreateInfo info;

            VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
            VkRenderPass renderPass = VK_NULL_HANDLE;

            std::vector<VkFramebuffer> framebuffers;
            std::vector<VkCommandPool> cmdPools;
            std::vector<VkCommandBuffer> cmdBuffers;

            VkSemaphore semaphore = VK_NULL_HANDLE;

            VkCommandBufferBeginInfo cmdBeginInfo = { };
            VkRenderPassBeginInfo renderPassBeginInfo = { };
            std::vector<VkClearValue> clearValues;

            PFN_vkCmdBeginRendering pBeginRendering = nullptr;
            PFN_vkCmdEndRendering pEndRendering = nullptr;

            VkDescriptorSetLayout textureSetLayout = VK_NULL_HANDLE;

            uint32_t imageCount = 0;

            std::vector<VulkanFrameInfo> frames;
        };

        static const std::vector<VkDescriptorPoolSize> POOL_SIZES = {
            { VK_DESCRIPTOR_TYPE_SAMPLER,                1000 },
            { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,          1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,          1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,   1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,   1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,       1000 }
        };

        void CheckVulkanResult(VkResult result) {
            if (result != VK_SUCCESS) {
                SR_ERROR("Immediate::VulkanRenderer : vulkan error! Code: {}", static_cast<int>(result));
            }
        }

    #if defined(SR_WIN32)
        static LRESULT CustomWindowProcPlatform(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)  {
            if (ImmediateGUI_WndProcHandler(hwnd, msg, wParam, lParam)) {
                return true;
            }

            switch (msg) {
                case WM_CREATE:
                case WM_DESTROY:
                    return DefWindowProc(hwnd, msg, wParam, lParam);
                case WM_CLOSE: {
                    /// We keep default behaviour. Higher-level code may close widgets itself via ImGui docking logic.
                    return DefWindowProc(hwnd, msg, wParam, lParam);
                }
                case WM_SETCURSOR: {
                    /// Fix cursor for secondary viewport windows.
                    SetClassLongPtr(hwnd, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(LoadCursor(NULL, IDC_ARROW)));
                    return DefWindowProc(hwnd, msg, wParam, lParam);
                }
                default:
                    return DefWindowProc(hwnd, msg, wParam, lParam);
            }
        }

        struct ImGui_ImplWin32_ViewportData {
            HWND    Hwnd;
            bool    HwndOwned;
            DWORD   DwStyle;
            DWORD   DwExStyle;

            ImGui_ImplWin32_ViewportData() { Hwnd = NULL; HwndOwned = false; DwStyle = DwExStyle = 0; }
            ~ImGui_ImplWin32_ViewportData() { IM_ASSERT(Hwnd == NULL); }
        };

        static void ImGui_ImplWin32_GetWin32StyleFromViewportFlags(ImGuiViewportFlags flags, DWORD* out_style, DWORD* out_ex_style) {
            if (flags & ImGuiViewportFlags_NoDecoration)
                *out_style = WS_POPUP;
            else
                *out_style = WS_OVERLAPPEDWINDOW;

            if (flags & ImGuiViewportFlags_NoTaskBarIcon)
                *out_ex_style = WS_EX_TOOLWINDOW;
            else
                *out_ex_style = WS_EX_APPWINDOW;

            if (flags & ImGuiViewportFlags_TopMost)
                *out_ex_style |= WS_EX_TOPMOST;
        }

        static void ImGui_ImplWin32_CreateWindow(ImGuiViewport* viewport) {
            ImGui_ImplWin32_ViewportData* vd = IM_NEW(ImGui_ImplWin32_ViewportData)();
            viewport->PlatformUserData = vd;

            ImGui_ImplWin32_GetWin32StyleFromViewportFlags(viewport->Flags, &vd->DwStyle, &vd->DwExStyle);
            HWND parent_window = NULL;
            if (viewport->ParentViewportId != 0)
                if (ImGuiViewport* parent_viewport = ImGui::FindViewportByID(viewport->ParentViewportId))
                    parent_window = (HWND)parent_viewport->PlatformHandle;

            RECT rect = { (LONG)viewport->Pos.x, (LONG)viewport->Pos.y, (LONG)(viewport->Pos.x + viewport->Size.x), (LONG)(viewport->Pos.y + viewport->Size.y) };
            ::AdjustWindowRectEx(&rect, vd->DwStyle, FALSE, vd->DwExStyle);
            vd->Hwnd = ::CreateWindowEx(
                vd->DwExStyle, "ImGui Platform", "Untitled", vd->DwStyle,
                rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
                parent_window, NULL, ::GetModuleHandle(NULL), NULL);

            vd->HwndOwned = true;
            viewport->PlatformRequestResize = false;
            viewport->PlatformHandle = viewport->PlatformHandleRaw = vd->Hwnd;

            vd->DwExStyle &= ~WS_CAPTION;
            vd->DwExStyle &= ~WS_SIZEBOX;
            vd->DwExStyle &= ~WS_SYSMENU;

            SetWindowLong(vd->Hwnd, GWL_STYLE, vd->DwExStyle);
            UpdateWindow(vd->Hwnd);
        }

        static void (*g_platformCreateWindow)(ImGuiViewport* vp) = nullptr;

        static void Replacement_Platform_CreateWindow(ImGuiViewport* vp) {
            if (g_platformCreateWindow) {
                g_platformCreateWindow(vp);
            }

            if (vp->PlatformHandle != nullptr) {
                SetWindowLongPtr((HWND)vp->PlatformHandle, GWLP_WNDPROC, (LONG_PTR)CustomWindowProcPlatform);
            }
        }
    #endif

        static int CreatePlatformSurface(ImGuiViewport* pv, ImU64 vk_inst, const void* vk_allocators, ImU64* out_vk_surface) {
        #if defined(SR_WIN32)
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

            VkResult err = vkCreateWin32SurfaceKHR(reinterpret_cast<VkInstance>(vk_inst), &sci, static_cast<const VkAllocationCallbacks*>(vk_allocators), (VkSurfaceKHR*)out_vk_surface);
            return (int)err;
        #else
            (void)pv; (void)vk_inst; (void)vk_allocators; (void)out_vk_surface;
            SRHaltOnce("Immediate::CreatePlatformSurface : unsupported platform!");
            return -1;
        #endif
        }

        bool CreateDescriptorPool(VulkanRenderer& r) {
            if (r.descriptorPool != VK_NULL_HANDLE) {
                return true;
            }

            VkDescriptorPoolCreateInfo pool_info = {};
            pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
            pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
            pool_info.maxSets = 1000 * (uint32_t)POOL_SIZES.size();
            pool_info.poolSizeCount = (uint32_t)POOL_SIZES.size();
            pool_info.pPoolSizes = POOL_SIZES.data();

            return vkCreateDescriptorPool(r.info.device, &pool_info, nullptr, &r.descriptorPool) == VK_SUCCESS;
        }

        bool CreateRenderPass(VulkanRenderer& r) {
            if (r.info.enableDynamicRendering) {
                return true;
            }

            if (r.renderPass != VK_NULL_HANDLE) {
                return true;
            }

            VkAttachmentDescription attachment = {};
            attachment.format = r.info.swapchainColorFormat;
            attachment.samples = r.info.msaaSamples;
            attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
            attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
            attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
            attachment.initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

            VkAttachmentReference color_attachment = {};
            color_attachment.attachment = 0;
            color_attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

            VkSubpassDescription subpass = {};
            subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
            subpass.colorAttachmentCount = 1;
            subpass.pColorAttachments = &color_attachment;

            VkSubpassDependency dependency = {};
            dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
            dependency.dstSubpass = 0;
            dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            dependency.srcAccessMask = 0;
            dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

            VkRenderPassCreateInfo rp_info = {};
            rp_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
            rp_info.attachmentCount = 1;
            rp_info.pAttachments = &attachment;
            rp_info.subpassCount = 1;
            rp_info.pSubpasses = &subpass;
            rp_info.dependencyCount = 1;
            rp_info.pDependencies = &dependency;

            return vkCreateRenderPass(r.info.device, &rp_info, nullptr, &r.renderPass) == VK_SUCCESS;
        }

        void DestroyFramebuffers(VulkanRenderer& r) {
            for (auto&& fb : r.framebuffers) {
                if (fb != VK_NULL_HANDLE) {
                    vkDestroyFramebuffer(r.info.device, fb, nullptr);
                }
            }
            r.framebuffers.clear();
        }

        bool CreateFramebuffers(VulkanRenderer& r) {
            if (r.info.enableDynamicRendering) {
                DestroyFramebuffers(r);
                return true;
            }

            DestroyFramebuffers(r);

            r.framebuffers.resize(r.imageCount, VK_NULL_HANDLE);

            for (uint32_t i = 0; i < r.imageCount; ++i) {
                VkImageView attachments[1] = { r.frames[i].imageView };

                VkFramebufferCreateInfo fb_info = {};
                fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
                fb_info.renderPass = r.renderPass;
                fb_info.attachmentCount = 1;
                fb_info.pAttachments = attachments;
                fb_info.width = r.frames[i].width;
                fb_info.height = r.frames[i].height;
                fb_info.layers = 1;

                if (vkCreateFramebuffer(r.info.device, &fb_info, nullptr, &r.framebuffers[i]) != VK_SUCCESS) {
                    return false;
                }
            }

            return true;
        }

        bool CreateCommandBuffers(VulkanRenderer& r) {
            r.cmdPools.clear();
            r.cmdBuffers.clear();

            r.cmdPools.resize(r.imageCount, VK_NULL_HANDLE);
            r.cmdBuffers.resize(r.imageCount, VK_NULL_HANDLE);

            for (uint32_t i = 0; i < r.imageCount; ++i) {
                VkCommandPoolCreateInfo pool_info = {};
                pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
                pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
                pool_info.queueFamilyIndex = r.info.graphicsQueueFamily;

                if (vkCreateCommandPool(r.info.device, &pool_info, nullptr, &r.cmdPools[i]) != VK_SUCCESS) {
                    return false;
                }

                VkCommandBufferAllocateInfo alloc_info = {};
                alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                alloc_info.commandPool = r.cmdPools[i];
                alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                alloc_info.commandBufferCount = 1;

                if (vkAllocateCommandBuffers(r.info.device, &alloc_info, &r.cmdBuffers[i]) != VK_SUCCESS) {
                    return false;
                }
            }

            r.cmdBeginInfo = {
                .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                .pNext = nullptr,
                .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
                .pInheritanceInfo = nullptr
            };

            r.clearValues = { { .color = { {0.0f, 0.0f, 0.0f, 1.0f} } } };

            r.renderPassBeginInfo = {
                .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                .pNext = nullptr,
                .renderPass = r.renderPass,
                .framebuffer = VK_NULL_HANDLE,
                .renderArea = { VkOffset2D(), { 0, 0 } },
                .clearValueCount = static_cast<uint32_t>(r.clearValues.size()),
                .pClearValues = r.clearValues.data(),
            };

            return true;
        }

        bool CreateSemaphore(VulkanRenderer& r) {
            if (r.semaphore != VK_NULL_HANDLE) {
                vkDestroySemaphore(r.info.device, r.semaphore, nullptr);
                r.semaphore = VK_NULL_HANDLE;
            }

            VkSemaphoreCreateInfo semaphoreCI = {};
            semaphoreCI.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

            return vkCreateSemaphore(r.info.device, &semaphoreCI, nullptr, &r.semaphore) == VK_SUCCESS;
        }

        void ResolveDynamicRenderingFunctions(VulkanRenderer& r) {
            if (!r.info.enableDynamicRendering) {
                r.pBeginRendering = nullptr;
                r.pEndRendering = nullptr;
                return;
            }

            r.pBeginRendering = (PFN_vkCmdBeginRendering)vkGetDeviceProcAddr(r.info.device, "vkCmdBeginRendering");
            r.pEndRendering   = (PFN_vkCmdEndRendering)vkGetDeviceProcAddr(r.info.device, "vkCmdEndRendering");

            if (!r.pBeginRendering) {
                r.pBeginRendering = (PFN_vkCmdBeginRendering)vkGetDeviceProcAddr(r.info.device, "vkCmdBeginRenderingKHR");
            }
            if (!r.pEndRendering) {
                r.pEndRendering = (PFN_vkCmdEndRendering)vkGetDeviceProcAddr(r.info.device, "vkCmdEndRenderingKHR");
            }

            if (!r.pBeginRendering || !r.pEndRendering) {
                SR_ERROR("Immediate::VulkanRenderer : failed to get dynamic rendering functions. Disabling dynamic rendering...");
                r.info.enableDynamicRendering = false;
                r.pBeginRendering = nullptr;
                r.pEndRendering = nullptr;
            }
        }

        bool InitImGuiVulkanBackend(VulkanRenderer& r) {
        #if defined(SR_WIN32)
            if (r.info.enableViewports && r.info.mainViewportPlatformHandleRaw) {
                ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
                if (!platform_io.Viewports.empty() && platform_io.Viewports.front()) {
                    ImGuiViewport* mainViewport = platform_io.Viewports.front();
                    mainViewport->PlatformHandle = r.info.mainViewportPlatformHandleRaw;
                    mainViewport->PlatformHandleRaw = r.info.mainViewportPlatformHandleRaw;
                }

                platform_io.Platform_CreateVkSurface = CreatePlatformSurface;

                g_platformCreateWindow = ImGui_ImplWin32_CreateWindow;
                platform_io.Platform_CreateWindow = Replacement_Platform_CreateWindow;
            }
        #endif

            ImGui_ImplVulkan_InitInfo init_info = {};
            init_info.Instance = r.info.instance;
            init_info.PhysicalDevice = r.info.physicalDevice;
            init_info.Device = r.info.device;
            init_info.QueueFamily = r.info.graphicsQueueFamily;
            init_info.Queue = r.info.graphicsQueue;
            init_info.DescriptorPool = r.descriptorPool;
            init_info.RenderPass = r.renderPass;
            init_info.MinImageCount = r.imageCount;
            init_info.ImageCount = r.imageCount;
            init_info.MSAASamples = r.info.msaaSamples;
            init_info.PipelineCache = r.info.pipelineCache;
            init_info.Subpass = 0;
            init_info.UseDynamicRendering = false;
            init_info.PipelineRenderingCreateInfo = {};
            init_info.Allocator = nullptr;
            init_info.CheckVkResultFn = CheckVulkanResult;
            init_info.MinAllocationSize = 0;

            if (r.info.enableDynamicRendering) {
                init_info.UseDynamicRendering = true;
                init_info.PipelineRenderingCreateInfo = {
                    .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
                    .pNext                   = nullptr,
                    .colorAttachmentCount    = 1,
                    .pColorAttachmentFormats = &r.info.swapchainColorFormat,
                    .depthAttachmentFormat   = VK_FORMAT_UNDEFINED,
                    .stencilAttachmentFormat = VK_FORMAT_UNDEFINED
                };
            }

            if (!ImGui_ImplVulkan_Init(&init_info)) {
                return false;
            }

            if (ImGui::GetIO().BackendRendererUserData) {
                auto* data = (ImGui_ImplVulkan_Data*)ImGui::GetIO().BackendRendererUserData;
                r.textureSetLayout = data->DescriptorSetLayout;
            }

            return true;
        }

        void ShutdownImGuiVulkanBackend(VulkanRenderer& r) {
            auto* backend = ImGui::GetCurrentContext() ? (ImGui_ImplVulkan_Data*)ImGui::GetIO().BackendRendererUserData : nullptr;
            if (backend) {
                ImGui_ImplVulkan_Shutdown();
            }
            r.textureSetLayout = VK_NULL_HANDLE;
        }

        void DestroyRenderer(VulkanRenderer& r) {
            ShutdownImGuiVulkanBackend(r);

            DestroyFramebuffers(r);

            if (r.renderPass != VK_NULL_HANDLE) {
                vkDestroyRenderPass(r.info.device, r.renderPass, nullptr);
                r.renderPass = VK_NULL_HANDLE;
            }

            for (auto&& pool : r.cmdPools) {
                if (pool != VK_NULL_HANDLE) {
                    vkDestroyCommandPool(r.info.device, pool, nullptr);
                }
            }
            r.cmdPools.clear();
            r.cmdBuffers.clear();

            if (r.semaphore != VK_NULL_HANDLE) {
                vkDestroySemaphore(r.info.device, r.semaphore, nullptr);
                r.semaphore = VK_NULL_HANDLE;
            }

            if (r.descriptorPool != VK_NULL_HANDLE) {
                vkDestroyDescriptorPool(r.info.device, r.descriptorPool, nullptr);
                r.descriptorPool = VK_NULL_HANDLE;
            }
        }

        bool SetupFrames(VulkanRenderer& r, const VulkanFrameInfo* frames, uint32_t frameCount) {
            if (!frames || frameCount == 0) {
                return false;
            }

            r.frames.assign(frames, frames + frameCount);
            r.imageCount = frameCount;
            return true;
        }
    }

    VulkanRendererHandle VulkanCreateRenderer(const VulkanRendererCreateInfo& info, const VulkanFrameInfo* frames, uint32_t frameCount) {
        auto* r = new VulkanRenderer();
        r->info = info;

        if (!SetupFrames(*r, frames, frameCount)) {
            delete r;
            return nullptr;
        }

        ResolveDynamicRenderingFunctions(*r);

        if (!CreateDescriptorPool(*r)) {
            delete r;
            return nullptr;
        }

        if (!CreateRenderPass(*r)) {
            DestroyRenderer(*r);
            delete r;
            return nullptr;
        }

        if (!CreateFramebuffers(*r)) {
            DestroyRenderer(*r);
            delete r;
            return nullptr;
        }

        if (!CreateCommandBuffers(*r)) {
            DestroyRenderer(*r);
            delete r;
            return nullptr;
        }

        if (!InitImGuiVulkanBackend(*r)) {
            DestroyRenderer(*r);
            delete r;
            return nullptr;
        }

        if (!CreateSemaphore(*r)) {
            DestroyRenderer(*r);
            delete r;
            return nullptr;
        }

        return r;
    }

    void VulkanDestroyRenderer(VulkanRendererHandle renderer) {
        if (!renderer) {
            return;
        }

        auto* r = static_cast<VulkanRenderer*>(renderer);
        DestroyRenderer(*r);
        delete r;
    }

    bool VulkanRecreateRenderer(VulkanRendererHandle renderer, const VulkanFrameInfo* frames, uint32_t frameCount) {
        if (!renderer) {
            return false;
        }

        auto* r = static_cast<VulkanRenderer*>(renderer);

        if (!SetupFrames(*r, frames, frameCount)) {
            return false;
        }

        if (r->semaphore != VK_NULL_HANDLE) {
            vkDestroySemaphore(r->info.device, r->semaphore, nullptr);
            r->semaphore = VK_NULL_HANDLE;
        }

        if (!CreateSemaphore(*r)) {
            return false;
        }

        if (!CreateFramebuffers(*r)) {
            return false;
        }

        return true;
    }

    void VulkanNewFrame(VulkanRendererHandle renderer) {
        if (!renderer) {
            return;
        }
        ImGui_ImplVulkan_NewFrame();
    }

    VkCommandBuffer VulkanRecordFrame(VulkanRendererHandle renderer, uint32_t frameIndex, bool tracyEnabled) {
        (void)tracyEnabled;

        if (!renderer) {
            return VK_NULL_HANDLE;
        }

        auto* r = static_cast<VulkanRenderer*>(renderer);
        if (frameIndex >= r->cmdBuffers.size()) {
            return VK_NULL_HANDLE;
        }

        VkCommandBuffer cmd = r->cmdBuffers[frameIndex];

        vkResetCommandPool(r->info.device, r->cmdPools[frameIndex], 0);
        vkBeginCommandBuffer(cmd, &r->cmdBeginInfo);

        static bool hasWarn = false;

        VkExtent2D extent = { r->frames[frameIndex].width, r->frames[frameIndex].height };

        if (r->info.enableDynamicRendering) {
            VkRenderingAttachmentInfoKHR colorAttachmentInfo = {
                .sType       = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR,
                .pNext       = nullptr,
                .imageView   = r->frames[frameIndex].imageView,
                .imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                .resolveMode = VK_RESOLVE_MODE_NONE,
                .resolveImageView = VK_NULL_HANDLE,
                .resolveImageLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                .loadOp      = VK_ATTACHMENT_LOAD_OP_CLEAR,
                .storeOp     = VK_ATTACHMENT_STORE_OP_STORE,
                .clearValue  = { .color = {{0.f, 0.f, 0.f, 1.f}} }
            };

            VkRenderingInfoKHR renderingInfo = {
                .sType                = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR,
                .pNext                = nullptr,
                .flags                = 0,
                .renderArea           = { {0, 0}, {extent.width, extent.height} },
                .layerCount           = 1,
                .viewMask             = 0,
                .colorAttachmentCount = 1,
                .pColorAttachments    = &colorAttachmentInfo,
                .pDepthAttachment     = nullptr,
                .pStencilAttachment   = nullptr
            };

            /// Transition swapchain image from PRESENT_SRC_KHR to COLOR_ATTACHMENT_OPTIMAL
            VkImageMemoryBarrier barrier = {};
            barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            barrier.oldLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            barrier.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
            barrier.image = r->frames[frameIndex].image;
            barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            barrier.subresourceRange.levelCount = 1;
            barrier.subresourceRange.layerCount = 1;
            vkCmdPipelineBarrier(
                cmd,
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                0,
                0, nullptr,
                0, nullptr,
                1, &barrier
            );

            r->pBeginRendering(cmd, &renderingInfo);
        }
        else {
            r->renderPassBeginInfo.framebuffer = r->framebuffers[frameIndex];
            r->renderPassBeginInfo.renderArea.extent = extent;
            vkCmdBeginRenderPass(cmd, &r->renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
        }

        if (auto&& drawData = ImGui::GetDrawData()) {
            ImGui_ImplVulkan_RenderDrawData(drawData, cmd);
        }
        else if (!hasWarn) {
            hasWarn = true;
            SR_WARN("Immediate::VulkanRenderer : imgui draw data is nullptr!");
        }

        if (r->info.enableDynamicRendering) {
            r->pEndRendering(cmd);

            /// Transition swapchain image from COLOR_ATTACHMENT_OPTIMAL back to PRESENT_SRC_KHR
            VkImageMemoryBarrier barrier = {};
            barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
            barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            barrier.dstAccessMask = 0;
            barrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
            barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            barrier.image = r->frames[frameIndex].image;
            barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            barrier.subresourceRange.levelCount = 1;
            barrier.subresourceRange.layerCount = 1;
            vkCmdPipelineBarrier(
                cmd,
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
                0,
                0, nullptr,
                0, nullptr,
                1, &barrier
            );
        }
        else {
            vkCmdEndRenderPass(cmd);
        }

        vkEndCommandBuffer(cmd);
        return cmd;
    }

    VkSemaphore VulkanGetRenderSemaphore(VulkanRendererHandle renderer) {
        if (!renderer) {
            return VK_NULL_HANDLE;
        }
        return static_cast<VulkanRenderer*>(renderer)->semaphore;
    }

    VkDescriptorSetLayout VulkanGetTextureDescriptorSetLayout(VulkanRendererHandle renderer) {
        if (!renderer) {
            return VK_NULL_HANDLE;
        }
        return static_cast<VulkanRenderer*>(renderer)->textureSetLayout;
    }

    void VulkanReloadFonts(VulkanRendererHandle renderer) {
        if (!renderer) {
            return;
        }

        if (ImGui::GetIO().BackendRendererUserData) {
            ImGui_ImplVulkan_CreateFontsTexture();
        }
    }
}

#endif // SR_USE_VULKAN && SR_USE_IMGUI

#if defined(SR_USE_VULKAN) && !defined(SR_USE_IMGUI)
namespace SR_GRAPH_GUI_NS::Immediate {
    VulkanRendererHandle VulkanCreateRenderer(const VulkanRendererCreateInfo& info, const VulkanFrameInfo* frames, uint32_t frameCount) { return nullptr; }
    void VulkanDestroyRenderer(VulkanRendererHandle renderer) { }
    bool VulkanRecreateRenderer(VulkanRendererHandle renderer, const VulkanFrameInfo* frames, uint32_t frameCount) { return false; }
    void VulkanNewFrame(VulkanRendererHandle renderer) { }
    VkCommandBuffer VulkanRecordFrame(VulkanRendererHandle renderer, uint32_t frameIndex, bool tracyEnabled) { return VK_NULL_HANDLE; }
    VkSemaphore VulkanGetRenderSemaphore(VulkanRendererHandle renderer) { return VK_NULL_HANDLE; }
    VkDescriptorSetLayout VulkanGetTextureDescriptorSetLayout(VulkanRendererHandle renderer) { return VK_NULL_HANDLE; }
    void VulkanReloadFonts(VulkanRendererHandle renderer) { }
}
#endif

