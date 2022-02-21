//
// Created by Monika on 11.02.2022.
//

#ifndef SRENGINE_SCENEVIEWER_H
#define SRENGINE_SCENEVIEWER_H

#include <EntityComponentSystem/GameObject.h>
#include <World/Scene.h>
#include <Window/Window.h>
#include <Render/Camera.h>

namespace SR_GRAPH_NS::GUI {
    class Guizmo;

    class SceneViewer : public Widget {
    public:
        explicit SceneViewer(Graphics::Window* window);
        ~SceneViewer() override;

    public:
        void SetScene(Helper::World::Scene::Ptr scene);
        void Enable(bool value);
        void Update();

        void OnKeyDown(const KeyDownEvent& event) override;
        void OnKeyPress(const KeyPressEvent& event) override;

    private:
        void SetCameraActive(bool value);
        void OnClose() override;
        void OnOpen() override;
        void Draw() override;

        void InitCamera();
        void SetCamera(Helper::GameObject::Ptr camera);
        void DrawTexture(Helper::Math::IVector2 winSize, Helper::Math::IVector2 texSize, uint32_t id, bool centralize);
        void DrawImage(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col, bool imposition);

    private:
        Graphics::Window* m_window = nullptr;
        Guizmo* m_guizmo = nullptr;
        int32_t m_id;
        Helper::GameObject::Ptr m_camera;
        Helper::World::Scene::Ptr m_scene;
        std::atomic<bool> m_enabled = false;
        std::atomic<bool> m_cameraActive = false;
        Math::FVector3 m_rotation;
        Math::FVector3 m_translation;

    };
}

#endif //SRENGINE_SCENEVIEWER_H
