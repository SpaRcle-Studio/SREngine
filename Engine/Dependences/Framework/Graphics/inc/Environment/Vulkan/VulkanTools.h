//
// Created by Nikita on 05.04.2021.
//

#ifndef GAMEENGINE_VULKANTOOLS_H
#define GAMEENGINE_VULKANTOOLS_H

#include <Environment/Vulkan/VulkanHelper.h>

namespace Framework::Graphics::VulkanTools {
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
