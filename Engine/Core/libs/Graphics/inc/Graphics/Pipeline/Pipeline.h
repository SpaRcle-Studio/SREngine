//
// Created by Monika on 07.12.2022.
//

#ifndef SRENGINE_PIPELINE_H
#define SRENGINE_PIPELINE_H

#include <Utils/Math/Vector3.h>
#include <Graphics/Pipeline/PipelineState.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class RenderContext;

    class Pipeline : public SR_UTILS_NS::NonCopyable {
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext>;
        using WindowPtr = SR_HTYPES_NS::SafePtr<Window>;
    public:
        /// ---------------------------------------- Инициализация рендера ---------------------------------------------

        /// Предназначено для инициализации всех структур и классов
        virtual bool PreInit(const PipelinePreInitInfo& info) { return false; }

        /// Подключаем окно и настраиваем взаимодействие рендера с ним
        virtual bool Init(const WindowPtr& pMainWindow) { return false; }

        /// Профайлинг и прочие пост-штучки
        virtual bool PostInit() { return false; }

        /// Чистим все данные графического конфейера и де-инициализируем его
        virtual bool Destroy() { return false; }

        SR_NODISCARD virtual PipelineType GetType() const noexcept = 0;

        /// --------------------------------------- Главные методы рендера ---------------------------------------------

        /// Вызывается перед началом рендера, подготовка к рендеру
        virtual void PrepareFrame();

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

        /// Вызывается в начале постоения сцены рендера, чистит очередь рендера.
        virtual void ClearFramebuffersQueue();

        /// Очистка кадрового буфера цветом. Если у буфера несколько attachment'ов,
        /// то в colorCount нужно задать их количество
        virtual void ClearBuffers();
        virtual void ClearBuffers(float_t r, float_t g, float_t b, float_t a, float_t depth, uint8_t colorCount);
        virtual void ClearBuffers(const std::vector<SR_MATH_NS::FColor>& colors, float_t depth);

        /// ------------------------------------------ Вызовы отрисовки ------------------------------------------------

        /// Отрисовка вершин по индексам
        virtual void DrawIndices(uint32_t count);

        /// Обычная отрисовка вершин
        virtual void Draw(uint32_t count);

        /// --------------------------------------------- Биндинги -----------------------------------------------------

        /// Vertex Buffer Object - биндими для рендера вершин
        virtual void BindVBO(uint32_t VBO);

        /// Index Buffer Object - биндим для рендера вершин по индексам
        virtual void BindIBO(uint32_t IBO);

        /// Uniform Buffer Object - обеспечивает привязку для передачм данных в шейдеры
        virtual void BindUBO(uint32_t UBO);

        /// Обеспечивает обновление данных в шейдере
        virtual void UpdateUBO(void* pData, uint64_t size);

        /// Передает данные в шейдер, которые не будут обновляться до следующего перерисовывания сцены
        /// Поддерживается не всеми API
        virtual void PushConstants(void* pData, uint64_t size);

        virtual void BindTexture(uint8_t activeTexture, uint32_t textureId);
        virtual void BindAttachment(uint8_t activeTexture, uint32_t textureId);

        /// Привязка UBO к набору дескрипторов. Поддерживается не всеми API
        virtual void BindDescriptorSet(uint32_t descriptorSet);

    private:
        bool m_isRenderState = false;

        uint64_t m_errorsCount = 0;

        std::atomic<bool> m_dirty = false;

        PipelineState m_state;
        PipelineState m_previousState;
        /// Состояние, которое было на момент постоения сцены рендера
        PipelineState m_buildState;

    };
}

#endif //SRENGINE_PIPELINE_H
