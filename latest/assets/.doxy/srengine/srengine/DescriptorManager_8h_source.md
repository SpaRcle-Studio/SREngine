

# File DescriptorManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Memory**](dir_cc5176abae198c1d3b7945975349bd99.md) **>** [**DescriptorManager.h**](DescriptorManager_8h.md)

[Go to the documentation of this file](DescriptorManager_8h.md)


```C++
//
// Created by Monika on 27.04.2024.
//

#ifndef SR_ENGINE_GRAPHICS_DESCRIPTOR_MANAGER_H
#define SR_ENGINE_GRAPHICS_DESCRIPTOR_MANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/ObjectPool.h>
#include <Utils/Types/SharedPtr.h>

#include <Graphics/Types/Descriptors.h>

namespace SR_GTYPES_NS {
    class Shader;
}

namespace SR_GRAPH_NS {
    class Pipeline;

    class DescriptorManager : public SR_UTILS_NS::Singleton<DescriptorManager> {
        SR_REGISTER_SINGLETON(DescriptorManager)
        using DescriptorSet = int32_t;
        struct DescriptorSetInfo {
            void* pShaderHandle = nullptr;
            DescriptorSet descriptorSet = SR_ID_INVALID;
        };
    public:
        using VirtualDescriptorSet = int32_t;
        enum class BindResult : uint8_t {
            None,
            Success,
            Duplicated,
            Failed
        };
    public:
        void CollectUnused();

        SR_NODISCARD VirtualDescriptorSet AllocateDescriptorSet(VirtualDescriptorSet reallocation = SR_ID_INVALID);
        BindResult Bind(VirtualDescriptorSet virtualDescriptorSet);
        void Flush();

        bool FreeDescriptorSet(VirtualDescriptorSet* pVirtualDescriptorSet);

        void SetPipeline(SR_HTYPES_NS::SharedPtr<Pipeline> pipeline) noexcept { m_pipeline = std::move(pipeline); }

    private:
        SR_NODISCARD DescriptorSet AllocateMemory(SR_GTYPES_NS::Shader* pShader) const;

    private:
        SR_HTYPES_NS::ObjectPool<std::vector<DescriptorSetInfo>, VirtualDescriptorSet> m_descriptorPool;
        SR_HTYPES_NS::SharedPtr<Pipeline> m_pipeline;

        mutable std::vector<DescriptorType> m_allocationTypesCache;

    };
}

#endif //SR_ENGINE_GRAPHICS_DESCRIPTOR_MANAGER_H
```


