//
// Created by Monika on 07.12.2022.
//

#include <Graphics/Pipeline/Pipeline.h>

#ifdef SR_DEBUG
    #define SR_PIPELINE_RENDER_GUARD(ret)              \
        if (!m_isWriteState) {                         \
            SRHalt("Missing call \"BeginRender()\"!"); \
            return ret;                                \
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
        if (m_isWriteState) {
            SRHalt("Pipeline::BeginRender() : missing call \"EndRender\"!");
            return false;
        }

        m_isWriteState = true;
        ++m_state.operations;

        return true;
    }

    void Pipeline::EndRender() {
        SR_PIPELINE_RENDER_GUARD(void())
        ++m_state.operations;
    }

    void Pipeline::DrawIndices(uint32_t countIndices) {
        SR_PIPELINE_RENDER_GUARD(void())
        ++m_state.operations;
        ++m_state.drawCalls;
    }
}
