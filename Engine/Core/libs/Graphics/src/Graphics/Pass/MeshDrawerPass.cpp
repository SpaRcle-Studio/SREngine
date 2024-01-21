//
// Created by Monika on 18.01.2024.
//

#include <Graphics/Pass/MeshDrawerPass.h>
#include <Graphics/Render/RenderStrategy.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Camera.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(MeshDrawerPass)

    bool MeshDrawerPass::IsLayerAllowed(SR_UTILS_NS::StringAtom layer) const {
        if (m_allowedLayers.empty()) {
            if (m_disallowedLayers.empty()) {
                return true;
            }
            return m_disallowedLayers.count(layer) == 0;
        }
        else if (m_allowedLayers.count(layer) == 1) {
            return true;
        }

        if (m_disallowedLayers.empty()) {
            return m_allowedLayers.count(layer) == 1;
        }

        return m_disallowedLayers.count(layer) == 0;
    }

    bool MeshDrawerPass::Render() {
        return (m_passWasRendered = GetRenderStrategy()->Render());
    }

    void MeshDrawerPass::Update() {
        if (m_passWasRendered) {
            GetRenderStrategy()->Update();
        }
    }

    void MeshDrawerPass::UseUniforms(ShaderPtr pShader, MeshPtr pMesh) {

    }

    void MeshDrawerPass::UseSharedUniforms(ShaderPtr pShader) {
        SR_TRACY_ZONE;

        pShader->SetFloat(SHADER_TIME, SR_HTYPES_NS::Time::Instance().Clock());

        if (m_camera) {
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());
            pShader->SetVec3(SHADER_VIEW_DIRECTION, m_camera->GetViewDirection());
            pShader->SetVec3(SHADER_VIEW_POSITION, m_camera->GetPositionRef());
        }
    }

    void MeshDrawerPass::UseConstants(ShaderPtr pShader) {

    }

    void MeshDrawerPass::UseSamplers(ShaderPtr pShader) {

    }

    void MeshDrawerPass::Bind() {
        SR_TRACY_ZONE;

        auto&& pStrategy = GetRenderStrategy();

        pStrategy->BindFilterCallback([this](auto&& layer) { return IsLayerAllowed(layer); });
        pStrategy->BindShaderReplaceCallback([this](auto&& pShader) { return ReplaceShader(pShader); });
        pStrategy->BindSharedUniformsCallback([this](auto&& pShader) { UseSharedUniforms(pShader); });
        pStrategy->BindUniformsCallback([this](auto&& pShader, auto&& pMesh) { UseUniforms(pShader, pMesh); });
        pStrategy->BindConstantsCallback([this](auto&& pShader) { UseConstants(pShader); });
        pStrategy->BindSamplersCallback([this](auto&& pShader) { UseSamplers(pShader); });

        Super::Bind();
    }

    RenderStrategy* MeshDrawerPass::GetRenderStrategy() const {
        return nullptr;
    }

    BasePass::ShaderPtr MeshDrawerPass::ReplaceShader(ShaderPtr pShader) const {
        SR_TRACY_ZONE;

        if (m_shaderReplacements.empty()) {
            return pShader;
        }

        if (auto&& pIt = m_shaderReplacements.find(pShader); pIt != m_shaderReplacements.end()) {
            return pIt->second;
        }

        return pShader;
    }
}