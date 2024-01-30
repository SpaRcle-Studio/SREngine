//
// Created by Monika on 06.06.2023.
//

#include <Graphics/Pass/CascadedShadowMapPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(CascadedShadowMapPass);

    bool CascadedShadowMapPass::Load(const SR_XML_NS::Node& passNode) {
        m_cascadeSplitLambda = passNode.TryGetAttribute("SplitLambda").ToFloat(0.95);
        m_usePerspective = passNode.TryGetAttribute("UsePerspective").ToBool(false);
        m_near = passNode.TryGetAttribute("Near").ToFloat(0.1f);
        m_far = passNode.TryGetAttribute("Far").ToFloat(100.f);
        return Super::Load(passNode);
    }

    void CascadedShadowMapPass::UseUniforms(IMeshClusterPass::ShaderPtr pShader, IMeshClusterPass::MeshPtr pMesh) {
        SR_TRACY_ZONE;

        pMesh->UseModelMatrix();

        if (CheckCamera()) {
            UpdateCascades();
        }

        pShader->SetValue<false>(SHADER_CASCADE_LIGHT_SPACE_MATRICES, m_cascadeMatrices.data());

        const auto lightPos = GetRenderScene()->GetLightSystem()->m_position;
        pShader->SetVec3(SHADER_DIRECTIONAL_LIGHT_POSITION, lightPos);
    }

    void CascadedShadowMapPass::UpdateCascades() {
        const auto lightPos = GetRenderScene()->GetLightSystem()->m_position;

        std::vector<float_t> cascadeSplits;
        cascadeSplits.resize(m_layersCount);

        m_cascadeMatrices.resize(4);
        m_cascadeSplitDepths.resize(4);

        const float_t clipRange = m_far - m_near;

        const float_t minZ = m_near;
        const float_t maxZ = m_near + clipRange;

        const float_t range = maxZ - minZ;
        const float_t ratio = maxZ / minZ;

        for (uint32_t i = 0; i < m_layersCount; i++) {
            const float_t p = static_cast<float_t>(i + 1) / static_cast<float_t>(m_layersCount);
            const float_t log = minZ * std::pow(ratio, p);
            const float_t uniform = minZ + range * p;
            const float_t d = m_cascadeSplitLambda * (log - uniform) + uniform;
            cascadeSplits[i] = (d - m_near) / clipRange;
        }

        float_t lastSplitDist = 0.0;

        for (uint32_t i = 0; i < m_layersCount; i++) {
            const float_t splitDist = cascadeSplits[i];

            SR_MATH_NS::FVector3 frustumCorners[8] = {
                SR_MATH_NS::FVector3(-1.0f,  1.0f, -1.0f),
                SR_MATH_NS::FVector3( 1.0f,  1.0f, -1.0f),
                SR_MATH_NS::FVector3( 1.0f, -1.0f, -1.0f),
                SR_MATH_NS::FVector3(-1.0f, -1.0f, -1.0f),
                SR_MATH_NS::FVector3(-1.0f,  1.0f,  1.0f),
                SR_MATH_NS::FVector3( 1.0f,  1.0f,  1.0f),
                SR_MATH_NS::FVector3( 1.0f, -1.0f,  1.0f),
                SR_MATH_NS::FVector3(-1.0f, -1.0f,  1.0f),
            };

            auto&& invCamera = (m_camera->GetProjectionRef() * m_camera->GetViewTranslateRef()).Inverse();

            for (auto&& frustumCorner : frustumCorners) {
                SR_MATH_NS::FVector4 invCorner = invCamera * SR_MATH_NS::FVector4(frustumCorner, 1.0f);
                frustumCorner = (invCorner / invCorner.w).XYZ();
            }

            for (uint32_t j = 0; j < 4; j++) {
                SR_MATH_NS::FVector3 dist = frustumCorners[j + 4] - frustumCorners[j];
                frustumCorners[j + 4] = frustumCorners[j] + (dist * splitDist);
                frustumCorners[j] = frustumCorners[j] + (dist * lastSplitDist);
            }

            auto&& frustumCenter = SR_MATH_NS::FVector3(0.0f);
            for (auto&& frustumCorner : frustumCorners) {
                frustumCenter += frustumCorner;
            }
            frustumCenter /= 8.0f;

            float_t radius = 0.0f;
            for (auto&& frustumCorner : frustumCorners) {
                float_t distance = (frustumCorner - frustumCenter).Length();
                radius = SR_MAX(radius, distance);
            }
            radius = std::ceil(radius * 16.0f) / 16.0f;

            auto&& maxExtents = SR_MATH_NS::FVector3(radius);
            SR_MATH_NS::FVector3 minExtents = -maxExtents;

            SR_MATH_NS::FVector3 lightDir = (-lightPos).Normalize();

            SR_MATH_NS::Matrix4x4 lightViewMatrix = SR_MATH_NS::Matrix4x4::LookAt(frustumCenter - lightDir * -minExtents.z, frustumCenter, SR_MATH_NS::FVector3(0.0f, 1.0f, 0.0f));

            m_cascadeSplitDepths[i] = (m_near + splitDist * clipRange) * -1.0f;

            if (m_usePerspective) {
                /// TODO: not works
                m_cascadeMatrices[i] = m_camera->GetProjectionRef() * lightViewMatrix;
            }
            else {
                auto&& lightOrthoMatrix = SR_MATH_NS::Matrix4x4::Ortho(minExtents.x, maxExtents.x, minExtents.y, maxExtents.y, 0.0f, maxExtents.z - minExtents.z);
                m_cascadeMatrices[i] = lightOrthoMatrix * lightViewMatrix;
            }

            lastSplitDist = cascadeSplits[i];
        }
    }

    void CascadedShadowMapPass::UseConstants(IMeshClusterPass::ShaderPtr pShader) {
        pShader->SetConstInt(SHADER_SHADOW_CASCADE_INDEX, m_currentFrameBufferLayer);
        Super::UseConstants(pShader);
    }

    bool CascadedShadowMapPass::CheckCamera() {
        if (!m_camera) {
            return false;
        }

        if (m_cameraPosition.Distance(m_camera->GetPosition()) > 1.0) {
            goto dirty;
        }

        if (m_cameraRotation != m_camera->GetRotation()) {
            goto dirty;
        }

        if (m_screenSize != m_camera->GetSize()) {
            goto dirty;
        }

        return false;

    dirty:
        m_cameraPosition = m_camera->GetPosition();
        m_cameraRotation = m_camera->GetRotation();
        m_screenSize = m_camera->GetSize();

        return true;
    }
}