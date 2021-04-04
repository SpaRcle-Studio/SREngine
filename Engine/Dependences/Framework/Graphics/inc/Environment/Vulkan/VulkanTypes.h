//
// Created by Nikita on 05.04.2021.
//

#ifndef GAMEENGINE_VULKANTYPES_H
#define GAMEENGINE_VULKANTYPES_H

#define SR_MAX_FRAMES_IN_FLIGHT 2

#include <vulkan/vulkan.h>
#include <optional>
#include <string>
#include <set>

namespace Framework::Graphics::VulkanTools {
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct QueueFamily {
        std::optional<uint32_t> m_iGraphicsFamily;
        std::optional<uint32_t> m_iPresentFamily;

        VkQueue                 m_graphicsQueue = {};
        VkQueue                 m_presentQueue  = {};

        bool isComplete() const {
            return m_iGraphicsFamily.has_value() && m_iPresentFamily.has_value();
        }
    };

    struct Device {
        VkPhysicalDevice         m_physicalDevice = VK_NULL_HANDLE;
        VkDevice                 m_logicalDevice  = {};
        VulkanTools::QueueFamily m_queue          = {};

        operator VkDevice() const { return m_logicalDevice; }
    };
}

#endif //GAMEENGINE_VULKANTYPES_H
