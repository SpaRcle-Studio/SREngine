//
// Created by Nikita on 02.07.2021.
//

#ifndef GAMEENGINE_DYNAMICTEXTUREDESCRIPTORSET_H
#define GAMEENGINE_DYNAMICTEXTUREDESCRIPTORSET_H

#include <Utils/macros.h>
#include <EvoVulkan/Memory/Allocator.h>

namespace SR_GRAPH_NS::VulkanTypes {
    struct DynamicTextureDescriptorSet {
        int32_t         m_textureID;
        VkDescriptorSet m_descriptor;
        uint32_t        m_textureSeed;

        operator VkDescriptorSet() const { return m_descriptor; }
    };
}

#endif //GAMEENGINE_DYNAMICTEXTUREDESCRIPTORSET_H
