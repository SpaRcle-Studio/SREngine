//
// Created by Nikita on 10.06.2021.
//

#ifndef GAMEENGINE_ABSTRACTCASTS_H
#define GAMEENGINE_ABSTRACTCASTS_H

#include <vulkan/vulkan.h>
#include <Types/Descriptors.h>
#include <Debug.h>

namespace Framework::Graphics::VulkanTools {
    SR_FORCE_INLINE VkDescriptorType CastAbsDescriptorTypeToVk(const DescriptorType& descriptorType) {
        switch (descriptorType) {
            case DescriptorType::Uniform:
                return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            case DescriptorType::CombinedImage:
                return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            default: {
                Helper::Debug::Error("VulkanTools::CastAbsDescriptorTypeToVk() : unknown type!");
                return VK_DESCRIPTOR_TYPE_MAX_ENUM;
            }
        }
    }

    SR_FORCE_INLINE std::set<VkDescriptorType> CastAbsDescriptorTypeToVk(const std::set<DescriptorType>& descriptorTypes) {
        std::set<VkDescriptorType> vk = {};
        for (const auto& type : descriptorTypes) {
            switch (type) {
                case DescriptorType::Uniform: {
                    vk.insert(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
                    break;
                }
                case DescriptorType::CombinedImage: {
                    vk.insert(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
                    break;
                }
                default: {
                    Helper::Debug::Error("VulkanTools::CastAbsDescriptorTypeToVk() : unknown type!");
                    return {};
                }
            }
        }
        return vk;
    }

    // const std::vector<std::pair<DescriptorType, std::pair<uint32_t, uint32_t>>>& updateValues
   /* SR_FORCE_INLINE std::vector<VkWriteDescriptorSet> CastUpdateValuesToWriteDescriptorSets(
            const VkDescriptorSet& descriptorSet,
            const std::vector<std::pair<DescriptorType, std::pair<uint32_t, uint32_t>>>& updateValues)
    {

    }*/
}

#endif //GAMEENGINE_ABSTRACTCASTS_H
