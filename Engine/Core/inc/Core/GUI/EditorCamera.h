//
// Created by Monika on 13.08.2022.
//

#ifndef SR_ENGINE_EDITOR_CAMERA_H
#define SR_ENGINE_EDITOR_CAMERA_H

#include <Graphics/Types/Camera.h>

namespace SR_CORE_GUI_NS {
    class SceneViewer;

    class EditorCamera : public SR_GTYPES_NS::Camera {
        SR_ENTITY_SET_VERSION(1000);
    public:
        EditorCamera(SceneViewer* pSceneViewer, uint32_t width, uint32_t height);

    public:
        SR_NODISCARD bool ExecuteInEditMode() const override;
        SR_NODISCARD bool IsEditorCamera() const noexcept override { return true; }

        SR_NODISCARD SR_MATH_NS::FPoint GetMousePos() const override;
        SR_NODISCARD SR_MATH_NS::FPoint GetActiveViewportSize() const override;

    private:
        SceneViewer* m_sceneViewer = nullptr;

    };
}

#endif //SR_ENGINE_EDITORCAMERA_H
