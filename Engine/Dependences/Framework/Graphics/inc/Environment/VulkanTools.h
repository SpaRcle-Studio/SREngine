//
// Created by Nikita on 25.03.2021.
//

#ifndef GAMEENGINE_VULKANTOOLS_H
#define GAMEENGINE_VULKANTOOLS_H

#include <vulkan/vulkan.h>

#include <vector>
#include <string>

namespace Framework::Graphics::VulkanTools {
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
    static bool CheckInstanceLauersSupported(const std::vector<const char*>& validLayersNames) {
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
            for (const auto& layer : availableLayers)
                if (strcmp(req, layer.layerName) == 0) {
                    found = true;
                    break;
                }
            if (!found)
                return false;
        }

        return true;
    }
}

#endif //GAMEENGINE_VULKANTOOLS_H
