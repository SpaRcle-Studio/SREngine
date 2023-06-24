//
// Created by Monika on 07.12.2022.
//

#ifndef SRENGINE_PIPELINESTATE_H
#define SRENGINE_PIPELINESTATE_H

#include <Graphics/Pipeline/PipelineType.h>
#include <Graphics/Pipeline/TextureHelper.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    struct PipelinePreInitInfo {
        uint32_t samplesCount = 0;
        std::string appName;
        std::string engineName;
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
        FramebufferPtr pFramebuffer = nullptr;

        int32_t buildIteration = 0;

        int32_t UBOId = SR_ID_INVALID;
        int32_t FBOId = SR_ID_INVALID;
        int32_t descriptorSetId = SR_ID_INVALID;
        int32_t shaderID = SR_ID_INVALID;

        /// Количество вызовов Draw и подобное
        uint64_t drawCalls = 0;
        /// Количество всех обращений к API в процессе отрисовки
        uint64_t operations = 0;
        /// Объем данных, который был передан на видеокарту в процессе отрисовки
        uint64_t transferredMemory = 0;

        uint64_t usedTextures = 0;
        uint64_t usedShaders = 0;

    };
}

#endif //SRENGINE_PIPELINESTATE_H
