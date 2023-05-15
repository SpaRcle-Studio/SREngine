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
        /// --------------------------------------- Главные методы рендера ---------------------------------------------

        /// Отрисовка кадра на экран
        /// После вызова функции кадр считается законченным и PipelineState очищается
        virtual void DrawFrame();

        /// Начало записи в буффер комманд. Разделение необходимо некоторым графическим API
        virtual bool BeginCmdBuffer();

        /// Конец записи в буффер комманд. Разделение необходимо некоторым графическим API
        virtual bool EndCmdBuffer();

        /// Начало рендера в кадровый буффер или в SwapChain
        virtual bool BeginRender();
        /// Обязательно нужно вызвать после успешного вызова BeginRender
        virtual void EndRender();

        /// --------------------------------------- Вспомогательные методы ---------------------------------------------

        virtual void ClearFramebuffersQueue();

        /// Очистка кадрового буфера цветом. Если у буфера несколько attachent'ов,
        // то в colorCount нужно задать их количество
        virtual void ClearBuffers();
        virtual void ClearBuffers(float_t r, float_t g, float_t b, float_t a, float_t depth, uint8_t colorCount);
        virtual void ClearBuffers(const SR_MATH_NS::FColor& color, float_t depth, uint8_t colorCount);

        /// ------------------------------------------ Вызовы отрисовки ------------------------------------------------

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
