//
// Created by Monika on 07.12.2022.
//

#include <Graphics/Pipeline/Pipeline.h>

#ifdef SR_DEBUG
    #define SR_PIPELINE_RENDER_GUARD(ret)                   \
        if (!m_isRenderState) {                             \
            SRHaltOnce("Missing call \"BeginRender()\"!");  \
            return ret;                                     \
        }

#else
    #define SR_PIPELINE_RENDER_GUARD(ret)
#endif

namespace SR_GRAPH_NS {
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

    void Pipeline::ClearFramebuffersQueue() {
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
        m_state.descriptorSetId = descriptorSet;
    }
}
