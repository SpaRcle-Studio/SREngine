//
// Created by Nikita on 28.03.2021.
//

#ifndef GAMEENGINE_VULKANTYPES_H
#define GAMEENGINE_VULKANTYPES_H

#include <vector>
#include <string>
#include <iostream>
#include <array>

#include <vulkan/vulkan.h>

namespace Framework::Graphics::VulkanTools {
    struct QueueUnit {
        int           m_iQueueFamily = -1;             // индекс семейства очередей
        VkQueue       m_hQueue       = VK_NULL_HANDLE; // очередь
        VkCommandPool m_hCommandPool = VK_NULL_HANDLE; // коммандный пул

        [[nodiscard]] bool IsRenderingCompatible() const {
            return m_iQueueFamily >= 0;
        }
        [[nodiscard]] bool IsReady() const {
            return m_iQueueFamily >= 0 && m_hQueue != VK_NULL_HANDLE && m_hCommandPool != VK_NULL_HANDLE;
        }
    };

    struct DepthStencil {
        VkImage                       m_depthStencilImage            = VK_NULL_HANDLE;
        VkImageView                   m_depthStencilImageView        = VK_NULL_HANDLE;
        VkFormat                      m_depthStencilFormat           = VK_FORMAT_UNDEFINED;
        bool                          m_stencilAvailable             = false;
        VkDeviceMemory                m_depthStencilImageMemory      = VK_NULL_HANDLE;

        [[nodiscard]] bool IsReady() const noexcept {
            return m_depthStencilImage != VK_NULL_HANDLE &&
                m_depthStencilImageMemory != VK_NULL_HANDLE &&
                m_depthStencilImageView != VK_NULL_HANDLE;
        }
    };

    struct Swapchain {
        VkSurfaceFormatKHR            m_surfaceFormat                = {};
        VkSwapchainKHR                m_vkSwapchainKhr               = VK_NULL_HANDLE;

        std::vector <VkImage>         m_swapchainImages              = std::vector<VkImage>();
        std::vector <VkImageView>     m_swapchainImageViews          = std::vector<VkImageView>();
        unsigned __int32              m_activeSwapchainImageID       = UINT32_MAX;

        VkSemaphore                   m_vkSemaphoreImageAvailable    = VK_NULL_HANDLE;
        VkSemaphore                   m_vkSemaphoreRenderingFinished = VK_NULL_HANDLE;

        VkFence                       m_swapchainImageAvailable      = VK_NULL_HANDLE;


        std::vector <VkCommandBuffer> m_commandBuffers               = std::vector<VkCommandBuffer>();
        bool                          m_ready                        = false;

        [[nodiscard]] bool IsReady() const {
            return m_ready;
        }
    };

    struct Device {
        VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
        VkDevice m_logicalDevice = VK_NULL_HANDLE;

        QueueUnit m_queue = {};

        [[nodiscard]] VkPhysicalDeviceProperties GetProperties() const {
            VkPhysicalDeviceProperties properties = {};
            if (this->m_physicalDevice != VK_NULL_HANDLE)
                vkGetPhysicalDeviceProperties(this->m_physicalDevice, &properties);
            return properties;
        }

        [[nodiscard]] bool IsReady() const {
            return m_physicalDevice != VK_NULL_HANDLE &&
                   m_logicalDevice != VK_NULL_HANDLE &&
                   m_queue.IsRenderingCompatible();
        }

        void DeInit() {
            if (this->m_logicalDevice != VK_NULL_HANDLE) {
                vkDestroyDevice(m_logicalDevice, nullptr);
                this->m_logicalDevice = VK_NULL_HANDLE;
            }
            this->m_logicalDevice = VK_NULL_HANDLE;
            this->m_queue = {};
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
}

#endif //GAMEENGINE_VULKANTYPES_H
