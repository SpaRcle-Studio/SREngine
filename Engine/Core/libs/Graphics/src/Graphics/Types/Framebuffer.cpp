//
// Created by Monika on 06.05.2022.
//

#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Types/Shader.h>

namespace SR_GTYPES_NS {
    Framebuffer::Framebuffer()
        : Super(SR_COMPILE_TIME_CRC32_TYPE_NAME(Framebuffer))
    {
        SR_UTILS_NS::ResourceManager::Instance().RegisterResource(this);
    }

    Framebuffer::~Framebuffer() {
        SRAssert(m_frameBuffer == SR_ID_INVALID);

    #ifdef SR_DEBUG
        for (auto&& [texture, format] : m_colors) {
            SRAssert(texture == SR_ID_INVALID);
            SR_UNUSED_VARIABLE(format);
        }
    #endif

        SRAssert(m_depth.texture == SR_ID_INVALID);
    }

    Framebuffer::Ptr Framebuffer::Create(uint32_t images, const SR_MATH_NS::IVector2 &size) {
        std::list<ImageFormat> colors;

        for (uint32_t i = 0; i < images; ++i) {
            colors.emplace_back(ImageFormat::RGBA8_UNORM);
        }

        return Create(colors, ImageFormat::Auto, size);
    }

    Framebuffer::Ptr Framebuffer::Create(const std::list<ImageFormat> &colors, ImageFormat depth, const SR_MATH_NS::IVector2 &size) {
        return Create(colors, depth, size, 0);
    }

    Framebuffer::Ptr Framebuffer::Create(const std::list<ImageFormat>& colors, ImageFormat depth, const SR_MATH_NS::IVector2& size, uint8_t samples) {
        return Create(colors, depth, size, samples, 1);
    }

    Framebuffer::Ptr Framebuffer::Create(const std::list<ImageFormat> &colors, ImageFormat depth, const SR_MATH_NS::IVector2 &size, uint8_t samples, uint32_t layersCount) {
        return Create(colors, depth, size, samples, 1, ImageAspect::DepthStencil);
    }

    Framebuffer::Ptr Framebuffer::Create(const std::list<ImageFormat> &colors, ImageFormat depth, const SR_MATH_NS::IVector2 &size, uint8_t samples, uint32_t layersCount, ImageAspect depthAspect) {
        auto&& pFBO = new Framebuffer();

        SRAssert(!size.HasZero() && !size.HasNegative());

        if (depth == ImageFormat::Unknown) {
            SRHalt("Framebuffer::Create() : depth format is unknown!");
            return nullptr;
        }

        pFBO->SetSize(size);
        pFBO->m_depth.format = depth;
        pFBO->m_depth.aspect = depthAspect;
        pFBO->m_sampleCount = samples;
        pFBO->m_layersCount = layersCount;

        for (auto&& color : colors) {
            ColorLayer layer;
            layer.format = color;
            pFBO->m_colors.emplace_back(layer);
        }

        return pFBO;
    }

    Framebuffer::Ptr Framebuffer::Create(const std::list<ImageFormat> &colors, ImageFormat depth) {
        return Create(colors, depth, SR_MATH_NS::IVector2(0, 0));
    }

    bool Framebuffer::Bind() {
        if (m_hasErrors) {
            return false;
        }

        if (!Update()) {
            SR_ERROR("Framebuffer::Bind() : failed to initialize framebuffer!");
            return false;
        }

        m_pipeline->BindFrameBuffer(this);
        m_pipeline->SetCurrentFrameBuffer(this);

        return true;
    }

    bool Framebuffer::Update() {
        if (IsCalculated() && !m_dirty) {
            return true;
        }

        if (m_size.HasZero() || m_size.HasNegative()) {
            SR_ERROR("FrameBuffer::Update() : incorrect framebuffer size!");
            m_hasErrors = true;
            return false;
        }

        if (m_sampleCount == 0) {
            m_currentSampleCount = m_pipeline->GetSamplesCount();
        }
        else {
            m_currentSampleCount = m_sampleCount;
        }

        /// если устройство не поддерживает, то не будем пытаться использовать
        if (!m_pipeline->IsMultiSamplingSupported()) {
            m_currentSampleCount = 1;
        }
        else {
            m_currentSampleCount = SR_MIN(m_currentSampleCount, m_pipeline->GetSupportedSamples());
        }

        SRFrameBufferCreateInfo createInfo;
        createInfo.size = m_size;
        createInfo.pFBO = &m_frameBuffer;
        createInfo.pDepth = &m_depth;
        createInfo.colors = &m_colors;
        createInfo.sampleCount = m_currentSampleCount;
        createInfo.layersCount = m_layersCount;

        if (!m_pipeline->AllocateFrameBuffer(createInfo)) {
            SR_ERROR("FrameBuffer::Update() : failed to allocate frame buffer!");
            m_hasErrors = true;
            return false;
        }

        m_hasErrors = false;
        m_dirty = false;
        m_isCalculated = true;

        m_pipeline->SetDirty(true);

        return true;
    }

    void Framebuffer::FreeVideoMemory() {
        if (m_frameBuffer != SR_ID_INVALID) {
            SRVerifyFalse(!m_pipeline->FreeFBO(&m_frameBuffer));
            m_frameBuffer = SR_ID_INVALID;
        }

        if (m_depth.texture != SR_ID_INVALID) {
            SRVerifyFalse(!m_pipeline->FreeTexture(&m_depth.texture));
        }

        for (auto&& texture : m_depth.subLayers) {
            if (texture == SR_ID_INVALID) {
                continue;
            }

            SRVerifyFalse(!m_pipeline->FreeTexture(&texture));
        }

        for (auto&& [texture, format] : m_colors) {
            if (texture == SR_ID_INVALID) {
                continue;
            }

            SRVerifyFalse(!m_pipeline->FreeTexture(&texture));
        }

        IGraphicsResource::FreeVideoMemory();
    }

    void Framebuffer::SetSize(const SR_MATH_NS::IVector2 &size) {
        m_size = size;
        SetDirty();
    }

    bool Framebuffer::BeginCmdBuffer(const ClearColors& clearColors, std::optional<float_t> depth) {
        m_pipeline->ClearBuffers(clearColors, depth);

        if (!m_pipeline->BeginCmdBuffer()) {
            return false;
        }

        SR_NOOP;

        return true;
    }

    bool Framebuffer::BeginCmdBuffer() {
        m_pipeline->ClearBuffers();

        if (!m_pipeline->BeginCmdBuffer()) {
            return false;
        }

        SR_NOOP;

        return true;
    }

    bool Framebuffer::BeginRender() {
        if (!m_pipeline->BeginRender()) {
            return false;
        }

        SR_NOOP;

        return true;
    }

    void Framebuffer::EndRender() {
        m_pipeline->EndRender();
    }

    void Framebuffer::EndCmdBuffer() {
        m_pipeline->EndCmdBuffer();
    }

    int32_t Framebuffer::GetId() {
        if (m_hasErrors) {
            return SR_ID_INVALID;
        }

        if ((!IsCalculated() || m_dirty) && !Update()) {
            SR_ERROR("Framebuffer::GetId() : failed to initialize framebuffer!");
        }

        return m_frameBuffer;
    }

    uint64_t Framebuffer::GetFileHash() const {
        return 0;
    }

    int32_t Framebuffer::GetColorTexture(uint32_t layer) {
        SR_TRACY_ZONE;

        if ((!IsCalculated() || m_dirty) && !Update()) {
            SR_ERROR("Framebuffer::GetColorTexture() : failed to initialize framebuffer!");
        }

        if (layer >= m_colors.size() || m_hasErrors) {
            return SR_ID_INVALID;
        }

        return m_colors.at(layer).texture;
    }

    bool Framebuffer::BeginCmdBuffer(const SR_MATH_NS::FColor &clearColor, float_t depth) {
        return BeginCmdBuffer(Framebuffer::ClearColors{ clearColor }, depth);
    }

    uint32_t Framebuffer::GetWidth() const {
        return m_size.x;
    }

    uint32_t Framebuffer::GetHeight() const {
        return m_size.y;
    }

    void Framebuffer::SetDepthEnabled(bool depthEnabled) {
        m_depthEnabled = depthEnabled;
        m_dirty = true;
    }

    void Framebuffer::SetSampleCount(uint8_t samples) {
        m_sampleCount = samples;
        m_dirty = true;
    }

    int32_t Framebuffer::GetDepthTexture(int32_t layer) {
        if (!m_depthEnabled) {
            return SR_ID_INVALID;
        }

        if ((!IsCalculated() || m_dirty) && !Update()) {
            SR_ERROR("Framebuffer::GetDepthTexture() : failed to initialize framebuffer!");
        }

        if (layer < 0) {
            return m_depth.texture;
        }

        if (layer >= m_depth.subLayers.size()) {
            SRHalt0();
            return SR_ID_INVALID;
        }

        return m_depth.subLayers[layer];
    }

    uint8_t Framebuffer::GetSamplesCount() const {
        SRAssert(m_currentSampleCount >= 1 && m_currentSampleCount <= 64);
        return m_currentSampleCount;
    }

    void Framebuffer::SetDirty() {
        m_dirty = true;
        if (m_pipeline) {
            m_pipeline->SetDirty(true);
        }
    }

    void Framebuffer::SetLayersCount(uint32_t layersCount) {
        m_layersCount = layersCount;
        m_dirty = true;
    }

    void Framebuffer::SetDepthAspect(ImageAspect depthAspect) {
        m_depth.aspect = depthAspect;
        m_dirty = true;
    }

    void Framebuffer::SetViewportScissor() {
        m_pipeline->SetViewport(m_size.x, m_size.y);
        m_pipeline->SetScissor(m_size.x, m_size.y);
    }
}