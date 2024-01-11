//
// Created by Monika on 10.10.2023.
//

#ifndef SR_ENGINE_SCRIPTABLERENDERTECHNIQUE_H
#define SR_ENGINE_SCRIPTABLERENDERTECHNIQUE_H

#include <Graphics/Render/IRenderTechnique.h>
#include <Utils/SRLM/LogicalMachine.h>

namespace SR_GRAPH_NS {
    class ScriptableRenderTechnique : public IRenderTechnique, public SR_SRLM_NS::LogicalMachine {
    public:
        using Ptr = ScriptableRenderTechnique*;

    public:
        SR_NODISCARD static ScriptableRenderTechnique::Ptr Load(const SR_UTILS_NS::Path& path);

        void UpdateMachine(float_t dt) override;

    private:

    };
}

#endif //SR_ENGINE_SCRIPTABLERENDERTECHNIQUE_H
