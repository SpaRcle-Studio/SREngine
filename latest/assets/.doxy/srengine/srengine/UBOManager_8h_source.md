

# File UBOManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Memory**](dir_dc778743e05f6f13753dd9bf5a4bd428.md) **>** [**UBOManager.h**](UBOManager_8h.md)

[Go to the documentation of this file](UBOManager_8h.md)


```C++
//
// Created by Monika on 10.06.2022.
//

#ifndef SR_ENGINE_UBO_MANAGER_H
#define SR_ENGINE_UBO_MANAGER_H

#include <Graphics/macros.h>

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
    struct SR_RENDERER_DLL_API VirtualUBOInfo : public SR_UTILS_NS::NonCopyable {
        using UBO = int32_t;

        struct Data {
            std::array<UBO, SR_MAX_FRAMES_IN_FLIGHT> ubos;
            void* pShaderHandle = nullptr;
            uint16_t uboSize = 0;

            void Validate() const {
                SR_TRACY_ZONE;
                for (auto ubo : ubos) {
                    SRAssert(ubo != SR_ID_INVALID);
                }
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

    class SR_RENDERER_DLL_API UBOManager : public SR_UTILS_NS::Singleton<UBOManager> {
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

        void InitSingleton() override;

    private:
        SR_NODISCARD bool AllocMemory(UBO* ubo, uint32_t uboSize);

    private:
        PipelinePtr m_pipeline;
        SR_HTYPES_NS::ObjectPool<VirtualUBOInfo, VirtualUBO> m_uboPool;
        std::vector<void*> m_handles;
        bool m_multiFrameMode = false;

    };
}

#endif //SR_ENGINE_UBOMANAGER_H
```


