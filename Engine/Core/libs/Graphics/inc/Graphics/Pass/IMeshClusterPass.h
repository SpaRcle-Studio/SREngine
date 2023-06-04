//
// Created by Monika on 04.06.2023.
//

#ifndef SRENGINE_IMESHCLUSTERPASS_H
#define SRENGINE_IMESHCLUSTERPASS_H

#include <Graphics/Pass/BasePass.h>
#include <Graphics/Render/MeshCluster.h>

namespace SR_GRAPH_NS {
    class IMeshClusterPass : public BasePass {
        using Super = BasePass;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
    public:
        explicit IMeshClusterPass(RenderTechnique* pTechnique, BasePass* pParent);
        ~IMeshClusterPass() override = default;

    public:
        bool Load(const SR_XML_NS::Node& passNode) override;

        SR_NODISCARD virtual MeshClusterTypeFlag GetClusterType() const noexcept;

        bool Render() override;
        void Update() override;

    protected:
        virtual bool RenderCluster(MeshCluster& pMeshCluster);
        virtual void UpdateCluster(MeshCluster& pMeshCluster);

        virtual void UseSamplers(ShaderPtr pShader, MeshPtr pMesh);
        virtual void UseUniforms(ShaderPtr pShader) { }

    private:
        MeshClusterTypeFlag m_meshClusters = 0;

    };
}

#endif //SRENGINE_IMESHCLUSTERPASS_H
