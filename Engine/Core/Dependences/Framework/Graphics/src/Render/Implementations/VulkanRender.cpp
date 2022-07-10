//
// Created by Monika on 24.04.2022.
//

#include <Render/Implementations/VulkanRender.h>

void Framework::Graphics::Impl::VulkanRender::UpdateUBOs() {
    if (!m_currentCamera) {
        return;
    }

    auto&& uboManager = Memory::UBOManager::Instance();
    auto&& time = clock();

    for (auto const& [shader, subCluster] : m_geometry.m_subClusters) {
        if (!shader || !shader->Ready()) {
            continue;
        }

        /**
         * TODO: нужно сделать что-то вроде SetSharedMat4, который будет биндить не в BLOCK а в SHARED_BLOCK
         */
        shader->SetMat4(Shader::VIEW_MATRIX, m_currentCamera->GetViewTranslateRef());
        shader->SetMat4(Shader::PROJECTION_MATRIX, m_currentCamera->GetProjectionRef());
        shader->SetFloat(Shader::TIME, time);

        for (auto const& [key, meshGroup] : subCluster.m_groups) {
            for (const auto &mesh : meshGroup) {
                if (!mesh->IsActive()) {
                    continue;
                }

                auto&& virtualUbo = mesh->GetVirtualUBO();
                if (virtualUbo == SR_ID_INVALID) {
                    continue;
                }

                mesh->GetMaterial()->Use();

                shader->SetMat4(Shader::MODEL_MATRIX, mesh->GetModelMatrixRef());

                if (uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
                    SR_ERROR("VulkanRender::UpdateUBOs() : memory has been duplicated!");
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
        shader->SetFloat(Shader::TIME, time);

        auto&& virtualUbo = m_skybox->GetVirtualUBO();
        if (virtualUbo == SR_ID_INVALID) {
            return;
        }

        if (uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
            SR_ERROR("VulkanRender::UpdateUBOs() : memory has been duplicated!");
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
