//
// Created by Nikita on 06.04.2021.
//

#ifndef GAMEENGINE_VULKANSTATICMEMORY_H
#define GAMEENGINE_VULKANSTATICMEMORY_H

#include <Environment/Vulkan/VulkanTypes.h>
#include <type_traits>

namespace Framework::Graphics::VulkanTools {
    class VulkanStaticMemory {
    public:
        VulkanStaticMemory() = delete;
        VulkanStaticMemory(VulkanStaticMemory const &) = delete;
        ~VulkanStaticMemory() = delete;
    private:
        inline static bool              m_allocated          = false;
    public:
        inline static uint64_t          m_maxCountFBOs       = 0;
        inline static VulkanFBO**       m_FBOs               = nullptr;

        inline static uint64_t          m_maxCountFBOGroups  = 0;
        inline static VulkanFBOGroup**  m_FBOGroups           = nullptr;


        //inline static uint64_t     m_maxCountImgViews   = 0;
        //inline static VkImageView* m_imgViews           = nullptr;
    public:
        template<typename T> static long GetFreeID() {
            if (std::is_same<T, VulkanFBO>::value) {
                for (uint64_t i = 0; i < m_maxCountFBOs; i++)
                    if (m_FBOs[i] == nullptr)
                        return i;
            }
            else if (std::is_same<T, VulkanFBOGroup>::value) {
                for (uint64_t i = 0; i < m_maxCountFBOGroups; i++)
                    if (m_FBOGroups[i] == nullptr)
                        return i;
            }
            //else if (std::is_same<T, VkImageView>::value) {
            //    for (uint64_t i = 0; i < m_maxCountImgViews; i++)
            //        if (m_imgViews[i] == nullptr)
            //            return i;
            //}

            Helper::Debug::Error("VulkanStaticMemory::GetFreeID() : failed find free ID for type \""+std::string(typeid(T).name())+"\"!");

            return -1;
        }
    public:
        static bool Alloc(const uint64_t& maxCountFBOs, const uint64_t& maxCountFBOGroups) {
            if (m_allocated) return false;

            Helper::Debug::System("VulkanStaticMemory::Alloc() : allocate all memory buffers...");

            m_maxCountFBOs = maxCountFBOs;
            m_FBOs = (VulkanFBO**)malloc(sizeof(VulkanFBO) * m_maxCountFBOs);
            for (uint64_t i = 0; i < m_maxCountFBOs; i++)
                m_FBOs[i] = nullptr;

            m_maxCountFBOGroups = maxCountFBOGroups;
            m_FBOGroups = (VulkanFBOGroup**)malloc(sizeof(VulkanFBOGroup) * m_maxCountFBOGroups);
            for (uint64_t i = 0; i < m_maxCountFBOGroups; i++)
                m_FBOGroups[i] = nullptr;

            //m_maxCountImgViews = maxCountImgViews;
            //m_imgViews = (VkImageView*)malloc(sizeof(VkImageView) * m_maxCountImgViews);
            //for (uint64_t i = 0; i < m_maxCountImgViews; i++)
            //    m_imgViews[i] = nullptr;

            m_allocated = true;
            return true;
        }

        static bool Free() {
            return false;
        }
    };
}

#endif //GAMEENGINE_VULKANSTATICMEMORY_H
