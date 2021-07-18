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
                this->m_currentCamera->UpdateShader<ProjViewUBO>(m_transparentShader);
                this->m_currentCamera->UpdateShader<SkyboxUBO>(m_skyboxShader);
            }
        }

        bool DrawGeometry() override {
            Shader::GetDefaultGeometryShader()->Use();

            for (auto const& [key, val] : m_geometry.m_groups) {
                this->m_env->BindVBO(val[0]->FastGetVBO());
                this->m_env->BindIBO(val[0]->FastGetIBO());

                for (uint32_t i = 0; i < m_geometry.m_counters[key]; i++)
                    val[i]->DrawVulkan();
            }

            this->m_env->UnUseShader();

            return true;
        }

        bool DrawSkybox() override {
            if (m_skybox && m_skyboxEnabled) {
                m_skyboxShader->Use();

                m_skybox->DrawVulkan();

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
