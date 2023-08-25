//
// Created by Monika on 11.02.2022.
//

#ifndef SRENGINE_SCENEVIEWER_H
#define SRENGINE_SCENEVIEWER_H

#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>

namespace SR_GRAPH_NS::Types {
    class Camera;
}

namespace SR_GRAPH_NS {
    class Window;
}

namespace SR_CORE_NS::GUI {
    class Hierarchy;
    class Guizmo;

    class SR_DLL_EXPORT SceneViewer : public Graphics::GUI::Widget {
        using Super = Graphics::GUI::Widget;
        using GameObjectPtr = SR_UTILS_NS::GameObject::Ptr;
        using WindowPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::Window>;
        SR_INLINE_STATIC const std::string CAMERA_XML = "Editor/Camera.xml";
    public:
        explicit SceneViewer(const WindowPtr& window, Hierarchy* hierarchy);
        ~SceneViewer() override;

    public:
        void SetScene(const ScenePtr& scene) override;
        void Enable(bool value);
        void FixedUpdate() override;

        void OnMouseDown(const SR_UTILS_NS::MouseInputData* data) override;
        void OnMouseUp(const SR_UTILS_NS::MouseInputData* data) override;

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) override;

    private:
        void LoadCameraSettings();
        void BackupCameraSettings();

        void OnClose() override;
        void OnOpen() override;
        void Draw() override;

        void InitCamera();
        void SetCamera(const GameObjectPtr& camera);
        void DrawTexture(Helper::Math::IVector2 winSize, Helper::Math::IVector2 texSize, uint32_t id, bool centralize);
        void DrawImage(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col, bool imposition);

    private:
        SR_MATH_NS::IVector2 m_textureSize;
        ImVec2 m_imagePosition;

        WindowPtr m_window;

        SR_MATH_NS::FVector3 m_velocity;
        SR_MATH_NS::FVector3 m_rotation;
        SR_MATH_NS::FVector3 m_translation;

        bool m_isPrefab = false;
        Hierarchy* m_hierarchy = nullptr;
        Guizmo* m_guizmo = nullptr;
        int32_t m_id = SR_ID_INVALID;
        GameObjectPtr m_camera;
        SR_WORLD_NS::Scene::Ptr m_scene;
        std::atomic<bool> m_enabled = false;
        bool m_updateNonHoveredSceneViewer = false;

    };
}

#endif //SRENGINE_SCENEVIEWER_H
