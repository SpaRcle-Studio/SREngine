//
// Created by Nikita on 27.05.2021.
//

#ifndef GAMEENGINE_OPENGLRENDER_H
#define GAMEENGINE_OPENGLRENDER_H

#include <Render/Render.h>

namespace Framework::Graphics::Impl {
    class OpenGLRender : public Render {
    public:
        void DrawSingleColors() noexcept override {
            /*this->m_flatGeometryShader->Use();

            this->m_currentCamera->UpdateShader<ProjViewUBO>(m_flatGeometryShader);

            if (!m_colorBuffer)
                this->m_colorBuffer = new ColorBuffer();

            this->m_colorBuffer->InitNames(this->GetAbsoluteCountMeshes());

            uint32_t id = 0;

            for (auto const& [key, val] : m_geometry.m_groups) {
                for (uint32_t i = 0; i < m_geometry.m_counters[key]; i++) {
                    this->m_flatGeometryShader->SetInt("id", (int) id);
                    this->m_flatGeometryShader->SetMat4("modelMat", val[i]->GetModelMatrix());

                    this->m_colorBuffer->LoadName(i, Helper::StringUtils::IntToColor(id + 1));

                    val[i]->SimpleDraw();

                    id++;
                }
            }

            this->m_env->UseShader(SR_NULL_SHADER);*/
        }

        bool DrawSettingsPanel() noexcept override {
            if (!m_isRun)
                return false;

            ImGui::Begin("Render settings");

            ImGui::Text("Pipeline name: %s", m_env->GetPipeLineName().c_str());

            //!!!ImGui::Text("Count meshes: %zu", m_countMeshes);
            ImGui::Text("Count transparent meshes: %u", m_transparentGeometry.m_total);

            ImGui::Checkbox("Grid", &m_gridEnabled);
            ImGui::Checkbox("Skybox", &m_skyboxEnabled);
            ImGui::Checkbox("WireFrame", &m_wireFrame);

            ImGui::End();

            return true;
        }

        bool DrawDebugWireframe() override {
            return true;
        }

        bool DrawGeometry() override {
            Shader::GetDefaultGeometryShader()->Use();
            this->m_currentCamera->UpdateShader<ProjViewUBO>(Shader::GetDefaultGeometryShader());

            for (auto const& [key, val] : m_geometry.m_groups) {
                this->m_env->BindVBO(val[0]->GetVBO<true>());
                this->m_env->BindIBO(val[0]->GetIBO<true>());

                for (uint32_t i = 0; i < m_geometry.m_counters[key]; i++)
                    val[i]->DrawOpenGL();
            }

            return true;
        }

        bool DrawSkybox() override {
            //if (Helper::Debug::Profile()) { EASY_FUNCTION(profiler::colors::Coral); }

            if (m_skybox.m_current && m_skyboxEnabled) {
                m_shaders[Shader::StandardID::Skybox]->Use();
                m_currentCamera->UpdateShader<SkyboxUBO>(m_shaders[Shader::StandardID::Skybox]);

                m_skybox.m_current->DrawOpenGL();
            }

            return true;
        }

        void DrawGrid() noexcept override {
            if (!m_gridEnabled)
                return;

            if (this->m_grid)
                this->m_grid->Draw();
        }

        bool DrawTransparentGeometry() noexcept override {
            return false;
        }
    };
}

#endif //GAMEENGINE_OPENGLRENDER_H
