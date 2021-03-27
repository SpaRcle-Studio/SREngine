//
// Created by Nikita on 28.03.2021.
//

#ifndef GAMEENGINE_VULKANTYPES_H
#define GAMEENGINE_VULKANTYPES_H

#include <vector>
#include <string>
#include <iostream>

#include <vulkan/vulkan.h>

namespace Framework::Graphics::VulkanTools {
    struct QueueFamilyInfo {
        int m_graphics = -1;
        int m_present = -1;
        int m_compute = -1;
        int m_transfer = -1;

        [[nodiscard]] bool IsRenderingCompatible() const {
            return m_graphics >= 0 && m_present >= 0;
        }
    };

    struct Device {
        VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
        VkDevice m_logicalDevice = VK_NULL_HANDLE;

        QueueFamilyInfo m_queueFamilies = {};

        struct {
            VkQueue m_graphics = VK_NULL_HANDLE;
            VkQueue m_present = VK_NULL_HANDLE;
        } m_queues;

        [[nodiscard]] VkPhysicalDeviceProperties GetProperties() const {
            VkPhysicalDeviceProperties properties = {};
            if (this->m_physicalDevice != VK_NULL_HANDLE)
                vkGetPhysicalDeviceProperties(this->m_physicalDevice, &properties);
            return properties;
        }

        [[nodiscard]] bool IsReady() const {
            return m_physicalDevice != VK_NULL_HANDLE &&
                   m_logicalDevice != VK_NULL_HANDLE &&
                   m_queues.m_graphics != VK_NULL_HANDLE &&
                   m_queues.m_present != VK_NULL_HANDLE &&
                   this->m_queueFamilies.IsRenderingCompatible();
        }

        void DeInit() {
            if (this->m_logicalDevice != VK_NULL_HANDLE) {
                vkDestroyDevice(m_logicalDevice, nullptr);
                this->m_logicalDevice = VK_NULL_HANDLE;
            }
            this->m_logicalDevice = VK_NULL_HANDLE;
            this->m_queues.m_graphics = VK_NULL_HANDLE;
            this->m_queues.m_present = VK_NULL_HANDLE;
            this->m_queueFamilies = {};
        }
    };

    struct SurfaceInfo {
        VkSurfaceCapabilitiesKHR m_capabilities = {};
        std::vector <VkSurfaceFormatKHR> m_formats;
        std::vector <VkPresentModeKHR> m_presentModes;

        [[nodiscard]] bool IsFormatSupported(VkFormat format) const {
            if (m_formats.size() == 1 && m_formats[0].format == VK_FORMAT_UNDEFINED)
                return true;
            else if (m_formats.size() > 1) {
                for (const auto &formatEntry : m_formats)
                    if (formatEntry.format == format)
                        return true;
            }
            return false;
        }

        [[nodiscard]] bool IsColorSpaceSupported(VkColorSpaceKHR colorSpace) const {
            if (m_formats.size() == 1 && m_formats[0].format == VK_FORMAT_UNDEFINED)
                return true;
            else if (m_formats.size() > 1) {
                for (const auto &formatEntry : m_formats)
                    if (formatEntry.colorSpace == colorSpace)
                        return true;
            }
            return false;
        }

        [[nodiscard]] bool IsSurfaceFormatSupported(VkSurfaceFormatKHR surfaceFormat) const {
            if (m_formats.size() == 1 && m_formats[0].format == VK_FORMAT_UNDEFINED)
                return true;
            else if (m_formats.size() > 1) {
                for (const auto &formatEntry : m_formats)
                    if (formatEntry.format == surfaceFormat.format &&
                        formatEntry.colorSpace == surfaceFormat.colorSpace)
                        return true;
            }
            return false;
        }
    };

    struct Swapchain {
        VkSwapchainKHR m_vkSwapchainKhr = VK_NULL_HANDLE;
        std::vector <VkImage> m_swapchainImages = std::vector<VkImage>();
        std::vector <VkCommandBuffer> m_commandBuffer = std::vector<VkCommandBuffer>();
        bool m_ready = false;
    };
}

#endif //GAMEENGINE_VULKANTYPES_H
