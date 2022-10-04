//
// Created by Nikita on 27.05.2021.
//

#ifndef GAMEENGINE_VULKANRENDER_H
#define GAMEENGINE_VULKANRENDER_H

#include <Graphics/Render/Render.h>
#include <Graphics/Types/Skybox.h>

/*
namespace Framework::Graphics::Impl {
    class VulkanRender : public Render {
    public:
        explicit VulkanRender(std::string name)
            : Render(std::move(name))
        { }

        ~VulkanRender() override = default;

    public:
        void DrawSingleColors() override {

        }

        void DrawSettingsPanel() override {

        }

        void UpdateUBOs() override;

        void CalculateAll() override {
           //static Environment* env = Environment::Get();

           //for (auto const& [shader, subCluster] : m_geometry.m_subClusters) {
           //    if (shader) shader->Init();
           //    else
           //        continue;

           //    for (auto const& [key, meshGroup] : subCluster.m_groups) {
           //        for (const auto &mesh : meshGroup)
           //            mesh->Calculate();
           //    }
           //}
        }

        void DrawGeometry() override;

        void DrawSkybox() override;

        void DrawTransparentGeometry() override {

        }

        void DrawGrid() override {

        }
    };
}*/

#endif //GAMEENGINE_VULKANRENDER_H
