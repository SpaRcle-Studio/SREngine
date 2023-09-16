//
// Created by Monika on 07.12.2022.
//

#ifndef SR_ENGINE_PIPELINE_H
#define SR_ENGINE_PIPELINE_H

#include <Utils/Math/Vector3.h>

#include <Graphics/Pipeline/PipelineState.h>
#include <Graphics/Overlay/OverlayType.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class RenderContext;
    class Overlay;

    class Pipeline : public SR_HTYPES_NS::SharedPtr<Pipeline> {
    public:
        using Super = SR_HTYPES_NS::SharedPtr<Pipeline>;
        using Ptr = SR_HTYPES_NS::SharedPtr<Pipeline>;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext>;
        using WindowPtr = SR_HTYPES_NS::SafePtr<Window>;
    public:
        explicit Pipeline(const RenderContextPtr& pContext);
        virtual ~Pipeline() = default;

        /// ---------------------------------------- Инициализация рендера ---------------------------------------------

        /// Предназначено для инициализации всех структур и классов
        virtual bool PreInit(const PipelinePreInitInfo& info) { return false; }

        /// Подключаем окно и настраиваем взаимодействие рендера с ним
        virtual bool Init(const WindowPtr& pMainWindow) { return false; }

        /// Профайлинг и прочие пост-штучки
        virtual bool PostInit() { return false; }

        /// Чистим все данные графического конфейера и де-инициализируем его
        virtual bool Destroy() { return true; }

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

        /// ------------------------------------------ Работа с Overlay ------------------------------------------------

        virtual bool InitOverlay();
        virtual void DestroyOverlay();
        virtual void ReCreateOverlay();
        virtual void SetOverlaySurfaceDirty();

        virtual bool BeginDrawOverlay(OverlayType overlayType);
        virtual void EndDrawOverlay(OverlayType overlayType);

        /// --------------------------------------- Вспомогательные методы ---------------------------------------------

        SR_NODISCARD virtual std::string GetVendor() const { return "None"; }
        SR_NODISCARD virtual std::string GetRenderer() const { return "None"; }
        SR_NODISCARD virtual std::string GetVersion() const { return "None"; }

        SR_NODISCARD WindowPtr GetWindow() const { return m_window; }
        SR_NODISCARD ShaderPtr GetCurrentShader() const { ++m_state.operations; return m_state.pShader; }
        SR_NODISCARD int32_t GetCurrentShaderId() const { ++m_state.operations; return m_state.shaderId; }

        void SetCurrentShaderId(int32_t id) { ++m_state.operations; m_state.shaderId = id; }

        virtual void OnResize(const SR_MATH_NS::UVector2& size);

        /// Вызывается в начале постоения сцены рендера, чистит очередь рендера.
        virtual void ClearFrameBuffersQueue();

        /// Очистка кадрового буфера цветом. Если у буфера несколько attachment'ов,
        /// то в colorCount нужно задать их количество
        virtual void ClearBuffers();
        virtual void ClearBuffers(float_t r, float_t g, float_t b, float_t a, float_t depth, uint8_t colorCount);
        virtual void ClearBuffers(const std::vector<SR_MATH_NS::FColor>& colors, float_t depth);

        /// Устанавливает состояние графического конвейера.
        /// Если грязный, то будет перестроена сцена
        /// Если чистый, то считаем, что постороение сцены завершено
        virtual void SetDirty(bool dirty);
        virtual void SetBuildIteration(uint8_t iteration);

        virtual uint64_t GetUsedMemory() const { return 0; }

        /// ------------------------------------------- Мультисемплинг -------------------------------------------------

        virtual void OnMultiSampleChanged();
        virtual void UpdateMultiSampling();

        SR_NODISCARD uint8_t GetSamplesCount() const;
        SR_NODISCARD bool IsMultiSamplingSupported() const noexcept { return m_isMultiSampleSupported; }

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

    protected:
        std::map<OverlayType, Overlay*> m_overlays;

        bool m_isRenderState = false;

        uint64_t m_errorsCount = 0;

        std::atomic<bool> m_dirty = false;

        WindowPtr m_window;
        RenderContextPtr m_renderContext;

        PipelineState m_state;
        PipelineState m_previousState;
        /// Состояние, которое было на момент постоения сцены рендера
        PipelineState m_buildState;

        /// Все параметры, относящиется к мультисемплингу
        std::optional<uint8_t> m_newSampleCount;
        uint8_t m_currentSampleCount = 0;
        uint8_t m_requiredSampleCount = 0;
        uint8_t m_supportedSampleCount = 0;
        bool m_isMultiSampleSupported = false;

    };
}

#endif //SR_ENGINE_PIPELINE_H
