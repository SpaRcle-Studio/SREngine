//
// Created by Nikita on 05.04.2021.
//

#ifndef GAMEENGINE_VULKANTOOLS_H
#define GAMEENGINE_VULKANTOOLS_H

#include <Environment/Vulkan/VulkanHelper.h>

namespace Framework::Graphics::VulkanTools {
    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }

    static VulkanTools::QueueFamily FindQueueFamilies(const VkPhysicalDevice& device, const VkSurfaceKHR& surface) {
        VulkanTools::QueueFamily queue;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                queue.m_iGraphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport) {
                queue.m_iPresentFamily = i;
            }

            if (queue.isComplete())
                break;

            i++;
        }

        return queue;
    }

    static bool CheckDeviceExtensionSupport(const VkPhysicalDevice& device, const std::vector<const char*>& deviceExtensions) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions)
            requiredExtensions.erase(extension.extensionName);

        return requiredExtensions.empty();
    }

    static VulkanTools::SwapChainSupportDetails QuerySwapChainSupport(const VkPhysicalDevice& device, const VkSurfaceKHR& surface) {
        VulkanTools::SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    static bool IsDeviceSuitable(const VkPhysicalDevice& device, const VkSurfaceKHR& surface, const std::vector<const char*>& exts) {
        VulkanTools::QueueFamily queue = VulkanTools::FindQueueFamilies(device, surface);

        bool extensionsSupported = CheckDeviceExtensionSupport(device, exts);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            VulkanTools::SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device, surface);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return queue.isComplete() && extensionsSupported && swapChainAdequate;
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

        VkPhysicalDevice physicalDevice = {};

        for (const auto& device : devices) {
            if (IsDeviceSuitable(device, surface, exts)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            Helper::Debug::Error("VulkanTools::PickPhysicalDevice() : failed to find a suitable GPU!");
            return VK_NULL_HANDLE;
        }

        return physicalDevice;
    }

    static Device InitDevice() {
        Device device = {};


    }
}

#endif //GAMEENGINE_VULKANTOOLS_H
