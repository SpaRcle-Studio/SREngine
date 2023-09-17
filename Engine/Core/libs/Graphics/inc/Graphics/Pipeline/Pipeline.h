//
// Created by Monika on 07.12.2022.
//

#ifndef SR_ENGINE_PIPELINE_H
#define SR_ENGINE_PIPELINE_H

#include <Utils/Math/Vector3.h>

#include <Graphics/Pipeline/PipelineState.h>
#include <Graphics/Pipeline/FrameBufferQueue.h>
#include <Graphics/Pipeline/IShaderProgram.h>
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
        using ShaderProgram = int32_t;
    public:
        explicit Pipeline(const RenderContextPtr& pContext);
        virtual ~Pipeline();

        /// ---------------------------------------- Инициализация рендера ---------------------------------------------

        /// Предназначено для инициализации всех структур и классов
        virtual bool PreInit(const PipelinePreInitInfo& info);

        /// Подключаем окно и настраиваем взаимодействие рендера с ним
        virtual bool Init() { return true; }

        /// Профайлинг и прочие пост-штучки
        virtual bool PostInit() { return true; }

        /// Чистим все данные графического конфейера и де-инициализируем его
        virtual bool Destroy() { return true; }

        SR_NODISCARD virtual PipelineType GetType() const noexcept = 0;

        /// --------------------------------------- Главные методы рендера ---------------------------------------------

        /// Вызывается перед началом рендера, подготовка к рендеру
        virtual void PrepareFrame();

        /// Вызывается в начале постоения сцены рендера, чистит очередь рендера.
        virtual void ClearFrameBuffersQueue();

        /// Отрисовка кадра на экран
        /// После вызова функции кадр считается законченным и PipelineState очищается
        virtual void DrawFrame();

        /// Начало записи в буффер комманд. Разделение необходимо некоторым графическим API
        virtual bool BeginCmdBuffer();

        /// Конец записи в буффер комманд. Разделение необходимо некоторым графическим API
        virtual void EndCmdBuffer();

        /// Начало рендера в кадровый буффер или в SwapChain
        virtual bool BeginRender();

        /// Обязательно нужно вызвать после успешного вызова BeginRender
        virtual void EndRender();

        virtual void SetViewport(int32_t width = -1, int32_t height = -1) { ++m_state.operations; };
        virtual void SetScissor(int32_t width = -1, int32_t height = -1) { ++m_state.operations; };

        /// ------------------------------------------ Работа с Overlay ------------------------------------------------

        virtual bool InitOverlay();
        virtual void DestroyOverlay();
        virtual void ReCreateOverlay();
        virtual void SetOverlaySurfaceDirty();

        virtual SR_HTYPES_NS::SharedPtr<Overlay> GetOverlay(OverlayType overlayType) const;
        virtual bool BeginDrawOverlay(OverlayType overlayType);
        virtual void EndDrawOverlay(OverlayType overlayType);

        virtual void SetOverlayEnabled(bool enabled);

        /// --------------------------------------- Вспомогательные методы ---------------------------------------------

        SR_NODISCARD virtual std::string GetVendor() const { return "None"; }
        SR_NODISCARD virtual std::string GetRenderer() const { return "None"; }
        SR_NODISCARD virtual std::string GetVersion() const { return "None"; }

        SR_NODISCARD WindowPtr GetWindow() const { return m_window; }
        SR_NODISCARD ShaderPtr GetCurrentShader() const { ++m_state.operations; return m_state.pShader; }
        SR_NODISCARD FramebufferPtr GetCurrentFrameBuffer() const noexcept { ++m_state.operations; return m_state.pFrameBuffer; }
        SR_NODISCARD int32_t GetCurrentShaderId() const { ++m_state.operations; return m_state.shaderId; }
        SR_NODISCARD int32_t GetCurrentFrameBufferId() const noexcept { ++m_state.operations; return m_state.frameBufferId; }
        SR_NODISCARD int32_t GetCurrentUBO() const noexcept { ++m_state.operations; return m_state.UBOId; }
        SR_NODISCARD int32_t GetCurrentDescriptorSet() const noexcept { ++m_state.operations; return m_state.descriptorSetId; }
        SR_NODISCARD bool IsDirty() const noexcept { ++m_state.operations; return m_dirty; }
        SR_NODISCARD FrameBufferQueue& GetQueue() noexcept { ++m_state.operations; return m_fboQueue; }

        SR_NODISCARD virtual void* GetCurrentFBOHandle() const { return nullptr; }
        SR_NODISCARD virtual std::set<void*> GetFBOHandles() const { return std::set<void*>(); /** NOLINT */ }
        SR_NODISCARD virtual uint8_t GetFrameBufferSampleCount() const { ++m_state.operations; return 0; }
        SR_NODISCARD virtual uint8_t GetBuildIterationsCount() const noexcept { ++m_state.operations; return 0; }
        SR_NODISCARD virtual uint8_t GetSupportedSamples() const { return m_supportedSampleCount; }
        SR_NODISCARD virtual SR_MATH_NS::FColor GetPixelColor(uint32_t textureId, uint32_t x, uint32_t y) { return SR_MATH_NS::FColor(0.f); }

        virtual void SetCurrentShader(ShaderPtr pShader) { ++m_state.operations; m_state.pShader = pShader; }
        virtual void SetCurrentShaderId(int32_t id) { ++m_state.operations; m_state.shaderId = id; }
        virtual void SetFrameBufferLayer(uint32_t layer) { ++m_state.operations; m_state.frameBufferLayer = layer; }
        virtual void SetCurrentFrameBuffer(FramebufferPtr pFrameBuffer);

        virtual void* GetOverlayTextureDescriptorSet(uint32_t textureId, OverlayType overlayType);

        virtual void PipelineError(const std::string& msg) const;

        virtual void OnResize(const SR_MATH_NS::UVector2& size);

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
        virtual void SetSampleCount(uint8_t count);

        SR_NODISCARD uint8_t GetSamplesCount() const;
        SR_NODISCARD bool IsMultiSamplingSupported() const noexcept { return m_isMultiSampleSupported; }

        /// ------------------------------------------ Работа с памятью ------------------------------------------------

        SR_NODISCARD virtual int32_t AllocateVBO(void* pVertices, Vertices::VertexType type, size_t count) { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t AllocateIBO(void* pIndices, uint32_t indexSize, size_t count, int32_t VBO) { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t AllocateUBO(uint32_t uboSize) { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t AllocDescriptorSet(const std::vector<uint64_t>& types) { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t AllocateShaderProgram(const SRShaderCreateInfo& createInfo, int32_t fbo) { return SR_ID_INVALID; };
        SR_NODISCARD virtual int32_t AllocateTexture(const SRTextureCreateInfo& createInfo) { return SR_ID_INVALID; };
        SR_NODISCARD virtual int32_t AllocateFrameBuffer(const SRFrameBufferCreateInfo& createInfo) { return SR_ID_INVALID; };
        SR_NODISCARD virtual int32_t AllocateCubeMap(const SRCubeMapCreateInfo& createInfo) { return SR_ID_INVALID; };

        virtual bool FreeDescriptorSet(int32_t* id) { return false; }
        virtual bool FreeVBO(int32_t* id) { return false; }
        virtual bool FreeIBO(int32_t* id) { return false; }
        virtual bool FreeUBO(int32_t* id) { return false; }
        virtual bool FreeFBO(int32_t* id) { return false; }
        virtual bool FreeCubeMap(int32_t* id) { return false; }
        virtual bool FreeShader(int32_t* id) { return false; }
        virtual bool FreeTexture(int32_t* id) { return false; }

        /// ------------------------------------------ Вызовы отрисовки ------------------------------------------------

        /// Отрисовка вершин по индексам
        virtual void DrawIndices(uint32_t count);

        /// Обычная отрисовка вершин
        virtual void Draw(uint32_t count);

        /// --------------------------------------------- Биндинги -----------------------------------------------------

        virtual void UseShader(uint32_t shaderProgram);
        virtual void UnUseShader();

        virtual void BindFrameBuffer(FramebufferPtr pFBO);

        /// Vertex Buffer Object - биндими для рендера вершин
        virtual void BindVBO(uint32_t VBO);

        /// Index Buffer Object - биндим для рендера вершин по индексам
        virtual void BindIBO(uint32_t IBO);

        /// Uniform Buffer Object - обеспечивает привязку для передачм данных в шейдеры
        virtual void BindUBO(uint32_t UBO);

        /// Обеспечивает обновление данных в шейдере
        virtual void UpdateUBO(uint32_t UBO, void* pData, uint64_t size);

        /// Привязываем к дескриптору юниформы. Работает не во всех API
        virtual void UpdateDescriptorSets(uint32_t descriptorSet, const SRDescriptorUpdateInfos& updateInfo);

        /// Передает данные в шейдер, которые не будут обновляться до следующего перерисовывания сцены
        /// Поддерживается не всеми API
        virtual void PushConstants(void* pData, uint64_t size);

        virtual void BindTexture(uint8_t activeTexture, uint32_t textureId);
        virtual void BindAttachment(uint8_t activeTexture, uint32_t textureId);

        /// Привязка UBO к набору дескрипторов. Поддерживается не всеми API
        virtual void BindDescriptorSet(uint32_t descriptorSet);

        virtual void ResetDescriptorSet();

    protected:
        std::map<OverlayType, SR_HTYPES_NS::SharedPtr<Overlay>> m_overlays;

        FrameBufferQueue m_fboQueue;

        bool m_isRenderState = false;
        bool m_isCmdState = false;
        bool m_enableValidationLayers = false;

        mutable uint64_t m_errorsCount = 0;

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
