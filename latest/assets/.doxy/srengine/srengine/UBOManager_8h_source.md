

# File UBOManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Memory**](dir_cc5176abae198c1d3b7945975349bd99.md) **>** [**UBOManager.h**](UBOManager_8h.md)

[Go to the documentation of this file](UBOManager_8h.md)


```C++
//
// Created by Monika on 10.06.2022.
//

#ifndef SR_ENGINE_UBO_MANAGER_H
#define SR_ENGINE_UBO_MANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Map.h>
#include <Utils/Types/ObjectPool.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_GTYPES_NS {
    class Shader;
}

namespace SR_GRAPH_NS {
    class Pipeline;
}

namespace SR_GRAPH_NS::Memory {
    struct SR_DLL_EXPORT VirtualUBOInfo : public SR_UTILS_NS::NonCopyable {
        using UBO = int32_t;

        struct Data {
            UBO ubo = SR_ID_INVALID;
            void* pShaderHandle = nullptr;
            uint16_t uboSize = 0;

            void Validate() const {
                SRAssert(ubo != SR_ID_INVALID);
                SRAssert(pShaderHandle);
                SRAssert(uboSize != 0);
            }
        };

        VirtualUBOInfo() = default;
        ~VirtualUBOInfo() override = default;

        VirtualUBOInfo(VirtualUBOInfo&& ref) noexcept {
            data = SR_UTILS_NS::Exchange(ref.data, {});
            shared = ref.shared;
        }

        VirtualUBOInfo& operator=(VirtualUBOInfo&& ref) noexcept {
            data = SR_UTILS_NS::Exchange(ref.data, {});
            shared = ref.shared;
            return *this;
        }

        void Reset() noexcept {
            data.clear();
        }

        SR_NODISCARD bool Valid() const noexcept {
            return !data.empty();
        }

        std::vector<Data> data;

        bool shared = false;

    };

    class SR_DLL_EXPORT UBOManager : public SR_UTILS_NS::Singleton<UBOManager> {
        SR_REGISTER_SINGLETON(UBOManager)
        using Super = SR_UTILS_NS::Singleton<UBOManager>;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
    public:
        using VirtualUBO = int32_t;
        using UBO = int32_t;
        
        enum class BindResult : uint8_t {
            None,
            Success,
            Duplicated,
            Failed
        };
    private:
        UBOManager();
        ~UBOManager() override;

    public:
        void SetPipeline(PipelinePtr pPipeline);
        void CollectUnused();

        SR_NODISCARD VirtualUBO AllocateUBO(VirtualUBO virtualUbo, uint32_t uboSize, bool shared);
        SR_NODISCARD VirtualUBO AllocateUBO(VirtualUBO virtualUbo, uint32_t uboSize);
        SR_NODISCARD VirtualUBO AllocateUBO(VirtualUBO virtualUbo);

        bool FreeUBO(VirtualUBO* ubo);

        BindResult BindUBO(VirtualUBO virtualUbo) noexcept;
        BindResult BindUBO(VirtualUBO virtualUbo, uint32_t uboSize) noexcept;

        BindResult BindNoDublicateUBO(VirtualUBO virtualUbo) noexcept;

        SR_NODISCARD UBO GetUBO(VirtualUBO virtualUbo) const noexcept;

    private:
        SR_NODISCARD bool AllocMemory(UBO* ubo, uint32_t uboSize);

    private:
        PipelinePtr m_pipeline;
        SR_HTYPES_NS::ObjectPool<VirtualUBOInfo, VirtualUBO> m_uboPool;

    };
}

#endif //SR_ENGINE_UBOMANAGER_H
```


