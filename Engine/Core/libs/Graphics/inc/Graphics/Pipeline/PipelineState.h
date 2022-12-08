//
// Created by Monika on 07.12.2022.
//

#ifndef SRENGINE_PIPELINESTATE_H
#define SRENGINE_PIPELINESTATE_H

#include <Graphics/Pipeline/PipelineType.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    /// Состояние графического конвейера
    /// Сбрасывается каждый кадр
    struct PipelineState {
    public:
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;

    public:
        PipelineState* pPreviousState = nullptr;

        ShaderPtr pShader = nullptr;
        FramebufferPtr pFramebuffer = nullptr;

        int32_t buildIteration = 0;

        int32_t UBOId = SR_ID_INVALID;
        int32_t FBOId = SR_ID_INVALID;
        int32_t descriptorSetId = SR_ID_INVALID;
        int32_t shaderID = SR_ID_INVALID;

        uint64_t drawCalls = 0;
        uint64_t operations = 0;
    };
}

#endif //SRENGINE_PIPELINESTATE_H
