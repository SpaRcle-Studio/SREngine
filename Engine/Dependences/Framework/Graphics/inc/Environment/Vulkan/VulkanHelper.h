//
// Created by Nikita on 05.04.2021.
//

#ifndef GAMEENGINE_VULKANHELPER_H
#define GAMEENGINE_VULKANHELPER_H

#include <Environment/Basic/BasicWindow.h>

#include <optional>
#include <string>
#include <set>

#include <Environment/Vulkan/VulkanStaticMemory.h>

namespace Framework::Graphics::VulkanTools {
    static VkSampleCountFlagBits GetMaxUsableSampleCount(const Device& device) {
        VkPhysicalDeviceProperties physicalDeviceProperties;
        vkGetPhysicalDeviceProperties(device.m_physicalDevice, &physicalDeviceProperties);

        VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
        if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
        if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
        if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
        if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
        if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
        if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

        return VK_SAMPLE_COUNT_1_BIT;
    }

    static VkFormat FindSupportedFormat(const Device& device, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
        for (VkFormat format : candidates) {
            VkFormatProperties props;
            vkGetPhysicalDeviceFormatProperties(device.m_physicalDevice, format, &props);

            if (tiling == VK_IMAGE_TILING_OPTIMAL)
                if (((props.linearTilingFeatures & features) == features) || ((props.optimalTilingFeatures & features) == features))
                    return format;
        }

        Helper::Debug::Error("VulkanTools::FindSupportedFormat() : failed to find supported format!");
        return VkFormat::VK_FORMAT_UNDEFINED;
    }

    static VkFormat FindDepthFormat(const Device& device) {
        return FindSupportedFormat(device,
                {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
                VK_IMAGE_TILING_OPTIMAL,
                VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
        );
    }

    static VulkanFBO* CreateFramebuffer(
            const Device& device, const VkRenderPass& renderPass,
            unsigned int width, unsigned int height,
            const std::vector<FBOAttach>& attachReq,
            Swapchain* swapchain = nullptr, __int16 swapImgID = -1)
    {
        Helper::Debug::Log("VulkanTools::CreateFramebuffer() : create vulkan framebuffer...");

        std::vector<VkImageView> attachments = {};

        {
            if (swapchain && swapImgID >= 0) {
                attachments.push_back(swapchain->m_swapChainImageViews[swapImgID]);
            }
            //    attachments.insert(attachments.end(),
            //            swapchain->m_swapChainImageViews.begin(),
             //           swapchain->m_swapChainImageViews.end());

            for (const auto& req : attachReq)
                switch (req) {
                    default:
                        Helper::Debug::Error("VulkanTools::CreateFramebuffer() : unknown required attachment!");
                        break;
                }
        }

        if (attachments.empty()) {
            Helper::Debug::Error("VulkanTools::CreateFramebuffer() : failed to create framebuffer! Attachments is empty!");
            return nullptr;
        }

        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass              = renderPass;
        framebufferInfo.attachmentCount         = attachments.size();
        framebufferInfo.pAttachments            = attachments.data();
        framebufferInfo.width                   = width;
        framebufferInfo.height                  = height;
        framebufferInfo.layers                  = 1;

        VkFramebuffer framebuffer = {};
        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &framebuffer) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::CreateFramebuffer() : failed to create framebuffer!");
            return nullptr;
        }

        long id = VulkanStaticMemory::GetFreeID<VulkanFBO>();
        if (id < 0) {
            Helper::Debug::Error("VulkanTools::CreateFramebuffer() : failed to allocate id for framebuffer!");
            return nullptr;
        }
        auto *fbo = new VulkanFBO(framebuffer, attachReq, attachments, id, swapchain);

        return fbo;
    }

    static std::vector<VkImageView> CreateImageViews(const Device& device, const std::vector<VkImage>& images, const VkFormat& format) {
        Helper::Debug::Graph("VulkanTools::CreateImageViews() : create " + std::to_string(images.size()) + " image views...");

        std::vector<VkImageView> viewImages(images.size());

        for (size_t i = 0; i < images.size(); i++) {
            VkImageViewCreateInfo createInfo           = {};
            createInfo.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image                           = images[i];
            createInfo.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format                          = format;
            createInfo.components.r                    = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g                    = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b                    = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a                    = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel   = 0;
            createInfo.subresourceRange.levelCount     = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount     = 1;

            if (vkCreateImageView(device, &createInfo, nullptr, &viewImages[i]) != VK_SUCCESS) {
                Helper::Debug::Error("VulkanTools::CreateImageViews() : failed to create image views!");
                return {};
            }
        }

        return viewImages;
    }

    static VkShaderModule CreateShaderModule(const VulkanTools::Device& device, const std::vector<char>& code) {
        Helper::Debug::Graph("VulkanTools::CreateShaderModule() : create vulkan shader module...");

        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            Helper::Debug::Error("VulkanTools::CreateShaderModule() : failed to create shader module!");
            return VK_NULL_HANDLE;
        }

        return shaderModule;
    }

    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, const BasicWindow* window) {
        if (capabilities.currentExtent.width != UINT32_MAX) {
            return capabilities.currentExtent;
        } else {
            VkExtent2D actualExtent = {
                    static_cast<uint32_t>(window->GetWidth()),
                    static_cast<uint32_t>(window->GetHeight())
            };

            actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
            actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

            return actualExtent;
        }
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        Helper::Debug::Log("debugCallback() : validation layer: " + std::string(pCallbackData->pMessage));
        return VK_FALSE;
    }

    static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
        Helper::Debug::Log("VulkanTools::PopulateDebugMessengerCreateInfo() : create vulkan debug callback...");
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
    }

    static VkPhysicalDeviceProperties GetDeviceProperties(const VkPhysicalDevice& physicalDevice) {
        VkPhysicalDeviceProperties physicalDeviceProperties = {};
        vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
        return physicalDeviceProperties;
    }

    static bool IsBetterThan(const VkPhysicalDevice& _new, const VkPhysicalDevice& _old) {
        auto _newProp = GetDeviceProperties(_new);
        auto _oldProp = GetDeviceProperties(_old);

        return _newProp.limits.maxStorageBufferRange > _oldProp.limits.maxStorageBufferRange;
    }

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

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.m_capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.m_formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.m_formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.m_presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.m_presentModes.data());
        }

        return details;
    }

    static bool IsDeviceSuitable(const VkPhysicalDevice& device, const VkSurfaceKHR& surface, const std::vector<const char*>& exts) {
        VulkanTools::QueueFamily queue = VulkanTools::FindQueueFamilies(device, surface);

        bool extensionsSupported = CheckDeviceExtensionSupport(device, exts);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            VulkanTools::SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device, surface);
            swapChainAdequate = !swapChainSupport.m_formats.empty() && !swapChainSupport.m_presentModes.empty();
        }

        return queue.isComplete() && extensionsSupported && swapChainAdequate;
    }
}

#endif //GAMEENGINE_VULKANHELPER_H
