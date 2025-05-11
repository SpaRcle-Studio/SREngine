

# File SSBOManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Memory**](dir_dc778743e05f6f13753dd9bf5a4bd428.md) **>** [**SSBOManager.h**](SSBOManager_8h.md)

[Go to the documentation of this file](SSBOManager_8h.md)


```C++
//
// Created by Monika on 24.04.2024.
//

#ifndef SR_GRAPHICS_ENGINE_SSBO_MANAGER_H
#define SR_GRAPHICS_ENGINE_SSBO_MANAGER_H

#include <Graphics/macros.h>

#include <Utils/Common/Singleton.h>
#include <Utils/Types/ObjectPool.h>

namespace SR_GTYPES_NS {
    class Shader;
}

namespace SR_GRAPH_NS {
    class Pipeline;

    class SSBOManager : public SR_UTILS_NS::Singleton<SSBOManager> {
        SR_REGISTER_SINGLETON(SSBOManager)
        using Super = SR_UTILS_NS::Singleton<SSBOManager>;
        using VirtualSSBO = int32_t;
        using SSBO = int32_t;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
    public:
        enum class BindResult : uint8_t {
            None,
            Success,
            Duplicated,
            Failed
        };
    public:
        void SetPipeline(PipelinePtr pPipeline) { m_pipeline = std::move(pPipeline); }

        SR_NODISCARD VirtualSSBO AllocateSSBO(VirtualSSBO virtualSSBO, uint32_t size, SSBOUsage usage);

        bool FreeSSBO(VirtualSSBO* pSSBO);
        BindResult BindSSBO(VirtualSSBO ssbo) noexcept;

    private:
        bool FreeMemory(SSBO* pSSBO) const;
        bool AllocateMemory(SSBO* pSSBO, uint32_t size, SSBOUsage usage) const;

    private:
        SR_HTYPES_NS::ObjectPool<SSBO, VirtualSSBO> m_ssboPool;
        PipelinePtr m_pipeline;
        void* m_identifier = nullptr;

    };
}

#endif //SR_GRAPHICS_ENGINE_SSBO_MANAGER_H
```


