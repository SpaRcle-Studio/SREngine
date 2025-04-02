

# File SSBOManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Memory**](dir_cc5176abae198c1d3b7945975349bd99.md) **>** [**SSBOManager.h**](SSBOManager_8h.md)

[Go to the documentation of this file](SSBOManager_8h.md)


```C++
//
// Created by Monika on 24.04.2024.
//

#ifndef SR_GRAPHICS_ENGINE_SSBO_MANAGER_H
#define SR_GRAPHICS_ENGINE_SSBO_MANAGER_H

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


