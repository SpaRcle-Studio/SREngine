//
// Created by Nikita on 01.04.2021.
//

#ifndef GAMEENGINE_VULKANHELPER_H
#define GAMEENGINE_VULKANHELPER_H

#include <Debug.h>
#include <Environment/Vulkan/VulkanTypes.h>
#include <Math/Vector3.h>

namespace Framework::Graphics::VulkanTools {
    static unsigned __int32 FindMemoryType(const VkPhysicalDevice &physicalDevice, unsigned __int32 typeFilter,
                                           VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        Helper::Debug::Error("VulkanTools::FindMemoryType() : failed to find suitable memory type!");
        return -1;
    }

    static std::string GetDeviceName(VkPhysicalDevice physicalDevice) {
        VkPhysicalDeviceProperties properties = {};
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);
        return properties.deviceName;
    }

    static unsigned __int32 FindMemoryTypeIndex(
            VkPhysicalDeviceMemoryProperties gpuMemoryProperties,
            VkMemoryRequirements memoryRequirements,
            VkMemoryPropertyFlags requiredProperties) {
        for (unsigned __int32 i = 0; i < gpuMemoryProperties.memoryTypeCount; ++i) {
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

    static bool CheckInstanceExtensionSupported(const std::vector<const char *> &instExtNames) {
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

        for (const char *req : instExtNames) {
            bool found = false;
            for (const auto &extProp : availableExt)
                if (strcmp(req, extProp.extensionName) == 0) {
                    found = true;
                    break;
                }
            if (!found)
                return false;
        }

        return true;
    }

    static bool
    CheckDeviceExtensionsSupported(VkPhysicalDevice physicalDevice, const std::vector<const char *> &deviceExtNames) {
        std::vector<VkExtensionProperties> availableExt;

        unsigned __int32 deviceExtCount = 0;
        vkEnumerateDeviceExtensionProperties(
                physicalDevice,
                nullptr,
                &deviceExtCount,
                nullptr);

        if (deviceExtCount == 0) {
            Helper::Debug::Warn(
                    "VulkanTools::CheckDeviceExtensionsSupported() : device isn't support extensions! Count is zero.");
            return false;
        }

        availableExt.resize(deviceExtCount);
        vkEnumerateDeviceExtensionProperties(
                physicalDevice,
                nullptr,
                &deviceExtCount,
                availableExt.data());

        for (const char *req : deviceExtNames) {
            bool found = false;
            for (const auto &extProp : availableExt) {
                //std::cout << extProp.extensionName << std::endl;
                if (strcmp(req, extProp.extensionName) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                Helper::Debug::Warn("VulkanTools::CheckDeviceExtensionsSupported() : extension \"" + std::string(req) +
                                    "\" isn't support!");
                return false;
            }
        }

        return true;
    }

    static bool CheckValidationLayersSupported(const std::vector<const char *> &validLayersNames) {
        std::vector<VkLayerProperties> availableLayers;

        unsigned int layersCount = 0;
        vkEnumerateInstanceLayerProperties(&layersCount, nullptr);

        if (layersCount == 0)
            return false;

        availableLayers.resize(layersCount);
        vkEnumerateInstanceLayerProperties(
                &layersCount,
                availableLayers.data());

        for (const char *req : validLayersNames) {
            bool found = false;
            for (const auto &layer : availableLayers) {
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

        for (unsigned int i = 0; i < queueFamilies.size(); i++) {
            VkBool32 presentationSupported = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surfaceKhr, &presentationSupported);

            if (presentationSupported && queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                qu.m_iQueueFamily = (int) i;
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

        if (formatCount > 0) {
            si.m_formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, si.m_formats.data());
        }

        //////////

        unsigned int presentModeCount = 0;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

        if (presentModeCount > 0) {
            si.m_presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount,
                                                      si.m_presentModes.data());
        }

        return si;
    }
}

#endif //GAMEENGINE_VULKANHELPER_H
