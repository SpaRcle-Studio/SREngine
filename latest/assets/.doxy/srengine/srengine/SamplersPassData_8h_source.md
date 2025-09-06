

# File SamplersPassData.h

[**File List**](files.md) **>** [**Data**](dir_0f42f4e4163da7b79318e6e4fde7c4ea.md) **>** [**SamplersPassData.h**](SamplersPassData_8h.md)

[Go to the documentation of this file](SamplersPassData_8h.md)


```C++
//
// Created by Monika on 07.05.2024.
//

#ifndef SR_ENGINE_GRAPHICS_I_SAMPLERS_PASS_H
#define SR_ENGINE_GRAPHICS_I_SAMPLERS_PASS_H

#include <Utils/Types/StringAtom.h>

#include <Graphics/Types/Texture.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_GRAPH_NS {
    class IRenderTechnique;

    SR_ENUM_NS_CLASS_T(SamplerDataUsageType, uint8_t,
        Texture,
        FrameBufferDepth,
        FrameBufferColor
    );

    struct SamplerData : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        SamplerData() = default;
        ~SamplerData() override;

        SamplerData(SamplerData&& other) noexcept;
        SamplerData(const SamplerData& other);
        SamplerData& operator=(SamplerData&& other) noexcept;
        SamplerData& operator=(const SamplerData& other);

        void OnPostLoad() override;

        uint32_t textureId = SR_ID_INVALID;
        uint32_t fboId = SR_ID_INVALID;
        SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Texture> pTexture;

        SR_NODISCARD bool IsFrameBufferUsage() const noexcept {
            return usageType == SamplerDataUsageType::FrameBufferColor || usageType == SamplerDataUsageType::FrameBufferDepth;
        }

        SR_NODISCARD bool IsTextureUsage() const noexcept { return usageType == SamplerDataUsageType::Texture; }
        SR_NODISCARD bool IsFrameBufferColorUsage() const noexcept { return usageType == SamplerDataUsageType::FrameBufferColor; }
        SR_NODISCARD bool IsFrameBufferDepthUsage() const noexcept { return usageType == SamplerDataUsageType::FrameBufferDepth; }

        SR_UTILS_NS::StringAtom id;
        SamplerDataUsageType usageType = SamplerDataUsageType::Texture;

        SR_UTILS_NS::StringAtom fboName;
        bool global = false;
        uint64_t index = 0;

        SR_UTILS_NS::Path texturePath;
    };

    class SamplersPassData final : public SR_UTILS_NS::Serializable {
        SR_CLASS()
    public:
        ~SamplersPassData() override;

    public:
        void UseSamplers(SR_GTYPES_NS::Shader* pShader);

        SR_NODISCARD bool HasSamplers() const noexcept { return !m_samplers.empty(); }
        SR_NODISCARD bool IsSamplersDirty() const noexcept { return m_dirtySamplers; }

        void MarkSamplersDirty() { m_dirtySamplers = true; }
        void PrepareSamplers();
        void SetRenderTechnique(IRenderTechnique* pTechnique) { m_pTechnique = pTechnique; }

    private:
        std::vector<SamplerData> m_samplers;

    private:
        bool m_dirtySamplers = true;
        IRenderTechnique* m_pTechnique = nullptr;

    };
}

#endif //SR_ENGINE_GRAPHICS_I_SAMPLERS_PASS_H
```


