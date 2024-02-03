//
// Created by Monika on 11.02.2022.
//

#ifndef SR_ENGINE_SCENE_VIEWER_H
#define SR_ENGINE_SCENE_VIEWER_H

#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>

namespace SR_GRAPH_NS::Types {
    class Camera;
}

namespace SR_GRAPH_NS {
    class Window;
}

namespace SR_CORE_GUI_NS {
    class Hierarchy;
    class Guizmo;

    class SR_DLL_EXPORT SceneViewer : public SR_GRAPH_GUI_NS::Widget {
        using Super = SR_GRAPH_GUI_NS::Widget;
        using GameObjectPtr = SR_UTILS_NS::GameObject::Ptr;
        using WindowPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::Window>;
        using EnginePtr = SR_HTYPES_NS::SharedPtr<Engine>;
        SR_INLINE_STATIC const std::string CAMERA_XML = "Editor/Camera.xml";
    public:
        explicit SceneViewer(const EnginePtr& pEngine, Hierarchy* hierarchy);
        ~SceneViewer() override;

    public:
        void SetScene(const ScenePtr& scene) override;
        void Enable(bool value);
        void FixedUpdate() override;

        void OnMouseDown(const SR_UTILS_NS::MouseInputData* data) override;
        void OnMouseUp(const SR_UTILS_NS::MouseInputData* data) override;

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) override;

        SR_NODISCARD SR_MATH_NS::FPoint GetImagePosition() const;
        SR_NODISCARD SR_MATH_NS::IPoint GetTextureSize() const { return m_textureSize; }

    private:
        void SelectMesh(SR_GTYPES_NS::MeshComponent* pMesh);

        void LoadCameraSettings();
        void BackupCameraSettings();

        void OnClose() override;
        void OnOpen() override;
        void Draw() override;

        bool UpdateViewSize();

        void SetCameraEnabled(bool enabled);
        void SetGizmoEnabled(bool enabled);
        void DrawTexture(SR_MATH_NS::IVector2 winSize, SR_MATH_NS::IVector2 texSize, uint32_t id, bool centralize);

    private:
        SR_MATH_NS::IVector2 m_textureSize;
        ImVec2 m_imagePosition;

        WindowPtr m_window;
        EnginePtr m_engine;

        SR_MATH_NS::FVector3 m_velocity;
        SR_MATH_NS::FVector3 m_cameraRotation;
        SR_MATH_NS::FVector3 m_cameraTranslation;

        bool m_isPrefab = false;
        Hierarchy* m_hierarchy = nullptr;
        Guizmo* m_guizmo = nullptr;
        int32_t m_id = SR_ID_INVALID;
        GameObjectPtr m_camera;
        GameObjectPtr m_gizmo;
        GameObjectPtr m_platform;
        SR_WORLD_NS::Scene::Ptr m_scene;
        std::atomic<bool> m_enabled = true;
        bool m_updateNonHoveredSceneViewer = false;
        SR_MATH_NS::IVector2 m_windowSize;

    };
}

#endif //SR_ENGINE_SCENEVIEWER_H
