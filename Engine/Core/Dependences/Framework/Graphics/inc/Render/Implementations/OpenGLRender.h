//
// Created by Nikita on 27.05.2021.
//

#ifndef GAMEENGINE_OPENGLRENDER_H
#define GAMEENGINE_OPENGLRENDER_H

#include <Render/Render.h>

namespace Framework::Graphics::Impl {
    class OpenGLRender : public Render {
    public:
        explicit OpenGLRender(std::string name)
            : Render(std::move(name))
        { }

        ~OpenGLRender() override = default;

    public:
        void DrawSingleColors() override {
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

        void DrawSettingsPanel() override {
            if (!m_isRun)
                return;

            ImGui::Begin("Render settings");

            ImGui::Text("Pipeline name: %s", m_env->GetPipeLineName().c_str());

            ImGui::Checkbox("Grid", &m_gridEnabled);
            ImGui::Checkbox("WireFrame", &m_wireFrame);

            ImGui::End();
        }

        void CalculateAll() override {

        }

        void DrawGeometry() override {
            SRDrawMeshCluster(m_geometry, OpenGL, {
                this->m_currentCamera->UpdateShader<ProjViewUBO>(shader);
            })
        }

        void DrawSkybox() override {
           //if (m_skybox.m_current && m_skyboxEnabled) {
            //    m_shaders[Shader::StandardID::Skybox]->Use();
            //    m_currentCamera->UpdateShader<SkyboxUBO>(m_shaders[Shader::StandardID::Skybox]);
//
            //    m_skybox.m_current->DrawOpenGL();
            //}
        }

        void DrawGrid() override {
            if (!m_gridEnabled)
                return;

            if (this->m_grid)
                this->m_grid->Draw();
        }

        void DrawTransparentGeometry() override {

        }
    };
}

#endif //GAMEENGINE_OPENGLRENDER_H
