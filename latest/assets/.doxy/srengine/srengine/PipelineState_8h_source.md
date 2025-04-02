

# File PipelineState.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pipeline**](dir_5b8a811d805f0a9bb3b25de386a42645.md) **>** [**PipelineState.h**](PipelineState_8h.md)

[Go to the documentation of this file](PipelineState_8h.md)


```C++
//
// Created by Monika on 07.12.2022.
//

#ifndef SR_ENGINE_PIPELINE_STATE_H
#define SR_ENGINE_PIPELINE_STATE_H

#include <Graphics/Pipeline/PipelineType.h>
#include <Graphics/Pipeline/FrameBufferFeatures.h>
#include <Graphics/Pipeline/TextureHelper.h>
#include <Graphics/Types/Descriptors.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class RenderStrategy;

    struct SRFrameBufferCreateInfo {
        SR_MATH_NS::IVector2 size;
        int32_t* pFBO = nullptr;
        DepthLayer* pDepth = nullptr;
        std::vector<ColorLayer>* colors = nullptr;
        uint8_t sampleCount = 0;
        uint32_t layersCount = 0;
        FrameBufferFeatures features;

    };

    struct SRTextureCreateInfo {
        const uint8_t* pData = nullptr;
        ImageFormat format = ImageFormat::None;
        TextureFilter filter = TextureFilter::Unknown;
        TextureCompression compression = TextureCompression::None;
        uint32_t width = 0;
        uint32_t height = 0;
        uint8_t mipLevels = 0;
        bool alpha = false;
        bool cpuUsage = false;
    };

    struct SRCubeMapCreateInfo {
        std::array<const uint8_t*, 6> data = {};
        uint32_t width = 0;
        uint32_t height = 0;
        bool cpuUsage = false;
    };

    struct SRDescriptorUpdateInfo {
        DescriptorType descriptorType = DescriptorType::Unknown;
        uint32_t binding = 0;
        uint32_t ubo = 0;
    };

    using SRDescriptorUpdateInfos = std::vector<SRDescriptorUpdateInfo>;

    struct PipelinePreInitInfo {
        uint32_t samplesCount = 0;
        std::string appName;
        std::string engineName;
        bool vsync = false;
        SR_UTILS_NS::Path GLSLCompilerPath;
    };

    struct PipelineTextureCreateInfo {
        uint8_t* pData = nullptr;
        ImageFormat format = ImageFormat::Unknown;
        SR_MATH_NS::IVector2 size;
        TextureFilter filter = TextureFilter::Unknown;
        TextureCompression compression = TextureCompression::None;
        uint8_t mipLevels = 0;
        bool alpha = false;
        bool cpuUsage = false;
    };

    struct PipelineState {
    public:
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;

    public:
        ShaderPtr pShader = nullptr;
        FramebufferPtr pFrameBuffer = nullptr;

        int32_t buildIteration = 0;

        int32_t UBOId = SR_ID_INVALID;
        int32_t FBOId = SR_ID_INVALID;
        int32_t SSBOId = SR_ID_INVALID;
        int32_t IBOId = SR_ID_INVALID;
        int32_t VBOId = SR_ID_INVALID;
        int32_t descriptorSetId = SR_ID_INVALID;
        int32_t shaderId = SR_ID_INVALID;
        int32_t frameBufferId = SR_ID_INVALID;

        uint32_t frameBufferLayer = 0;

        RenderStrategy* pRenderStrategy = nullptr;

        mutable uint32_t drawCalls = 0;
        mutable uint32_t vertices = 0;
        mutable uint32_t operations = 0;

        mutable uint32_t transferredMemory = 0;
        mutable uint32_t transferredCount = 0;
        mutable uint32_t allocatedMemory = 0;

        mutable uint32_t usedTextures = 0;
        mutable uint32_t usedShaders = 0;

        mutable uint32_t allocations = 0;
        mutable uint32_t deletions = 0;

    };
}

#endif //SR_ENGINE_PIPELINE_STATE_H
```


