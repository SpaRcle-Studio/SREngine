

# File DescriptorManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Memory**](dir_dc778743e05f6f13753dd9bf5a4bd428.md) **>** [**DescriptorManager.h**](DescriptorManager_8h.md)

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
        using Super = SR_UTILS_NS::Singleton<DescriptorManager>;
        SR_REGISTER_SINGLETON(DescriptorManager)
        using DescriptorSet = int32_t;
        struct DescriptorSetInfo {
            void* pShaderHandle = nullptr;
            uint8_t frameIndex = 0;
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
        void InitSingleton() override;

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
        std::vector<void*> m_handles;

        bool m_multiFrameMode = false;

        mutable std::vector<DescriptorType> m_allocationTypesCache;

    };
}

#endif //SR_ENGINE_GRAPHICS_DESCRIPTOR_MANAGER_H
```


