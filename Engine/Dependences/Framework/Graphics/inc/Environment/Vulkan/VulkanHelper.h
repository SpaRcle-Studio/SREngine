//
// Created by Nikita on 05.04.2021.
//

#ifndef GAMEENGINE_VULKANHELPER_H
#define GAMEENGINE_VULKANHELPER_H

#include <Environment/Vulkan/VulkanTypes.h>

#include <optional>
#include <string>
#include <set>

namespace Framework::Graphics::VulkanTools {
    static std::vector<VkPhysicalDevice> GetDevices(const VkInstance& vkInstance) {
        unsigned int deviceCount = 0;
        vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr);

        std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
        vkEnumeratePhysicalDevices(vkInstance, &deviceCount, physicalDevices.data());

        return physicalDevices;
    }

    static std::string GetDeviceName(const VkPhysicalDevice& physicalDevice) {
        VkPhysicalDeviceProperties properties = {};
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);
        return properties.deviceName;
    }

}

#endif //GAMEENGINE_VULKANHELPER_H
