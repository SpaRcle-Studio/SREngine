

# File DynamicTextureDescriptorSet.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pipeline**](dir_b95270d167403b29f5d572cffd5b214a.md) **>** [**Vulkan**](dir_f68684f6785c69ede334c05a5da1778e.md) **>** [**DynamicTextureDescriptorSet.h**](DynamicTextureDescriptorSet_8h.md)

[Go to the documentation of this file](DynamicTextureDescriptorSet_8h.md)


```C++
//
// Created by Nikita on 02.07.2021.
//

#ifndef SR_ENGINE_DYNAMICTEXTUREDESCRIPTORSET_H
#define SR_ENGINE_DYNAMICTEXTUREDESCRIPTORSET_H

#include <Graphics/macros.h>

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

#endif //SR_ENGINE_DYNAMICTEXTUREDESCRIPTORSET_H
```


