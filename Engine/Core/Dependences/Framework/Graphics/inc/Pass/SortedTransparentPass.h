//
// Created by Monika on 01.08.2022.
//

#ifndef SRENGINE_SORTEDTRANSPARENTPASS_H
#define SRENGINE_SORTEDTRANSPARENTPASS_H

#include <Pass/BasePass.h>
#include <Render/SortedMeshQueue.h>

namespace SR_GRAPH_NS {
    class SortedTransparentPass : public BasePass {
        using ShaderPtr = SR_GTYPES_NS::Shader*;
    public:
        explicit SortedTransparentPass(RenderTechnique* pTechnique);
        ~SortedTransparentPass() override = default;

    public:
        void Prepare() override;
        bool Render() override;
        void Update() override;

    private:
        SortedTransparentMeshQueue m_sorted;

    };
}

#endif //SRENGINE_SORTEDTRANSPARENTPASS_H
