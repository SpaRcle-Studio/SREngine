//
// Created by Nikita on 10.06.2021.
//

#ifndef GAMEENGINE_ABSTRACTCASTS_H
#define GAMEENGINE_ABSTRACTCASTS_H

#include <vulkan/vulkan.h>
#include <Types/Descriptors.h>
#include <Debug.h>

namespace Framework::Graphics::VulkanTools {
    SR_FORCE_INLINE std::set<VkDescriptorType> CastAbsDescriptorTypeToVk(const std::set<DescriptorType>& descriptorTypes) {
        std::set<VkDescriptorType> vk = {};
        for (const auto& type : descriptorTypes) {
            if (type == DescriptorType::Uniform)
                vk.insert(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
            else {
                Helper::Debug::Error("VulkanTools::CastAbsDescriptorTypeToVk() : unknown type!");
                return {};
            }
        }
        return vk;
    }
}

#endif //GAMEENGINE_ABSTRACTCASTS_H
