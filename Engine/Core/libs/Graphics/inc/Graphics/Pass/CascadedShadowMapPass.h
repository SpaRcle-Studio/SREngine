//
// Created by Monika on 06.06.2023.
//

#ifndef SRENGINE_CASCADEDSHADOWMAPPASS_H
#define SRENGINE_CASCADEDSHADOWMAPPASS_H

#include <Graphics/Pass/ShaderOverridePass.h>

namespace SR_GRAPH_NS {
    class CascadedShadowMapPass : public ShaderOverridePass {
        using Super = ShaderOverridePass;
    public:
        CascadedShadowMapPass(RenderTechnique* pTechnique, BasePass* pParent);

    public:
        bool Init() override;
        void DeInit() override;

        bool Render() override;
        void Update() override;

        bool Load(const SR_XML_NS::Node& passNode) override;

        SR_NODISCARD const std::vector<SR_MATH_NS::Matrix4x4>& GetCascadeMatrices() const { return m_cascadeMatrices; }

    protected:
        void UseSharedUniforms(ShaderPtr pShader) override;
        void UseConstants(ShaderPtr pShader) override;
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh) override;

        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    private:
        void UpdateCascades();

    private:
        uint32_t m_currentCascade = 0;
        uint32_t m_cascadesCount = 0;
        float_t m_cascadeSplitLambda = 0.95f;

        std::vector<SR_MATH_NS::Matrix4x4> m_cascadeMatrices;
        std::vector<float_t> m_cascadeSplitDepths;

    };
}

#endif //SRENGINE_CASCADEDSHADOWMAPPASS_H
