//
// Created by Monika on 07.12.2022.
//

#include <Graphics/Pipeline/Pipeline.h>
#include <Graphics/Overlay/Overlay.h>

#ifdef SR_DEBUG
    #define SR_PIPELINE_RENDER_GUARD(ret)                   \
        if (!m_isRenderState) {                             \
            SRHaltOnce("Missing call \"BeginRender()\"!");  \
            return ret;                                     \
        }                                                   \

#else
    #define SR_PIPELINE_RENDER_GUARD(ret)
#endif

namespace SR_GRAPH_NS {
    Pipeline::Pipeline(const RenderContextPtr& pContext)
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Manually)
        , m_renderContext(pContext)
    { }

    void Pipeline::DrawFrame() {
        ++m_state.operations;
        m_previousState = m_state;
        m_state = PipelineState();
    }

    bool Pipeline::BeginRender() {
        if (m_isRenderState) {
            SRHalt("Pipeline::BeginRender() : missing call \"EndRender\"!");
            return false;
        }

        m_isRenderState = true;
        ++m_state.operations;

        return true;
    }

    void Pipeline::EndRender() {
        SR_PIPELINE_RENDER_GUARD(void())
        ++m_state.operations;
    }

    void Pipeline::DrawIndices(uint32_t count) {
        SR_PIPELINE_RENDER_GUARD(void())
        ++m_state.operations;
        ++m_state.drawCalls;
    }

    void Pipeline::Draw(uint32_t count) {
        SR_PIPELINE_RENDER_GUARD(void())
        ++m_state.operations;
        ++m_state.drawCalls;
    }

    bool Pipeline::BeginCmdBuffer() {
        ++m_state.operations;
        return true;
    }

    bool Pipeline::EndCmdBuffer() {
        ++m_state.operations;
        return true;
    }

    void Pipeline::ClearFrameBuffersQueue() {
        ++m_state.operations;
    }

    void Pipeline::ClearBuffers() {
        ++m_state.operations;
    }

    void Pipeline::ClearBuffers(float_t r, float_t g, float_t b, float_t a, float_t depth, uint8_t colorCount) {
        ++m_state.operations;
    }

    void Pipeline::ClearBuffers(const std::vector<SR_MATH_NS::FColor>& colors, float_t depth) {
        ++m_state.operations;
    }

    void Pipeline::PrepareFrame() {
        ++m_state.operations;
        UpdateMultiSampling();
    }

    void Pipeline::BindVBO(uint32_t VBO) {
        ++m_state.operations;
    }

    void Pipeline::BindIBO(uint32_t IBO) {
        ++m_state.operations;
    }

    void Pipeline::BindUBO(uint32_t UBO) {
        ++m_state.operations;
    }

    void Pipeline::UpdateUBO(void* pData, uint64_t size) {
        ++m_state.operations;
        m_state.transferredMemory += size;
    }

    void Pipeline::PushConstants(void *pData, uint64_t size) {
        ++m_state.operations;
        m_state.transferredMemory += size;
    }

    void Pipeline::BindTexture(uint8_t activeTexture, uint32_t textureId) {
        ++m_state.operations;
        ++m_state.usedTextures;
    }

    void Pipeline::BindAttachment(uint8_t activeTexture, uint32_t textureId) {
        ++m_state.operations;
        ++m_state.usedTextures;
    }

    void Pipeline::BindDescriptorSet(uint32_t descriptorSet) {
        ++m_state.operations;
        m_state.descriptorSetId = static_cast<int32_t>(descriptorSet);
    }

    void Pipeline::OnResize(const SR_MATH_NS::UVector2& size) {

    }

    void Pipeline::DestroyOverlay() {

    }

    void Pipeline::OnMultiSampleChanged() {
        SR_INFO("Pipeline::OnMultiSampleChanged() : samples count was changed to " + SR_UTILS_NS::ToString(GetSamplesCount()));
        SetDirty(false);
        m_renderContext->OnMultiSampleChanged();
    }

    uint8_t Pipeline::GetSamplesCount() const {
        SRAssert(m_currentSampleCount >= 1 && m_currentSampleCount <= 64);
        return m_currentSampleCount;
    }

    void Pipeline::UpdateMultiSampling() {
        const bool isMultiSampleSupported = m_isMultiSampleSupported;

        m_isMultiSampleSupported = true;

        if (m_supportedSampleCount <= 1) {
            m_isMultiSampleSupported = false;
        }

        const bool multiSampleSupportsChanged = isMultiSampleSupported != m_isMultiSampleSupported;

        if (m_newSampleCount.has_value() || multiSampleSupportsChanged) {
            const uint8_t oldSampleCount = m_currentSampleCount;

            if (multiSampleSupportsChanged) {
                if (!IsMultiSamplingSupported()) {
                    m_currentSampleCount = 1;
                }
                else if (m_newSampleCount.has_value()) {
                    m_currentSampleCount = m_newSampleCount.value();
                }
                else {
                    m_currentSampleCount = m_requiredSampleCount;
                }
            }
            else if (m_newSampleCount.has_value()) {
                m_currentSampleCount = m_newSampleCount.value();
            }

            m_currentSampleCount = SR_MIN(m_currentSampleCount, m_supportedSampleCount);

            if (oldSampleCount != m_currentSampleCount) {
                OnMultiSampleChanged();
            }

            m_newSampleCount = std::nullopt;
        }
    }

    void Pipeline::SetBuildIteration(uint8_t iteration) {
        m_state.buildIteration = iteration;
        ++m_state.operations;
    }

    bool Pipeline::BeginDrawOverlay(OverlayType overlayType) {
        ++m_state.operations;
        ++m_state.drawCalls;

        auto&& pIt = m_overlays.find(overlayType);
        if (pIt == m_overlays.end() || !pIt->second) {
            return false;
        }

        return pIt->second->BeginDraw();
    }

    void Pipeline::EndDrawOverlay(OverlayType overlayType) {
        ++m_state.operations;

        auto&& pIt = m_overlays.find(overlayType);
        if (pIt == m_overlays.end() || !pIt->second) {
            return;
        }

        pIt->second->EndDraw();
    }

    bool Pipeline::InitOverlay() {
        return false;
    }

    void Pipeline::ReCreateOverlay() {
        ++m_state.operations;

        for (auto&& [type, pOverlay] : m_overlays) {
            if (pOverlay->ReCreate()) {
                continue;
            }

            SR_ERROR("Pipeline::ReCreateOverlay() : failed to re-create \"" + pOverlay->GetName() + "\" overlay!");
        }
    }

    void Pipeline::SetOverlaySurfaceDirty() {
        ++m_state.operations;

        for (auto&& [type, pOverlay] : m_overlays) {
            pOverlay->SetSurfaceDirty();
        }
    }

    void Pipeline::SetDirty(bool dirty) {
        m_dirty = dirty;

        if (!m_dirty) {
            m_buildState = m_state;
        }
    }
}
