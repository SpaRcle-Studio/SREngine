//
// Created by Nikita on 25.03.2021.
//

#ifndef GAMEENGINE_VULKANTOOLS_H
#define GAMEENGINE_VULKANTOOLS_H

#include <Environment/VulkanTypes.h>

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

    static QueueFamilyInfo GetQueueFamilyInfo(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, bool uniqueStrict = false) {
        QueueFamilyInfo qfi;

        unsigned int queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        for (unsigned int i = 0; i < queueFamilies.size(); i++){
            if (queueFamilies[i].queueCount > 0 && queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                qfi.m_graphics = i;
                break;
            }
        }

        for (unsigned int i = 0; i < queueFamilies.size(); i++){
            if (i == qfi.m_graphics && uniqueStrict) {
                continue;
            }

            unsigned int presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);

            if (queueFamilies[i].queueCount > 0 && presentSupport) {
                qfi.m_present = i;
                break;
            }
        }

        return qfi;
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
            bool uniqueQueueFamilies) {
        Device resultDevice = {};

        unsigned int deviceCount = 0;
        vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            Helper::Debug::Error("VulkanTools::InitDevice() : can't detect device with Vulkan support!");
            return resultDevice;
        }

        std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
        vkEnumeratePhysicalDevices(vkInstance, &deviceCount, physicalDevices.data());

        for (const auto& physicalDevice : physicalDevices) {
            resultDevice.m_queueFamilies = GetQueueFamilyInfo(
                    physicalDevice,
                    surface,
                    uniqueQueueFamilies);

            Helper::Debug::Log("VulkanTools::InitDevice() : found device - \"" + GetDeviceName(physicalDevice) + "\"");

            if (!resultDevice.m_queueFamilies.IsRenderingCompatible()) {
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

            //std::cout << resultDevice.GetProperties().limits.maxStorageBufferRange << std::endl;
            if (resultDevice.m_physicalDevice != VK_NULL_HANDLE) {
                VkPhysicalDeviceProperties properties = {};
                vkGetPhysicalDeviceProperties(physicalDevice, &properties);

                if (properties.limits.maxStorageBufferRange < resultDevice.GetProperties().limits.maxStorageBufferRange )
                    continue;
            }


            resultDevice.m_physicalDevice = physicalDevice;
            //std::cout << resultDevice.GetProperties().limits.maxPushConstantsSize << std::endl;
            //break; // todo
            //PFN_vkGetPhysicalDeviceMemoryProperties
        }

        if (resultDevice.m_physicalDevice == VK_NULL_HANDLE) {
            Helper::Debug::Error("VulkanTools::InitDevice() : can't detect device!");
            return resultDevice;
        }

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

        unsigned __int32 queueFamilies[2] {
            (unsigned __int32)resultDevice.m_queueFamilies.m_graphics,
            (unsigned __int32)resultDevice.m_queueFamilies.m_present
        };

        for (int i = 0; i < (uniqueQueueFamilies ? 2 : 1); i++) {
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamilies[i];
            queueCreateInfo.queueCount = 1; // количество очередей
            queueCreateInfo.pQueuePriorities = nullptr;

            queueCreateInfos.push_back(queueCreateInfo);
        }

        // ========== create logical device ==============

        VkDeviceCreateInfo deviceCreateInfo = {};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
        deviceCreateInfo.queueCreateInfoCount = (unsigned int)queueCreateInfos.size();

        Helper::Debug::Graph("VulkanTools::InitDevice() : use device \""+std::string(resultDevice.GetProperties().deviceName)+"\"");

        if (!extRequired.empty()) {
            if (!CheckDeviceExtensionsSupported(resultDevice.m_physicalDevice, extRequired)) {
                Helper::Debug::Error("VulkanTools::InitDevice() : not all required device extensions supported!");
                return resultDevice;
            }

            deviceCreateInfo.enabledExtensionCount = (unsigned __int32)extRequired.size();
            deviceCreateInfo.ppEnabledExtensionNames = extRequired.data();
        }

        if (!validLayersRequired.empty()) {
            if (!CheckValidationLayersSupported(validLayersRequired)) {
                Helper::Debug::Error("VulkanTools::InitDevice() : not all required validation layers supported!");
                return resultDevice;
            }
        }

        VkPhysicalDeviceFeatures deviceFeatures = {};
        deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

        if (vkCreateDevice(resultDevice.m_physicalDevice, &deviceCreateInfo, nullptr, &(resultDevice.m_logicalDevice)) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::InitDevice() : failed to create logical device!");
            return resultDevice;
        }

        vkGetDeviceQueue(
                resultDevice.m_logicalDevice,
                resultDevice.m_queueFamilies.m_graphics,
                0,
                &(resultDevice.m_queues.m_graphics));

        vkGetDeviceQueue(
                resultDevice.m_logicalDevice,
                resultDevice.m_queueFamilies.m_present,
                0,
                &(resultDevice.m_queues.m_present));

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
        Helper::Debug::Graph("VulkanTools::DeInitDevice() : device successfully destroyrd!");
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
                Helper::Debug::Log("VulkanTools::InitSwapchain() : use present mode MAILBOX.");
                presentModeKhr = current;
            }
        if (!presentModeKhr) {
            Helper::Debug::Log("VulkanTools::InitSwapchain() : use present mode FIFO.");
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

        //!=============================================================================================================

        Swapchain swapchain = {};
        swapchain.m_vkSwapchainKhr = swapchainKhr;
        swapchain.m_ready = true;

        unsigned __int32 nImages = 0;
        vkGetSwapchainImagesKHR(device.m_logicalDevice, swapchainKhr, &nImages, nullptr);

        swapchain.m_swapchainImages.resize(nImages);
        vkGetSwapchainImagesKHR(device.m_logicalDevice, swapchainKhr, &nImages, swapchain.m_swapchainImages.data());

        return swapchain;
    }
}

#endif //GAMEENGINE_VULKANTOOLS_H
