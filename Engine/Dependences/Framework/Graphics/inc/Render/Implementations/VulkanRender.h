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
