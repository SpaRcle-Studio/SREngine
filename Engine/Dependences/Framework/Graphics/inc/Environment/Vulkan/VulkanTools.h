//
// Created by Nikita on 25.03.2021.
//

#ifndef GAMEENGINE_VULKANTOOLS_H
#define GAMEENGINE_VULKANTOOLS_H

#include <Environment/Vulkan/VulkanTypes.h>
#include <Math/Vector3.h>

#include <Environment/Basic/BasicWindow.h>

#ifdef WIN32
    #include <Environment/Win32Window.h>
#endif

namespace Framework::Graphics::VulkanTools {
    static std::string GetDeviceName(VkPhysicalDevice physicalDevice) {
        VkPhysicalDeviceProperties properties = {};
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);
        return properties.deviceName;
    }

    static unsigned __int32 FindMemoryTypeIndex(
            VkPhysicalDeviceMemoryProperties gpuMemoryProperties,
            VkMemoryRequirements memoryRequirements,
            VkMemoryPropertyFlags requiredProperties)
    {
        for(unsigned __int32 i = 0; i < gpuMemoryProperties.memoryTypeCount; ++i) {
            if (memoryRequirements.memoryTypeBits & (1 << i))
                if ((gpuMemoryProperties.memoryTypes[i].propertyFlags & requiredProperties) == requiredProperties)
                    return i;
        }
        Helper::Debug::Error("VulkanTools::FindMemoryTypeIndex() : couldn't find proper memory type!");
        return UINT32_MAX;
    }

    static VkPhysicalDeviceProperties GetDeviceProperties(VkPhysicalDevice physicalDevice) {
        VkPhysicalDeviceProperties physicalDeviceProperties = {};
        vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
        return physicalDeviceProperties;
    }
    static VkPhysicalDeviceMemoryProperties GetDeviceMemoryProperties(VkPhysicalDevice physicalDevice) {
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = {};
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &physicalDeviceMemoryProperties);
        return physicalDeviceMemoryProperties;
    }

    static std::vector<VkPhysicalDevice> GetDevices(VkInstance vkInstance) {
        unsigned int deviceCount = 0;
        vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr);

        std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
        vkEnumeratePhysicalDevices(vkInstance, &deviceCount, physicalDevices.data());

        return physicalDevices;
    }

    static bool CheckInstanceExtensionSupported(const std::vector<const char*>& instExtNames) {
        std::vector<VkExtensionProperties> availableExt;

        unsigned int instExtCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &instExtCount, nullptr);

        if (instExtCount == 0)
            return false;

        availableExt.resize(instExtCount);
        vkEnumerateInstanceExtensionProperties(
                nullptr,
                &instExtCount,
                availableExt.data());

        for (const char* req : instExtNames) {
            bool found = false;
            for (const auto& extProp : availableExt)
                if (strcmp(req, extProp.extensionName) == 0) {
                    found = true;
                    break;
                }
            if (!found)
                return false;
        }

        return true;
    }

    static bool CheckDeviceExtensionsSupported(VkPhysicalDevice physicalDevice, const std::vector<const char*>& deviceExtNames){
        std::vector<VkExtensionProperties> availableExt;

        unsigned __int32 deviceExtCount = 0;
        vkEnumerateDeviceExtensionProperties(
                physicalDevice,
                nullptr,
                &deviceExtCount,
                nullptr);

        if (deviceExtCount == 0) {
            Helper::Debug::Warn("VulkanTools::CheckDeviceExtensionsSupported() : device isn't support extensions! Count is zero.");
            return false;
        }

        availableExt.resize(deviceExtCount);
        vkEnumerateDeviceExtensionProperties(
                physicalDevice,
                nullptr,
                &deviceExtCount,
                availableExt.data());

        for (const char* req : deviceExtNames) {
            bool found = false;
            for (const auto& extProp : availableExt) {
                //std::cout << extProp.extensionName << std::endl;
                if (strcmp(req, extProp.extensionName) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                Helper::Debug::Warn("VulkanTools::CheckDeviceExtensionsSupported() : extension \""+std::string(req)+"\" isn't support!");
                return false;
            }
        }

        return true;
    }

    static bool CheckValidationLayersSupported(const std::vector<const char*>& validLayersNames) {
        std::vector<VkLayerProperties> availableLayers;

        unsigned int layersCount = 0;
        vkEnumerateInstanceLayerProperties(&layersCount, nullptr);

        if (layersCount == 0)
            return false;

        availableLayers.resize(layersCount);
        vkEnumerateInstanceLayerProperties(
                &layersCount,
                availableLayers.data());

        for (const char* req : validLayersNames) {
            bool found = false;
            for (const auto& layer : availableLayers) {
                if (strcmp(req, layer.layerName) == 0) {
                    found = true;
                    break;
                }
            }

            if (!found)
                return false;
        }

        return true;
    }

    static QueueUnit GetQueueFamily(VkPhysicalDevice physicalDevice, VkSurfaceKHR surfaceKhr) {
        QueueUnit qu = {};

        unsigned int queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        for (unsigned int i = 0; i < queueFamilies.size(); i++){
            VkBool32 presentationSupported = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surfaceKhr, &presentationSupported);

            if (presentationSupported && queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                qu.m_iQueueFamily = (int)i;
                break;
            }
        }

        return qu;
    }

    static SurfaceInfo GetSurfaceInfo(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
        SurfaceInfo si;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &(si.m_capabilities));

        unsigned int formatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

        if (formatCount > 0){
            si.m_formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, si.m_formats.data());
        }

        //////////

        unsigned int presentModeCount = 0;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

        if (presentModeCount > 0){
            si.m_presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, si.m_presentModes.data());
        }

        return si;
    }

    //!=================================================================================================================

    static bool CreateCommandPool(Device* device, Swapchain* swapchain) {
        VkCommandPoolCreateInfo commandPoolCreateInfo = {};
        commandPoolCreateInfo.sType                   = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        commandPoolCreateInfo.queueFamilyIndex        = device->m_queue.m_iQueueFamily;

        if (vkCreateCommandPool(device->m_logicalDevice, &commandPoolCreateInfo, nullptr, &device->m_queue.m_hCommandPool) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::CreateCommandPool() : failed to create command pool!");
            return false;
        }

        swapchain->m_commandBuffers.resize(swapchain->m_swapchainImages.size());

        VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
        commandBufferAllocateInfo.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocateInfo.commandPool                 = device->m_queue.m_hCommandPool;
        commandBufferAllocateInfo.level                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        commandBufferAllocateInfo.commandBufferCount          = (unsigned __int32)swapchain->m_commandBuffers.size();

        if (vkAllocateCommandBuffers(
                device->m_logicalDevice,
                &commandBufferAllocateInfo,
                swapchain->m_commandBuffers.data()) != VK_SUCCESS)
        {
            Helper::Debug::Error("VulkanTools::CreateCommandPool() : failed to allocate command buffers!");
            return false;
        }

        return true;
    }
    static bool CreateImageViews(Device device, Swapchain* swapchain) {
        swapchain->m_swapchainImageViews.resize(swapchain->m_swapchainImages.size());

        for (size_t i = 0; i < swapchain->m_swapchainImages.size(); i++) {
            VkImageViewCreateInfo createInfo = {};
            createInfo.sType                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image                 = swapchain->m_swapchainImages[i];
            createInfo.viewType              = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format                = swapchain->m_surfaceFormat.format;

            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

            createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel   = 0;
            createInfo.subresourceRange.levelCount     = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount     = 1;

            if (vkCreateImageView(
                    device.m_logicalDevice,
                    &createInfo, nullptr,
                    &swapchain->m_swapchainImageViews[i]) != VK_SUCCESS)
            {
                Helper::Debug::Error("VulkanTools::CreateImageViews() : failed create image view at index "+std::to_string(i)+"!");
                return false;
            }
        }

        return true;
    }
    static bool CreateDepthStencilImage(Device* device, Swapchain* swapchain, Helper::Math::Vector2 surfaceSize) {
        static const std::vector<VkFormat> try_formats {
                VK_FORMAT_D32_SFLOAT_S8_UINT,
                VK_FORMAT_D24_UNORM_S8_UINT,
                VK_FORMAT_D16_UNORM_S8_UINT,
                VK_FORMAT_D32_SFLOAT,
                VK_FORMAT_D16_UNORM
        };
        for (const auto& f : try_formats) {
            VkFormatProperties format_properties = {};
            vkGetPhysicalDeviceFormatProperties(device->m_physicalDevice, f, &format_properties);
            if(format_properties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
                swapchain->m_depthStencilFormat = f;
                break;
            }
        }

        if (swapchain->m_depthStencilFormat == VK_FORMAT_UNDEFINED) {
            Helper::Debug::Error("VulkanTools::CreateDepthStencilImage() : depth stencil format not selected!");
            return false;
        } else if (
                swapchain->m_depthStencilFormat == VK_FORMAT_D32_SFLOAT_S8_UINT ||
                swapchain->m_depthStencilFormat == VK_FORMAT_D24_UNORM_S8_UINT  ||
                swapchain->m_depthStencilFormat == VK_FORMAT_D16_UNORM_S8_UINT ||
                swapchain->m_depthStencilFormat == VK_FORMAT_S8_UINT ) swapchain->m_stencilAvailable = true;

        //!=============================================================================================================

        VkImageCreateInfo imageCreateInfo       = {};
        imageCreateInfo.sType                   = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageCreateInfo.flags                   = 0;
        imageCreateInfo.imageType               = VK_IMAGE_TYPE_2D;
        imageCreateInfo.format                  = swapchain->m_depthStencilFormat;
        imageCreateInfo.extent.width            = surfaceSize.x;
        imageCreateInfo.extent.height           = surfaceSize.y;
        imageCreateInfo.extent.depth            = 1;
        imageCreateInfo.mipLevels               = 1;
        imageCreateInfo.arrayLayers             = 1;
        imageCreateInfo.samples                 = VK_SAMPLE_COUNT_1_BIT;
        imageCreateInfo.tiling                  = VK_IMAGE_TILING_OPTIMAL;
        imageCreateInfo.usage                   = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        imageCreateInfo.sharingMode             = VK_SHARING_MODE_EXCLUSIVE;
        imageCreateInfo.queueFamilyIndexCount   = VK_QUEUE_FAMILY_IGNORED;
        imageCreateInfo.pQueueFamilyIndices     = nullptr;
        imageCreateInfo.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;

        if (vkCreateImage(device->m_logicalDevice, &imageCreateInfo, nullptr, &swapchain->m_depthStencilImage) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::CreateDepthStencilImage() : can't create depth stencil image!");
            return false;
        }


        VkMemoryRequirements imageMemoryRequirements = {};
        vkGetImageMemoryRequirements(device->m_logicalDevice, swapchain->m_depthStencilImage, &imageMemoryRequirements);

        unsigned __int32 memoryIndex = FindMemoryTypeIndex(
                GetDeviceMemoryProperties(device->m_physicalDevice),
                imageMemoryRequirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        VkMemoryAllocateInfo memoryAllocateInfo = {};
        memoryAllocateInfo.sType				= VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memoryAllocateInfo.allocationSize		= imageMemoryRequirements.size;
        memoryAllocateInfo.memoryTypeIndex	    = memoryIndex;

        if (vkAllocateMemory(device->m_logicalDevice, &memoryAllocateInfo, nullptr, &swapchain->m_depthStencilImageMemory) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::CreateDepthStencilImage() : failed to allocate memory!");
            return false;
        }
        if (vkBindImageMemory(device->m_logicalDevice, swapchain->m_depthStencilImage, swapchain->m_depthStencilImageMemory, 0) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::CreateDepthStencilImage() : failed to bind memory!");
            return false;
        }

        VkImageViewCreateInfo imageViewCreateInfo           = {};
        imageViewCreateInfo.sType				            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.image				            = swapchain->m_depthStencilImage;
        imageViewCreateInfo.viewType				        = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format				            = swapchain->m_depthStencilFormat;
        imageViewCreateInfo.components.r			        = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.g			        = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.b			        = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.a			        = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.subresourceRange.aspectMask		= VK_IMAGE_ASPECT_DEPTH_BIT | (swapchain->m_stencilAvailable ? VK_IMAGE_ASPECT_STENCIL_BIT : 0);
        imageViewCreateInfo.subresourceRange.baseMipLevel	= 0;
        imageViewCreateInfo.subresourceRange.levelCount		= 1;
        imageViewCreateInfo.subresourceRange.baseArrayLayer	= 0;
        imageViewCreateInfo.subresourceRange.layerCount		= 1;

        if (vkCreateImageView(device->m_logicalDevice, &imageViewCreateInfo, nullptr, &swapchain->m_depthStencilImageView) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::CreateDepthStencilImage() : failed to create image view!");
            return false;
        }

        return true;
    }
    static bool CreateVulkanSemaphore(Device device, Swapchain* swapchain) {
        VkSemaphoreCreateInfo semaphoreCreateInfo = {};
        semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        if (vkCreateSemaphore(
                device.m_logicalDevice,
                &semaphoreCreateInfo,
                nullptr,
                &swapchain->m_vkSemaphoreImageAvailable) != VK_SUCCESS ||
            vkCreateSemaphore(
                device.m_logicalDevice,
                &semaphoreCreateInfo,
                nullptr,
                &swapchain->m_vkSemaphoreRenderingFinished) != VK_SUCCESS)
        {
            Helper::Debug::Error("VulkanTools::CreateVulkanSemaphore() : failed to create semaphore!");
            return false;
        }
        else
            return true;
    }

    //!=================================================================================================================

    static VkDevice InitLogicalDevice(
            QueueUnit* queueUnit,
            VkPhysicalDevice physicalDevice,
            const std::vector<const char*>& reqDeviceExtensions,
            const std::vector<const char*>& reqValidLayers)
    {
        Helper::Debug::Graph("VulkanTools::InitLogicalDevice() : use device \""+GetDeviceName(physicalDevice)+"\"");

        VkDevice logicalDevice = {};

        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex        = queueUnit->m_iQueueFamily;
        queueCreateInfo.queueCount              = 1; // количество очередей
        queueCreateInfo.pQueuePriorities        = nullptr;

        VkDeviceCreateInfo deviceCreateInfo     = {};
        deviceCreateInfo.sType                  = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pQueueCreateInfos      = &queueCreateInfo;
        deviceCreateInfo.queueCreateInfoCount   = 1;

        if (!reqDeviceExtensions.empty()) {
            if (!CheckDeviceExtensionsSupported(physicalDevice, reqDeviceExtensions)) {
                Helper::Debug::Error("VulkanTools::InitLogicalDevice() : not all required device extensions supported!");
                return VK_NULL_HANDLE;
            }

            deviceCreateInfo.enabledExtensionCount = (unsigned __int32)reqDeviceExtensions.size();
            deviceCreateInfo.ppEnabledExtensionNames = reqDeviceExtensions.data();
        }

        if (!reqValidLayers.empty()) {
            if (!CheckValidationLayersSupported(reqValidLayers)) {
                Helper::Debug::Error("VulkanTools::InitLogicalDevice() : not all required validation layers supported!");
                return VK_NULL_HANDLE;
            }
        }

        VkPhysicalDeviceFeatures deviceFeatures = {};
        deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

        if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::InitLogicalDevice() : failed to create logical device!");
            return VK_NULL_HANDLE;
        }

        vkGetDeviceQueue(
                logicalDevice,
                queueUnit->m_iQueueFamily,
                0,
                &(queueUnit->m_hQueue));

        Helper::Debug::Graph("VulkanTools::InitLogicalDevice() : device successfully initialized!");

        return logicalDevice;
    }

    static void DeInitWindowSurface(VkInstance vkInstance, VkSurfaceKHR* vkSurfaceKhr){
        vkDestroySurfaceKHR(vkInstance, *vkSurfaceKhr, nullptr);
        *vkSurfaceKhr = VK_NULL_HANDLE;
    }
    static VkSurfaceKHR InitWindowSurface(VkInstance vkInstance, BasicWindow* window) {
        #ifdef WIN32
            auto* win32Window = dynamic_cast<Win32Window *>(window);

            VkWin32SurfaceCreateInfoKHR win32SurfaceCreateInfoKhr;
            win32SurfaceCreateInfoKhr.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
            win32SurfaceCreateInfoKhr.hwnd = win32Window->GetHWND();
            win32SurfaceCreateInfoKhr.hinstance = win32Window->GetHINSTANCE();
            win32SurfaceCreateInfoKhr.flags = 0;
            win32SurfaceCreateInfoKhr.pNext = nullptr;

            auto vkCreateWin32SurfaceKHR =
                    (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(vkInstance, "vkCreateWin32SurfaceKHR");

            VkSurfaceKHR vkSurface;

            if (vkCreateWin32SurfaceKHR(vkInstance, &win32SurfaceCreateInfoKhr, nullptr, &vkSurface) != VK_SUCCESS)
                return nullptr;

            return vkSurface;
        #else
            return nullptr;
        #endif
    }

    static Device InitDevice(
            VkInstance vkInstance,
            VkSurfaceKHR surface,
            const std::vector<const char*>& extRequired,
            const std::vector<const char*>& validLayersRequired,
            bool uniqueQueueFamilies)
    {
        Device resultDevice = {};

        auto physicalDevices = GetDevices(vkInstance);
        if (physicalDevices.empty()) {
            Helper::Debug::Error("VulkanTools::InitDevice() : can't detect device with Vulkan support!");
            return resultDevice;
        }

        for (const auto& physicalDevice : physicalDevices) {
            Helper::Debug::Log("VulkanTools::InitDevice() : found device - \"" + GetDeviceName(physicalDevice) + "\"");

            resultDevice.m_queue = GetQueueFamily(
                    physicalDevice,
                    surface);

            if (!resultDevice.m_queue.IsRenderingCompatible()) {
                Helper::Debug::Warn("VulkanTools::InitDevice() : device isn't rendering compatible");
                continue;
            }

            if (!extRequired.empty() && !CheckDeviceExtensionsSupported(physicalDevice, extRequired)) {
                Helper::Debug::Warn("VulkanTools::InitDevice() : extensions int's support");
                continue;
            }

            SurfaceInfo si = GetSurfaceInfo(physicalDevice, surface);
            if (si.m_formats.empty() || si.m_presentModes.empty()) {
                Helper::Debug::Warn("VulkanTools::InitDevice() : formats is empty or present modes is empty");
                continue;
            }

            // Выбираем наиболее предпочтительноте устройство, если их несколько

            if (resultDevice.m_physicalDevice != VK_NULL_HANDLE) {
                VkPhysicalDeviceProperties properties = {};
                vkGetPhysicalDeviceProperties(physicalDevice, &properties);

                if (properties.limits.maxStorageBufferRange < resultDevice.GetProperties().limits.maxStorageBufferRange)
                    continue;
            }

            resultDevice.m_physicalDevice = physicalDevice;
        }

        if (resultDevice.m_physicalDevice == VK_NULL_HANDLE) {
            Helper::Debug::Error("VulkanTools::InitDevice() : can't detect device!");
            return resultDevice;
        }

        resultDevice.m_logicalDevice = InitLogicalDevice(
                &resultDevice.m_queue,
                resultDevice.m_physicalDevice,
                extRequired,
                validLayersRequired);
        if (resultDevice.m_logicalDevice == VK_NULL_HANDLE) {
            Helper::Debug::Error("VulkanTools::InitDevice() : failed to initialize logical device!");
            return {};
        }

        if (!resultDevice.IsReady()) {
            Helper::Debug::Error("VulkanTools::InitDevice() : failed to initialize device!");
            return resultDevice;
        }

        Helper::Debug::Graph("VulkanTools::InitDevice() : device successfully initialized! \n\t\tDevice name: " +
            std::string(resultDevice.GetProperties().deviceName));

        return resultDevice;
    }
    static void DeInitDevice(Device* device) {
        device->DeInit();
        //Helper::Debug::Graph("VulkanTools::DeInitDevice() : device successfully destroyed!");
    }

    static Swapchain InitSwapchain(Device device, VkSurfaceKHR surface) {
        VkSwapchainKHR swapchainKhr = {};

        SurfaceInfo si = GetSurfaceInfo(device.m_physicalDevice, surface);

        /// FORMAT
        VkSurfaceFormatKHR surfaceFormatKhr = {};
        if (si.m_formats.size() == 1 && si.m_formats[0].format == VK_FORMAT_UNDEFINED)
            surfaceFormatKhr = { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
        else
            for (const auto& current : si.m_formats){
                if (current.format == VK_FORMAT_B8G8R8A8_UNORM && current.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                    surfaceFormatKhr = current;
            }
        if (!surfaceFormatKhr.format)
            surfaceFormatKhr = si.m_formats[0];

        /// PRESENT MODE
        VkPresentModeKHR presentModeKhr = {};
        for (auto current : si.m_presentModes)
            if (current == VK_PRESENT_MODE_MAILBOX_KHR) {
                Helper::Debug::Graph("VulkanTools::InitSwapchain() : use present mode MAILBOX.");
                presentModeKhr = current;
            }
        if (!presentModeKhr) {
            Helper::Debug::Graph("VulkanTools::InitSwapchain() : use present mode FIFO.");
            presentModeKhr = VK_PRESENT_MODE_FIFO_KHR;
        }

        VkSurfaceCapabilitiesKHR surfaceCapabilitiesKhr = {};
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device.m_physicalDevice, surface, &surfaceCapabilitiesKhr);

        VkSwapchainCreateInfoKHR swapchainCreateInfoKhr = {};
        swapchainCreateInfoKhr.sType                    = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfoKhr.surface                  = surface;
        swapchainCreateInfoKhr.minImageCount            = surfaceCapabilitiesKhr.minImageCount < 3 ? surfaceCapabilitiesKhr.minImageCount : 3;
        swapchainCreateInfoKhr.imageFormat              = surfaceFormatKhr.format;
        swapchainCreateInfoKhr.imageColorSpace          = surfaceFormatKhr.colorSpace;
        swapchainCreateInfoKhr.imageExtent              = surfaceCapabilitiesKhr.currentExtent;
        swapchainCreateInfoKhr.imageArrayLayers         = 1;
        swapchainCreateInfoKhr.imageUsage               = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapchainCreateInfoKhr.imageSharingMode         = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfoKhr.preTransform             = surfaceCapabilitiesKhr.currentTransform;
        swapchainCreateInfoKhr.compositeAlpha           = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainCreateInfoKhr.presentMode              = presentModeKhr;
        swapchainCreateInfoKhr.clipped                  = VK_TRUE;
        swapchainCreateInfoKhr.oldSwapchain             = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(device.m_logicalDevice, &swapchainCreateInfoKhr, nullptr, &swapchainKhr) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::InitSwapchain() : failed to create swapchain!");
            return {};
        }

        //!===============================================[Swapchain]===================================================

        Swapchain swapchain = {};
        swapchain.m_vkSwapchainKhr = swapchainKhr;
        swapchain.m_surfaceFormat  = surfaceFormatKhr;

        unsigned __int32 nImages = 0;
        vkGetSwapchainImagesKHR(device.m_logicalDevice, swapchainKhr, &nImages, nullptr);

        Helper::Debug::Graph("VulkanTools::InitSwapchain() : swapchain has a " + std::to_string(nImages) + " images.");

        swapchain.m_swapchainImages.resize(nImages);
        vkGetSwapchainImagesKHR(device.m_logicalDevice, swapchainKhr, &nImages, swapchain.m_swapchainImages.data());

        swapchain.m_ready = true;
        return swapchain;
    }
    static void DeInitSwapchain(const Device device, Swapchain* swapchain) {
        if (swapchain->m_vkSwapchainKhr != VK_NULL_HANDLE) {
            vkDestroySwapchainKHR(device.m_logicalDevice, swapchain->m_vkSwapchainKhr, nullptr);
            swapchain->m_vkSwapchainKhr = VK_NULL_HANDLE;
        }
    }

    static VkRenderPass InitRenderPass(const Device& device, const Swapchain& swapchain) {
        std::array<VkAttachmentDescription, 2> attachments = {};
        attachments[0].flags		    = 0;
        attachments[0].format		    = swapchain.m_depthStencilFormat;
        attachments[0].samples		    = VK_SAMPLE_COUNT_1_BIT;
        attachments[0].loadOp		    = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachments[0].storeOp		    = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachments[0].stencilLoadOp    = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachments[0].stencilStoreOp   = VK_ATTACHMENT_STORE_OP_STORE;
        attachments[0].initialLayout    = VK_IMAGE_LAYOUT_UNDEFINED;
        attachments[0].finalLayout	    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        attachments[1].flags		    = 0;
        attachments[1].format		    = swapchain.m_surfaceFormat.format;
        attachments[1].samples		    = VK_SAMPLE_COUNT_1_BIT;
        attachments[1].loadOp		    = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachments[1].storeOp		    = VK_ATTACHMENT_STORE_OP_STORE;
        attachments[1].initialLayout    = VK_IMAGE_LAYOUT_UNDEFINED;
        attachments[1].finalLayout	    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;



        VkAttachmentReference subPass0DepthStencilAttachment = {};
        subPass0DepthStencilAttachment.attachment	         = 0;
        subPass0DepthStencilAttachment.layout		         = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        std::array<VkAttachmentReference, 1> subPass0ColorAttachments = {};
        subPass0ColorAttachments[0].attachment	                      = 1;
        subPass0ColorAttachments[0].layout		                      = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        std::array<VkSubpassDescription, 1> subPasses = {};
        subPasses[0].pipelineBindPoint			      = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subPasses[0].colorAttachmentCount		      = subPass0ColorAttachments.size();
        subPasses[0].pColorAttachments			      = subPass0ColorAttachments.data(); //! layout(location=0) out vec4 FinalColor;
        subPasses[0].pDepthStencilAttachment		  = &subPass0DepthStencilAttachment;



        VkRenderPassCreateInfo renderPassCreateInfo = {};
        renderPassCreateInfo.sType				    = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfo.attachmentCount	    = attachments.size();
        renderPassCreateInfo.pAttachments		    = attachments.data();
        renderPassCreateInfo.subpassCount		    = subPasses.size();
        renderPassCreateInfo.pSubpasses			    = subPasses.data();

        VkRenderPass renderPass = {};
        if (vkCreateRenderPass(device.m_logicalDevice, &renderPassCreateInfo, nullptr, &renderPass) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::InitRenderPass() : failed to create render pass!");
            return VK_NULL_HANDLE;
        }

        return renderPass;
    }
    static void DeInitRenderPass(Device device, VkRenderPass* renderPass) {
        if (*renderPass != VK_NULL_HANDLE) {
            vkDestroyRenderPass(device.m_logicalDevice, *renderPass, nullptr);
            *renderPass = VK_NULL_HANDLE;
        }
    }

    static VkFramebuffer CreateFrameBuffer(
            VkRenderPass renderPass,
            Device device,
            const std::vector<VkImageView>& attachments,
            Helper::Math::Vector2 surfaceSize)
    {
        VkFramebufferCreateInfo framebufferCreateInfo {};
        framebufferCreateInfo.sType			    = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.renderPass		= renderPass;
        framebufferCreateInfo.attachmentCount	= attachments.size();
        framebufferCreateInfo.pAttachments	    = attachments.data();
        framebufferCreateInfo.width			    = surfaceSize.x;
        framebufferCreateInfo.height			= surfaceSize.y;
        framebufferCreateInfo.layers			= 1;

        VkFramebuffer frameBuffer = {};
        if (vkCreateFramebuffer(device.m_logicalDevice, &framebufferCreateInfo, nullptr, &frameBuffer) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::CreateFrameBuffer() : failed to create frame buffer!");
            return VK_NULL_HANDLE;
        }

        return frameBuffer;
    }
    static void DestroyFrameBuffer(const Device& device, VkFramebuffer framebuffer) {
        if (framebuffer != VK_NULL_HANDLE)
            vkDestroyFramebuffer(device.m_logicalDevice, framebuffer, nullptr);
    }


    static VkFence InitSynchronizations(const Device& device) {
        VkFenceCreateInfo fenceCreateInfo = {};
        fenceCreateInfo.sType			  = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

        VkFence fence = {};
        if (vkCreateFence(device.m_logicalDevice, &fenceCreateInfo, nullptr, &fence) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::InitSynchronizations() : failed to create fence!");
            return VK_NULL_HANDLE;
        }

        return fence;
    }

    static void DeInitSynchronizations(const Device& device, VkFence* fence) {
        if (*fence != VK_NULL_HANDLE) {
            vkDestroyFence(device.m_logicalDevice, *fence, nullptr);
            *fence = VK_NULL_HANDLE;
        }
    }
}

#endif //GAMEENGINE_VULKANTOOLS_H
