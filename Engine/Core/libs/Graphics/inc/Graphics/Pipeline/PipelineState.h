//
// Created by Monika on 07.12.2022.
//

#ifndef SR_ENGINE_PIPELINESTATE_H
#define SR_ENGINE_PIPELINESTATE_H

#include <Graphics/Pipeline/PipelineType.h>
#include <Graphics/Pipeline/TextureHelper.h>
#include <Graphics/Types/Descriptors.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    struct SRFrameBufferCreateInfo {
        SR_MATH_NS::IVector2 size;
        int32_t* pFBO = nullptr;
        DepthLayer* pDepth = nullptr;
        std::vector<ColorLayer>* colors = nullptr;
        uint8_t sampleCount = 0;
        uint32_t layersCount = 0;
    };

    struct SRTextureCreateInfo {
        uint8_t* pData = nullptr;
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
        std::array<uint8_t*, 6> data = {};
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

    /// Состояние графического конвейера
    /// Сбрасывается каждый кадр
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
        int32_t descriptorSetId = SR_ID_INVALID;
        int32_t shaderId = SR_ID_INVALID;
        int32_t frameBufferId = SR_ID_INVALID;

        uint32_t frameBufferLayer = SR_ID_INVALID;

        /// Количество вызовов Draw и подобное
        mutable uint32_t drawCalls = 0;
        /// Количество всех обращений к API в процессе отрисовки
        mutable uint32_t operations = 0;

        /// Объем данных, который был передан на видеокарту в процессе отрисовки
        mutable uint32_t transferredMemory = 0;
        /// Объем выделенной памяти
        mutable uint32_t allocatedMemory = 0;

        mutable uint32_t usedTextures = 0;
        mutable uint32_t usedShaders = 0;

        /// Сколько было произведено выделений памяти
        mutable uint32_t allocations = 0;
        /// Сколько было произведено удалений памяти
        mutable uint32_t deletions = 0;

    };
}

#endif //SR_ENGINE_PIPELINESTATE_H
