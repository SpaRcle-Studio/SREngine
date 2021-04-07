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
    struct Swapchain {
        unsigned int m_width  = 0;
        unsigned int m_height = 0;
        bool         m_ready  = false;

        VkSwapchainKHR             m_swapChain             = VK_NULL_HANDLE;
        std::vector<VkImage>       m_swapChainImages;
        VkFormat                   m_swapChainImageFormat;
        VkExtent2D                 m_swapChainExtent;
        std::vector<VkImageView>   m_swapChainImageViews;
        //std::vector<VkFramebuffer> m_swapChainFramebuffers;

        operator VkSwapchainKHR() const { return m_swapChain; }
    };


    enum class FBOAttach {
        ColorRGB, ColorRGBA, Depth
    };

    //! \usage Don't use malloc/alloc/calloc/free! Use operator new and delete.
    //! \warn Create only as pointer!
    class VulkanFBO {
    public:
        /*! \Info
            if pSwapchain != nullptr => frame buffer will be attach swapchain image views
         */
        VulkanFBO(const VkFramebuffer& fbo, const std::vector<FBOAttach>& attachReq,
                const std::vector<VkImageView>& attachments,
                unsigned long statMemID, Swapchain* pSwapchain = nullptr)
        {
            this->m_framebuffer = fbo;
            this->m_attachReq   = attachReq;
            this->m_attachments = attachments;
            this->m_staticMemID = (long)statMemID;
            this->m_pSwapchain  = pSwapchain;
        }
        VulkanFBO(VulkanFBO const &) = delete;
        ~VulkanFBO() {
            this->m_framebuffer = VK_NULL_HANDLE;
            this->m_attachments.clear();
            this->m_attachReq.clear();
            this->m_staticMemID = -1;
        }
    public:
        VkFramebuffer                m_framebuffer    = VK_NULL_HANDLE;
        Swapchain*                   m_pSwapchain     = nullptr;

        std::vector<FBOAttach>       m_attachReq      = {};

        std::vector<VkImageView>     m_attachments    = {};
        std::vector<VkImage>         m_images         = {};
        std::vector<VkDeviceMemory>  m_imageMemories  = {};

        long                         m_staticMemID    = -1;
    public:
        operator VkFramebuffer() const { return m_framebuffer; }
    };

    //! \usage Don't use malloc/alloc/calloc/free! Use operator new and delete.
    //! \warn Create only as pointer!
    class VulkanFBOGroup {
    public:
        VulkanFBOGroup(
                const std::vector<VulkanFBO*>& FBOs,
                const std::vector<VkCommandBuffer>& commandBuffers,
                unsigned long staticMemID)
        {
            this->m_FBOs           = FBOs;
            this->m_commandBuffers = commandBuffers;
            this->m_staticMemID    = (long)staticMemID;
        }
        VulkanFBOGroup(VulkanFBOGroup const &) = delete;
        ~VulkanFBOGroup() {
            this->m_staticMemID = -1;
            this->m_commandBuffers.clear();
            this->m_FBOs.clear();
        }
    public:
        std::vector<VulkanFBO*>      m_FBOs           = {};
        std::vector<VkCommandBuffer> m_commandBuffers = {};

        long                         m_staticMemID    = -1;
    public:
        [[nodiscard]] SR_FORCE_INLINE VkFramebuffer GetFramebuffer(const unsigned int& i) const noexcept {
            return m_FBOs[i]->m_framebuffer;
        }
        [[nodiscard]] SR_FORCE_INLINE VkCommandBuffer GetCommandBuffer(const unsigned int& i) const noexcept {
            return m_commandBuffers[i];
        }
    };

    class VulkanMesh {
    public:
        VkBuffer m_VBO            = VK_NULL_HANDLE;
        VkDeviceMemory m_VBMemory = VK_NULL_HANDLE;

        VkBuffer m_IBO            = VK_NULL_HANDLE;
        VkDeviceMemory m_IBMemory = VK_NULL_HANDLE;
    };

    //!=================================================================================================================

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR        m_capabilities = {};
        std::vector<VkSurfaceFormatKHR> m_formats      = {};
        std::vector<VkPresentModeKHR>   m_presentModes = {};
    };

    struct Synchronization {
        std::vector<VkSemaphore> m_imageAvailableSemaphores;
        std::vector<VkSemaphore> m_renderFinishedSemaphores;
        std::vector<VkFence>     m_inFlightFences;
        std::vector<VkFence>     m_imagesInFlight;
        size_t                   m_currentFrame = 0;

        bool                     m_ready = false;
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
