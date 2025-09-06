

# File Pipeline.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pipeline**](dir_b95270d167403b29f5d572cffd5b214a.md) **>** [**Pipeline.h**](Pipeline_8h.md)

[Go to the documentation of this file](Pipeline_8h.md)


```C++
//
// Created by Monika on 07.12.2022.
//

#ifndef SR_ENGINE_PIPELINE_H
#define SR_ENGINE_PIPELINE_H

#include <Graphics/Pipeline/PipelineState.h>
#include <Graphics/Pipeline/FrameBufferQueue.h>
#include <Graphics/Pipeline/IShaderProgram.h>
#include <Graphics/Overlay/OverlayType.h>
#include <Graphics/Pipeline/TextureHelper.h>

#include <Utils/Math/Vector3.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/PoolSet.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class RenderStrategy;
    class RenderContext;
    class Overlay;
    class Window;

    class Pipeline : public SR_HTYPES_NS::SharedPtr<Pipeline> {
    public:
        using Super = SR_HTYPES_NS::SharedPtr<Pipeline>;
        using ClearColors = std::vector<SR_MATH_NS::FColor>;
        using Ptr = SR_HTYPES_NS::SharedPtr<Pipeline>;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext>;
        using WindowPtr = SR_HTYPES_NS::SharedPtr<Window>;
        using ShaderProgram = int32_t;
    public:
        explicit Pipeline(const RenderContextPtr& pContext);
        virtual ~Pipeline();


        virtual bool PreInit(const PipelinePreInitInfo& info);

        virtual bool Init();

        virtual bool PostInit() { return true; }

        virtual bool Destroy() { return true; }

        SR_NODISCARD virtual PipelineType GetType() const noexcept = 0;


        virtual void PrepareFrame();

        virtual void ClearFrameBuffersQueue();
        virtual void ResetSubmitQueue();

        virtual void DrawFrame();

        virtual bool BeginCmdBuffer();

        virtual void EndCmdBuffer();

        virtual bool BeginRender();

        virtual bool BeginCompute();

        virtual void EndCompute();

        virtual void EndRender();

        virtual void SetViewport(int32_t width = -1, int32_t height = -1) { ++m_state.operations; };
        virtual void SetScissor(int32_t width = -1, int32_t height = -1) { ++m_state.operations; };

        virtual void SwitchWindow(const WindowPtr& pWindow);

        virtual void WaitComputeIdle();
        virtual void WaitRenderIdle();

        void OnFrameBuildEnd();


        virtual bool InitOverlay();
        virtual void DestroyOverlay();
        virtual void ReCreateOverlay();
        virtual void SetOverlaySurfaceDirty();

        virtual const SR_HTYPES_NS::SharedPtr<Overlay>& GetOverlay(OverlayType overlayType) const;
        virtual void PrepareOverlay(OverlayType overlayType);
        virtual bool BeginDrawOverlay(OverlayType overlayType);
        virtual void EndDrawOverlay(OverlayType overlayType);
        virtual bool HasActiveOverlay() const;

        virtual void SetOverlayEnabled(OverlayType overlayType, bool enabled);


        SR_NODISCARD virtual std::string GetVendor() const { return "None"; }
        SR_NODISCARD virtual std::string GetRenderer() const { return "None"; }
        SR_NODISCARD virtual std::string GetVersion() const { return "None"; }

        SR_NODISCARD RenderContextPtr GetRenderContext() const noexcept { return m_renderContext; }
        SR_NODISCARD WindowPtr GetWindow() const { return m_window; }
        SR_NODISCARD ShaderPtr GetCurrentShader() const { ++m_state.operations; return m_state.pShader; }
        SR_NODISCARD FramebufferPtr GetCurrentFrameBuffer() const noexcept { ++m_state.operations; return m_state.pFrameBuffer; }
        SR_NODISCARD int32_t GetCurrentShaderId() const { ++m_state.operations; return m_state.shaderId; }
        SR_NODISCARD int32_t GetCurrentFrameBufferId() const noexcept { ++m_state.operations; return m_state.frameBufferId; }
        SR_NODISCARD int32_t GetCurrentUBO() const { ++m_state.operations; return m_state.UBOId; }
        SR_NODISCARD int32_t GetCurrentDescriptorSet() const noexcept { ++m_state.operations; return m_state.descriptorSetId; }
        SR_NODISCARD uint32_t GetCurrentFrameBufferLayer() const noexcept { ++m_state.operations; return m_state.frameBufferLayer; }
        SR_NODISCARD bool IsDirty() const noexcept { ++m_state.operations; return m_dirty; }
        SR_NODISCARD FrameBufferQueue& GetQueue() noexcept { ++m_state.operations; return m_fboQueue; }
        SR_NODISCARD RenderStrategy* GetCurrentRenderStrategy() const noexcept { ++m_state.operations; return m_state.pRenderStrategy; }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetRenderStageId() const { return m_renderStageId; }

        SR_NODISCARD virtual uint8_t GetCurrentFrameIndex() const { return 0; }
        SR_NODISCARD virtual void* GetCurrentShaderHandle() const { return nullptr; }
        SR_NODISCARD virtual void* GetCurrentFBOHandle() const { return nullptr; }
        SR_NODISCARD virtual std::set<void*> GetFBOHandles() const { return std::set<void*>();  }
        SR_NODISCARD virtual std::set<void*> GetShaderHandles() const { return std::set<void*>();  }
        SR_NODISCARD virtual uint8_t GetFrameBufferSampleCount() const { ++m_state.operations; return 0; }
        SR_NODISCARD virtual uint8_t GetBuildIterationsCount() const noexcept { ++m_state.operations; return 0; }
        SR_NODISCARD virtual uint8_t GetSupportedSamples() const noexcept { return m_supportedSampleCount; }
        SR_NODISCARD virtual bool IsShaderConstantSupport() const { ++m_state.operations; return false; }
        SR_NODISCARD virtual SR_MATH_NS::FColor GetPixelColor(uint32_t textureId, uint32_t x, uint32_t y) { return SR_MATH_NS::FColor(0.f); }
        SR_NODISCARD virtual uint16_t GetSwapchainImagesCount() const { return 0; }

        virtual void SetSwapchainImagesCount(uint16_t count) { }
        virtual void SetRenderStageId(SR_UTILS_NS::StringAtom id) { m_renderStageId = id; }
        virtual void SetCurrentShader(ShaderPtr pShader) { ++m_state.operations; m_state.pShader = pShader; }
        virtual void SetCurrentShaderId(int32_t id) { ++m_state.operations; m_state.shaderId = id; }
        virtual void SetCurrentFrameBufferLayer(uint32_t layer) { ++m_state.operations; m_state.frameBufferLayer = layer; }
        virtual void SetCurrentFrameBuffer(FramebufferPtr pFrameBuffer);
        virtual void SetCurrentRenderStrategy(RenderStrategy* pStrategy) { ++m_state.operations; m_state.pRenderStrategy = pStrategy; }

        virtual void* GetOverlayTextureDescriptorSet(uint32_t textureId, OverlayType overlayType) const;

        virtual void PipelineError(const std::string& msg) const;

        virtual void OnResize(const SR_MATH_NS::UVector2& size);

        virtual void ClearBuffers();
        virtual void ClearBuffers(float_t r, float_t g, float_t b, float_t a, float_t depth, uint8_t colorCount);
        virtual void ClearBuffers(const ClearColors& clearColors, std::optional<float_t> depth);

        virtual void ClearDepthBuffer(float_t depth);
        virtual void ClearColorBuffer(const ClearColors& clearColors);

        virtual void SetDirty(bool dirty);

        virtual uint64_t GetUsedMemory() const { return 0; }


        virtual void OnMultiSampleChanged();
        virtual void UpdateMultiSampling();
        virtual void SetSampleCount(uint8_t count);

        virtual void SetVSyncEnabled(bool enabled) { }

        SR_NODISCARD uint32_t GetFramesPerSecond() const noexcept { return m_framesPerSecond; }
        SR_NODISCARD const PipelineState& GetPreviousState() const { return m_previousState; }
        SR_NODISCARD const PipelineState& GetBuildState(uint8_t frameIndex) const;
        SR_NODISCARD const PipelineState& GetState() const { return m_state; }
        SR_NODISCARD uint8_t GetSamplesCount() const;
        SR_NODISCARD bool IsMultiSamplingSupported() const noexcept;
        SR_NODISCARD virtual bool IsVSyncEnabled() const { return false; }
        SR_NODISCARD bool IsShaderChanged() const noexcept { return m_isShaderChanged; }
        SR_NODISCARD bool IsRenderState() const noexcept { return m_isRenderState; }
        SR_NODISCARD bool IsFBOQueueValid() const noexcept;


        SR_NODISCARD virtual int32_t AllocateVBO(const void* pVertices, Vertices::VertexType type, size_t count) { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t AllocateVBO(const SR_UTILS_NS::Vertex* pVertices, Vertices::VertexType type, size_t count);
        SR_NODISCARD virtual int32_t AllocateIBO(const void* pIndices, uint32_t indexSize, size_t count, int32_t VBO) { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t AllocateUBO(uint32_t uboSize) { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t AllocateSSBO(uint32_t ssboSize, SSBOUsage usage) { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t AllocDescriptorSet(const std::vector<DescriptorType>& types) { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t AllocateShaderProgram(const SRShaderCreateInfo& createInfo, int32_t fbo) { return SR_ID_INVALID; };
        SR_NODISCARD virtual int32_t AllocateTexture(const SRTextureCreateInfo& createInfo) { return SR_ID_INVALID; };
        SR_NODISCARD virtual int32_t AllocateFrameBuffer(const SRFrameBufferCreateInfo& createInfo) { return SR_ID_INVALID; };
        SR_NODISCARD virtual int32_t AllocateCubeMap(const SRCubeMapCreateInfo& createInfo) { return SR_ID_INVALID; };

        virtual bool FreeDescriptorSet(int32_t* id) { return false; }
        virtual bool FreeVBO(int32_t* id) { return false; }
        virtual bool FreeIBO(int32_t* id) { return false; }
        virtual bool FreeUBO(int32_t* id) { return false; }
        virtual bool FreeFBO(int32_t* id) { return false; }
        virtual bool FreeSSBO(int32_t* id) { return false; }
        virtual bool FreeCubeMap(int32_t* id) { return false; }
        virtual bool FreeShader(int32_t* id) { return false; }
        virtual bool FreeTexture(int32_t* id) { return false; }

        virtual bool IsSamplerValid(int32_t id) const { return false; }


        virtual void DrawIndices(uint32_t count);

        virtual void Draw(uint32_t count);


        virtual void Dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);


        virtual void UseShader(uint32_t shaderProgram);
        virtual void UnUseShader();

        virtual void BindFrameBuffer(FramebufferPtr pFBO);

        virtual void BindVBO(uint32_t VBO);

        virtual void BindIBO(uint32_t IBO);

        virtual void BindUBO(uint32_t UBO);

        virtual void BindSSBO(uint32_t SSBO);

        virtual bool MapSSBO(uint32_t SSBO, void** ppData) { return false; }
        virtual void UnMapSSBO(uint32_t SSBO) {}

        virtual void FlushSSBO(uint32_t SSBO, uint64_t offset, uint64_t size);

        virtual void UpdateUBO(uint32_t UBO, void* pData, uint64_t size);

        virtual void UpdateSSBO(uint32_t SSBO, void* pData, uint64_t size);

        virtual void ReadSSBO(uint32_t SSBO, void* pData, uint64_t size);

        virtual void UpdateDescriptorSets(uint32_t descriptorSet, const SRDescriptorUpdateInfos& updateInfo);

        virtual void PushConstants(void* pData, uint64_t size);

        virtual void BindTexture(uint8_t activeTexture, uint32_t textureId);
        virtual void BindAttachment(uint8_t activeTexture, uint32_t textureId);

        virtual bool BindDescriptorSet(uint32_t descriptorSet);

        virtual void ResetLastShader();

    protected:
        std::map<OverlayType, SR_HTYPES_NS::SharedPtr<Overlay>> m_overlays;

        PipelinePreInitInfo m_preInitInfo;

        FrameBufferQueue m_fboQueue;

        bool m_isComputeState = false;
        bool m_isRenderState = false;
        bool m_isCmdState = false;
        bool m_enableValidationLayers = false;

        mutable uint64_t m_errorsCount = 0;

        std::atomic<bool> m_dirty = false;

        SR_UTILS_NS::StringAtom m_renderStageId;

        WindowPtr m_window;
        RenderContextPtr m_renderContext;

        SR_HTYPES_NS::PoolSet<bool> m_bindedDescriptors;

        PipelineState m_state;
        PipelineState m_previousState;
        std::vector<PipelineState> m_buildStates;

        std::optional<uint8_t> m_newSampleCount;
        uint8_t m_currentSampleCount = 0;
        uint8_t m_requiredSampleCount = 0;
        uint8_t m_supportedSampleCount = 0;
        bool m_isMultiSampleSupported = false;
        bool m_FBOForEachSwapchainImage = false;

        uint32_t m_frames = 0;
        uint32_t m_framesPerSecond = 0;
        std::optional<SR_UTILS_NS::TimePointType> m_lastSecond;

        bool m_isShaderChanged = true;

    };
}

#endif //SR_ENGINE_PIPELINE_H
```


