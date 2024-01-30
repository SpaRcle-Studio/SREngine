//
// Created by Monika on 06.06.2023.
//

#ifndef SR_ENGINE_CASCADED_SHADOW_MAP_PASS_H
#define SR_ENGINE_CASCADED_SHADOW_MAP_PASS_H

#include <Graphics/Pass/OffScreenMeshDrawerPass.h>

namespace SR_GRAPH_NS {
    class CascadedShadowMapPass : public OffScreenMeshDrawerPass {
        SR_REGISTER_LOGICAL_NODE(CascadedShadowMapPass, Cascaded Shadow Map Pass, { "Passes" })
        using Super = OffScreenMeshDrawerPass;
    public:
        bool Load(const SR_XML_NS::Node& passNode) override;

        SR_NODISCARD const std::vector<SR_MATH_NS::Matrix4x4>& GetCascadeMatrices() const { return m_cascadeMatrices; }
        SR_NODISCARD const std::vector<float_t>& GetSplitDepths() const { return m_cascadeSplitDepths; }

    protected:
        void UseConstants(ShaderPtr pShader) override;
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh) override;

        bool CheckCamera();
        void UpdateCascades();

    protected:
        SR_MATH_NS::FVector3 m_cameraPosition;
        SR_MATH_NS::Quaternion m_cameraRotation;
        SR_MATH_NS::UVector2 m_screenSize;

        float_t m_near = 0.f;
        float_t m_far = 0.f;

        float_t m_cascadeSplitLambda = 0.95f;

        bool m_usePerspective = false;

        std::vector<SR_MATH_NS::Matrix4x4> m_cascadeMatrices;
        std::vector<float_t> m_cascadeSplitDepths;

    };
}

#endif //SR_ENGINE_CASCADED_SHADOW_MAP_PASS_H
