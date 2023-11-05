//
// Created by Monika on 25.12.2022.
//

#include <Graphics/Memory/IGraphicsResource.h>
#include <Graphics/Pipeline/Pipeline.h>

namespace SR_GRAPH_NS::Memory {
    void IGraphicsResource::SetRenderContext(const IGraphicsResource::RenderContextPtr& renderContext) {
        m_renderContext = renderContext;
        m_pipeline = m_renderContext->GetPipeline();
        SRAssert(m_pipeline);
    }

    void IGraphicsResource::DeInitGraphicsResource() {
        m_pipeline = nullptr;
        m_renderContext = nullptr;
    }

    void IGraphicsResource::MarkPipelineUnBuild() {
        if (m_isCalculated && m_pipeline) {
            m_pipeline->SetDirty(true);
        }
    }
}
