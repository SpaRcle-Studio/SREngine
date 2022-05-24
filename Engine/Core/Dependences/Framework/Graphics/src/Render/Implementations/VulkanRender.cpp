//
// Created by Monika on 24.04.2022.
//

#include <Render/Implementations/VulkanRender.h>

void Framework::Graphics::Impl::VulkanRender::UpdateUBOs() {
    if (!m_currentCamera) {
        return;
    }

    for (auto const& [shader, subCluster] : m_geometry.m_subClusters) {
        if (!shader || !shader->Ready()) {
            continue;
        }

        shader->SetMat4(Shader::VIEW_MATRIX, m_currentCamera->GetViewTranslateRef());
        shader->SetMat4(Shader::PROJECTION_MATRIX, m_currentCamera->GetProjectionRef());
        shader->SetFloat(Shader::TIME, clock());

        for (auto const& [key, meshGroup] : subCluster.m_groups) {
            for (const auto &mesh : meshGroup) {
                mesh->GetMaterial()->Use();

                shader->SetMat4(Shader::MODEL_MATRIX, mesh->GetModelMatrixRef());

                if (auto&& ubo = mesh->GetUBO(); ubo != SR_ID_INVALID) {
                    m_env->BindUBO(ubo);
                }
                else {
                    SRAssertOnce(false);
                }

                shader->Flush();
            }
        }
    }

    if (m_skybox) {
        auto&& shader = m_skybox->GetShader();

        if (!shader || !shader->Ready()) {
            return;
        }

        shader->SetMat4(Shader::VIEW_NO_TRANSLATE_MATRIX, m_currentCamera->GetViewRef());
        shader->SetMat4(Shader::PROJECTION_MATRIX, m_currentCamera->GetProjectionRef());
        shader->SetFloat(Shader::TIME, clock());

        if (auto&& ubo = m_skybox->GetUBO(); ubo != SR_ID_INVALID) {
            m_env->BindUBO(ubo);
        }
        else {
            SRAssertOnce(false);
        }

        shader->Flush();
    }
}

void Framework::Graphics::Impl::VulkanRender::DrawGeometry()  {
    static Environment* env = Environment::Get();

    for (auto const& [shader, subCluster] : m_geometry.m_subClusters) {
        if (!shader || shader && !shader->Use()) {
            continue;
        }

        for (auto const& [key, meshGroup] : subCluster.m_groups) {
            env->BindVBO((*meshGroup.begin())->GetVBO<true>());
            env->BindIBO((*meshGroup.begin())->GetIBO<true>());

            for (const auto &mesh : meshGroup)
                mesh->DrawVulkan();
        }

        shader->UnUse();
    }
}

void Framework::Graphics::Impl::VulkanRender::DrawSkybox()  {
    if (m_skybox) {
        auto&& shader = m_skybox->GetShader();

        if (!shader || !shader->Use()) {
            return;
        }

        m_skybox->Draw();

        shader->UnUse();
    }
}
