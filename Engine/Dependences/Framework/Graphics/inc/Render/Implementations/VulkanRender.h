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

        bool DrawGeometry() noexcept override {
            this->m_env->ClearBuffers(0.5f, 0.5f, 0.5f, 1.f, 1.f, 1);

            for (uint8_t i = 0; i < m_env->GetCountBuildIter(); i++) {
                m_env->SetBuildIteration(i);

                m_env->BindFrameBuffer(0);

                m_env->BeginRender();

                //Shader::GetDefaultGeometryShader()->Use();

                m_env->EndRender();
            }

            return true;
        }

        bool DrawSkybox() noexcept override {

            return true;
        }

        void DrawGrid() noexcept override {

        }

        bool DrawTransparentGeometry() noexcept override {
            return false;
        }
    };
}

#endif //GAMEENGINE_VULKANRENDER_H
