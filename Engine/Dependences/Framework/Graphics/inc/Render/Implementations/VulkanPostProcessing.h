//
// Created by Nikita on 12.06.2021.
//

#ifndef GAMEENGINE_VULKANPOSTPROCESSING_H
#define GAMEENGINE_VULKANPOSTPROCESSING_H

#include <Render/PostProcessing.h>

namespace Framework::Graphics {
    class VulkanPostProcessing : public PostProcessing {
    private:
        ~VulkanPostProcessing() override = default;
    public:
        VulkanPostProcessing(Camera *camera) : PostProcessing(camera) {}
    public:
        void BeginGeometry() override {}
        void EndGeometry() override {}

        void BeginSkybox() override {}
        void EndSkybox() override {}
    public:
        bool Free() override {
            Helper::Debug::Graph("OpenGLPostProcessing::Free() : free post processing pointer...");
            delete this;
            return true;
        }

        bool Destroy() override {
            return PostProcessing::Destroy();
        }

        bool OnResize(uint32_t w, uint32_t h) override {
            return true;
        }
    };
}

#endif //GAMEENGINE_VULKANPOSTPROCESSING_H
