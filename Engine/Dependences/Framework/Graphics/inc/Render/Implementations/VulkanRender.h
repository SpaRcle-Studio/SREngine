//
// Created by Nikita on 27.05.2021.
//

#ifndef GAMEENGINE_VULKANRENDER_H
#define GAMEENGINE_VULKANRENDER_H

#include <Render/Render.h>

namespace Framework::Graphics::Impl {
    class VulkanRender : public Render {
        void DrawSingleColors() noexcept override {

        }

        bool DrawSettingsPanel() noexcept override {
            return true;
        }

        void UpdateUBOs() override {
            if (m_currentCamera) {
                this->m_currentCamera->UpdateShader<ProjViewUBO>(Shader::GetDefaultGeometryShader());
                this->m_currentCamera->UpdateShader<ProjViewUBO>(m_shaders[Shader::StandardID::Transparent]);
                this->m_currentCamera->UpdateShader<SkyboxUBO>(m_shaders[Shader::StandardID::Skybox]);
            }
        }

        bool DrawDebugWireframe() override {
            return true;
        }

        bool DrawGeometry() override {
            Shader::GetDefaultGeometryShader()->Use();

            for (auto const& [key, val] : m_geometry.m_groups) {
                this->m_env->BindVBO(val[0]->GetVBO<true>());
                this->m_env->BindIBO(val[0]->GetIBO<true>());

                for (const auto& mesh : val)
                    mesh->DrawVulkan();
            }

            this->m_env->UnUseShader();

            return true;
        }

        bool DrawSkybox() override {
            if (m_skybox.m_current && m_skyboxEnabled) {
                m_shaders[Shader::StandardID::Skybox]->Use();

                m_skybox.m_current->DrawVulkan();

                m_env->UnUseShader();
            }

            return true;
        }

        bool DrawTransparentGeometry() noexcept override {
            return false;
        }

        void DrawGrid() noexcept override {

        }
    };
}

#endif //GAMEENGINE_VULKANRENDER_H
