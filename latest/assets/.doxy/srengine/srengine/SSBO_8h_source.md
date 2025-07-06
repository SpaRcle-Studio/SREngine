

# File SSBO.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Memory**](dir_dc778743e05f6f13753dd9bf5a4bd428.md) **>** [**SSBO.h**](SSBO_8h.md)

[Go to the documentation of this file](SSBO_8h.md)


```C++
//
// Created by Monika on 06.07.2025.
//

#ifndef SR_ENGINE_GRAPHICS_MEMORY_SSBO_H
#define SR_ENGINE_GRAPHICS_MEMORY_SSBO_H

#include <Graphics/Pipeline/Pipeline.h>
#include <Graphics/Pipeline/TextureHelper.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_STRUCT_T(SSBOFlags, uint32_t,
        None              = 0,                   
        Counter           = 1 << 1,              
        Structured        = 1 << 2,              
        StructuredCounter = Counter | Structured 
    )

    class SR_RENDERER_DLL_API SSBOInstance final : public SR_UTILS_NS::NonCopyable {
    public:
        using Ptr = std::unique_ptr<SSBOInstance>;

    private:
        SSBOInstance();

    public:
        ~SSBOInstance() override;

    public:
        SR_NODISCARD static SSBOInstance::Ptr Create(
            uint64_t size,
            SSBOUsage usage = SSBOUsage::Auto,
            SR_UTILS_NS::StringAtom name = SR_UTILS_NS::StringAtom(),
            SSBOFlags flags = SSBOFlags::None
        );

        template<typename T> SR_NODISCARD static SSBOInstance::Ptr Create(
            uint64_t count,
            SSBOUsage usage = SSBOUsage::Auto,
            SR_UTILS_NS::StringAtom name = SR_UTILS_NS::StringAtom(),
            SSBOFlags flags = SSBOFlags::None
        ) {
            return Create(sizeof(T) * count, usage, name, flags);
        }

        SR_NODISCARD Pipeline::Ptr GetPipeline() const noexcept;
        void DeAllocate();

        void Resize(uint64_t size);
        void SetUsage(SSBOUsage usage);
        void SetSizeAndUsage(uint64_t size, SSBOUsage usage);
        void SetName(SR_UTILS_NS::StringAtom name);

        void Flush(uint32_t offset = 0, uint32_t size = SR_UINT32_MAX);
        void FlushCounter();
        void* Map() const;
        void* MapData() const;
        void UnMap() const;

        void UpdateSSBO(const void* pData, uint64_t size = SR_UINT64_MAX);

        void Memset(int32_t value, uint64_t offset = 0, uint64_t size = SR_UINT32_MAX);
        void ResetCounter(uint32_t value = 0);

        bool Bind(SR_UTILS_NS::StringAtom name = SR_UTILS_NS::StringAtom()) const;

        SR_NODISCARD int32_t GetSSBO() const noexcept;
        SR_NODISCARD uint32_t GetCounter() const;
        SR_NODISCARD void* GetMappedData() const;

    private:
        bool ReAllocate();

        SR_NODISCARD uint64_t GetCounterSize() const;
        SR_NODISCARD bool HasCounter() const;
        SR_NODISCARD bool IsStructured() const;

    private:
        mutable void* m_mappedData = nullptr;
        int32_t m_SSBO = SR_ID_INVALID;
        uint64_t m_size = 0;
        SR_UTILS_NS::StringAtom m_name;
        SSBOUsage m_usage = SSBOUsage::Auto;
        SSBOFlags m_flags = SSBOFlags::None;
        mutable SR_GRAPH_NS::Pipeline::Ptr m_pipeline = nullptr;

    };
}

#endif //SR_ENGINE_GRAPHICS_MEMORY_SSBO_H
```


