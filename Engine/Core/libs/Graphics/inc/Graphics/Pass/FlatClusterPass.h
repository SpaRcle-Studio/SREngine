//
// Created by Monika on 18.10.2023.
//

#ifndef SRENGINE_FLATCLUSTERPASS_H
#define SRENGINE_FLATCLUSTERPASS_H

#include <Graphics/Pass/IMeshClusterPass.h>

namespace SR_GRAPH_NS {
    class FlatClusterPass : public IMeshClusterPass {
        SR_REGISTER_LOGICAL_NODE(FlatClusterPass, Flat Cluster Pass, { "Passes" })
        using Super = IMeshClusterPass;
    public:
        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

        void Update() override;
        bool Render() override;

        void UseSharedUniforms(SR_GTYPES_NS::Shader* pShader) override;

        void OnClusterDirty() override;

    };
}

#endif //SRENGINE_FLATCLUSTERPASS_H
