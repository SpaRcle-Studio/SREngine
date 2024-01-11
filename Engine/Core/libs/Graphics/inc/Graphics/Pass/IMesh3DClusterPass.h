//
// Created by Monika on 18.10.2023.
//

#ifndef SR_ENGINE_IMESH3DCLUSTERPASS_H
#define SR_ENGINE_IMESH3DCLUSTERPASS_H

#include <Graphics/Pass/IMeshClusterPass.h>

namespace SR_GRAPH_NS {
    class IMesh3DClusterPass : public IMeshClusterPass {
        using Super = IMeshClusterPass;
    public:
        bool Init() override;

    protected:
        bool Render() override;
        void Update() override;

        void OnClusterDirty() override;

        virtual bool RenderCluster(MeshCluster& meshCluster);
        virtual void UpdateCluster(MeshCluster& meshCluster);
        virtual void MarkDirtyCluster(MeshCluster& meshCluster);

    protected:
        ShadowMapPass* m_shadowMapPass = nullptr;
        CascadedShadowMapPass* m_cascadedShadowMapPass = nullptr;

    };
}

#endif //SR_ENGINE_IMESH3DCLUSTERPASS_H
