//
// Created by Monika on 25.12.2022.
//

#include <Graphics/Memory/IGraphicsResource.h>

namespace SR_GRAPH_NS::Memory {
    void IGraphicsResource::SetRenderContext(const IGraphicsResource::RenderContextPtr& renderContext) {
        m_renderContext = renderContext;
        m_pipeline = m_renderContext->GetPipeline();
        SRAssert(m_pipeline);
    }
}
