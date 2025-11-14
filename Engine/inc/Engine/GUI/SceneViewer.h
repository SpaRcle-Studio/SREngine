//
// Created by Monika on 11.02.2022.
//

#ifndef SR_ENGINE_SCENE_VIEWER_H
#define SR_ENGINE_SCENE_VIEWER_H

#include <Graphics/GUI/Widget.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>

namespace SR_GTYPES_NS {
    class Camera;
    class IRenderComponent;
}

namespace SR_GRAPH_NS {
    class Window;
}

namespace SR_CORE_NS {
    class Engine;
}

/**
 * Create a SceneViewer bound to the given engine and hierarchy.
 * @param pEngine Shared pointer to the Engine used for rendering and scene interaction.
 * @param hierarchy Pointer to the Hierarchy UI component associated with this viewer.
 */
/**
 * Set the scene that this viewer displays and interacts with.
 * @param scene Pointer to the Scene to display.
 */
/**
 * Enable or disable the scene viewer.
 * @param value `true` to enable the viewer, `false` to disable it.
 */
/**
 * Perform fixed-interval updates for the viewer (called by the engine tick).
 */
/**
 * Handle mouse button press events directed at the viewer.
 * @param data Pointer to mouse input data describing the event.
 */
/**
 * Handle mouse button release events directed at the viewer.
 * @param data Pointer to mouse input data describing the event.
 */
/**
 * Handle key down events while the viewer has focus.
 * @param data Pointer to keyboard input data describing the key event.
 */
/**
 * Handle key press (character) events while the viewer has focus.
 * @param data Pointer to keyboard input data describing the key press.
 */
/**
 * Position of the rendered image inside the widget.
 * @returns The image position as an FPoint.
 */
/**
 * Size of the rendered texture used by the viewer.
 * @returns The texture size as an FPoint.
 */
/**
 * The gizmo game object currently used by the viewer.
 * @returns Shared pointer to the gizmo GameObject, or `nullptr` if none is set.
 */
/**
 * Access the SceneTools instance associated with this viewer.
 * @returns Pointer to SceneTools, or `nullptr` if not available.
 */
/**
 * Select the specified mesh render component in the viewer (for editing/inspection).
 * @param pMesh Pointer to the render component to select.
 */
/**
 * Load camera configuration for the viewer from its configured source.
 */
/**
 * Backup current camera configuration maintained by the viewer.
 */
/**
 * Called when the viewer widget is closed.
 */
/**
 * Called when the viewer widget is opened.
 */
/**
 * Render the viewer contents into the widget.
 */
/**
 * Update internal view and texture sizes based on the current widget/window size.
 * @returns `true` if the view size changed and an update was performed, `false` otherwise.
 */
/**
 * Enable or disable camera controls for this viewer.
 * @param enabled `true` to enable camera controls, `false` to disable them.
 */
/**
 * Enable or disable gizmo interaction in the viewer.
 * @param enabled `true` to enable the gizmo, `false` to disable it.
 */
/**
 * Draw the provided texture within the given window area.
 * @param winSize Window size in pixels.
 * @param texSize Texture size in pixels.
 * @param id Texture identifier to draw.
 * @param centralize `true` to center the texture inside the window area, `false` to align to the origin.
 */
namespace SR_CORE_GUI_NS {
    class Hierarchy;
    class Guizmo;
    class SceneTools;

    class SR_CORE_DLL_API SceneViewer : public SR_GRAPH_GUI_NS::Widget {
        using Super = SR_GRAPH_GUI_NS::Widget;
        using GameObjectPtr = SR_UTILS_NS::GameObject::Ptr;
        using WindowPtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::Window>;
        using EnginePtr = SR_HTYPES_NS::SharedPtr<Engine>;
        SR_INLINE_STATIC const std::string CAMERA_XML = "Editor/Camera.xml";
    public:
        SceneViewer() = default;
        SceneViewer(const SR_HTYPES_NS::SharedPtr<Engine>& pEngine, Hierarchy* hierarchy);
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
        SR_NODISCARD SR_MATH_NS::FPoint GetTextureSize() const { return m_textureSize; }
        SR_NODISCARD GameObjectPtr GetGizmo() const { return m_gizmo; }

    private:
        SR_NODISCARD SR_CORE_GUI_NS::SceneTools* GetSceneTools() const;

        void SelectMesh(SR_GTYPES_NS::IRenderComponent* pMesh);

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
        SR_MATH_NS::FVector2 m_textureSize;
        SR_MATH_NS::FVector2 m_imagePosition;

        WindowPtr m_window;
        EnginePtr m_engine;

        SR_MATH_NS::FVector3 m_cameraRotation;
        SR_MATH_NS::FVector3 m_cameraTranslation;

        bool m_isPrefab = false;
        Hierarchy* m_hierarchy = nullptr;
        int32_t m_id = SR_ID_INVALID;
        GameObjectPtr m_camera;
        GameObjectPtr m_gizmo;
        GameObjectPtr m_platform;
        SR_WORLD_NS::Scene::Ptr m_scene;
        std::atomic<bool> m_enabled = true;
        bool m_updateNonHoveredSceneViewer = false;
        SR_MATH_NS::IVector2 m_windowSize;
        std::optional<Utils::CursorLock> m_cursorLock;
        SR_MATH_NS::FVector2 m_mousePos;

    };
}

#endif //SR_ENGINE_SCENE_VIEWER_H