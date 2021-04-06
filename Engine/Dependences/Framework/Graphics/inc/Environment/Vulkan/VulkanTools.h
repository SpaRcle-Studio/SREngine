//
// Created by Nikita on 05.04.2021.
//

#ifndef GAMEENGINE_VULKANTOOLS_H
#define GAMEENGINE_VULKANTOOLS_H

#include <Environment/Vulkan/VulkanHelper.h>

namespace Framework::Graphics::VulkanTools {
    static VkCommandPool CreateCommandPool(const Device& device) {
        Helper::Debug::Graph("VulkanTools::CreateCommandPool() : create vulkan command pool...");

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = device.m_queue.m_iGraphicsFamily.value();

        VkCommandPool commandPool = {};
        if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::CreateCommandPool() : failed to create command pool!");
            return VK_NULL_HANDLE;
        }

        return commandPool;
    }

    static Synchronization CreateSync(const Device& device, const Swapchain& swapchain) {
        Helper::Debug::Graph("VulkanTools::CreateSync() : create vulkan synchronizations...");

        Synchronization sync = {};

        sync.m_imageAvailableSemaphores.resize(SR_MAX_FRAMES_IN_FLIGHT);
        sync.m_renderFinishedSemaphores.resize(SR_MAX_FRAMES_IN_FLIGHT);
        sync.m_inFlightFences.resize(SR_MAX_FRAMES_IN_FLIGHT);
        sync.m_imagesInFlight.resize(swapchain.m_swapChainImages.size(), VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < SR_MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &sync.m_imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(device, &semaphoreInfo, nullptr, &sync.m_renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(device, &fenceInfo, nullptr, &sync.m_inFlightFences[i]) != VK_SUCCESS)
            {
                Helper::Debug::Error("VulkanTools::CreateSync() : failed to create synchronization objects for a frame!");
                return {};
            }
        }

        sync.m_ready = true;

        return sync;
    }

    static VkRenderPass CreateRenderPass(const Device& device, const Swapchain& swapchain) {
        Helper::Debug::Graph("VulkanTools::CreateRenderPass() : create vulkan render pass...");

        VkAttachmentDescription colorAttachment = {};
        colorAttachment.format         = swapchain.m_swapChainImageFormat;
        colorAttachment.samples        = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef = {};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass = {};
        subpass.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments    = &colorAttachmentRef;

        VkSubpassDependency dependency = {};
        dependency.srcSubpass    = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass    = 0;
        dependency.srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo renderPassInfo = {};
        renderPassInfo.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments    = &colorAttachment;
        renderPassInfo.subpassCount    = 1;
        renderPassInfo.pSubpasses      = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies   = &dependency;

        VkRenderPass renderPass = {};
        if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::CreateRenderPass() : failed to create render pass!");
            return VK_NULL_HANDLE;
        }

        return renderPass;
    }

    static VkInstance CreateInstance(
            const VkApplicationInfo& appInfo, const std::vector<const char*>& reqExts,
            const std::vector<const char*>& validLayers, const bool& enableValidLayers)
    {
        Helper::Debug::Graph("VulkanTools::CreateInstance() : create vulkan instance...");

        VkInstance instance = {};

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(reqExts.size());
        createInfo.ppEnabledExtensionNames = reqExts.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (enableValidLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validLayers.size());
            createInfo.ppEnabledLayerNames = validLayers.data();

            PopulateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT * ) & debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            Helper::Debug::Graph("VulkanTools::CreateInstance() : failed to create vulkan instance!");
            return VK_NULL_HANDLE;
        }

        return instance;
    }

    static VkDebugUtilsMessengerEXT SetupDebugMessenger(const VkInstance& instance) {
        Helper::Debug::Graph("VulkanTools::SetupDebugMessenger() : create debug messenger...");

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        PopulateDebugMessengerCreateInfo(createInfo);

        VkDebugUtilsMessengerEXT debugMessenger = {};

        if (VulkanTools::CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::SetupDebugMessenger() : failed to set up debug messenger!");
            return VK_NULL_HANDLE;
        }

        return debugMessenger;
    }

    static Swapchain CreateSwapchain(const Device& device, const Surface& surface, const BasicWindow* window) {
        Helper::Debug::Graph("VulkanTools::Swapchain() : create vulkan swapchain...");

        VulkanTools::SwapChainSupportDetails swapChainSupport = VulkanTools::QuerySwapChainSupport(device.m_physicalDevice, surface);

        VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities, window);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
            imageCount = swapChainSupport.capabilities.maxImageCount;

        Helper::Debug::Graph("VulkanTools::Swapchain() : swapchain support " + std::to_string(imageCount) + " images.");

        VkSwapchainCreateInfoKHR createInfo = {};
        createInfo.sType            = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface          = surface;

        createInfo.minImageCount    = imageCount;
        createInfo.imageFormat      = surfaceFormat.format;
        createInfo.imageColorSpace  = surfaceFormat.colorSpace;
        createInfo.imageExtent      = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        uint32_t queueFamilyIndices[] = { device.m_queue.m_iGraphicsFamily.value(), device.m_queue.m_iPresentFamily.value()};

        if (device.m_queue.m_iGraphicsFamily != device.m_queue.m_iPresentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

        createInfo.preTransform   = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode    = presentMode;
        createInfo.clipped        = VK_TRUE;

        createInfo.oldSwapchain   = VK_NULL_HANDLE;

        VulkanTools::Swapchain swapchain = {};

        Helper::Debug::Graph("VulkanTools::Swapchain() : create swapchain KHR...");

        if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain.m_swapChain) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::Swapchain() : failed to create swap chain!");
            return {};
        }

        vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
        swapchain.m_swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapchain.m_swapChainImages.data());

        swapchain.m_swapChainImageFormat = surfaceFormat.format;
        swapchain.m_swapChainExtent      = extent;

        swapchain.m_ready = true;

        return swapchain;
    }

    static Surface CreateSurface(const VkInstance& instance, BasicWindow* window){
        Helper::Debug::Graph("VulkanTools::CreateSurface() : create surface...");

        Surface surface = {};

        auto* win32Window = dynamic_cast<Win32Window*>(window);

        VkWin32SurfaceCreateInfoKHR win32SurfaceCreateInfoKhr;
        win32SurfaceCreateInfoKhr.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        win32SurfaceCreateInfoKhr.hwnd = win32Window->GetHWND();
        win32SurfaceCreateInfoKhr.hinstance = win32Window->GetHINSTANCE();
        win32SurfaceCreateInfoKhr.flags = 0;
        win32SurfaceCreateInfoKhr.pNext = nullptr;

        auto vkCreateWin32SurfaceKHR =
                (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(instance, "vkCreateWin32SurfaceKHR");

        if (vkCreateWin32SurfaceKHR(instance, &win32SurfaceCreateInfoKhr, nullptr, &surface.m_surf) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::CreateSurface(): failed to create surface!");
            return {};
        }

        surface.m_ready = true;

        return surface;
    }

    static VkPhysicalDevice PickPhysicalDevice(const VkInstance& instance, const VkSurfaceKHR& surface, const std::vector<const char*>& exts) {
        Helper::Debug::Graph("Vulkan::PickPhysicalDevice() : get device with support vulkan...");

        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0) {
            Helper::Debug::Error("VulkanTools::PickPhysicalDevice() : can't detect device with support vulkan!");
            return VK_NULL_HANDLE;
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        for (const auto& device : devices) {
            Helper::Debug::Log("VulkanTools::PickPhysicalDevice() : found device - " + VulkanTools::GetDeviceName(device));

            if (VulkanTools::IsDeviceSuitable(device, surface, exts)) {
                if (physicalDevice != VK_NULL_HANDLE) {
                    if (VulkanTools::IsBetterThan(device, physicalDevice))
                        physicalDevice = device;
                }
                else
                    physicalDevice = device;
            } else
                Helper::Debug::Warn("VulkanTools::PickPhysicalDevice() : device " + VulkanTools::GetDeviceName(device) + " isn't support extensions!");
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            Helper::Debug::Error("VulkanTools::PickPhysicalDevice() : failed to find a suitable GPU!");
            return VK_NULL_HANDLE;
        } else
            Helper::Debug::Log("VulkanTools::PickPhysicalDevice() : use device - " + VulkanTools::GetDeviceName(physicalDevice));

        return physicalDevice;
    }

    static Device InitDevice(
            const VkInstance& instance, const Surface& surface,
            const std::vector<const char*>& deviceExts,
            const std::vector<const char*>& validLayers, const bool& enableValidLayers)
    {
        Helper::Debug::Graph("VulkanTools::InitDevice() : initialize logical device...");
        Device device = {};

        device.m_physicalDevice = PickPhysicalDevice(instance, surface, deviceExts);

        device.m_queue = VulkanTools::FindQueueFamilies(device.m_physicalDevice, surface);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { device.m_queue.m_iGraphicsFamily.value(), device.m_queue.m_iPresentFamily.value()};

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExts.size());
        createInfo.ppEnabledExtensionNames = deviceExts.data();

        if (enableValidLayers) {
            Helper::Debug::Graph("VulkanTools::InitDevice() : validation layers enabled.");

            createInfo.enabledLayerCount = static_cast<uint32_t>(validLayers.size());
            createInfo.ppEnabledLayerNames = validLayers.data();
        } else {
            Helper::Debug::Graph("VulkanTools::InitDevice() : validation layers disabled.");

            createInfo.enabledLayerCount = 0;
        }

        Helper::Debug::Graph("VulkanTools::InitDevice() : create logical device...");
        if (vkCreateDevice(device.m_physicalDevice, &createInfo, nullptr, &device.m_logicalDevice) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::InitDevice() : failed to create logical device!");
            return {};
        }

        vkGetDeviceQueue(device, device.m_queue.m_iGraphicsFamily.value(), 0, &device.m_queue.m_graphicsQueue);
        vkGetDeviceQueue(device, device.m_queue.m_iPresentFamily.value(), 0, &device.m_queue.m_presentQueue);

        device.m_ready = true;

        Helper::Debug::Graph("VulkanTools::InitDevice() : device successfully initialized! \n\t\tDevice name: " +
                             std::string(VulkanTools::GetDeviceProperties(device.m_physicalDevice).deviceName)
                             + "\n\t\tGraphics queue: " + std::to_string(device.m_queue.m_iGraphicsFamily.value())
                             + "\n\t\tPresent queue: " + std::to_string(device.m_queue.m_iPresentFamily.value()));

        return device;
    }
}

#endif //GAMEENGINE_VULKANTOOLS_H
