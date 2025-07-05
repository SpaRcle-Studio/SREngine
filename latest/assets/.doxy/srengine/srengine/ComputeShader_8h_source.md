

# File ComputeShader.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**ComputeShader.h**](ComputeShader_8h.md)

[Go to the documentation of this file](ComputeShader_8h.md)


```C++
//
// Created by Monika on 29.06.2025.
//

#ifndef SR_ENGINE_GRAPHICS_TYPES_COMPUTE_SHADER_H
#define SR_ENGINE_GRAPHICS_TYPES_COMPUTE_SHADER_H

#include <Graphics/Types/Shader.h>
#include <Graphics/Pipeline/Pipeline.h>

namespace SR_GTYPES_NS {
    class SR_RENDERER_DLL_API ComputeShader final : public SR_UTILS_NS::NonCopyable {
    public:
        using Ptr = std::unique_ptr<ComputeShader>;

    private:
        ComputeShader();

    public:
        ~ComputeShader() override;

    public:
        SR_NODISCARD static ComputeShader::Ptr Load(const SR_UTILS_NS::Path& path);

    public:
        SR_NODISCARD const SR_GTYPES_NS::Shader::Ptr& GetShader() const noexcept;
        SR_NODISCARD const SR_GRAPH_NS::Pipeline::Ptr& GetPipeline() const;

        bool BeginCompute();
        void Dispatch(uint32_t x, uint32_t y, uint32_t z);
        void Dispatch();
        void EndCompute();

    private:
        SR_GTYPES_NS::Shader::Ptr m_pShader = nullptr;
        mutable SR_GRAPH_NS::Pipeline::Ptr m_pipeline = nullptr;
        int32_t m_descriptorSet = SR_ID_INVALID;
        int32_t m_virtualUBO = SR_ID_INVALID;
        bool m_isComputeState = false;
        bool m_isDispatched = false;

    };
}

#endif //SR_ENGINE_GRAPHICS_TYPES_COMPUTE_SHADER_H
```


