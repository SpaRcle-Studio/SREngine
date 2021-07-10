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

        void UpdateGeometry() override {
            if (m_currentCamera) {
                this->m_currentCamera->UpdateShader(Shader::GetDefaultGeometryShader());
                this->m_currentCamera->UpdateShader(m_transparentShader);
            }
        }

        bool DrawGeometry() override {
            Shader::GetDefaultGeometryShader()->Use();

            for (auto const& [key, val] : m_geometry.m_groups) {
                this->m_env->BindVBO(val[0]->FastGetVBO());
                this->m_env->BindIBO(val[0]->FastGetIBO());

                for (m_t = 0; m_t < m_geometry.m_counters[key]; m_t++)
                    val[m_t]->DrawVulkan();
            }

            this->m_env->UnUseShader();

            return true;
        }

        bool DrawSkybox() override {

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
