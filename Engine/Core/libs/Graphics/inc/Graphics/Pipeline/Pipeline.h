//
// Created by Monika on 07.12.2022.
//

#ifndef SRENGINE_PIPELINE_H
#define SRENGINE_PIPELINE_H

#include <Graphics/Pipeline/PipelineState.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class Pipeline : public SR_UTILS_NS::NonCopyable {
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
    public:
        /// ----------------------------- Главные методы рендера ----------------------

        /// Отрисовка кадра на экран
        /// После вызова функции кадр считается законченным и PipelineState очищается
        virtual void DrawFrame();

        /// Начало рендера в кадровый буффер или в SwapChain
        virtual bool BeginRender();
        /// Обязательно нужно вызвать после успешного вызова BeginRender
        virtual void EndRender();

        /// -------------------------------- Вызовы отрисовки -------------------------

        virtual void DrawIndices(uint32_t countIndices);

    private:
        bool m_isWriteState = false;

        uint64_t m_errorsCount = 0;

        std::atomic<bool> m_dirty = false;

        PipelineState m_state;
        PipelineState m_previousState;

    };
}

#endif //SRENGINE_PIPELINE_H
