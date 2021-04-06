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

    struct Synchronization {
        std::vector<VkSemaphore> m_imageAvailableSemaphores;
        std::vector<VkSemaphore> m_renderFinishedSemaphores;
        std::vector<VkFence>     m_inFlightFences;
        std::vector<VkFence>     m_imagesInFlight;
        size_t                   m_currentFrame = 0;

        bool                     m_ready = false;
    };

    struct Swapchain {
        unsigned int m_width  = 0;
        unsigned int m_height = 0;
        bool         m_ready  = false;

        VkSwapchainKHR             m_swapChain             = VK_NULL_HANDLE;
        std::vector<VkImage>       m_swapChainImages;
        VkFormat                   m_swapChainImageFormat;
        VkExtent2D                 m_swapChainExtent;
        std::vector<VkImageView>   m_swapChainImageViews;
        std::vector<VkFramebuffer> m_swapChainFramebuffers;

        operator VkSwapchainKHR() const { return m_swapChain; }
    };

    struct Surface {
        VkSurfaceKHR m_surf = VK_NULL_HANDLE;

        bool m_ready = false;

        operator VkSurfaceKHR() const { return m_surf; }
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
        bool                     m_ready          = false;

        operator VkDevice() const { return m_logicalDevice; }
    };
}

#endif //GAMEENGINE_VULKANTYPES_H
