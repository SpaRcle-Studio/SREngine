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
            this->m_flatGeometryShader->Use();

            this->m_currentCamera->UpdateShader(m_flatGeometryShader);

            if (!m_colorBuffer)
                this->m_colorBuffer = new ColorBuffer();

            this->m_colorBuffer->InitNames(this->GetAbsoluteCountMeshes());

            uint32_t id = 0;

            for (auto const& [key, val] : m_meshGroups) {
                for (m_t = 0; m_t < m_countMeshesInGroups[key]; m_t++) {
                    this->m_flatGeometryShader->SetInt("id", (int) id);
                    this->m_flatGeometryShader->SetMat4("modelMat", val[m_t]->GetModelMatrix());

                    this->m_colorBuffer->LoadName(m_t, Helper::StringUtils::IntToColor(id + 1));

                    val[m_t]->SimpleDraw();

                    id++;
                }
            }

            this->m_env->UseShader(SR_NULL_SHADER);
        }

        bool DrawSettingsPanel() noexcept override {
            if (!m_isRun)
                return false;

            ImGui::Begin("Render settings");

            ImGui::Text("Pipeline name: %s", m_env->GetPipeLineName().c_str());

            //!!!ImGui::Text("Count meshes: %zu", m_countMeshes);
            ImGui::Text("Count transparent meshes: %zu", m_countTransparentMeshes);

            ImGui::Checkbox("Grid", &m_gridEnabled);
            ImGui::Checkbox("Skybox", &m_skyboxEnabled);
            ImGui::Checkbox("WireFrame", &m_wireFrame);

            ImGui::End();

            return true;
        }

        bool DrawGeometry() override {
            Shader::GetDefaultGeometryShader()->Use();
            this->m_currentCamera->UpdateShader(Shader::GetDefaultGeometryShader());

            if (m_wireFrame) {
                this->m_env->SetDepthTestEnabled(false);
                this->m_env->SetWireFrameEnabled(true);
                this->m_env->SetCullFacingEnabled(false);

                for (auto const& [key, val] : m_meshGroups) {
                    m_env->BindVAO(key);
                    for (m_t = 0; m_t < m_countMeshesInGroups[key]; m_t++)
                        val[m_t]->DrawOpenGL();
                }

                //for (m_t = 0; m_t < m_countMeshes; m_t++)
                //    m_meshes[m_t]->DrawOpenGL();

                this->m_env->SetWireFrameEnabled(false);
                this->m_env->SetDepthTestEnabled(true);
                this->m_env->SetCullFacingEnabled(true);
            } else {
               //for (m_t = 0; m_t < m_countMeshes; m_t++)
                //    m_meshes[m_t]->DrawOpenGL();

                for (auto const& [key, val] : m_meshGroups) {
                    m_env->BindVAO(key);
                    for (m_t = 0; m_t < m_countMeshesInGroups[key]; m_t++)
                        val[m_t]->DrawOpenGL();
                }
            }

            return true;
        }

        bool DrawSkybox() override {
            //if (Helper::Debug::Profile()) { EASY_FUNCTION(profiler::colors::Coral); }

            if (m_skybox && m_skyboxEnabled) {
                //m_skyboxShader->Use();
                //m_currentCamera->UpdateShader(m_skyboxShader);
                //m_skyboxShader->SetVec3("CamPos", m_currentCamera->GetGLPosition());
                m_skybox->Draw(m_currentCamera);
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
