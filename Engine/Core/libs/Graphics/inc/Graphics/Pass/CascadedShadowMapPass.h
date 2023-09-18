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
        SR_NODISCARD const std::vector<float_t>& GetSplitDepths() const { return m_cascadeSplitDepths; }

    protected:
        void UseSharedUniforms(ShaderPtr pShader) override;
        void UseConstants(ShaderPtr pShader) override;
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh) override;

        bool CheckCamera();
        void UpdateCascades();

        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    protected:
        SR_MATH_NS::FVector3 m_cameraPosition;
        SR_MATH_NS::Quaternion m_cameraRotation;
        SR_MATH_NS::UVector2 m_screenSize;

        float_t m_near = 0.f;
        float_t m_far = 0.f;

        uint32_t m_currentCascade = 0;
        uint32_t m_cascadesCount = 0;
        float_t m_cascadeSplitLambda = 0.95f;

        bool m_usePerspective = false;

        std::vector<SR_MATH_NS::Matrix4x4> m_cascadeMatrices;
        std::vector<float_t> m_cascadeSplitDepths;

    };
}

#endif //SRENGINE_CASCADEDSHADOWMAPPASS_H
