//
// Created by Monika on 10.10.2023.
//

#include <Graphics/Render/ScriptableRenderTechnique.h>

namespace SR_GRAPH_NS {
    ScriptableRenderTechnique::Ptr ScriptableRenderTechnique::Load(const SR_UTILS_NS::Path& path) {
        return dynamic_cast<ScriptableRenderTechnique*>(SR_SRLM_NS::LogicalMachine::Load<ScriptableRenderTechnique>(path));
    }
}