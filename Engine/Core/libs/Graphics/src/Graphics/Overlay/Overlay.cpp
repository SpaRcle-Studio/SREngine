//
// Created by Monika on 15.09.2023.
//

#include <Graphics/Overlay/Overlay.h>

namespace SR_GRAPH_NS {
    Overlay::Overlay(Overlay::PipelinePtr pPipeline)
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Manually)
        , m_pipeline(std::move(pPipeline))
    { }
}